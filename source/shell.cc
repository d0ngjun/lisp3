#include <cctype>
#include <fstream>
#include <iostream>

#include "lisp.h"

using std::cin;
using std::endl;
using std::ifstream;
using std::isspace;
using std::istream;
using std::cout;
using std::string;

// return complete s-expression or a simple symbol.
static string read(istream &is);
static string eval(lisp &l, const string &s);
static bool is_newline(char c);
static bool is_comment(char c);

int main(int argc, char *argv[])
{
    bool interactive = argc == 1;
    ifstream ifs(argv[1]);
    istream &is = interactive ? cin : ifs;

    lisp l;

    for (;;) {
        if (interactive) {
            cout << "> ";
        }

        string s = read(is);
        if (s.empty()) {
            break;
        }

        s = eval(l, s);

        if (!s.empty()) {
            cout << s << endl;
        }
    }

    return 0;
}

static string read(istream &is)
{
    string s;
    int pars = 0;
    char c;

    while ((c = is.get()) != EOF) {
        if (isspace(c) || is_newline(c)) {
            if (s.empty()) {
                continue;
            } else if (pars == 0) {
                break;
            } else {
                c = ' ';
            }
        } else if (is_comment(c)) {
            // only support one line comment.
            do {
                c = is.get();
            } while (!is_newline(c));
            is.unget();

            continue;
        } else if (c == '(') {
            if (!s.empty() && pars == 0) {
                is.unget();
                break;
            } else {
                ++pars;
            }
        } else if (c == ')') {
            --pars;
        }

        s += c;
    }

    return s;
}

static string eval(lisp &l, const string &s)
{
    expr e = l.make_expr(s);

    return e.eval(lisp::env).to_string();
}

static bool is_newline(char c)
{
    return c == '\n' || c == '\r';
}

static bool is_comment(char c)
{
    // # is for shell mode use.
    return c == ';' || c == '#';
}
