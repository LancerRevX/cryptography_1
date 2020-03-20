cmake_minimum_required(VERSION 3.5)

project(cryptography_4 LANGUAGES C)

add_executable(cryptography_4 main.c)

target_link_libraries(cryptography_4 mpfr)
target_link_libraries(cryptography_4 gmp)
