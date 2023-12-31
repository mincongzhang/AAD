## Backward Mode Introduction

Consider a general function like below:

$$y = h ( g ( f(x) ) )$$

$$\frac{\partial y}{\partial x} =\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}$$

We have noticed that in forward mode we are decomposing calculations into elementary steps and getting the derivative of each step from the left to the right side following the chain rule:

$$\frac{\partial y}{\partial x} = \overleftarrow{\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}} $$

We can also try go backward on the chain. And we call this backward mode:

$$\frac{\partial y}{\partial x} = \overrightarrow{\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}} $$


### Evaluation Trace, Primal Trace and Tangent Trace

Before looking into the details, let's go through some definitions and terms. 

As we have already known that in forward mode we decompose calculations into elementary steps, now we define all the steps form an __evaluation trace__. Some also call this evaluation trace the __Wengert list__, which is named after the author of this paper *Wengert, Robert Edwin. "A simple automatic derivative evaluation program." Communications of the ACM 7.8 (1964): 463-464*.

Let's take this function as an example and its derivative, and evaluate the function when $x = 3$:

$$y = h ( g ( f(x) ) ) = sin[(2x)^2]$$

$$\frac{\partial y}{\partial x} = \frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x} = \frac{\partial sin[(2x)^2]}{\partial (2x)^2} \frac{\partial (2x)^2}{\partial 2x} \frac{\partial 2x}{\partial x}$$

All the steps below form an __evaluation trace__. The values of the intermediate variables are sometimes called the __primal trace__.

| Intermediate Vars.                | Expressions               | Expression Eval. | Values (Primal Trace)| 
|:----------------------------------|:--------------------------|:-----------------|:---------------------|
| $v_0$                             | $x$                       | $x$              | 3                    |
| $v_1$                             | $2v_0$                    | $2x$             | 6                    |
| $v_2$                             | $v_1^2$                   | $(2x)^2$         | 36                   |
| $v_3$                             | $sin(v_2)$                | $sin[(2x)^2]$    | sin(36)              |

Now we extend the table for derivitives. The values of of the intermediate derivative variables are called the __tangent trace__. And we still set $x = 3$.

| Intermediate Vars.                | Expressions               | Expression Eval. | Values (Primal Trace)|  Interm. Deriv. Vars.    | Deriv. Expressions     |   Deriv. Expressions Eval.    | Deriv. Values (Tangent Trace)| 
|:----------------------------------|:--------------------------|:----------------|:----------------------|:-------------------------|:-----------------------|:------------------------------|:----------------------------:|
| $v_0$                             | $x$                       | $x$             | 3                     |  $d_0$                   | 1                      | 1                             | 1                            |
| $v_1$                             | $2v_0$                    | $2x$            | 6                     |  $d_1$                   | $d_0 \cdot 2$          | 2                             | 2                            |
| $v_2$                             | $v_1^2$                   | $(2x)^2$        | 36                    |  $d_2$                   | $d_1 \cdot 2\cdot2x$   | $8x$                          | 24                           |
| $v_3$                             | $sin(v_2)$                | $sin[(2x)^2]$   | sin(36)               |  $d_3$                   | $d_2 \cdot cos[(2x)^2]$| $8x \cdot cos[(2x)^2]$        | 24cos(36)                    |

### How Forward Mode Works

When we use dual numbers to conduct the forward mode automatic differentiation, we use operator overloading and get the __primal trace__ from the __real number part__ and get the __tangent trace__ from the __infinitesimal part__ at the same time, and eventually we get the derivative from the __tangent trace__.

| Intermediate Vars.                | Expressions               | Expression Eval. | Values (Primal Trace)|  Interm. Deriv. Vars.    | Deriv. Expressions     |   Deriv. Expressions Eval.    | Deriv. Values (Tangent Trace)| Forward |
|:----------------------------------|:--------------------------|:----------------|:----------------------|:-------------------------|:-----------------------|:------------------------------|:----------------------------:|:-------:|          
| $v_0$                             | $x$                       | $x$             | 3                     |  $d_0$                   | 1                      | 1                             | 1                            |    ↓    |
| $v_1$                             | $2v_0$                    | $2x$            | 6                     |  $d_1$                   | $d_0 \cdot 2$          | 2                             | 2                            |    ↓    |
| $v_2$                             | $v_1^2$                   | $(2x)^2$        | 36                    |  $d_2$                   | $d_1 \cdot 2\cdot2x$   | $8x$                          | 24                           |    ↓    |
| $v_3$                             | $sin(v_2)$                | $sin[(2x)^2]$   | sin(36)               |  $d_3$                   | $d_2 \cdot cos[(2x)^2]$| $8x \cdot cos[(2x)^2]$        | 24cos(36)                    |    ↓    |

![image](https://github.com/mincongzhang/AAD/assets/5571030/b131db64-e1f2-4ccc-bc6b-0ec714272c3c)


### How Backward Mode Works

Let's see how can we get the derivative with backward mode. First, we need to do a forward pass to get the table for primal trace. 

We then propagate the partials backward to obtain the desired derivatives (following the chain rule).

| Intermediate Vars.                | Expressions               | Expression Eval. | Values (Primal Trace)|  Interm. Deriv. Vars.    | Deriv. Expressions     |   Deriv. Expressions Eval.    | Deriv. Values (Tangent Trace)| Backward |
|:----------------------------------|:--------------------------|:----------------|:----------------------|:-------------------------|:-----------------------|:------------------------------|:----------------------------:|:-------:|          
| $v_0$                             | $x$                       | $x$             | 3                     |  $d_0$                   | 1                      | 1                             | 1                            |    ↑    |
| $v_1$                             | $2v_0$                    | $2x$            | 6                     |  $d_1$                   | $d_0 \cdot 2$          | 2                             | 2                            |    ↑    |
| $v_2$                             | $v_1^2$                   | $(2x)^2$        | 36                    |  $d_2$                   | $d_1 \cdot 2\cdot2x$   | $8x$                          | 24                           |    ↑    |
| $v_3$                             | $sin(v_2)$                | $sin[(2x)^2]$   | sin(36)               |  $d_3$                   | $d_2 \cdot cos[(2x)^2]$| $8x \cdot cos[(2x)^2]$        | 24cos(36)                    |    ↑    |


![image](https://github.com/mincongzhang/AAD/assets/5571030/805edd2e-6ceb-4c9a-941e-a172231636eb)


__How Backward is better than Forward?__

it takes only one application of reverse mode to compute the entire gradient. In general, if the dimension of the outputs is significantly smaller than that of inputs, reverse mode is a better choice.


https://jingnanshi.com/blog/autodiff.html

-----------

backward mode

First, we need to do a forward pass, where we obtain the primal trace. We then propagate the partials backward to obtain the desired derivatives (following the chain rule).

![image](https://github.com/mincongzhang/AAD/assets/5571030/4a9bb3fa-656a-4266-a7c5-6248457d050e)

![image](https://github.com/mincongzhang/AAD/assets/5571030/55fd41aa-dd89-4392-8660-356870fe8256)

![image](https://github.com/mincongzhang/AAD/assets/5571030/56a0c03b-655a-44bb-b415-9e60826968c2)



In general, if the dimension of the outputs is significantly smaller than that of inputs, reverse mode is a better choice.
