#ifndef adagio_vbox_h
#define adagio_vbox_h

#include "adagio/Widget.h"
#include <list>

namespace adagio
{

typedef std::list<Widget*> Widgetlist;

class VBox: public Widget
{
public:
	virtual Widget* Clone() const;
	virtual void Handle_event(const ALLEGRO_EVENT &event);
	virtual void Render() const;
	void Add_widget(Widget* w);
	const Widgetlist& Get_widgets() const;
	void Set_spacing(int spacing);
	int Get_spacing() const;
private:
	Widgetlist widgets;
	int spacing;
};

}

#endif
