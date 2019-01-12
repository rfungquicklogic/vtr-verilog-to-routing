#ifndef INTERNAL_BITS_HPP
#define INTERNAL_BITS_HPP

#include <cstdint>
#include <string>
#include <algorithm>
#include "rtl_utils.hpp"

typedef uint64_t veri_internal_bits_t;

namespace BitSpace {
    typedef uint8_t bit_value_t;

    #define GET_VERI_BITWIDTH(type_in)  (sizeof(type_in)<<2) // the bitwidth /2 since we need 2 bits per veri bit

    const bit_value_t _0 = 0x0;
    const bit_value_t _1 = 0x1;
    const bit_value_t _x = 0x2;
    const bit_value_t _z = 0x3;

    /***                                                              
     * these are taken from the raw verilog truth tables so that the evaluation are correct.
     * only use this to evaluate any expression for the number_t binary digits.
     * reference: http://staff.ustc.edu.cn/~songch/download/IEEE.1364-2005.pdf
     * 
     *******************************************************/

    static const bit_value_t l_buf[4] = {
        /*	 0   1   x   z  <- a*/
            _0,_1,_x,_x
    };

    static const bit_value_t l_not[4] = {
        /*   0   1   x   z 	<- a */
            _1,_0,_x,_x
    };

    #define unroll_1d(lut) { lut[_0], lut[_1], lut[_x], lut[_z] }
    #define unroll_2d(lut) { unroll_1d(lut[_0]), unroll_1d(lut[_1]), unroll_1d(lut[_x]), unroll_1d(lut[_z]) }

    #define unroll_1d_invert(lut) { l_not[lut[_0]], l_not[lut[_1]], l_not[lut[_x]], l_not[lut[_z]] }
    #define unroll_2d_invert(lut) { unroll_1d_invert(lut[_0]), unroll_1d_invert(lut[_1]), unroll_1d_invert(lut[_x]), unroll_1d_invert(lut[_z]) }

    static const bit_value_t l_and[4][4] = {
        /* a  /	 0   1   x   z 	<-b */	
        /* 0 */	{_0,_0,_0,_0},	
        /* 1 */	{_0,_1,_x,_x},	
        /* x */	{_0,_x,_x,_x},	
        /* z */	{_0,_x,_x,_x}
    };
    static const bit_value_t l_nand[4][4] = 
        unroll_2d_invert(l_and);

    static const bit_value_t l_or[4][4] = {
        /* a  /	 0   1   x   z 	<-b */	
        /* 0 */	{_0,_1,_x,_x},	
        /* 1 */	{_1,_1,_1,_1},	
        /* x */	{_x,_1,_x,_x},	
        /* z */	{_x,_1,_x,_x}
    };
    static const bit_value_t l_nor[4][4] = 
        unroll_2d_invert(l_or);

    static const bit_value_t l_xor[4][4] = {
        /* a  /	 0   1   x   z 	<-b */	
        /* 0 */	{_0,_1,_x,_x},	
        /* 1 */	{_1,_0,_x,_x},	
        /* x */	{_x,_x,_x,_x},	
        /* z */	{_x,_x,_x,_x}
    };
    static const bit_value_t l_xnor[4][4] = 
        unroll_2d_invert(l_xor);


    /*****************************************************
     *  Tran NO SUPPORT FOR THESE YET 
     * TODO: Maybe ?? convert the z since it is technically not supported internally
     * */
    static const bit_value_t l_notif1[4][4] = {
        /* in /	 0   1   x   z 	<-control */	
        /* 0 */	{_z,_1,_x,_x},
        /* 1 */	{_z,_0,_x,_x},
        /* x */	{_z,_x,_x,_x},
        /* z */	{_z,_x,_x,_x}
    };

