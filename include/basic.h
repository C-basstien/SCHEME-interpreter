#ifndef _BASIC_H_
#define _BASIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "notify.h"


#define STRLEN       256
#define BIGSTRING 65536


#define TRUE    1
#define FALSE   0

typedef unsigned int uint;

typedef char* string;

#define init_string( s )    s=calloc(STRLEN, sizeof(char));\
                            memset( s, '\0', STRLEN );/*remplie le string de caractère \0 sur une longueur strlen*/

#ifdef __cplusplus
}
#endif

#endif /* _BASIC_H_ */
