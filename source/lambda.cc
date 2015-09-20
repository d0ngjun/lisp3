#include "error.h"
#include "lambda.h"

lambda::lambda(const expr &p, const expr &b, const shared_ptr<environ> &e) : _parameters(p), _body(b), _env(e)
{
}

expr lambda::call(const vector<expr> &args) const
{
    // generate a new environment for eval.
    shared_ptr<environ> local(new environ(_env));
    expr e = _parameters.bind(args, local);

    return e.failed() ? e : _body.eval(local);
}

string lambda::to_string() const
{
    return "lambda " + _parameters.to_string() + " " + _body.to_string();
}

bool operator==(const lambda &l1, const lambda &l2)
{
    return l1._parameters == l2._parameters && l1._body == l2._body && l1._env == l2._env;
}
