#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "object.h"
#include "print.h"

#define HSIZE 101
unsigned int hash (char* str,unsigned int mod);
object* create_env(void* end_adr,unsigned int size);
void kill_env(object* env);
void add_var(object* env,object sym,object val);
object find_var(object* env,object sym);
void modify_var_value (object var,object val);
void define_map(object* env,object sym, object val);
void print_env(object* env);
void print_cell(object cenv);
void print_var(object o);

#ifdef __cplusplus
}
#endif
#endif /* _ENVIRONMENT_H_*/
