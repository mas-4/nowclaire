//
// Created by malan on 6/16/2024.
//

#ifndef NOWCLAIRE_FILE_HANDLER_H
#define NOWCLAIRE_FILE_HANDLER_H

#include <sys/stat.h>

typedef struct Listing {
    char *name;
    char *extension;
    char *path;
    bool is_dir;
} File;

typedef struct FileList {
    File *files;
    size_t size;
    size_t count;
} FileList;

int fl_list(const char *path, FileList *flist);

#endif //NOWCLAIRE_FILE_HANDLER_H
