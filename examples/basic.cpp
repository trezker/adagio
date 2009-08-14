#include <allegro5/allegro5.h>
#include <allegro5/a5_iio.h>
#include <allegro5/a5_font.h>
#include <allegro5/a5_ttf.h>
#include <allegro5/a5_primitives.h>
#include <adagio/adagio.h>


namespace adagio
{

	class Button_pressed_event: public Event
	{
		virtual Event* Clone() const
		{
			return new Button_pressed_event(*this);
		}
	};

	class Widget_renderers
	{
	public:
		Widget_renderers()
		:font(NULL)
		{
		}

		void Init()
		{
			font = al_load_font("data/times.ttf", 20, 0);
			if(!font)
				font = al_load_font("examples/data/times.ttf", 20, 0);
		}

		void Render_group(const Group& group)
		{
			const Group::Widgets &widgets = group.Get_widgets();
			for(Group::Widgets::const_iterator i = widgets.begin(); i != widgets.end(); ++i)
			{
				(*i)->Render();
			}
		}
		
		void Render_button(const Button& button)
		{
			int x = button.Get_x();
			int y = button.Get_y();
			int w = button.Get_w();
			int h = button.Get_h();
			if(button.Get_mouse_over())
			{
				if(button.Get_pressed())
					al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgb(50, 50, 50));
				else
					al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgb(200, 200, 200));
			}
			else
				al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgb(100, 100, 100));
			al_draw_text(font, x+w/2, y, ALLEGRO_ALIGN_CENTRE, button.Get_label().c_str());
		}

		void Render_toggle_button(const Toggle_button& button)
		{
			int x = button.Get_x();
			int y = button.Get_y();
			int w = button.Get_w();
			int h = button.Get_h();

			if(button.Get_active() || button.Get_pressed())
				al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgb(50, 50, 50));
			else
				al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgb(100, 100, 100));

			al_draw_text(font, x+w/2, y, ALLEGRO_ALIGN_CENTRE, button.Get_label().c_str());
		}

		void Render_radio_button(const Radio_button& button)
		{
			int x = button.Get_x();
			int y = button.Get_y();
			int w = button.Get_w();
			int h = button.Get_h();

			if(button.Get_active())
				al_draw_filled_circle(x+8, y+8, 6, al_map_rgb(50, 50, 50));
			al_draw_circle(x+8, y+8, 8, al_map_rgb(150, 150, 150), 1);

			al_draw_text(font, x+20, y, ALLEGRO_ALIGN_LEFT, button.Get_label().c_str());
		}
	private:
		ALLEGRO_FONT* font;
	};
	Widget_renderers wr;

	void Init_default_widgets(Widget_factory &wf, Resource_manager &rm)
	{
		wr.Init();
		Button* button = new Button;
		wf.Set_prototype("button", button);
		button->Set_renderer(Bind_renderfunction<Widget_renderers, Button>(&Widget_renderers::Render_button, wr));

		Toggle_button* toggle_button = new Toggle_button;
		wf.Set_prototype("toggle_button", toggle_button);
		toggle_button->Set_renderer(Bind_renderfunction<Widget_renderers, Toggle_button>(&Widget_renderers::Render_toggle_button, wr));

		Radio_button* radio_button = new Radio_button;
		wf.Set_prototype("radio_button", radio_button);
		radio_button->Set_renderer(Bind_renderfunction<Widget_renderers, Radio_button>(&Widget_renderers::Render_radio_button, wr));

		Group* group = new Group;
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
		button->Set_position(10, 10);
		button->Set_size(100, 30);

		adagio::Toggle_button* toggle_button = widget_factory.Clone<adagio::Toggle_button>("toggle_button");
		toggle_button->Set_label("Ze toggle");
		toggle_button->Set_position(10, 50);
		toggle_button->Set_size(100, 30);

		adagio::Radio_button* radio_button1 = widget_factory.Clone<adagio::Radio_button>("radio_button");
		radio_button1->Create_group();
		radio_button1->Set_label("Radio one");
		radio_button1->Set_position(10, 100);
		radio_button1->Set_size(100, 30);

		adagio::Radio_button* radio_button2 = widget_factory.Clone<adagio::Radio_button>("radio_button");
		radio_button2->Set_group(radio_button1->Get_group());
		radio_button2->Set_label("Radio two");
		radio_button2->Set_position(10, 150);
		radio_button2->Set_size(100, 30);

		adagio::Group* root = widget_factory.Clone<adagio::Group>("group");
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
					printf("button ");
//					const adagio::Button_pressed_event& b_event = dynamic_cast<const adagio::Button_pressed_event&>(gui_event);
					if("clicked" == gui_event.type)
					{
						//Do stuff
					}
				}
				if(toggle_button == gui_event.source)
				{
					printf("toggle_button ");
				}
				printf("%s\n", gui_event.type.c_str());
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
		printf("%s\n", param);
	}
	return 0;
}
