//
// Created by Michael Sendker on 5/25/24.
//

#ifndef NOWCLAIRE_TEST_H
#define NOWCLAIRE_TEST_H
#include <stdio.h>

#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

#define CHECK_ERROR(x, ...) \
    if (x != 0) { \
        printf("\t%s[FAIL] ", RED); \
        printf(__VA_ARGS__); \
        printf(" %s\n", RESET); \
        return 1; \
    }

#endif //NOWCLAIRE_TEST_H
