/* Main program for the TINY Compiler */
/* Kenneth Louden's Legendary Code */
#include "globals.h"
/*  Set NO_PARSE to TRUE to get a scanner-only compiler
    Set NO_ANALYSE to TRUE to get a parser-only compiler 
    Set NO_CODE to TRUE to get a compiler that generates no code */
#define NO_PARSE FALSE
#define NO_ANALYSE FALSE
#define NO_CODE FALSE

#include "util.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#if !NO_ANALYSE
#include "analyse.h"
#if !NO_CODE
#include "cgen.h"
#endif
#endif
#endif
/* Global Variables be declared here */
int lineno = 0;
FILE *source;
FILE *listing;
FILE *code;

//Allocate and set tracing flags
int EchoSource = TRUE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyse = TRUE;
int TraceCode = TRUE;
int Error = FALSE;

main(int argc,char *argv[]) {
    TreeNode *syntaxTree;
    char pgm[20]; //Source Code Name
    if(argc!=2) {
        fprintf(stderr,"usage: %s <filename> \n",argv[0]);
        exit(1);
    }
    strcpy(pgm,argv[1]);
    if(strchr(pgm,'.')==NULL)
        strcat(pgm,".tny");
    source = fopen(pgm,"r");
    if(source==NULL) {
        fprintf(stderr,"File %s is not found!\n",pgm);
        exit(1);
    }
    listing = stdout;
    fprintf(listing,"\nTINY COMPILATION:%s\n",pgm);
#if NO_PARSE
    while(getToken()!=ENDFILE);
#else
    syntaxTree = parse();
    if(TraceParse) {
        fprintf(listing,"\nSyntax Tree:\n");
        printTree(syntaxTree);
    }
#if !NO_ANALYSE
    if(!Error) {
        fprintf(listing,"\nBuilding Symbol Table...\n");
        buildSymtab(syntaxTree);
        fprintf(listing,"\nChecking Types...\n");
        typeCheck(syntaxTree);
        fprintf(listing,"\nType Checking Done!\n");
    }
#if !NO_CODE
    if(!Error) {
        char *codefile;
        int fnlen = strcspn(pgm,".");
        codefile = (char *)calloc(fnlen+4,sizeof(char));
        strncpy(codefile,pgm,fnlen);
        strcat(codefile,".tm");
        code = fopen(codefile,"w");
        if(code == NULL) {
            printf("Unable to open %s\n",codefile);
            exit(1);
        }
        codeGen(syntaxTree,codefile);
        fclose(code);
    }
#endif
#endif
#endif
    return 0;    
}