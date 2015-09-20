#include "error.h"

error::error(error_reason r, const string &d) : reason(r), detail(d)
{
}

string error::to_string() const
{
    string s;

    switch(reason) {
    case DIVIDE_ZERO:
        s += "[DIVIDE_ZERO]: ";
        break;
    case BAD_TAG:
        s += "[BAD_TAG]: ";
        break;
    case BAD_TYPE:
        s += "[BAD_TYPE]: ";
        break;
    case BAD_NUMBER:
        s += "[BAD_NUMBER]: ";
        break;
    case BAD_OPERATER:
        s += "[BAD_OPERATOR]: ";
        break;
    case BAD_SYMBOL:
        s += "[BAD_SYMBOL]: ";
        break;
    case BAD_EXPR:
        s += "[BAD_EXPR]: ";
        break;
    case PARSER_ERROR:
        s += "[PARSER_ERROR]: ";
        break;
    default:
        s += "[UNKNOWN]: ";
        break;
    }

    if (!detail.empty()) {
        s += detail;
    }

    return s;
}
