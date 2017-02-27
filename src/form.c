#include "form.h"


object DEFINE(object args,object* env)
{
    /***On se contente de définir des variables pour l'instant, on pourra déclarer des fonctions avec cette forme plus tard ***/
	object buff=args;
	object sym,val;
    if(buff==nil) {WARNING_MSG("No defined variable"); return error;}
	else if (buff->data.pair.car->type!=SCM_SYMBOL&&buff->data.pair.car->type!=SCM_PAIR){WARNING_MSG("Error: expression after define is not a symbol or a function"); return error;}
	/***/
	sym=buff->data.pair.car;
	if(sym->type==SCM_PAIR)
	{
	    sym=sym->data.pair.car;/*eval(sym->data.pair.car, env);*/
        if (find_var(env,sym)==nil)
        {
          add_var(env,sym,make_compound(buff->data.pair.car->data.pair.cdr,buff->data.pair.cdr,create_env(env,HSIZE)));
          return sym;
        }
    }
	if (find_var(env,sym)==nil)
	{
		val=eval(buff->data.pair.cdr->data.pair.car,env);
		if(val==nil) {WARNING_MSG("No value assigned to %s so default value is nil",buff->data.pair.car->data.symbol);}
		add_var(env,sym,val);
		return sym;
	}
	else {WARNING_MSG("%s is already defined in this environement use setn to modify it",sym->data.symbol); return error;}
}
object SET(object args,object* env)
{
    object buff=args;
    object sym,val,var;
    if(buff==nil) {WARNING_MSG("No defined variable"); return error;}
	else if (buff->data.pair.car->type!=SCM_SYMBOL) {WARNING_MSG("Error: expression after set! is not a symbol"); return error;}
	sym=buff->data.pair.car;
	var=find_var(env,sym);
	if(var!=nil)
	{

		val=eval(buff->data.pair.cdr->data.pair.car,env);
		if(val==nil) {WARNING_MSG("No value assigned to %s so default value is nil",buff->data.pair.car->data.symbol);}
		modify_var_value(var,val);
		return sym;
	}
	else {WARNING_MSG("%s is not declared in this environement use define to declare it",sym->data.symbol); return error;}
}
object IF(object args, object* env)
{
    object buff=args;/* (if (cond) (run this intruction if cond true) (otherwise run this))*/
    object temp=eval(buff->data.pair.car,env);
    if(temp!=false && temp!=error){buff=buff->data.pair.cdr->data.pair.car;}
    else{buff=buff->data.pair.cdr->data.pair.cdr->data.pair.car;}
    return buff;
}
object AND(object args,object* env)
{
	object buff=args;
	object var;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	if(buff==false) {return false;}
	while(buff!=nil)
	{
		if((buff->data.pair.car->type!=SCM_SYMBOL)&&(buff->data.pair.car->type!=SCM_PAIR))
		{
			if(buff->data.pair.car==false) {return false;}
		}
		else if(buff->data.pair.car->type==SCM_SYMBOL)
		{
			var=find_var(env,buff->data.pair.car);
			if(var!=nil)
			{
				if(var->data.pair.cdr==false) {return false;}
			}
			else {WARNING_MSG("%s is not declared in this environement use define to declare it",buff->data.pair.car->data.symbol); return error;}
		}
		else if (buff->data.pair.car->type==SCM_PAIR)
		{
			object res_eval=eval(buff->data.pair.car,env);
			if(res_eval==error) {return error;}
			else if(res_eval==false) {return false;}
		}
		buff=buff->data.pair.cdr;
	}
	return true;
}
object OR(object args, object* env)
{
    object buff=args;
	object var;
	if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
	if(buff==true) {return true;}
	while(buff!=nil)
	{
		if((buff->data.pair.car->type!=SCM_SYMBOL)&&(buff->data.pair.car->type!=SCM_PAIR))
		{
			if(buff->data.pair.car!=false) {return true;}
		}
		else if(buff->data.pair.car->type==SCM_SYMBOL)
		{
			var=find_var(env,buff->data.pair.car);
			if(var!=nil)
			{
				if(var->data.pair.cdr!=false) {return true;}
			}
			else {WARNING_MSG("%s is not declared in data environement use define to declare it",buff->data.pair.car->data.symbol); return error;}
		}
		else if (buff->data.pair.car->type==SCM_PAIR)
		{
			object res_eval=eval(buff->data.pair.car,env);
			if(res_eval==error) {return error;}
			else if(res_eval!=false) {return true;}
		}
		buff=buff->data.pair.cdr;
	}
	return false;
}
/************************************************************************************************************************/
object QUOTE(object args, object* env)
{
    return args->data.pair.car;
}
object BEGIN(object args, object* env)
{
    object buff=args;
    while(buff->data.pair.cdr!=nil)
    {
        if(buff->data.pair.cdr!=nil){eval(buff->data.pair.car,env );}
        buff=buff->data.pair.cdr;
    }
    return eval(buff->data.pair.car,env);
}
object LAMBDA(object args, object* env)
{
    object buff=args;
    return make_compound(buff->data.pair.car,buff->data.pair.cdr,create_env(env,HSIZE));
}
object LET(object args, object* env)
{
    /*** (let ((parameter1 value1)... (parametern valuen)) body)
                                <=>
    ((lambda (parameter1... parametern) body) value1...valuen )***/
    object buff=args;
    if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
    object Lpara;
    object Lval;
    object expr=buff->data.pair.cdr;
    buff=buff->data.pair.car;
    read_var_let(buff,&Lpara,&Lval);
    return make_pair(make_compound(Lpara,expr,create_env(env,HSIZE)),Lval);
}
object LETX(object args, object* env)
{
    /*** (let* ((parameter1 value1)... (parametern valuen)) body)
                                <=>
    ((lambda( parameter1 )((...((lambda(parametern) body ) valuen)...)) value1)***/

