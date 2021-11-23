#pragma once

#include "environ.h"

class lisp {
public:
    lisp();
    ~lisp();

    expr make_expr(const std::string &s) const;

    // global environment.
    static std::shared_ptr<environ> env;

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