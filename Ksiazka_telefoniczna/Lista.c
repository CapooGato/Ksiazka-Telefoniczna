/**
 * @file Lista.c
 * @brief Implementacja funkcji dla modulu Listy.
 */

#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Zmienna globalna przechowujaca aktualne ID.
 *
 * Zmienna jest dostepna z zewnatrz (extern).
 */
int ID = 0;


/**
 * @brief Wyswietla menu glowne.
 */
void menu()
{
	kontakty = (Kontakty*)malloc(sizeof(Kontakty) * 5);
	int wybor;
	do {
		printf("\n 0 = zakoncz,\n 1 = dodaj nowa osobe do ksiazki telefonicznej,\n 2 = usun kontakt po ID,\n 3 = Edytuj kontakt\n"
			" 4 = wyswietl dane kontaktu po ID\n 5 = wyswietl od konkretnego ID,\n 6 = Sortowanie \nWybor: ");
		scanf("%i", &wybor);
		switch (wybor)
		{
		case 1:
		{
			dodajKontakt();	break;
		}
		case 2:
		{
			remove_contact(); break;

		}
		case 3:
		{
			edytujKontakt(); break;
		}
		case 4:
		{
			wyswietlKontakt(); break;
		}
		case 5:
		{
			wyswietlOd_konkretnegoID(); break;
		}
		case 6:
		{
			sort();	break;
		}
		}

	} while (wybor != 0);
}

/**
 * @brief Zapisuje wszystkie kontakty do pliku.
 */
void save_to_file_all()
{
	//Plik ottwarty w trybie nadpisywania
	FILE* plik;
	plik = fopen("Kontakty.txt", "w");

	if (!plik)
	{
		printf("\nBlad otwarcia pliku!");
		return;
	}

	//Ustawiamy wskaznik pliku na jego poczatek, jest to potrzebne bo inaczej moze on byc w randomowym miesjcu co prowadzi do niepraawidlowosci
	rewind(plik);

	//wpisujemy wszystkie osoby do pliku
	int numer = 0;
	for (numer; numer < ID; numer++)
	{
		fprintf(plik, "ID: %i \n %i, %s %s \n %s %s %s \n %s %s \n %s %s \n\n", kontakty[numer].id, kontakty[numer].wiek, kontakty[numer].imie
			, kontakty[numer].nazwisko, kontakty[numer].ulica, kontakty[numer].nr_domu, kontakty[numer].nr_mieszkania, kontakty[numer].kod_pocztowy
			, kontakty[numer].miasto, kontakty[numer].nr_telefonu, kontakty[numer].zapasowy_nr_telefonu);
	}
	fclose(plik);
}

/**
 * @brief Dodaje nowy kontakt.
 *
 * @param wiekk                   Wiek kontaktu.
 * @param imiee                   Imie kontaktu.
 * @param nazwiskoo               Nazwisko kontaktu.
 * @param ulicaa                  Ulica kontaktu.
 * @param nr_domuu                Numer domu kontaktu.
 * @param nr_mieszkaniaa          Numer mieszkania kontaktu.
 * @param kod_pocztowyy           Kod pocztowy kontaktu.
 * @param miastoo                 Miasto kontaktu.
 * @param nr_telefonuu            Numer telefonu kontaktu.
 * @param zapasowy_nr_telefonuu   Zapasowy numer telefonu kontaktu.
 */
