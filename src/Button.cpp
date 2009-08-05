#include "adagio/Button.h"
#include "adagio/Widget_renderer.h"

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
	if(renderfunction)
		(*renderfunction)(*this);
}

}
