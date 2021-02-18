#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//co zwracaja poszzczegolne funkcje, odwolywanie sie do tablicy w funkcjach, wczytywanie , wypisywanie,
//czy tablice na poczatku oplaca sie wypelniac zerami
//wypisywanie wielu zer gdy komorka 0



#define string_size 9900
#define number_size 1100
static const int base = 1e9;
static const int base_digit = 9;
char licz1[string_size];
char licz2[string_size];
int sign1, sign2;
int a[number_size], b[number_size], p[number_size], k[number_size], s[number_size], r[number_size];
long long w[2*number_size];
int n,m;
int d1, d2;
FILE *fp;  //plik z liczba a
FILE *fp2; //plik z liczba b
FILE *fp3; //plik z liczba utworozna przy pomocy obliczen na a i b

int MAX (int x, int y);
void Init();
void Sum();
void Sub();
void Mult();
void Div();
long long mnoz(long long a,long long b, long long p);

int MAX (int x, int y)
{
    if(x>y)
        return x;
    else
        return y;
}

void Init()
{
    //inicjalizacja zmiennych
    for(int i=0; i<number_size; i++)
    {
        //przygotowywanie tablic
        a[i]=0;
        b[i]=0; //liczby a i p
        p[i]=0;
        k[i]=0;
        s[i]=0; //do binserch
        r[i]=0; //reszta z dzielenia
    }
    for(int i=0; i<2*number_size; i++)
    {
        //przygotowywanie tablic
        w[i]=0; //wynik
    }

    fp = fopen ("liczba1.txt", "r");
    fp2 = fopen ("liczba2.txt", "r");
    fp3 = fopen ("wynik.txt","w");

    d1=0, d2=0;
    char ch; //zmienna pomocnicza do wczytania sringa

    //wczytywanie liczby pierwszej do licz1 i ustalenie jej dlugosci
    ch=fgetc(fp);
    while (ch!=EOF)
    {
        licz1[d1]=ch;
        ch = fgetc(fp);
        d1++;
    }

    //wczytywanie liczby drugiej do licz2 i ustalenie jej dlugosci
    ch=fgetc(fp2);
    while (ch!=EOF)
    {
        licz2[d2]=ch;
        ch = fgetc(fp2);
        d2++;
    }

    fclose(fp);
    fclose(fp2);

    //konwersja liczb
    //jeœli liczba jest ujemna usstaw sign na 1, jeœli jest dodatnia ustaw sign na 0
    if (licz1[0]=='-')
        sign1=1;
    else
        sign1=0;
    n=0;
    for(int i = d1-1; i >= 0+sign1; i -= base_digit)
    {
        unsigned int x = 0;
        for(int j = MAX(sign1, i-base_digit+1); j<=i; j++)
            x = x*10 + (unsigned int) (licz1[j] - '0');
        a[n]=x;
        n++;
    }

    if (licz2[0]=='-')
        sign2=1;
    else
        sign2=0;
    m=0;
    for(int i = d2-1; i >= 0+sign2; i -= base_digit)
    {
        unsigned int x = 0;
        for(int j = MAX(sign2, i-base_digit+1); j<=i; j++)
            x = x*10 + (unsigned int) (licz2[j] - '0');
        b[m]=x;
        m++;
    }
}

void Sum()
{
    int nadmiar=0;
    w[0]=(a[0]+b[0])%base;
    for (int i=1; i<MAX(n,m); i++)
    {
        nadmiar=((w[i-1])-(w[i-1])%base)/base;
        // nadmiar pierwsza cyfra sumy dwoch komorek tablic a i b jesli liczba przekracza 9 cyfr
        w[i]=((a[i]+b[i])%base)+nadmiar;
        //suma dwoch komorek z nadmiarem z poprzedniej liczby
    }
}

void Sub()
{
    //odejmowanie jesli liczba1 > liczba2
    if(n>m || a[n-1]>b[n-1])
    {
        //odejmowanie kazdej komorki jak w odejmowaniu slupkowym
        for(int i=0; i<n; i++)
        {
            if(a[i]>b[i])
            {
                w[i]=a[i]-b[i];
            }
            else // jesli komorka liczby1 jest mniejsza od komorki z liczby2 zapozyczamy z kolejnej
                //komorki liczby1 jedynke i dodajemy jej wartosc do aktualnej komorki
            {
                a[i+1]=a[i+1]-1;
                a[i]=a[i]+base;
                w[i]=a[i]-b[i];
            }

        }
    }
    else
// jesli liczba ktora chcemy odjac jest wieksza od liczby od ktorej odejmujemy
// zamieniamy je miejscami a wynik wypisujemy z minusem
    {
        for(int i=0; i<m; i++)
        {
            if(b[i]>a[i])
            {
                w[i]=b[i]-a[i];
            }
            else // jesli komorka liczby2 jest mniejsza od komorki z liczby1 zapozyczamy z kolejnej
                //komorki liczby2 jedynke i dodajemy jej wartosc do aktualnej komorki
            {
                b[i+1]=b[i+1]-1;
                b[i]=b[i]+base;
                w[i]=b[i]-a[i];
            }
        }
        fprintf(fp3,"-");

    }
}