void nowy_kontakt(int wiekk, char* imiee, char* nazwiskoo, char* ulicaa, char* nr_domuu, char* nr_mieszkaniaa, char* kod_pocztowyy,
	char* miastoo, char* nr_telefonuu, char* zapasowy_nr_telefonuu)
{
	odczytZPliku();
	if ((ID) % 5 == 0)
	{
		Kontakty* nowaTablica = (Kontakty*)realloc(kontakty, sizeof(Kontakty) * (ID + 8));
		kontakty = nowaTablica;
	}
	FILE* plik;
	plik = fopen("Kontakty.txt", "a+");
	kontakty[ID].id = ID;
	kontakty[ID].wiek = wiekk;

	strncpy(kontakty[ID].imie, imiee, MAX_DLUGOSC);

	strncpy(kontakty[ID].nazwisko, nazwiskoo, MAX_DLUGOSC);

	strncpy(kontakty[ID].ulica, ulicaa, MAX_DLUGOSC);

	strncpy(kontakty[ID].nr_domu, nr_domuu, MAX_DLUGOSC);

	strncpy(kontakty[ID].nr_mieszkania, nr_mieszkaniaa, MAX_DLUGOSC);

	strncpy(kontakty[ID].kod_pocztowy, kod_pocztowyy, MAX_DLUGOSC);

	strncpy(kontakty[ID].miasto, miastoo, MAX_DLUGOSC);

	strncpy(kontakty[ID].nr_telefonu, nr_telefonuu, MAX_DLUGOSC_TELEFON);

	strncpy(kontakty[ID].zapasowy_nr_telefonu, zapasowy_nr_telefonuu, MAX_DLUGOSC_TELEFON);

	//Ustawienia wksaznikow na nastepna strukture, jesli struktura jest pierwsza to wskazuje na null
	if (ID == 0)
		kontakty[ID].next = NULL;
	else
	{
		kontakty[ID - 1].next = &kontakty[ID];
		kontakty[ID].next = NULL;
	}

	fprintf(plik, "ID: %d \n %i, %s %s \n %s %s %s \n %s %s \n %s %s \n\n", kontakty[ID].id, kontakty[ID].wiek, kontakty[ID].imie
		, kontakty[ID].nazwisko, kontakty[ID].ulica, kontakty[ID].nr_domu, kontakty[ID].nr_mieszkania, kontakty[ID].kod_pocztowy
		, kontakty[ID].miasto, kontakty[ID].nr_telefonu, kontakty[ID].zapasowy_nr_telefonu);

	//Po dodaniu osoby zwiekszamy pomocnicze ID
	ID++;
	fclose(plik);
	puts("\nPomyslnie dodano do pliku.\n");
}


/**
 * @brief Usuwa kontakt.
 *
 * Funkcja remove_contact() sluzy do usuwania kontaktu z systemu.
 * Po wywolaniu tej funkcji, kontakt zostanie trwale usuniety z systemu.
 */
void remove_contact()
{
	odczytZPliku();
	//Jesli ID jest mniejsze od 0 to znaczy ze plik jest pusty
	if (ID < 0)
	{
		puts("\n\nNie ma jeszcze zadnych kontaktow!");
		return;
	}

	int iremove = 0;
	printf("\nPodaj ID osoby ktora chcesz usunac: ");
	scanf("%d", &iremove);

	/*Fix bledu gdzie, remove 3 moglo usuwac index o wartosci 3, jak i potem 2*/
	if (iremove < 0 || iremove >= ID)
	{
		puts("Podaj prawidlowa liczbe indeksu!");
		return;
	}

 
	for (iremove; iremove < ID - 1; iremove++)
	{
		kontakty[iremove] = kontakty[iremove + 1];
		kontakty[iremove].id--;
	}

	//Po usunieciu kontaktu pomocnicze ID sie zmniejsza o 1
	ID--;

	//Zapisujemy zmienione kontakty do pliku
	save_to_file_all();
}

/**
 * @brief Dodaje nowy kontakt.
 *
 * Funkcja dodajKontakt() sluzy do dodawania nowego kontaktu do systemu.
 * Po wywolaniu tej funkcji, uzytkownik bedzie mogl wprowadzic dane nowego kontaktu,
 * ktore zostana zapisane w systemie.
 */
void dodajKontakt()
{
	odczytZPliku();
	
	char im[MAX_DLUGOSC], nazw[MAX_DLUGOSC], ul[MAX_DLUGOSC], dom[MAX_DLUGOSC], mieszk[MAX_DLUGOSC], poczt[MAX_DLUGOSC],
		miast[MAX_DLUGOSC], tel[MAX_DLUGOSC_TELEFON], zaptel[MAX_DLUGOSC_TELEFON];
	int wi;
	printf("\nWiek: "); scanf("%i", &wi);
	printf("\nImie: "); scanf("%s", im);
	printf("\nNazwisko: "); scanf("%s", nazw);
	printf("\nUlica: "); scanf("%s", ul);
	printf("\nNr domu: "); scanf("%s", dom);
	printf("\nNr Mieszkania: "); scanf("%s", mieszk);
	printf("\nNr Poczty: "); scanf("%s", poczt);
	printf("\nMiasto: "); scanf("%s", miast);

	char pomocniczaTelefon[50];
	char pomocniczaZapasowyTelefon[50];
	do
	{
		printf("\nNr telefonu: "); scanf("%s", pomocniczaTelefon);
		printf("\nZapasowy nr telefonu: "); scanf("%s", pomocniczaZapasowyTelefon);

	} while (strlen(pomocniczaTelefon) >= 12 || strlen(pomocniczaZapasowyTelefon) >= 12);

	strncpy(tel, pomocniczaTelefon, MAX_DLUGOSC_TELEFON);
	strncpy(zaptel, pomocniczaZapasowyTelefon, MAX_DLUGOSC_TELEFON);

	nowy_kontakt(wi, im, nazw, ul, dom, mieszk, poczt, miast, tel, zaptel);
}

