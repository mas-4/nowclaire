//
// Created by malan on 6/16/2024.
//

#include "file_handler.h"
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdlib.h>

int fl_init(FileList *flist, size_t size) {
    flist->files = malloc(sizeof(File) * size);
    if (flist->files == NULL) {
        return -1;
    }
    flist->size = size;
    flist->count = 0;
    return 0;
}

int fl_free(FileList *flist) {
    if (flist->files == NULL) {
        return -1;
    }
    for (size_t i = 0; i < flist->count; i++) {
        if (flist->files[i].name != NULL) {
            free(flist->files[i].name);
        }
        if (flist->files[i].extension != NULL) {
            free(flist->files[i].extension);
        }
        if (flist->files[i].path != NULL) {
            free(flist->files[i].path);
        }
    }
    free(flist->files);
    return 0;
}

int fl_expand(FileList *flist) {
    flist->size *= 2;
    File *tmp = realloc(flist->files, sizeof(File) * flist->size);
    if (tmp == NULL) {
        return -1;
    }
    flist->files = tmp;
    return 0;
}

int fl_insert(FileList *flist, File *file) {
    if (flist->count == flist->size) {
        if (fl_expand(flist) == -1) {
            return -1;
        }
    }
    flist->files[flist->count] = *file;
    flist->count++;
    return 0;
}

#ifdef _WIN32
/* Windows-specific headers and definitions */
#include <windows.h>

// -1 means failure
int fl_list(const char *path, FileList *flist) {
    size_t size = 20;
    if (flist != NULL) {
        return -1;
    }
    if (fl_init(flist, size) == -1) {
        return -1;
    }

    WIN32_FIND_DATA find_file_data;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char DirSpec[MAX_PATH];
    DWORD dwError;

    strncpy(DirSpec, path, strlen(path) + 1);
    strncat(DirSpec, "\\*", 3);

    hFind = FindFirstFile(DirSpec, &find_file_data);
    do {
        if (hFind == INVALID_HANDLE_VALUE) {
            return -1; // user should free file_stats
        }
        if (strcmp(find_file_data.cFileName, ".") == 0 || strcmp(find_file_data.cFileName, "..") == 0) {
            continue;
        }
        if (flist->count == flist->size) {
            if (fl_expand(flist) == -1) {
                fl_free(flist);
                return -1;
            }
        }

        File file;
        file.name = malloc(strlen(find_file_data.cFileName) + 1);
        strcpy(file.name, find_file_data.cFileName);
        file.extension = malloc(strlen(find_file_data.cFileName) + 1);
        file.path = malloc(strlen(path) + strlen(find_file_data.cFileName) + 2);
        strcpy(file.path, path);
        strcat(file.path, "\\");
        strcat(file.path, find_file_data.cFileName);
        file.is_dir = (find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        fl_insert(flist, &file);

    } while (FindNextFile(hFind, &find_file_data) != 0);

    return 0;
}

#elif __unix__ || __APPLE__
/* Unix/Linux/MacOS-specific headers and definitions */

#endif

#endif /* FILESYSTEM_H */