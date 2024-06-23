#include <stdio.h>

#include "build.h"
#include "files.h"

void build(const char *indir, const char *outdir) {
    FileList fl;
    fl_init(&fl);
    fl_populate(indir, &fl);
    for (int i = 0; i < fl.count; i++) {
        printf("Building file '%s'\n", fl.files[i]);
        const char* source = read_file(fl.files[i]);
//        const char* output = compile_file(source);
        write_file(outdir, fl.files[i], source);
    }
    printf("Build complete\n");
    fl_free(&fl);
}
