#pragma once

#include <utility>

#include "expr.h"

class environ {
public:
    explicit environ(const std::shared_ptr<environ> &p = nullptr);

    expr put(const std::string &key, const expr &value);
    expr get(const std::string &key) const;

    std::string to_string() const;

private:
    std::vector<std::pair<std::string, expr>> _store;
    std::shared_ptr<environ> _parent;

    friend bool operator==(const environ &e1, const environ &e2);
};

bool operator==(const environ &e1, const environ &e2);