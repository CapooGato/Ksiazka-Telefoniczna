#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Ulatwienie_sobie_zycia_allegro.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>




//Sprawdza czy sa jakies bledy przy inicjalizacji bibliotek allegro
int inicjalizacja_allegro()
{
	al_init();
	if (!al_init())
	{
		fprintf(stderr, "\nBlad inicjalizacji \"al_init()\"");
		return -1;
	}

	al_install_mouse();
	if (!al_install_mouse())
	{
		fprintf(stderr, "\nBlad inicjalizacji \"al_install_mouse()\"");
		return -1;
	}

	al_init_primitives_addon();
	if (!al_install_mouse())
	{
		fprintf(stderr, "\nBlad inicjalizacji \"al_init_primitives_addon()\"");
		return -1;
	}
	
	al_init_image_addon();
	if (!al_init_image_addon())
	{
		fprintf(stderr, "\nBlad inicjalizacji \"al_init_image_addon()\"");
		return -1;
	}

	return 0;
}

//Ekran glowny i jego inputy: {mysz, etc}
int Ekran_glowny()
{
	bool zakoncz = 0;
	ALLEGRO_DISPLAY* display = NULL;
	display = al_create_display(1000, 1000);			
	al_set_window_title(display, "Donde esta la biblioteca");	
	
	//!!!!!!!!!!!!!!zdj sie resetuje jak zminimalizuje ekran!!!!!!!!!!!!
	ALLEGRO_BITMAP* tlo = al_load_bitmap("C:\\Users\\Seweryn\\Desktop\\Studia\\Semestr 2\\Podstawy programowania 2\\Projekt\\Tlo.png");
	al_draw_bitmap(tlo, 0, 0, 0);
	al_flip_display();

	


	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	while (!zakoncz)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (event.mouse.x >= 0 && event.mouse.x <= 200 &&
				event.mouse.y >= 0 && event.mouse.y <= 150) {
				printf("Przycisk zosta³ klikniêty\n");
			}
		}
	}
	al_flip_display();
	al_destroy_display(display);
	al_destroy_bitmap(tlo);
	al_destroy_event_queue(queue);
	al_uninstall_mouse();
	return 0;
}