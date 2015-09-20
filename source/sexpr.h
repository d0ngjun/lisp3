#ifndef _SEXPR_H
#define _SEXPR_H

#include "environ.h"

class sexpr {
public:
    explicit sexpr(const vector<expr> &v);

    expr eval(const shared_ptr<environ> &env) const;

    expr bind(const vector<expr> &args, shared_ptr<environ> &env) const;

    expr car() const;

    expr cdr() const;

    string to_string() const;

private:
    vector<expr> _exprs;

    friend bool operator==(const sexpr &s1, const sexpr &s2);
};

bool operator==(const sexpr &s1, const sexpr &s2);

#endif
