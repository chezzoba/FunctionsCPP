#include <iostream>
#include "Polynomial.cpp"

using namespace std;

struct Stepfunction {
    Array c, r, e;
    const string s = "z";

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
            int l = e.size;
            for (int i = 0; i < e.size-1; i++) {
                cout << c[i] << "*[ " << s << (r[i] >= 0 ? " +" : " ") << r[i] << " ]^" << e[i] << (c[i+1] >= 0 ? " +" : " ");
            };
            cout << c[l-1] << "[ " << s << (r[l-1] >= 0 ? " +" : " ") << r[l-1] << " ]^" << e[l-1] << endl;
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

        Stepfunction operator+(double p) {
            Stepfunction newsf;
            Array nc;
            bool found = false;
            for (int i=0; i<e.size; i++) {
                if (e[i] == 0 && r[i] == 0) {
                    nc.push(c[i] + p);
                    found = true;
                    break;
                } else {
                    nc.push(c[i]);
                };
            };
            if (found) {newsf.load(nc, r, e);}
            else {newsf.load(c, r, e); newsf.push(p, 0, 0);};
            return newsf;
        };

        Stepfunction derivative( ) {
            Stepfunction d;
            int l = this->c.size;
            for (int i = 0; i < l; i++) {
                d.push(c[i] * e[i], r[i], e[i] - 1);
            };
            return d;
        };
        Stepfunction integral( double C = 0 ) {
            Stepfunction ing;
            int l = this->c.size;
            for (int i = 0; i < l; i++) {
                ing.push(c[i] / ( e[i] + 1 ), r[i], e[i] + 1);
            };
            return ing + C;
        };
};

