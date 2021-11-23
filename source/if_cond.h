#pragma once

#include "environ.h"

class if_cond {
public:
    if_cond(const expr &c, const expr &i, const expr &e);

    expr eval(const std::shared_ptr<environ> &env) const;

    std::string to_string() const;

private:
    expr _cond;
    expr _if;
    expr _else;
};