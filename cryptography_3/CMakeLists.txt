cmake_minimum_required(VERSION 3.5)

project(cryptography_3 LANGUAGES C)

add_executable(cryptography_3 main.c)

target_link_libraries(cryptography_3 mpfr)
target_link_libraries(cryptography_3 gmp)
