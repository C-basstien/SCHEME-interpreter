#include <stdio.h>
#include <ctype.h>
#include <read.h>
#include <limits.h>
#include "mem.h"
#include "getSexpr.h"
void flip( uint *i )
{
	if ( *i == FALSE ){*i = TRUE;}
	else {*i = FALSE;}
}

/**
 * @fn char* first_usefull_char(char* line)
 *
 * @brief retourne un pointeur sur le premier caractere utile dans line
 * ou NULL si line ne contient que des espaces et des commentaires
 */
char* first_usefull_char(char* line)
{

	int i=0;
	if (line == NULL) {return NULL;}
	i = 0;/* on saute les espaces */
	while(line[i] != '\0' && isspace(line[i])) {i++;}/* si fin de ligne => ligne inutile */
	if(line[i] == '\0') {return NULL;}/* si premier caractere non espace est ';' => ligne inutile */
	if(line[i] == ';'){return NULL;}
	return line + i; /* ligne utile */
}

/**
 * @fn uint  sfs_get_sexpr( char *input, FILE *fp )
 *
 * @brief extrait la prochaine S-Expression dans le flux fp et la stocke dans input
 * (meme si elle est repartie sur plusieurs lignes)
 * @param fp (FILE *) flux d'entree (ouvert en ecriture, mode texte)
 * @param input (char *) chaine allouee de taille BIGSTRING, dans laquelle la S-Expression sera stockée
 *
 * @return S_OK si une S-Expression apparemment valide a ete trouvee
 * @return S_KO si on n'a pas trouve de S-Expression valide
 * @return S_END si fin de fichier atteinte sans avoir lu de caractere utile.
 *
 * sfs_get_sexpr commence par lire une ligne dans fp,
 * puis compte le nombre de parentheses ouvrantes et fermantes sur la ligne.
 * Les parentheses dans des chaines et les caracteres Scheme #\( et #\)
 * ne sont pas comptes.
 *
 * Si le compte devient zéro et que
 *        - la ligne est fini, la fonction retourne S_OK
 * 				- la ligne n'est pas fini la fonction retourne S_KO
 *
 * S'il y a plus de parentheses fermantes qu'ouvrantes,
 * la fonction retourne S_KO.
 * Les commentaires et espaces qui figurent a la fin de chaque ligne
 * sont remplacés par un espace.
 * Les espaces qui figurent a la fin de la S-Expression (y compris '\n')
 * sont supprimés.
 *
 * Attention : cette fonction refuse les S-Expression multiple sur une seule ligne. Ainsi :
 *    a b c
 *    (qqchose) (autrechose)
 *    (qqchose) 78
 * seront considereees comme des erreurs
 * et la fonction retournera S_KO
 *
 * @pre fp doit etre prealablement ouvert en lecture
 * @pre input doit etre prealablement alloue en memoire, de taille BIGSTRING
 */



