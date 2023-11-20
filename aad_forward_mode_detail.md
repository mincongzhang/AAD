# Automatic Differentiation - Forward Mode

### Background - Differential calculus and derivatives

There are a number of methods for writing software to compute derivatives of functions and their approximations: 

1. derive symbolic expressions for the derivative manually and then directly code the resulting expressions
2. finite differences
3. automatic differentiation, which provides a way to compute multiple derivatives of highly complex functions efficiently and accurately

### Background - Two classic approaches to computing derivatives

#### 1. Symbolic Expression

Derive a symbolic expression for the derivative manually and then directly code the resulting expression might be the most popular approach to computing derivatives. 

For example, suppose we know how to compute the derivatives of the functions $f$ and $g$.

$$
\begin{aligned}
y  &= f(x)    \\
z  &= g(x, y)
\end{aligned}
$$

We can use the chain rule to get the derivatives:

$$
\begin{aligned}
y' &= f'(x)   \\
z' &= \frac{\partial g(x, y)}{\partial x} + y' \frac{\partial g(x, y)}{\partial y}
\end{aligned}
$$

Ultimately we get the differentiable expressions and we can compute derivatives. This is straightforward and intuitive. But the disadvantages would be:

(1)It could be tedious and error prone if we have multiple variables and complicated function

(2)Every modification to the function must be repeated in differential form

e.g. if we have 1000 variables and a functions with 1000 chains then it could be almost impossible to manually get the derivitives. We could of course try to use some tool like a derivative calculator to get the derivitives and then code the expressions, but this complicates the build process and put constrains on coding styles.  

#### 2. Finite Differences

By definition, the derivative of a function $f$, written $`f'(x)`$ or $\frac{df}{dx}$ is defined by 

$$f'(x) = \lim_{\delta \to 0} \frac{f(x+\delta) - f(x)}{\delta}$$

In this equation we can choose $\delta$ to be a small value, rather than take the limit as it approaches zero, and compute $\frac{f(x+\delta) - f(x)}{\delta}$. This is an approximation
to $`f'(x)`$ known as the __forward difference__.

There is some difficulty associated with choosing a suitable value for $\delta$. Too large and the approximation to the definition of the derivative is poor. Too small and we can expect the result to be dominated by rounding errors. 

We can improve the accuracy using __central differences__, i.e. $\frac{f(x+\delta) - f(x-\delta)}{2\delta}$, but the errors can still be large. 

Note that this also requires two seperate evaluations of $f$. If we generalise this method to compute $n$ partial derivatives of a function then we can expect to require $n+1$ separate computations of $f$.

### Automatic Differentiation Forward Mode - Dual Numbers

Let's check the equation again:

$$f'(x) = \lim_{\delta \to 0} \frac{f(x+\delta) - f(x)}{\delta}$$

And look at the following example:

$$f(x) = 2x^2 + 1$$

