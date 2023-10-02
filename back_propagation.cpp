#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <assert.h> 

class Var
{
public:
    using ExpFunc = std::function< double( const Var *, const Var * ) >;
    class Expression
    {
    private:
        ExpFunc func;
        const Var * input_x;
        const Var * input_y;

    public:

        Expression( ExpFunc f, const Var * x, const  Var * y ) : func( f ), input_x( x ), input_y( y ) { }
        double eval() const
        {
            return func( input_x, input_y );
        }

    };

    Var( double val = 0.0 ) : m_val( val ), m_grad( 1.0 )
    {

        auto init_eval_trace = []( const Var * x, const Var * y ) {
            return x->getVal();
        };
        m_eval_traces.emplace_back( Expression( init_eval_trace, this, nullptr ) );

        auto init_tan_trace = []( const  Var * x, const Var * y )
        {
            return 1;
        };
        m_tan_traces[this] = std::vector< Expression > { Expression( init_tan_trace, this, nullptr ) };
    }

    void addEvalTrace( const Expression & exp )
    {
        m_eval_traces.emplace_back( exp );
    }

    void addTanTrace( const Var * ptr, const Expression & exp )
    {
        auto it = m_tan_traces.find( ptr );
        if( it != m_tan_traces.end() )
        {
            it->second.emplace_back( exp );
        }
        else
        {
            m_tan_traces[ptr] = std::vector< Expression > { exp };
        }
    }


    void addTanTrace( const Var * ptr, const std::vector<Expression> exps )
    {
        auto it = m_tan_traces.find( ptr );
        if( it != m_tan_traces.end() )
        {
            it->second.insert( it->second.end(), exps.begin(), exps.end() );
        }
        else
        {
            m_tan_traces[ptr] = exps;
        }
    }

    void setVal( double val )
    {
        m_val = val;
    }

    double getVal() const
    {
        return m_val;
    }

    double val() const
    {
        double res = 0.0;
        for( const auto & exp : m_eval_traces )
        {
            res += exp.eval();
        }
        return res;
    }

    double derivOn( const Var & on_input ) const
    {
        double res = 0.0;

        auto it = m_tan_traces.find( &on_input );
        if( it != m_tan_traces.end() )
        {
            auto exps = it->second;
            for( const auto & exp : exps )
            {
                res += exp.eval();
            }
        }

        return res;
    }

    Var operator+( const Var & other )
    {
        Var z;
        
        auto val_func = []( const Var * x, const Var * y )
        {
            return  x && y ? x->val() + y->val() : 0;
        };
        z.addEvalTrace(Expression(val_func, this, &other));

        for( auto &[ptr, exps] : m_tan_traces )
        {
            z.addTanTrace( ptr, exps );
        }
        for( auto &[ptr, exps] : other.m_tan_traces )
        {
            z.addTanTrace( ptr, exps );
        }

        return std::move( z );
    }

    Var operator*( const Var & other )
    {
        Var z;
        
        auto val_func = []( const Var * x, const Var * y ) {
                return  x && y ? x->val() * y->val() : 0;
            };
        z.addEvalTrace(Expression(val_func, this, &other));

        for( auto &[ptr, exps] : m_tan_traces )
        {
            for( auto & exp : exps ) {
                auto mult_func = [exp]( const Var * x, const Var * y ) {
                    return y ? exp.eval() * y->val() : 0;
                };
                z.addTanTrace( ptr, Expression(mult_func, this, &other) );
            }
        }
        for( auto &[ptr, exps] : other.m_tan_traces )
        {
            for( auto & exp : exps )
            {
                auto mult_func = [exp]( const Var * x, const Var * y ) 
                {
                    return x ? exp.eval() * x->val() : 0;
                };
                z.addTanTrace( ptr, Expression( mult_func, this, &other ) );
            }
        }

        return std::move( z );
    }

    static Var sin( const Var & v )
    {
        Var z;
        
        auto val_func = []( const Var * x, const Var * y ) 
        {
            return  x ? std::sin(x->val()) : 0;
        };
        z.addEvalTrace(Expression(val_func, &v, nullptr));
        
        for( auto &[ptr, exps] : v.m_tan_traces )
        {
            for( auto & exp : exps )
            {
                auto mult_func = [exp]( const Var * x, const Var * y ) 
                {
                    return x ? exp.eval() * std::cos(x->val()) : 0;
                };
                z.addTanTrace( ptr, Expression( mult_func, &v, nullptr ) );
            }
        }
        return std::move( z );
    }

private:

    double m_val;
    double m_grad;

    std::vector< Expression > m_eval_traces;
    std::unordered_map< const Var *, std::vector< Expression > > m_tan_traces;

};

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
    assert(std::abs(z.derivOn(x) - 3.58385) < 0.0001);
    assert(std::abs(z.derivOn(y) - 2) < 0.0001);
    
    std::cout<<"z val:"<<z.val()<<std::endl;
    std::cout<<"dz/dx:"<<z.derivOn(x)<<std::endl;
    std::cout<<"dz/dy:"<<z.derivOn(y)<<std::endl;

    return 0;
}
