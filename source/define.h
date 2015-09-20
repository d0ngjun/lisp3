#ifndef _DEFINE_H
#define _DEFINE_H

#include "environ.h"

class define {
public:
    explicit define(const expr &n, const expr &v, const shared_ptr<environ> &e);

    expr eval() const;

    string to_string() const;

private:
    string _name;
    expr _value;
    shared_ptr<environ> _env;
};

#endif
