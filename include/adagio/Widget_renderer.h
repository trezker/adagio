#ifndef adagio_widget_renderer_h
#define adagio_widget_renderer_h

#ifndef NULL
#define NULL 0
#endif

namespace adagio
{

class Widget;

class Renderfunction_impl
{
public:
	void (*func)( const Widget& );
	Renderfunction_impl(){}
	Renderfunction_impl(void (*f)( const Widget& ))
	:func(f)
	{}
	Renderfunction_impl* Clone() const
	{
		return new Renderfunction_impl(*this);
	} 
	virtual void operator()(const Widget& arg0)
	{
		return func(arg0);
	}
};

template <typename U>
class Renderfunction_impl_U: public Renderfunction_impl
{
public:
	void (*func)( const U& );
	Renderfunction_impl_U(void (*f)( const U& ))
	:func(f)
	{}
	Renderfunction_impl_U* Clone() const
	{
		return new Renderfunction_impl_U(*this);
	} 
	virtual void operator()(const Widget& arg0)
	{
		return func(dynamic_cast<U &> (arg0));
	}
};

template <class T>
class Renderfunctor_impl : public Renderfunction_impl
{
	void (T::*func)( const Widget& );
	T *o;
public:
	Renderfunctor_impl(void (T::*f)( const Widget& ), T& instance)
	:func(f)
	,o(&instance)
	{}
	Renderfunctor_impl* Clone() const
	{
		return new Renderfunctor_impl(*this);
	} 
	virtual void operator()(const Widget& arg0)
	{
		return (o->*func)(arg0);
	}
};

template <class T, class U>
class Renderfunctor_impl_U : public Renderfunction_impl
{
	void (T::*func)( const U& );
	T *o;
public:
	Renderfunctor_impl_U(void (T::*f)( const U& ), T& instance)
	:func(f)
	,o(&instance)
	{}
	Renderfunctor_impl_U* Clone() const
	{
		return new Renderfunctor_impl_U(*this);
	} 
	virtual void operator()(const Widget& arg0)
	{
		return (o->*func)(dynamic_cast<U &>(arg0));
	}
};

/* Class: Renderfunction
 * Universal function container for widget rendering functions.
 * */
class Renderfunction
{
	Renderfunction_impl* impl;
public:
	/* Constructor: Renderfunction
	 * Creates a function that does nothing.
	 * */
	Renderfunction()
	:impl(NULL)
	{
	}
	
	/* Constructor: Renderfunction
	 * Copy constructor
	 * */
	Renderfunction(const Renderfunction& o)
	{
		if(o.impl)
			impl = o.impl->Clone();
		else
			impl = NULL;
	}

	/* Destructor: ~Renderfunction
	 * 
	 * */
	~Renderfunction()
	{
		if(impl)
			delete impl;
	}
	
	/* Constructor: Renderfunction
	 * Constructor for ordinary function taking the Widget base class as argument.
	 * 
	 * Example:
	 * >void foo(const Widget& b);
	 * >Renderfunction(foo);
	 * */
	Renderfunction(void (*f)( const Widget& ))
	{
		impl = new Renderfunction_impl(f);
	}

	/* Constructor: Renderfunction
	 * Constructor for ordinary function taking a specific Widget derived class as argument.
	 * 
	 * Example:
	 * >void foo(const Button& b);
	 * >Renderfunction<Button>(foo);
	 * */
	template<typename U>
	Renderfunction(void (*f)( const U& ))
	{
		impl = new Renderfunction_impl_U<U>(f);
	}
	
	/* Constructor: Renderfunction
	 * Constructor for member function the Widget base class as argument.
	 *
	 * Example: 
	 * >class Foo{ 
	 * >	void bar(const Widget &w);
	 * >};
	 * >Foo aFoo;
	 * >Renderfunction<Foo>(&Foo::bar, aFoo);
	 * */
	template<typename T>
	Renderfunction(void (T::*f)( const Widget& ), T& instance)
	{
		impl = new Renderfunctor_impl<T>(f, instance);
	}

	/* Constructor: Renderfunction
	 * Constructor for member function taking a specific Widget derived class as argument.
	 *
	 * Example: 
	 * >class Foo{ 
	 * >	void bar(const Button &w);
	 * >};
	 * >Foo aFoo;
	 * >Renderfunction<Foo, Button>(&Foo::bar, aFoo);
	 * */
	template<typename T, typename U>
	Renderfunction(void (T::*f)( const U& ), T& instance)
	{
		impl = new Renderfunctor_impl_U<T, U>(f, instance);
	}
	
	void operator()(const Widget& arg0) const
	{
		if(impl)
			(*impl)(arg0);
	}
};

}

#endif
