#include "primitive.h"
#include "read.h"
/**convertion object types primitves**/
object CHAR_TO_INT(object args)
{
	if(args==nil) {WARNING_MSG("No operand after operator"); return error;}
	if(args->type==SCM_PAIR)
	{
		if(args->data.pair.cdr!=nil) {WARNING_MSG("Too much operands after operator"); return error;}
		if(args->data.pair.car->type!=SCM_CHARACTER) {WARNING_MSG("Operand is not a character"); return error;}
		num x;
		x.numtype=NUM_INTEGER;
		x.val.integer=args->data.pair.car->data.character - '0';
		object integer = make_number(x);
		return integer;
	}
	else {
		if(args->type!=SCM_CHARACTER) {WARNING_MSG("Operand is not a character"); return error;}
		num x;
		x.numtype=NUM_INTEGER;
		x.val.integer=args->data.character - '0';
		object integer = make_number(x);
		return integer;
	}

}
object INT_TO_CHAR(object args)
{
	if(args==nil) {WARNING_MSG("No operand after operator"); return error;}
	if(args->type==SCM_PAIR) {
		if(args->data.pair.cdr!=nil) {WARNING_MSG("Too much operands after operator"); return error;}
		if(args->data.pair.car->type!=SCM_NUMBER) {WARNING_MSG("Operand is not a number"); return error;}
		if(args->data.pair.car->data.number.numtype!=NUM_INTEGER) {WARNING_MSG("Operand is not an integer"); return error;}
		object character = make_character(args->data.pair.car->data.number.val.integer + '0');
		return character;
	}
	else {
		if(args->type!=SCM_NUMBER) {WARNING_MSG("Operand is not a number"); return error;}
		if(args->data.number.numtype!=NUM_INTEGER) {WARNING_MSG("Operand is not an integer"); return error;}
		object character = make_character(args->data.number.val.integer + '0');
		return character;
	}

}
object NUMBER_TO_STRING(object args)
{
    if(args==nil) {WARNING_MSG("No operand after operator"); return error;}
	if(args->type==SCM_PAIR)
	{
		if(args->data.pair.cdr!=nil) {WARNING_MSG("Too much operands after operator"); return error;}
		if(args->data.pair.car->type!=SCM_NUMBER) {WARNING_MSG("Operand is not a number"); return error;}
		object str=make_string(conv_num_string(args->data.pair.car->data.number));
		return str;
	}
	else
	{
		if(args->type!=SCM_NUMBER) {WARNING_MSG("Operand is not a string"); return error;}
		object str=make_string(conv_num_string(args->data.number));
		return str;
	}
}
object STRING_TO_NUMBER(object args)
{
	if(args==nil) {WARNING_MSG("No operand after operator"); return error;}
	if(args->type==SCM_PAIR)
	{
		if(args->data.pair.cdr!=nil) {WARNING_MSG("Too much operands after operator"); return error;}
		if(args->data.pair.car->type!=SCM_STRING) {WARNING_MSG("Operand is not a string"); return error;}
		object numb=conv_string_num (args->data.pair.car->data.string);
		return numb;
	}
	else
	{
		if(args->type!=SCM_STRING) {WARNING_MSG("Operand is not a string"); return error;}
		object numb=conv_string_num(args->data.string);
		return numb;

	}
}
object SYMBOL_TO_STRING(object args)
{
	if(args==nil) {WARNING_MSG("No operand after operator"); return error;}
	if(args->type==SCM_PAIR)
	{
		if(args->data.pair.cdr!=nil) {WARNING_MSG("Too much operands after operator"); return error;}
		if(args->data.pair.car->type!=SCM_SYMBOL) {WARNING_MSG("Operand is not a symbol"); return error;}
		object string = make_string(args->data.pair.car->data.symbol);
		return string;
	}
	else
	{
		if(args->type!=SCM_SYMBOL) {WARNING_MSG("Operand is not a symbol"); return error;}
		object string = make_string(args->data.symbol);
		return string;
	}
}
object STRING_TO_SYMBOL(object args)
{
	if(args==nil) {WARNING_MSG("No operand after operator"); return error;}
	if(args->type==SCM_PAIR)
	{
		if(args->data.pair.cdr!=nil) {WARNING_MSG("Too much operands after operator"); return error;}
		if(args->data.pair.car->type!=SCM_STRING) {WARNING_MSG("Operand is not a string"); return error;}
		object symbol = make_symbol(args->data.pair.car->data.string);
		return symbol;
	}
	else
	{
		if(args->type!=SCM_STRING) {WARNING_MSG("Operand is not a string"); return error;}
		object symbol = make_symbol(args->data.string);
		return symbol;
	}
}