/**
 * @brief Odczytuje dane z pliku.
 *
 * Funkcja odczytZPliku() sluzy do odczytywania danych kontaktow z pliku.
 * Po wywolaniu tej funkcji, system odczyta dane z pliku i umozliwi dostep
 * do nich w celu wyswietlenia, edycji lub innych operacji.
 */
void odczytZPliku()
{
	FILE* plik;
	plik = fopen("Kontakty.txt", "r");
	if (!plik)
	{
		printf("\nBlad otwarcia pliku!");
		return;
	}
	
			
	//odczytujemy najwyzsze id z pliku
	int id = 0;
	char linia[100];
	while (fgets(linia, sizeof(linia), plik) != NULL) {
		if (sscanf(linia, "ID: %d", &id) == 1)
			id++;
	}
	ID = id;

	int c = 0;
	while (c <= ID-1)
	{
		c += 4;
		Kontakty* nowaTablica = (Kontakty*)realloc(kontakty, sizeof(Kontakty) * (c + 1));
		if (nowaTablica == NULL) {
			puts("Blad reallokacji pamieci linia 229");
			return;
		}
		else
		kontakty = nowaTablica;	
	}

	rewind(plik);
	int iplikPobierz = 0;
	while ((fscanf(plik, "ID: %d", &kontakty[iplikPobierz].id) == 1)) {

		fscanf(plik, "ID: %d\n", &kontakty[iplikPobierz].id);
		fscanf(plik, " %d, %s %s\n", &kontakty[iplikPobierz].wiek, &kontakty[iplikPobierz].imie, &kontakty[iplikPobierz].nazwisko);
		fscanf(plik, " %s %s %s\n", &kontakty[iplikPobierz].ulica, &kontakty[iplikPobierz].nr_domu, &kontakty[iplikPobierz].nr_mieszkania);
		fscanf(plik, " %s %s\n", &kontakty[iplikPobierz].kod_pocztowy, &kontakty[iplikPobierz].miasto);
		fscanf(plik, " %s %s\n\n", &kontakty[iplikPobierz].nr_telefonu, &kontakty[iplikPobierz].zapasowy_nr_telefonu);

		iplikPobierz++;
	}
	int ipomDoWskaznikow = 0;

	//ustawianie wskaznikow 
	while (ipomDoWskaznikow < ID - 1)
	{
		kontakty[ipomDoWskaznikow].next = &kontakty[ipomDoWskaznikow + 1];
		ipomDoWskaznikow++;
	}

	/*puts("\n\n\n\n");
	for (int i = 0; i < ID ; i++)
		printf("\n%p", kontakty[i].next)*/;
	fclose(plik);
}

/**
 * @brief Edytuje istniejacy kontakt.
 *
 * Funkcja edytujKontakt() umozliwia uzytkownikowi edycje danych istniejacego kontaktu.
 * Po wywolaniu tej funkcji, uzytkownik bedzie mogl wprowadzic nowe dane dla wybranego kontaktu,
 * ktore zostana zaktualizowane w systemie.
 */
