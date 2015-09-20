#ifndef _LET_H
#define _LET_H

#include "environ.h"

class let {
public:
    explicit let(const expr &n, const expr &v, const expr &e, const shared_ptr<environ> &env);

    expr eval() const;

    string to_string() const;

private:
    string _name;
    expr _value;
    expr _expr;
    shared_ptr<environ> _env;
};

#endif
