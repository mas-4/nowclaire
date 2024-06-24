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
            char subdir[MAX_PATH];
            snprintf(subdir, sizeof(subdir), "%s\\%s", indir, find_file_data.cFileName);
            fl_populate(subdir, fl);
            continue;
        }
        if (fl->count == fl->cap) {
            fl->cap *= 2;
            char **new_files = (char **)realloc(fl->files, fl->cap * sizeof(char *));
            if (new_files == NULL) {
                fprintf(stderr, "Out of memory\n");
                fl_free(fl);
                exit(71);
            }
            fl->files = new_files;
        }
        char fullpath[MAX_PATH];
        snprintf(fullpath, sizeof(fullpath), "%s\\%s", indir, find_file_data.cFileName);
        fl->files[fl->count] = strdup(fullpath);
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
    free(fl->files);
}

const char *read_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file '%s'\n", path);
        return nullptr;
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    rewind(f);
    char *source = (char *)calloc(1, fsize + 1);
    fread(source, fsize, 1, f);
    fclose(f);
    source[fsize] = '\0';
    return source;
}

void free_file(const char *file) {
    free((void *)file);
}

static void ensure_path(const char *path) {
    char *p = strdup(path);
    for (char *c = p; *c; c++) {
        if (*c == '\\') {
            *c = 0;
            CreateDirectory(p, NULL);
            *c = '\\';
        }
    }
    free(p);
}

void write_file(const char *outdir, const char *path, const char *content) {
    char outpath[MAX_PATH];
    snprintf(outpath, sizeof(outpath), "%s\\%s", outdir, path);
    ensure_path(outpath); // Ensure the path exists (create if necessary
    FILE *f = fopen(outpath, "w");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file '%s' for writing\n", outpath);
        return;
    }
    fwrite(content, strlen(content), 1, f);
    fclose(f);
}
