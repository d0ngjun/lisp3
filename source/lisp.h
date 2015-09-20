#ifndef _LISP_H
#define _LISP_H

#include "environ.h"

class lisp {
public:
    lisp();
    ~lisp();

    expr make_expr(const string &s) const;

    // global environment.
    static shared_ptr<environ> env;

private:
    mpc_parser_t *_number;
    mpc_parser_t *_string;
    mpc_parser_t *_define;
    mpc_parser_t *_let;
    mpc_parser_t *_if_cond;
    mpc_parser_t *_lambda;
    mpc_parser_t *_symbol;
    mpc_parser_t *_sexpr;
    mpc_parser_t *_expr;
    mpc_parser_t *_lispy;
};

#endif
