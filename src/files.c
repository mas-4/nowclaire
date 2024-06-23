#include <stdio.h>
#include "files.h"

#ifdef _WIN32
/* Windows-specific headers and definitions */
#include <windows.h>

void fl_init(FileList *fl) {
    fl->count = 0;
    fl->cap = 8;
    fl->files = (char **) malloc(fl->cap * sizeof(char *));
}

void fl_populate(const char *indir, FileList *fl) { // NOLINT recursive
    // Walk the dir and subdirs, return a list of paths
    WIN32_FIND_DATA find_file_data;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char DirSpec[MAX_PATH];
    DWORD dwError;

    strncpy(DirSpec, indir, strlen(indir) + 1);
    strncat(DirSpec, "\\*", 3);

    hFind = FindFirstFile(DirSpec, &find_file_data);

    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "FindFirstFile error. Error is %lu\n", GetLastError());
        exit(70);
    }

    do {
        // if its '.' or '..' skip
        if (strcmp(find_file_data.cFileName, ".") == 0 || strcmp(find_file_data.cFileName, "..") == 0) {
            continue;
        }
        if (find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            fl_populate(find_file_data.cFileName, fl);
            continue;
        }
        if (fl->count == fl->cap) {
            fl->cap *= 2;
            char **new_files = (char **) realloc(fl->files, fl->cap * sizeof(char *));
            if (new_files == NULL) {
                fprintf(stderr, "Out of memory\n");
                fl_free(fl);
                exit(71);
            }
            fl->files = new_files;
        }
        fl->files[fl->count] = (char *) malloc(strlen(find_file_data.cFileName) + 1);
        strncpy(fl->files[fl->count], find_file_data.cFileName, strlen(find_file_data.cFileName) + 1);
        fl->count++;
    } while (FindNextFile(hFind, &find_file_data) != 0);

    dwError = GetLastError();
    FindClose(hFind);
    if (dwError != ERROR_NO_MORE_FILES) {
        fprintf(stderr, "FindNextFile error. Error is %lu\n", dwError);
    }
}

#endif

void fl_free(FileList *fl) {
    for (int i = 0; i < fl->count; i++) {
        free(fl->files[i]);
    }
    free(fl->files);
}

const char *read_file(const char *path) {
    // Read
    return nullptr;
}
