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

    size_t const N = 2019;
    mpz_t a, A, mod;
    mpz_init(a);
    mpz_init(A);
    mpz_init(mod);

    mpz_set_ui(a, 2019);
    mpz_set(A, a);
    mpz_ui_pow_ui(mod, 10, N);

    for (size_t n = 2; n <= N; n++) {
        mpz_powm(A, a, A, mod);
    }
    gmp_printf("%Zi\n", A);

    mpz_clear(a);
    mpz_clear(A);
    mpz_clear(mod);

    return EXIT_SUCCESS;
}
