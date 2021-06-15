# distutils: language = c++
from libcpp.string cimport string

cdef extern from "Mechanics.hpp":
    cdef cppclass Stepfunction:
        Stepfunction(string) except +
        Stepfunction() except +
        void push(double coef, double root, double exp)
        void print()
        double& get "operator()"(double)
        Stepfunction derivative()
        Stepfunction integral(double)
        Stepfunction operator+(Stepfunction)
        Stepfunction operator-()
        Stepfunction& mul "operator*"(double)
        Stepfunction& div "operator/"(double)
        string str()

cdef class StepFunction:
    cdef Stepfunction sf, othersf
    def __cinit__(self, list arr = [[0]*3], str symbol = "z"):
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
        return self.sf.str().decode('utf-8')
    __repr__ = __str__

    @staticmethod
    cdef create(Stepfunction sfn):
        fn = StepFunction()
        fn.sf = sfn
        return fn

    def __add__(StepFunction left, StepFunction right):
        return StepFunction.create(left.sf + right.sf)

    __radd__ = __add__

    def derivative(self):
        return StepFunction.create(self.sf.derivative())
    
    def integral(self, double C = 0):
        newsf = StepFunction()
        newsf.sf = self.sf.integral(C)
        return newsf
    def __neg__(self):
        return StepFunction.create(-self.sf)
    def __sub__(StepFunction left, StepFunction right):
        return StepFunction.create(left.sf + (-right.sf))
    def __rsub__(StepFunction left, StepFunction right):
        return StepFunction.create(-left.sf + right.sf)
    def __mul__(StepFunction a, double b):
        return StepFunction.create(a.sf.div(b))
    __rmul__ = __mul__

    def __truediv__(StepFunction a, double b):
        return StepFunction.create(a.sf.div(b))