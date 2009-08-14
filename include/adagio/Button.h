#ifndef adagio_button_h
#define adagio_button_h

#include "adagio/Widget.h"
#include <string>

namespace adagio
{

class Button: public Widget
{
public:
	Button();
	virtual Widget* Clone() const;
	virtual void Handle_event(const ALLEGRO_EVENT &event);
	virtual void Render() const;
	void Set_label(const std::string& label);
	std::string Get_label() const;
	bool Get_pressed() const;
protected:
	std::string label;
	bool pressed;
};

}

#endif
