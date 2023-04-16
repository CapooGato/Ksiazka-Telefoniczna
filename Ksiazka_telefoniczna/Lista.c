#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>

int ID = 0;

void remove_contact()
{
	//ID_check();


	printf("\n\nID w remove contacts: %d", ID);
	if (ID < 0)
	{
		puts("\n\nNie ma jeszcze zadnych kontaktow!");
		return;
	}

	int iremove = 0;
	printf("\nPodaj ID osoby ktora chcesz usunac: ");
	scanf("%i", &iremove);


	/*Fix bledu gdzie, remove 3 moglo usuwac index o wartosci 3, jak i potem 2*/
	if (iremove < 0 || iremove >ID)
	{
		puts("Podaj prawidlowa liczbe indeksu!");
		return;
	}


	printf("\n\nID przed usunieciem: %i", ID);

	for (iremove; iremove < ID; iremove++)
	{

		kontakty[iremove] = kontakty[iremove + 1];
		kontakty[iremove].id--;
	}

	ID--;

	printf("\n\nID Po usunieciu: %i", ID);
	save_to_file_all();
}


//Wpisujemy nowe osoby 
void save_to_file_all()
{
	//ID_check();

	int numer = 0;
	FILE* plik;
	plik = fopen("Kontakty.txt", "w");

	if (!plik)
	{
		printf("\nBlad otwarcia pliku!");
		return;
	}

	//wpisujemy wszystkie osoby do pliku
	for (numer; numer < ID; numer++)
	{
		fprintf(plik, "ID: %i \n %i, %s %s \n %s %s %s \n %s %s \n %s %s \n\n", kontakty[numer].id, kontakty[numer].wiek, kontakty[numer].imie
			, kontakty[numer].nazwisko, kontakty[numer].ulica, kontakty[numer].nr_domu, kontakty[numer].nr_mieszkania, kontakty[numer].kod_pocztowy
			, kontakty[numer].miasto, kontakty[numer].nr_telefonu, kontakty[numer].zapasowy_nr_telefonu);
	}

	fclose(plik);
}

//Dodajemy nowy kontakt
void nowy_kontakt(int wiekk, char* imiee, char* nazwiskoo, char* ulicaa, char* nr_domuu, char* nr_mieszkaniaa, char* kod_pocztowyy,
	char* miastoo, char* nr_telefonuu, char* zapasowy_nr_telefonuu)
{

	//ID_check();
	FILE* plik;
	plik = fopen("Kontakty.txt", "a+");
	kontakty[ID].id = ID;
	kontakty[ID].wiek = wiekk;
	printf("\n\n\n DOpisz do pliku ID = %i", ID);
	// printf("\n\n\n DOpisz do pliku id = %i", id);
	strncpy(kontakty[ID].imie, imiee, MAX_DLUGOSC);

	strncpy(kontakty[ID].nazwisko, nazwiskoo, MAX_DLUGOSC);

	strncpy(kontakty[ID].ulica, ulicaa, MAX_DLUGOSC);

	strncpy(kontakty[ID].nr_domu, nr_domuu, MAX_DLUGOSC);

	strncpy(kontakty[ID].nr_mieszkania, nr_mieszkaniaa, MAX_DLUGOSC);

	strncpy(kontakty[ID].kod_pocztowy, kod_pocztowyy, MAX_DLUGOSC);

	strncpy(kontakty[ID].miasto, miastoo, MAX_DLUGOSC);

	strncpy(kontakty[ID].nr_telefonu, nr_telefonuu, MAX_DLUGOSC);

	strncpy(kontakty[ID].zapasowy_nr_telefonu, zapasowy_nr_telefonuu, MAX_DLUGOSC);

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

	ID++;
	fclose(plik);
	puts("\nPomyslnie dodano do pliku.\n");

	save_to_file_all();
}

