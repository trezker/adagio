#ifndef adagio_widget_h
#define adagio_widget_h

namespace adagio
{

struct ALLEGRO_EVENT;
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

	void Set_event_queue(Event_queue* event_queue);

	void Set_renderer(Renderfunction* renderfunction);
protected:
	Widget* parent;
	Event_queue* event_queue;
	Renderfunction* renderfunction;
	int x;
	int y;
	int w;
	int h;
private:
};

}

#endif
