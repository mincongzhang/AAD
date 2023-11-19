forward mode problem:
complexity

so we need backward mode

Evaluation Trace: 原公式计算流程

Tangent Trace: chain rules, depends on the derivatives and values of the earlier variables. The values of the intermediate variables are sometimes called the primal trace, and the derivative values the tangent trace.


In terms of complexity:

forward mode

-----------

First, we need to do a forward pass, where we obtain the primal trace. We then propagate the partials backward to obtain the desired derivatives (following the chain rule).

In general, if the dimension of the outputs is significantly smaller than that of inputs, reverse mode is a better choice.
