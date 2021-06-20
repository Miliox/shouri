cmake_minimum_required (VERSION 3.20)

SET(INSTALL_GTEST OFF CACHE BOOL "Disable Gtest Installer")

add_subdirectory(argparse)
add_subdirectory(fmt)
add_subdirectory(googletest)
add_subdirectory(benchmark)

add_subdirectory(mos6507)
add_subdirectory(app)