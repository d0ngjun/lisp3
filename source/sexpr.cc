#include "error.h"
#include "sexpr.h"

sexpr::sexpr(const std::vector<expr> &v) : _exprs(v)
{
}

expr sexpr::eval(const std::shared_ptr<environ> &env) const
{
    if (_exprs.empty()) {
        return expr();
    }

    auto first = _exprs.begin();
    auto end = _exprs.end();
    std::vector<expr> args;
    expr f = first->eval(env);
    for (++first; first != end; ++first) {
        args.push_back(first->eval(env));
    }

    // return args.empty() ? f : f.call(args);
    if (args.empty()) {
        return f;
    } else {
        return f.call(args);
    }
}

expr sexpr::bind(const std::vector<expr> &args, std::shared_ptr<environ> &env) const
{
    expr e;

    if (args.size() == _exprs.size()) {
        for (size_t i = 0; i < args.size(); ++i) {
            // NOTE: expr::eval ensure args are evaluated.
            // FIXME: need add a protection to ensure this them.
            env->put(_exprs[i].to_string(), args[i]);
        }
    } else if (args.size() > _exprs.size()) {
        e = error(BAD_EXPR, "too many arguments");
    } else {
        e = error(BAD_EXPR, "too few arguments");
    }

    return e;
}

expr sexpr::car() const
{
    return _exprs.empty() ? expr() : *_exprs.begin();
}

expr sexpr::cdr() const
{
    return expr(sexpr(std::vector<expr>(_exprs.begin() + 1, _exprs.end())));
}

std::string sexpr::to_string() const
{
    std::string s = "(";

    if (!_exprs.empty()) {
        auto i = _exprs.begin();
        auto last = _exprs.end() - 1;

        for (; i != last; ++i) {
            s += i->to_string() + " ";
        }
        s += i->to_string();
    }

    s += ")";

    return s;
}

bool operator==(const sexpr &s1, const sexpr &s2)
{
    return s1._exprs == s2._exprs;
}
