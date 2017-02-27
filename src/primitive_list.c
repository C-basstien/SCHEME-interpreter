#include "primitive.h"

/**List primitives**/
object CONS(object args)
{
	if(args==nil) {WARNING_MSG("No operand after operator"); return error;}
	if(args->type!=SCM_PAIR) {WARNING_MSG("Not enough operands after operator"); return error;}
	if(args->data.pair.cdr->type!=SCM_PAIR) {return make_pair(args->data.pair.car,args->data.pair.cdr);} /*Cas rare*/
	if(args->data.pair.cdr->data.pair.cdr!=nil) {WARNING_MSG("Too much operands after operator"); return error;}
	object o = make_pair(args->data.pair.car,args->data.pair.cdr->data.pair.car);
	return o;
}
object CAR(object args)
{
	if(args==nil) {WARNING_MSG("No operand after operator"); return error;}
	if(args->type!=SCM_PAIR) {WARNING_MSG("Operand is not a pair"); return error;}
	return args->data.pair.car;
}
object CDR(object args)
{
	if(args==nil) {WARNING_MSG("No operand after operator"); return error;}
	if(args->type!=SCM_PAIR) {WARNING_MSG("Operand is not a pair"); return error;}
	return args->data.pair.cdr;
}
object SET_CAR(object args,object env)
{
	return args;
}
object SET_CDR(object args,object env)
{
	return args;
}
object LIST(object args)
{
	return args;
}
object LENGTH (object args)
{
    if (args==error){return error;}
    object buff=args->data.pair.car;
    num res;res.numtype=NUM_INTEGER;res.val.integer=0;
	if(buff==nil) {return make_number(res);}
	while(buff!=nil)
	{
	    res.val.integer++;
		buff=buff->data.pair.cdr;
	}
	return make_number(res);
}
object GLOBALCARCDR (string func,object args)
{
    object res=args;
    int i;
    for(i=strlen(func)-2;i>=1;i--)
    {
        if(func[i]=='a'){res=CAR(res);}
        else{res=CDR(res);}
    }
    return res;
}
