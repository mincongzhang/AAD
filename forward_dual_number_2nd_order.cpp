#include <iostream>
#include <stdlib.h> 
#include <assert.h> 

template <typename T>
class Dual
{
    private:
    T m_real; //Real part
    T m_infsimal; //Infinitesimal part
    
    public:
    Dual (T r, T i = 0.0): m_real(r), m_infsimal(i) {}

    T real() const
    {
        return m_real;
    }
    
    T infsimal() const
    {
        return m_infsimal;
    }
    
    T deriv() const
    {
        return m_infsimal;
    }
    
    static Dual<T> create_infsimal_dual()
    {
        return Dual<T>(T(0.0), T(1.0));
    }
};

template <typename T>
Dual<T> operator+(const Dual<T> &x, const Dual<T> &y)
{
    return Dual(x.real() + y.real(), x.infsimal() + y.infsimal());
}

template <typename T>
Dual<T> operator*(const Dual<T> &x, const Dual<T> &y)
{
    return Dual(x.real() * y.real(), x.real() * y.infsimal() + x.infsimal() * y.real());
}

template <typename T>
Dual<T> func_to_deriv(Dual<T> x)
{
    return x*x + Dual<T>(2.0, 0.0) * x ;
}


template <typename T>
T first_order_deriv(Dual<T> x)
{
    Dual<T> res = func_to_deriv(Dual<T>(x) + Dual<T>::create_infsimal_dual());
    return res.deriv();
}

double second_order_deriv(double x)
{
    Dual<double> res = first_order_deriv<Dual<double>>(Dual<double>(x) + Dual<double>::create_infsimal_dual());
    return res.deriv();
}

int main()
{
    Dual<double> d(0.0, 1.0);
    Dual<double> x(3.0);
    Dual<double> y = func_to_deriv<double>(x + d);
    std::cout<<"f(x)=x^2 + 2x, f'(x)=2x+2, f'(3)="<<y.deriv()<<std::endl;   
    assert(std::abs(y.deriv() - 8.0) < 0.0001);
    
    double first_order_d = first_order_deriv<double>(3.0);
    std::cout<<"f(x)=x^2 + 2x, f'(x)=2x+2, f'(3)="<<first_order_d<<std::endl;   
    assert(std::abs(first_order_d - 8.0) < 0.0001);
    
    double second_order_d = second_order_deriv(3.0);
    std::cout<<"f(x)=x^2 + 2x, f'(x)=2, f'(3)="<<second_order_d<<std::endl;   
    assert(std::abs(second_order_d - 2.0) < 0.0001);
    
    return 0;
};
