#ifndef _GETSEXRP_H_
#define _GETSEXRP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef enum
{
	NOTHING,        /* rien n'a ete trouve encore.. */
	STRING_ATOME,   /* la premiere trouvee dans la ligne semble etre un atome */
	BASIC_ATOME,    /* la premiere trouvee dans la ligne semble etre d'une chaine */
	S_EXPR_PARENTHESIS, /* la premiere trouvee dans la ligne semble etre une expression parenthesee */
	FINISHED        /* on a trouve une S-Expr bien formee */
} EXPRESSION_TYPE_T;

enum {S_OK, S_KO, S_END};

void flip( uint *i );
char* first_usefull_char(char* line);
unsigned int   get_sexpr( string input, FILE *fp );

#ifdef __cplusplus
}
#endif
#endif /*_GETSEXRP_H_*/
