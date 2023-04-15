#pragma once
//max dlugosc danych jaka mozna wpisac 
#define MAX_DLUGOSC 25
//max liczba kontaktow w ksiazce telefonicznej
#define MAX_KONTAKTOW 10
typedef struct {
	int id, wiek;
	char imie[MAX_DLUGOSC];
	char nazwisko[MAX_DLUGOSC];
	char ulica[MAX_DLUGOSC];
	char nr_domu[MAX_DLUGOSC];
	char nr_mieszkania[MAX_DLUGOSC];
	char kod_pocztowy[MAX_DLUGOSC];
	char miasto[MAX_DLUGOSC];
	char nr_telefonu[MAX_DLUGOSC];
	char zapasowy_nr_telefonu[MAX_DLUGOSC];

	struct kontakty* next;
}Kontakty;

//Deklarujemy tablice kontaktow, ułatwia to znacznie prace nad projektem, rozmiar tutaj to 10, bo w fazie testowania nie ma potrzeby użycia wiekszej
//w finalnej wersji projektu zostanie to zmienione na przykladowo 9999999, lub w ogole zniesiemy limit.
Kontakty kontakty[MAX_KONTAKTOW];

extern int ID;
/*Funkcje sa opisane w pliku Lista.c*/
void remove_contact();
void save_to_file_all();
void nowy_kontakt(int wiekk, char* imiee, char* nazwiskoo, char* ulicaa, char* nr_domuu, char* nr_mieszkaniaa, char* kod_pocztowyy,
	char* miastoo, char* nr_telefonuu, char* zapasowy_nr_telefonuu);
void menu();
void ID_check();
