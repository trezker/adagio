#ifndef adagio_button_h
#define adagio_button_h

#include "adagio/Widget.h"

namespace adagio
{

class Button: public Widget
{
public:
	virtual Widget* Clone() const;
	virtual void Handle_event(const ALLEGRO_EVENT &event);
	virtual void Render() const;
private:
};

}

#endif
