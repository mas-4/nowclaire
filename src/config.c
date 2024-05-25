//
// Created by Michael Sendker on 5/24/24.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"

#define str(x) #x
#define xstr(x) str(x)

#define MAJOR_VERSION 0
#define MINOR_VERSION 1
#define PATCH_VERSION 0
#define VERSION xstr(MAJOR_VERSION) "." xstr(MINOR_VERSION) "." xstr(PATCH_VERSION)

Config config = {0};
char *default_host = "127.0.0.1";
char *default_port = "5000";
char *default_outdir = "build";

void parse_host(char *host);

void print_usage()
{

    printf("Usage: nowclaire [options] <input file>\n");
    printf("Options:\n");
    printf("\
    -o, --output <output directory>                                     default: build (when hot reload specified)\n\
    --host [host[:port]]                  run hot reload with host      default: 127.0.0.1:5000\n\
    -v, --version                         print version\n\
    -h, --help                            print this message\n");
}

int parse_args(int argc, char **argv)
{
    config.free = 0;
    if (argc < 2 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
    {
        print_usage();
        return 1;
    }
    if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)
    {
        printf("nowclaire %s\n", VERSION);
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0)
        {
            if (i + 1 < argc)
            {
                config.outdir = argv[i + 1];
                i++;
            }
            else
            {
                return 1;
            }
        }
        else if (strcmp(argv[i], "--host") == 0)
        {
            if (i + 1 > argc)
            {
                config.host = default_host;
                config.port = default_port;
                continue;
            }
            // if the next argument does not start with either localhost or a valid ip address, use defaults
            if (strncmp(argv[i + 1], "localhost", 9) != 0 && strchr(argv[i + 1], '.') == NULL)
            {
                config.host = default_host;
                config.port = default_port;
                continue;
            }
            parse_host(argv[i + 1]);
            i++;
        }
        else
        {
            config.indir = argv[i];
        }
    }

    // if host is null and output is null, set output to default
    if (config.host == NULL && config.outdir == NULL)
    {
        config.outdir = default_outdir;
    }

    return 0;
}

void parse_host(char *host)
{
    host = strdup(host);
    config.free = 1;
    // if the host contains a colon, split the host and port
    char *colon = strchr(host, ':');
    if (colon != NULL)
    {
        *colon = '\0';
        config.host = host;
        config.port = colon + 1;
    }
    else
    {
        config.host = host;
        config.port = default_port;
    }

}

int free_config()
{
    if (config.free)
    {
        free(config.host);
    }
    config.indir = NULL;
    config.outdir = NULL;
    config.host = NULL;
    config.port = NULL;
    config.free = 0;
    return 0;
}