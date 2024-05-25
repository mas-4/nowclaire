#define LOGGER_H_IMPL

#include <stdio.h>
#include "test.h"
#include "parse_args_test.h"


int run_test(int (*test)(), const char *name)
{
    printf("[TEST] %s...\n", name);
    int result = test();
    if (result == 0)
    {
        printf("\t%s[OKAY]%s\n", GREEN, RESET);
    }
    return result;
}

int main() {

    int (*tests[])() = {
        test_parse_args,
    };
    const char *test_names[] = {
        "test_parse_args",
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);

    int result  = 0;
    for (int i = 0; i < num_tests; i++)
    {
        result += run_test(tests[i], test_names[i]);
    }

    if (result == 0)
    {
        printf("[ALL TESTS PASSED]\n");
    }
    else
    {
        printf("[FAIL] %d tests failed\n", result);
    }

    return result;
}
