## Backward Mode Intro

Consider a general function like below:

$$y = h ( g ( f(x) ) )$$

$$\frac{\partial y}{\partial x} =\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}$$

We have noticed that in forward mode we are decomposing calculations into elementary steps and getting the derivative of each step from the left to the right side following the chain rule:

$$\frac{\partial y}{\partial x} = \overleftarrow{\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}} $$

In forward mode we are doing $\frac{\partial h}{\partial g} \frac{\partial g}{\partial f}$ again and again. We can try go backward on the chain:

$$\frac{\partial y}{\partial x} = \overrightarrow{\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}} $$

So we can only calculate $\frac{\partial h}{\partial g} \frac{\partial g}{\partial f}$ once and apply it to the rest of the calculations. This is the idea of backward mode. 

Let's denote $H = \frac{\partial h}{\partial g} \frac{\partial g}{\partial f}$, then we can have:

$$
\begin{aligned}
\frac{\partial y}{\partial x_1} &= H \left( \frac{\partial f}{\partial x_1}\right)    \\
\frac{\partial y}{\partial x_2} &= H \left( \frac{\partial f}{\partial x_2}\right)     \\
... \ &= \ ...   \\
\frac{\partial y}{\partial x_n} &= H \left( \frac{\partial f}{\partial x_n}\right)     \\
\end{aligned}
$$


## Backward mode

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
