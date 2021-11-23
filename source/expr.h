#pragma once

#include <memory>
#include <string>
#include <vector>

#include "error.h"
#include "mpc.h"

class if_cond;
class define;
class environ;
class lambda;
class let;
class sexpr;
class symbol;

// for _type.
enum {
    EMPTY,      // 0
    ARITH,      // 1
    LOGIC,      // 2
    BOOLEAN,    // 3
    NUMBER,     // 4
    STRING,     // 5
    DEFINE,     // 6
    LET,        // 7
    IF,         // 8
    LAMBDA,     // 9
    SYMBOL,     // 10
    SEXPR,      // 11
    ERROR,      // 12
};

class expr {
public:
    typedef expr arith(const std::vector<expr> &v);
    typedef bool logic(const std::vector<expr> &v);

    // empty
    expr();
    explicit expr(arith *a);
    explicit expr(logic *l);
    explicit expr(const bool b);
    explicit expr(const long n);
    explicit expr(const char *s);
    explicit expr(const define &d);
    explicit expr(const let &l);
    explicit expr(const if_cond &i);
    explicit expr(const lambda &l);
    explicit expr(const symbol &s);
    explicit expr(const sexpr &s);
    // can freely construct expression via an error.
    expr(const error &e);

    expr(const expr &e);

    ~expr();

    expr &operator=(const expr &e);

    expr eval(const std::shared_ptr<environ> &env) const;

    expr call(const std::vector<expr> &args) const;

    expr bind(const std::vector<expr> &args, std::shared_ptr<environ> &env) const;

    bool failed() const;

    bool to_boolean() const;

    std::string to_string() const;

private:
    int _type;
    union {
        arith *_arith;
        logic *_logic;
        bool _boolean;
        long _number;
        std::string *_string;
        define *_define;
        let *_let;
        if_cond *_if_cond;
        lambda *_lambda;
        symbol *_symbol;
        sexpr *_sexpr;
        error *_error;
    };

    friend expr operator+(const expr &e1, const expr &e2);
    friend expr operator-(const expr &e1, const expr &e2);
    friend expr operator*(const expr &e1, const expr &e2);
    friend expr operator/(const expr &e1, const expr &e2);

    friend bool operator==(const expr &e1, const expr &e2);
    friend bool operator!=(const expr &e1, const expr &e2);
    friend bool operator<(const expr &e1, const expr &e2);
    friend bool operator>(const expr &e1, const expr &e2);
    friend bool operator&&(const expr &e1, const expr &e2);
    friend bool operator||(const expr &e1, const expr &e2);
    friend bool operator!(const expr &e);
};

expr operator+(const expr &e1, const expr &e2);
expr operator-(const expr &e1, const expr &e2);
expr operator*(const expr &e1, const expr &e2);
expr operator/(const expr &e1, const expr &e2);

bool operator==(const expr &e1, const expr &e2);
bool operator!=(const expr &e1, const expr &e2);
bool operator<(const expr &e1, const expr &e2);
bool operator>(const expr &e1, const expr &e2);
bool operator&&(const expr &e1, const expr &e2);
bool operator||(const expr &e1, const expr &e2);
bool operator!(const expr &e);