void edytujKontakt()
{
	odczytZPliku();
	if (ID == 0)
	{
		puts("\n\nNie ma jeszcze zadnych kontaktow!");
		return;
	}

	int  zmien;
	puts("Podaj ID numeru do edytownaia: "); scanf("%d", &zmien);

	if (zmien < 0 || zmien >ID - 1)
	{
		puts("Podaj prawidlowa liczbe indeksu!");
		return;
	}
	char Nim[MAX_DLUGOSC], Nnazw[MAX_DLUGOSC], Nul[MAX_DLUGOSC], Ndom[MAX_DLUGOSC], Nmieszk[MAX_DLUGOSC], Npoczt[MAX_DLUGOSC],
		Nmiast[MAX_DLUGOSC];

	puts("");
	int Nwi;
	printf("\nNowy Wiek: "); scanf("%i", &Nwi);
	kontakty[zmien].wiek = Nwi;

	printf("\nNowe Imie: "); scanf("%s", Nim);
	strncpy(kontakty[zmien].imie, Nim, MAX_DLUGOSC);

	printf("\nNowe Nazwisko: "); scanf("%s", Nnazw);
	strncpy(kontakty[zmien].nazwisko, Nnazw, MAX_DLUGOSC);

	printf("\nNowa Ulica: "); scanf("%s", Nul);
	strncpy(kontakty[zmien].ulica, Nul, MAX_DLUGOSC);

	printf("\nNowy Nr domu: "); scanf("%s", Ndom);
	strncpy(kontakty[zmien].nr_domu, Ndom, MAX_DLUGOSC);

	printf("\nNowy Nr Mieszkania "); scanf("%s", Nmieszk);
	strncpy(kontakty[zmien].nr_mieszkania, Nmieszk, MAX_DLUGOSC);

	printf("\nNowy Nr Poczty "); scanf("%s", Npoczt);
	strncpy(kontakty[zmien].kod_pocztowy, Npoczt, MAX_DLUGOSC);

	printf("\nNowe Miasto "); scanf("%s", Nmiast);
	strncpy(kontakty[zmien].miasto, Nmiast, MAX_DLUGOSC);

	//-;;- jest to potrzebne bo C.
	char pomocniczaTelefon[50];
	char pomocniczaZapasowyTelefon[50];
	do
	{
		printf("\nNowy Nr telefonu: "); scanf("%s", pomocniczaTelefon);
		printf("\nNowy Zapasowy nr telefonu: "); scanf("%s", pomocniczaZapasowyTelefon);
	} while (strlen(pomocniczaTelefon) >12 || strlen(pomocniczaZapasowyTelefon) >12);

	strncpy(kontakty[zmien].nr_telefonu, pomocniczaTelefon, MAX_DLUGOSC_TELEFON);
	strncpy(kontakty[zmien].zapasowy_nr_telefonu, pomocniczaZapasowyTelefon, MAX_DLUGOSC_TELEFON);

	printf("\nEdytowano pomyslnie\n");
	save_to_file_all();
}

/**
 * @brief Wyswietla dane kontaktu.
 *
 * Funkcja wyswietlKontakt() sluzy do wyswietlania danych konkretnego kontaktu.
 * Po wywolaniu tej funkcji, system wyswietli informacje o danym kontakcie,
 * takie jak imie, nazwisko, numer telefonu itp.
 */
void wyswietlKontakt()
{
	odczytZPliku();
	if (ID == 0)
	{
		puts("\n\nNie ma jeszcze zadnych kontaktow!");
		return;
	}

	int idDoWyswietlenia;
	printf("\nPodaj ID numeru ktorego dane chcesz odczytac: ");
	scanf("%i", &idDoWyswietlenia);

	if (idDoWyswietlenia < 0 || idDoWyswietlenia >ID - 1)
	{
		puts("Podaj prawidlowa liczbe indeksu!");
		return;
	}

	puts("");
	printf("ID: %i \n %i, %s %s \n %s %s %s \n %s %s \n %s %s \n\n", kontakty[idDoWyswietlenia].id, kontakty[idDoWyswietlenia].wiek, kontakty[idDoWyswietlenia].imie
		, kontakty[idDoWyswietlenia].nazwisko, kontakty[idDoWyswietlenia].ulica, kontakty[idDoWyswietlenia].nr_domu, kontakty[idDoWyswietlenia].nr_mieszkania, kontakty[idDoWyswietlenia].kod_pocztowy
		, kontakty[idDoWyswietlenia].miasto, kontakty[idDoWyswietlenia].nr_telefonu, kontakty[idDoWyswietlenia].zapasowy_nr_telefonu);
}

