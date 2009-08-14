#ifndef adagio_radio_button_h
#define adagio_radio_button_h

#include "adagio/Button.h"
#include <list>

namespace adagio
{

class Radio_button: public Button
{
public:
	typedef std::list<Radio_button*> Radio_group;

	Radio_button(Radio_group* group = NULL);
	Radio_button(const Radio_button& o);
	~Radio_button();
	virtual Widget* Clone() const;
	virtual void Handle_event(const ALLEGRO_EVENT &event);
	virtual void Render() const;

	bool Get_active() const;
	void Set_active(bool active);

	void Create_group();
	void Set_group(Radio_group* group);
	Radio_group* Get_group() const;
private:
	Radio_group* group;
	bool active;
};

}

#endif
