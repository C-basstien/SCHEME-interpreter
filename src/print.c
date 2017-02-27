#include "mem.h"

#include "print.h"
#include "environment.h"
#include <stdio.h>

void print_atom( object o )
{

    if (o->type==SCM_NUMBER)
    {
        if (o->data.number.numtype==NUM_REAL)
        {
            printf( "%lf",o->data.number.val.real );
        }
        else if (o->data.number.numtype==NUM_INTEGER)
        {
            printf( "%d",o->data.number.val.integer );
        }
        else if (o->data.number.numtype==NUM_UINTEGER)
        {
            printf( "%u",o->data.number.val.uinteger );
        }

        else if (o->data.number.numtype==NUM_COMPLEX)
        {
            if (o->data.number.val.complex.IM>=0)
            {
                printf( "%lf+%lfi",o->data.number.val.complex.RE,o->data.number.val.complex.IM);
            }
            else
            {
                printf( "%lf%lfi",o->data.number.val.complex.RE,o->data.number.val.complex.IM);
            }
        }

        else if (o->data.number.numtype==NUM_UNDEF)
        {
            printf( "error undef number");
        }

        else if (o->data.number.numtype==NUM_PINFTY)
        {
            printf( "+inf");
        }

        else if (o->data.number.numtype==NUM_MINFTY)
        {
            printf( "-inf");
        }
    }
    else if (o->type==SCM_CHARACTER)
    {
        if(o->data.character=='\n'){printf("#\\newline");}
        else if(o->data.character==' '){printf("#\\space");}
        else{printf("#\\%c",o->data.character );}
    }
    else if (o->type==SCM_STRING)
    {
        printf( "\"%s\"",o->data.string );
    }
    else if (o->type==SCM_NIL)
    {
        printf("()");
    }
    else if (o->type==SCM_BOOLEAN )
    {
        if (o->data.number.val.integer==0){printf("#f");}
        else {printf("#t");}
    }
    else if (o->type==SCM_SYMBOL )
    {
        printf("%s",o->data.symbol);
    }
    else if (o->type==SCM_FORM)
    {
        printf("form");
    }
    else if (o->type==SCM_PRIMITIVE)
    {
        printf("primitive");
    }
    else if (o->type==SCM_COMPOUND)
    {
        printf("corps:");print(o->data.compound.body);
        printf(",paramètres:");print(o->data.compound.parms);
        printf(",environemnts:");print_env(o->data.compound.env);

    }
    else if (o->type==SCM_ADDRESS)
    {
        printf("address");
    }
    return;
}

void print_pair( object o )
{

    print(o->data.pair.car);
    if (o->data.pair.cdr->type!=SCM_NIL)/*on a fini de lire notre paire donc pas besoin d'afficher la liste vide dans ce cas*/
    {
        /*on appelle directement SCM_print_pair ,car un cdr est toujours une paire dans ces conditions*/
        printf(" ");
        if (o->data.pair.cdr->type==SCM_PAIR){print_pair(o->data.pair.cdr);}
        else{print_atom(o->data.pair.cdr);}
    }
    return;
}

void print( object o )
{
    if ( SCM_PAIR == o->type ){printf("(");print_pair( o );printf(")");}
    else {print_atom( o );}
    return;
}
