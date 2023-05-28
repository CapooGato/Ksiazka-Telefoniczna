#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Lista.h"

/*Z racji, ze Visual Studio, nie jest stworzone dla jezyka C, tylko dla C++, wystepuja warningi, bledy z tym zwiazne, najczesciej dotycza one naruszenia dostepu.
Mozliwe jest, ze bedzie potrzeba dodania "_CRT_SECURE_NO_WARNINGS", bez "" w: projekt -> Wlasciwosci -> C/C++ -> Preprocesor -> Definicje Preprocesora -> Lewy przycisk ->
-> edytuj -> definicje preprocesora -> wpisac:  _CRT_SECURE_NO_WARNINGS  */
int main(int argc, int** argv)
{

	//
	//nowy_kontakt(19, "D", "Karwat", "Fajna", "62B", "0", "26-065", "Pieksozow", "888111444", "111000222");

	//nowy_kontakt(20, "C", "Kawecki", "Fajna", "62B", "0", "26-065", "Pieksozow", "999888111", "111000222");
	//
	//nowy_kontakt(19, "A", "Gesler", "Fajna", "62B", "0", "26-065", "Pieksozow", "999111888", "000999888");

 //   nowy_kontakt(20, "Kapitan", "Tytus", "Nie_Fajna", "62B", "0", "26-065", "Pieksozow", "222333444", "555666777");


	menu();

	return 0;
}
