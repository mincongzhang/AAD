## Forward mode revisit

Let's revisit our forward mode using dual numbers. We know that we can do calculations on infinitesimal parts using operator overloading and read the derivative from the coefficient of the infinitesimal part of the final result. 

Consider a general function like below:

$$y = h ( g ( f(x) ) )$$

$$\frac{\partial y}{\partial x} =\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}$$

With our dual number solution, we are decomposing calculations into elementary steps and getting the derivative of each step. So the first derivative we get is $\frac{\partial f}{\partial x}$, then $\frac{\partial g}{\partial f}$ and eventually $\frac{\partial h}{\partial g}$.

One more concrete example, let's have a function:

$$y = sin[(2x)^2]$$

$$\frac{\partial y}{\partial x} =\frac{\partial sin[(2x)^2]}{\partial (2x)^2} \frac{\partial (2x)^2}{\partial 2x} \frac{\partial 2x}{\partial x}$$

Following the order of operations and operator overloading we know that we are calculating the derivative of $\frac{\partial 2x}{\partial x}$ first, then $\frac{\partial (2x)^2}{\partial 2x}$ and eventually $\frac{\partial sin[(2x)^2]}{\partial (2x)^2}$

## Forward mode vs backward mode

how is it forward and how is it backward?



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
