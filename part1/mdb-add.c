/**********************************************************************
* FILENAME :        myadd.c          ASSIGNMENT :      lab4      
*
* DESCRIPTION :
*        Adds a record into a database
*
* PUBLIC FUNCTIONS :
*        struct Node *last_node(struct List *list)	-> 
*			Gets the last node of linked list *list
*
*        Copyright 2014 All rights reserved.
* 
* AUTHOR :    Theodore Ahlfeld        START DATE :    20141003
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mdb.h"
#include "mylist.h"

/* Function Prototypes */
struct Node *last_node(struct List *list);

static int node_num = 0;

int main(int argc, char *argv[]) {
   /* Error Handling for FILE *fp */
   if(argc == 1) {
      perror("No file name specified\n"\
            "Ex: ./mdb-add mdb-cs315\n");
      exit(1);
   }
   char *filename = argv[1];
   FILE *fp;   struct List list;
   initList(&list);

   /* Only try to read from database if the file exists */
   if((fp = fopen(filename, "rb"))) {
      if(!loadmdb(fp, &list)) {
         perror("Error loading database");
         exit(1);
      }
   }
   if(!(fp = fopen(filename, "ab"))) {
      perror("File could not load\n");
      exit(1);
   }

   char input[LINE];
   struct MdbRec *rec = (struct MdbRec *)malloc(sizeof(struct MdbRec));
   printf("name please (will truncate to 15 chars): ");
   fgets(input, sizeof(input), stdin);
   strncpy(rec->name, input, 16);
   
   printf("msg please (will truncate to 23 chars): ");
   fgets(input, sizeof(input), stdin);
   strncpy(rec->msg, input, 24);
   /* Makes either the last char or the nl char is a null terminator */
   rec->name[(strlen(rec->name)<size_name) ? strlen(rec->name)-1 : size_name-1] = '\0';
   rec->msg[(strlen(rec->msg)<size_msg) ? strlen(rec->msg)-1 : size_msg-1] = '\0';
   
   addAfter(&list, last_node(&list), rec);
   /* Prints the inputed entry and writes to file fp */
   printf("%4d: {%s} said {%s}\n", ++node_num, rec->name, rec->msg);
   fwrite(rec, sizeof(char), sizeof(struct MdbRec), fp);
   fclose(fp);
   freemdb(&list);
   return 0;
}

/*
 * Gets the last node in a linked list
 * struct List *list	-> 	The linked list to get the last node
 * return 		-> 	returns the last node in the list
 */
struct Node *last_node(struct List *list)
{
   struct Node *node = list->head;
   while(node && node->next) {
      node = node->next;
      node_num++;
   }
   if(node) node_num++;
   return node;
}
