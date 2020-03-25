#ifndef PRIME_FACTORIZE_H
#define PRIME_FACTORIZE_H

#include <string.h>
#include <stdlib.h>
#include <gmp.h>
#include "mpz_aprcl.h"

struct Factor {
    mpz_t factor;
    size_t power;
};

typedef struct FactorList List;
struct FactorList {
    struct Factor* data;
    size_t length;
};

List list_new() {
    List list = {
        .data = 0,
        .length = 0
    };
    return list;
}

void list_add(List* list) {
    struct Factor* buffer = malloc(sizeof (struct Factor) * (list->length + 1));
    memcpy(buffer, list->data, sizeof (struct Factor) * list->length);
    mpz_init(buffer[list->length].factor);
    if (list->length > 0) {
        free(list->data);
    }
    list->data = buffer;
    list->length += 1;
}

struct Factor* list_last(List* list) {
    return &list->data[list->length - 1];
}

void list_delete(List list) {
    for (size_t i = 0; i < list.length; i++) {
        mpz_clear(list.data[i].factor);
    }
    if (list.length > 0) {
        free(list.data);
    }
}

List prime_factorize(mpz_t const N) {
    mpz_t n;
    mpz_init_set(n, N);

    List factors = list_new();
    mpz_t a;
    mpz_init_set_ui(a, 2);
    while (mpz_cmp(a, n) <= 0) {
        if (mpz_aprcl(a) == 2 && mpz_divisible_p(n, a)) {
            mpz_div(n, n, a);
            list_add(&factors);
            mpz_set(list_last(&factors)->factor, a);
            list_last(&factors)->power = 1;
            while (mpz_divisible_p(n, a)) {
                mpz_div(n, n, a);
                list_last(&factors)->power += 1;
            }
        }
        mpz_add_ui(a, a, 1);
    }
    mpz_clear(a);
    return factors;
}

#endif // PRIME_FACTORIZE_H
