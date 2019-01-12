/* Authors: Aaron Graham (aaron.graham@unb.ca, aarongraham9@gmail.com),
 *           Jean-Philippe Legault (jlegault@unb.ca, jeanphilippe.legault@gmail.com) and
 *            Dr. Kenneth B. Kent (ken@unb.ca)
 *            for the Reconfigurable Computing Research Lab at the
 *             Univerity of New Brunswick in Fredericton, New Brunswick, Canada
 */

#include <string>

#include "internal_bits.hpp"
#include "rtl_int.hpp"
#include "rtl_utils.hpp"

using namespace BitSpace;

/**
 * Compare operations
 */
typedef enum
{
    LESS_THAN,
    GREATHER_THAN,
    EQUAL,
    UNKNOWN
}EVAL_RESULT;

static EVAL_RESULT eval_op(const VNumber& a_in, const VNumber& b_in)
{
	assert_Werr( a_in.size() ,
		"empty 1st bit string" 
	);

	assert_Werr( b_in.size() ,
		"empty 2nd bit string" 
	);

	bool neg_a = (a_in.is_negative());
	bool neg_b = (b_in.is_negative());

	if(neg_a && !neg_b)
		return LESS_THAN;
	else if(!neg_a && neg_b)
		return GREATHER_THAN;

	VNumber a;
	VNumber b;
	bool invert_result = (neg_a && neg_b);

	if(invert_result)
	{
		a = a_in.twos_complement();
		b = b_in.twos_complement();
	}
	else
	{
		a = a_in.get_copy();
		b = b_in.get_copy();
	}

	size_t std_length = std::max(a.size(), b.size());
	const bit_value_t pad_a = a.get_padding_bit();
	const bit_value_t pad_b = b.get_padding_bit();

	for(size_t i=std_length-1; i < std_length ; i--)
	{
		bit_value_t bit_a = pad_a;
		if(i < a.size())
			bit_a = a.get_bit_from_lsb(i);

		bit_value_t bit_b = pad_b;
		if(i < b.size())
			bit_b = b.get_bit_from_lsb(i);

		if	(bit_a == BitSpace::_x || bit_b == BitSpace::_x)	
			return UNKNOWN;
		else if(bit_a != bit_b)
		{
			if(bit_a == BitSpace::_1)
				return (invert_result)? LESS_THAN: GREATHER_THAN;
			else
				return (invert_result)? GREATHER_THAN: LESS_THAN;
		}
	}
	return EQUAL;
}

static EVAL_RESULT eval_op(veri_internal_bits_t a, VNumber b)
{
	VNumber bits_value = VNumber(std::to_string(a));
	return eval_op(bits_value, b);
}

static EVAL_RESULT eval_op(VNumber a,veri_internal_bits_t b)
{
	VNumber bits_value = VNumber(std::to_string(b));
	return eval_op(a, bits_value);
}

bit_value_t bit_eval(EVAL_RESULT evaluate_to, bool invert_evaluation, const VNumber& a, const VNumber& b)
{
	EVAL_RESULT evaluate = eval_op(a,b);
	return 	(evaluate == UNKNOWN) 							?	BitSpace::_x :
			(invert_evaluation && evaluate != LESS_THAN ) 	?	BitSpace::_1 :
			(!invert_evaluation && evaluate == LESS_THAN ) 	?	BitSpace::_1 :
																BitSpace::_0 ;
}

/**
 * Unary Reduction operations
 */
static bit_value_t reduce_op(const VNumber& a, const bit_value_t lut[4][4])
{
	assert_Werr( a.size() ,
		"empty bit string" 
	);

	bit_value_t result = a.get_bit_from_lsb(0);
	for(size_t i=1; i < a.size(); i++)
	{
		result = lut[result][a.get_bit_from_lsb(i)];
	}

	return result;
}

/**
 * Binary Reduction operations
 */
static VNumber& redux_op(const VNumber& a, const VNumber& b, const bit_value_t lut[4][4])
{
	assert_Werr( a.size() ,
		"empty 1st bit string" 
	);

	assert_Werr( b.size() ,
		"empty 2nd bit string" 
	);

	size_t std_length = std::max(a.size(), b.size());
	const bit_value_t pad_a = a.get_padding_bit();
	const bit_value_t pad_b = b.get_padding_bit();

	VNumber result(std_length, _x, false);

	for(size_t i=0; i < result.size(); i++)
	{
		bit_value_t bit_a = pad_a;
		if(i < a.size())
			bit_a = a.get_bit_from_lsb(i);

		bit_value_t bit_b = pad_b;
		if(i < b.size())
			bit_b = b.get_bit_from_lsb(i);

		result.set_bit_from_lsb(i, lut[bit_a][bit_b]);
	}

	return result;
}