/**
 * @brief Wyswietla dane kontaktu na podstawie konkretnego identyfikatora.
 *
 * Funkcja wyswietlOd_konkretnegoID() umozliwia wyswietlenie danych kontaktu
 * na podstawie podanego identyfikatora. Po wywolaniu tej funkcji, system
 * wyszuka kontakt o podanym identyfikatorze i wyswietli jego informacje 
 o wszystkich kontaktach zaczynajac od podanego.
 */
void wyswietlOd_konkretnegoID()
{
	odczytZPliku();
	if (ID == 0)
	{
		puts("\n\nNie ma jeszcze zadnych kontaktow!");
		return;
	}

	int odId;
	printf("\nPodaj od jakiego ID chcesz wyswietlic kontakty: ");
	scanf("%i", &odId);

	if (odId < 0 || odId >ID - 1)
	{
		puts("Podaj prawidlowa liczbe indeksu!");
		return;
	}

	for (odId; odId < ID; odId++)
	{
		printf("\nID: %i \n %i, %s %s \n %s %s %s \n %s %s \n %s %s \n\n", kontakty[odId].id, kontakty[odId].wiek, kontakty[odId].imie
			, kontakty[odId].nazwisko, kontakty[odId].ulica, kontakty[odId].nr_domu, kontakty[odId].nr_mieszkania, kontakty[odId].kod_pocztowy
			, kontakty[odId].miasto, kontakty[odId].nr_telefonu, kontakty[odId].zapasowy_nr_telefonu);
		puts("");
	}
}

/**
 * @brief Funckja do sortowania
 *
 * Funkcja ktora wowluje funkcje mainSort
 * w instrukcji switch, z opowiednimi parametrami
 *
 */
void sort()
{
	int wybor, rosnaco;

	printf("\nPodaj wedlug ktorego pola chcesz sortowac: \n");
	printf("0: Wiek\n1: Imie \n2: Nazwisko\n3: Ulica \n4: Nr_domu\n5: Nr_mieszkania\n6: Kod_pocztowy \n7: Miasto\n8: Nr. telefonu\n9: Zapasowy Nr. telefonu\nWybor: ");
	scanf("%d", &wybor);

	switch (wybor)
	{
	case 0:
	{
		puts("\n 1 = rosnaco, 0 = malejaco ");
		scanf("%d", &rosnaco);
		mainSort(rosnaco, "wiek");
		break;
	}
	case 1:
	{
		puts("\n 1 = rosnaco, 0 = malejaco ");
		scanf("%d", &rosnaco);
		mainSort(rosnaco, "imie");
		break;
	}
	case 2:
	{
		puts("\n 1 = rosnaco, 0 = malejaco ");
		scanf("%d", &rosnaco);
		mainSort(rosnaco, "nazwisko");
		break;
	}
	case 3:
	{
		puts("\n 1 = rosnaco, 0 = malejaco ");
		scanf("%d", &rosnaco);
		mainSort(rosnaco, "ulica");
		break;
	}
	case 4:
	{
		puts("\n 1 = rosnaco, 0 = malejaco ");
		scanf("%d", &rosnaco);
		mainSort(rosnaco, "nr_domu");
		break;
	}
	case 5:
	{
		puts("\n 1 = rosnaco, 0 = malejaco ");
		scanf("%d", &rosnaco);
		mainSort(rosnaco, "nr_mieszkania");
		break;
	}
	case 6:
	{
		puts("\n 1 = rosnaco, 0 = malejaco ");
		scanf("%d", &rosnaco);
		mainSort(rosnaco, "kod_pocztowy");
		break;
	}
	case 7:
	{
		puts("\n 1 = rosnaco, 0 = malejaco ");
		scanf("%d", &rosnaco);
		mainSort(rosnaco, "miasto");
		break;
	}
	case 8:
	{
		puts("\n 1 = rosnaco, 0 = malejaco ");
		scanf("%d", &rosnaco);
		mainSort(rosnaco, "nr_telefonu");
		break;
	}
	case 9:
	{
		puts("\n 1 = rosnaco, 0 = malejaco ");
		scanf("%d", &rosnaco);
		mainSort(rosnaco, "zapasowy_nr_telefonu");
		break;
	}
	default:
		puts("\nWybrano nieprawidlowa opcje");
		break;
	}
}


