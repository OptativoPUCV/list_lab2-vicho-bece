#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * lista = (List *)malloc(sizeof(List) * 1);
  lista->head = NULL;
  lista->tail = NULL;  
  return lista;
}

void * firstList(List * list) {
  if(list->head == NULL) return NULL;
  list->current = list->head;
  return (void *)list->head->data;
}

void * nextList(List * list) {
  if(list->current == NULL) return NULL;
  list->current = list->current->next;
  if(list->current == NULL) return NULL;
  return (void *)list->current->data;
}

void * lastList(List * list) {
  if(list->head == NULL) return NULL;
  list->current = list->tail;
    return (void *)list->tail->data;
}

void * prevList(List * list) {
  if(list->current == NULL) return NULL;
  list->current = list->current->prev;
  if(list->current == NULL) return NULL;
    return (void *)list->current->data;
}

void pushFront(List * list, const void * data) {
  Node * nodo = createNode(data);
  if(list->head == NULL){
    nodo->next = NULL;
    nodo->prev = NULL;
    list->head = nodo;
    list->tail = nodo;
  }
  else{
    nodo->next = list->head;
    nodo->prev = NULL;
    list->head = nodo;
    list->head->prev = NULL;
  }

}

void pushBack(List * list, const void * data) {
    Node * nodo = createNode(data);
    if(list->head == NULL){
      nodo->next = NULL;
      nodo->prev =NULL;
      list->head = nodo;
      list->tail = nodo;
    }
    else{
      nodo->next = NULL;
      nodo->prev = list->tail;
      list->tail = nodo;
      list->current->next = list->tail;
    }
}

void pushCurrent(List * list, const void * data) {
  Node * nuevoNODO = createNode(data);
  if(list->current == list->head){
    nuevoNODO->prev = list->head;
    nuevoNODO->next = list->head->next;
    list->head->next = nuevoNODO;
  }
  if(list->current == list->tail)
    pushBack(list, data);
}

void * popFront(List * list) {
  const void * aux = list->head->data;
  list->head = list->head->next;
    free(list->current);
    list->current = list->head;
    list->head->prev = NULL;
    return (void *)aux;
}

void * popBack(List * list) {
  const void * aux = list->tail->data;
  list->tail = list->tail->prev;
  free(list->current);
  list->current = list->tail;
  list->tail->next = NULL;
  return (void *)aux;
}

void * popCurrent(List * list) {
  if(list->current == list->head)
    return popFront(list);

  if(list->current == list->tail)
    return popBack(list);

  const void * aux;
  if(list->current->prev == list->head){
    aux = list->current->data;
    list->current->next = list->head;
    
    free(list->current);
    list->current = list->head->next;
    list->head->next = list->current;
  }
  
    return (void *)aux;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}