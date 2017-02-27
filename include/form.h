#ifndef _FORME_H_
#define _FORME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "eval.h"
#include "object.h"

object DEFINE(object args,object* env);
object SET(object args,object* env);
object IF(object args, object* env);
object AND(object args,object* env);
object OR(object args, object* env);
object QUOTE(object args, object* env);
object BEGIN(object args, object* env);
object LAMBDA(object args, object* env);
object LET(object args, object* env);
object LETX(object args, object* env);
object MAP(object args, object* env);
object SHOW(object args, object* env);

void read_var_let (object paraval,object* Lpara,object* Lval);
void read_val_map(object L,object* Lval,int n);
void make_link(object* L,object val);
object make_letx (object body,object Lpara,object Lval, object* env);
#ifdef __cplusplus
}
#endif
#endif /*_FORME_H_*/
