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

const VNumber V_ADD(const VNumber& a);
const VNumber V_MINUS(const VNumber& a);

const VNumber V_BITWISE_NOT(const VNumber& a);
const VNumber V_BITWISE_AND(const VNumber& a);
const VNumber V_BITWISE_OR(const VNumber& a);
const VNumber V_BITWISE_XOR(const VNumber& a);
const VNumber V_BITWISE_NAND(const VNumber& a);
const VNumber V_BITWISE_NOR(const VNumber& a);
const VNumber V_BITWISE_XNOR(const VNumber& a);
const VNumber V_LOGICAL_NOT(const VNumber& a);

/**
 * Binary Operator
 */
const VNumber V_BITWISE_AND(const VNumber& a,const VNumber& b);
const VNumber V_BITWISE_OR(const VNumber& a,const VNumber& b);
const VNumber V_BITWISE_XOR(const VNumber& a,const VNumber& b);
const VNumber V_BITWISE_NAND(const VNumber& a,const VNumber& b);
const VNumber V_BITWISE_NOR(const VNumber& a,const VNumber& b);
const VNumber V_BITWISE_XNOR(const VNumber& a,const VNumber& b);

const VNumber V_SIGNED_SHIFT_LEFT(const VNumber& a, const VNumber& b);
const VNumber V_SIGNED_SHIFT_RIGHT(const VNumber& a, const VNumber& b);
const VNumber V_SHIFT_LEFT(const VNumber& a, const VNumber& b);
const VNumber V_SHIFT_RIGHT(const VNumber& a, const VNumber& b);

const VNumber V_LOGICAL_AND(const VNumber& a,const VNumber& b);
const VNumber V_LOGICAL_OR(const VNumber& a,const VNumber& b);

const VNumber V_LT(const VNumber& a,const VNumber& b);
const VNumber V_GT(const VNumber& a,const VNumber& b);
const VNumber V_LE(const VNumber& a,const VNumber& b);
const VNumber V_GE(const VNumber& a,const VNumber& b);
const VNumber V_EQUAL(const VNumber& a,const VNumber& b);
const VNumber V_NOT_EQUAL(const VNumber& a,const VNumber& b);
const VNumber V_CASE_EQUAL(const VNumber& a,const VNumber& b);
const VNumber V_CASE_NOT_EQUAL(const VNumber& a,const VNumber& b);

const VNumber V_ADD(const VNumber& a,const VNumber& b);
const VNumber V_MINUS(const VNumber& a,const VNumber& b);
const VNumber V_MULTIPLY(const VNumber& a,const VNumber& b);
const VNumber V_POWER(const VNumber& a,const VNumber& b);
const VNumber V_DIV(const VNumber& a,const VNumber& b);
const VNumber V_MOD(const VNumber& a,const VNumber& b);

/**
 * Ternary Operator
 */
const VNumber V_TERNARY(const VNumber& a, const VNumber& b, const VNumber& c);

inline const VNumber operator!(const VNumber& a){ return V_LOGICAL_NOT(a); }
inline const VNumber operator~(const VNumber& a){ return V_BITWISE_NOT(a); }

inline const VNumber operator-(const VNumber& a){ return V_MINUS(a); }
inline const VNumber operator+(const VNumber& a){ return V_ADD(a); }

inline const VNumber operator&(const VNumber& a, const VNumber& b){ return V_BITWISE_AND(a,b); }
inline const VNumber operator|(const VNumber& a, const VNumber& b){ return V_BITWISE_OR(a,b); }
inline const VNumber operator^(const VNumber& a, const VNumber& b){ return V_BITWISE_XOR(a,b); }

inline const VNumber operator<<(const VNumber& a, const VNumber& b){ return V_SHIFT_LEFT(a,b); }
inline const VNumber operator>>(const VNumber& a, const VNumber& b){ return V_SHIFT_RIGHT(a,b); }

inline const VNumber operator&&(const VNumber& a, const VNumber& b){ return V_LOGICAL_AND(a,b); }
inline const VNumber operator||(const VNumber& a, const VNumber& b){ return V_LOGICAL_OR(a,b); }
inline const VNumber operator<(const VNumber& a, const VNumber& b){ return V_LT(a,b); }
inline const VNumber operator>(const VNumber& a, const VNumber& b){ return V_GT(a,b); }
inline const VNumber operator<=(const VNumber& a, const VNumber& b){ return V_LE(a,b); }
inline const VNumber operator>=(const VNumber& a, const VNumber& b){ return V_GE(a,b); }
inline const VNumber operator==(const VNumber& a, const VNumber& b){ return V_EQUAL(a,b); }
inline const VNumber operator!=(const VNumber& a, const VNumber& b){ return V_NOT_EQUAL(a,b); }

inline const VNumber operator+(const VNumber& a, const VNumber& b){ return V_ADD(a,b); }
inline const VNumber operator-(const VNumber& a, const VNumber& b){ return V_MINUS(a,b); }
inline const VNumber operator*(const VNumber& a, const VNumber& b){ return V_MULTIPLY(a,b); }
inline const VNumber operator/(const VNumber& a, const VNumber& b){ return V_DIV(a,b); }
inline const VNumber operator%(const VNumber& a, const VNumber& b){ return V_MOD(a,b); }

#endif //RTL_INT_H
