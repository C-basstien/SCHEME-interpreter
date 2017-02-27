#include "environment.h"

/**
    scheme environment structure:
                                 -a scheme environment contain variables represented by a symbol and a value  that can contain all type of object
                                 -when a function is declared, a new environment is created with all the local parameters used
                                 -if functions are declared indempdently (no function inside function), there environment are independent
                                 -declare a function inside a function is possible (that's create new environment inside the current environment)
                                 -start adress is fixed when the environment is created, it's can't change after
                                 -end adress is fixed when the environment is created it's take the value of start adress of the environment
                                 the function that has been created, it's can't change after
                                 -each elements are added in a stack after start adress, so obj1 here is the last elements added to the env
                                 -when a function is called it's look first in his environment if it's not finding a variable,
                                 it will look in the environment upper
                                _________________________________________________________________________
                                |                                                                        |
                                ▽                                                                        |
    level 0:(main env)          start_adr00->obj1->...->obji->...->objn->NULL (end_adr00)                |
                                                    |     |                                              |
                                                    ▽     ▽                                              |
    level 1 (function envs)                       |....|  start_adr1i->obj1->...->objh->...->objl->start_adr00 (end_adr1i)
                                                                                |
                                                                                ▽
    level 2 (function inside function envs)                                     start_adr2h->obj1->...->objz->...->objy->start_adr2h(end_adr2h)
    .
    level k   (k-composition of inside function)
    .
    .
    level m   (m-composition of inside function)

                                -in order too get a faster i implement this structure in hash table
                                -the size of the hash table is fixed to 101 but it's calcuate modulo 100
                                -the reason of this is because we kept the last adress of the table for saving the end adress (or return adress)
                                /0->obj->...->
                                          |
                                          |
                                .         |---->/0


                                                /100start_adress0
                                .
                                .
                                .->...>
                                .
                                /99->...->
                                /100->end_adress
                                **/
unsigned int hash (char* str,unsigned int mod)
{
    const int a=31;
    unsigned int h=0;
    int i=strlen(str)-1;
    while(i>=0)
	{
        h=h*a+str[i];
        i--;
    }
    h=h%mod;
    return h;
}
/*constructor and destructor of environment*/
object* create_env(void* end_adr,unsigned int size)
{
    object *env=calloc(size,sizeof(object));
    unsigned int i;
    for(i=0;i<size-1;i++){env[i]=nil;}
    env[size-1]=make_address(end_adr);
    return env;
}
void kill_env(object* env)
{

}
/*add,find,set,remove functions for variables*/
void add_var(object* env,object sym,object val)
{
    unsigned int i=hash(sym->data.symbol,HSIZE-1);
    object var=make_pair(sym,val);
    env[i]=make_pair(var,env[i]);
}
object find_var(object* env,object sym)
{
    object buff;
    object* curr_env=env;
    unsigned int i;
    while(curr_env!=NULL)
    {
        i=hash(sym->data.symbol,HSIZE-1);
        buff=curr_env[i];
        while(buff->type==SCM_PAIR&&buff->data.pair.car->type==SCM_PAIR)
        {
            if(!strcmp(buff->data.pair.car->data.pair.car->data.symbol,sym->data.symbol)){return buff->data.pair.car;}
            buff=buff->data.pair.cdr;
        }
        curr_env=curr_env[HSIZE-1]->data.address;
    }
    return nil;
}
void modify_var_value (object var,object val)
{
	kill_object (var->data.pair.cdr);
	var->data.pair.cdr=copy_object(val);
}
void define_map(object* env,object sym, object val)
{/*Update environment with a new list of values and symbols define by the compound*/
    if(sym==nil && val==nil){}
    else if((sym==nil && val!=nil) || (sym!=nil && val==nil))
    {
        WARNING_MSG("There is not the same number of parameters and arguments");
        return(error);
    }
    else if(sym->type!=SCM_PAIR || val->type!=SCM_PAIR)
    {
        WARNING_MSG("Either parameter or argument is not a pair");
        return(error);
    }
    else
    {
        define_map(env,sym->data.pair.cdr, val->data.pair.cdr);
        add_var(env,sym->data.pair.car,val->data.pair.car);
    }

}

/*print tools for debugging environment*/
void print_env(object* env)
{
    int i;
    for(i=0;i<HSIZE;i++){/*printf("[%d]:",i);*/print_cell(env[i]);/*printf("\n");*/}printf("\n");
}
void print_cell(object cenv)
{
    object buff=cenv;
	/*printf("{");*/
	while (buff!=nil&&buff->type!=SCM_ADDRESS)
	{
	    if(buff->type==SCM_PAIR)
	    {
            print_var(buff->data.pair.car);
            printf(" ");
            buff=buff->data.pair.cdr;
	    }
	    else {print_atom(buff);}
	}
    if(buff->type==SCM_ADDRESS){print_atom(buff);}
	/*printf("}");*/
}
void print_var(object var)
{
    print_atom(var->data.pair.car);printf(":");
	if (var->data.pair.cdr->type!=SCM_PAIR) {print_atom(var->data.pair.cdr);}
	else {print(var->data.pair.cdr);}
}
