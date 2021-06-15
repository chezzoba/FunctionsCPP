# distutils: language = c++
from libcpp.string cimport string

cdef extern from "Mechanics.hpp":
    cdef cppclass Stepfunction:
        Stepfunction(string) except +
        Stepfunction() except +
        void push(double coef, double root, double exp)
        void print()
        double& get "operator()"(double)
        Stepfunction operator+(double)
        Stepfunction derivative()
        Stepfunction integral(double)
        string str()

cdef class StepFunction:
    cdef Stepfunction sf
    def __cinit__(self, list arr = [[0, 1, 1]], str symbol = "z"):
        self.sf = Stepfunction(symbol.encode())
        for c, r, e in arr:
            self.sf.push(c, r, e)
    def push(self, double coef, double root, double exp):
        self.sf.push(coef, root, exp)
    def print(self):
        self.sf.print()
    def __call__(self, double z):
        return self.sf.get(z)
    def __str__(self):
        return self.sf.str()
    __repr__ = __str__
    def __add__(self, double other):
        newsf = StepFunction()
        newsf.push(other, 0, 0)
        return newsf
    __radd__ = __add__

    def derivative(self):
        newsf = StepFunction()
        newsf.sf = self.sf.derivative()
        return newsf
    
    def integral(self, double C = 0):
        newsf = StepFunction()
        newsf.sf = self.sf.integral(C)
        return newsf