/**
 * @brief Zamienia dwa obiekty typu Kontakty miejscami.
 *
 * Funkcja swapK() sluzy do zamiany miejscami dwoch obiektow typu Kontakty.
 * Przyjmuje wskazniki A i B do dwoch obiektow, a nastepnie zamienia je miejscami.
 * Po wykonaniu funkcji, obiekt wskazywany przez A bedzie znajdowac sie pod adresem,
 * ktory wczesniej wskazywal B, a obiekt wskazywany przez B bedzie znajdowac sie
 * pod adresem, ktory wczesniej wskazywal A.
 *
 * @param A Wskaznik do pierwszego obiektu typu Kontakty.
 * @param B Wskaznik do drugiego obiektu typu Kontakty.
 */
void swapK(Kontakty* A, Kontakty* B)
{
	Kontakty tmpkontakt = *A;
	*A = *B;
	*B = tmpkontakt;

	int tmpID = A->id;
	A->id = B->id;
	B->id = tmpID;
	save_to_file_all();
}

/**
* @brief Funkcje do porownywania ze soba pol w strukturze Kontakty
*
* Funkcje zwracaja short, a nie bool poniewaz musza obslugiwac 3 rozne przypadki
*
*/
/**
 * @defgroup Porownania Porownania kontaktow
 * @{
 */

 /**
  * @brief Porownuje kontakty na podstawie wieku.
  *
  * @param A       Wskaznik do pierwszego obiektu typu Kontakty.
  * @param B       Wskaznik do drugiego obiektu typu Kontakty.
  * @param rosnaco Flaga okreslajaca porzadek rosnacy (1) lub malejacy (0).
  *
  * @return Wartosc zwracana zalezna od wyniku porownania.
  */
short porownanieWiek(Kontakty* A, Kontakty* B, int rosnaco)
{
	if (A->wiek > B->wiek && (rosnaco == 1))
		return 1;
	else if (A->wiek < B->wiek && (rosnaco == 0))
		return 0;

	return -1;
}
/**
 * @brief Porownuje kontakty na podstawie imienia.
 *
 * @param A       Wskaznik do pierwszego obiektu typu Kontakty.
 * @param B       Wskaznik do drugiego obiektu typu Kontakty.
 * @param rosnaco Flaga okreslajaca porzadek rosnacy (1) lub malejacy (0).
 *
 * @return Wartosc zwracana zalezna od wyniku porownania.
 */
short porownanieImie(Kontakty* A, Kontakty* B, int rosnaco)
{
	if (strcmp(A->imie, B->imie) > 0 && (rosnaco == 1))
		return 1;
	else if (strcmp(A->imie, B->imie) < 0 && (rosnaco == 0))
		return 0;

	return -1;
}
/**
 * @brief Porownuje kontakty na podstawie nazwiska.
 *
 * @param A       Wskaznik do pierwszego obiektu typu Kontakty.
 * @param B       Wskaznik do drugiego obiektu typu Kontakty.
 * @param rosnaco Flaga okreslajaca porzadek rosnacy (1) lub malejacy (0).
 *
 * @return Wartosc zwracana zalezna od wyniku porownania.
 */
short porownanieNazwisko(Kontakty* A, Kontakty* B, int rosnaco)
{
	if (strcmp(A->nazwisko, B->nazwisko) > 0 && (rosnaco == 1))
		return 1;
	else if (strcmp(A->nazwisko, B->nazwisko) < 0 && (rosnaco == 0))
		return 0;
}
/**
 * @brief Porownuje kontakty na podstawie ulicy.
 *
 * @param A       Wskaznik do pierwszego obiektu typu Kontakty.
 * @param B       Wskaznik do drugiego obiektu typu Kontakty.
 * @param rosnaco Flaga okreslajaca porzadek rosnacy (1) lub malejacy (0).
 *
 * @return Wartosc zwracana zalezna od wyniku porownania.
 */
short porownanieUlica(Kontakty* A, Kontakty* B, int rosnaco)
{
	if (strcmp(A->ulica, B->ulica) > 0 && (rosnaco == 1))
		return 1;
	else if (strcmp(A->ulica, B->ulica) < 0 && (rosnaco == 0))
		return 0;

	return -1;
}
/**
 * @brief Porownuje kontakty na podstawie numeru domu.
 *
 * @param A       Wskaznik do pierwszego obiektu typu Kontakty.
 * @param B       Wskaznik do drugiego obiektu typu Kontakty.
 * @param rosnaco Flaga okreslajaca porzadek rosnacy (1) lub malejacy (0).
 *
 * @return Wartosc zwracana zalezna od wyniku porownania.
 */
