#include <algorithm>
#include <sstream>

#include "buildin.h"
#include "define.h"
#include "environ.h"
#include "if_cond.h"
#include "lambda.h"
#include "let.h"
#include "sexpr.h"
#include "symbol.h"

expr::expr() : _type(EMPTY)
{
}

expr::expr(arith *a) : _type(ARITH), _arith(a)
{
}

expr::expr(logic *l) : _type(LOGIC), _logic(l)
{
}

expr::expr(const bool b) : _type(BOOLEAN), _boolean(b)
{
}

expr::expr(const long n) : _type(NUMBER), _number(n)
{
}

expr::expr(const char *s) : _type(STRING), _string(new std::string(s))
{
}

expr::expr(const define &d) : _type(DEFINE), _define(new define(d))
{
}

expr::expr(const let &l) : _type(LET), _let(new let(l))
{
}

expr::expr(const if_cond &i) : _type(IF), _if_cond(new if_cond(i))
{
}

expr::expr(const lambda &l) : _type(LAMBDA), _lambda(new lambda(l))
{
}

expr::expr(const symbol &s) : _type(SYMBOL), _symbol(new symbol(s))
{
}

expr::expr(const sexpr &s) : _type(SEXPR), _sexpr(new sexpr(s))
{
}

expr::expr(const error &e) : _type(ERROR), _error(new error(e))
{
}

expr::expr(const expr &e) : _type(e._type)
{
    switch (_type) {
    case ARITH:
        _arith = e._arith;
        break;
    case LOGIC:
        _logic = e._logic;
        break;
    case BOOLEAN:
        _boolean = e._boolean;
        break;
    case NUMBER:
        _number = e._number;
        break;
    case STRING:
        _string = new std::string(*e._string);
        break;
    case DEFINE:
        _define = new define(*e._define);
        break;
    case LET:
        _let = new let(*e._let);
        break;
    case IF:
        _if_cond = new if_cond(*e._if_cond);
        break;
    case LAMBDA:
        _lambda = new lambda(*e._lambda);
        break;
    case SYMBOL:
        _symbol = new symbol(*e._symbol);
        break;
    case SEXPR:
        _sexpr = new sexpr(*e._sexpr);
        break;
    case ERROR:
        _error = new error(*e._error);
        break;
    default: // EMPTY
        break;
    }
}

expr::~expr()
{
    switch (_type) {
    case STRING:
        delete _string;
        break;
    case DEFINE:
        delete _define;
        break;
    case LET:
        delete _let;
        break;
    case IF:
        delete _if_cond;
        break;
    case LAMBDA:
        delete _lambda;
        break;
    case SYMBOL:
        delete _symbol;
        break;
    case SEXPR:
        delete _sexpr;
        break;
    case ERROR:
        delete _error;
        break;
    default: // empty or number or arith or logic
        break;
    }
}

expr &expr::operator=(const expr &e)
{
    if (this != &e) {
        expr f(e);

        std::swap(_type, f._type);
        // _number is long enough.
        std::swap(_number, f._number);
    }

    return *this;
}

expr expr::eval(const std::shared_ptr<environ> &env) const
{
    expr e;

    switch (_type) {
    case DEFINE:
        e = _define->eval();
        break;
    case LET:
        e = _let->eval();
        break;
    case IF:
        e = _if_cond->eval(env);
        break;
    case SYMBOL:
        e = _symbol->eval(env);
        break;
    case SEXPR:
        e = _sexpr->eval(env);
        break;
    // empty or arith or logic or boolean or number or define or lambda
    default:
        e = *this;
        break;
    }

    return e;
}

expr expr::call(const std::vector<expr> &arguments) const
{
    expr e;

    switch (_type) {
    case ARITH:
        e = _arith(arguments);
        break;
    case LOGIC:
        e = expr(_logic(arguments));
        break;
    case LAMBDA:
        e = _lambda->call(arguments);
        break;
    default:
        e = error(BAD_TYPE, to_string());
        break;
    }

    return e;
}

expr expr::bind(const std::vector<expr> &args, std::shared_ptr<environ> &env) const
{
    return _type == SEXPR ? _sexpr->bind(args, env) : error(BAD_TYPE, to_string());
}

