#pragma once

#include "environ.h"

class define {
public:
    explicit define(const expr &n, const expr &v, const std::shared_ptr<environ> &e);

    expr eval() const;

    std::string to_string() const;

private:
    std::string _name;
    expr _value;
    std::shared_ptr<environ> _env;
};