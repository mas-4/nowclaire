//
// Created by Michael Sendker on 5/24/24.
//

#ifndef NOWCLAIRE_CONFIG_H
#define NOWCLAIRE_CONFIG_H

typedef struct {
    char *indir;
    char *outdir;
    char *host;
    char *port;
    int free;
} Config;

int parse_args(int argc, char **argv);

int free_config();

extern Config config;

#endif //NOWCLAIRE_CONFIG_H
