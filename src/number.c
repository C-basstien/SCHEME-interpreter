#include "number.h"


int compare_sup_num(num a,num b)/*a>b*/
{
	if (a.numtype==NUM_COMPLEX||b.numtype==NUM_COMPLEX|| a.numtype==NUM_UNDEF||b.numtype==NUM_UNDEF) {return -1;}
	else if (a.numtype==NUM_MINFTY) {return 0;}
	else if (b.numtype==NUM_PINFTY) {return 0;}
	else if (a.numtype==NUM_PINFTY) {return 1;}
	else
	{
		if (a.numtype==NUM_REAL)/*soit c'est un réel soit un entier*/
		{
			if (b.numtype==NUM_REAL)
			{
				if (a.val.real>b.val.real) {return 1;}
				else {return 0;}
			}
			else
			{
				if (a.val.real>b.val.integer) {return 1;}
				else {return 0;}
			}
		}
		else
		{
			if (b.numtype==NUM_REAL)
			{
				if (a.val.integer>b.val.real) {return 1;}
				else {return 0;}
			}
			else
			{
				if (a.val.integer>b.val.integer) {return 1;}
				else {return 0;}
			}
		}
	}
}
int compare_inf_num(num a,num b)/*a<b*/
{
	if (a.numtype==NUM_COMPLEX||b.numtype==NUM_COMPLEX|| a.numtype==NUM_UNDEF||b.numtype==NUM_UNDEF) {return -1;}
	else if (a.numtype==NUM_PINFTY) {return 0;}
	else if (b.numtype==NUM_MINFTY) {return 0;}
	else if (a.numtype==NUM_MINFTY) {return 1;}
	else
	{
		if (a.numtype==NUM_REAL)/*soit c'est un réel soit un entier*/
		{
			if (b.numtype==NUM_REAL)
			{
				if (a.val.real<b.val.real) {return 1;}
				else {return 0;}
			}
			else
			{
				if (a.val.real<b.val.integer) {return 1;}
				else {return 0;}
			}
		}
		else
		{
			if (b.numtype==NUM_REAL)
			{
				if (a.val.integer<b.val.real) {return 1;}
				else {return 0;}
			}
			else
			{
				if (a.val.integer<b.val.integer) {return 1;}
				else {return 0;}
			}
		}
	}
}
int equal_num(num a,num b)/*a==b*/
{
	if (a.numtype==NUM_COMPLEX)
	{
		if (b.numtype==NUM_COMPLEX) {if(a.val.complex.RE==b.val.complex.RE && a.val.complex.IM==b.val.complex.IM) {return 1;} return 0;}
		if(a.val.complex.IM==0)
		{
			if(b.numtype==NUM_REAL) {if(a.val.complex.RE==b.val.real) {return 1;} return 0;}
			else {if(a.val.complex.RE==(double)b.val.integer) {return 1;} return 0;}
		}
		return 0;
	}
	else if (a.numtype==NUM_REAL)
	{
		if (b.numtype==NUM_COMPLEX)
		{
			if(b.val.complex.IM==0) {if(a.val.real==b.val.complex.RE) {return 1;} return 0;}
			return 0;
		}
		else if (b.numtype==NUM_REAL) {if(a.val.real==b.val.real) {return 1;} return 0;}
		else {if(a.val.real==(double)b.val.integer) {return 1;} return 0;}
	}
	else
	{
		if (b.numtype==NUM_COMPLEX)
		{
			if(b.val.complex.IM==0) {if((double)a.val.integer==b.val.complex.RE) {return 1;} return 0;}
			return 0;
		}
		else if (b.numtype==NUM_REAL) {if((double)a.val.integer==b.val.real) {return 1;} return 0;}
		else {if(a.val.integer==b.val.integer) {return 1;} return 0;}
	}
}
num add_num(num a,num b)/*a+b*/
{
	num res;
	if (a.numtype==NUM_UNDEF||b.numtype==NUM_UNDEF) {res.numtype=NUM_UNDEF; return res;}
	else if (a.numtype==NUM_PINFTY)
	{
		if (b.numtype!=NUM_MINFTY) {return a;}
		else {res.numtype=NUM_UNDEF; return res;}
	}
	else if (a.numtype==NUM_MINFTY)
	{
		if (b.numtype!=NUM_PINFTY) {return a;}
		else {res.numtype=NUM_UNDEF; return res;}
	}
	else if (b.numtype==NUM_PINFTY)
	{
		if (a.numtype!=NUM_MINFTY) {return b;}
		else {res.numtype=NUM_UNDEF; return res;}
	}
	else if (b.numtype==NUM_MINFTY)
	{
		if (a.numtype!=NUM_PINFTY) {return b;}
		else {res.numtype=NUM_UNDEF; return res;}
	}
	else
	{
		if (a.numtype==NUM_REAL)
		{
			if (b.numtype==NUM_REAL)
			{
				res.numtype=NUM_REAL;
				res.val.real=a.val.real+b.val.real;
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.numtype=NUM_REAL;
				res.val.real=a.val.real+b.val.integer;
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.real+b.val.complex.RE;
				res.val.complex.IM=b.val.complex.IM;
				return res;
			}
		}
		else if (a.numtype==NUM_INTEGER)
		{
			if (b.numtype==NUM_REAL)
			{
				res.numtype=NUM_REAL;
				res.val.real=a.val.integer+b.val.real;
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.numtype=NUM_INTEGER;
				res.val.integer=a.val.integer+b.val.integer;
				if(res.val.integer>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.integer<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.integer+b.val.complex.RE;
				res.val.complex.IM=b.val.complex.IM;
				return res;
			}
		}
		else if (a.numtype==NUM_COMPLEX)
		{
			res.numtype=NUM_COMPLEX;
			if (b.numtype==NUM_REAL)
			{
				res.val.complex.RE=a.val.complex.RE+b.val.real;
				res.val.complex.IM=a.val.complex.IM;
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.val.complex.RE=a.val.complex.RE+b.val.integer;
				res.val.complex.IM=a.val.complex.IM;
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.complex.RE+b.val.complex.RE;
				res.val.complex.IM=a.val.complex.IM+b.val.complex.IM;
				return res;
			}
		}
	}
	return res;
}
num sub_num(num a,num b)/*a-b*/
{
	num res;
	if (a.numtype==NUM_UNDEF||b.numtype==NUM_UNDEF) {return a;}
	else if (a.numtype==NUM_PINFTY)
	{
		if (b.numtype!=NUM_PINFTY) {return a;}
		else {res.numtype=NUM_UNDEF; return res;}
	}
	else if (a.numtype==NUM_MINFTY)
	{
		if (b.numtype!=NUM_MINFTY) {return a;}
		else {res.numtype=NUM_UNDEF; return res;}
	}
	else if (b.numtype==NUM_PINFTY)
	{
		if (a.numtype!=NUM_PINFTY) {return b;}
		else {res.numtype=NUM_UNDEF; return res;}
	}
	else if (b.numtype==NUM_MINFTY)
	{
		if (a.numtype!=NUM_MINFTY) {return b;}
		else {res.numtype=NUM_UNDEF; return res;}
	}
	else
	{
		if (a.numtype==NUM_REAL)
		{
			if (b.numtype==NUM_REAL)
			{
				res.numtype=NUM_REAL;
				res.val.real=a.val.real-b.val.real;
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.numtype=NUM_REAL;
				res.val.real=a.val.real-b.val.integer;
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.real-b.val.complex.RE;
				res.val.complex.IM=-b.val.complex.IM;
				return res;
			}
		}
		else if (a.numtype==NUM_INTEGER)
		{
			if (b.numtype==NUM_REAL)
			{
				res.numtype=NUM_REAL;
				res.val.real=a.val.integer-b.val.real;
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.numtype=NUM_INTEGER;
				res.val.integer=a.val.integer-b.val.integer;
				if(res.val.integer>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.integer<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.integer-b.val.complex.RE;
				res.val.complex.IM=-b.val.complex.IM;
				return res;
			}
		}
		else if (a.numtype==NUM_COMPLEX)
		{
			res.numtype=NUM_COMPLEX;
			if (b.numtype==NUM_REAL)
			{
				res.val.complex.RE=a.val.complex.RE-b.val.real;
				res.val.complex.IM=a.val.complex.IM;
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.val.complex.RE=a.val.complex.RE-b.val.integer;
				res.val.complex.IM=a.val.complex.IM;
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.complex.RE-b.val.complex.RE;
				res.val.complex.IM=a.val.complex.IM-b.val.complex.IM;
				return res;
			}
		}
	}
	return res;
}
num mul_num(num a,num b)/*a*b*/
{
	num res;
	if (a.numtype==NUM_UNDEF||b.numtype==NUM_UNDEF) {res.numtype=NUM_UNDEF; return res;}
	else if (a.numtype==NUM_PINFTY||a.numtype==NUM_MINFTY)
	{
		if (b.numtype==NUM_PINFTY) {return a;}
		if (b.numtype==NUM_MINFTY)
		{
			if (a.numtype==NUM_PINFTY) {return b;}
			else {res.numtype=NUM_PINFTY; return res;}
		}
		else
		{
			if (b.numtype==NUM_REAL)
			{
				if(b.val.real==0) {res.numtype=NUM_UNDEF; return res;}
				else if (b.val.real<0)
				{
				    if(a.numtype==NUM_MINFTY){res.numtype=NUM_PINFTY; return res;}
				    res.numtype=NUM_MINFTY; return res;
                }
				else {return a;}
			}
			else if (b.numtype==NUM_INTEGER)
			{
				if(b.val.integer==0) {res.numtype=NUM_UNDEF; return res;}
				else if (b.val.integer<0)
				{
				   if(a.numtype==NUM_MINFTY){res.numtype=NUM_PINFTY; return res;}
				   res.numtype=NUM_MINFTY; return res;
                }
				else {return a;}
			}
			return a;
		}
	}
	else if (b.numtype==NUM_PINFTY||b.numtype==NUM_MINFTY)
	{
		if (a.numtype==NUM_PINFTY) {return b;}
		if (a.numtype==NUM_MINFTY)
		{
			if (b.numtype==NUM_PINFTY) {return a;}
			else {res.numtype=NUM_PINFTY; return res;}
		}
		else
		{
			if (a.numtype==NUM_REAL)
			{
				if(a.val.real==0) {res.numtype=NUM_UNDEF; return res;}
				else if (a.val.real<0)
				{
				    if(b.numtype==NUM_MINFTY){res.numtype=NUM_PINFTY; return res;}
				    res.numtype=NUM_MINFTY; return res;
                }
				else {return b;}
			}
			else if (a.numtype==NUM_INTEGER)
			{
				if(a.val.integer==0) {res.numtype=NUM_UNDEF; return res;}
				else if (a.val.integer<0)
				{
				    if(b.numtype==NUM_MINFTY){res.numtype=NUM_PINFTY; return res;}
				    res.numtype=NUM_MINFTY; return res;
                }
				else {return b;}
			}
			return b;
		}
	}
	else
	{
		if (a.numtype==NUM_REAL)
		{
			if (b.numtype==NUM_REAL)
			{
				res.numtype=NUM_REAL;
				res.val.real=a.val.real*b.val.real;
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.numtype=NUM_REAL;
				res.val.real=a.val.real*b.val.integer;
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.real*b.val.complex.RE;
				res.val.complex.IM=a.val.real*b.val.complex.IM;
				return res;
			}
		}
		else if (a.numtype==NUM_INTEGER)
		{
			if (b.numtype==NUM_REAL)
			{
				res.numtype=NUM_REAL;
				res.val.real=a.val.integer*b.val.real;
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.numtype=NUM_INTEGER;
				double resb;/*pour gérer le dépassement des types int*/
				resb=((double)a.val.integer)*((double)b.val.integer);
				if(resb>INT_MAX){res.numtype=NUM_PINFTY;}
				else if(resb<INT_MIN){res.numtype=NUM_MINFTY;}
				else{res.val.integer=(int)resb;}
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.integer*b.val.complex.RE;
				res.val.complex.IM=a.val.integer*b.val.complex.IM;
				return res;
			}
		}
		else if (a.numtype==NUM_COMPLEX)
		{
			res.numtype=NUM_COMPLEX;
			if (b.numtype==NUM_REAL)
			{
				res.val.complex.RE=a.val.complex.RE*b.val.real;
				res.val.complex.IM=a.val.complex.IM*b.val.real;
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.val.complex.RE=a.val.complex.RE*b.val.integer;
				res.val.complex.IM=a.val.complex.IM*b.val.integer;
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.complex.RE*b.val.complex.RE-a.val.complex.IM*b.val.complex.IM;
				res.val.complex.IM=a.val.complex.IM*b.val.complex.RE+a.val.complex.RE*b.val.complex.IM;
				return res;
			}
		}
	}
	return res;
}
num div_num(num a,num b)/*a/b*/
{
	num res;
	if (a.numtype==NUM_UNDEF||b.numtype==NUM_UNDEF) {res.numtype=NUM_UNDEF; return res;}
	else if (a.numtype==NUM_PINFTY||a.numtype==NUM_MINFTY)
	{
		if (b.numtype==NUM_PINFTY) {return a;}
		if (b.numtype==NUM_MINFTY)
		{
			if (a.numtype==NUM_PINFTY) {return b;}
			else {res.numtype=NUM_PINFTY; return res;}
		}
		else
		{
			if (b.numtype==NUM_REAL)
			{
				if(b.val.real==0) {res.numtype=NUM_UNDEF; return res;}
				else if (b.val.real<0) {res.numtype=NUM_MINFTY; return res;}
				else {return a;}
			}
			else if (b.numtype==NUM_INTEGER)
			{
				if(b.val.integer==0) {res.numtype=NUM_UNDEF; return res;}
				else if (b.val.integer<0) {res.numtype=NUM_MINFTY; return res;}
				else {return a;}
			}
			return a;
		}
	}
	else if (b.numtype==NUM_PINFTY||b.numtype==NUM_MINFTY)
	{
		if (a.numtype==NUM_PINFTY) {return b;}
		if (a.numtype==NUM_MINFTY)
		{
			if (b.numtype==NUM_PINFTY) {return a;}
			else {res.numtype=NUM_PINFTY; return res;}
		}
		else
		{
			if (a.numtype==NUM_REAL)
			{
				if(a.val.real==0) {res.numtype=NUM_UNDEF; return res;}
				else if (a.val.real<0) {res.numtype=NUM_MINFTY; return res;}
				else {return b;}
			}
			else if (a.numtype==NUM_INTEGER)
			{
				if(a.val.integer==0) {res.numtype=NUM_UNDEF; return res;}
				else if (a.val.integer<0) {res.numtype=NUM_MINFTY; return res;}
				else {return b;}
			}
			return b;
		}
	}
	else
	{
		if (a.numtype==NUM_REAL)
		{
			if (b.numtype==NUM_REAL)
			{
				res.numtype=NUM_REAL;
				if(b.val.real!=0) {res.val.real=a.val.real/b.val.real;}
				else
				{
					if(a.val.real==0) {res.numtype=NUM_UNDEF; return res;}
					else if (a.val.real<0) {res.numtype=NUM_MINFTY; return res;}
					else {res.numtype=NUM_PINFTY; return res;}
				}
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.numtype=NUM_REAL;
				if(b.val.integer!=0)
				{
					double b2=b.val.integer;
					res.val.real=a.val.real/b2;
				}
				else
				{
					if(a.val.real==0) {res.numtype=NUM_UNDEF; return res;}
					else if (a.val.real<0) {res.numtype=NUM_MINFTY; return res;}
					else {res.numtype=NUM_PINFTY; return res;}
				}
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.real*b.val.complex.RE/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				res.val.complex.IM=-a.val.real*b.val.complex.IM/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				return res;
			}
		}
		else if (a.numtype==NUM_INTEGER)
		{
			if (b.numtype==NUM_REAL)
			{
				res.numtype=NUM_REAL;
				if(b.val.real!=0) {res.val.real=a.val.integer/b.val.real;}
				else
				{
					if(a.val.integer==0) {res.numtype=NUM_UNDEF; return res;}
					else if (a.val.integer<0) {res.numtype=NUM_MINFTY; return res;}
					else {res.numtype=NUM_PINFTY; return res;}
				}
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.numtype=NUM_REAL;
				if(b.val.integer!=0) {res.val.real=a.val.integer/((double)b.val.integer);}
				else
				{
					if(a.val.integer==0) {res.numtype=NUM_UNDEF; return res;}
					else if (a.val.integer<0) {res.numtype=NUM_MINFTY; return res;}
					else {res.numtype=NUM_PINFTY; return res;}
				}
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.integer*b.val.complex.RE/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				res.val.complex.IM=-a.val.integer*b.val.complex.IM/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				return res;
			}
		}
		else if (a.numtype==NUM_COMPLEX)
		{
			res.numtype=NUM_COMPLEX;
			if (b.numtype==NUM_REAL)
			{
				res.val.complex.RE=a.val.complex.RE/b.val.real;
				res.val.complex.IM=a.val.complex.IM/b.val.real;
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.val.complex.RE=a.val.complex.RE/b.val.integer;
				res.val.complex.IM=a.val.complex.IM/b.val.integer;
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=(a.val.complex.RE*b.val.complex.RE+a.val.complex.IM*b.val.complex.IM)/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				res.val.complex.IM=(a.val.complex.IM*b.val.complex.RE-a.val.complex.RE*b.val.complex.IM)/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				return res;
			}
		}
	}
	return res;
}
num quotient(num a,num b)/*(INT)a/b*/
{
	num res;
	if (a.numtype==NUM_UNDEF||b.numtype==NUM_UNDEF) {res.numtype=NUM_UNDEF; return res;}
	else if (a.numtype==NUM_PINFTY||a.numtype==NUM_MINFTY)
	{
		if (b.numtype==NUM_PINFTY) {return a;}
		if (b.numtype==NUM_MINFTY)
		{
			if (a.numtype==NUM_PINFTY) {return b;}
			else {res.numtype=NUM_PINFTY; return res;}
		}
		else
		{
			if (b.numtype==NUM_REAL)
			{
				if(b.val.real==0) {res.numtype=NUM_UNDEF; return res;}
				else if (b.val.real<0) {res.numtype=NUM_MINFTY; return res;}
				else {return a;}
			}
			else if (b.numtype==NUM_INTEGER)
			{
				if(b.val.integer==0) {res.numtype=NUM_UNDEF; return res;}
				else if (b.val.integer<0) {res.numtype=NUM_MINFTY; return res;}
				else {return a;}
			}
			return a;
		}
	}
	else if (b.numtype==NUM_PINFTY||b.numtype==NUM_MINFTY)
	{
		if (a.numtype==NUM_PINFTY) {return b;}
		if (a.numtype==NUM_MINFTY)
		{
			if (b.numtype==NUM_PINFTY) {return a;}
			else {res.numtype=NUM_PINFTY; return res;}
		}
		else
		{
			if (a.numtype==NUM_REAL)
			{
				if(a.val.real==0) {res.numtype=NUM_UNDEF; return res;}
				else if (a.val.real<0) {res.numtype=NUM_MINFTY; return res;}
				else {return b;}
			}
			else if (a.numtype==NUM_INTEGER)
			{
				if(a.val.integer==0) {res.numtype=NUM_UNDEF; return res;}
				else if (a.val.integer<0) {res.numtype=NUM_MINFTY; return res;}
				else {return b;}
			}
			return b;
		}
	}
	else
	{
		if (a.numtype==NUM_REAL)
		{
			if (b.numtype==NUM_REAL)
			{
				res.numtype=NUM_INTEGER;
				if(b.val.real!=0) {res.val.integer=a.val.real/b.val.real;}
				else
				{
					if(a.val.real==0) {res.numtype=NUM_UNDEF; return res;}
					else if (a.val.real<0) {res.numtype=NUM_MINFTY; return res;}
					else {res.numtype=NUM_PINFTY; return res;}
				}
				if(res.val.integer>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.integer<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.numtype=NUM_INTEGER;
				if(b.val.integer!=0)
				{
					res.val.integer=a.val.real/b.val.integer;
				}
				else
				{
					if(a.val.real==0) {res.numtype=NUM_UNDEF; return res;}
					else if (a.val.real<0) {res.numtype=NUM_MINFTY; return res;}
					else {res.numtype=NUM_PINFTY; return res;}
				}
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.real*b.val.complex.RE/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				res.val.complex.IM=-a.val.real*b.val.complex.IM/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				return res;
			}
		}
		else if (a.numtype==NUM_INTEGER)
		{
			if (b.numtype==NUM_REAL)
			{
				res.numtype=NUM_INTEGER;
				if(b.val.real!=0) {res.val.real=a.val.integer/b.val.real;}
				else
				{
					if(a.val.integer==0) {res.numtype=NUM_UNDEF; return res;}
					else if (a.val.integer<0) {res.numtype=NUM_MINFTY; return res;}
					else {res.numtype=NUM_PINFTY; return res;}
				}
				if(res.val.integer>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.integer<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.numtype=NUM_INTEGER;
				if(b.val.integer!=0) {res.val.integer=a.val.integer/((double)b.val.integer);}
				else
				{
					if(a.val.integer==0) {res.numtype=NUM_UNDEF; return res;}
					else if (a.val.integer<0) {res.numtype=NUM_MINFTY; return res;}
					else {res.numtype=NUM_PINFTY; return res;}
				}
				if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
				else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=a.val.integer*b.val.complex.RE/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				res.val.complex.IM=-a.val.integer*b.val.complex.IM/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				return res;
			}
		}
		else if (a.numtype==NUM_COMPLEX)
		{
			res.numtype=NUM_COMPLEX;
			if (b.numtype==NUM_REAL)
			{
				res.val.complex.RE=a.val.complex.RE/b.val.real;
				res.val.complex.IM=a.val.complex.IM/b.val.real;
				return res;
			}
			else if (b.numtype==NUM_INTEGER)
			{
				res.val.complex.RE=a.val.complex.RE/b.val.integer;
				res.val.complex.IM=a.val.complex.IM/b.val.integer;
				return res;
			}
			else if (b.numtype==NUM_COMPLEX)
			{
				res.numtype=NUM_COMPLEX;
				res.val.complex.RE=(a.val.complex.RE*b.val.complex.RE+a.val.complex.IM*b.val.complex.IM)/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				res.val.complex.IM=(a.val.complex.IM*b.val.complex.RE-a.val.complex.RE*b.val.complex.IM)/(pow(b.val.complex.RE,2)+pow(b.val.complex.IM,2));
				return res;
			}
		}
	}
	return res;
}
num remainderb(num a,num b)/*a%b*/
{
	num res;
	if (a.numtype==NUM_UNDEF||b.numtype==NUM_UNDEF) {res.numtype=NUM_UNDEF; return res;}
	else if (a.numtype==NUM_PINFTY||a.numtype==NUM_MINFTY)
	{
		if (b.numtype==NUM_PINFTY) {return a;}
		if (b.numtype==NUM_MINFTY)
		{
			if (a.numtype==NUM_PINFTY) {return b;}
			else {res.numtype=NUM_PINFTY; return res;}
		}
	}
	else if (a.numtype==NUM_INTEGER && b.numtype==NUM_INTEGER)
	{
		res.numtype=NUM_INTEGER;
		if(b.val.integer!=0) {res.val.integer=a.val.integer%(b.val.integer);}
		else
		{
			if(a.val.integer==0) {res.numtype=NUM_UNDEF; return res;}
			else if (a.val.integer<0) {res.numtype=NUM_MINFTY; return res;}
			else {res.numtype=NUM_PINFTY; return res;}
		}
		if(res.val.real>INT_MAX) {res.numtype=NUM_PINFTY;}
		else if(res.val.real<INT_MIN) {res.numtype=NUM_MINFTY;}
		return res;

	}
	else {res.numtype=NUM_UNDEF; return res;}
	return res;
}
num norm_num (num a)/*|a|*/
{
	num res;
	if (a.numtype==NUM_COMPLEX)
	{
		res.numtype=NUM_REAL;
		res.val.real=sqrt(pow(a.val.complex.RE,2)+pow(a.val.complex.IM,2));
		return res;
	}
	else if (a.numtype==NUM_REAL)
	{
		res.numtype=NUM_REAL;
		if (a.val.real<0) {res.val.real=-a.val.real; return res;}
		res.val.real=a.val.real; return res;
	}
	else if (a.numtype==NUM_INTEGER)
	{
		res.numtype=NUM_INTEGER;
		if (a.val.integer<0) { res.val.integer=-a.val.integer; return res;}
		res.val.integer=a.val.integer;
		return res;
	}
	else if (a.numtype==NUM_PINFTY)
	{
		res.numtype=NUM_PINFTY;
		return res;
	}
	else if (a.numtype==NUM_MINFTY)
	{
		res.numtype=NUM_PINFTY;
		return res;
	}
	res.numtype=NUM_UNDEF; return res;
}

