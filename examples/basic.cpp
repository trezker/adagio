#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <adagio/adagio.h>
#include <adagio/Simple_renderer.h>

namespace adagio
{
	class Button_pressed_event: public Event
	{
		virtual Event* Clone() const
		{
			return new Button_pressed_event(*this);
		}
	};
}

int main()
{
	try{
		al_init();
		al_install_mouse();
		al_install_keyboard();
		al_init_image_addon();
		al_init_font_addon();
		al_init_ttf_addon();
		
		ALLEGRO_DISPLAY *display;
		al_set_new_display_flags(ALLEGRO_WINDOWED);
		display = al_create_display(640, 480);

		ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
		al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)display);
		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_mouse_event_source());

		adagio::Widget_factory widget_factory;
		adagio::Simple_renderer widget_renderer;
		widget_renderer.Init(widget_factory);
		//Optional, modify the widget prototypes, do skinning and behaviour changes, add custom widgets.

		//Create and set up widgets
		adagio::Button* button = widget_factory.Clone<adagio::Button>("button");
		button->Set_label("Ze button");
/*		button->Set_position(10, 10);
		button->Set_size(100, 30);
*/
		adagio::Toggle_button* toggle_button = widget_factory.Clone<adagio::Toggle_button>("toggle_button");
		toggle_button->Set_label("Ze toggle");
/*		toggle_button->Set_position(10, 50);
		toggle_button->Set_size(100, 30);
*/
		adagio::Radio_button* radio_button1 = widget_factory.Clone<adagio::Radio_button>("radio_button");
		radio_button1->Create_group();
		radio_button1->Set_label("Radio one");
/*		radio_button1->Set_position(10, 100);
		radio_button1->Set_size(100, 30);
*/
		adagio::Radio_button* radio_button2 = widget_factory.Clone<adagio::Radio_button>("radio_button");
		radio_button2->Set_group(radio_button1->Get_group());
		radio_button2->Set_label("Radio two");
/*		radio_button2->Set_position(10, 150);
		radio_button2->Set_size(100, 30);
*/
//		adagio::Group* root = widget_factory.Clone<adagio::Group>("group");
		adagio::VBox* root = widget_factory.Clone<adagio::VBox>("vbox");
		root->Set_position(10, 20);
		root->Set_size(100, 300);
		root->Set_spacing(10);
		root->Add_widget(button);
		root->Add_widget(toggle_button);
		root->Add_widget(radio_button1);
		root->Add_widget(radio_button2);

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
			while(!gui_event_queue.Empty())
			{
				const adagio::Event &gui_event = gui_event_queue.Front();
				if(button == gui_event.source)
				{
					std::cout<<"button "<<std::endl;
//					const adagio::Button_pressed_event& b_event = dynamic_cast<const adagio::Button_pressed_event&>(gui_event);
					if("clicked" == gui_event.type)
					{
						//Do stuff
					}
				}
				if(toggle_button == gui_event.source)
				{
					std::cout<<"toggle_button "<<std::endl;
				}
				std::cout<<gui_event.type.c_str()<<std::endl;
				gui_event_queue.Pop();
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
		std::cout<<param<<std::endl;
	}
	return 0;
}
