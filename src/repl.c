#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "object.h"
#include "getSexpr.h"
#include "read.h"
#include "print.h"
#include "environment.h"
#include "eval.h"
#include "form.h"
#include "primitive.h"

/* mode d'interaction avec l'interpreteur (exemple)*/
typedef enum {INTERACTIF,SCRIPT} inter_mode;


void usage_error( char *command ) {fprintf( stderr, "Usage: %s [file.scm]\n   If no file is given, executes in Shell mode.\n", command );}

object* main_env;
object nil;
object true;
object false;
object error;
int main ( int argc, char *argv[] )
{
    char     input[BIGSTRING];
    uint     here = 0;
    object   output = NULL;
    object   sexpr = NULL;
    inter_mode mode;
    FILE *   fp = NULL; /* le flux dans lequel les commande seront lues : stdin (mode shell) ou un fichier */
    /* exemples d'utilisation des macros du fichier notify.h *//* WARNING_MSG : sera toujours affiche */
    /* macro INFO_MSG : uniquement si compil avec -DVERBOSE. Cf Makefile*/
    /* macro DEBUG_MSG : uniquement si compil avec -DDEBUG (ie : compil avec make debug). Cf Makefile */
    /* La ligne suivante provoquerait l'affichage du message puis la sortie du programme avec un code erreur non nul (EXIT_FAILURE) */
    /* ERROR_MSG("Erreur. Arret du programme"); */
    if ( argc > 2 ) {usage_error( argv[0] );exit( EXIT_FAILURE );}
    if(argc == 2 && strcmp(argv[1], "-h") == 0) {usage_error( argv[0] );exit( EXIT_SUCCESS );}
    init_interpreter();/*print_env(main_env);*/
    fp = stdin;mode = INTERACTIF;/*par defaut : mode shell interactif */
    if(argc == 2)
    {
        fp = fopen( argv[1], "r" );/* mode fichier de commandes */
        if ( fp == NULL ) {perror( "fopen" );exit( EXIT_FAILURE );}
        mode = SCRIPT;
    }
    while ( 1 )
    {
        input[0]='\0';here = 0;
        output = NULL;sexpr = NULL;
        uint Sexpr_err= get_sexpr( input, fp );

        if ( S_OK != Sexpr_err)
        {
            /* si fichier alors on sort*/
            if (mode == SCRIPT)
            {
                fclose( fp );
                if (Sexpr_err==S_END) {exit(EXIT_SUCCESS);}/* Cas fin de fichier script */
                ERROR_MSG("Malformed S-expression --- Aborts");/* Cas S-Expression mal formee dans le fichier script */
            }
            continue; /*sinon on rend la main à l'utilisateur*/
        }
        if ( 0 == strlen( input ) ) {continue;}

        /*Pour le step 0 on se contente d'afficher la S-Expression lue  puis d'en lire une autre
        METTRE EN COMMENTAIRE LES DEUX LIGNES SUIVANTES POUR PASSER A L'INCREMENT 1 */
        /*printf("%s\n", input );
        continue;*/
        here  = 0;
        sexpr = read( input, &here );
        if(sexpr!=error){sexpr = sexpr->data.pair.car;}/*Pour éviter le double parenthesage*/
        if ( NULL == sexpr )/* si fichier alors on sort*/
        {
            if (mode == SCRIPT) {fclose( fp );ERROR_MSG("Invalid S-expression --- Aborts");}/*macro ERROR_MSG : message d'erreur puis fin de programme ! */
            continue ;/*sinon on rend la main à l'utilisateur*/
        }
        if(sexpr!=error){output =eval( sexpr,main_env );}
        if( NULL == output)/* si fichier alors on sort*/
        {
            if (mode == SCRIPT) { fclose( fp );ERROR_MSG("Error while evaluating input --- Aborts");}/*macro ERROR_MSG : message d'erreur puis fin de programme ! */
            continue ;/*sinon on rend la main à l'utilisateur*/
        }
        if(output!=error){printf( "==> " );print( output );printf( "\n" );}
    }
    if (mode == SCRIPT) {fclose( fp );}
    exit( EXIT_SUCCESS );
}
