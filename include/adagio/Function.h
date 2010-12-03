#ifndef adagio_function_h
#define adagio_function_h

#include <iostream>

#ifndef NULL
#define NULL 0
#endif

/*twitter
implemented function and bind for a specific use. +1 in skill "C++ templates". -1 in dependency "boost".
*/
namespace adagio
{
/*
template <typename V>
class Function_impl
{
public:
	void (*func)( V );
	Function_impl(){}
	virtual ~Function_impl(){}
	Function_impl(void (*f)( V ))
	:func(f)
	{}
	virtual Function_impl* Clone() const
	{
		std::cout<<"Clone base"<<std::endl;
		return new Function_impl(*this);
	}
	virtual void operator()(V arg0)
	{
		return func(arg0);
	}
};
*/
template <typename V>
class Function_impl
{
public:
	void (*func)( V );
	Function_impl(){}
	virtual ~Function_impl(){}
	Function_impl(void (*f)( V ))
	:func(f)
	{}
	virtual Function_impl* Clone() const
	{
		std::cout<<"Clone base"<<std::endl;
		return new Function_impl(*this);
	}
	virtual void operator()(V arg0)
	{
		return func(arg0);
	}
};

template <typename U, typename V>
class Function_impl_U: public Function_impl<V>
{
public:
	void (*func)( U );
	Function_impl_U(void (*f)( U ))
	:func(f)
	{}
	virtual Function_impl_U* Clone() const
	{
		return new Function_impl_U(*this);
	}
	virtual void operator()(V arg0)
	{
		return func(dynamic_cast<U> (arg0));
	}
};

template <class T, typename V>
class Functor_impl : public Function_impl<V>
{
	void (T::*func)( V );
	T *o;
public:
	Functor_impl(void (T::*f)( V ), T& instance)
	:func(f)
	,o(&instance)
	{}
	virtual Functor_impl* Clone() const
	{
		return new Functor_impl(*this);
	}
	virtual void operator()(V arg0)
	{
		return (o->*func)(arg0);
	}
};

template <class T, typename U, typename V>
class Functor_impl_U : public Function_impl<V>
{
	void (T::*func)( U );
	T *o;
public:
	Functor_impl_U(void (T::*f)( U ), T& instance)
	:func(f)
	,o(&instance)
	{}
	virtual Functor_impl_U* Clone() const
	{
		return new Functor_impl_U(*this);
	}
	virtual void operator()(V arg0)
	{
		return (o->*func)(dynamic_cast<U>(arg0));
	}
};

/* Function: Bind_renderfunction
 * For ordinary functions.
 * */
template<typename U>
Function_impl<U> Bind_function(void (*f)( U ))
{
	return Function_impl<U>(f);
}

template<typename U, typename V>
Function_impl_U<U, V> Bind_function(void (*f)( U ))
{
	return Function_impl_U<U, V>(f);
}

/* Function: Bind_renderfunction
 * For member functions.
 * */
template<class T, class U, typename V>
Functor_impl_U<T, U, V> Bind_function(void (T::*f)( U ), T& instance)
{
	return Functor_impl_U<T, U, V>(f, instance);
}

/* Class: Function
 * Universal function container for widget rendering functions.
 * */
template<typename V>
class Function
{
	Function_impl<V>* impl;
public:
	/* Constructor: Function
	 * Creates a function that does nothing.
	 * */
	Function()
	:impl(NULL)
	{
	}
	
	/* Constructor: Function
	 * Copy constructor
	 * */
	Function(const Function& o)
	{
		if(o.impl)
			impl = o.impl->Clone();
		else
			impl = NULL;
	}
	
	Function& operator=(const Function& o)
	{
		if(o.impl)
			impl = o.impl->Clone();
		else
			impl = NULL;
		return *this;
	}

	/* Destructor: ~Function
	 * 
	 * */
	~Function()
	{
		if(impl)
			delete impl;
	}
	
	/* Constructor: Function
	 * Constructor for ordinary function taking the Widget base class as argument.
	 * 
	 * Example:
	 * >void foo(V b);
	 * >Function(foo);
	 * */
	Function(void (*f)( V ))
	{
		impl = new Function_impl<V>(f);
	}

	/* Constructor: Function
	 * Constructor for bound function.
	 * See Bind_renderfunction
	 * */
	Function(const Function_impl<V>& binding)
	{
		impl = binding.Clone();
	}

	void operator()(V arg0) const
	{
		if(impl)
			(*impl)(arg0);
	}
};

}

#endif
