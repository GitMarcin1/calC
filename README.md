# Projekt C - Kalkulator wielkich liczb

Celem projektu jest stworzyć kalkulator operujący na liczbach o wielkości do 32768 bitów.Obsługiwać on będzie operacje dodawania, odejmowania, mnożenia oraz dzielenia całkowitego\
z resztą. Program pobiera z plików dwie duże liczby w postaci stringów, które następnie dzielone są na mniejsze liczby, zamieniane ze stringów w typ int, i częściami\
zapisywane od tyłu w tablicach. Program uruchamiany jest w konsoli, po uruchomieniu, zestandardowego wejścia wczytana zostanie przy pomocy odpowiedniej litery (S−sumowanie, R−odejmowanie, M−mnozenie, D−dzielenie)operacja, która ma zostać wykonana. Wypisywanie wyniku zarówno na standardowe wyjściejak i do pliku.Projekt podzielony jest na dwa pliki: main.c i bignum.h. Struktura pliku bignum.h \
int a[1100], b[1100], p[1100], k[1100], s[1100], r[1100];\
long long w[2200],\
a, b - dane liczby\
p, k, s - zmienne potrzebne do wykonania dzielenia\
w - liczba będąca wynikiem danej operacjir - liczba będąca resztą z dzielenia a przez b\
n, m - liczba komórek tablicy a[], b[]\
void init(plik.txt)- funkcja wczytuje dwie liczby a i b z plików liczba1.txt, liczba2.txt- pliki należy umieścić w folderze z plikiem wykonywalnym kalkulator- funkcja wczytuje \liczby a i b do tablicy charów i konwertuje je do tablic a[] i b[]\
void sum()- funkcja wykonuje operację dodawania liczby a do liczby b, wynik znajduje się w tablicy w[]- zastosowany zostanie algorytm dodawania w słupku z przeniesieniem- \szacowana złożoność algorytmu to O(n)\
void sub()- funkcja wykonuje operację odejmowania liczby b od liczby a, wynik znajduje się w tablicy w[]- zastosowany zostanie algorytm odejmowania w słupku z przeniesieniem-\ szacowana złożoność algorytmu to O(n)\
void mult()- funkcja wykonuje operację mnożenia liczby a przez liczbę b, wynik znajduje się w tablicy w[]- zastosowany zostanie algorytm szybkiego mnożenia Karatsuby oparty na\ strategii dziel irządź- szacowana złożoność algorytmu to O(nlog23) (aktualnie zastąpione algorytmem rosyjskich chłopów i mnożeniem słupkowym - czas O(n^2)\
void div()- funkcja wykonuje operację dzielenia całkowitego z resztą liczby a przez liczbę b, wynikznajduje się w tablicy w[] a reszta w tablicy r[]- zastosowany zostanie algorytm wyszukiwania binarnego wyniku, testowanie wyniku będziewykorzystywać zdefiniowaną wcześniej funkcję mult()- szacowana złożoność algorytmu toO(nlog23∗log(n−m))\
void save(plik.txt)- funkcja zapisuje wynik ostatniej operacji do pliku plik.txt w folderze, w którym znajduje sięprogram- jeśli plik już istnieje w folderze, jego zawartość \zostaje usunięta i nadpisana nowym wynikiem.\
Używane biblioteki:<stdio.h>, <stdlib.h>, <string.h>\

 (mnożenie aktualnie zastąpione algorytmem rosyjskich chłopów i mnożeniem słupkowym - czas O(n^2), dzielenie nieaktywne)

