#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"
typedef struct object_t object_t;
typedef object_t *object;
typedef object (*ptr_form )( object,object* );
typedef object (*ptr_primitive)( object );
struct object_t
{
    unsigned int type;
    union
    {
        num number;char character;char* string;char* symbol;
        struct pair_t{object car;object cdr;} pair;
        ptr_form form;
        ptr_primitive primitive;
        struct compound_t{object parms;object body;object* env;} compound;
        void* address;
    }data;
};

object make_object( unsigned int type );
object make_nil( void );
object make_number (num val);
object make_boolean(unsigned int val);
object make_symbol (char* sym );
object make_character (char chr);
object make_string (string str);
object make_pair (object car,object cdr);
object make_form(ptr_form f);
object make_primitive (ptr_primitive f);
object make_compound (object parms, object body, object* env);
object make_address (void* adr);
object copy_object (object o);

void kill_object (object o);


#define SCM_NUMBER       0x00
#define SCM_CHARACTER    0x01
#define SCM_STRING       0x02
#define SCM_PAIR         0x03
#define SCM_NIL          0x04
#define SCM_BOOLEAN      0x05
#define SCM_SYMBOL       0x06
#define SCM_FORM         0x07
#define SCM_PRIMITIVE    0x08
#define SCM_COMPOUND     0x09
#define SCM_ADDRESS      0x0a

extern object* main_env;
extern object nil;
extern object true;
extern object false;
extern object error;

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