    static const bit_value_t l_notif0[4][4] = {
        /* in /	 0   1   x   z 	<-control */	
        /* 0 */	{_1,_z,_x,_x},
        /* 1 */	{_0,_z,_x,_x},
        /* x */	{_x,_z,_x,_x},
        /* z */	{_x,_z,_x,_x}
    };

    static const bit_value_t l_bufif1[4][4] = {
        /* in /	 0   1   x   z 	<-control */	
        /* 0 */	{_z,_0,_x,_x},
        /* 1 */	{_z,_1,_x,_x},
        /* x */	{_z,_x,_x,_x},
        /* z */	{_z,_x,_x,_x}
    };

    static const bit_value_t l_bufif0[4][4] = {
        /* in /	 0   1   x   z 	<-control */	
        /* 0 */	{_0,_z,_x,_x},
        /* 1 */	{_1,_z,_x,_x},
        /* x */	{_x,_z,_x,_x},
        /* z */	{_x,_z,_x,_x}
    };

    /* cmos gates */
    static const bit_value_t l_rpmos[4][4] = {
        /* in /	 0   1   x   z 	<-control */	
        /* 0 */	{_0,_z,_x,_x},
        /* 1 */	{_1,_z,_x,_x},
        /* x */	{_x,_z,_x,_x},
        /* z */	{_z,_z,_z,_z}
    };

    static const bit_value_t l_rnmos[4][4] = {
        /* in /	 0   1   x   z 	<-control */	
        /* 0 */	{_z,_0,_x,_x},
        /* 1 */	{_z,_1,_x,_x},
        /* x */	{_z,_x,_x,_x},
        /* z */	{_z,_z,_z,_z}
    };

    static const bit_value_t l_nmos[4][4] = {
        /* in /	 0   1   x   z 	<-control */	
        /* 0 */	{_z,_0,_x,_x},
        /* 1 */	{_z,_1,_x,_x},
        /* x */	{_z,_x,_x,_x},
        /* z */	{_z,_z,_z,_z}
    };


    // see table 5-21 p:54 IEEE 1364-2005
    static const bit_value_t l_ternary[4][4] = {
        /* in /	 0   1   x   z 	<-control */	
        /* 0 */	{_0,_x,_x,_x},
        /* 1 */	{_x,_1,_x,_x},
        /* x */	{_x,_x,_x,_x},
        /* z */	{_x,_x,_x,_x}
    };

    /*****
     * these extend the library and simplify the process
     */
    /* helper */
    static const bit_value_t l_unk[4][4] = {
        /* in /	 0   1   x   z 	<-control */	
        /* 0 */	{_x,_x,_x,_x},
        /* 1 */	{_x,_x,_x,_x},
        /* x */	{_x,_x,_x,_x},
        /* z */	{_x,_x,_x,_x}
    };

    static const bit_value_t l_case_eq[4][4] = {
        /* a  /	 0   1   x   z 	<-b */	
        /* 0 */	{_1,_0,_0,_0},	
        /* 1 */	{_0,_1,_0,_0},	
        /* x */	{_0,_0,_1,_0},	
        /* z */	{_0,_0,_0,_1}
    };

    static const bit_value_t l_case_neq[4][4] =
        unroll_2d_invert(l_case_eq);


    static const bit_value_t l_lt[4][4] = {
        /* a  /	 0   1   x   z 	<-b */	
        /* 0 */	{_0,_0,_x,_x},	
        /* 1 */	{_1,_0,_x,_x},	
        /* x */	{_x,_x,_x,_x},	
        /* z */	{_x,_x,_x,_x}
    };
    static const bit_value_t l_ge[4][4] = unroll_2d(l_lt);

    static const bit_value_t l_gt[4][4] = {
        /* a  /	 0   1   x   z 	<-b */	
        /* 0 */	{_0,_1,_x,_x},	
        /* 1 */	{_0,_0,_x,_x},	
        /* x */	{_x,_x,_x,_x},	
        /* z */	{_x,_x,_x,_x}
    };
    static const bit_value_t l_le[4][4] = unroll_2d(l_gt);

