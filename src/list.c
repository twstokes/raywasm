/* List routines for generic object */

#include "list.h"

list_t *l_init() {
   list_t *new;
   new = malloc(sizeof(list_t));
   new->position = NULL;
   new->head = NULL;
   new->tail = NULL;
   return(new);
}

void l_add(list_t *list, void *objPtr) {
   node_t *new;
   new = malloc(sizeof(node_t));
   new->objPtr = objPtr;
   new->next = NULL;
   
   /* Empty list? */
   if (list->tail == NULL) {
      /* Yes -- new node is both head and tail of list */
      list->head = new;
      list->tail = new;
   }
   else {
      /* No -- add new node to tail */
      list->tail->next = new;
      list->tail = new;
   }
}

void l_setstart(list_t *list) {
     list->position = list->head;
}

void *l_getnext(list_t *list) {
   node_t *nodePtr = list->position; 
   if (nodePtr == NULL) {
      return(NULL);
   }

   /* Advance to next node in list */
   list->position = list->position->next;
   return(nodePtr->objPtr);
}
