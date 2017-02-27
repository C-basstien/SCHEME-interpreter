#include <stdio.h>
#include <ctype.h>
#include "read.h"
#include <limits.h>
#include "mem.h"

object read_atom(char* input, uint* pos)
{
	int i0=*pos;
	int l=strlen(input);
	if(input[*pos]=='"')
	{/*if it's a string*/
		(*pos)++;
		while(in_a_string(input,pos,l)) {(*pos)++;}
		(*pos)++;
		char* atom = malloc(sizeof(atom)*(*pos-i0-1));
		int j; for(j=i0+1; j<*pos-1; j++) {atom[j-i0-1]=input[j];}
		atom[(*pos)-i0-2]='\0';
		find_special_special_string(atom);
		return make_string(atom);
	}
	else
	{
		while(((input[*pos]!=' ')&&(input[*pos]!='\t') &&(input[*pos]!='(')&&(input[*pos]!='"')) && *pos<l)
		{
			if (((*pos)+2<l)&&(input[*pos]=='#')&&(input[(*pos)+1]=='\\')&&((input[(*pos)+2]=='(')||(input[(*pos)+2]=='"'))) {*pos+=3;} /*si c'est un char #\( ou #\"on incrémente de 3*/
			else(*pos)++;
		}/*isolating the first atom in the input"*/
	}

	char* atom = malloc(sizeof(atom)*(*pos-i0+1));
	int j; for(j=i0; j<*pos; j++) {atom[j-i0]=input[j];}
	atom[(*pos)-i0]='\0';
	if (!(strcmp (atom,"nan"))) {num nbre; nbre.numtype=NUM_UNDEF; return make_number(nbre);}
	if(atom[0]=='+'|| atom[0]=='-'||isDigit(atom[0])|| isComplex(atom))
	{
	     if (!strcmp(atom,"+")) {return make_symbol("+");}
	     else if(!strcmp(atom,"-")) {return make_symbol("-");}
	     return conv_string_num (atom);
    }
	else if(atom[0]=='#')
	{
		if(atom[1]=='t')
		{
			if(atom[2]=='\0') {return true;}
			WARNING_MSG("Invalid boolean"); return error;
		}
		else if(atom[1]=='f')
		{
			if(atom[2]=='\0') {return false;}
			WARNING_MSG("Invalid boolean"); return error;
		}
		else if(atom[1]=='\\')
		{
			if (!(strcmp (atom,"#\\space"))) { return make_character(' ');}
			if (!(strcmp (atom,"#\\newline"))) {return make_character('\n');}
			if(atom[3]=='\0') {return make_character(atom[2]);}
			WARNING_MSG("Invalid char"); return error;
		}
		else {WARNING_MSG("Invalid boolean"); return error;}
	}
	else{return make_symbol(atom);}
	return error;
}

object read_pair(char* input, uint* pos)
{/* Attention, la liste en entrée comporte une parenthèse de début et une parenhèse de fin*/
	int difNbParenthesis = 1; int i0=(*pos)+1;
	uint posList=0;
	while(difNbParenthesis >0)
	{
		(*pos)++;
		switch (input[*pos])
		{
		case '(':difNbParenthesis++; break;
		case ')':difNbParenthesis--; break;
		}
	}
	(*pos)++;
	char* list = malloc(sizeof(list)*(*pos-i0));
	int j; for(j=i0; j<*pos-1; j++) {list[j-i0]=input[j];}
	list[*pos-i0-1]='\0';
	return read(list, &posList);
}

object read(char* input, uint* pos)
{
	object tree,car,cdr;
	uint l = strlen(input);
	simplifie_chaine(input,pos,l);/*On élimine les espaces et les tabulations.*/
	if(*pos<l)
	{
	    if((input[*pos]=='\''&&((*pos)<l)))
		{/*it's a quote*/
		    car=make_symbol("'");(*pos)++;cdr=read(input, pos);
		    if((car==error)||(cdr==error)) {return error;}
		    tree=make_pair(car,cdr);return tree;
        }
		if((input[*pos]!='('))
		{/*it's an atome */
			car=read_atom(input, pos); cdr=read(input, pos);
			if((car==error)||(cdr==error)) {return error;}
			tree=make_pair(car,cdr);
			return tree;
		}
		else if((input[*pos+1]==')')&&((*pos)<l))
		{/*it's nil (emppty list)*/
			car=nil; (*pos)+=2; cdr=read(input, pos);
			if((car==error)||(cdr==error)) {return error;}
			tree=make_pair(car,cdr);
			return tree;
		}

		else /*Si c'est une liste, on va l'extraire de l'entrée input en comptant les parenthèses...*/
		{/*it's a list*/
			car=read_pair(input, pos);
			cdr=read(input, pos);
			if((car==error)||(cdr==error)) {return error;}
			tree=make_pair(car,cdr);
			return tree;
		}
	}
	else {return nil;}/*end of the input*/
}


