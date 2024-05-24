#define LOGGER_H_IMPL

#include <stdio.h>
#include <logger.h>

#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

#define CHECK_ERROR(x, msg) if (x != 0) { printf("\t%s[FAIL] %s%s %d\n", RED, msg, RESET, x); return x; }


int test_hello()
{
    CHECK_ERROR(0, "test_hello")
    return 0;
}


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
    set_logging_level(LOG_LEVEL_DEBUG);

    int (*tests[])() = {
        test_hello,
    };
    int num_tests = sizeof(tests) / sizeof(tests[0]);

    int result  = 0;
    for (int i = 0; i < num_tests; i++)
    {
        result += run_test(tests[i], "test_hello");
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
