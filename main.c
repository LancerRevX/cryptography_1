#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef WIN32
    #include <windows.h>
#endif

#include <gmp.h>
#include <mpfr.h>

int main()
{
    #ifdef WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    gmp_randstate_t randstate;
    gmp_randinit_default(randstate);
    gmp_randseed_ui(randstate, time(0));

    mpz_t N;
    mpz_init(N);
    mpz_ui_pow_ui(N, 10, 100);

    mpz_t a, b;
    mpz_init(a);
    mpz_init(b);

    size_t const M = 10000;
    size_t division_count = 0;
    for (size_t i = 0; i < M; i++) {
        mpz_urandomm(a, randstate, N);
        mpz_add_ui(a, a, 1);
        mpz_urandomm(b, randstate, N);
        mpz_add_ui(b, b, 1);

        if (mpz_cmp(a, b) == -1) {
            mpz_swap(a, b);
        }

        while (mpz_sgn(b) != 0) {
            mpz_mod(a, a, b);
            mpz_swap(a, b);
            division_count += 1;
        }
    }

    mpz_clear(a);
    mpz_clear(b);

    printf("Относительная частота: %lf\n", (double) division_count / M);

    mpfr_t estimation;
    mpfr_init(estimation);
    mpfr_set_z(estimation, N, MPFR_RNDN);
    mpfr_log(estimation, estimation, MPFR_RNDN);
    mpfr_mul_d(estimation, estimation, M_LN2, MPFR_RNDN);
    mpfr_mul_ui(estimation, estimation, 12, MPFR_RNDN);
    mpfr_div_d(estimation, estimation, M_PI * M_PI, MPFR_RNDN);
    mpfr_printf("Теоретическая оценка: %Rg\n", estimation);

    mpz_clear(N);
    mpfr_clear(estimation);

    return EXIT_SUCCESS;
}
