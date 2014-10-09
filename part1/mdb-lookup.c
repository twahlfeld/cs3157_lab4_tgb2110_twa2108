/**********************************************************************
* FILENAME :        mdb-lookup.c          ASSIGNMENT :      lab4      
*
* DESCRIPTION :
*        Reads a database and searches for a specified entry.
*
* PUBLIC FUNCTIONS :
*        void find_match(void *data)	->	Finds the 5 char string in *data
*                                                          
*        Copyright 2014 All rights reserved.
* 
* AUTHOR :    Theodore Ahlfeld        START DATE :    20141003
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylist.h"
#include "mdb.h"

/* Function prototypes */
void find_match(void *data);

/* Global variables for searching nodes */
static char substring[6];
static int resultNum = 1;

int main(int argc, char *argv[])
{
   /* Error handling for FILE *fp */
   if(argc == 1) {
      perror("No file name specified\n"\
            "Ex: ./mdb-lookup mdb-cs315\n");
      exit(1);
   }
   char *filename = argv[1];
   FILE *fp = fopen(filename, "rb");
   struct List list;
   initList(&list);
   if(fp == NULL) {
      perror(filename);
      exit(1);
   }
   if(!loadmdb(fp, &list)) {
      perror("Error loading database");
      exit(1);
   }

   char input[sizeof(struct MdbRec)];
   printf("lookup: ");
   /* Searches for each record for a string until EOF is read */
   while(fgets(input, sizeof(input), stdin)) {
      
      strncpy(substring, input, 5);
      /* Makes either the last char or the nl a null terminator */
      substring[(strlen(input) <= 5)? strlen(substring)-1 : 5] = '\0';
      traverseList(&list, &find_match);
      resultNum = 1;
      printf("lookup: ");
   }
   freemdb(&list);
   printf("\nQuiting %s\n", argv[0]);
   return 0;
}

/*
 * Searches a record for the specified string
 * void *data	->	The data of a linked list
 */
void find_match(void *data)
{
   struct MdbRec *rec = (struct MdbRec *)data;
   if(strstr(rec->name, substring) || strstr(rec->msg, substring))
      printf("%4d: {%s} said {%s}\n", resultNum++, rec->name, rec->msg);
}