    static const bit_value_t l_eq[4][4] = 
        unroll_2d(l_xnor);

    static const bit_value_t l_sum[4][4][4] = {
        /* c_in */ 
        /* 0 */ unroll_2d(l_xor),
        /* 1 */ unroll_2d(l_xnor),
        /* x */ unroll_2d(l_unk),
        /* z */ unroll_2d(l_unk)
    };

    static const bit_value_t l_carry[4][4][4] = {
        /* c_in */
        /* 0 */ unroll_2d(l_and),
        /* 1 */ unroll_2d(l_or),
        /* x */ unroll_2d(l_ternary),
        /* z */ unroll_2d(l_ternary)
    };

    bit_value_t from_char(char val_in);
    bit_value_t from_char(char val_in)
    {
        switch(val_in)
        {
            case '0':    return _0;
            case '1':    return _1;
            case 'x':    return _x;
            default:     return _z;
        }            
    }

    char to_char(bit_value_t val_in);
    char to_char(bit_value_t val_in)
    {
        switch(val_in)
        {
            case _0:    return '0';
            case _1:    return '1';
            case _x:    return 'x';
            default:    return 'z';
        } 
    }

    bool is_unk(bit_value_t val_in);
    bool is_unk(bit_value_t val_in)
    {
        //we care about the second the bit since _x and _z has it set
        return static_cast<bool>(val_in & 0x2);
    }


    template<typename T>
    class BitFields
    {
    private :

        T bits;

        size_t get_bit_location(size_t address) const
        {
            size_t real_address = ((address%this->size())<<1);
            return real_address;
        }

    public :

        void init_values(bit_value_t init)
        {
            for(size_t i=0; i < this->size() ; i++)
            {
                this->bits |= init;
                init <<= 2;
            }
        }

        BitFields()
        {
            this->init_values(_x);
        }

        BitFields(bit_value_t initial_value)
        {
            this->init_values(initial_value);
        }        
        
        bit_value_t get_bit(size_t address) const
        {
            size_t real_address = this->get_bit_location(address);
            return (this->bits >> real_address) & 0x3;
        }

        void set_bit(size_t address, bit_value_t value)
        {	
            size_t real_address = this->get_bit_location(address);

            T long_value = value;

            T set_value = long_value << real_address;
            T zero_out_location = ~(0x3 << real_address);

            this->bits &= zero_out_location;
            this->bits |= set_value;
        }

        size_t size() const
        {
            return GET_VERI_BITWIDTH(bits)
        }

        bool has_unknowns()
        {
            //this speeds up the check quite a bit since we can do lookup by packet of 4 (2 bit per value) knowing
            //that if any even bit are set (lsb is 1) then we have an unknown
            //masking it with 10101010 does just that.. 1010 = 0x5
            return static_cast<bool>(this->bits & 0x5555555555555555);
        }

        std::string to_string(bool big_endian) const
        {
            int start =      (big_endian)? 0x0: this->size()-1;
            int end =        (big_endian)? this->size()-1: 0x0;
            int increment =  (big_endian)? 1: -1;

            std::string to_return = "";
            for(int address=start; (big_endian)? (address <= static_cast<int>(end)): (address >= static_cast<int>(end)); address += increment)
            {
                to_return.push_back(BitSpace::to_char(this->bits[to_index(address)].get_bit(address)));
            }
            return to_return;
        }
    };

    #define DEBUG_V_BITS

    /*****
     * we use large array since we process the bits in chunks
     */
    class VerilogBits
    {
    private:

        BitFields<veri_internal_bits_t> *bits;
        uint16_t bit_size;

        inline int16_t to_index(int16_t address) const
        {
            return (address >> 2);
        }

        inline size_t list_size() const
        {
            return (this->bit_size / ( GET_VERI_BITWIDTH(veri_internal_bits_t) ));
        }

    public:

        VerilogBits()
        {
        }

        VerilogBits(size_t data_size, bit_value_t value_in)
        {
            
            this->init_bits(data_size, value_in);
        }

        void init_bits(size_t data_size, bit_value_t value_in)
        {
            this->bit_size = static_cast<uint16_t>(data_size);
            this->bits = new BitFields<veri_internal_bits_t>[to_index(this->bit_size)];
            for(size_t i=0; i < to_index(this->bit_size); i++)
            {
                bits[i].init_values(value_in);
            }
        }

        size_t size() const
        {
            return bit_size;
        }

        inline bit_value_t get_bit(size_t address) const
        {
    #ifdef DEBUG_V_BITS
            assert_Werr(address < this->bit_size,
                "Bit Array index out of bounds");
    #endif
            return (this->bits[to_index(address)].get_bit(address));
        }

        inline void set_bit(size_t address, bit_value_t value)
        {
    #ifdef DEBUG_V_BITS
            assert_Werr(address < this->bit_size,
                "Bit Array index out of bounds");
    #endif
            (this->bits[to_index(address)].set_bit(address, value));
        }

        std::string to_string(bool big_endian) const
        {
            int start =      (big_endian)? 0x0: this->size()-1;
            int end =        (big_endian)? this->size()-1: 0x0;
            int increment =  (big_endian)? 1: -1;

            std::string to_return = "";
            for(int address=start; (big_endian)? (address <= static_cast<int>(end)): (address >= static_cast<int>(end)); address += increment)
            {
                to_return.push_back(BitSpace::to_char(this->bits[to_index(address)].get_bit(address)));
            }
            return to_return;
        }

        bool has_unknowns() const
        {
            bool has_it = false;
            for(size_t i =0 ; i < this->list_size() && !has_it; i++)
            {
                has_it = this->bits[i].has_unknowns();
            }
            return has_it;
        }
    }; 
}

class VNumber 
{
private:
    bool sign;
    BitSpace::VerilogBits bitstring;

public:

    VNumber(){}

    VNumber(std::string verilog_string)
    {
        set_value(verilog_string);
    }

    VNumber(long long numeric_value)
    {
        set_value(numeric_value);
    }

    VNumber(size_t len, BitSpace::bit_value_t init_bits, bool input_sign)
    {
        this->bitstring.init_bits(len, BitSpace::_0);
        this->sign = sign;
    }
    
    /***
     * getters
     */
    int64_t get_value() const
    {
        assert_Werr( (! this->bitstring.has_unknowns() ) ,
                    "Invalid Number contains dont care values. number: " + this->bitstring.to_string(false)
        );

        // We need to accomodate for signed values
        assert_Werr( (this->bitstring.size() < GET_VERI_BITWIDTH(veri_internal_bits_t)),
                    "Invalid Number. Too large to be converted. number size: " + this->bitstring.size()
        );      

        int64_t result = 0;
        int8_t pad = this->is_negative();
        for(size_t bit_index = 0; bit_index < this->size(); bit_index++)
        {
            int64_t current_bit = pad;
            if(bit_index < this->size())
                current_bit = this->bitstring.get_bit(bit_index);
   
            result |= (current_bit << bit_index);
        }

        return result;
    }

    // convert lsb_msb bitstring to verilog
    std::string to_string() const
    {
        std::string out = this->bitstring.to_string(false);
        size_t len = this->bitstring.size();

        return std::string(
            std::to_string(len) 
            + "\'sb" 
            + out
        );
    }