/**
 * Addition operations
 */
static VNumber& sum_op(const VNumber& a, const VNumber& b, const bit_value_t& initial_carry)
{
	assert_Werr( a.size() ,
		"empty 1st bit string" 
	);

	assert_Werr( b.size() ,
		"empty 2nd bit string" 
	);

	size_t std_length = std::max(a.size(), b.size());
	const bit_value_t pad_a = a.get_padding_bit();
	const bit_value_t pad_b = b.get_padding_bit();

	bit_value_t previous_carry = initial_carry;
	VNumber result(std_length+1, _x, false);

	for(size_t i=0; i < std_length-1; i++)
	{
		bit_value_t bit_a = pad_a;
		if(i < a.size())
			bit_a = a.get_bit_from_lsb(i);

		bit_value_t bit_b = pad_b;
		if(i < b.size())
			bit_b = b.get_bit_from_lsb(i);

		result.set_bit_from_lsb(i, l_sum[previous_carry][bit_a][bit_b]);
		previous_carry = l_carry[previous_carry][bit_a][bit_b];
	}
	result.set_bit_from_lsb(std_length-1, previous_carry);

	return result;
}

static VNumber& shift_op(const VNumber& a, int64_t b, bool sign_shift)
{
	VNumber to_return;
	if(b < static_cast<int64_t>(a.size()))
		b = 0;

	//if b is negative than shift right
	if(b==0)
	{
		to_return = a.get_copy();
	}
	else if(b < 0)
	{
		bit_value_t pad = ( sign_shift ) ? a.get_padding_bit(): BitSpace::_0;
		to_return = VNumber(a.size(), pad, sign_shift);
		for(size_t i=0; i < (a.size() + b); i++)
		{
			to_return.set_bit_from_lsb(i, a.get_bit_from_lsb(i-b));
		}
	}
	else
	{
		bit_value_t pad = BitSpace::_0;
		to_return =VNumber((a.size() + b), pad, sign_shift);
		for(size_t i=0; i < a.size(); i++)
		{
			to_return.set_bit_from_lsb(i+b, a.get_bit_from_lsb(i));
		}
	}
	return to_return;
}

bool V_TRUE(VNumber a)
{
	return	( reduce_op(a,l_or) == BitSpace::_1 );
}

/***
 *                    __          __   __   ___  __       ___    __       
 *    |  | |\ |  /\  |__) \ /    /  \ |__) |__  |__)  /\   |  | /  \ |\ | 
 *    \__/ | \| /~~\ |  \  |     \__/ |    |___ |  \ /~~\  |  | \__/ | \| 
 *                                                                        
 */

VNumber& V_BITWISE_NOT(const VNumber& a)
{
	assert_Werr( a.size() ,
		"empty bit string" 
	);

	VNumber to_return(a.size(), BitSpace::_0, false);
	for(size_t i=0; i <a.size(); i++)
		to_return.set_bit_from_lsb(i, l_not[a.get_bit_from_lsb(i)]);
	return to_return;
}

VNumber& V_LOGICAL_NOT(const VNumber& a)
{
	VNumber to_return(1, l_not[reduce_op(a,l_or)], false);
	return to_return;
}

VNumber& V_ADD(const VNumber& a)
{
	VNumber result(a);
	return result;
}

VNumber& V_MINUS(const VNumber& a)
{
	return a.twos_complement();
}

VNumber& V_BITWISE_AND(const VNumber& a)
{
	VNumber to_return(1, reduce_op(a, l_and), false);
	return to_return;
}

VNumber& V_BITWISE_OR(const VNumber& a)
{
	VNumber to_return(1, reduce_op(a, l_or), false);
	return to_return;
}

VNumber& V_BITWISE_XOR(const VNumber& a)
{
	VNumber to_return(1, reduce_op(a, l_xor), false);
	return to_return;
}

VNumber& V_BITWISE_NAND(const VNumber& a)
{
	VNumber to_return(1, reduce_op(a, l_nand), false);
	return to_return;
}

VNumber& V_BITWISE_NOR(const VNumber& a)
{
	VNumber to_return(1, reduce_op(a, l_nor), false);
	return to_return;
}

VNumber& V_BITWISE_XNOR(const VNumber& a)
{
	VNumber to_return(1, reduce_op(a, l_xnor), false);
	return to_return;
}

