#ifndef NOWCLAIRE_FILES_H
#define NOWCLAIRE_FILES_H

typedef struct {
    char **files;
    int count;
    int cap;
} FileList;

void fl_init(FileList* fl);
void fl_populate(const char* indir, FileList* fl);
void fl_free(FileList* fl);
const char* read_file(const char* path);
void free_file(const char* file);
void write_file(const char* outdir, const char* path, const char* content);

#endif //NOWCLAIRE_FILES_H
