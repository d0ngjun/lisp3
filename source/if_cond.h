#ifndef _IF_COND_H
#define _IF_COND_H

#include "environ.h"

class if_cond {
public:
    if_cond(const expr &c, const expr &i, const expr &e);

    expr eval(const shared_ptr<environ> &env) const;

    string to_string() const;

private:
    expr _cond;
    expr _if;
    expr _else;
};

#endif
