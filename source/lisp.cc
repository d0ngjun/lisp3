#include "buildin.h"
#include "if_cond.h"
#include "define.h"
#include "error.h"
#include "lambda.h"
#include "let.h"
#include "lisp.h"
#include "sexpr.h"
#include "symbol.h"

std::shared_ptr<environ> lisp::env(new environ());

static expr make_expr(const mpc_ast_t *ast, std::shared_ptr<environ> &env);

lisp::lisp() : _number(mpc_new("number")), _string(mpc_new("string")), _define(mpc_new("define")), _let(mpc_new("let")), _if_cond(mpc_new("if")), _lambda(mpc_new("lambda")), _symbol(mpc_new("symbol")), _sexpr(mpc_new("sexpr")), _expr(mpc_new("expr")), _lispy(mpc_new("lispy"))
{
    mpca_lang(MPCA_LANG_DEFAULT, \
        "number : /[+-]?[0-9]+/; \
        string : /\"(\\\\.|[^\"])*\"/; \
        define : \"define\" <symbol> <expr>; \
        let : \"let\" <symbol> <expr> <expr>?; \
        if : \"if\" <expr> <expr> <expr>?; \
        lambda : \"lambda\" <expr> <expr>; \
        symbol : /[a-zA-Z_+\\-*\\/=<>!&|]+/; \
        sexpr : '(' <expr>* ')'; \
        expr : <number> | <string> | <define> | <let> | <if> | <lambda> | <symbol> | <sexpr>; \
        lispy : /^/ <expr>* /$/;", \
        _number, _string, _define, _let, _if_cond, _lambda, _symbol, _sexpr, _expr, _lispy);

    // global symbol.
    lisp::env->put("+", expr(buildin_plus));
    lisp::env->put("-", expr(buildin_minus));
    lisp::env->put("*", expr(buildin_multiplies));
    lisp::env->put("/", expr(buildin_divides));

    lisp::env->put("=", expr(buildin_equal));
    lisp::env->put("<", expr(buildin_less));
    lisp::env->put(">", expr(buildin_larger));
    lisp::env->put("!", expr(buildin_not));
    lisp::env->put("&", expr(buildin_and));
    lisp::env->put("|", expr(buildin_or));
}

lisp::~lisp()
{
    mpc_cleanup(10, _number, _string, _define, _let, _if_cond, _lambda, _symbol, _sexpr, _expr, _lispy);
}

expr lisp::make_expr(const std::string &s) const
{
    expr e;
    mpc_result_t r;

    if (mpc_parse("<>", s.c_str(), _lispy, &r)) {
        mpc_ast_t *ast = (mpc_ast_t *)r.output;
        // mpc_ast_print(ast);
        e = ::make_expr(ast->children[1], env);
        mpc_ast_delete(ast);
    } else {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
    }

    return e;
}

template <typename T>
static expr make_expr(const mpc_ast_t *a1, const mpc_ast_t *a2, std::shared_ptr<environ> &env)
{
    expr e1 = make_expr(a1, env);
    expr e2 = make_expr(a2, env);

    return expr(T(e1, e2, env));
}

template <typename T>
static expr make_expr(const mpc_ast_t *a1, const mpc_ast_t *a2, const mpc_ast_t *a3, std::shared_ptr<environ> &env)
{
    expr e1 = make_expr(a1, env);
    expr e2 = make_expr(a2, env);
    expr e3 = make_expr(a3, env);

    return expr(T(e1, e2, e3, env));
}

template <typename T>
static expr make_expr(const mpc_ast_t *a1, const mpc_ast_t *a2, const mpc_ast_t *a3)
{
    expr e1 = make_expr(a1, lisp::env);
    expr e2 = make_expr(a2, lisp::env);
    expr e3 = make_expr(a3, lisp::env);

    return expr(T(e1, e2, e3));
}

static expr make_expr(const mpc_ast_t *ast, std::shared_ptr<environ> &env)
{
    expr e;

    if (ast == NULL) {
        return e;
    }

    mpc_ast_t **children = ast->children;
    mpc_ast_t *third = ast->children_num > 3 ? children[3] : NULL;

    if (strstr(ast->tag, "number") != NULL) {
        long n = strtol(ast->contents, NULL, 10);
        e = errno != ERANGE ? expr(n) : error(BAD_NUMBER, ast->contents);
    } else if (strstr(ast->tag, "string") != NULL) {
        e = expr(ast->contents);
    } else if (strstr(ast->tag, "define") != NULL) {
        e = make_expr<define>(children[1], children[2], env);
    } else if (strstr(ast->tag, "let") != NULL) {
        e = make_expr<let>(children[1], children[2], third, env);
    } else if (strstr(ast->tag, "if") != NULL) {
        e = make_expr<if_cond>(children[1], children[2], third);
    } else if (strstr(ast->tag, "lambda") != NULL) {
        e = make_expr<lambda>(children[1], children[2], env);
    } else if (strstr(ast->tag, "symbol") != NULL) {
        e = expr(symbol(ast->contents));
    } else if (strstr(ast->tag, "sexpr") != NULL) {
        std::vector<expr> exprs;
        for (int i = 1; i < ast->children_num - 1; ++i) {
            exprs.push_back(make_expr(ast->children[i], env));
        }
        e = expr(sexpr(exprs));
    } else {
        e = error(BAD_TAG, ast->tag);
    }

    return e;
}