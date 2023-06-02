#pragma once

#define MAX_DLUGOSC 500
#define MAX_DLUGOSC_TELEFON 13	//Ostatni znak to \0, w chinach np numery maja 11 cyfr

typedef struct {
	int id, wiek;
	char imie[MAX_DLUGOSC];
	char nazwisko[MAX_DLUGOSC];
	char ulica[MAX_DLUGOSC];
	char nr_domu[MAX_DLUGOSC];
	char nr_mieszkania[MAX_DLUGOSC];
	char kod_pocztowy[MAX_DLUGOSC];
	char miasto[MAX_DLUGOSC];
	char nr_telefonu[MAX_DLUGOSC_TELEFON];
	char zapasowy_nr_telefonu[MAX_DLUGOSC_TELEFON];

	struct kontakty* next;
}Kontakty;

Kontakty *kontakty;

extern int ID;

void menu();
void save_to_file_all();
void nowy_kontakt(int wiekk, char* imiee, char* nazwiskoo, char* ulicaa, char* nr_domuu, char* nr_mieszkaniaa, char* kod_pocztowyy,
	char* miastoo, char* nr_telefonuu, char* zapasowy_nr_telefonuu);

void remove_contact();
void dodajKontakt();
void odczytZPliku();

void edytujKontakt();
void wyswietlKontakt();
void wyswietlOd_konkretnegoID();

void swapK(Kontakty* A, Kontakty* B);

//Szukalem innych rozwiazan, ale i tak wszystkie sprowadzaly sie do tego czegos
short porownanieWiek(Kontakty* A, Kontakty* B, int rosnaco);
short porownanieImie(Kontakty* A, Kontakty* B, int rosnaco);
short porownanieNazwisko(Kontakty* A, Kontakty* B, int rosnaco);
short porownanieUlica(Kontakty* A, Kontakty* B, int rosnaco);
short porownanieNr_domu(Kontakty* A, Kontakty* B, int rosnaco);
short porownanieNr_mieszkania(Kontakty* A, Kontakty* B, int rosnaco);
short porownanieKod_pocztowy(Kontakty* A, Kontakty* B, int rosnaco);
short porownanieMiasto(Kontakty* A, Kontakty* B, int rosnaco);
short porownanieNr_telefonu(Kontakty* A, Kontakty* B, int rosnaco);
short porownanieZapasowy_nr_telefonu(Kontakty* A, Kontakty* B, int rosnaco);


void mainSort(int rosnaco, char* pole);
void sort();
