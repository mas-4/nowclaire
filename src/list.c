//
// Created by malan on 6/16/2024.
//

#include <stdlib.h>
#include "list.h"

LList *ll_init() {
    LList *list = malloc(sizeof(LList));
    list->head = NULL;
    return list;
}

void ll_free(LList *list) {
    Node *node = list->head;
    while (node != NULL) {
        Node *next = node->next;
        free(node);
        node = next;
    }
    free(list);
}

void ll_insert(LList *list, Node *prev, void *data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = prev->next;
    node->prev = prev;
    prev->next = node;
    if (node->next != NULL) {
        node->next->prev = node;
    }
}

void ll_push(LList *list, void *data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = list->head;
    node->prev = NULL;
    if (list->head != NULL) {
        list->head->prev = node;
    }
    list->head = node;
}

Node* ll_pop(LList *list) {
    Node *node = list->head;
    if (node != NULL) {
        list->head = node->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        }
    }
    return node;
}

void ll_remove(LList *list, Node *node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    free(node);
}