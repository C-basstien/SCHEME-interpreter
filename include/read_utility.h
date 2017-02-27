#ifndef _READUT_H_
#define _READUT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "object.h"

int isDigit(char c);
int isComplex (char* in);
int isGlobalcarcdr(object osym);
object conv_string_num (char* atom);
string conv_num_string(num numb);
void simplifie_chaine(char* input, uint *pos,int l);
int in_a_string(char* input,uint *pos,int l);
void find_special_special_string (string str );

#ifdef __cplusplus
}
#endif

#endif /* _READUT_H_ */
