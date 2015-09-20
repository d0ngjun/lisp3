#include "if_cond.h"

if_cond::if_cond(const expr &c, const expr &i, const expr &e) : _cond(c), _if(i), _else(e)
{
}

expr if_cond::eval(const shared_ptr<environ> &env) const
{
    expr e = _cond.eval(env);
    if (e.failed()) {
        return e;
    }

    return e.to_boolean() ? _if.eval(env) : _else.eval(env);
}

string if_cond::to_string() const
{
    string s = "if " + _cond.to_string() + " " + _if.to_string();
    s += _else == expr() ? "" : " " + _else.to_string();

    return s;
}
