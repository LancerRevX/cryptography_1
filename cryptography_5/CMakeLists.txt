cmake_minimum_required(VERSION 3.5)

project(cryptography_5 LANGUAGES C)

add_executable(cryptography_5 main.c mpz_aprcl.c)

target_link_libraries(cryptography_5 mpfr)
target_link_libraries(cryptography_5 gmp)
