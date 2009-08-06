#ifndef adagio_button_h
#define adagio_button_h

#include "adagio/Widget.h"
#include <string>

namespace adagio
{

class Button: public Widget
{
public:
	enum Event_type
	{
		EVENT_PRESSED
	};
	virtual Widget* Clone() const;
	virtual void Handle_event(const ALLEGRO_EVENT &event);
	virtual void Render() const;
	void Set_label(const std::string& label);
private:
};

}

#endif
