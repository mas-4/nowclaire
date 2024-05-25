//
// Created by Michael Sendker on 5/25/24.
//
#include <string.h>

#include "parse_args_test.h"
#include "test.h"
#include "config.h"


int test_all_args()
{
    // nowclaire --output output --host localhost input
    char *argv[] = {"nowclaire", "--output", "output", "--host", "localhost", "input"};
    int argc = 6;
    parse_args(argc, argv);
    CHECK_ERROR(strcmp(config.outdir, "output"), "test_all_args: Output is not set correctly %s", config.outdir)
    CHECK_ERROR(strcmp(config.host, "localhost"), "test_all_args: Host is not set correctly %s", config.host)
    CHECK_ERROR(strcmp(config.indir, "input"), "test_all_args: Input is not set correctly %s", config.indir)
    CHECK_ERROR(strcmp(config.port, "5000"), "test_all_args: Port is not set correctly %s", config.port)
    CHECK_ERROR(config.free == 0, "Because we included a novel host this got parsed, so free should be 1 %d",
                config.free)
    return 0;
}

int test_no_args()
{
    // nowclaire
    char *argv[] = {"nowclaire"};
    int argc = 1;
    int ret = parse_args(argc, argv);
    CHECK_ERROR(ret == 0, "test_no_args: Return value is not 1 %d", ret)
    return 0;
}

int test_colon_port()
{
    // nowclaire --host localhost:8080 input
    char *argv[] = {"nowclaire", "--host", "localhost:8080", "input"};
    int argc = 4;
    parse_args(argc, argv);
    CHECK_ERROR(strcmp(config.host, "localhost"), "test_colon_port: Host is not set correctly %s", config.host)
    CHECK_ERROR(strcmp(config.port, "8080"), "test_colon_port: Port is not set correctly %s", config.port)
    CHECK_ERROR(strcmp(config.indir, "input"), "test_colon_port: Input is not set correctly %s", config.indir)
    CHECK_ERROR(config.outdir == NULL, "test_colon_port: Output should be null if not specified with host %s",
                config.outdir)
    CHECK_ERROR(config.free == 0,
                "test_colon_port: Because we included a novel host this got parsed, so free should be 1 %d",
                config.free)
    return 0;
}

int test_no_host()
{
    // nowclaire --host input
    char *argv[] = {"nowclaire", "--host", "input"};
    int argc = 3;
    parse_args(argc, argv);
    CHECK_ERROR(strcmp(config.host, "127.0.0.1"), "test_no_host: Host is not set correctly %s", config.host)
    CHECK_ERROR(strcmp(config.port, "5000"), "test_no_host: Port is not set correctly %s", config.port)
    CHECK_ERROR(strcmp(config.indir, "input"), "test_no_host: Input is not set correctly %s", config.indir)
    return 0;
}

int test_parse_args()
{
    int failed = 0;
    // array of tests
    int (*tests[])() = {
        test_all_args,
        test_no_args,
        test_colon_port,
        test_no_host,
    };
    for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        failed += tests[i]();
        free_config();
    }

    return failed;
}