short porownanieNr_domu(Kontakty* A, Kontakty* B, int rosnaco)
{
	if (strcmp(A->nr_domu, B->nr_domu) > 0 && (rosnaco == 1))
		return 1;
	else if (strcmp(A->nr_domu, B->nr_domu) < 0 && (rosnaco == 0))
		return 0;

	return -1;
}

/**
 * @brief Porownuje kontakty na podstawie numeru mieszkania.
 *
 * @param A       Wskaznik do pierwszego obiektu typu Kontakty.
 * @param B       Wskaznik do drugiego obiektu typu Kontakty.
 * @param rosnaco Flaga okreslajaca porzadek rosnacy (1) lub malejacy (0).
 *
 * @return Wartosc zwracana zalezna od wyniku porownania.
 */
short porownanieNr_mieszkania(Kontakty* A, Kontakty* B, int rosnaco)
{
	if (strcmp(A->nr_mieszkania, B->nr_mieszkania) > 0 && (rosnaco == 1))
		return 1;
	else if (strcmp(A->nr_mieszkania, B->nr_mieszkania) < 0 && (rosnaco == 0))
		return 0;

	return -1;
}
/**
 * @brief Porownuje kontakty na podstawie kodu pocztowego.
 *
 * @param A       Wskaznik do pierwszego obiektu typu Kontakty.
 * @param B       Wskaznik do drugiego obiektu typu Kontakty.
 * @param rosnaco Flaga okreslajaca porzadek rosnacy (1) lub malejacy (0).
 *
 * @return Wartosc zwracana zalezna od wyniku porownania.
 */
short porownanieKod_pocztowy(Kontakty* A, Kontakty* B, int rosnaco)
{
	if (strcmp(A->kod_pocztowy, B->kod_pocztowy) > 0 && (rosnaco == 1))
		return 1;
	else if (strcmp(A->kod_pocztowy, B->kod_pocztowy) < 0 && (rosnaco == 0))
		return 0;

	return -1;
}
/**
 * @brief Porownuje kontakty na podstawie miasta.
 *
 * @param A       Wskaznik do pierwszego obiektu typu Kontakty.
 * @param B       Wskaznik do drugiego obiektu typu Kontakty.
 * @param rosnaco Flaga okreslajaca porzadek rosnacy (1) lub malejacy (0).
 *
 * @return Wartosc zwracana zalezna od wyniku porownania.
 */
short porownanieMiasto(Kontakty* A, Kontakty* B, int rosnaco)
{
	if (strcmp(A->miasto, B->miasto) > 0 && (rosnaco == 1))
		return 1;
	else if (strcmp(A->miasto, B->miasto) < 0 && (rosnaco == 0))
		return 0;

	return -1;
}
/**
 * @brief Porownuje kontakty na podstawie numeru telefonu.
 *
 * @param A       Wskaznik do pierwszego obiektu typu Kontakty.
 * @param B       Wskaznik do drugiego obiektu typu Kontakty.
 * @param rosnaco Flaga okreslajaca porzadek rosnacy (1) lub malejacy (0).
 *
 * @return Wartosc zwracana zalezna od wyniku porownania.
 */
short porownanieNr_telefonu(Kontakty* A, Kontakty* B, int rosnaco)
{
	if (strcmp(A->nr_telefonu, B->nr_telefonu) > 0 && (rosnaco == 1))
		return 1;
	else if (strcmp(A->nr_telefonu, B->nr_telefonu) < 0 && (rosnaco == 0))
		return 0;

	return -1;
}
/**
 * @brief Porownuje kontakty na podstawie numeru telefonu zapasowego.
 *
 * @param A       Wskaznik do pierwszego obiektu typu Kontakty.
 * @param B       Wskaznik do drugiego obiektu typu Kontakty.
 * @param rosnaco Flaga okreslajaca porzadek rosnacy (1) lub malejacy (0).
 *
 * @return Wartosc zwracana zalezna od wyniku porownania.
 */
