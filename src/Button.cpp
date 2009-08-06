#include "adagio/Button.h"

namespace adagio
{

Widget* Button::Clone() const
{
	return new Button(*this);
}

void Button::Handle_event(const ALLEGRO_EVENT &event)
{
}

void Button::Render() const
{
	renderfunction(*this);
}

}
