#ifndef adagio_renderfunction_h
#define adagio_renderfunction_h

#include <iostream>

#ifndef NULL
#define NULL 0
#endif

/*twitter
implemented function and bind for a specific use. +1 in skill "C++ templates". -1 in dependency "boost".
*/
namespace adagio
{

class Widget;

class Renderfunction_impl
{
public:
	void (*func)( const Widget& );
	Renderfunction_impl(){}
	virtual ~Renderfunction_impl(){}
	Renderfunction_impl(void (*f)( const Widget& ))
	:func(f)
	{}
	virtual Renderfunction_impl* Clone() const
	{
		std::cout<<"Clone base"<<std::endl;
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
	virtual Renderfunction_impl_U* Clone() const
	{
		return new Renderfunction_impl_U(*this);
	} 
	virtual void operator()(const Widget& arg0)
	{
		return func(dynamic_cast<const U &> (arg0));
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
	virtual Renderfunctor_impl* Clone() const
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
	virtual Renderfunctor_impl_U* Clone() const
	{
		return new Renderfunctor_impl_U(*this);
	} 
	virtual void operator()(const Widget& arg0)
	{
		return (o->*func)(dynamic_cast<const U &>(arg0));
	}
};

/* Function: Bind_renderfunction
 * For ordinary functions.
 * */
template<class U>
Renderfunction_impl_U<U> Bind_renderfunction(void (*f)( const U& ))
{
	return Renderfunction_impl_U<U>(f);
}

/* Function: Bind_renderfunction
 * For member functions.
 * */
template<class T, class U>
Renderfunctor_impl_U<T, U> Bind_renderfunction(void (T::*f)( const U& ), T& instance)
{
	return Renderfunctor_impl_U<T, U>(f, instance);
}

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
	
	Renderfunction& operator=(const Renderfunction& o)
	{
		if(o.impl)
			impl = o.impl->Clone();
		else
			impl = NULL;
		return *this;
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
	 * Constructor for bound function.
	 * See Bind_renderfunction
	 * */
	Renderfunction(const Renderfunction_impl& binding)
	{
		impl = binding.Clone();
	}

	void operator()(const Widget& arg0) const
	{
		if(impl)
			(*impl)(arg0);
	}
};

}

#endif
