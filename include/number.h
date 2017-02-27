#ifndef _NUMBER_H_
#define _NUMBER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "basic.h"
#include <limits.h>
#include <math.h>

#define NUM_REAL     0x00
#define NUM_INTEGER  0x01
#define NUM_UINTEGER 0x02
#define NUM_COMPLEX  0x03
#define NUM_UNDEF    0x04
#define NUM_PINFTY   0x05
#define NUM_MINFTY   0x06

typedef struct num_t
{
    uint numtype;
    union
    {
        double real;
        int integer;
        uint uinteger;
        struct cmplx_num{double RE;double IM;}complex;
    }val;

} num;
int equal_num(num a ,num b);
int compare_sup_num(num a,num b);
int compare_inf_num(num a,num b);
num add_num(num a,num b);
num sub_num(num a,num b);
num mul_num(num a,num b);
num div_num(num a,num b);
num quotient(num a,num b);
num remainder(num a,num b);
num norm_num (num a);

#ifdef __cplusplus
}
#endif

#endif /* _NUMBER_H_ */
