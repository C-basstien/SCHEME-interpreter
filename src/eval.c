#include "eval.h"


object eval_args(object args, object* env)
{
    object res=make_pair(nil,nil);
    if(args->type==SCM_PAIR)
    {
        res->data.pair.car=eval(args->data.pair.car,env);
        res->data.pair.cdr=eval_args(args->data.pair.cdr,env);
    }
    else{res=eval(args,env);}
    return res;/*(function (..arg0..) (..arg1..) ...(..argn..))--> eval(function eval(..arg0..) eval(..arg1..) ...eval(..argn..))*/
}

object eval( object s_exprs, object* env )
{
	object buff=s_exprs;/*return s_exprs;*/
	object var;
    new_eval:/*label for a new evaluation of the expression after a if instruction*/
	if(buff->type!=SCM_PAIR)
	{
		if (buff->type==SCM_SYMBOL) {buff=make_pair(buff,nil);} /* symbol-->(symbol ) */
		else {return buff;} /*atome--> atome*/
	}
	if(buff->data.pair.car->type==SCM_PAIR&&buff->data.pair.cdr==nil){buff=buff->data.pair.car;}/*((car cdr)())-->(car cdr)*/
	if (buff->data.pair.car->type==SCM_SYMBOL)
	{
        var=find_var(env,buff->data.pair.car);
        if (var!=nil)
        {/*a symbol as been found*/
            if(var->data.pair.cdr->type==SCM_PRIMITIVE)
            {/*Symbol of a primitive*/
                if(var->data.pair.cdr->data.primitive==CAR||var->data.pair.cdr->data.primitive==CDR){buff=eval(buff->data.pair.cdr,env);}/*(CAR (a0 a1 ...an))-->(CAR (eval (a0  a1 ...an)*/
                else{buff=eval_args(buff->data.pair.cdr,env);}/* so don't forget to quote the expression otherwise the interperter will try to evaluate the args expression*/
                buff=(*(var->data.pair.cdr->data.primitive))(buff);
                return buff;
            }
            else if(var->data.pair.cdr->type==SCM_FORM)
            {/*Symbol of a form*/
                buff=(*(var->data.pair.cdr->data.form))(buff->data.pair.cdr,env);/*(form(car) args(cdr))*/
                if(var->data.pair.cdr->data.form==IF || var->data.pair.cdr->data.form==LET||var->data.pair.cdr->data.form==LETX){goto new_eval;}
                return buff;
            }
            else if (var->data.pair.cdr->type==SCM_COMPOUND)
            {/*Symbol of a compound (user function)*/
                object new_buff=make_pair(nil,nil);
                new_buff->data.pair.car=var->data.pair.cdr; /* On ne passe pas par un make_pair afin de ne pas faire des copies d'objet, sinon on ne pourra pas modifier les environnements des fermetures.*/
                new_buff->data.pair.cdr=buff->data.pair.cdr;
                return eval(new_buff,env);
            }
			else if(isGlobalcarcdr(buff->data.pair.car))
			{/* for all derivate car and cdr primitives: caaaaar cdadar cddddr caar cadr... without creating new ones  */
			    string f=buff->data.pair.car->data.symbol;
                buff=eval(buff->data.pair.cdr,env);
                return GLOBALCARCDR(f,buff);
            }
			else
            {/*symbol that represent simple variables*/
                if(buff->data.pair.cdr->type!=SCM_NIL && buff->data.pair.car->type!=SCM_PRIMITIVE ) {WARNING_MSG("Car is not a primitive");return error;}
                buff->data.pair.car=var->data.pair.cdr;
                if(buff->data.pair.cdr->type!=SCM_NIL){buff->data.pair.cdr=eval(buff->data.pair.cdr,env);return buff;}
                else{return buff->data.pair.car;} /*on retourne sa valeur*/
            }
		}
		else {WARNING_MSG("%s is not declared in this environment use define to declare it",buff->data.pair.car->data.symbol); return error;}/*on a trouvé aucun symboles correspondant*/
	}
	else if (buff->data.pair.car->type==SCM_COMPOUND)
	{
        object vals;
        vals=eval_args(buff->data.pair.cdr,env);/*(coumpound(car) args(cdr))*/
        object parms = buff->data.pair.car->data.compound.parms;
        define_map(buff->data.pair.car->data.compound.env,parms,vals);
        object* new_env=buff->data.pair.car->data.compound.env;
        buff=buff->data.pair.car->data.compound.body;
        while(buff!=nil)/*like a intern begin inside compound structures*//*eval each instruction and return the last one body=(instr1)(instr2)*/
        {
            if(buff->data.pair.cdr!=nil)
            {
                eval(buff->data.pair.car,new_env);
                buff=buff->data.pair.cdr;
            }
            else{return eval(buff->data.pair.car,new_env);}
        }
    }
	else if (buff->data.pair.car->type==SCM_PAIR){buff->data.pair.car=eval(buff->data.pair.car,env);return eval(buff,env);}
    else if(buff->data.pair.cdr->type!=SCM_NIL && buff->data.pair.car->type!=SCM_PRIMITIVE){WARNING_MSG("Car is not a primitive");return error;}
	else if(buff->data.pair.car==true){return true;}
	else if (buff->data.pair.car==false){return false;}
	return buff;
}
