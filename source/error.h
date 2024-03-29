#pragma once

#include <string>

enum error_reason {
    DIVIDE_ZERO,
    BAD_TAG,
    BAD_TYPE,
    BAD_NUMBER,
    BAD_OPERATER,
    BAD_SYMBOL,
    BAD_EXPR,
    PARSER_ERROR,
};

class error {
public:
    explicit error(error_reason r, const std::string &d = "");

    std::string to_string() const;

private:
    error_reason reason;
    std::string detail;
};