#pragma once

#define MAX_DLUGOSC 25
#define MAX_KONTAKTOW 50
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

Kontakty kontakty[MAX_KONTAKTOW];

extern int ID;

void remove_contact();
void save_to_file_all();
void nowy_kontakt(int wiekk, char* imiee, char* nazwiskoo, char* ulicaa, char* nr_domuu, char* nr_mieszkaniaa, char* kod_pocztowyy,
	char* miastoo, char* nr_telefonuu, char* zapasowy_nr_telefonuu);
void menu();
void ID_check();
void dodajKontakt();
void odczytZPliku();
