#include <algorithm>

#include "environ.h"

environ::environ(const std::shared_ptr<environ> &p) : _parent(p)
{
}

expr environ::put(const std::string &key, const expr &value)
{
    auto i = find_if(_store.begin(), _store.end(), [&key](std::pair<std::string, expr> v) {
        return v.first == key;
    });
    if (i == _store.end()) {
        _store.push_back(make_pair(key, value));
    } else {
        *i = make_pair(key, value);
    }

    return expr();
}

expr environ::get(const std::string &key) const
{
    expr e = error(BAD_SYMBOL, key + " is not defined");
    auto i = find_if(_store.begin(), _store.end(), [&key](std::pair<std::string, expr> v) {
        return v.first == key;
    });
    if (i != _store.end()) {
        e = i->second;
    } else if (_parent != NULL) {
        e = _parent->get(key);
    }

    return e;
}

std::string environ::to_string() const
{
    std::string s;

    for (auto e : _store) {
        s += e.first + " = " + e.second.to_string() + "\n";
    }

    s += "\n";

    if (_parent != NULL) {
        s += _parent->to_string();
    }

    return s;
}

bool operator==(const environ &e1, const environ &e2)
{
    return e1._store == e2._store && *e1._parent == *e2._parent;
}
