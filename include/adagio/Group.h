#ifndef adagio_group_h
#define adagio_group_h

#include "adagio/Widget.h"
#include <string>
#include <list>

namespace adagio
{

class Group: public Widget
{
public:
	virtual Widget* Clone() const;
	virtual void Handle_event(const ALLEGRO_EVENT &event);
	virtual void Render() const;
	void Add_widget(Widget* w);
	typedef std::list<Widget*> Widgets;
	const Widgets& Get_widgets() const;
private:
	Widgets widgets;	
};

}

#endif
