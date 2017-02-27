#include "primitive.h"
#include "form.h"

void init_interpreter ( void )
{

    /**Basic symbol**/
    nil=make_nil();false=make_boolean(0);true=make_boolean(1);
    /**Main environment initialization***/
    main_env=create_env(NULL,HSIZE);/*list end marker*/
    add_var(main_env,make_symbol("()"),nil);
    add_var(main_env,make_symbol("#t") ,true);
    add_var(main_env,make_symbol("#f"),false);
    /***Forms***/
    /*conditionals*/
    add_var(main_env,make_symbol("if"),make_form(IF));
    add_var(main_env,make_symbol("and"),make_form(AND));
    add_var(main_env,make_symbol("or"),make_form(OR));
    /*declaration and set*/
    add_var(main_env,make_symbol("define"),make_form(DEFINE));
    add_var(main_env,make_symbol("set!"),make_form(SET));
    /*procedure*/
    add_var(main_env,make_symbol("quote"),make_form(QUOTE));
    add_var(main_env,make_symbol("'"),make_form(QUOTE));
    add_var(main_env,make_symbol("begin"),make_form(BEGIN));
    add_var(main_env,make_symbol("lambda"),make_form(LAMBDA));
    add_var(main_env,make_symbol("let"),make_form(LET));
    add_var(main_env,make_symbol("let*"),make_form(LETX));
    add_var(main_env,make_symbol("map"),make_form(MAP));
    add_var(main_env,make_symbol("show"),make_form(SHOW));
    /***Primitives***/
    /*arithmetic and logic*/
    add_var(main_env,make_symbol("="),make_primitive(EQUAL));
    add_var(main_env,make_symbol("<"),make_primitive(INF));
    add_var(main_env,make_symbol(">"),make_primitive(SUP));
    add_var(main_env,make_symbol("+"),make_primitive(ADD));
    add_var(main_env,make_symbol("-"),make_primitive(SUBSTRACT));
    add_var(main_env,make_symbol("*"),make_primitive(MULTIPLY));
    add_var(main_env,make_symbol("/"),make_primitive(DIVIDE));
    add_var(main_env,make_symbol("quotient"),make_primitive(QUOTIENT));
    add_var(main_env,make_symbol("%"),make_primitive(REMAINDER));
    /*tests on types*/
    add_var(main_env,make_symbol("nil?"),make_primitive(IS_NIL));
    add_var(main_env,make_symbol("boolean?"),make_primitive(IS_BOOLEAN));
    add_var(main_env,make_symbol("number?"),make_primitive(IS_NUMBER));
    add_var(main_env,make_symbol("char?"),make_primitive(IS_CHAR));
    add_var(main_env,make_symbol("string?"),make_primitive(IS_STRING));
    add_var(main_env,make_symbol("symbol?"),make_primitive(IS_SYMBOL));
    add_var(main_env,make_symbol("pair?"),make_primitive(IS_PAIR));
    /*types conversions*/
    add_var(main_env,make_symbol("char->integer"),make_primitive(CHAR_TO_INT));
    add_var(main_env,make_symbol("integer->char"),make_primitive(INT_TO_CHAR));
    add_var(main_env,make_symbol("str->number"),make_primitive(STRING_TO_NUMBER));
    add_var(main_env,make_symbol("number->str"),make_primitive(NUMBER_TO_STRING));
    add_var(main_env,make_symbol("str->symbol"),make_primitive(STRING_TO_SYMBOL));
    add_var(main_env,make_symbol("symbol->str"),make_primitive(SYMBOL_TO_STRING));
    /*list operators*/
    add_var(main_env,make_symbol("list"),make_primitive(LIST));
    add_var(main_env,make_symbol("cons"),make_primitive(CONS));
    add_var(main_env,make_symbol("car"),make_primitive(CAR));
    add_var(main_env,make_symbol("cdr"),make_primitive(CDR));
    add_var(main_env,make_symbol("lenght"),make_primitive(LENGTH));
    /*files command*/

}
