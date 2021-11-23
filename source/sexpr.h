#pragma once

#include "environ.h"

class sexpr {
public:
    explicit sexpr(const std::vector<expr> &v);

    expr eval(const std::shared_ptr<environ> &env) const;

    expr bind(const std::vector<expr> &args, std::shared_ptr<environ> &env) const;

    expr car() const;

    expr cdr() const;

    std::string to_string() const;

private:
    std::vector<expr> _exprs;

    friend bool operator==(const sexpr &s1, const sexpr &s2);
};

bool operator==(const sexpr &s1, const sexpr &s2);