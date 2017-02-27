#include <stdio.h>
#include <ctype.h>
#include "read_utility.h"
#include <limits.h>
#include "mem.h"

int isDigit(char c)
{
	if((c>='0')&&(c<='9')) {return 1;}
	else {return 0;}
}
int isComplex (char* in)
{

	int l=strlen(in);if (!(strcmp (in,"i"))){return 1;}
	int c; int i=0; int opp=0 ; int opp_flag=0; /*variable pour compter le nombre de + ou - et d'unité imaginaire*/
	for(c=0; c<l; c++)
	{
		if (in[c]=='i')
		{
			if((c>0 && !(isDigit(in[c-1])) && in[c-1]!='+'&& in[c-1]!='-')){return 0;}
            if( c+1<l && in[c+1]!='+'&& in[c+1]!='-' && in[c+1]!='\0') {return 0;}
			i++;
		}
		else if (in[c]=='+'||in[c]=='-') {opp++; opp_flag++;}
		else {opp_flag=0;}
		if(i>1 ||opp>2||opp_flag==2) {return 0;}/*deux signe + - se suivent ->pas valide ou trops de i ou signe*/

	}
	if(i==1) {return 1;}
	else {return 0;}
}
int isGlobalcarcdr(object osym)
{
	if(osym->type!=SCM_SYMBOL){return 0;}
	string sym=osym->data.symbol;
	if(sym[0]=='c' && sym[strlen(sym)-1]=='r')
	{
	    int i;
	    for(i=1;i<strlen(sym)-1;i++){if(sym[i]!='a' && sym[i]!='d'){return 0;}}
	    return 1;
	}
    return 0;
}
object conv_string_num (char* atom)
{
        int num_type;
        num nbre; char* ptr;
		if (!(strcmp (atom,"+inf"))) {nbre.numtype=NUM_PINFTY; return make_number(nbre);}
		else if (!(strcmp (atom,"-inf"))) {nbre.numtype=NUM_MINFTY; return make_number(nbre);}
		else if (!(strcmp (atom,"nan"))) {nbre.numtype=NUM_UNDEF; return make_number(nbre);}
		if(strlen(atom)>1)
		{
			int i=1; int k=0; /*compte le nombre de virgule*/
			if(isComplex(atom)) {num_type=NUM_COMPLEX;}
			else
			{
				for (i=1; i<strlen(atom); i++)
				{
					if(!isDigit(atom[i]) && atom[i]!='.') {return make_symbol(atom);}

					else if(atom[i]=='.')
					{
						num_type=NUM_REAL; k++;
						if(k>1) {WARNING_MSG("Invalid number too many '.'"); return error;}
					}
					else if(!k) {num_type=NUM_INTEGER;}
				}
			}
		}
		else if(atom[0]=='i'){num_type=NUM_COMPLEX;}
		else {num_type=NUM_INTEGER;}

