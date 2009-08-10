#ifndef adagio_widget_h
#define adagio_widget_h

#include "adagio/Renderfunction.h"
union ALLEGRO_EVENT;

namespace adagio
{

class Event_queue;
class Renderfunction;

/* Class: Widget
 * */
class Widget
{
public:
	Widget();
	virtual ~Widget();
	/* Function: Clone
	 * Clones the Widget instance and returns the copy.
	 * */
	virtual Widget* Clone() const = 0;
	virtual void Handle_event(const ALLEGRO_EVENT &event) = 0;
	virtual void Render() const = 0;

	void Set_parent(Widget* parent);

	void Set_position(int x, int y);
	void Set_size(int w, int h);
	int Get_x() const;
	int Get_y() const;
	int Get_w() const;
	int Get_h() const;

	void Set_event_queue(Event_queue* event_queue);
	void Set_renderer(const Renderfunction& renderfunction);
protected:
	Widget* parent;
	Event_queue* event_queue;
	Renderfunction renderfunction;
	int x;
	int y;
	int w;
	int h;
private:
};

}

#endif
