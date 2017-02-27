#ifndef _EVAL_H_
#define _EVAL_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "object.h"
#include "notify.h"
#include "form.h"
#include "primitive.h"
#include "environment.h"
void init_interpreter ( void );
object eval( object s_exprs, object* env );
object eval_args(object args, object* env);

#ifdef __cplusplus
}
#endif

#endif /* _EVAL_H_ */
