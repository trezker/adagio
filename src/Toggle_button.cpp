#include "adagio/Toggle_button.h"
#include "adagio/Event_queue.h"
#include <allegro5/allegro.h>

namespace adagio
{

Toggle_button::Toggle_button()
:active(false)
{
}

Widget* Toggle_button::Clone() const
{
	return new Toggle_button(*this);
}

void Toggle_button::Handle_event(const ALLEGRO_EVENT &event)
{
	if(pressed && ALLEGRO_EVENT_MOUSE_BUTTON_UP == event.type)
	{
		if(mouse_over)
		{
			active = !active;
			Push_event(Event(this, "toggled"));
		}
	}

	Button::Handle_event(event);
	//Todo: toggle
}

void Toggle_button::Render() const
{
	renderfunction(*this);
}

bool Toggle_button::Get_active() const
{
	return active;
}

void Toggle_button::Set_active(bool a)
{
	active = a;
	//Event toggled?
}

}
