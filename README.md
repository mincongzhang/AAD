# Automatic Differentiation Proof of Concept

### Forward Mode (using Dual Number)

Example:

```
    Dual d(0.0, 1.0);
    Dual x(3.0);
    Dual y = func_to_deriv(x + d);
    std::cout<<y.deriv()<<std::endl;
```

### Backward Mode (using expression tree and back propagation)

Example:
```
    Var x;
    Var y;
    Var z = x*y + Var::sin(x);
    
    x.setVal(2);
    y.setVal(4);
    std::cout<<"z val:"<<z.val()<<std::endl;
    std::cout<<"dz/dx:"<<z.derivOn(x)<<std::endl;
    std::cout<<"dz/dy:"<<z.derivOn(y)<<std::endl;
```

### References

https://web.archive.org/web/20050315101043/http://homepage.mac.com/sigfpe/paper.pdf

https://github.com/autodiff/autodiff

https://sidsite.com/posts/autodiff/

https://jingnanshi.com/blog/autodiff.html

https://www.cs.toronto.edu/~rgrosse/courses/csc2541_2022/tutorials/tut01.pdf

https://www.cs.toronto.edu/~rgrosse/courses/csc321_2018/slides/lec10.pdf
