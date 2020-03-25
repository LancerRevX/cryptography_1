#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#ifdef WIN32
    #include <windows.h>
#endif

#include <gmp.h>

int main() {
    #ifdef WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    mpz_t n, i;
    mpz_init(n);
    mpz_init(i);

    mpz_set_ui(n, 9);

    bool prime = true;
    mpz_set_ui(i, 3);

    unsigned long last_digit = mpz_mod_ui(i, n, 10);
    switch (last_digit) {
        case 0:
        case 2:
        case 4:
        case 5:
        case 6:
        case 8:
            prime = false;
    }

    gmp_printf("%Zi is %sprime\n", n, prime ? "" : "not ");

    mpz_clear(n);
    mpz_clear(i);

    return EXIT_SUCCESS;
}
