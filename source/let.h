#pragma once

#include "environ.h"

class let {
public:
    explicit let(const expr &n, const expr &v, const expr &e, const std::shared_ptr<environ> &env);

    expr eval() const;

    std::string to_string() const;

private:
    std::string _name;
    expr _value;
    expr _expr;
    std::shared_ptr<environ> _env;
};