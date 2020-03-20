cmake_minimum_required(VERSION 3.5)

project(cryptography_1 LANGUAGES C)

add_executable(cryptography_1 main.c)

target_link_libraries(cryptography_1 mpfr)
target_link_libraries(cryptography_1 gmp)
