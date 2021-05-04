#include <iostream>
#include "makedic.cpp"

using namespace std;

double pow (double base, double exp) {
    double prod = 1;
    for (int i = 0; i < int(exp); i++) {
        prod *= base;
    };
    return prod;
};

struct Polynomial  {
    double f, c;
        Array<double> arr;
        Polynomial (double freq, double coef) {
        f = freq; c = coef;
        };
        double operator()(double x) {
            double sum = 0;
            for (int i=0; i<arr.size; i++) {
                sum += arr[i] * pow(x*f, i);
            };
            return c * sum;
        };
        void push(double term) {
            arr.push(term);
        };
        void load(Array<double> aray) {
            for (int i = 0; i < aray.size; i++) {
                arr.push(aray[i]);
            };
        };
        void print() {
            if (c != 1) {
                cout << c << "*[";
            } else {
                cout << (c == 1 ? "" : "[");
            };
            if (arr[0] != 0) {
                cout << arr[0] << " + ";
            };
            for (int i=1; i<arr.size-1; i++) {
                if (arr[i] != 0) {
                    printf("%f*(%f*x)^%d + ", arr[i], f, i);
                };
            };
            printf("%f*(%f*x)^%d", arr[arr.size-1], f, arr.size-1);
            cout << ( c == 1 ? "" : "]") << "\n";
        };

        Polynomial derivative() {
            Polynomial newpol(this->f, (this->c)*(this->f));
            for (int i=1; i <arr.size; i++) {
                newpol.push((i * arr[i]));
            };
            return newpol;
        };

        Polynomial integral(double C) {
            Polynomial newpol(this->f, (this->c)*(this->f));
            newpol.push(C * (this->f) / (this->c));
            for (int i = 0; i < arr.size; i++) {
                newpol.push(arr[i] / (i + 1));
            };
            return newpol;
        };
        double dintegral(double a, double b) {
            return (this->integral(0))(b) - (this->integral(0))(a);
        };
        Polynomial operator+(double p) {
            Polynomial newpol(this->f, (this->c));
            newpol.push(p * (this->f) / (this->c)); 
            newpol.load(arr.slice(1, arr.size));
            return newpol;
        };

        Polynomial operator*(double p) {
            Polynomial newpol(this->f, p * (this->c));
            newpol.load(arr);
            return newpol;
        };

        Polynomial operator/(double p) {
            Polynomial newpol(this->f, (this->c) / p);
            newpol.load(arr);
            return newpol;
        };
        Polynomial operator-() {
            Polynomial newpol(this->f, -(this->c));
            newpol.load(arr);
            return newpol;
        };
};

Polynomial operator+(double a, Polynomial poly) {
    return poly + a;
};

Polynomial operator*(double a, Polynomial poly) {
    return poly * a;
};

Polynomial operator-(Polynomial poly, double p) {
    return poly + (-p);
};

Polynomial operator-(double p, Polynomial poly) {
    return p + (-poly);
};

Polynomial operator+(Polynomial poly1, Polynomial poly2) {
    int max = poly2.arr.size < poly1.arr.size ? poly1.arr.size : poly2.arr.size;
    Polynomial sum(1, 1); double val1, val2;
    for (int i=0; i<max; i++) {
        val1 = i > poly1.arr.size ? 0 : poly1.arr[i]*poly1.c*pow(poly1.f, i);
        val2 = i > poly2.arr.size ? 0 : poly2.arr[i]*poly2.c*pow(poly2.f, i);
        sum.push(val1 + val2);
    };
    return sum;
};
