#ifndef _PRINT_H_
#define _PRINT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"

void print( object );
void print_atom( object );
void print_pair( object );

#ifdef __cplusplus
}
#endif

#endif /* _PRINT_H_ */
