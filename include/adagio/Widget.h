#ifndef adagio_widget_h
#define adagio_widget_h

namespace adagio
{

class Event_queue;
class Widget_renderer;

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

	void Set_parent(Widget* parent);

	void Set_position(int x, int y);
	void Set_size(int w, int h);
	void Set_event_queue(Event_queue* event_queue);

	void Set_renderer(Widget_renderer* renderer);
	virtual void Render() const = 0;
private:
	Widget* parent;
	Widget_renderer* renderer;
	Event_queue* event_queue;
	int x;
	int y;
	int w;
	int h;
};

}

#endif
