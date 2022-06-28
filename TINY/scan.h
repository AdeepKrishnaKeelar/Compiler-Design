/* 
The scanner interface for the TINY Compiler
*/
#ifndef _SCAN_H_
#define _SCAN_H_

//Maximum size of the token is 40
#define MAXTOKENLEN 40

//tokenString array stores the lexeme of each token
extern char tokenString[MAXTOKENLEN+1];

//function getToken returns the next token in source file
TokenType getToken(void);

#endif