/***
 *     __               __          __   __   ___  __       ___    __       
 *    |__) | |\ |  /\  |__) \ /    /  \ |__) |__  |__)  /\   |  | /  \ |\ | 
 *    |__) | | \| /~~\ |  \  |     \__/ |    |___ |  \ /~~\  |  | \__/ | \| 
 *                                                                          
 */

VNumber& V_BITWISE_AND(const VNumber& a, const VNumber& b)
{
	return redux_op(a,b,l_and);
}

VNumber& V_BITWISE_OR(const VNumber& a, const VNumber& b)
{
	return redux_op(a,b,l_or);
}

VNumber& V_BITWISE_XOR(const VNumber& a, const VNumber& b)
{
	return redux_op(a,b,l_xor);
}

VNumber& V_BITWISE_NAND(const VNumber& a, const VNumber& b)
{
	return redux_op(a,b,l_nand);
}

VNumber& V_BITWISE_NOR(const VNumber& a, const VNumber& b)
{
	return redux_op(a,b,l_nor);
}

VNumber& V_BITWISE_XNOR(const VNumber& a, const VNumber& b)
{
	return redux_op(a,b,l_xnor);
}

/**
 * Logical Operations
 */

VNumber& V_CASE_EQUAL(const VNumber& a, const VNumber& b)
{
	return redux_op(a, b, l_case_eq);
}

VNumber& V_CASE_NOT_EQUAL(const VNumber& a, const VNumber& b)
{
	return redux_op(a, b, l_case_neq);
}

VNumber& V_LOGICAL_AND(const VNumber& a, const VNumber& b)
{
	bit_value_t bit_a = reduce_op(a, l_or);
	bit_value_t bit_b = reduce_op(b, l_or);

	VNumber to_return(1, l_and[bit_a][bit_b], false);

	return to_return;
}

VNumber& V_LOGICAL_OR(const VNumber& a, const VNumber& b)
{
	bit_value_t bit_a = reduce_op(a, l_or);
	bit_value_t bit_b = reduce_op(b, l_or);

	VNumber to_return(1, l_or[bit_a][bit_b], false);

	return to_return;
}

VNumber& V_LT(const VNumber& a, const VNumber& b)
{
	VNumber to_return(1, bit_eval(LESS_THAN, false, a, b), false);
	return to_return;
}

VNumber& V_GT(const VNumber& a, const VNumber& b)
{
	VNumber to_return(1, bit_eval(GREATHER_THAN, false, a, b), false);
	return to_return;
}

VNumber& V_EQUAL(const VNumber& a, const VNumber& b)
{
	VNumber to_return(1, bit_eval(EQUAL, false, a, b), false);
	return to_return;
}

VNumber& V_GE(const VNumber& a, const VNumber& b)
{
	VNumber to_return(1, bit_eval(LESS_THAN, true, a, b), false);
	return to_return;
}

VNumber& V_LE(const VNumber& a, const VNumber& b)
{
	VNumber to_return(1, bit_eval(GREATHER_THAN, true, a, b), false);
	return to_return;
}

VNumber& V_NOT_EQUAL(const VNumber& a, const VNumber& b)
{
	VNumber to_return(1, bit_eval(EQUAL, true, a, b), false);
	return to_return;
}

VNumber& V_SIGNED_SHIFT_LEFT(const VNumber& a, const VNumber& b)
{
	if(b.is_dont_care_string())	
		return VNumber("x");
	
	return shift_op(a, b.get_value(), true);
}

VNumber& V_SHIFT_LEFT(const VNumber& a, const VNumber& b)
{
	if(b.is_dont_care_string())	
		return VNumber("x");
	
	return shift_op(a, b.get_value(), false);
}

VNumber& V_SIGNED_SHIFT_RIGHT(const VNumber& a, const VNumber& b)
{
	if(b.is_dont_care_string())	
		return VNumber("x");
	
	return shift_op(a, -1* b.get_value(), true);
}

VNumber& V_SHIFT_RIGHT(const VNumber& a, const VNumber& b)
{
	if(b.is_dont_care_string())	
		return VNumber("x");
	
	return shift_op(a, -1* b.get_value(), false);
}

VNumber& V_ADD(const VNumber& a, const VNumber& b)
{
	return sum_op(a, b, _0);
}

VNumber& V_MINUS(const VNumber& a, const VNumber& b)
{
	VNumber complement = V_MINUS(b);
	return sum_op(a, complement, _1);
}

