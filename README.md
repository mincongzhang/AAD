# Automatic Differentiation - Proof of Concept

## Forward Mode - Using Dual Number

First order example for $f(x)=(x+2)(x+1)$:

```
Dual func_to_deriv(Dual x)
{
    return (x + Dual(2.0, 0.0)) * (x + Dual(1.0, 0.0));
}

int main()
{
    Dual d(0.0, 1.0);
    Dual x(3.0);
    Dual y = func_to_deriv(x + d);
    
    assert(std::abs(y.deriv() - 9.0) < 0.0001);
    
    return 0;
};
```

First and second order example for $f(x)=x^2 + 2x$:

```
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
```

## Backward Mode - Using Expression Tree and Back Propagation

Example for $z = xy + sinx$:
```

int main()
{
    Var x;
    Var y;
    
    Var xy = x*y;
    Var sinx = Var::sin(x);
    
    Var z = xy + sinx;
    
    x.setVal(2);
    y.setVal(4);
    
    assert(std::abs(z.val() - 8.9093) < 0.0001);
    assert(std::abs(z.derivOn(x) - 3.58385) < 0.001);
    assert(std::abs(z.derivOn(y) - 2) < 0.001);

    return 0;
}
```

## References

https://web.archive.org/web/20050315101043/http://homepage.mac.com/sigfpe/paper.pdf

Dan Piponi (2004) Automatic Differentiation, C++ Templates, and Photogrammetry, Journal of Graphics Tools, 9:4, 41-55, DOI: 10.1080/10867651.2004.10504901

https://github.com/autodiff/autodiff

https://sidsite.com/posts/autodiff/

https://jingnanshi.com/blog/autodiff.html

https://www.cs.toronto.edu/~rgrosse/courses/csc2541_2022/tutorials/tut01.pdf

https://www.cs.toronto.edu/~rgrosse/courses/csc321_2018/slides/lec10.pdf

## Forward Mode Detail Explain

https://github.com/mincongzhang/AAD/blob/main/aad_forward_mode_detail.md