Let's set $\delta = d$, a small non-zero number, then the approximation to $`f'(x)`$ is given by:

$$f'(x) = \lim_{\delta \to 0} \frac{f(x+\delta) - f(x)}{\delta} = \frac{4dx + 2d^2}{d} = \frac{4dx}{d} + \frac{2d^2}{d} = 4x + \frac{2d^2}{d} $$

The exact derivative is $4x$ so we have an error term $\frac{2d^2}{d}$. If $d^2$ is small compared to $d$ then the error becomes small and the approximation approaches the true value of the derivative. Ultimately, if $d^2$ were zero then we could compute the derivative as $4x$ exactly. 

But unfortunately the only choice for a real number $d$ such that $d^2 = 0$ is $d=0$. $d$ is the denominator so if we set $d=0$ then the whole computation is meaningless. How do we find a non-zero number $d$ such that $d^2=0$?

#### Introduce Dual Numbers

It's the time we introduce the __dual numbers__. It's similar to the concept of complex numbers, where we have the equation $x^2 + 1 = 0$ and we define the imaginary number $i$ with the property $i^2 = -1$. We extend the real numbers by adding a new infinitesimal variable $d$, with the property that $d^2 = 0$ but $d \neq 0$. And some additional properties like commutativity so that $a \times d = d \times a$, and $a+d = d+a$ for any real number $a$. 

So now we can have the equation as:


$$f'(x)   = \lim_{\delta \to 0} \frac{f(x+\delta) - f(x)}{\delta} =  \frac{f(x+d) - f(x)}{d}$$  

$$f(x+d)  =  f(x) + d f'(x)$$


And for our example $f(x) = 2x^2 + 1$, remember with the dual number definition we have $d^2 = 0$ but $d \neq 0$, and commutativity $a \times d = d \times a$, $a+d = d+a$:

$$
\begin{aligned}
f(x+d)  &=  2(x+d)^2 + 1 \\
          &=  2(x^2 + 2xd + d^2) + 1 \\
          &=  2x^2 + 4xd + 2d^2+ 1 \\
          &=  2x^2 + 4xd + 2 \times 0 + 1 \\
          &=  2x^2 + 4xd + 1 \\
          &=  (2x^2 + 1)  + d \times 4x = f(x) + d f'(x)
\end{aligned}
$$

So we can read off the derivative of $`f(x)`$ as the coefficient of $d$, i.e. 

$$f'(x) = 4x$$

And that is the same as what we can derive manually.   

Consider another example, $f(x) = x^n$. With Binomial theorem and $d^2 = 0$ but $d \neq 0$, we have

$$
\begin{aligned}
f(x+d)  &=  (x+d)^n \\
          &=  \binom{n}{0} x^{n} d^{0}  + \binom{n}{1} x^{n-1} d^{1} + \binom{n}{2} x^{n-2} d^{2} + ... + \binom{n}{n-1} x^{1} d^{n-1} + \binom{n}{n} x^{0} d^{n} \\
          &=  \binom{n}{0} x^{n} d^{0}  + \binom{n}{1} x^{n-1} d^{1} + d^2 \left[ \binom{n}{2} x^{n-2} + ... + \binom{n}{n-1} x^{1} d^{n-1 - 2} + \binom{n}{n} x^{0} d^{n-2}  \right] \\
          &=  \binom{n}{0} x^{n} d^{0}  + \binom{n}{1} x^{n-1} d^{1} + 0 \times \left[ \binom{n}{2} x^{n-2} + ... + \binom{n}{n-1} x^{1} d^{n-1 - 2} + \binom{n}{n} x^{0} d^{n-2}  \right] \\
          &=  \binom{n}{0} x^{n} d^{0}  + \binom{n}{1} x^{n-1} d
\end{aligned}
$$

So we can read off the derivative of $`f(x)`$ as the coefficient of $d$, i.e. 

$$f'(x) = \binom{n}{1} x^{n-1} = \frac{n!}{1!(n-1)!} x^{n-1} = n x^{n-1}$$

That is also the same as what we can derive manually.   

We now have a strategy for computing derivatives: perform all of our function evaluations over the real numbers extended by infinitesimal $d$ and read off the derivateive from the final coefficient of $d$. These extended numbers are called __dual numbers__.

### Automatic Differentiation Forward Mode - Dual Number Implementation

Let's think about how do we implement dual numbers. The implementation is in fact very similiar to the implementation of complex numbers as a class. We can write a dual number in the following form for real numbers $r$ and $i$:

$$r + i d$$

We call $r$ the real part and $i$ the infinitesimal part.

We can now define the class by

```
class Dual
{
    private:
    double m_real; //Real part
    double m_infsimal; //Infinitesimal part
    
    public:
    Dual (double r, double i = 0.0): m_real(r), m_infsimal(i) {}
};
```

Now we just need to consider some dual number calculation rules.

#### Addition And Subtraction

Two dual numbers addition and subtraction:

$$(r_0 + i_0  d ) + (r_1 + i_1 d ) = ( r_0 + r_1 ) + ( i_0 + i_1 ) d$$

$$(r_0 + i_0  d ) - (r_1 + i_1  d ) = ( r_0 - r_1 ) + ( i_0 - i_1 ) d$$


```
Dual operator+(const Dual &x, const Dual &y)
{
    return Dual(x.real() + y.real(), x.infsimal() + y.infsimal());
}

Dual operator-(const Dual &x, const Dual &y)
{
    return Dual(x.real() - y.real(), x.infsimal() - y.infsimal());
}
```

#### Multiplication

Similarly two dual numbers multiplication can be:

$$(r_0 + i_0  d ) (r_1 + i_1  d ) = r_0  r_1 + ( r_0 i_1 + r_1 i_0 ) d$$


```
Dual operator*(const Dual &x, const Dual &y)
{
    return Dual(x.real() * y.real(), x.real() * y.infsimal() + x.infsimal() * y.real());
}
```

#### Example Using Addition And Multiplication

With what we have implemented we can write a very simple equation and compute the derivative:

$$f(x) = (x+2)(x+1) = x^2 + 3x + 2$$

We manually get the derivative:

$$f'(x) = 2x + 3$$

When $x=3$:

$$f'(3) = 2 \times 3 + 3 = 9$$

And with our implementation, we have:

$$f(x+d) = f(x) + df'(x)$$

We can define $d$, $x$ and $f(x)$ as follow. We can then see the full implementation and the result is also 9:

```
Dual d(0.0, 1.0);
Dual x(3.0);
```

```
Dual func_to_deriv(Dual x)
{
    return (x + Dual(2.0, 0.0)) * (x + Dual(1.0, 0.0));
}
```

```
#include <iostream>
#include <stdlib.h> 
#include <assert.h> 