		if (num_type==NUM_INTEGER)
		{
			if (strtol(atom, &ptr, 10)>INT_MAX)
			{
				nbre.numtype=NUM_PINFTY;
				return make_number(nbre);
			}
			if (strtol(atom, &ptr, 10)<INT_MIN)
			{
				nbre.numtype=NUM_MINFTY;
				return make_number(nbre);
			}
			nbre.numtype=NUM_INTEGER;
			nbre.val.integer=(int) strtol(atom, &ptr, 10);
			return make_number(nbre);
		}
		else if (num_type==NUM_REAL)
		{
			if (strtod(atom, &ptr)>INT_MAX)
			{
				nbre.numtype=NUM_PINFTY;
				return make_number(nbre);
			}
			if (strtod(atom, &ptr)<INT_MIN)
			{
				nbre.numtype=NUM_MINFTY;
				return make_number(nbre);
			}
			nbre.numtype=NUM_REAL;
			nbre.val.real=strtod(atom, &ptr);
			return make_number(nbre);
		}
		else if(num_type==NUM_COMPLEX)
		{

			string buff1=calloc(strlen(atom),sizeof(char));

			int i=1; int j=0;
			int part_i_is_find=0;

			buff1[0]=atom[0];
			if(atom[0]=='i') {buff1[0]='1'; buff1[1]='\0'; part_i_is_find=1;i=1;}
			else if((atom[0]=='-')&&(atom[1]=='i')) {buff1[0]='-'; buff1[1]='1';buff1[2]='\0'; part_i_is_find=1;i=2;}
			else if((atom[0]=='+')&&(atom[1]=='i')) {buff1[0]='1'; buff1[1]='\0'; part_i_is_find=1;i=2;}
			else
			{
				while((i<strlen(atom))&&(atom[i]!='+'&& atom[i]!='-'))
				{
					buff1[i]=atom[i];
					if(atom[i]=='i')  {part_i_is_find=1;}
					i++;
				}
				buff1[i+1]='\0';
			}
			string buff2=calloc(strlen(atom)-i,sizeof(char));
			if (part_i_is_find==0)
			{
                if((atom[i]=='-')&&(atom[i+1]=='i')) {buff2[0]='-'; buff2[1]='1';buff2[2]='\0';  part_i_is_find=2;j=1;}
                else if((atom[i]=='+')&&(atom[i+1]=='i')) {buff2[0]='1'; buff2[1]='\0'; part_i_is_find=2;j=1;}
			}
			if (!j)
			{
                for(j=0; j<strlen(atom)-i; j++)
                {
                    buff2[j]=atom[i+j];
                    if(atom[i+j]=='i'){part_i_is_find=2;}
                }
			}
			nbre.numtype=NUM_COMPLEX;
			if(part_i_is_find==2)
			{
				nbre.val.complex.RE=strtod(buff1, &ptr);
				nbre.val.complex.IM=strtod(buff2, &ptr);
				return make_number(nbre);
			}
			else
			{
				nbre.val.complex.RE=strtod(buff2, &ptr);
				nbre.val.complex.IM=strtod(buff1, &ptr);
				return make_number(nbre);
			}
		}
        return error;
}
string conv_num_string(num numb)
{
	string str=calloc(STRLEN,sizeof(char));
	if(numb.numtype==NUM_INTEGER)
	{
		sprintf(str,"%d",numb.val.integer);
	}
	else if(numb.numtype==NUM_REAL)
	{
		sprintf(str,"%lf",numb.val.real);
	}
	else if(numb.numtype==NUM_COMPLEX)
	{
		if(numb.val.complex.IM<0) {sprintf(str,"%lf%lfi",numb.val.complex.RE,numb.val.complex.IM);}
		sprintf(str,"%lf+%lfi",numb.val.complex.RE,numb.val.complex.IM);
	}
	else if(numb.numtype==NUM_PINFTY)
	{
		sprintf(str,"+inf");
	}
	else if(numb.numtype==NUM_MINFTY)
	{
		sprintf(str,"-inf");
	}
	else if(numb.numtype==NUM_UNDEF)
	{
		sprintf(str,"NaN");
	}
	return str;
}
void simplifie_chaine(char* input,uint *pos,int l)
{
	while(((input[*pos]==' ')||(input[*pos]=='\t'))&&(*pos)<l) {(*pos)++;}
}
int in_a_string(char* input,uint *pos,int l)
{
	if(((*pos)>0)&&(input[(*pos)-1]=='\\')&&(input[*pos]=='"' )&& *pos<l) {return 1;}
	else if (input[*pos]!='"' && *pos<l) {return 1;}
	return 0;
}
void find_special_special_string (string str )/*pour le cas ou on un \" dans un string*/
{
	int i,j;
	for(i=0; i<strlen(str); i++)
	{
		if(str[i]=='\\')
		{
			if(str[i+1]=='"')
			{
				for(j=i; j<strlen(str)-1; j++) {str[j]=str[j+1];}
				str[j]='\0';
			}
		}
	}

}
