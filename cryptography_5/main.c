#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#ifdef WIN32
    #include <windows.h>
#endif

#include <gmp.h>
#include <mpfr.h>

#include "mpz_aprcl.h"
#include "prime_factorize.h"

size_t is_power(mpz_t const, mpz_t const);
//size_t is_odd_prime_power(mpz_t const);
size_t is_power_of_2(mpz_t const);

//void euler_function_prime_power(mpz_t, mpz_t const, size_t);
//void carmichael_function(mpz_t, mpz_t const);

int main() {
    #ifdef WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    mpz_t a, b, c, N;
    mpz_inits(a, b, c, N, 0);

    gmp_randstate_t randstate;
    gmp_randinit_default(randstate);
    gmp_randseed_ui(randstate, time(0));

    mpz_ui_pow_ui(N, 10, 3);

    for (size_t j = 0; j < 1; j++) {
        mpz_urandomm(a, randstate, N);
        gmp_printf("%Zi = 2 ^ %llu\n", a, is_power_of_2(a));
    }

    mpz_clears(a, b, c, N, 0);

    return EXIT_SUCCESS;
}

//void carmichael_function(mpz_t rop, mpz_t const op) {
//    size_t n = 0;
//    if (mpz_cmp_ui(op, 2) == 0) {
//        euler_function_prime_power(rop, op, 1);
//    } else if (mpz_cmp_ui(op, 4) == 0) {
//        euler_function_prime_power(rop, op, 2);
//    } else if ((n = is_odd_prime_power(op))) {
//        euler_function_prime_power(rop, op, n);
//    } else if ((n = is_power_of_2(op))) {
//        euler_function_prime_power(rop, op, n);
//        mpz_div_ui(rop, rop, 2);
//    } else {
//        mpz_t a;
//        mpz_init(a);
//        mpz_set_ui(rop, 1);
//        List factors = prime_factorize(op);
//        for (size_t i = 0; i < factors.length; i++) {
//            mpz_set(a, factors.data[i].factor);
//            mpz_pow_ui(a, a, factors.data[i].power);
//            carmichael_function(a, a);
//            mpz_lcm(rop, rop, a);
//        }
//        list_delete(factors);
//        mpz_clear(a);
//    }
//}

//void euler_function_prime_power(mpz_t rop, mpz_t const op, size_t n) {
//    mpz_root(rop, op, n);
//    mpz_pow_ui(rop, rop, n - 1);
//    mpz_sub(rop, op, rop);
//}

//size_t is_odd_prime_power(mpz_t const op) {

//}

size_t is_power(mpz_t const op1, mpz_t const op2) {
    mpfr_t a, b;
    mpfr_init(a);
    mpfr_init(b);
    mpfr_set_z(a, op1, MPFR_RNDN);
    mpfr_set_z(b, op2, MPFR_RNDN);
    mpfr_log(a, a, MPFR_RNDN);
    mpfr_log(b, b, MPFR_RNDN);
    mpfr_div(a, a, b, MPFR_RNDN);
    size_t power = mpfr_get_ui(a, MPFR_RNDN);
    mpfr_clear(a);
    mpfr_clear(b);
    mpz_t n;
    mpz_init(n);
    mpz_pow_ui(n, op2, power);
    if (mpz_cmp(n, op1) != 0) {
        power = 0;
    }
    mpz_clear(n);
    return power;
}

size_t is_power_of_2(mpz_t const op) {
    mpz_t two;
    mpz_init_set_ui(two, 2);
    size_t power = is_power(op, two);
    mpz_clear(two);
    return power;
}
