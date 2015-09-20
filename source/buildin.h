#ifndef _BUILDIN_H
#define _BUILDIN_H

#include "expr.h"

expr buildin_plus(const vector<expr> &v);
expr buildin_minus(const vector<expr> &v);
expr buildin_multiplies(const vector<expr> &v);
expr buildin_divides(const vector<expr> &v);

bool buildin_equal(const vector<expr> &v);
bool buildin_less(const vector<expr> &v);
bool buildin_larger(const vector<expr> &v);
bool buildin_and(const vector<expr> &v);
bool buildin_or(const vector<expr> &v);
bool buildin_not(const vector<expr> &v);

string buildin_to_string(const expr::arith *a);
string buildin_to_string(const expr::logic *l);

#endif
