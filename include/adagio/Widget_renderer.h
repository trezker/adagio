#ifndef adagio_widget_renderer_h
#define adagio_widget_renderer_h

namespace adagio
{

/* Class: Widget
 * */
class Widget_renderer
{
public:
	Widget();
	virtual ~Widget_renderer();
};

class Default_widget_renderer
{
public:
	void Render(Group* w);
	void Render(Button* w);
};

}

#endif
