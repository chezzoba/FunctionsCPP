#include <iostream>
#include "Polynomial.hpp"

using namespace std;

struct Stepfunction {
    Array c, r, e;
    string s;

    Stepfunction (string symbol = "z") {
        s = symbol;
    };

    void load( Array coefs, Array roots, Array exps ) {
            for (int i = 0; i < coefs.size; i++) {
                if (coefs[i] != 0) {
                    c.push(coefs[i]);
                    r.push(roots[i]);
                    e.push(exps[i]);
                };
            };
        };
        void print( ) {
            cout << this->str() << endl;
        };

        string str( ) {
            stringstream out;
            int l = e.size;
            for (int i = 0; i < e.size-1; i++) {
                out << c[i] << "*[ " << s << (r[i] >= 0 ? " +" : " ") << r[i] << " ]^" << e[i] << (c[i+1] >= 0 ? " +" : " ");
            };
            out << c[l-1] << "[ " << s << (r[l-1] >= 0 ? " +" : " ") << r[l-1] << " ]^" << e[l-1];
            return out.str();
        };

        double operator()(double x) {
            double sum = 0;
            for (int i=0; i<c.size; i++) {
                sum += c[i] * (x <= r[i] ? 0 : pow(x - r[i], e[i]));
            };
            return sum;
        };

        void push(double coef, double root, double exp) {
            c.push(coef); r.push(root); e.push(exp);
        };

        Stepfunction operator+ (Stepfunction b) {
            Stepfunction f(s);
            f.load(this->c, this->r, this->e);
            f.load(b.c, b.r, b.e);
            return f;
        };

        Stepfunction operator* (double a) {
            Stepfunction f(s);
            Array newc;
            for (int i = 0; i < c.size; i++) {
                newc.push(c[i] * a);
            };
            f.load(newc, r, e);
            return f;
        };

        Stepfunction operator/ (double a) {
            return *this * (1 / a);
        };

        Stepfunction operator-() {
            Stepfunction newf(this->s);
            newf.load(c.map([](double co){return -co;}), r, e);
            return newf;
        };

        Stepfunction operator+(double p) {
            Stepfunction newsf(s);
            Array nc;
            bool found = false;
            for (int i=0; i<e.size; i++) {
                if (e[i] == 0 && r[i] == 0) {
                    nc.push(c[i] + p);
                    found = true;
                } else {
                    nc.push(c[i]);
                };
            };
            if (found) {newsf.load(nc, r, e);}
            else {newsf.load(c, r, e); newsf.push(p, 0, 0);};
            return newsf;
        };

        Stepfunction derivative( ) {
            Stepfunction d(s);
            int l = this->c.size;
            for (int i = 0; i < l; i++) {
                d.push(c[i] * e[i], r[i], e[i] - 1);
            };
            return d;
        };
        Stepfunction integral( double C = 0 ) {
            Stepfunction ing(s);
            int l = this->c.size;
            for (int i = 0; i < l; i++) {
                ing.push(c[i] / ( e[i] + 1 ), r[i], e[i] + 1);
            };
            ing.push(C, 0, 0);
            return ing;
        };
};