#pragma once

#include "environ.h"

class lambda {
public:
    explicit lambda(const expr &p, const expr &b, const std::shared_ptr<environ> &e);

    expr call(const std::vector<expr> &args) const;

    std::string to_string() const;

private:
    expr _parameters;
    expr _body;
    std::shared_ptr<environ> _env;

    friend bool operator==(const lambda &l1, const lambda &l2);
};

bool operator==(const lambda &l1, const lambda &l2);