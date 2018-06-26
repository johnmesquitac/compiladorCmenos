/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the TINY compiler*/
/* (allows only one symbol table)                   */
/* Symbol table is implemented as a chained         */
/* hash table                                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "globals.h"

/* SIZE is the size of the hash table */
#define SIZE 400

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/* the hash function */
static int hash (char* name, char* scope)
{ 
    int temp = 0;
    int i = 0;
    while (name[i] != '\0')
    { 
        temp = ((temp << SHIFT) + name[i]) % SIZE;
        ++i;
    }
    i = 0;
    while (scope[i] != '\0')
    { 
        temp = ((temp << SHIFT) + scope[i]) % SIZE;
        ++i;
    }
    return temp;
}

/* the list of line numbers of the source 
 * code in which a variable is referenced
 */
typedef struct LineListRec {
    int lineno;
    struct LineListRec *next;
} *LineList;

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec {
    char *name;
    char *scope;
    char *typeId;
    char *typeData;
    LineList lines;
    int memloc; /* memory location for variable */
    int tam;
    struct BucketListRec *next;
} *BucketList;

/* the hash table */
static BucketList hashTable[SIZE];

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert(char *name, int lineno, int loc, char *scope, char *typeId, char *typeData, int tam) {
    int h = hash(name, scope);
    BucketList l = hashTable[h];
    while ((l != NULL) && ((strcmp(name, l->name) != 0) || (strcmp(scope, l->scope) != 0)))
        l = l->next;
    if (l == NULL) /* variable not yet in table */
    {
        l = (BucketList) malloc(sizeof(struct BucketListRec));
        l->name = name;
        l->lines = (LineList) malloc(sizeof(struct LineListRec));
        l->lines->lineno = lineno;
        l->memloc = loc;
        l->lines->next = NULL;
        l->scope = scope;
        l->typeId = typeId;
        l->typeData = typeData;
        l->next = hashTable[h];
        l->tam = tam;
        hashTable[h] = l;
    } else /* found in table, so just add line number */
    {
        LineList t = l->lines;
        while (t->next != NULL) t = t->next;
        t->next = (LineList) malloc(sizeof(struct LineListRec));
        t->next->lineno = lineno;
        t->next->next = NULL;
    }
} /* st_insert */


/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup(char *name, char *scope) {
    int h = hash(name, scope);  
    BucketList l = hashTable[h];
    //printf("%s \t %s\n", name, scope);
    while ((l != NULL) && ((strcmp(name, l->name) != 0) || (strcmp(scope, l->scope) != 0))){
        //printf("Entrou %s\n", l->name);
        l = l->next;
    }
    //if(l != NULL) printf("Existe %s \t %s \t %d\n", l->name, l->scope, strcmp(name, l->name));
    if (l == NULL) return -1;
    else return l->memloc;
}

char *st_lookup_type(char *name, char *scope) {
    int h = hash(name, scope);
    BucketList l = hashTable[h];
    while ((l != NULL) && ((strcmp(name, l->name) != 0) || (strcmp(scope, l->scope) != 0)))
        l = l->next;
    if (l == NULL)
        return "null";
    else
        return l->typeData;
}

char *st_lookup_typeId(char *name, char *scope) {
    int h = hash(name, scope);
    BucketList l = hashTable[h];
    while ((l != NULL) && ((strcmp(name, l->name) != 0) || (strcmp(scope, l->scope) != 0)))
        l = l->next;
    if (l == NULL)
        return "null";
    else
        return l->typeId;
}


int st_lookup_tam(char *scope){
     int i,j=0;
     for (i = 0; i < SIZE; ++i) {
        if (hashTable[i] != NULL) {
            BucketList l = hashTable[i];
            while (l != NULL) {
                if(strcmp(scope, l->scope) == 0 && strcmp("call", l->typeId) != 0){ 
                    if(strcmp(l->typeId, "vector") != 0) j++;
                    else j = j + l->tam;
                }
                l = l->next;
            }
        }
    }
    return j+1;
}

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE *listing) {
    int i;
    fprintf(listing, "Location  Variable Name  Escopo    Tipo ID    Tipo Dado  Line Numbers\n");
    fprintf(listing, "--------  -------------  ------  -----------  ---------  ------------\n");
    for (i = 0; i < SIZE; ++i) {
        if (hashTable[i] != NULL) {
            BucketList l = hashTable[i];
            while (l != NULL) {
                LineList t = l->lines;
                fprintf(listing, "%-9d ", l->memloc);
                fprintf(listing, "%-14s ", l->name);
                fprintf(listing, "%-6s  ", l->scope);
                fprintf(listing, "%-11s  ", l->typeId);
                fprintf(listing, "%-7s  ", l->typeData);
                while (t != NULL) {
                    fprintf(listing, "%4d ", t->lineno);
                    t = t->next;
                }
                fprintf(listing, "\n");
                l = l->next;
            }
        }
    }
} /* printSymTab */
