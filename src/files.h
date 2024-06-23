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

#endif //NOWCLAIRE_FILES_H
