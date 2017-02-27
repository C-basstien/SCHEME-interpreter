#include "object.h"
#include "mem.h"


object make_object( uint type )
{
	object o=malloc(sizeof( *o ));
	o->type=type;
	return o;
}

object make_nil( void )
{
	object o=make_object( SCM_NIL );
	return o;
}

object make_boolean(unsigned int val)
{
	object o=make_object(SCM_BOOLEAN);
	o->data.number.numtype=NUM_INTEGER;
	o->data.number.val.integer=val;
	return o;
}
object make_symbol (string sym )
{
	object o=make_object(SCM_SYMBOL);
	o->data.symbol=calloc(strlen(sym), sizeof(char));
	strncpy (o->data.symbol,sym,strlen(sym));
	return o;
}
object make_number (num n)
{
	object o=make_object(SCM_NUMBER);
	if (n.numtype==NUM_REAL)
	{
		o->data.number.numtype=NUM_REAL;
		o->data.number.val.real =n.val.real;
	}
	else if (n.numtype==NUM_INTEGER)
	{
		o->data.number.numtype=NUM_INTEGER;
		o->data.number.val.integer=n.val.integer;
	}
	else if (n.numtype==NUM_UINTEGER)
	{
		o->data.number.numtype=NUM_UINTEGER;
		o->data.number.val.uinteger=n.val.uinteger;
	}
	else if (n.numtype==NUM_COMPLEX)
	{
		o->data.number.numtype=NUM_COMPLEX;
		o->data.number.val.complex.RE =n.val.complex.RE;
		o->data.number.val.complex.IM =n.val.complex.IM;
	}
	else if (n.numtype==NUM_UNDEF)
	{
		o->data.number.numtype=NUM_UNDEF;
	}
	else if (n.numtype==NUM_PINFTY)
	{
		o->data.number.numtype=NUM_PINFTY;
	}
	else if (n.numtype==NUM_MINFTY)
	{
		o->data.number.numtype=NUM_MINFTY;
	}
	return o;
}
object make_character (char chr)
{
	object o=make_object(SCM_CHARACTER);
	o->data.character = chr;
	return o;
}
object make_string (string str)
{
	object o=make_object(SCM_STRING);
	o->data.string=calloc(strlen(str), sizeof(char));
	strncpy (o->data.string,str,strlen(str));
	return o;
}
object make_pair (object car,object cdr)
{
	object o=make_object(SCM_PAIR);
	o->data.pair.car =copy_object(car);
	o->data.pair.cdr =copy_object(cdr);
	return o;
}
object make_form (ptr_form f)
{
    object o=make_object(SCM_FORM);
    o->data.form=f;
    return o;
}
object make_primitive (ptr_primitive f)
{
    object o=make_object(SCM_PRIMITIVE);
    o->data.primitive=f;
    return o;
}
object make_compound(object parms, object body, object* env)
{
    object o=make_object(SCM_COMPOUND);
    o->data.compound.parms = parms;
    o->data.compound.body = body;
    o->data.compound.env = env;
    return o;
}
object make_address(void* adr)
{
    object o=make_object(SCM_ADDRESS);
    o->data.address=adr;
}
object copy_object (object o)
{
	object r = NULL;
	switch(o->type)
	{
	    case SCM_NUMBER:{r=make_number(o->data.number);return r;}break;
        case SCM_CHARACTER:{r=make_character(o->data.character); return r;}break;
        case SCM_STRING:{r=make_string(o->data.string); return r;}break;
        case SCM_PAIR:{r=make_pair(o->data.pair.car,o->data.pair.cdr); return r;}break;
        case SCM_NIL:{r=nil; return r;}break;
        case SCM_BOOLEAN:{if(o==true){return true;}return false;}break;
        case SCM_SYMBOL:{r=make_symbol(o->data.symbol); return r;}break;
        case SCM_FORM:{r=make_form(o->data.form);return r;}break;
        case SCM_PRIMITIVE:{r=make_primitive(o->data.primitive);return r;}break;
        case SCM_COMPOUND:{r=make_compound(o->data.compound.parms,o->data.compound.body,o->data.compound.env);return r;}break;
        case SCM_ADDRESS:{r=make_address(o->data.address);return r;}break;
	}
	return r;
}
void kill_object (object o)
{
    switch(o->type)
    {
        case SCM_STRING:{free(o->data.string);free(o);}break;
        case SCM_SYMBOL:{free(o->data.symbol);free(o);}break;
        case SCM_PAIR:{kill_object(o->data.pair.car); kill_object(o->data.pair.cdr);free(o);}break;
        case SCM_COMPOUND:{kill_object(o->data.compound.parms);kill_object(o->data.compound.body);kill_object(o->data.compound.env);free(o);}break;
        default:{free(o);}break;
    }
}
