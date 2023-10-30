# Automatic Differentiation

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
y  &= f\(x\)    \\
z  &= g\(x, y\)
\end{aligned}
$$

We can use the chain rule to get the derivatives:

$$
\begin{aligned}
y' &= f'\(x\)   \\
z' &= \frac{\partial g\(x, y\)}{\partial x} + y' \frac{\partial g\(x, y\)}{\partial y}
\end{aligned}
$$

Ultimately we get the differentiable expressions and we can compute derivatives. 

Pros:

(1)Straightforward and intuitive

Cons:

(1)If we have multiple variables and complicated function then it could be tedious and error prone. 

(2)Every modification to the function must be repeated in differential form. 

e.g. if we have 1000 variables and a functions with 1000 chains then it could be almost impossible to manually get the derivitives. We could of course try to use some tool like a derivative calculator to get the derivitives and then code the expressions, but this complicates the build process and put constrains on coding styles.  

#### 2. Finite Differences

By definition, the derivative of a function $f$, written $`f'(x)`$ or $\frac{df}{dx}$ is defined by 

$$f'\(x\) = \lim_{\delta \to 0} \frac{f\(x+\delta\) - f\(x\)}{\delta}$$

In this equation we can choose $\delta$ to be a small value, rather than take the limit as it approaches zero, and compute $\frac{f\(x+\delta\) - f\(x\)}{\delta}$. This is an approximation
to $`f'(x)`$ known as the __forward difference__.

There is some difficulty associated with choosing a suitable value for $\delta$. Too large and the approximation to the definition of the derivative is poor. Too small and we can expect the result to be dominated by rounding errors. 

We can improve the accuracy using __central differences__, i.e. $\frac{f\(x+\delta\) - f\(x-\delta\)}{2\delta}$, but the errors can still be large. 

Note that this also requires two seperate evaluations of $f$. If we generalise this method to compute $n$ partial derivatives of a function then we can expect to require $n+1$ separate computations of $f$.

### Automatic Differentiation Forward Mode - Dual Number

Let's check the equation again:

$$f'\(x\) = \lim_{\delta \to 0} \frac{f\(x+\delta\) - f\(x\)}{\delta}$$

And look at the following example:

$$f\(x\) = 2x^2 + 1$$

Let's set $\delta = d$, a small non-zero number, then the approximation to $`f'(x)`$ is given by:

$$f'\(x\) = \lim_{\delta \to 0} \frac{f\(x+\delta\) - f\(x\)}{\delta} = \frac{4dx + 2d^2}{d} = \frac{4dx}{d} + \frac{2d^2}{d} = 4x + \frac{2d^2}{d} $$

The exact derivative is $4x$ so we have an error term $\frac{2d^2}{d}$. If $d^2$ is small compared to $d$ then the error becomes small and the approximation approaches the true value of the derivative. Ultimately, if $d^2$ were zero then we could compute the derivative as $4x$ exactly. 

But unfortunately the only choice for a real number $d$ such that $d^2 = 0$ is $d=0$. $d$ is the denominator so if we set $d=0$ then the whole computation is meaningless. How do we find a non-zero number $d$ such that $d^2=0$?

It's the time we introduce the __dual numbers__. It's similar to the concept of complex numbers, where we have the equation $x^2 + 1 = 0$ and we define the imaginary number $i$ with the property $i^2 = -1$. We extend the real numbers by adding a new infinitesimal variable, $d$, with the property that $d^2 = 0$ but $d \neq 0$.

### Automatic Differentiation Forward Mode - Dual Number Implementation

### Automatic Differentiation Forward Mode - Example Using Dual Number

Example:

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

### Forward Mode - Partial Derivatives

### Backward Mode (using expression tree and back propagation)

Example:
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

### References

https://web.archive.org/web/20050315101043/http://homepage.mac.com/sigfpe/paper.pdf

Dan Piponi (2004) Automatic Differentiation, C++ Templates, and Photogrammetry, Journal of Graphics Tools, 9:4, 41-55, DOI: 10.1080/10867651.2004.10504901

https://github.com/autodiff/autodiff

https://sidsite.com/posts/autodiff/

https://jingnanshi.com/blog/autodiff.html

https://www.cs.toronto.edu/~rgrosse/courses/csc2541_2022/tutorials/tut01.pdf

https://www.cs.toronto.edu/~rgrosse/courses/csc321_2018/slides/lec10.pdf
