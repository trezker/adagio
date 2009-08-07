#include <allegro5/allegro5.h>
#include <allegro5/a5_iio.h>
#include <allegro5/a5_font.h>
#include <allegro5/a5_ttf.h>
#include <adagio/adagio.h>


namespace adagio
{

/*	void Render_group(const Widget& widget)
	{
		const Group& group = dynamic_cast<const Group&>(widget);
		const Group::Widgets &widgets = group.Get_widgets();
		for(Group::Widgets::const_iterator i = widgets.begin(); i != widgets.end(); ++i)
		{
			(*i)->Render();
		}
	}
*/
//adagio::Renderfunctor_impl_U<adagio::Widget_renderers, adagio::Group>::Renderfunctor_impl_U(void (adagio::Widget_renderers::*)(const adagio::Widget&), adagio::Widget_renderers&)
//adagio::Renderfunctor_impl_U<adagio::Widget_renderers, adagio::Group>::Renderfunctor_impl_U(void (adagio::Widget_renderers::*)(const adagio::Group&), adagio::Widget_renderers&)
//adagio::Renderfunctor_impl_U<adagio::Widget_renderers, adagio::Group>::Renderfunctor_impl_U(const adagio::Renderfunctor_impl_U<adagio::Widget_renderers, adagio::Group>&)

	class Widget_renderers
	{
	public:
		void Render_group(const Group& group)
		{
			const Group::Widgets &widgets = group.Get_widgets();
			for(Group::Widgets::const_iterator i = widgets.begin(); i != widgets.end(); ++i)
			{
				(*i)->Render();
			}
		}
	};
	Widget_renderers wr;

	void Render_group(const Group& group)
	{
		const Group::Widgets &widgets = group.Get_widgets();
		for(Group::Widgets::const_iterator i = widgets.begin(); i != widgets.end(); ++i)
		{
			(*i)->Render();
		}
	}

	void Init_default_widgets(Widget_factory &wf, Resource_manager &rm)
	{
		Button* button = new Button;
		wf.Set_prototype("button", button);


		Group* group = new Group;
//		group->Set_renderer(Bind_renderfunction<Group>(Render_group));
		group->Set_renderer(Bind_renderfunction<Widget_renderers, Group>(&Widget_renderers::Render_group, wr));
		wf.Set_prototype("group", group);
	}
}

int main()
{
	try{
		al_init();
		al_install_mouse();
		al_install_keyboard();
		al_init_iio_addon();
		al_init_font_addon();
		al_init_ttf_addon();
		
		ALLEGRO_DISPLAY *display;
		al_set_new_display_flags(ALLEGRO_WINDOWED);
		display = al_create_display(640, 480);

		ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
		al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)display);
		al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)al_get_keyboard());
		al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)al_get_mouse());

		adagio::Resource_manager resource_manager;
		adagio::Widget_factory widget_factory;
		adagio::Init_default_widgets(widget_factory, resource_manager); //Sets up default widgets
		//Optional, modify the widget prototypes, do skinning and behaviour changes, add custom widgets.

		//Create and set up widgets
		adagio::Button* button = widget_factory.Clone<adagio::Button>("button");
		button->Set_label("Ze button");

		adagio::Group* root = widget_factory.Clone<adagio::Group>("group");
		root->Add_widget(button);

		adagio::Event_queue gui_event_queue;
		root->Set_event_queue(&gui_event_queue); //All widgets send events to parent.

	//	double last_time = al_current_time();
		bool quit = false;
		while(!quit)
		{
			ALLEGRO_EVENT event;
			if (al_get_next_event(event_queue, &event))
			{
				if (ALLEGRO_EVENT_KEY_DOWN == event.type)
				{
					if (ALLEGRO_KEY_ESCAPE == event.keyboard.keycode)
					{
						break;
					}
				}
				if (ALLEGRO_EVENT_DISPLAY_CLOSE == event.type)
				{
					break;
				}
				root->Handle_event(event);
			}

	/*		double current_time = al_current_time();
			double dt = current_time - last_time;
			last_time = current_time;
	*/
			adagio::Event gui_event;
			while(gui_event_queue.Get_next_event(gui_event))
			{
				if(button == gui_event.source && adagio::Button::EVENT_PRESSED == gui_event.type)
				{
					//do stuff
				}
			}
			//Update other stuff

			//Render other stuff
			root->Render();
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_rest(0.001);
		}

		delete button;
		delete root;

		al_destroy_event_queue(event_queue);
		al_destroy_display(display);
	}
	catch(const char* param)
	{
		printf("%s\n", param);
	}
	return 0;
}
