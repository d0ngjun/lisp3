#include "symbol.h"

symbol::symbol(const string &n) : _name(n)
{
}

expr symbol::eval(const shared_ptr<environ> &env) const
{
    expr e = env->get(_name);

    return e.failed() ? expr(*this) : e;
}

string symbol::to_string() const
{
    return _name;
}

bool operator==(const symbol &s1, const symbol &s2)
{
    return s1._name == s2._name;
}
