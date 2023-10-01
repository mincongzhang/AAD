    """
    z = xy + sin(x)
    a = xy
    b = sin(x)
    z = a + b
    --------------------
    dz/da = 1
    dz/db = 1
    --------------------
    da/dx = y
    da/dy = x

    db/dx = cos(x)
    db/dy = 0

    dz/dx = dz/da * da/dx + dz/db * db/dx = da/dx + db/dx =  y + cos(x)
    dz/dy = dz/da * da/dy = x
    """
    import math

    from collections import defaultdict


    class Var:
        def __init__(self, val=0, grad=1, name=""):
            self.val = val
            self.grad = grad
            self.name = name
            self.val_expressions = [(lambda x, y: x.val, (self, None))]
            self.grad_expressions = {self: [(lambda x, y: 1, (self, None), name)]}

        def set_val(self, v):
            self.val = v

        def get_val(self):
            res = 0
            for (func, (v1, v2)) in self.val_expressions:
                res += func(v1, v2)
            return res

        def get_grad(self, on_input):
            res = 0
            print("on input:", on_input.name, on_input.get_val())
            if on_input in self.grad_expressions:
                for (func, (d1, d2), name) in self.grad_expressions[on_input]:
                    f_res = func(d1, d2)
                    print(name, "=", f_res)
                    res += f_res
            return res

        def __add__(self, other):
            z = Var(name="c")
            z.val_expressions = [(lambda x, y: x.get_val() + y.get_val(), (self, other))]

            z.grad_expressions = defaultdict(list)
            x_keys = self.grad_expressions.keys()

            for k in x_keys:
                funcs = []
                for (func, (v1, v2), name) in self.grad_expressions[k]:
                    funcs.append((func, (v1, v2), f"{name} on {self.name} to add"))
                z.grad_expressions[k] += funcs

            y_keys = other.grad_expressions.keys()
            for k in y_keys:
                funcs = []
                for (func, (v1, v2), name) in other.grad_expressions[k]:
                    funcs.append((func, (v1, v2), f"{name} on {other.name} to add"))
                z.grad_expressions[k] += funcs

            return z

        def __mul__(self, other):
            z = Var(name="a")
            z.val_expressions = [(lambda x, y: x.get_val() * y.get_val(), (self, other))]

            z.grad_expressions = defaultdict(list)
            x_keys = self.grad_expressions.keys()

            for k in x_keys:
                funcs = []
                for (func, (v1, v2), name) in self.grad_expressions[k]:
                    funcs.append((lambda x, y: func(v1, v2) * y.get_val(), (self, other), f"({name})*{other.name}"))
                z.grad_expressions[k] += funcs

            y_keys = other.grad_expressions.keys()
            for k in y_keys:
                funcs = []
                for (func, (v1, v2), name) in other.grad_expressions[k]:
                    funcs.append((lambda x, y: func(v1, v2) * x.get_val(), (self, other), f"({name})*{self.name}"))
                z.grad_expressions[k] += funcs

            return z

        @staticmethod
        def sin(var1):
            z = Var(name="b")
            z.val_expressions = [(lambda x, y: math.sin(x.get_val()), (var1, None))]

            z.grad_expressions = defaultdict(list)
            keys = var1.grad_expressions.keys()

            for k in keys:
                funcs = []
                for (func, (v1, v2), name) in var1.grad_expressions[k]:
                    funcs.append((lambda x, y: func(v1, v2) * math.cos(x.get_val()), (var1, None), f"{name} cos({var1.name})"))
                z.grad_expressions[k] += funcs

            return z


    x = Var(name="x")
    y = Var(name="y")

    z = x * y + Var.sin(x)

    x.set_val(2)
    y.set_val(4)
    print(x.get_val())
    print(y.get_val())
    print(z.get_val())
    print("dz/dx:", z.get_grad(x))
    print("dz/dy:", z.get_grad(y))
