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

    mpz_t b, r;
    mpz_init(b);
    mpz_init(r);

    size_t const M = 10000;
    size_t counter = 0;
    for (size_t i = 0; i < M; i++) {
        mpz_urandomm(b, randstate, N);
        mpz_add_ui(b, b, 1);

        mpz_mod(r, N, b);
        mpz_div_ui(b, b, 2);
        if (mpz_cmp(r, b) < 0) {
            counter += 1;
        }
    }

    mpz_clear(b);
    mpz_clear(r);

    printf("Относительная частота: %lf\n", (double) counter / M);

    mpfr_t estimation;
    mpfr_init(estimation);
    mpfr_set_z(estimation, N, MPFR_RNDN);
    mpfr_sqrt(estimation, estimation, MPFR_RNDN);
    mpfr_ui_div(estimation, 1, estimation, MPFR_RNDN);
    mpfr_add_d(estimation, estimation, 2.0 - 2.0 * M_LN2, MPFR_RNDN);
    mpfr_printf("Теоретическая оценка: %Rg\n", estimation);

    mpz_clear(N);
    mpfr_clear(estimation);

    return EXIT_SUCCESS;
}
