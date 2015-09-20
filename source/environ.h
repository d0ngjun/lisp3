#ifndef _ENVIRON_H
#define _ENVIRON_H

#include <utility>

#include "expr.h"

using std::pair;

class environ {
public:
    explicit environ(const shared_ptr<environ> &p = NULL);

    expr put(const string &key, const expr &value);
    expr get(const string &key) const;

    string to_string() const;

private:
    vector<pair<string, expr>> _store;
    shared_ptr<environ> _parent;

    friend bool operator==(const environ &e1, const environ &e2);
};

bool operator==(const environ &e1, const environ &e2);

#endif
