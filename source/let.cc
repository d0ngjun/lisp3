#include "let.h"

let::let(const expr &n, const expr &v, const expr &e, const shared_ptr<environ> &env) : _name(n.to_string()), _value(v), _expr(e), _env(env)
{
}

expr let::eval() const
{
    shared_ptr<environ> local(new environ(_env));
    local->put(_name, _value.eval(_env));

    return _expr.eval(local);
}

string let::to_string() const
{
    string s = "let " + _name + " " + _value.to_string();
    s += _expr == expr() ? "" : " " + _expr.to_string();

    return s;
}
