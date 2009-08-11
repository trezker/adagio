#ifndef adagio_event_queue_h
#define adagio_event_queue_h

#include <queue>

namespace adagio
{

class Widget;

class Event
{
public:
	Widget* source;
	int type;
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
