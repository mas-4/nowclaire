//
// Created by malan on 6/16/2024.
//

#ifndef NOWCLAIRE_LIST_H
#define NOWCLAIRE_LIST_H

typedef struct Node {
    void *data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct LList {
    Node *head;
} LList;

#endif //NOWCLAIRE_LIST_H
