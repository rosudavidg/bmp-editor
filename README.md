```
Fiecare poza va fi retinuta intr-un vector bidimensional de tip pixel, 
alocat dinamic. Structura pixel este alcatuita din trei valori de tip 
unsigned char: b, g, r.

Alte poze auxiliare sau matrice auxiliare vor fi alocate dinamic. 
Memoria alocata acestora va fi eliberata dupa utilizarea lor.

Functia main
	In functia main citesc datele de intrare din input.txt si apelez functiile
aferente celor patru task-uri.

Task 1
	Intr-o matrice de pixeli auxiliara, copiez elementele pozei originale.
Apoi, pentru fiecare pixel, calculez suma componentelor si o impart la 3.
Noul pixel va avea cele trei componente egale cu numarul rezultat.
Matricea de pixeli auxiliara reprezinta poza ceruta si va fi afisata in
fisierul cerut.

Task 2
	Toate elementele pozei au fost copiate intr-o matrice auxiliara astfel:
fiecare element cu pozitia (x, y) este copiat in pozitia (x+1,y+1), iar apoi
matricea este bordata cu valoare (0,0,0). Astfel, orice pixel din poza initiala
are acum vecini in toate cele 4 directii (vecin pixel, sau vecin nul). Pentru
fiecare pixel se aplica algoritmul de prelucrare, care are la baza filtrele date.
Pentru fiecare filtru aplicat, poza generata va fi afisata intr-un fisier.

Task 3
	Pentru algoritmul de selectie am nevoie de o matrice auxiliara, pentru
a retine care pixeli au fost selectati.
	checked[x][y] = 1, daca pixelul de pe pozitia (x,y) a fost selectat, 
sau 0, altfel.
	Dupa inversarea pozei, incep algoritmul de selectie de la pixelul din 
pozitia (0,0). Pentru fiecare pixel selectat, se va aplica:
	- Se verifica care dintre vecini respecta regula ceruta (sus, jos, stanga, 
dreapta), si nu au fost inca selectati.
	- Se adauga intr-un vector de tip coada elementele care respecta regula de
mai sus. Se copiaza valoarea pixelului initial selectat in fiecare pixel din
coada.
	- Se procedeaza in mod recursiv verificarea vecinilor pixelilor din coada,
pana cand se ajunge la sfarsitul acesteia. Atunci zona va fi maximala, iar
toti pixelii din zona vor avea aceleasi componente (r, g, b).
	- Dupa finalizarea unei zone, se cauta pe aceeasi linie, de la stanga la
dreapta un nou pixel care nu a fost selectat. Daca nu exista, se trece la 
urmatoarea linie. Dupa ce s-a ajuns la ultimul pixel, algoritmul se opreste,
iar in matrice toate zonele sunt construite.
	Pentru realizarea fisierului compressed.bin, se aplica ulmatorul algoritm:
	- Se afiseaza cele doua headere
	- Se inverseaza liniile imaginii
	- Se afiseaza prima linie de pixeli
	- Pentru fiecare linie, de la linia 2, la penultima:
		- Se afiseaza primul pixel
		- Pentru toti pixelii de pe linie, de la pixelul 2, la penultimul, 
		se verifica daca are cel putin un vecin diferit de acesta. Daca are, 
		pixelul inseamna ca reprezinta marginea unei zone, deci ce afiseaza.
		Daca pixelul are toti vecinii identici, acesta nu se afiseaza.
		- Se afiseaza primul pixel
	- Se afiseaza ultima linie de pixeli
	Afisarea unui pixel (x, y) din poza, cu valoarea (r, g, b), reprezinta
afisarea valorilor x+1, y+1, r, g, b in binar.

Task 4
	Pentru decompresia unui fisier, aplic urmatorul algoritm:
	- Citesc din fisier cele doua headere
	- Aloc memorie pentru poza
	- Citesc elemente de tipul (linie, coloana, r, g, b) pana la sfarsitul 
fisierului
	- Initializez din nou matricea checked cu aceeasi semnificatie
	- Pentru fiecare element citit (x, y, r, g, b), checked[x-1][y-1] va fi 1,
iar acesta se va adauga in pozitia (x-1,y-1) in poza
	- Dupa adaugarea tuturor pixelilor, se va aplica urmatorul algoritm de 
completare a zonelor:
		- Pentru fiecare pixel, de la (0,0), la ultimul pixel de pe penultima
	linie, daca acesta este deja verificat, se verifica vecinul de jos. Daca 
	vecinul nu a fost verificat, cei doi pixeli vor face parte din aceeasi zona, 
	deci valorile celor doi vor fi la fel. Daca vecinul a fost verificat, 
	algoritmul trece mai departe.
		- La sfarsit, toti pixelii din interiorul zonelor vor fi completati.
	- Se roteste poza
	- Se afiseaza cele doua headere si poza in fisierul specificat.
	
```
