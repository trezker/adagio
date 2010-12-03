#ifndef adagio_widget_h
#define adagio_widget_h

#include "adagio/Function.h"
union ALLEGRO_EVENT;

namespace adagio
{

class Event_queue;
class Event;

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
	bool Get_mouse_over() const;

	void Set_event_queue(Event_queue* event_queue);
	void Set_renderer(const Function<const Widget&>& renderfunction);
protected:
	void Push_event(const Event& event);
	void Handle_child_event(const Event& event);

	Widget* parent;
	Event_queue* event_queue;
	Function<const Widget&> renderfunction;
	int x;
	int y;
	int w;
	int h;
	bool mouse_over;
private:
};

}

#endif
