#ifndef _MEM_H_
#define _MEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

void *sfs_malloc( size_t size );
void  sfs_free( void *ptr );


#ifdef __cplusplus
}
#endif

#endif /* _MEM_H_ */
