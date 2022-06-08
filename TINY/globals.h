#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

//Maxreserved = number of reserved words
#define MAXRESERVED 8

typedef enum {
    //Book Keeping Tokens
    ENDFILE,ERROR,
    //Reserved Words
    IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,
    //Multicharacter Tokens
    ID,NUM,
    //Special Symbols
    ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI
}TokenType;

extern FILE* source; //source code text file
extern FILE* listing; //listing output text file
extern FILE* code; //code text file for TM Simulator

extern int lineno; //source line number for listing

//SYNTAX TREE FOR PARSING
 
 typedef enum {StmtK,ExpK} NodeKind;
 typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StatKind;
 typedef enum {OpK,ConstK,IdK} ExpKind;

 //ExpType is used for type checking
 typedef enum {Void,Integer,Boolean} ExpType;

 #define MAXCHILDREN 3

 typedef struct treeNode {
     struct treeNode *child[MAXCHILDREN];
     struct treeNode *sibling;
     int lineno;
     NodeKind nodekind;
     union {
         StatKind stat;
         ExpKind exp; 
     }kind;
     union {
         TokenType op;
         int val;
         char *name;
     }sttr;
     ExpType type; //For type checking of expr
 }TreeNode;

 //Flags for tracing
 
 /*EchoSource = TRUE casues the source program to
   be echoed to the listing file with line numbers
   during parsing
 */

extern int EchoSource;

/*
TraceScan = TRUE causes token information to be
printed to be listing file as each token is
recognised by the scanner
*/

extern int TraceScan;

/*
TraceParse = TRUE causes the syntax tree to be 
printed to the listing file in linearised form
using indents for children
*/
extern int TraceParse;

/*
TraceAnalyse = TRUE causes the symbol table inserts
and lookups to be reported to the listing file
*/
extern int TraceAnalyse;

/*
TraceCode = TRUE causes the comments to be written
to the TM code file as code is generated
*/
extern int TraceCode;

/*
Error = TRUE prevents further passes if an error occurs
*/
extern int Error;
#endif