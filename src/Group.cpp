#include "adagio/Group.h"

namespace adagio
{

Widget* Group::Clone() const
{
	return new Group(*this);
}

void Group::Handle_event(const ALLEGRO_EVENT &event)
{
	for(Widgets::iterator i = widgets.begin(); i != widgets.end(); ++i)
	{
		(*i)->Handle_event(event);
	}
}

void Group::Render() const
{
	renderfunction(*this);
}

void Group::Add_widget(Widget* w)
{
	widgets.push_back(w);
}

const Group::Widgets& Group::Get_widgets() const
{
	return widgets;
}

}
