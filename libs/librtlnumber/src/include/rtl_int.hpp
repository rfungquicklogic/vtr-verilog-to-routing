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

bool V_TRUE(VNumber& a);

VNumber V_ADD(VNumber& a);
VNumber V_MINUS(VNumber& a);

VNumber V_BITWISE_NOT(VNumber& a);
VNumber V_BITWISE_AND(VNumber& a);
VNumber V_BITWISE_OR(VNumber& a);
VNumber V_BITWISE_XOR(VNumber& a);
VNumber V_BITWISE_NAND(VNumber& a);
VNumber V_BITWISE_NOR(VNumber& a);
VNumber V_BITWISE_XNOR(VNumber& a);
VNumber V_LOGICAL_NOT(VNumber& a);

/**
 * Binary Operator
 */
VNumber V_BITWISE_AND(VNumber& a,VNumber& b);
VNumber V_BITWISE_OR(VNumber& a,VNumber& b);
VNumber V_BITWISE_XOR(VNumber& a,VNumber& b);
VNumber V_BITWISE_NAND(VNumber& a,VNumber& b);
VNumber V_BITWISE_NOR(VNumber& a,VNumber& b);
VNumber V_BITWISE_XNOR(VNumber& a,VNumber& b);

VNumber V_SIGNED_SHIFT_LEFT(VNumber& a, VNumber& b);
VNumber V_SIGNED_SHIFT_RIGHT(VNumber& a, VNumber& b);
VNumber V_SHIFT_LEFT(VNumber& a, VNumber& b);
VNumber V_SHIFT_RIGHT(VNumber& a, VNumber& b);

VNumber V_LOGICAL_AND(VNumber& a,VNumber& b);
VNumber V_LOGICAL_OR(VNumber& a,VNumber& b);

VNumber V_LT(VNumber& a,VNumber& b);
VNumber V_GT(VNumber& a,VNumber& b);
VNumber V_LE(VNumber& a,VNumber& b);
VNumber V_GE(VNumber& a,VNumber& b);
VNumber V_EQUAL(VNumber& a,VNumber& b);
VNumber V_NOT_EQUAL(VNumber& a,VNumber& b);
VNumber V_CASE_EQUAL(VNumber& a,VNumber& b);
VNumber V_CASE_NOT_EQUAL(VNumber& a,VNumber& b);

VNumber V_ADD(VNumber& a,VNumber& b);
VNumber V_MINUS(VNumber& a,VNumber& b);
VNumber V_MULTIPLY(VNumber& a,VNumber& b);
VNumber V_POWER(VNumber& a,VNumber& b);
VNumber V_DIV(VNumber& a,VNumber& b);
VNumber V_MOD(VNumber& a,VNumber& b);

/**
 * Ternary Operator
 */
VNumber V_TERNARY(VNumber& a, VNumber& b, VNumber& c);

inline VNumber operator!(VNumber& a){ return V_LOGICAL_NOT(a); }
inline VNumber operator~(VNumber& a){ return V_BITWISE_NOT(a); }

inline VNumber operator-(VNumber& a){ return V_MINUS(a); }
inline VNumber operator+(VNumber& a){ return V_ADD(a); }

inline VNumber operator&(VNumber& a, VNumber& b){ return V_BITWISE_AND(a,b); }
inline VNumber operator|(VNumber& a, VNumber& b){ return V_BITWISE_OR(a,b); }
inline VNumber operator^(VNumber& a, VNumber& b){ return V_BITWISE_XOR(a,b); }

inline VNumber operator<<(VNumber& a, VNumber& b){ return V_SHIFT_LEFT(a,b); }
inline VNumber operator>>(VNumber& a, VNumber& b){ return V_SHIFT_RIGHT(a,b); }

inline VNumber operator&&(VNumber& a, VNumber& b){ return V_LOGICAL_AND(a,b); }
inline VNumber operator||(VNumber& a, VNumber& b){ return V_LOGICAL_OR(a,b); }
inline VNumber operator<(VNumber& a, VNumber& b){ return V_LT(a,b); }
inline VNumber operator>(VNumber& a, VNumber& b){ return V_GT(a,b); }
inline VNumber operator<=(VNumber& a, VNumber& b){ return V_LE(a,b); }
inline VNumber operator>=(VNumber& a, VNumber& b){ return V_GE(a,b); }
inline VNumber operator==(VNumber& a, VNumber& b){ return V_EQUAL(a,b); }
inline VNumber operator!=(VNumber& a, VNumber& b){ return V_NOT_EQUAL(a,b); }

inline VNumber operator+(VNumber& a, VNumber& b){ return V_ADD(a,b); }
inline VNumber operator-(VNumber& a, VNumber& b){ return V_MINUS(a,b); }
inline VNumber operator*(VNumber& a, VNumber& b){ return V_MULTIPLY(a,b); }
inline VNumber operator/(VNumber& a, VNumber& b){ return V_DIV(a,b); }
inline VNumber operator%(VNumber& a, VNumber& b){ return V_MOD(a,b); }

#endif //RTL_INT_H
