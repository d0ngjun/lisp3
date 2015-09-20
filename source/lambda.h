#ifndef _LAMBDA_H
#define _LAMBDA_H

#include "environ.h"

class lambda {
public:
    explicit lambda(const expr &p, const expr &b, const shared_ptr<environ> &e);

    expr call(const vector<expr> &args) const;

    string to_string() const;

private:
    expr _parameters;
    expr _body;
    shared_ptr<environ> _env;

    friend bool operator==(const lambda &l1, const lambda &l2);
};

bool operator==(const lambda &l1, const lambda &l2);

#endif
