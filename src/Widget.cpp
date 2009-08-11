#include "adagio/Widget.h"

#ifndef NULL
#define NULL 0
#endif

namespace adagio
{

Widget::Widget()
:	parent(NULL),
	event_queue(NULL),
	x(0),
	y(0),
	w(0),
	h(0),
	mouse_over(false)
{
}

Widget::~Widget()
{
}

void Widget::Set_parent(Widget* p)
{
	parent = p;
}

void Widget::Set_position(int ix, int iy)
{
	x = ix;
	y = iy;
}

void Widget::Set_size(int iw, int ih)
{
	w = iw;
	h = ih;
}

int Widget::Get_x() const
{
	return x;
}

int Widget::Get_y() const
{
	return y;
}

int Widget::Get_w() const
{
	return w;
}

int Widget::Get_h() const
{
	return h;
}

bool Widget::Get_mouse_over() const
{
	return mouse_over;
}

void Widget::Set_event_queue(Event_queue* e)
{
	event_queue = e;
}

void Widget::Set_renderer(const Renderfunction& r)
{
	renderfunction = r;
}

void Widget::Handle_child_event(const Event& event)
{
/*	if(event_queue)
	{
		event_queue.
	}
*/
}

}
