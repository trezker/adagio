#ifndef adagio_event_queue_h
#define adagio_event_queue_h

namespace adagio
{

class Widget;

class Event
{
public:
	Widget* source;
	int type;
};

class Event_queue
{
public:
	bool Get_next_event(Event &e);
private:
};

}

#endif
