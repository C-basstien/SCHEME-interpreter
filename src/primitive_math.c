#include "primitive.h"
/**math primitives**/
/*Conditional*/
object EQUAL(object args)
{
	object buff=args;
	object previous=buff->data.pair.car;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->type!=SCM_PAIR)
		{
			if(buff==previous) {}
			else
			{
				if(buff->type!=previous->type) {return false;}
				if(buff->type!=SCM_SYMBOL)
				{
					if(previous->type==SCM_NUMBER) {if(!equal_num(previous->data.number,buff->data.number)) {return false;}}
					else if(previous->type==SCM_CHARACTER) {if(buff->data.character!=previous->data.character) {return false;}}
					else if(previous->type==SCM_STRING) {if(strcmp (buff->data.string,previous->data.string)) {return false;}}
				}
			}
			return true;
		}
		if(buff->data.pair.car==previous) {}
		else
		{
			if(buff->data.pair.car->type!=previous->type) {return false;}
			if((buff->data.pair.car->type!=SCM_SYMBOL)&&(buff->data.pair.car->type!=SCM_PAIR))
			{
				if(previous->type==SCM_NUMBER) {if(!equal_num(previous->data.number,buff->data.pair.car->data.number)) {return false;}}
				else if(previous->type==SCM_CHARACTER) {if(buff->data.pair.car->data.character!=previous->data.character) {return false;}}
				else if(previous->type==SCM_STRING) {if(strcmp (buff->data.pair.car->data.string,previous->data.string)) {return false;}}
			}
		}
		buff=buff->data.pair.cdr;
	}
	return true;
}

object INF(object args)
{
	object buff=args;
	int first=1;
	num last_num;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->type!=SCM_PAIR)
		{
			if(buff->type==SCM_NUMBER)
			{
				if(first) {first=0;}
				else if(compare_inf_num(last_num,buff->data.number)) {return true;}
				return false;
			}
			else {WARNING_MSG("< only accept numbers"); return error;}
		}

		if(buff->data.pair.car->type==SCM_NUMBER)
		{
			if(first) {first=0;}
			else if(!compare_inf_num(last_num,buff->data.pair.car->data.number)) {return false;}
			last_num=buff->data.pair.car->data.number;
		}
		else {WARNING_MSG("< only accept numbers"); return error;}
		buff=buff->data.pair.cdr;
	}
	return true;
}
object SUP(object args)
{
	object buff=args;
	int first=1;
	num last_num;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->type!=SCM_PAIR)
		{
			if(buff->type==SCM_NUMBER)
			{
				if(first) {first=0;}
				else if(compare_sup_num(last_num,buff->data.number)) {return true;}
				return false;
			}
			else {WARNING_MSG("> only accept numbers"); return error;}
		}
		if(buff->data.pair.car->type==SCM_NUMBER)
		{
			if(first) {first=0;}
			else if(!compare_sup_num(last_num,buff->data.pair.car->data.number)) {return false;}
			last_num=buff->data.pair.car->data.number;
		}
		else {WARNING_MSG("> only accept numbers"); return error;}
		buff=buff->data.pair.cdr;
	}
	return true;

}

object ADD(object args)
{
	object buff=args;
	num last_num; last_num.numtype=NUM_INTEGER; last_num.val.integer=0;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->type!=SCM_PAIR)
		{
			if(buff->type==SCM_NUMBER) {last_num=add_num(last_num,buff->data.number);}
			else {WARNING_MSG("+ only accept numbers"); return error;}
			return make_number(last_num);
		}
		if(buff->data.pair.car->type==SCM_NUMBER)
		{
			last_num=add_num(last_num,buff->data.pair.car->data.number);
		}

		else {WARNING_MSG("+ only accept numbers"); return error;}
		buff=buff->data.pair.cdr;
	}
	return make_number(last_num);
}
object SUBSTRACT(object args)
{
	object buff=args;
	num last_num; last_num.numtype=NUM_INTEGER; last_num.val.integer=0;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	last_num=sub_num(buff->data.pair.car->data.number,last_num);
	buff=buff->data.pair.cdr;
	while(buff!=nil)
	{
		if(buff->type!=SCM_PAIR)
		{
			if(buff->type==SCM_NUMBER) {last_num=sub_num(last_num,buff->data.number);}
			else {WARNING_MSG("- only accept numbers"); return error;}
			return make_number(last_num);
		}
		if(buff->data.pair.car->type==SCM_NUMBER)
		{
			last_num=sub_num(last_num,buff->data.pair.car->data.number);
		}
		else {WARNING_MSG("- only accept numbers"); return error;}
		buff=buff->data.pair.cdr;
	}
	return make_number(last_num);
}
object MULTIPLY(object args)
{

	object buff=args;
	num last_num; last_num.numtype=NUM_INTEGER; last_num.val.integer=1;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->type!=SCM_PAIR)
		{
			if(buff->type==SCM_NUMBER) {last_num=mul_num(last_num,buff->data.number);}
			else {WARNING_MSG("* only accept numbers"); return error;}
			return make_number(last_num);
		}
		if(buff->data.pair.car->type==SCM_NUMBER)
		{
			last_num=mul_num(last_num,buff->data.pair.car->data.number);
		}
		else {WARNING_MSG("* only accept numbers"); return error;}
		buff=buff->data.pair.cdr;
	}
	return make_number(last_num);
}
object DIVIDE(object args)
{
	object buff=args;
	int first=1;
	num last_num;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->type!=SCM_PAIR)
		{
			if(buff->type==SCM_NUMBER) {last_num=div_num(last_num,buff->data.number);}
			else {WARNING_MSG("/ only accept numbers"); return error;}
			return make_number(last_num);
		}
		if(buff->data.pair.car->type==SCM_NUMBER)
		{
			if(first) {last_num=buff->data.pair.car->data.number; first=0;}
			else {last_num=div_num(last_num,buff->data.pair.car->data.number);}
		}
		else {WARNING_MSG("/ only accept numbers"); return error;}
		buff=buff->data.pair.cdr;
	}
	return make_number(last_num);
}
object QUOTIENT(object args)
{
	object buff=args;
	int first=1;
	num last_num;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->type!=SCM_PAIR)
		{
			if(buff->type==SCM_NUMBER) {last_num=quotient(last_num,buff->data.number);}
			else {WARNING_MSG("quotient only accept numbers"); return error;}
			return make_number(last_num);
		}
		if(buff->data.pair.car->type==SCM_NUMBER)
		{
			if(first) {last_num=buff->data.pair.car->data.number; first=0;}
			else {last_num=quotient(last_num,buff->data.pair.car->data.number);}
		}
		else {WARNING_MSG("quotient only accept numbers"); return error;}
		buff=buff->data.pair.cdr;
	}
	return make_number(last_num);
}
object REMAINDER(object args)
{
	object buff=args;
	int first=1;
	num last_num;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	while(buff!=nil)
	{
		if(buff->type!=SCM_PAIR)
		{
			if(buff->type==SCM_NUMBER) {last_num=remainder(last_num,buff->data.number);}
			else {WARNING_MSG("remainder only accept numbers"); return error;}
			return make_number(last_num);
		}
		if(buff->data.pair.car->type==SCM_NUMBER)
		{
			if(first) {last_num=buff->data.pair.car->data.number; first=0;}
			else {last_num=remainder(last_num,buff->data.pair.car->data.number);}
		}
		else {WARNING_MSG("remainders only accept numbers"); return error;}
		buff=buff->data.pair.cdr;
	}
	return make_number(last_num);
}