short porownanieZapasowy_nr_telefonu(Kontakty* A, Kontakty* B, int rosnaco)
{
	if (strcmp(A->zapasowy_nr_telefonu, B->zapasowy_nr_telefonu) > 0 && (rosnaco == 1))
		return 1;
	else if (strcmp(A->zapasowy_nr_telefonu, B->zapasowy_nr_telefonu) < 0 && (rosnaco == 0))
		return 0;

	return -1;
}

/**
 * @}
 */

/**
 * \brief Sortuje tablice obiektow typu Kontakty przy uzyciu okreslonej funkcji porownujacej.
 *
 * Ta funkcja sortuje tablice obiektow typu Kontakty w porzadku rosnacym lub malejacym,
 * w zaleznosci od dostarczonej funkcji porownujacej.
 *
 * \param porownanie Wskaznik na funkcje porownujaca, ktora okresla kolejnosc obiektow.
 *                   Funkcja porownujaca powinna miec sygnature:
 *                   short porownanie(Kontakty* obj1, Kontakty* obj2, int rosnaco)
 *                   gdzie `obj1` i `obj2` sa wskaznikami na obiekty typu Kontakty, a `rosnaco`
 *                   okresla kolejnosc sortowania (0 dla malejacego, wartosc rozna od zera dla rosnacego).
 *
 * \param rosnaco Okresla kolejnosc sortowania. Jesli `rosnaco` nie jest zerem, tablica zostanie posortowana
 *                w porzadku rosnacym; w przeciwnym razie zostanie posortowana w porzadku malejacym.
 */
void bobmbelekSort(short(*porownanie)(Kontakty*, Kontakty*, int), int rosnaco)
{
	odczytZPliku();
	bool swapped;
	int i, j;
	for (j = 0; j < ID - 1; j++)
	{
		swapped = false;
		for (i = 0; i < ID - 1 - j; i++)
		{
			if (porownanie(&kontakty[i], &kontakty[i + 1], rosnaco) == 1 || porownanie(&kontakty[i], &kontakty[i + 1], rosnaco) == 0)
			{
				swapped = true;
				swapK(&kontakty[i], &kontakty[i + 1]);
			}
		}
		if (!swapped)
			break;
	}
}

/**
 * @brief Funckja do sortowania
 *
 * Funkcja ktora wywoluje w switch() sortowanie po polu wybranym przez
 * uzytkownika
 *
 */
void mainSort(int rosnaco, char* pole)
{
	short ipole;
	//Nie moza zrobic switcha na char * dlatego trzeba tak zrobic
	if (strcmp(pole, "wiek") == 0)
		ipole = 0;
	else if (strcmp(pole, "imie") == 0)
		ipole = 1;
	else if (strcmp(pole, "nazwisko") == 0)
		ipole = 2;
	else if (strcmp(pole, "ulica") == 0)
		ipole = 3;
	else if (strcmp(pole, "nr_domu") == 0)
		ipole = 4;
	else if (strcmp(pole, "nr_mieszkania") == 0)
		ipole = 5;
	else if (strcmp(pole, "kod_pocztowy") == 0)
		ipole = 6;
	else if (strcmp(pole, "miasto") == 0)
		ipole = 7;
	else if (strcmp(pole, "nr_telefonu") == 0)
		ipole = 8;
	else if (strcmp(pole, "zapasowy_nr_telefonu") == 0)
		ipole = 9;

	switch (ipole)
	{
	case 0:
		bobmbelekSort(porownanieWiek, rosnaco); break;
	case 1:
		bobmbelekSort(porownanieImie, rosnaco); break;
	case 2:
		bobmbelekSort(porownanieNazwisko, rosnaco);	break;
	case 3:
		bobmbelekSort(porownanieUlica, rosnaco); break;
	case 4:
		bobmbelekSort(porownanieNr_domu, rosnaco); break;
	case 5:
		bobmbelekSort(porownanieNr_mieszkania, rosnaco); break;
	case 6:
		bobmbelekSort(porownanieKod_pocztowy, rosnaco); break;
	case 7:
		bobmbelekSort(porownanieMiasto, rosnaco); break;
	case 8:
		bobmbelekSort(porownanieNr_telefonu, rosnaco); break;
	case 9:
		bobmbelekSort(porownanieZapasowy_nr_telefonu, rosnaco); break;
	default:
		puts("\nWybrano nieprawidlowa opcje");
		break;
	}
}

