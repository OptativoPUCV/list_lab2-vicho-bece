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
    if(list->tail == NULL){
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
  if(list->current == list->head)
    pushFront(list,data);

  if(list->current == list->tail)
    pushBack(list,data);
  
  Node * nuevoNODO = createNode(data);
  if(list->current->prev == list->head)
  {
    nuevoNODO->prev = list->head->next;
    nuevoNODO->next = list->current->prev;
    list->current = nuevoNODO;
  }  
  else if(list->current->next == list->tail)
  {
    nuevoNODO->prev = list->current->next;
    nuevoNODO->next = list->tail->prev;
  }
    else{
      nuevoNODO->prev = list->current->next;
      nuevoNODO->next = list->current->next;
    }
  
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  const void * aux = list->current->data; 
  if(list->current == list->head){
    list->head = list->head->next;
    free(list->current);
    list->current = list->head;
    list->head->prev = NULL;
  }

  else if(list->current == list->tail){ 
    list->tail = list->tail->prev;
    free(list->current);
    list->current = list->tail;
    list->tail->next = NULL;
  }
  else{
    list->current->prev = list->current->next;
    list->current->next = list->current->prev;
    const void * search = list->current->next->data;
    free(list->current);
    list->current = list->head;
    while(list->current->data != search)
      list->current = list->current->next;
  }


    return (void *)aux;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}