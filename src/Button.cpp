#include "adagio/Button.h"
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

}
