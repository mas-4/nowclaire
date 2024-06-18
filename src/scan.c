//
// Created by malan on 6/16/2024.
//

#include "scan.h"
#include "file_handler.h"
#include "logger.h"

#include <list.h>
#include <stdlib.h>
#include <stdio.h>

// We need to recursively iterate every file in the directory.
// If it ends with .html we scan it for tokens

LList** scan_files(const char *dir) {
    FileList *flist;
    fl_list(dir, flist);
    for(size_t i = 0; i < flist->count; i++) {
        if (flist->files[i].extension == "html") {
            // read in the file


        }
    }

    return tokens;
}

LList* scan_tokens(const char *path) {
    File *file = fopen(path, "r");
    if (file == NULL) {
        log_debug("Could not open file '%s'\n", path);
        return NULL;
    }
    char line[1024];
    while (fgets(line))

    return tokens;
}