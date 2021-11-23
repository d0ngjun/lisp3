#pragma once

#include "expr.h"

expr buildin_plus(const std::vector<expr> &v);
expr buildin_minus(const std::vector<expr> &v);
expr buildin_multiplies(const std::vector<expr> &v);
expr buildin_divides(const std::vector<expr> &v);

bool buildin_equal(const std::vector<expr> &v);
bool buildin_less(const std::vector<expr> &v);
bool buildin_larger(const std::vector<expr> &v);
bool buildin_and(const std::vector<expr> &v);
bool buildin_or(const std::vector<expr> &v);
bool buildin_not(const std::vector<expr> &v);

std::string buildin_to_string(expr::arith *a);
std::string buildin_to_string(expr::logic *l);