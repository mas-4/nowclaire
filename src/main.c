#define LOGGER_H_IMPL

#include "logger.h"
#include "config.h"

int main(int argc, char **argv) {
    set_logging_level(LOG_LEVEL_DEBUG);
    parse_args(argc, argv);

    if (config.outdir != NULL) {
        log_debug("Output directory: ");
        log_debug(config.outdir);
        log_debug("\n");
    }
    if (config.host != NULL) {
        log_debug("Host: ");
        log_debug(config.host);
        log_debug("\n");
    }

    free_config();
    return 0;
}