    /***
     * setters
     */
    void set_value(std::string verilog_string)
    {
        size_t loc = verilog_string.find("\'");
        if(loc == std::string::npos)
        {
            verilog_string.insert(0, "\'sd");
            loc = 0;
        }

        size_t bitsize = 0;
        if(loc != 0)
            bitsize = strtoul(verilog_string.substr(0,loc).c_str(), NULL, 10);

        this->sign = false;
        if(std::tolower(verilog_string[loc+1]) == 's')
            this->sign = true;

        char base = std::tolower(verilog_string[loc+1+sign]);
        size_t radix = (base == 'b') ? 2   :
                        (base == 'o') ? 8   :
                        (base == 'd') ? 10  :
                        (base == 'h') ? 16  :
                                        -1  ;

        //remove underscores
        std::string v_value_str = verilog_string.substr(loc+2+sign);
        verilog_string.erase(std::remove(v_value_str.begin(), v_value_str.end(), '_'), v_value_str.end());
        std::string temp_bitstring = string_of_radix_to_bitstring(v_value_str, radix);

        // adjust the size of the bitstring
        while(temp_bitstring.length() > 1)
        {
            if(bitsize <= 0)
            {
                if(temp_bitstring[0] == temp_bitstring[1])
                    temp_bitstring.erase(temp_bitstring.begin(),temp_bitstring.begin()+1);
                else
                    break;
            }
            else if(bitsize > temp_bitstring.length())
            {
                temp_bitstring.insert(temp_bitstring.begin(),this->get_padding_bit());
            }
            else if(bitsize < temp_bitstring.length())
            {
                temp_bitstring.erase(temp_bitstring.begin(),temp_bitstring.begin()+1);
            }
            else if(bitsize == temp_bitstring.length())
            {
                break;
            }
        }

        // convert the bits to the internal data struct the bitstring is in little endian and we switch to big endian
        this->bitstring.init_bits(temp_bitstring.size(), BitSpace::_0);
        size_t counter=temp_bitstring.size();
        for(char in: temp_bitstring)
            this->bitstring.set_bit(--counter,BitSpace::from_char(in));
    }

    void set_value(long long in)
    {
        this->set_value(std::to_string(in));
    }

    /****
     * bit twiddling functions
     */
    BitSpace::bit_value_t get_bit_from_msb(size_t index) const
    {
        return this->bitstring.get_bit(this->bitstring.size()-index);
    }

    BitSpace::bit_value_t get_bit_from_lsb(size_t index) const
    {
        return this->bitstring.get_bit(this->bitstring.size()-index);
    }

    void set_bit_from_msb(size_t index, BitSpace::bit_value_t val)
    {
        this->bitstring.set_bit(this->bitstring.size()-index, val);
    }

    void set_bit_from_lsb(size_t index, BitSpace::bit_value_t val)
    {
        this->bitstring.set_bit(index, val);
    }

    /***
     *  other
     */
    size_t size() const
    {
        return this->bitstring.size();
    }

    bool is_signed() const
    {
        return this->is_signed;
    }

    bool is_negative() const
    {
        return ( this->get_bit_from_msb(0) == BitSpace::_1 && this->sign );
    }

    BitSpace::bit_value_t get_padding_bit() const
    {
        return this->is_negative()? BitSpace::_1:BitSpace::_0;
    }

    bool is_dont_care_string() const
    {
        return this->bitstring.has_unknowns();
    }

    VNumber& twos_complement() const
    {
        VNumber to_return(this->size(), BitSpace::_0, this->is_signed());
        BitSpace::bit_value_t previous_carry = BitSpace::_1;

        for(int i=0; i<this->size(); i++)
        {
            BitSpace::bit_value_t bit_a = BitSpace::l_not[this->get_bit_from_lsb(i)];
            to_return.set_bit_from_lsb(i, BitSpace::l_xor[previous_carry][bit_a]);
            previous_carry = BitSpace::l_and[previous_carry][bit_a];
        }
        return to_return;
    }

    VNumber& copy() const
    {
        VNumber to_return(this->size(), BitSpace::_0, this->is_signed());
        for(int i=0; i<this->size(); i++)
            to_return.set_bit_from_lsb(i, this->get_bit_from_lsb(i));
        
        return to_return;
    }
};

#endif
