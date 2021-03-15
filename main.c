/*
Kacper Kolodynski
Temat:Przetwarzanie obrazu
Data: 1.12.2018 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										    *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			    *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		    *
 * \param[out] wymx szerokosc obrazka						    *
 * \param[out] wymy wysokosc obrazka						    *
 * \param[out] szarosci liczba odcieni szarosci					    *
 * \return liczba wczytanych pikseli						    *
 ************************************************************************************/

int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",wymx,wymy,szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<*wymy;i++) {
    for (j=0;j<*wymx;j++) {
      if (fscanf(plik_we,"%d",&(obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return *wymx**wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */


/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}


//Negatyw
void negatyw(int tab[][MAX],int odcieni,int wymx, int wymy){
  for (int i=0;i<wymy;i++) {
    for (int j=0;j<wymx;j++){
      tab[i][j]=fabs(odcieni-tab[i][j]);
                           }
		            }
    }
	//Progrowanie
void progowanie(float prog,int odcieni,int tab[][MAX],int wymx, int wymy){
	int i,j;
	float prog2;
	prog2=prog/100*odcieni;
	int p = (int)prog2;
	printf("%d\n", p);
	for (i=0;i<wymy;i++)
	{
		for (j=0;j<wymx;j++)
		{
		if(tab[i][j]<=p) tab[i][j]=0;
		else tab[i][j]=odcieni;
	   	}
      	}
    }
	
//Konturowanie
	void konturowanie(int tab[][MAX],int wymx,int wymy){
		for (int i=0;i<wymy-1;i++){
			for(int j=0; j<wymx-1; j++){
			tab[i][j]=fabs(tab[i+1][j]-tab[i][j]) + fabs(tab[i][j+1]-tab[i][j]);
						  }
					 }

	     }		
//Rozmycie
	void rozmycie(int tab[][MAX],int rodzaj,int promien,int wymx, int wymy)	
	{
			if(promien ==1){ 
			for(int i=1;i<wymy-1;i++)
					{
				for(int j=1;j<wymx-1;j++)
						{
					if(rodzaj == 2)
						{
						tab[i][j]=(tab[i][j-1]+tab[i][j]+tab[i][j+1])/3;
						}
					else tab[i][j]=(tab[i-1][j]+tab[i][j] +tab[i+1][j])/3;

					        }
					 }
	                                 }
			else if(promien == 2) {
			for(int i=2;i<wymy-2;i++)
					{
				for(int j=2;j<wymx-2;j++)
						{
					if(rodzaj == 2)
						{
						tab[i][j]=(tab[i][j-2]+tab[i][j-1]+tab[i][j+1]+tab[i][j]+tab[i][j+2])/5;
						}
					else tab[i][j]=(tab[i-2][j]+tab[i-1][j]+tab[i][j]+tab[i+1][j] +tab[i+2][j])/5;
					        }
					   }
	}
				
						}
void zapisz(char nazwa2[100],int obraz_pgm[][MAX],int wymx,int wymy, int szarosci){
	FILE *plik;
	plik=fopen(nazwa2,"w");
	fprintf(plik,"P2\n");
	fprintf(plik,"%d %d\n",wymx, wymy); 
	fprintf(plik,"%d\n", szarosci);
	for(int i=0;i<wymy;i++){
	fprintf(plik,"\n");
	for(int j=0;j<wymx;j++){
	fprintf(plik,"%d ",obraz_pgm[i][j]);
	

				}	
				}
fclose(plik);					
}

int main() {
  int obraz[MAX][MAX] ;
  int wymx,wymy,odcieni;
  int odczytano = 0;
  FILE *plik;
  char nazwa[100];
  char nazwa2[100]; //zainicjowanie nazwy dla pliku wyjsciowego
  float prog; 
int opcja=-1;
 int rodzaj;
int promien;

printf("Podaj nazwe pliku:\n");
  scanf("%s", nazwa);
  plik=fopen(nazwa,"r");
  while(plik == NULL) 
{
	printf("Taki plik nie istnieje\n");
	printf("Podaj prawidlowa nazwe pliku\n");
	scanf("%s", nazwa);
	plik=fopen(nazwa,"r");
}
  if (plik != NULL && odczytano == 0) {       /* co spowoduje zakomentowanie tego warunku */
    odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
    fclose(plik);
  }


while(opcja!=0){
printf("Menu\n");
printf("1 - Wczytaj inny plik\n");
printf("2 - Zapisz\n");
printf("3 - Wyświetl\n");
printf("4 - Konturuj\n");
printf("5 - Negatyw\n");
printf("6 - Proguj\n");
printf("7 - Rozmyj\n");
printf("0 - Wyjście\n");
scanf("%d", &opcja);
	switch(opcja){
	case 1:
		printf("Podaj nazwe pliku:\n");
  		scanf("%s", nazwa);
  		plik=fopen(nazwa,"r");
		while(plik == NULL)
				{
	        printf("Taki plik nie istnieje\n");
	        printf("Podaj prawidlowa nazwe pliku\n");
	        scanf("%s", nazwa);
	        plik=fopen(nazwa,"r");
				}
  		if (plik != NULL) {       /* co spowoduje zakomentowanie tego warunku */
    			odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
    			fclose(plik);
  		}
		break;
	case 2: 
		printf("Podaj nazwe pliku ktory chcesz zapisac\n");
		scanf("%s", nazwa2);
		zapisz(nazwa2,obraz,wymx,wymy,odcieni); 
		printf("Zapisano %s\n", nazwa2);		
		break;
	case 3: 
		wyswietl(nazwa2);
		printf("Wyświetlono %s\n", nazwa2);
		break;
	case 4: 
		konturowanie(obraz,wymx,wymy);
		printf("Wykonano konturowanie\n");		
		break;
	case 5: 
		negatyw(obraz,odcieni,wymx,wymy);
		printf("Wykonano negatyw\n");
		break;
	case 6:
		printf("Podaj wartość progowania: \n");
		scanf("%f", &prog);
		progowanie(prog,odcieni,obraz,wymx,wymy);
		printf("Wykonano progowanie\n");
		break; 
		
	case 7:
		printf("Wybierz rodzaj rozmycia pionowe/poziome: \n");
		printf("1 - pionowe\n");
		printf("2 - poziome\n");
		scanf("%d", &rodzaj);
		printf("1 - promien = 1\n");
		printf("2 - promien = 2\n");
		scanf("%d", &promien);
		rozmycie(obraz,rodzaj,promien,wymx,wymy);

		break;
	case 0:
		break;	
	default: 
	printf("Nie rozpoznano opcji, prosze podac inna\n");
			}
}
  return 0;
}
/*
Testy programu:

Test 1:

Cel: Test ma na celu sprawdzenie czy program poprawnie wczytuje plik do pamieci poprzez zapisanie a nastepnie wyswietlenie pliku wczytanego.

Metoda testowania-dane wejsciowe: 
-Podanie nazwy pliku typu pgm istniejacego w katalogu, w ktorym znajduje sia kod progamu.W testach zostal uzyty plik "kubus.pgm".
-Wybranie opcji "Zapisz" aby zapisać plik w pamieci programu.
-Wybranie opcji "Wyswietl" w celu wyswietlenia pliku oraz potwierdzeniu,że plik zostal poprawnie wczytany a nastepnie zapisany. 

Dane wyjsciowe:
-Komunikat wymagajacy wpisania poprawnej nazwy pliku w celu wczytania.
-Po wpisaniu poprawnej nazwy pliku zostaje wyświetlone menu z opcjami przetwarzania obrazu.
-Po wybraniu opcji "Zapisz" wyswietlony zostaje komunikat wymagajacy wpisania nazwy pod która chcemy miec zapisany wczytany plik. Nastepnie zostaje wyswietlony komunikat informujacy o tym że plik zostal zapisany pod podaną wczesniej nazwa.
-Po wybraniu opcji "Wyswietl" zostaje wyswietlony przetworzony obraz, który wczytalismy oraz komunikat informujący o wyswietleniu pliku zapisanego.

Rezultat testu:Program poprawnie wczytal plik. Potwierdza to zapisanie oraz wyswietlenie pliku wczytanego. Test 1 przebiegl pomyslnie.

Test 2:
Cel: Test ma na celu sprawdzenie czy program wczyta nie istniejący plik.

Metoda testowania-dane wejsciowe:
-Wpisanie dowolnej nazwy pliku, która nie istnieje w naszym katalogu.

Dane wyjściowe:
-Wyswietlony zostaje komunikat informujacy nas,ze taki plik nie istnieje.
-Wyswietlony zostaje komunikat wymagający wpisania poprawnej nazwy pliku.

Rezultat testu:Program poprawnie odrzucil wymysloną przez nas nazwe pliku. Test 2 przebiegl pomyslnie.

Test 3:
Cel: Test ma na celu sprawdzenie czy program poprawnie wykona opcje "Konturowanie".
Metoda testowania-dane wejsciowe:
-Wczytujemy plik "kubus.pgm".
-Wybieramy opcje "Konturowanie".
-Wybieramy opcje "Zapisz" w celu zapisania oprazu konturowanego.Wpisujemy nazwe, pod która chcemy zapisać plik.
-Wybieramy opcje "Wyswietl" w celu sprawdzenia czy podana operacja sie udala.

Dane wyjsciowe:
-Wyswietlony zostaje komunikat informujacy o wykonaniu konturowania na wczytanym pliku.
-Wyswietlony zostaje komunikat informujacy o zapisaniu pliku pod nazwa ktora podalismy.
-Plik na ktorym wykonano opcje konturowania zostaje wyswietlony.Wyswietla sie rowniez komunikat informujacy o wyswietleniu pliku zapisanego.

Rezultat testu:Program poprawnie wykonal operacje konturowania. Potwierdza to wyswietlenie pliku konturowanego. Test 3 przebiegl pomyslnie.


Test 4:
Cel:Test ma na celu sprawdzenie czy program poprawnie wykona opcje "Negatyw".

Metoda testowania-dane wejsciowe:
-Wczytujemy plik "kubus.pgm".
-Wybieramy opcje "Negatyw".
-Wybieramy opcje "Zapisz"-Zapisujemy plik, na ktorym wykonano operacje "Negatyw".Wpisujemy nazwe, pod ktora chcemy miec zapisany przetworzony plik.
-Wybieramy opcje "Wyswietl" w celu sprawdzenia czy podana operacja sie udala.

Dane wyjsciowe:
-Wyswietlony zostaje komunikat informujacy o tym ze na wczytanym pliku wykonano operacje "Negatyw".
-Wyswietlony zostaje komunikat informujacy o zapisaniu pliku pod nazwa ktora podalismy.
-Plik na ktorym wykonano opcje "Negatyw" zostaje wyswietlony.Wyswietla sie rowniez komunikat informujacy o wyswietleniu pliku zapisanego.

Rezultat testu:Program poprawnie wykonał operacje "Negatyw".Test 4 przebiegl pomyslnie.

Test 5:
Cel:Test ma na celu sprawdzenie czy program poprawnie wykona opcję "Progowanie".

Metoda testowania-dane wejsciowe:
-Wczytujemy plik "kubus.pgm".
-Wybieramy opcje "Progowanie" a nastepnie wpisujemy wartosc progu dla ktorego obraz ma byc progowany, ktory jest czytany jako procent.
-Wybieramy opcje "Zapisz"-Zapisujemy plik, na ktorym wykonano operacje "Progowanie".Wpisujemy nazwe, pod ktora chcemy miec zapisany przetworzony plik.
-Wybieramy opcje "Wyswietl" w celu sprawdzenia czy podana operacja sie udala.

Dane wyjsciowe:
-Wyswietlony zostaje komunikat informujacy o tym ze na wczytanym pliku wykonano operacje progowania.
-Wyswietlony zostaje komunikat informujacy o zapisaniu pliku pod nazwa ktora podalismy.
-Plik na ktorym wykonano opcje progowania zostaje wyswietlony.Wyswietla sie rowniez komunikat informujacy o wyswietleniu pliku zapisanego.

Rezultat testu:Program poprawnie wykonal operacje progowania.Test 5 przebiegl pomyslnie.

Test 6:
Cel:Test ma na celu sprawdzenie czy program poprawnie wykona opcje rozmycia pionowego przy promieniu rownym 1.

Metoda testowania-dane wejsciowe:
-Wczytujemy plik "kubus.pgm".
-Wybieramy opcje "rozmycie".
-Wybieramy opcje "pionowe"
-Wybieramy opcje "promien =1"
-Wybieramy opcje "Zapisz"-Zapisujemy plik, na ktorym wykonano operacje "rozmycie".Wpisujemy nazwe, pod ktora chcemy miec zapisany przetworzony plik.
-Wybieramy opcje "Wyswietl" w celu sprawdzenia czy podana operacja sie udala.

Dane wyjsciowe:
-Wyswietlony zostaje komunikat wymagajacy podania rodzaju rozmycia a nastepnie promienia.
-Wyswietlony zostaje komunikat informujacy o zapisaniu pliku pod nazwa ktora podalismy.
-Rozmyty plik zostaje wyswietlony.Wyswietla sie rowniez komunikat informujacy o wyswietleniu pliku zapisanego.

Rezultat testu:Program poprawnie wykonal operacje rozmycia pionowego o promieniu rownym 1.Test 6 przebiegl pomyslnie.

Test 7:
Cel:Test ma na celu sprawdzenie czy program poprawnie wykona opcję rozmycia poziomego o promieniu rownym 2.

Metoda testowania-dane wejsciowe:
-Wczytujemy plik "kubus.pgm".
-Wybieramy opcje "rozmycie".
-Wybieramy opcje "poziome"
-Wybieramy opcje "promien = 2"
-Wybieramy opcje "Zapisz"-Zapisujemy plik, na ktorym wykonano operacje "rozmycie".Wpisujemy nazwe, pod ktora chcemy miec zapisany przetworzony plik.
-Wybieramy opcje "Wyswietl" w celu sprawdzenia czy podana operacja sie udala.

Dane wyjsciowe:
-Wyswietlony zostaje komunikat wymagajacy podania rodzaju rozmycia a nastepnie promienia a nastepnie o wartosci promienia.
-Wyswietlony zostaje komunikat informujacy o zapisaniu pliku pod nazwa ktora podalismy.
-Plik na ktorym wykonano opcje rozmycia zostaje wyswietlony.Wyswietla sie rowniez komunikat informujacy o wyswietleniu pliku zapisanego.

Rezultat testu:Program poprawnie wykonal operacje rozmycia poziomego o promieniu rownym 2.Test 7 przebiegl pomyslnie.

Test 8
1.Cel:Test ma na celu sprawdzenie czy program poprawnie wykona kilka losowych operacji na jednym obrazie.

1.Metoda testowania-dane wejsciowe:
-Wczytujemy plik "kubus.pgm"
-Wybieramy opcje "konturowanie"
-Wybieramy opcje "negatyw" nastepnie zapisujemy.
-Wybieramy opcje "wyswietlenie" w celu wyswietlenia dwukrotnie przetworzonego obrazu.

1.Dane wyjściowe:
-Wyswietlony zostaje komunikat o wykonaniu konturowania
-Wyswietlony zostaje komunikat o wykonaniu negatywu oraz o zapisaniu pliku, na ktorym zostalo wykonane dwukrotne przetworzenie.

1.Rezultat testu: Program poprawnie wykonal wszystkie wymienione wyzej operacje. Test 7 przebiegl pomyslnie.

2.Cel: Druga proba polega na zmianie kolejnosci wymienionych wyzej operacji

2.Metoda testowania-dane wejsciowe
-Wczytujemy plik "kubus.pgm"
-Wybieramy opcje "negatyw"
-Wybieramy opcje "konturowanie" nastepnie zapisujemy.
-Wybieramy opcje "wyswietlenie" w celu wyswietlenia dwukrotnie przetworzonego obrazu.

2.Dane wyjsciowe:
-Wyswietlony zostaje komunikat o wykonaniu negatywu
-Wyswietlony zostaje komunikat o wykonaniu konturowania oraz o zapisaniu pliku, na ktorym zostalo wykonane dwukrotne przetworzenie.

2.Rezultat proby 2: Proba 2 przebiegla pomyslnie, pomimo wykonania identycznych czynnosci jak w probie 1,program wyswietlil obraz inaczej wygladajacy-oznacza to ze w tym przypadku kolejnosc miala znaczenie. 
Test 9.
Cel:Test ma na celu sprawdzenie czy przy wybraniu opcji "Wyjscie" program sie wylaczy.

Metoda testowania-dane wejsciowe:
-Wczytujemy plik "kubus.pgm"
-Wybieramy opcje "Wyjscie"

Dane wyjsciowe:
-Program sie wylaczyl

Rezulat testu: Program poprawnie wykonal operacje "wyjscie" oraz sie wylaczyl. Test 9 przebiegl pomyslnie.

Test 10.
1.Cel:Test ma na celu sprawdzenie czy program poprawnie wykona kilka operacji innych niz negatyw oraz konturowanie na jednym obrazie.

1.Metoda testowania-dane wejsciowe:
-Wczytujemy plik "kubus.pgm"
-Wybieramy opcje "progowanie"
-Wybieramy opcje "rozmycie "nastepnie "poziome" oraz "promien = 2 " a potem zapisujemy.
-Wybieramy opcje "wyswietlenie" w celu wyswietlenia dwukrotnie przetworzonego obrazu.

1.Dane wyjsciowe:
-Wyswietlony zostaje komunikat o wykonaniu progowania oraz o zapisaniu pliku pod nazwa, ktora wybralismy dla przetworzonego obrazu.

1.Rezultat testu:Program poprawnie wykonal progowanie oraz rozmycie na jednym obrazie. Proba 2 wyglada identycznie jednak w odwrotnej kolejnosci wywolujemy funkcje.Proba 2 rowniez przebiegla pomyslnie i wyswietlila poprawnie obraz.

3.Cel:Test ma na celu sprawdzenie czy program poprawnie wykona operacje konturowania oraz rozmycia na jednym obrazie.
3.Metoda testowania-dane wejsciowe:
-Wczytujemy plik "kubus.pgm"
-Wybieramy opcje konturowanie 
-Wybieramy opcje rozmycia pionowego o promieniu 1
-Wybieramy opcje wyswietlenia 

3.Dane wyjsciowe:
-Wyswietlony zostaje komunikat o wykonaniu konturowania
-Wyswietlony zostaje obraz po dwukrotnym przetworzeniu oraz komunikat "wyswietlono".

3.Rezultat testu:Program poprawani wykonal operacje rozmycia oraz konturowania na jednym obrazie.
Proba 3 przebiegla pomyslnie.

Test 11.
Cel:Test ma na celu wykonanie wszystkich operacji na jednym obrazie.

Metoda testowania-dane wejsciowe:
-Wczytujemy plik "kubus.pgm"
-Wybieramy opcje rozmycia poziomego o promieniu rownym 2
-Wybieramy opcje negatywu 
-Wybieramy opcje progowania dla progu =80
-Wybieramy opcje konturowania a nastepnie zapisujemy czterokrotnie przetowrzony obraz pod dowolna nazwa.
-Wybieramy opcje wyswietlenia 

Dane wyjsciowe:
-Wyswietlony zostaje komunikat informujacy o wykonaniu negatywu
-Wyswietlony zostaje komunikat informujacy o wykonaniu progowania
-Wyswietlony zostaje komunikat informujacy o wykonaniu konturowania
-Wyswietlony zostaje komunikat informujacy o wykonaniu o zapisaniu
-przetworzony obraz zostaje wyswietlony

Rezultat testu: Obraz czterokrotnie przetworzony zostaje pomyslnie wyswietlony. Test 11 przebiegl pomyslnie.

Test 12.
Cel:Sprawdzenie jak zareaguje program przy wcisnieciu innego numeru niz tego przypisanym do opcji.

Metoda testowania-dane wejsciowe:
-Wczytujemy plik "kubus.pgm"
-Wybieramy numer "9"

Dane wyjsciowe:
-Wyswietlono komunikat "Nie rozpoznano opcji, prosze podac inna"

Rezultat testu: Program poprawnie zareagowal na nieznany numer.

Wnioski:Program poprawnie przeszedl wszystkie testy, wykonal poprawnie wszystkie rodzaje przetwarzania oraz wykonal operacje wyjscia.Na podstawie powyzszych testow mozemy stwierdzic ze program dziala poprawnie.
 */