bool expr::failed() const
{
    return _type == ERROR;
}

bool expr::to_boolean() const
{
    // other type will considered as false.
    return _type == BOOLEAN && _boolean;
}

std::string expr::to_string() const
{
    std::string s;
    std::ostringstream ss;

    switch (_type) {
    case ARITH:
        s = buildin_to_string(_arith);
        break;
    case LOGIC:
        s = buildin_to_string(_logic);
        break;
    case BOOLEAN:
        s = _boolean ? "#t" : "#f";
        break;
    case NUMBER:
        ss << _number;
        s = ss.str();
        break;
    case STRING:
        s = *_string;
        break;
    case DEFINE:
        s = _define->to_string();
        break;
    case LET:
        s = _let->to_string();
        break;
    case IF:
        s = _if_cond->to_string();
        break;
    case LAMBDA:
        s = _lambda->to_string();
        break;
    case SYMBOL:
        s = _symbol->to_string();
        break;
    case SEXPR:
        s = _sexpr->to_string();
        break;
    case ERROR:
        s = _error->to_string();
        break;
    default: // empty
        break;
    }

    return s;
}

expr operator+(const expr &e1, const expr &e2)
{
    if (e1._type != NUMBER || e2._type != NUMBER) {
        return error(BAD_TYPE, "e1 = " + e1.to_string() + ", e2 = " + e2.to_string());
    }

    return expr(e1._number + e2._number);
}

expr operator-(const expr &e1, const expr &e2)
{
    if (e1._type != NUMBER || e2._type != NUMBER) {
        return error(BAD_TYPE, "e1 = " + e1.to_string() + ", e2 = " + e2.to_string());
    }

    return expr(e1._number - e2._number);
}

expr operator*(const expr &e1, const expr &e2)
{
    if (e1._type != NUMBER || e2._type != NUMBER) {
        return error(BAD_TYPE, "e1 = " + e1.to_string() + ", e2 = " + e2.to_string());
    }

    return expr(e1._number * e2._number);
}

expr operator/(const expr &e1, const expr &e2)
{
    if (e1._type != NUMBER || e2._type != NUMBER) {
        return error(BAD_TYPE, "e1 = " + e1.to_string() + ", e2 = " + e2.to_string());
    }

    return expr(e1._number / e2._number);
}

bool operator==(const expr &e1, const expr &e2)
{
    if (e1._type != e2._type) {
        return false;
    }

    bool e;

    switch (e1._type) {
    case EMPTY:
        e = true;
        break;
    case ARITH:
    case LOGIC:
    case BOOLEAN:
    case NUMBER:
        e = e1._number == e2._number;
        break;
    case STRING:
        e = *e1._string == *e2._string;
        break;
    case LAMBDA:
        e = *e1._lambda == *e2._lambda;
        break;
    case SYMBOL:
        e = *e1._symbol == *e2._symbol;
        break;
    case SEXPR:
        e = *e1._sexpr == *e2._sexpr;
        break;
    case ERROR:
        e = *e1._error == *e2._error;
        break;
    default:
        e = false;
        break;
    }

    return e;
}

bool operator!=(const expr &e1, const expr &e2)
{
    return !(e1 == e2);
}

bool operator<(const expr &e1, const expr &e2)
{
    if (e1._type != NUMBER || e2._type != NUMBER) {
        return false;
    }

    return e1._number < e2._number;
}

bool operator>(const expr &e1, const expr &e2)
{
    if (e1._type != NUMBER || e2._type != NUMBER) {
        return false;
    }

    return e1._number > e2._number;
}

bool operator&&(const expr &e1, const expr &e2)
{
    if (e1._type != BOOLEAN || e2._type != BOOLEAN) {
        return false;
    }

    return e1._boolean && e2._boolean;
}

bool operator||(const expr &e1, const expr &e2)
{
    if (e1._type != BOOLEAN || e2._type != BOOLEAN) {
        return false;
    }

    return e1._boolean || e2._boolean;
}

bool operator!(const expr &e)
{
    if (e._type != BOOLEAN) {
        return false;
    }

    return !e._boolean;
}
