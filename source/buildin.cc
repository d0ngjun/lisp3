#include "buildin.h"

typedef expr arith_func(const expr &, const expr &);
typedef bool logic_func(const expr &, const expr &);

static expr buildin_arith(const std::vector<expr> &v, arith_func *f);
static bool buildin_logic(const std::vector<expr> &v, logic_func *f, bool stop);

expr buildin_plus(const std::vector<expr> &v)
{
    return buildin_arith(v, operator+);
}

expr buildin_minus(const std::vector<expr> &v)
{
    return buildin_arith(v, operator-);
}

expr buildin_multiplies(const std::vector<expr> &v)
{
    return buildin_arith(v, operator*);
}

expr buildin_divides(const std::vector<expr> &v)
{
    return buildin_arith(v, operator/);
}

bool buildin_equal(const std::vector<expr> &v)
{
    return buildin_logic(v, operator==, false);
}

bool buildin_less(const std::vector<expr> &v)
{
    return buildin_logic(v, operator<, false);
}

bool buildin_larger(const std::vector<expr> &v)
{
    return buildin_logic(v, operator>, false);
}

bool buildin_and(const std::vector<expr> &v)
{
    return buildin_logic(v, operator&&, false);
}

bool buildin_or(const std::vector<expr> &v)
{
    return buildin_logic(v, operator||, true);
}

bool buildin_not(const std::vector<expr> &v)
{
    // assert v.size() == 1
    return !v.front();
}

std::string buildin_to_string(expr::arith *a)
{
    std::string s;

    if (a == buildin_plus) {
        s = "buildin_plus";
    } else if (a == buildin_minus) {
        s = "buildin_minus";
    } else if (a == buildin_multiplies) {
        s = "buildin_multiplies";
    } else if (a == buildin_divides) {
        s = "buildin_divides";
    } else {
        s = "not a arithmetic function";
    }

    return s;
}

std::string buildin_to_string(expr::logic *l)
{
    std::string s;

    if (l == buildin_equal) {
        s = "buildin_equal";
    } else if (l == buildin_less) {
        s = "buildin_less";
    } else if (l == buildin_larger) {
        s = "buildin_larger";
    } else if (l == buildin_and) {
        s = "buildin_and";
    } else if (l == buildin_or) {
        s = "buildin_or";
    } else if (l == buildin_not) {
        s = "buildin_not";
    } else {
        s = "not a logic function";
    }

    return s;
}

static expr buildin_arith(const std::vector<expr> &v, arith_func *f)
{
    // FIXME: need to indicate error.
    if (v.size() == 0) {
        return expr();
    }

    auto first = v.begin();
    auto end = v.end();

    expr e(*first);

    for (++first; first != end; ++first) {
        e = f(e, *first);
    }

    return e;
}

static bool buildin_logic(const std::vector<expr> &v, logic_func *f, bool stop)
{
    // FIXME: need to indicate error.
    if (v.size() == 0) {
        return true;
    } else if (v.size() == 1) {
        return false;
    }

    auto first = v.begin();
    auto second = first + 1;
    auto end = v.end();
    bool e = !stop;

    for (; second != end && e != stop; first = second++) {
        e = f(*first, *second);
    }

    return e;
}