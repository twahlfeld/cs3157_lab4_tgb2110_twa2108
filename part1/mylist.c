/**********************************************************************
* FILENAME :        mylist.c          ASSIGNMENT :      lab3      
*
* DESCRIPTION :
*        Functions for a linked list.
*
* PUBLIC FUNCTIONS :
*        struct Node *addFront(struct List *list, void *data)  ->
*              Adds a new node in front of *list with *data
*        void traverseList(struct List *list, void(*f)(void *))   ->
*              Traverse through all nodes in *list perform function (*f)
*        struct Node *findNode(struct List *list, const void *dataSought,
*           int(*compar)(const void *, const void *)) ->
*              Find node in *list with *dataSought evaluated by *compar
*        void flipSignDouble(void *data)  -> 
*              flips sign of the double value of data
*        void compareDouble(const void *data1, const void *data2)
*              compares if the double values of data1 and data2 are the same
*        void *popFront(struct List *list)   ->
*              returns and removes the first node from *list
*        void removeAllNodes(struct List *list) ->
*              Removes every node ins *list
*        struct Node *addAfter(struct List *list,
*           struct Node *prevNode, void *data) ->
*              Add a node after *prevNode and returns the new node
*        void reverseList(struct List *list) ->
*              reverses the order on all nodes in *list
*                                                          
*        Copyright 2014 All rights reserved.
* 
* AUTHOR :    Theodore Ahlfeld        START DATE :    20140925
*
*/

#include <stdlib.h>
#include "mylist.h"

/*
 * Adds a node in front of *list containing *data
 * struct List *list -> The list of nodes to add the node in
 * void *data        -> The data for the new node to have
 * return   -> NULL node could not be made otherwise return the new node
 */
struct Node *addFront(struct List *list, void *data)
{
   struct Node *newNode = (struct Node *)
               malloc(sizeof(struct Node));
   /* Only performs operation  */
   if(!newNode)
      return NULL;
   newNode->data = data;
   newNode->next = list->head;
   list->head = newNode;
   return newNode;
}

/*
 * Traverses *list performing function (*f) on each node's data
 * struct List *list -> The list of nodes
 * void (*f)(void *) -> The function to perform on each node 
 */
void traverseList(struct List *list, void (*f)(void *))
{
   struct Node *tmpNode = list->head;
   while(tmpNode) {
      f(tmpNode->data);
      tmpNode = tmpNode->next;
   }
}

/*
 * Finds the node in *list with *dataSought using the *compar function
 * struct List *list       -> The list of nodes to search through
 * const void *dataSought  -> The data to find in the node
 * int (*compar)(const void *, const void)   -> 
 *                The function to compare *dataSought and each node's data
 * return   -> returns NULL if node is not found otherwise returns the found node
 */
struct Node *findNode(struct List *list, const void *dataSought,
   int (*compar)(const void *, const void *))
{
   struct Node *tmpNode = list->head;
   while(tmpNode) {
      if(compar(dataSought, tmpNode->data) == 0)
         return tmpNode;
      tmpNode = tmpNode->next;
   }
   return NULL;
}

/*
 * Flips the signs of the double value of *data
 * void *data  -> The data to flip the sign of
 */
void flipSignDouble(void *data)
{
   *(double *)data = *(double *)(data)*-1;
}

/*
 *  Compares to data together
 *  *data1  -> 1st data to compare
 *  *data2  -> 2nd data to compare
 *  return  -> returns 0 if data is same otherwise return 1
 */
int compareDouble(const void *data1, const void *data2)
{
   if(*(double *)data1 == *(double *)data2)
      return 0;
   return 1;
}

/*
 * Removes and returns the data of the 1st node in *list
 * struct List *list -> List of nodes
 * return            -> Returns NULL is list is empty otherwise returns data
 */
void *popFront(struct List *list)
{
   if(!list->head)
      return NULL;

   struct Node *tmpNode = list->head;
   list->head = tmpNode->next;
   void *data = tmpNode->data;
   free(tmpNode);
   return data;
}

/*
 * Removes all nodes in *list
 * struct List *list -> List of nodes
 */
void removeAllNodes(struct List *list)
{
   struct Node *node = list->head;
   while(node) {
      struct Node *tmpNode = node;
      node = node->next;
      free(tmpNode);
   }
   initList(list);
}
 
/*
 * Adds a node after *prevNode
 * struct List *list -> The list of nodes
 * struct Node *prevNode   -> The node to add the new node after
 * void *data  -> The data to create the new node with
 * return   -> Returns the new node if it was created otherwise NULL
 */ 
struct Node *addAfter(struct List *list, 
         struct Node *prevNode, void *data)
{
   if(!prevNode)
      return addFront(list, data);

   struct Node *newNode = (struct Node *)
            malloc(sizeof(struct Node));
   if(!newNode)
      return NULL;

   newNode->data = data;
   newNode->next = prevNode->next;
   prevNode->next = newNode;

   return newNode;
}

/*
 * Reverse the order on all nodes in *list
 * struct List list  -> The list of nodes
 */
void reverseList(struct List *list)
{
   struct Node *prv = NULL;
   struct Node *cur = list->head;
   struct Node *nxt;
   while(cur) {
      nxt = cur->next;
      cur->next = prv;
      prv = cur;
      cur = nxt;
   }

   list->head = prv;
}
