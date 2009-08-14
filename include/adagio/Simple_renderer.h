#ifndef adagio_simple_renderer_h
#define adagio_simple_renderer_h

#include <allegro5/allegro.h>
#include <allegro5/a5_font.h>

namespace adagio
{

class Widget_factory;
class Group;
class Button;
class Toggle_button;
class Radio_button;

class Simple_renderer
{
public:
	Simple_renderer();
	void Init(Widget_factory& factory);
	void Render_group(const Group& group);
	void Render_button(const Button& button);
	void Render_toggle_button(const Toggle_button& button);
	void Render_radio_button(const Radio_button& button);
private:
	ALLEGRO_FONT* font;
};

}

#endif
