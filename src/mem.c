#include "mem.h"


void *sfs_malloc( size_t size ) {

    return malloc( size );
}

void  sfs_free( void *ptr ) {

    free( ptr );
}

