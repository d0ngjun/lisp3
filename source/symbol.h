#ifndef _SYMBOL_H
#define _SYMBOL_H

#include "environ.h"

class symbol {
public:
    explicit symbol(const string &s);

    expr eval(const shared_ptr<environ> &env) const;

    string to_string() const;

private:
    const string _name;

    friend bool operator==(const symbol &s1, const symbol &s2);
};

bool operator==(const symbol &s1, const symbol &s2);

#endif
