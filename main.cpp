#include <iostream>
#include "Mechanics.cpp"

using namespace std;

int main ( ) {
    //Polynomial squared(1, 1);
    Array coefs, roots, exps;
    for (int i=0; i<5; i++) {
        coefs.push(9-5*i);
        roots.push(5*i-1);
        exps.push(i);
    }
    string symbol="y";
    Polynomial powers(1, 1, symbol);
    powers.load(coefs);
    powers.print();
    powers.derivative().print();
    cout << endl << endl;

    Stepfunction My;
    My.load(coefs, roots, exps);
    My.print();
    (My+5).print();
    My.integral(-7).print();
    return EXIT_SUCCESS;
}