    /*value gives to parameter can depend of previous parmetter declared inside the let arguments
     (let* ((x 10) (y (* x 2))) (+ x y))=>30
     (let ((x 10) (y (* x 2))) (+ x y))=>error x not defined in(y (*x 2))*/
    object buff=args;
    if(buff==nil) {WARNING_MSG("No operand after operator"); return error;}
    object Lpara;
    object Lval;
    object expr=buff->data.pair.cdr;
    buff=buff->data.pair.car;
    read_var_let(buff,&Lpara,&Lval);
    return make_letx (expr,Lpara,Lval,create_env(env,HSIZE));
}

object MAP(object args, object* env)
{
    /*** (map f (x0.0 ... x0.n) ... (xk.0 ... xk.n))
                                <=>
    (list (f x0.0 ... xk.0) ... (f x0.n ... xk.n))***/
    if(args==nil || args==error){return error;}
    else if(args->type!=SCM_PAIR) {WARNING_MSG("Operand is not a pair"); return error;}
    object buff=args;
    object function=buff->data.pair.car;
    int i,n,s;
    object Leval=eval(make_pair(make_symbol("list"),buff->data.pair.cdr),env);
    object size=LENGTH(make_pair(CAR(Leval),nil));
    n=size->data.number.val.integer;
    buff=Leval;if(buff->type!=SCM_PAIR){return error;}
    object lbuff=make_pair(nil,nil);object lres=make_pair(nil,nil);
    while(buff!=nil)/*évalue chaque liste et vérifie  que toutes les listes ont la meme longeur*/
    {
        size=LENGTH(make_pair(CAR(buff),nil));s=size->data.number.val.integer;
        if(n!=s){WARNING_MSG("Error: mapping of list with different size "); return error;}
        buff=buff->data.pair.cdr;
    }
    for(i=0;i<n;i++)
    {
        read_val_map(Leval,&lbuff,i);
        make_link(&lres,eval(make_pair(function,lbuff),env));
    }
    return lres->data.pair.cdr;
}
object SHOW(object args, object* env)
{
    print_env(env);
    return nil;
}
/** read and construction functions for list structures**/
void read_var_let (object paraval,object* Lpara,object* Lval)
{
    *Lpara=make_pair(CAR(CAR(paraval)),nil);
    *Lval=make_pair(CAR(CDR(CAR(paraval))),nil);
    if(paraval->data.pair.cdr!=nil){read_var_let(paraval->data.pair.cdr,&((*Lpara)->data.pair.cdr),&((*Lval)->data.pair.cdr));}
}
void read_val_map(object L,object* Lval,int n)
{
    object temp=L->data.pair.car;
    int i;for (i=0;i<n;i++){temp=CDR(temp);}
    *Lval=make_pair(CAR(temp),nil);
    if(L->data.pair.cdr!=nil){read_val_map(L->data.pair.cdr, &((*Lval)->data.pair.cdr),n);}
}
void make_link(object* L,object val)
{
    if ((*L)->data.pair.cdr!=nil){make_link(&((*L)->data.pair.cdr),val);}
    else {(*L)->data.pair.cdr=make_pair(val,nil);}
}
object make_letx (object body,object Lpara,object Lval, object* env)
{
    object bd,para,val;bd=body;para=make_pair(CAR(Lpara),nil);val=make_pair(CAR(Lval),nil);
    if(Lpara->data.pair.cdr!=nil && Lval->data.pair.cdr!=nil){bd=make_pair(make_letx(body,Lpara->data.pair.cdr,Lval->data.pair.cdr,env),nil);return make_pair(make_compound(para,bd,env),val);}
    else{return make_pair(make_compound(para,body,env),val); }
}