//Menu z wyobrem co chcemy zrobic
void menu()
{
	int wybor;

	do {
		printf("\n 0 = zakoncz,\n 1 = dodaj nowa osobe do ksiazki telefonicznej,\n 2 = usun kontakt po ID,\n 3 = Edytuj kontakt\n"
			" 4 = wyswietl dane kontaktu po ID\n 5 = wyswietl od konkretnego ID,\nWybor: ");
		scanf("%i", &wybor);

		switch (wybor)
		{
		case 1:
		{

			if (ID >= MAX_KONTAKTOW) {
				puts("\n\nPrzekorczono dozwolona ilosc kontaktow!");
				break;
			}

			char im[MAX_DLUGOSC], nazw[MAX_DLUGOSC], ul[MAX_DLUGOSC], dom[MAX_DLUGOSC], mieszk[MAX_DLUGOSC], poczt[MAX_DLUGOSC],
				miast[MAX_DLUGOSC], tel[MAX_DLUGOSC], zaptel[MAX_DLUGOSC];
			int wi;
			printf("\nWiek: "); scanf("%i", &wi);
			printf("\nImie: "); scanf("%s", im);
			printf("\nNazwisko: "); scanf("%s", nazw);
			printf("\nUlica: "); scanf("%s", ul);
			printf("\nNr domu: "); scanf("%s", dom);
			printf("\nNr Mieszkania: "); scanf("%s", mieszk);
			printf("\nNr Poczty: "); scanf("%s", poczt);
			printf("\nMiasto: "); scanf("%s", miast);
			printf("\nNr telefonu: "); scanf("%s", tel);
			printf("\nZapasowy nr telefonu: "); scanf("%s", zaptel);
			nowy_kontakt(wi, im, nazw, ul, dom, mieszk, poczt, miast, tel, zaptel);
			break;
		}
		case 2:
		{
			remove_contact();
			break;
		}
		case 3:
		{
			if (ID == 0)
			{
				puts("\n\nNie ma jeszcze zadnych kontaktow!");
				break;
			}

			int  zmien;
			puts("Podaj ID numeru do edytownaia: "); scanf("%i", &zmien);

			if (zmien < 0 || zmien >ID - 1)
			{
				puts("Podaj prawidlowa liczbe indeksu!");
				break;
			}
			char Nim[MAX_DLUGOSC], Nnazw[MAX_DLUGOSC], Nul[MAX_DLUGOSC], Ndom[MAX_DLUGOSC], Nmieszk[MAX_DLUGOSC], Npoczt[MAX_DLUGOSC],
				Nmiast[MAX_DLUGOSC], Ntel[MAX_DLUGOSC], Nzaptel[MAX_DLUGOSC];

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

			printf("\nNowy Nr telefonu "); scanf("%s", Ntel);
			strncpy(kontakty[zmien].nr_telefonu, Ntel, MAX_DLUGOSC);

			printf("\nNowy Zapasowy nr telefonu "); scanf("%s", Nzaptel);
			strncpy(kontakty[zmien].zapasowy_nr_telefonu, Nzaptel, MAX_DLUGOSC);

			printf("\nEdytowano pomyslnie\n");
			save_to_file_all();
			break;
		}
		case 4:
		{
			if (ID == 0)
			{
				puts("\n\nNie ma jeszcze zadnych kontaktow!");
				break;
			}

			int idDoWyswietlenia;
			printf("\nPodaj ID numeru ktorego dane chcesz odczytac: ");
			scanf("%i", &idDoWyswietlenia);

			if (idDoWyswietlenia < 0 || idDoWyswietlenia >ID - 1)
			{
				puts("Podaj prawidlowa liczbe indeksu!");
				break;
			}

			puts("");
			printf("ID: %i \n %i, %s %s \n %s %s %s \n %s %s \n %s %s \n\n", kontakty[idDoWyswietlenia].id, kontakty[idDoWyswietlenia].wiek, kontakty[idDoWyswietlenia].imie
				, kontakty[idDoWyswietlenia].nazwisko, kontakty[idDoWyswietlenia].ulica, kontakty[idDoWyswietlenia].nr_domu, kontakty[idDoWyswietlenia].nr_mieszkania, kontakty[idDoWyswietlenia].kod_pocztowy
				, kontakty[idDoWyswietlenia].miasto, kontakty[idDoWyswietlenia].nr_telefonu, kontakty[idDoWyswietlenia].zapasowy_nr_telefonu);
			break;
		}
		case 5:
		{
			if (ID == 0)
			{
				puts("\n\nNie ma jeszcze zadnych kontaktow!");
				break;
			}

			int odId;
			printf("\nPodaj od jakiego ID chcesz wyswietlic kontakty: ");
			scanf("%i", &odId);


			if (odId < 0 || odId >ID - 1)
			{
				puts("Podaj prawidlowa liczbe indeksu!");
				break;
			}

			for (odId; odId < ID; odId++)
			{
				printf("\nID: %i \n %i, %s %s \n %s %s %s \n %s %s \n %s %s \n\n", kontakty[odId].id, kontakty[odId].wiek, kontakty[odId].imie
					, kontakty[odId].nazwisko, kontakty[odId].ulica, kontakty[odId].nr_domu, kontakty[odId].nr_mieszkania, kontakty[odId].kod_pocztowy
					, kontakty[odId].miasto, kontakty[odId].nr_telefonu, kontakty[odId].zapasowy_nr_telefonu);
				puts("");
			}
			break;
		}
		}


	} while (wybor != 0);

}

