#include <iostream>
#include <stdlib.h> 

class Dual
{
    private:
    double m_real; //Real part
    double m_inf_simal; //Infinitesimal part
    
    public:
    Dual (double r, double i = 0.0): m_real(r), m_inf_simal(i) {}

    double real() const
    {
        return m_real;
    }
    
    double infsimal() const
    {
        return m_inf_simal;
    }
    
    double deriv() const
    {
        return m_inf_simal;
    }
};

Dual operator+(const Dual &x, const Dual &y)
{
    return Dual(x.real() + y.real(), x.infsimal() + y.infsimal());
}

Dual operator*(const Dual &x, const Dual &y)
{
    return Dual(x.real() * y.real(), x.real() * y.infsimal() + x.infsimal() * y.real());
}

Dual func_to_deriv(Dual x)
{
    return (x + Dual(2.0, 0.0)) * (x + Dual(1.0, 0.0));
}

int main()
{
    Dual d(0.0, 1.0);
    Dual x(3.0);
    Dual y = func_to_deriv(x + d);
    
    std::cout<<y.deriv()<<std::endl;   
    return 0;
};
