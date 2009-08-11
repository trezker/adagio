#include "adagio/Button.h"
#include "adagio/Event_queue.h"
#include <allegro5/allegro.h>

namespace adagio
{

Widget* Button::Clone() const
{
	return new Button(*this);
}

void Button::Handle_event(const ALLEGRO_EVENT &event)
{
	if(ALLEGRO_EVENT_MOUSE_AXES == event.type)
	{
		int emx = event.mouse.x;
		int emy = event.mouse.y;
		if(!mouse_over && !(emx<x || emx>x+w || emy<y || emy>y+h))
		{
			mouse_over = true;
		}
		else if(mouse_over && (emx<x || emx>x+w || emy<y || emy>y+h))
		{
			mouse_over = false;
		}
	}
	if(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN == event.type)
	{
		if(mouse_over)
		{
			pressed = true;
		}
	}
	if(ALLEGRO_EVENT_MOUSE_BUTTON_UP == event.type)
	{
		pressed = false;
		if(mouse_over)
		{
			Event e;
			e.source = this;
			e.type = EVENT_PRESSED;
			Push_event(e);
		}
	}
}

void Button::Render() const
{
	renderfunction(*this);
}

void Button::Set_label(const std::string& l)
{
	label = l;
}

std::string Button::Get_label() const
{
	return label;
}

bool Button::Get_pressed() const
{
	return pressed;
}

}
