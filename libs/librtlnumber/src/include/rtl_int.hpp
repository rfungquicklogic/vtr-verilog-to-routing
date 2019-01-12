/* Authors: Aaron Graham (aaron.graham@unb.ca, aarongraham9@gmail.com),
 *           Jean-Philippe Legault (jlegault@unb.ca, jeanphilippe.legault@gmail.com) and
 *            Dr. Kenneth B. Kent (ken@unb.ca)
 *            for the Reconfigurable Computing Research Lab at the
 *             Univerity of New Brunswick in Fredericton, New Brunswick, Canada
 */

#ifndef RTL_INT_H
#define RTL_INT_H

#include <string>
#include "internal_bits.hpp"

/**
 * Unary Operator
 */

bool V_TRUE(const VNumber& a);

VNumber&  V_ADD(const VNumber& a);
VNumber&  V_MINUS(const VNumber& a);

VNumber&  V_BITWISE_NOT(const VNumber& a);
VNumber&  V_BITWISE_AND(const VNumber& a);
VNumber&  V_BITWISE_OR(const VNumber& a);
VNumber&  V_BITWISE_XOR(const VNumber& a);
VNumber&  V_BITWISE_NAND(const VNumber& a);
VNumber&  V_BITWISE_NOR(const VNumber& a);
VNumber&  V_BITWISE_XNOR(const VNumber& a);
VNumber&  V_LOGICAL_NOT(const VNumber& a);

/**
 * Binary Operator
 */
VNumber&  V_BITWISE_AND(const VNumber& a,const VNumber& b);
VNumber&  V_BITWISE_OR(const VNumber& a,const VNumber& b);
VNumber&  V_BITWISE_XOR(const VNumber& a,const VNumber& b);
VNumber&  V_BITWISE_NAND(const VNumber& a,const VNumber& b);
VNumber&  V_BITWISE_NOR(const VNumber& a,const VNumber& b);
VNumber&  V_BITWISE_XNOR(const VNumber& a,const VNumber& b);

VNumber&  V_SIGNED_SHIFT_LEFT(const VNumber& a, VNumber b);
VNumber&  V_SIGNED_SHIFT_RIGHT(const VNumber& a, VNumber b);
VNumber&  V_SHIFT_LEFT(const VNumber& a, VNumber b);
VNumber&  V_SHIFT_RIGHT(const VNumber& a, VNumber b);

VNumber&  V_LOGICAL_AND(const VNumber& a,const VNumber& b);
VNumber&  V_LOGICAL_OR(const VNumber& a,const VNumber& b);

VNumber&  V_LT(const VNumber& a,const VNumber& b);
VNumber&  V_GT(const VNumber& a,const VNumber& b);
VNumber&  V_LE(const VNumber& a,const VNumber& b);
VNumber&  V_GE(const VNumber& a,const VNumber& b);
VNumber&  V_EQUAL(const VNumber& a,const VNumber& b);
VNumber&  V_NOT_EQUAL(const VNumber& a,const VNumber& b);
VNumber&  V_CASE_EQUAL(const VNumber& a,const VNumber& b);
VNumber&  V_CASE_NOT_EQUAL(const VNumber& a,const VNumber& b);

VNumber&  V_ADD(const VNumber& a,const VNumber& b);
VNumber&  V_MINUS(const VNumber& a,const VNumber& b);
VNumber&  V_MULTIPLY(const VNumber& a,const VNumber& b);
VNumber&  V_POWER(const VNumber& a,const VNumber& b);
VNumber&  V_DIV(const VNumber& a,const VNumber& b);
VNumber&  V_MOD(const VNumber& a,const VNumber& b);

/**
 * Ternary Operator
 */
VNumber  V_TERNARY(VNumber a, VNumber b, VNumber c);

inline VNumber& operator!(const VNumber& a){ return V_LOGICAL_NOT(a); }
inline VNumber& operator~(const VNumber& a){ return V_BITWISE_NOT(a); }

inline VNumber& operator-(const VNumber& a){ return V_MINUS(a); }
inline VNumber& operator+(const VNumber& a){ return V_ADD(a); }

inline VNumber& operator&(const VNumber& a, const VNumber& b){ return V_BITWISE_AND(a,b); }
inline VNumber& operator|(const VNumber& a, const VNumber& b){ return V_BITWISE_OR(a,b); }
inline VNumber& operator^(const VNumber& a, const VNumber& b){ return V_BITWISE_XOR(a,b); }

inline VNumber& operator<<(const VNumber& a, const VNumber& b){ return V_SHIFT_LEFT(a,b); }
inline VNumber& operator>>(const VNumber& a, const VNumber& b){ return V_SHIFT_RIGHT(a,b); }

inline VNumber& operator&&(const VNumber& a, const VNumber& b){ return V_LOGICAL_AND(a,b); }
inline VNumber& operator||(const VNumber& a, const VNumber& b){ return V_LOGICAL_OR(a,b); }
inline VNumber& operator<(const VNumber& a, const VNumber& b){ return V_LT(a,b); }
inline VNumber& operator>(const VNumber& a, const VNumber& b){ return V_GT(a,b); }
inline VNumber& operator<=(const VNumber& a, const VNumber& b){ return V_LE(a,b); }
inline VNumber& operator>=(const VNumber& a, const VNumber& b){ return V_GE(a,b); }
inline VNumber& operator==(const VNumber& a, const VNumber& b){ return V_EQUAL(a,b); }
inline VNumber& operator!=(const VNumber& a, const VNumber& b){ return V_NOT_EQUAL(a,b); }

inline VNumber& operator+(const VNumber& a, const VNumber& b){ return V_ADD(a,b); }
inline VNumber& operator-(const VNumber& a, const VNumber& b){ return V_MINUS(a,b); }
inline VNumber& operator*(const VNumber& a, const VNumber& b){ return V_MULTIPLY(a,b); }
inline VNumber& operator/(const VNumber& a, const VNumber& b){ return V_DIV(a,b); }
inline VNumber& operator%(const VNumber& a, const VNumber& b){ return V_MOD(a,b); }

#endif //RTL_INT_H
