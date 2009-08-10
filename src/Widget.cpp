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
	h(0)
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


void Widget::Set_event_queue(Event_queue* e)
{
	event_queue = e;
}

void Widget::Set_renderer(const Renderfunction& r)
{
	renderfunction = r;
}

}
