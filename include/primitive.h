#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "eval.h"
#include "object.h"
#include "read.h"

object EQUAL(object args);
object SUP(object args);
object INF(object args);
object ADD(object args);
object SUBSTRACT(object args);
object MULTIPLY(object args);
object DIVIDE(object args);
object QUOTIENT(object args);
object REMAINDER(object args);
object CHAR_TO_INT(object args);
object INT_TO_CHAR(object args);
object STRING_TO_NUMBER(object args);
object NUMBER_TO_STRING(object args);
object SYMBOL_TO_STRING(object args);
object STRING_TO_SYMBOL(object args);
object CONS(object args);
object CAR(object args);
object CDR(object args);
object IS_STRING(object args);
object IS_BOOLEAN(object args);
object IS_NIL(object args);
object IS_NUMBER(object args);
object IS_SYMBOL(object args);
object IS_CHAR(object args);
object IS_PAIR(object args);
object LIST(object args);
object LENGTH (object args);
object GLOBALCARCDR (string func,object args);

#ifdef __cplusplus
}
#endif
#endif /* _PRIMITIVE_H_*/
