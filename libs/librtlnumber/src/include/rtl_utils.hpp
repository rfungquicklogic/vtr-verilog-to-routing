/* Authors: Aaron Graham (aaron.graham@unb.ca, aarongraham9@gmail.com),
 *           Jean-Philippe Legault (jlegault@unb.ca, jeanphilippe.legault@gmail.com) and
 *            Dr. Kenneth B. Kent (ken@unb.ca)
 *            for the Reconfigurable Computing Research Lab at the
 *             Univerity of New Brunswick in Fredericton, New Brunswick, Canada
 */

#ifndef RTL_UTILS_H
#define RTL_UTILS_H

#include <string>
#include <iostream>

#include <string.h>

#ifndef DEBUG 
#define DEBUG 0 // set debug mode [0 == off; 1 == on]
#endif

#if DEBUG
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define DEBUG_MSG(dbgMsg) {\
    std::cout << __FILENAME__ << ":" << __LINE__ << " DEBUG: " << __func__ << "()" << ": " << dbgMsg;\
    }
#define DEBUG_NEWLINE() {\
    std::cout << std::endl;\
    }
#else
#define DEBUG_MSG(...)
#define DEBUG_NEWLINE()
#endif


std::string string_of_radix_to_bitstring(std::string orig_string, short radix);

inline void _assert_Werr(bool cond, const char *FUNCT, int LINE, std::string error_string)
{
    if (!cond) { 
        std::cout << "ERROR:" << FUNCT << "::" << std::to_string(LINE) << "\t" << error_string << std::endl;
        std::abort();
    }
}
#define assert_Werr(cond, error_string) _assert_Werr((cond),  __func__, __LINE__, std::string(error_string))

#endif
