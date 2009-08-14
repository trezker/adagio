#include "adagio/Radio_button.h"
#include "adagio/Event_queue.h"
#include <allegro5/allegro.h>
#include <algorithm>

namespace adagio
{
	/* Rules:
	 * The radio button has one group.
	 * The radio button is in its group.
	 * The radio button removes itself from its group
	 * 	a) in destructor
	 *  b) in Set_group
	 * The radio button deletes its group when it becomes empty.
	*/

	Radio_button::Radio_button(Radio_group* g)
	:group(g)
	,active(false)
	{
		if(!group)
			group = new Radio_group;
		group->push_back(this);
	}

	Radio_button::Radio_button(const Radio_button& o)
	:group(o.group)
	,active(false)
	{
		Set_renderer(o.renderfunction);
		if(!group)
			group = new Radio_group;
		group->push_back(this);
	}

	Radio_button::~Radio_button()
	{
		group->erase(std::find(group->begin(), group->end(), this));
		if(group->empty())
			delete group;
	}

	void Radio_button::Create_group()
	{
		Set_group(new Radio_group);
	}

	void Radio_button::Set_group(Radio_group* g)
	{
		if(g != NULL)
		{
			group->erase(std::find(group->begin(), group->end(), this));
			if(group->empty())
				delete group;
			group = g;
			group->push_back(this);
		}
	}

	Radio_button::Radio_group* Radio_button::Get_group() const
	{
		return group;
	}

	Widget* Radio_button::Clone() const
	{
		return new Radio_button(*this);
	}

	void Radio_button::Handle_event(const ALLEGRO_EVENT &event)
	{
		if(pressed && ALLEGRO_EVENT_MOUSE_BUTTON_UP == event.type)
		{
			if(mouse_over)
			{
				if(!active)
				{
					for(Radio_group::iterator i = group->begin(); i != group->end(); ++i)
					{
						if(*i == this)
							continue;
						(*i)->Set_active(false);
					}
					active = !active;
					Push_event(Event(this, "toggled"));
				}
			}
		}

		Button::Handle_event(event);
	}

	void Radio_button::Render() const
	{
		renderfunction(*this);
	}

	bool Radio_button::Get_active() const
	{
		return active;
	}

	void Radio_button::Set_active(bool a)
	{
		if(active != a)
		{
			if(!active)
			{
				printf("Should not happen");
				for(Radio_group::iterator i = group->begin(); i != group->end(); ++i)
				{
					if(*i == this)
						continue;
					(*i)->Set_active(false);
				}
			}
			active = a;
			Push_event(Event(this, "toggled"));
		}
	}

}
