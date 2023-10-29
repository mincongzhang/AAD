# Automatic Differentiation

### Background - Differential calculus and derivatives computation

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

Straightforward and intuitive.

Cons:

(1)If we have multiple variables and complicated function then it could be tedious and error prone. 

(2)Every modification to the function must be repeated in differential form. 

e.g. if we have 1000 variables and a functions with 1000 chains then it could be almost impossible to manually get the derivitives. We could of course try to use some tool like a derivative calculator to get the derivitives automatically, but this complicates the build process and put constrains on coding styles.  

### Automatic Differentiation Forward Mode - Dual Number

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