unsigned int   get_sexpr( string input, FILE *fp )
{
	int       parlevel = 0;
	uint      in_string = FALSE;
	uint      s = 0;
	char      k[BIGSTRING];
	char      *ret = NULL;
	char      *chunk = NULL;
	uint      i = 0;
	string    sfs_prompt;
	EXPRESSION_TYPE_T typeOfExpressionFound = NOTHING;
	parlevel = 0;
	memset( input, '\0', BIGSTRING );
	do
	{
		ret = NULL;
		chunk=k;
		memset( chunk, '\0', BIGSTRING );

		/* si en mode interactif*/
		if ( stdin == fp )
		{
			uint nspaces = 2*parlevel;
			init_string( sfs_prompt );/* le prompt indique le niveau de parenthese et decale la prochaine entrée en fonction de ce niveau (un peu à la python)*/
			sprintf( sfs_prompt, "SFS:%u > ", parlevel );
			for ( i= 0; i< nspaces; i++ ) {sfs_prompt[strlen(sfs_prompt)] = ' ';}
			if (nspaces>0) {input[strlen(input)+1] = '\0'; input[strlen(input)] = ' ';} /* si sur plusieurs lignes, le \n équivaut à un espace*/
			printf("%s",sfs_prompt);/*saisie de la prochaine ligne à ajouter dans l'input*/
			ret = fgets( chunk, BIGSTRING, fp );
			if (ret && chunk[strlen(chunk)-1] == '\n') chunk[strlen(chunk)-1] = '\0';

		}
		/*si en mode fichier*/
		else
		{
			ret = fgets( chunk, BIGSTRING, fp );
			if ( NULL == ret )/* fin de fichier...*/
			{
				if ( parlevel != 0 ) {WARNING_MSG( "Parse error: missing ')'" ); return S_KO;}
				return S_END;
			}

			if (strlen(chunk) == BIGSTRING-1 && chunk[BIGSTRING-1] != '\n'  && !feof(fp))
			{
				WARNING_MSG( "Too long line for this interpreter!" ); return S_KO;
			}
		}


		if (first_usefull_char(chunk) == NULL) {continue;}/* si la ligne est inutile => on va directement à la prochaine iteration */
		s = strlen( chunk );

		if ( s > 0 )
		{
			if (strlen(input) + s > BIGSTRING-1 ) {WARNING_MSG( "Too long a S-expression for this interpreter!" ); return S_KO;}
			for ( i = 0; i< strlen(chunk); i++ ) {
				/* si la fin de la ligne chunk est inutile,
				   on ajoute un espace dans input et on sort de la boucle*/
				if ( in_string == FALSE && first_usefull_char(chunk + i) == NULL ) {chunk[i]='\0'; input[strlen(input)] = ' '; break;}


				switch(chunk[i])
				{
				case '(':
					if (in_string == FALSE && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) )
					{
						parlevel++; typeOfExpressionFound = S_EXPR_PARENTHESIS;
					}
					break;
				case ')':
					if ( in_string == FALSE && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) )
					{
						parlevel--;
						if (parlevel == 0 ) {typeOfExpressionFound = FINISHED;}
						if ( parlevel < 0 ) {WARNING_MSG( "Parse error : cannot start with ')'" ); return S_KO;}
					}
					break;
				case '"':
					if ( i<2 || chunk[i-1] != '\\' )
					{
						if ( in_string == FALSE )
						{
							if(typeOfExpressionFound == BASIC_ATOME) {WARNING_MSG("Parse error: invalid string after atom : '%s'", chunk+i); return S_KO;}
							in_string = TRUE;
							if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {typeOfExpressionFound = STRING_ATOME;}
						}
						else
						{
							in_string = FALSE;
							if(typeOfExpressionFound == STRING_ATOME) {typeOfExpressionFound = FINISHED;}
						}
					}
					break;
				default:
					if(in_string == FALSE)
					{
						if(isspace(chunk[i])) {if(typeOfExpressionFound == BASIC_ATOME) {typeOfExpressionFound = FINISHED;}}
						else if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {typeOfExpressionFound = BASIC_ATOME;}
					}
					break;
				}


				if(typeOfExpressionFound == FINISHED)
				{
					char *first_useful = first_usefull_char(chunk + i + 1);
					if( first_useful != NULL)
					{
						if(*first_useful == ')' ) {WARNING_MSG( "Parse error: too many closing parenthesis')'" );}
						else {WARNING_MSG("Parse error: invalid trailing chars after S-Expr : '%s'", chunk+i);}
						return S_KO;
					}
				}
				input[strlen(input)] = chunk[i];/* recopie char par char*/
			}
			if(in_string == TRUE) {WARNING_MSG( "Parse error: non terminated string on line %s", chunk ); return S_KO;}
		}
		if ( parlevel > 0 && fp != stdin )
		{
			if ( feof( fp ) ) {WARNING_MSG( "Parse error: missing ')'" ); return S_KO;}
			if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = ' ';
		}
	} while ( parlevel > 0 );
	while (isspace(input[strlen(input)-1])) input[strlen(input)-1] = '\0';/* Suppression des espaces restant a la fin de l'expression, notamment le dernier '\n' */
	return S_OK;
}
