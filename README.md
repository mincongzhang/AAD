# Automatic Differentiation Proof of Concept

### Forward Mode (using Dual Number)

Example:

```
    Dual d(0.0, 1.0);
    Dual x(3.0);
    Dual y = func_to_deriv(x + d);
    std::cout<<y.deriv()<<std::endl;  // 9
```

### Backward Mode (using expression tree and back propagation)

Example:
```
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
    
```

### References

https://web.archive.org/web/20050315101043/http://homepage.mac.com/sigfpe/paper.pdf

https://github.com/autodiff/autodiff

https://sidsite.com/posts/autodiff/

https://jingnanshi.com/blog/autodiff.html

https://www.cs.toronto.edu/~rgrosse/courses/csc2541_2022/tutorials/tut01.pdf

https://www.cs.toronto.edu/~rgrosse/courses/csc321_2018/slides/lec10.pdf
