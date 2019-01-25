#Authors: Aaron Graham (aaron.graham@unb.ca, aarongraham9@gmail.com),
#         Jean-Philippe Legault (jlegault@unb.ca, jeanphilippe.legault@gmail.com) and
#          Dr. Kenneth B. Kent (ken@unb.ca)
#          for the Reconfigurable Computing Research Lab at the
#           Univerity of New Brunswick in Fredericton, New Brunswick, Canada

SRC=

.PHONY: all

C = clang++ \
-std=c++14 \
-lpthread \
-ggdb \
-O0 \
-Werror \
-Wpedantic \
-Wall \
-ferror-limit=1000


cleanup_flags=\
-fno-omit-frame-pointer \
-ferror-limit=1000 \
-Werror \
-Wpedantic \
-Wclobbered \
-Wcast-function-type \
-Wempty-body \
-Wignored-qualifiers \
-Wimplicit-fallthrough=3 \
-Wmissing-field-initializers \
-Woverride-init \
-Wredundant-move \
-Wtype-limits \
-Wuninitialized \
-Wshift-negative-value \
-Waddress \
-Wbool-compare \
-Wbool-operation \
-Wc++11-compat-Wc++14-compat \
-Wcatch-value \
-Wchar-subscripts \
-Wcomment \
-Wformat \
-Wint-in-bool-context \
-Winit-self \
-Wlogical-not-parentheses \
-Wmaybe-uninitialized \
-Wmemset-elt-size \
-Wmemset-transposed-args \
-Wmisleading-indentation \
-Wmissing-attributes \
-Wmultistatement-macros \
-Wnarrowing \
-Wnonnull \
-Wnonnull-compare \
-Wopenmp-simd \
-Wparentheses \
-Wpessimizing-move \
-Wpointer-sign \
-Wreorder \
-Wrestrict \
-Wreturn-type \
-Wsequence-point \
-Wsign-compare \
-Wsizeof-pointer-div \
-Wsizeof-pointer-memaccess \
-Wstrict-aliasing \
-Wstrict-overflow=1 \
-Wswitch \
-Wtautological-compare \
-Wtrigraphs \
-Wuninitialized \
-Wunknown-pragmas \
-Wunused-label \
-Wunused-value \
-Wunused-variable \
-Wvolatile-register-var \
-Wno-unknown-warning-option

all: clean build debug

#Build everything
build: 
	$(C) -Isrc/include src/*.cpp main.cpp -o rtl_number

clean:
	rm -Rf ./rtl_number

debug:
	gdb --args ./rtl_number "+" "4'b1010"

test:
	./verify_librtlnumber.sh

.phony: all
