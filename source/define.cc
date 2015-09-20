#include "define.h"
#include "lisp.h"

define::define(const expr &n, const expr &v, const shared_ptr<environ> &e) : _name(n.to_string()), _value(v), _env(e)
{
}

expr define::eval() const
{
    lisp::env->put(_name, _value.eval(_env));
    return expr();
}

string define::to_string() const
{
    return "define " + _name + " " + _value.to_string();
}