class Dual
{
    private:
    double m_real; //Real part
    double m_infsimal; //Infinitesimal part
    
    public:
    Dual (double r, double i = 0.0): m_real(r), m_infsimal(i) {}

    double real() const
    {
        return m_real;
    }
    
    double infsimal() const
    {
        return m_infsimal;
    }
    
    double deriv() const
    {
        return m_infsimal;
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
    
    assert(std::abs(y.deriv() - 9.0) < 0.0001);
    
    std::cout<<y.deriv()<<std::endl;   
    return 0;
};
```


#### Division

Division is a bit complicated. First we write down the division of two dual numbers:

$$\frac{r_0 + i_0  d }{r_1 + i_1  d } = \frac{r_0 + i_0 d}{r_1} \frac{1}{1+\frac{i_1}{r_1} d}$$

Then we need to look at the Generalized Binomial Theorem and binomial expansion of negative power:

$$(1+bx)^n = 1 + n(bx) + \frac{n(n-1)}{2} (bx)^2 + \frac{n(n-1)(n-2)}{3} (bx)^3 + ... + \frac{n(n-1)...(n-r)}{r}(bx)^r + ...$$

It's an infinite series when $n$ is not a positive integer. It's valid when $|bx| < 1$ or $|x| < \frac{1}{|b|}$. 

Back to our case, we have $n=-1$, $b = (i_1/r_1)$ and $x=d$. Aparently $|bx| = (i_1/r_1)d < 1$ because we define $d$ as an infinitesimal number. So we have the following because we defined $d^2=0$:

$$
\begin{aligned}
\frac{r_0 + i_0  d }{r_1 + i_1  d } &= \frac{r_0 + i_0 d}{r_1} \frac{1}{1+\frac{i_1}{r_1} d} \\
                                    &=  \frac{r_0 + i_0 d}{r_1} \left[1 - (\frac{i_1}{r_1}d) + \frac{-1(-1-1)}{2} (\frac{i_1}{r_1}d)^2 + \frac{-1(-1-1)(-1-2)}{3} (\frac{i_1}{r_1}d)^3 + ... + \frac{-1(-1-1)...(-1-r)}{r}(\frac{i_1}{r_1}d)^r + ...\right] \\
                                    &= \frac{r_0 + i_0 d}{r_1} \left[1 - (\frac{i_1}{r_1}d) + d^2(...) \right] \\
                                    &= \frac{r_0 + i_0 d}{r_1} \left[1 - (\frac{i_1}{r_1}d)  \right] \\
                                    &= \frac{r_0}{r_1} + \frac{r_1 i_0 - r_0 i_1}{r_1 ^ {2}}d
\end{aligned}
$$

### Partial Derivatives

We have demonstrated how to differentiate with one single variable, and we can generelise the same method to partial derivatives. Instead of introducing a single variable $d$ such that $d^2=0$, we introduce a set of variables $d_i$ with $i \in I$, where $I$ is an index set. 

<!--
We also need to introduce that the $d_i$ commute with all real numbers (e.g. $ad_i = d_ia$, and $a+d_i = d_i + a$, for all real $a$), and that $d_i d_j = 0$ for all $i,j \in I$.
A general dual number of this type may now be written as
$$x = a + \sum_{i \in I}^{} b_i d_i $$
-->

Suppose we have a function $f(x,y)$, then we compute $f(x+d_0, y+d_1)$. The required partial derivatives appear as the coefficients of $d_0$ and $d_1$.

$$f(x+d_0, y+d_1) = f(x,y) + \frac{\partial f}{\partial x} (x,y) d_0 + \frac{\partial f}{\partial y} (x,y) d_1$$


### Second Derivatives and Higher

Now let's see how do we compuate second derivatives. We just need to use template type for the real and infinitesimal parts. 

If we want to get the first order derivatives, we can set the real and infinitesimal parts as double. 

If we want to get the second order derivatives, we can set the real and infinitesimal parts as dual numbers, read the real part of the infinitesimal coefficients (which are dual numbers) as the first order derivatives, and read the infinitesimal part of the infinitesimal coefficients (which are dual numbers) as the second order derivatives. 

Let's check the example below:

```
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
```
