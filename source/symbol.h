#pragma once

#include "environ.h"

class symbol {
public:
    explicit symbol(const std::string &s);

    expr eval(const std::shared_ptr<environ> &env) const;

    std::string to_string() const;

private:
    const std::string _name;

    friend bool operator==(const symbol &s1, const symbol &s2);
};

bool operator==(const symbol &s1, const symbol &s2);