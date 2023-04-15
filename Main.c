#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Lista.h"
#include <allegro5/allegro5.h>
#include "Ulatwienie_sobie_zycia_allegro.h"

/*Z racji, ze Visual Studio, nie jest stworzone dla jezyka C, tylko dla C++, wystepuja warningi, bledy z tym zwiazne, najczesciej dotycza one naruszenia dostepu.
Mozliwe jest, ze bedzie potrzeba dodania "_CRT_SECURE_NO_WARNINGS", bez "" w: projekt -> Wlasciwosci -> C/C++ -> Preprocesor -> Definicje Preprocesora -> Lewy przycisk -> 
-> edytuj -> definicje preprocesora -> wpisac:  _CRT_SECURE_NO_WARNINGS  */
int main(int argc, int **argv)
{
	/*Reczne dodanie kilku kontaktow*/

	nowy_kontakt(19,"Damian", "Karwat", "Kielce", "62B", "0", "26-065", "Pieksozow", "888111444", "111000222");
	nowy_kontakt(20,"Seweryn", "Kawecki", "Kielce", "62B", "0", "26-065", "Pieksozow", "999888111", "111000222");
	nowy_kontakt(19, "Magda", "Gesler", "Kielce", "62B", "0", "26-065", "Pieksozow", "999111888", "000999888");
	nowy_kontakt(20, "Kapitan", "Tytus", "Kielce", "62B", "0", "26-065", "Pieksozow", "222333444", "555666777");
	
	save_to_file_all();

	//Menu
	menu();

	/*Zabawa z dzialaniem allegro, ktore jest na drugi kamien milowy*/
	//inicjalizacja_allegro(); 
	//Ekran_glowny();
	return 0;
}
