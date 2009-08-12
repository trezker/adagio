#include "adagio/Button.h"
#include "adagio/Event_queue.h"
#include <allegro5/allegro.h>

namespace adagio
{

Button::Button()
:pressed(false)
{
}

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
			Push_event(Event(this, "enter"));
		}
		else if(mouse_over && (emx<x || emx>x+w || emy<y || emy>y+h))
		{
			mouse_over = false;
			Push_event(Event(this, "leave"));
		}
	}
	if(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN == event.type)
	{
		if(mouse_over)
		{
			pressed = true;
			Push_event(Event(this, "pressed"));
		}
	}
	if(pressed && ALLEGRO_EVENT_MOUSE_BUTTON_UP == event.type)
	{
		pressed = false;
		Push_event(Event(this, "released"));
		if(mouse_over)
		{
			Push_event(Event(this, "clicked"));
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
