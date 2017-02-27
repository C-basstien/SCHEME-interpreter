#include "primitive.h"
/**test object types primitves**/

object IS_NIL(object args)
{
	object buff=args;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->data.pair.car->type!=SCM_NIL)
		{
			return false;
		}
		buff=buff->data.pair.cdr;
	}
	return true;
}
object IS_BOOLEAN(object args)
{
	object buff=args;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->data.pair.car->type!=SCM_BOOLEAN)
		{
			return false;
		}
		buff=buff->data.pair.cdr;
	}
	return true;
}
object IS_STRING(object args)
{
	object buff=args;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->data.pair.car->type!=SCM_STRING)
		{
			return false;
		}
		buff=buff->data.pair.cdr;
	}
	return true;
}
object IS_SYMBOL(object args)
{
	object buff=args;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->data.pair.car->type!=SCM_SYMBOL)
		{
			return false;
		}
		buff=buff->data.pair.cdr;
	}
	return true;
}
object IS_NUMBER(object args)
{
	object buff=args;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->data.pair.car->type!=SCM_NUMBER)
		{
			return false;
		}
		buff=buff->data.pair.cdr;
	}
	return true;
}
object IS_CHAR(object args)
{
	object buff=args;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->data.pair.car->type!=SCM_CHARACTER)
		{
			return false;
		}
		buff=buff->data.pair.cdr;
	}
	return true;
}
object IS_PAIR(object args)
{
	object buff=args;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->data.pair.car->type!=SCM_PAIR)
		{
			return false;
		}
		buff=buff->data.pair.cdr;
	}
	return true;
}
