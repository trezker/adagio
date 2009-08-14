#ifndef adagio_toggle_button_h
#define adagio_toggle_button_h

#include "adagio/Button.h"

namespace adagio
{

class Toggle_button: public Button
{
public:
	Toggle_button();
	virtual Widget* Clone() const;
	virtual void Handle_event(const ALLEGRO_EVENT &event);
	virtual void Render() const;
	bool Get_active() const;
	void Set_active(bool active);
private:
	bool active;
};

}

#endif
