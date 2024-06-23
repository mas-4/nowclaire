#define LOGGER_H_IMPL

#include <stdio.h>
#include "config.h"
#include "build.h"

void run_hot_reload() {
    printf("Running hot reload: host '%s'\n", config.host);
}

void run_build() {
    printf("Running build: Output directory '%s'\n", config.outdir);
    build(config.indir, config.outdir);
}

int main(int argc, char **argv) {
    parse_args(argc, argv);

    if (config.host != NULL) {
        if (config.outdir != NULL) // No need to build if we're just hosting, warn
            printf("Warning: Output directory '%s' will be ignored when host is specified\n", config.outdir);
        run_hot_reload();
    } else if (config.outdir != NULL) {
        run_build();
    } else {
        printf("No host or output directory specified\n");
    }

    free_config();
    return 0;
}