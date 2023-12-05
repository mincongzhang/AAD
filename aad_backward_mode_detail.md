## Backward Mode Introduction

Consider a general function like below:

$$y = h ( g ( f(x) ) )$$

$$\frac{\partial y}{\partial x} =\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}$$

We have noticed that in forward mode we are decomposing calculations into elementary steps and getting the derivative of each step from the left to the right side following the chain rule:

$$\frac{\partial y}{\partial x} = \overleftarrow{\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}} $$

In forward mode we are doing $\frac{\partial h}{\partial g} \frac{\partial g}{\partial f}$ again and again. We can try go backward on the chain:

$$\frac{\partial y}{\partial x} = \overrightarrow{\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}} $$

So we can only calculate $\frac{\partial h}{\partial g} \frac{\partial g}{\partial f}$ once and apply it to the rest of the calculations. This is the idea of backward mode. 


### Evaluation Trace, Primal Trace and Tangent Trace

Before looking into the details, let's go through some definitions and terms. 

As we have already known that in forward mode we decompose calculations into elementary steps, all the steps form an __evaluation trace__. 

Some also call this evaluation trace the __Wengert list__, which is named after the author of this paper *Wengert, Robert Edwin. "A simple automatic derivative evaluation program." Communications of the ACM 7.8 (1964): 463-464*.

Let's take this function as an example and its derivative, and evaluate the function when $x = 1$:

$$y = sin[(2x)^2]$$

$$\frac{\partial y}{\partial x} =\frac{\partial sin[(2x)^2]}{\partial (2x)^2} \frac{\partial (2x)^2}{\partial 2x} \frac{\partial 2x}{\partial x}$$

All the steps below form a evaluation trace.

| Intermediate Vars. (Primal Trace) | Expressions | Values | 
|:---------------------------------:|:-----------:|:------:|
| $v_0$                             | $x$         | 1      |
| $v_1$                             | $2v_0$      | 2      |
| $v_2$                             | $v_1^2$     | 4      |
| $v_3$                             | $sin(v_2)$  | -0.76  |

Now we extend it to derivitives:

| Intermediate Vars. (Primal Trace) | Expressions | Values | Intermediate Deriv Vars. (Tangent Trace) | Deriv Expressions | 
|:---------------------------------:|:-----------:|:------:|:----------------------------------------:|:-----------------:|
| $v_0$                             | $x$         | 1      |  $d_0$                                   |
| $v_1$                             | $2v_0$      | 2      |  $d_1$
| $v_2$                             | $v_1^2$     | 4      |  $d_2$
| $v_3$                             | $sin(v_2)$  | -0.76  |  $d_3$



primal trace:

tangent trace:


evaluation trace:


This essentially gives us the way to conduct forward mode AD: by using dual numbers, we can get the primal and tangent trace simultaneously.



First, we need to do a forward pass, where we obtain the primal trace (Table 2). We then propagate the partials backward to obtain the desired derivatives (following the chain rule).




https://jingnanshi.com/blog/autodiff.html




forward mode problem:
complexity

so we need backward mode

Evaluation Trace: 原公式计算流程

Tangent Trace: chain rules, depends on the derivatives and values of the earlier variables. The values of the intermediate variables are sometimes called the primal trace, and the derivative values the tangent trace.


In terms of complexity:

forward mode

-----------

backward mode

First, we need to do a forward pass, where we obtain the primal trace. We then propagate the partials backward to obtain the desired derivatives (following the chain rule).

![image](https://github.com/mincongzhang/AAD/assets/5571030/4a9bb3fa-656a-4266-a7c5-6248457d050e)

![image](https://github.com/mincongzhang/AAD/assets/5571030/55fd41aa-dd89-4392-8660-356870fe8256)

![image](https://github.com/mincongzhang/AAD/assets/5571030/56a0c03b-655a-44bb-b415-9e60826968c2)



In general, if the dimension of the outputs is significantly smaller than that of inputs, reverse mode is a better choice.
