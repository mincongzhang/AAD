## Forward mode revisit

Let's revisit our forward mode using dual numbers. We know that we can do calculations on infinitesimal parts using operator overloading and read the derivative from the coefficient of the infinitesimal part of the final result. 

Consider a general function like below:

$$y = h ( g ( f(x) ) )$$

$$\frac{\partial y}{\partial x} =\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}$$

With our dual number solution, we are decomposing calculations into elementary steps and getting the derivative of each step. So the first derivative we get is $\frac{\partial f}{\partial x}$, then $\frac{\partial g}{\partial f}$ and eventually $\frac{\partial h}{\partial g}$.

One more concrete example, let's have a function and its derivative:

$$y = sin[(2x)^2]$$

$$\frac{\partial y}{\partial x} =\frac{\partial sin[(2x)^2]}{\partial (2x)^2} \frac{\partial (2x)^2}{\partial 2x} \frac{\partial 2x}{\partial x}$$

Following the order of operations and operator overloading, we know that we are firstly calculating $2x$ and getting the coefficient of its infinitesimal part, which is the derivative, i.e. $\frac{\partial 2x}{\partial x}$. Then we get $\frac{\partial (2x)^2}{\partial 2x}$ and eventually $\frac{\partial sin[(2x)^2]}{\partial (2x)^2}$.

So now we know that the "forward mode" means calculating the derivitive from the right to the left through the chain rules:

$$\frac{\partial y}{\partial x} = \overleftarrow{\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}} $$

##  Forward Mode: pros and cons

We know that we are going to talk about backward mode, and there must be some disadvantages of forward mode.

Since everyone is familiar with the fancy machine learning, let's take it as an example. In machine learning there won't be only one $x$ input parameter, there could be hundreds or thousands of input paramaters. And if we are using forward mode to get the partial derivatives of all the parameters, we might have:

$$
\begin{aligned}
\frac{\partial y}{\partial x_1} &= \overleftarrow{\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x_1}}    \\
\frac{\partial y}{\partial x_2} &= \overleftarrow{\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x_2}}    \\
... \ &= \ ...   \\
\frac{\partial y}{\partial x_n} &= \overleftarrow{\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x_n}}    \\
\end{aligned}
$$

Have you noticed that we have $O(n)$ complexity on forward mode? This is the inefficience of forward mode when inputs are more than outputs, i.e. $f: \mathbb{R}^n \rightarrow \mathbb{R}^m$, where $n>m$. 

Also have you noticed that we are doing $\frac{\partial h}{\partial g} \frac{\partial g}{\partial f}$ again and again? What if we go backward of the derivative like:

$$\frac{\partial y}{\partial x} = \overrightarrow{\frac{\partial h}{\partial g} \frac{\partial g}{\partial f} \frac{\partial f}{\partial x}} $$

So we can only calculate $\frac{\partial h}{\partial g} \frac{\partial g}{\partial f}$ once and apply it to the rest of the calculations? Yes we can. That's how our backward mode comes up. 

Let's say $H = \frac{\partial h}{\partial g} \frac{\partial g}{\partial f}$, then we can have:

$$
\begin{aligned}
\frac{\partial y}{\partial x_1} &= H (\frac{\partial f}{\partial x_1})    \\
\frac{\partial y}{\partial x_2} &= H (\frac{\partial f}{\partial x_2})    \\
... \ &= \ ...   \\
\frac{\partial y}{\partial x_n} &= H (\frac{\partial f}{\partial x_n})    \\
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