void Mult()
{
    for(int i=0; i<n; i++)
    {
        long long dod=0;
        long long c=0;

        for(int j=0; j<=m; j++)
        {

            c= mnoz(a[i],b[j],base)+dod%base;
            w[j+i]+=c;
            dod=((long long) a[i]*b[j] /base) +(dod/base);

        }
    }

    for(int i=0; i<=2*MAX(n,m); i++)
    {
        long long sz=w[i]/base;
        w[i]=(w[i]%base);
        w[i+1]+=sz;
    }

}

long long mnoz(long long a, long long b, long long p)
            {
                long long w = 0;
                while (b)
                {
                    if (b % 2 == 1)
                        w = (w + a) % p;
                    b /= 2;
                    a = (2 * a) % p;
                }
                return w;
            }
/*
void Mult()
{
    //maxs wieksza z dlugosci liczb
    int rozmiar=maxs; // dlugosc podzielonej liczby na dwie czesci
    // int potega = 10^n;

    unsigned long long karatsuba(unsigned int a[],unsigned int b[])
    {

        if(rozmiar==1)
        {
            liczba1*liczba2

        }
    //zmiana rozmiaru na o polowe mniejszy
        if(rozmiar%2==0)
        {
            rozmiar=rozmiar/2;
        }
        else
        {
            rozmiar=(rozmiar/2) +1
        }


        unsigned int liczbaa1[rozmiar]; // pierwsza czesc liczby a

        unsigned int liczbaa2[rozmiar]; // druga czesc liczbya


        unsigned int liczbab1[rozmiar]; // pierwsza czesc liczby b

        unsigned int liczbab2[rozmiar]; // druga czesc liczby b



        for(int i=0; i<rozmiar; i++)
        {

            liczbaa1[i]=a[rozmiar + i];

            liczbaa2[i]=a[i];
        }


        for(int i=0; i<rozmiar; i++)
        {

            liczbab1[i]=b[rozmiar + i];

            liczbab2[i]=b[i];
        }

        unsigned long long a1b1= karatsuba(liczbaa1[],liczbab1[]);
        unsigned long long a2b2= karatsuba(liczbaa2[],liczbab2[]);
        unsigned long long e= karatsuba(sum1(liczbaa1[],liczbaa2[]),sum1(liczbab1,liczbab2));
        unsigned long long f=sum1(a1b1,a2b2);
        unsigned long long g=sub1(e[],f[]);


        // return w[]?

    }

}

// wyszukiwanie binarne, tablica p[]-poczatek,k[]-koniec,s[]-srodek,r[]-reszta
void Div()
{
   // p->0
   // k-> 10^(n-m)

    //gdy liczba2 jest wieksza od liczby1 to sie w niej nie miesci wiec wynik dzielenia to 0, a reszta jest cala liczba1
    if(m>n)
    {
        w->0
        //r->liczba1

        for(int i=0;i<1100){
            r[i]=a[i];
        }
    }
    //inaczej binary search w poszukiwaniuw yniku z dzielenia
    else
    {
    //dopoki poczatek mniejszy od konca
        while(p[]<=k[])
        {

            srodek=(p+k)/2

            if((srodek*b)<a)
            {
                p = srodek + 1
            }
            else if((srodek*b)>a)
            {
                k= srodek -1

            }
            else
            {
                //wynik z dzielenia nie ma reszty wiec
                //w=k;
                for(int i=0;i<1100;i++){
                    w[i]=k[i];
                }
            }

        }

        //w znaleziona najwieksza liczbap taka ze p*b>a

        for(int i=0;i<1100;i++){
            w[i]=p[i];
        }
        //reszta z dzielenia

        r=a-(w*b);

    }



}
*/

void Save()
{
    int nonzero=1100;
    /* while(a[nonzero]==0||nonzero==0)
         nonzero--;
     for(int i=nonzero; i>=0; i--)
         fprintf(fp3,"%d",a[i]);
     fprintf(fp3,"\n");

     nonzero=1100;
     while(b[nonzero]==0||nonzero==0)
         nonzero--;
     for(int i=nonzero; i>=0; i--)
         fprintf(fp3,"%d",b[i]);
     fprintf(fp3,"\n");
    */


    nonzero=2199;
    while(w[nonzero]==0)
        nonzero--;
    for(int i=nonzero; i>=0; i--)
    {
       if(w[i]<base/10 && i<nonzero)
        {
            int g=0;
            g=w[i]+1;
            while(g<base/10)
            {
                fprintf(fp3,"0");
                g=g*10;
            }
        }

        int x = (int) w[i];
        fprintf(fp3, "%d", x);
    }


    fclose(fp3);
}

