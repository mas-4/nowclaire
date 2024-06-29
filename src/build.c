#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "build.h"
#include "files.h"

void build(const char *indir, const char *outdir) {
    FileList fl;
    fl_init(&fl);
    fl_populate(indir, &fl);
    for (int i = 0; i < fl.count; i++) {
        char* relative_path = malloc(strlen(fl.paths[i]) + 1);
        strip_prefix(fl.paths[i], indir, relative_path);
        printf("Building file '%s'\n", fl.paths[i]);
        const char* source = read_file(fl.paths[i]);

//        const char* output = compile_file(source);

        write_file(outdir, relative_path, source);
        free(relative_path);
        free_file(source);
    }
    printf("Build complete\n");
    fl_free(&fl);
}
