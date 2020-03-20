#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#ifdef WIN32
    #include <windows.h>
#endif

#include <gmp.h>
#include <mpfr.h>

int main() {
    #ifdef WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    gmp_randstate_t randstate;
    gmp_randinit_default(randstate);
    gmp_randseed_ui(randstate, time(0));

    mpz_t N;
    mpz_init(N);
    mpz_ui_pow_ui(N, 10, 10);

    mpz_t m, x, x_square;
    mpz_init(m);
    mpz_init(x);
    mpz_init(x_square);

    size_t const M = 1000;
    size_t not_square_free_count = 0;
    for (size_t i = 0; i < M; i++) {
        mpz_urandomm(m, randstate, N);
        mpz_add_ui(m, m, 1);

        mpz_set_ui(x, 2);
        mpz_pow_ui(x_square, x, 2);
        while (mpz_cmp(x_square, m) <= 0) {
            if (mpz_divisible_p(m, x_square)) {
                not_square_free_count += 1;
                break;
            } else {
                mpz_add_ui(x, x, 1);
                mpz_pow_ui(x_square, x, 2);
            }
        }
    }

    mpz_clear(m);
    mpz_clear(x);
    mpz_clear(x_square);

    printf("Относительная частота: %lf\n", (double) (M - not_square_free_count) / M);

    mpfr_t estimation;
    mpfr_init(estimation);
    mpfr_set_z(estimation, N, MPFR_RNDN);
    mpfr_sqrt(estimation, estimation, MPFR_RNDN);
    mpfr_ui_div(estimation, 1, estimation, MPFR_RNDN);
    mpfr_add_d(estimation, estimation, 6.0 / (M_PI * M_PI), MPFR_RNDN);
    mpfr_printf("Теоретическая оценка: %Rg\n", estimation);

    mpz_clear(N);
    mpfr_clear(estimation);

    return EXIT_SUCCESS;
}
