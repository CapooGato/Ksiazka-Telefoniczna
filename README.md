# Ksiazka-Telefoniczna

Phone book in console :), the data about person is saved in text file.
Dynamically allocated memory for another person
What's in txt?:

ID: 46 
 20, Seweryn Kawecki 
 Fajna 37C 0 
 26-065 Kielce 
 999888111 111000222 

 ID: 47 
 19, Magda Gesler 
 Fajna 12 0 
 26-065 Pozan 
 999111888 444444444 
 
Struct:
 typedef struct {
    int id; /**< Identyfikator kontaktu. */
    int wiek; /**< Wiek kontaktu. */
    char imie[MAX_DLUGOSC]; /**< Imie kontaktu. */
    char nazwisko[MAX_DLUGOSC]; /**< Nazwisko kontaktu. */
    char ulica[MAX_DLUGOSC]; /**< Ulica kontaktu. */
    char nr_domu[MAX_DLUGOSC]; /**< Numer domu kontaktu. */
    char nr_mieszkania[MAX_DLUGOSC]; /**< Numer mieszkania kontaktu. */
    char kod_pocztowy[MAX_DLUGOSC]; /**< Kod pocztowy kontaktu. */
    char miasto[MAX_DLUGOSC]; /**< Miasto kontaktu. */
    char nr_telefonu[MAX_DLUGOSC_TELEFON]; /**< Numer telefonu kontaktu. */
    char zapasowy_nr_telefonu[MAX_DLUGOSC_TELEFON]; /**< Zapasowy numer telefonu kontaktu. */

    struct kontakty* next; /**< Wskaznik na kolejny kontakt. */
} Kontakty;

