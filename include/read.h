#ifndef _READ_H_
#define _READ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "object.h"
#include "read_utility.h"

object read_atom(char* input, uint* pos);
object read_pair(char* input, uint* pos);
object read(char* input, uint* pos);


#ifdef __cplusplus
}
#endif

#endif /* _READ_H_ */
