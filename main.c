#include <stdio.h>
#include <stdlib.h>
#include "bignums.h"

int main()
{
    char a;
    scanf("%c",&a);

    Init();

    if(a=='S'){
        Sum(); //Suma
    }
    if(a=='R'){
        Sub(); //Ró¿nica
    }

    if(a=='M'){
        Mult();//Iloczyn
    }
   // if(a=='D'){
   //     Div();//Iloraz i reszta z dzielenia
    //}

    Save();
    return 0;
}
