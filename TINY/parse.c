#include "globals.h"
// #include "util.h"
// #include "scan.h"
// #include "parse.h"

static TreeMode=stat_sequence(void);
static TreeMode=statement(void);
static TreeMode=if_stmt(void);
static TreeMode=repeat_stmt(void);
static TreeMode=assign_stat(void);
static TreeMode=write_stmt(void);
static TreeMode=simple_exp(void);
static TreeMode=exp(void);
static TreeMode=term(void);
static TreeMode=factor(void);

static void syntaxError(char *message){
    fprintf(listing,"\n>>> ");
    fprintf(listing,"Syntax error at line")
}

static void match(TokenType expected){
    if (token==expected) token =getToken();
    else{
        syntaxError("ünexpected token -> ");
        printToken(token,tokenString);
        fprintf(listing,"      ");
    }
}

TreeMode *stat_sequence(void){
    TreeMode *t = statement();
    TreeMode *p=t;
    while((token!=ENDFILE)&&(token!=END)&&(token!=ELSE)&&(token!=UNTIL)){
        TreeMode *q;
        match(SEMI);
        if (q!=NULL){
            if(t==NULL)t=p=q;
            else{
                p->sibling=q;
                p=q;
            }
        }
    }
    return t;
}

TreeMode *statement (void){
    TreeMode *t=NULL;
    switch(token){
        case IF: t=if_stmt();break;
        case REPEAT:t=repeat_stmt();break;
        case READ: t=read_stmt();break;
        case WRITE:t=write_stmt();break;
        default:syntaxError("unexpected token -> ");
        printToken(token,tokenString);
        token=getToken();
        break;
    }
    return t;
}