VNumber& V_MULTIPLY(const VNumber& a_in, const VNumber& b_in)
{
	if(a_in.is_dont_care_string() || b_in.is_dont_care_string())
		return VNumber("x");

	VNumber a;
	VNumber b;

	bool neg_a = a_in.is_negative();
	bool neg_b = b_in.is_negative();
	
	if(neg_a)	
		a = V_MINUS(a_in);
	else
		a = a_in;

	if(neg_b)	
		b = V_MINUS(b_in);
	else
		b = b_in;
		
	bool invert_result = ((!neg_a && neg_b) || (neg_a && !neg_b));

	//TODO this won't work
	VNumber result("0");
	VNumber b_copy = b;

	for(size_t i=0; i< a.size(); i++)
	{
		bit_value_t bit_a = a.get_bit_from_lsb(i) /* TODO: This or: bits_from_msb(i)*/;
		if(bit_a == _1)
			result = V_ADD(result,b);
		shift_op(b_copy, 1, _0);
	}

	if(invert_result)	
		result = V_MINUS(result);

	return result;
}

VNumber& V_POWER(const VNumber& a, const VNumber& b)
{
	if(a.is_dont_care_string() || b.is_dont_care_string())
		return VNumber("xxxx");
	
	EVAL_RESULT res_a = eval_op(a, 0);
	short val_a = 	(res_a == EQUAL) 			? 	0: 
					(res_a == LESS_THAN) 		? 	((eval_op(a,-1) == LESS_THAN))	?	-2: -1:
					/* GREATHER_THAN */  			((eval_op(a,1) == GREATHER_THAN))	?	2: 1;

	EVAL_RESULT res_b = eval_op(b, 0);
	short val_b = 	(res_b == EQUAL) 			? 	0: 
					(res_b == LESS_THAN) 		? 	-1:
					/* GREATHER_THAN */				1;

	//TODO this won't work

	//compute
	if(val_b == 1 && (val_a < -1 || val_a > 1 ))
	{
		VNumber result("1");
		
		VNumber tmp_b = b;
		while(eval_op(tmp_b,0) == GREATHER_THAN)
		{
			tmp_b = V_MINUS(tmp_b, VNumber("1"));
			result = V_MULTIPLY( result, a);
		}
		return result;
	}
	if (val_b == 0 || val_a == 1)	
	{
		return VNumber("1000");
	}
	else if(val_b == -1 && val_a == 0)
	{
		return VNumber("xxxx");
	}
	else if(val_a == -1)
	{
		if(a.is_negative()) 	// even
			return VNumber("0111");
		else				//	odd
			return VNumber("1000");
	}
	else	
	{
		return VNumber("0000");
	}
}

//TODO this won't work
/////////////////////////////
VNumber& V_DIV(const VNumber& a_in, const VNumber& b)
{
	if(a_in.is_dont_care_string() || b.is_dont_care_string() || eval_op(b,0) == EQUAL)
		return VNumber("x");

	VNumber a(a_in);

	VNumber result("0");
	//TODO signed division!
	while(eval_op(a, b) == GREATHER_THAN )
	{
		VNumber  count("1");
		VNumber  sub_with = b;
		VNumber  tmp = b;
		while(eval_op(tmp, a) == LESS_THAN)
		{
			sub_with = tmp;
			shift_op(count, 1,_0);
			shift_op(tmp, 1,_0);
		}
		a = V_MINUS(a, sub_with);
		result = V_ADD(result, count);
	}
	return result;
}

VNumber& V_MOD(const VNumber& a_in, const VNumber& b)
{
	if(a_in.is_dont_care_string() || b.is_dont_care_string() || eval_op(b, 0) == EQUAL)
		return VNumber("x");

	VNumber to_return(a_in);
	//TODO signed division!
	while(eval_op(b, to_return)  == LESS_THAN)
	{
		VNumber  sub_with = b;
		for( VNumber  tmp = b; eval_op(tmp, to_return) == LESS_THAN; shift_op(tmp, 1,_0))
		{
			sub_with = tmp;
		}
		to_return = V_MINUS(to_return, sub_with);
	}
	return to_return;
}

/***
 *    ___  ___  __             __          __   __   ___  __       ___    __       
 *     |  |__  |__) |\ |  /\  |__) \ /    /  \ |__) |__  |__)  /\   |  | /  \ |\ | 
 *     |  |___ |  \ | \| /~~\ |  \  |     \__/ |    |___ |  \ /~~\  |  | \__/ | \| 
 *                                                                                 
*/
VNumber& V_TERNARY(const VNumber& a_in, const VNumber& b_in, const VNumber& c_in)
{
	/*	if a evaluates properly	*/
	EVAL_RESULT eval = eval_op(V_LOGICAL_NOT(a_in),0);

	if(eval == UNKNOWN)		return redux_op(b_in, c_in, l_ternary);
	else if(eval == EQUAL)	return VNumber(b_in);
	else					return VNumber(c_in);
}
