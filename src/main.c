#define LOGGER_H_IMPL

#include <stdio.h>
#include "config.h"

int main(int argc, char **argv) {
    parse_args(argc, argv);

    if (config.outdir != NULL) {
        printf("Output directory '%s'\n", config.outdir);
    }
    if (config.host != NULL) {
        printf("Host '%s'\n", config.host);
    }

    free_config();
    return 0;
}