cmake_minimum_required(VERSION 3.5)

project(cryptography_6 LANGUAGES C)

add_executable(cryptography_6 main.c)

target_link_libraries(cryptography_6 gmp)
