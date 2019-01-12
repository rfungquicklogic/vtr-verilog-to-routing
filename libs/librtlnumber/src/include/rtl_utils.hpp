/* Authors: Aaron Graham (aaron.graham@unb.ca, aarongraham9@gmail.com),
 *           Jean-Philippe Legault (jlegault@unb.ca, jeanphilippe.legault@gmail.com) and
 *            Dr. Kenneth B. Kent (ken@unb.ca)
 *            for the Reconfigurable Computing Research Lab at the
 *             Univerity of New Brunswick in Fredericton, New Brunswick, Canada
 */

#ifndef RTL_UTILS_H
#define RTL_UTILS_H

#include <string>

std::string string_of_radix_to_bitstring(std::string orig_string, short radix);

#define assert_Werr(cond, error_string) _assert_Werr((cond),  __func__, __LINE__, (error_string))
#define _assert_Werr(cond,  __func__, __LINE__, error_string) __assert_Werr((cond),  __func__, __LINE__, std::string((error_string)))
inline void __assert_Werr(bool cond, const char *FUNCT, int LINE, std::string error_string);

#endif
