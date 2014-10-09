/**********************************************************************
* FILENAME :        mdb.c          ASSIGNMENT :      lab4      
*
* DESCRIPTION :
*        Loads a database and stores each record in a linked list.
*
* PUBLIC FUNCTIONS :
*    	int loadmdb(FILE *fp, struct List *dest) ->
*			Loads each record from file *fp to linked list *dest
*	void freemdb(struct List *list) ->
			frees all records and nodes in the linked list *list

*        Copyright 2014 All rights reserved.
* 
* AUTHOR :    Theodore Ahlfeld        START DATE :    20141003
*
*/

#include <stdlib.h>
#include "mdb.h"
#include "mylist.h"

/*
 * Load a linked list with all entries from a file
 * FILE *fp		->	The database file
 * struct List *dest	->	The linked list to store the database records in
 * return		->	Returns 0 if load failed otherwise return 1
 */
int loadmdb(FILE *fp, struct List *dest)
{
   /* Ensures file is valid */
   if (!fp) 
      return 0;
   
   struct Node *newNode = NULL;
   struct MdbRec *rec = (struct MdbRec *)malloc(sizeof(struct MdbRec));
   /* Reads a MdbRec struct from file fp to store in linked list until EOF is found */
   while(fread(rec, sizeof(struct MdbRec), sizeof(char), fp))
   {
      /* Add new node to list and allocates for the next record */
      newNode = addAfter(dest, newNode, rec);
      rec = (struct MdbRec *)malloc(sizeof(struct MdbRec));
   }
   /* Frees the last garbage record and closes the file */
   free(rec);
   fclose(fp);
   return 1;
}

/*
 * Frees the database and all nodes and records
 * struct List *list	->	The list to free all nodes and records from
 */
void freemdb(struct List *list)
{
   traverseList(list, &free);
   removeAllNodes(list);
}
