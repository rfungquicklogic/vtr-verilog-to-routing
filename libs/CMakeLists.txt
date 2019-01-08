#VTR developed libraries
add_subdirectory(libarchfpga)
add_subdirectory(libvtrutil)
add_subdirectory(liblog)
add_subdirectory(libpugiutil)
add_subdirectory(libeasygl)

if(WITH_LIB_RTL)
	add_subdirectory(librtlnumber)
endif()

#Externally developed libraries
add_subdirectory(EXTERNAL)
