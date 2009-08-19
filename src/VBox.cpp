#include "adagio/VBox.h"

namespace adagio
{

Widget* VBox::Clone() const
{
	return new VBox(*this);
}

void VBox::Handle_event(const ALLEGRO_EVENT &event)
{
	for(Widgetlist::iterator i = widgets.begin(); i != widgets.end(); ++i)
	{
		(*i)->Handle_event(event);
	}
}

void VBox::Render() const
{
	renderfunction(*this);
}

void VBox::Add_widget(Widget* wi)
{
	widgets.push_back(wi);
	wi->Set_parent(this);
	int num_widgets = widgets.size();
	int widget_h = (h+(num_widgets-1)*spacing)/num_widgets;
	int widget_y = y;
	for(Widgetlist::iterator i = widgets.begin(); i != widgets.end(); ++i)
	{
		(*i)->Set_position(x, widget_y);
		(*i)->Set_size(w, widget_h);
		widget_y += widget_h + spacing;
	}
}

const Widgetlist& VBox::Get_widgets() const
{
	return widgets;
}

void VBox::Set_spacing(int s)
{
	spacing = s;
}

int VBox::Get_spacing() const
{
	return spacing;
}

}
