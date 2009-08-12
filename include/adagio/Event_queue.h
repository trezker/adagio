#ifndef adagio_event_queue_h
#define adagio_event_queue_h

#include <queue>
#include <string>

namespace adagio
{

#define TYPE_ID(a,b,c,d)     (((a)<<24) | ((b)<<16) | ((c)<<8) | (d))

class Widget;

class Event
{
public:
	Event(Widget* source, const std::string& type);
	Widget* source;
	std::string type;
	virtual Event* Clone() const;
};

class Event_queue
{
public:
	~Event_queue();
	void Push(const Event& e);
	void Pop();
	bool Empty() const;
	const Event& Front() const;
private:
	typedef std::queue<Event*> Events;
	Events events;
};

}

#endif
