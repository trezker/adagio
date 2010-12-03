#include "adagio/Simple_renderer.h"
#include "adagio/Widget_factory.h"

#include "adagio/Group.h"
#include "adagio/VBox.h"

#include "adagio/Button.h"
#include "adagio/Toggle_button.h"
#include "adagio/Radio_button.h"

#include <allegro5/allegro_primitives.h>

namespace adagio
{

Simple_renderer::Simple_renderer()
:font(NULL)
{
}

void Simple_renderer::Init(Widget_factory& factory)
{
	font = al_load_font("data/times.ttf", 20, 0);
	if(!font)
		font = al_load_font("examples/data/times.ttf", 20, 0);

	Button* button = new Button;
	factory.Set_prototype("button", button);
	button->Set_renderer(Bind_function<Simple_renderer, const Button&, const Widget&>(&Simple_renderer::Render_button, *this));

	Toggle_button* toggle_button = new Toggle_button;
	factory.Set_prototype("toggle_button", toggle_button);
	toggle_button->Set_renderer(Bind_function<Simple_renderer, const Toggle_button&, const Widget&>(&Simple_renderer::Render_toggle_button, *this));

	Radio_button* radio_button = new Radio_button;
	factory.Set_prototype("radio_button", radio_button);
	radio_button->Set_renderer(Bind_function<Simple_renderer, const Radio_button&, const Widget&>(&Simple_renderer::Render_radio_button, *this));

	Group* group = new Group;
	factory.Set_prototype("group", group);
	group->Set_renderer(Bind_function<Simple_renderer, const Group&, const Widget&>(&Simple_renderer::Render_group, *this));

	VBox* vbox = new VBox;
	factory.Set_prototype("vbox", vbox);
	vbox->Set_renderer(Bind_function<Simple_renderer, const VBox&, const Widget&>(&Simple_renderer::Render_vbox, *this));
}

void Simple_renderer::Render_group(const Group& group)
{
	const Group::Widgets &widgets = group.Get_widgets();
	for(Group::Widgets::const_iterator i = widgets.begin(); i != widgets.end(); ++i)
	{
		(*i)->Render();
	}
}

void Simple_renderer::Render_vbox(const VBox& vbox)
{
	const Group::Widgets &widgets = vbox.Get_widgets();
	for(Group::Widgets::const_iterator i = widgets.begin(); i != widgets.end(); ++i)
	{
		(*i)->Render();
	}
}

void Simple_renderer::Render_button(const Button& button)
{
	int x = button.Get_x();
	int y = button.Get_y();
	int w = button.Get_w();
	int h = button.Get_h();
	if(button.Get_mouse_over())
	{
		if(button.Get_pressed())
			al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgb(50, 50, 50));
		else
			al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgb(200, 200, 200));
	}
	else
		al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgb(100, 100, 100));
	al_draw_text(font, al_map_rgb_f(1, 1, 1), x+w/2, y, ALLEGRO_ALIGN_CENTRE, button.Get_label().c_str());
}

void Simple_renderer::Render_toggle_button(const Toggle_button& button)
{
	int x = button.Get_x();
	int y = button.Get_y();
	int w = button.Get_w();
	int h = button.Get_h();

	if(button.Get_active() || button.Get_pressed())
		al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgb(50, 50, 50));
	else
		al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgb(100, 100, 100));

	al_draw_text(font, al_map_rgb_f(1, 1, 1), x+w/2, y, ALLEGRO_ALIGN_CENTRE, button.Get_label().c_str());
}

void Simple_renderer::Render_radio_button(const Radio_button& button)
{
	int x = button.Get_x();
	int y = button.Get_y();
	int w = button.Get_w();
	int h = button.Get_h();

	if(button.Get_active())
		al_draw_filled_circle(x+8, y+8, 6, al_map_rgb(50, 50, 50));
	al_draw_circle(x+8, y+8, 8, al_map_rgb(150, 150, 150), 1);

	al_draw_text(font, al_map_rgb_f(1, 1, 1), x+20, y, ALLEGRO_ALIGN_LEFT, button.Get_label().c_str());
}

}
