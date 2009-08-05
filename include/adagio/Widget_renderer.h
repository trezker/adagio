#ifndef adagio_widget_renderer_h
#define adagio_widget_renderer_h

namespace adagio
{

class Widget;

class Renderfunction
{
public:
	void (*func)( const Widget& );
	Renderfunction(){}
	Renderfunction(void (*f)( const Widget& ))
	:func(f)
	{}
	virtual void operator()(const Widget& arg0)
	{
		return func(arg0);
	}
};

template <class T>
class Renderfunctor : public Renderfunction
{
	void (T::*func)( const Widget& );
	T *o;
public:
	Renderfunctor(void (T::*f)( const Widget& ), T& instance)
	:func(f)
	,o(&instance)
	{}
	virtual void operator()(const Widget& arg0)
	{
		return (o->*func)(arg0);
	}
};

}

#endif
