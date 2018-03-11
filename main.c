//Sortowanie metodą Shella i Quicksort
// Politechnika Świętokrzyska
// w Kielcach
// (C)2016  gr. 1ID13B  Mykola Bohdan  Eugeniusz Fedoroszczak
//-----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <sys/time.h>
#include <string.h>

#define processor 2266




long long TimeValue=0;
unsigned long long time_RDTSC()
{
    union ticks
    {
        unsigned long long tx;
        struct dblword
        {
            long tl,th;
        } dw;
    } t;
    asm("rdtsc\n": "=a"(t.dw.tl),"=d"(t.dw.th));
    return t.tx;
}
void time_start()
{
    TimeValue=time_RDTSC();
}
long long time_stop()
{
    return (time_RDTSC()-TimeValue)/processor;
}

long long times;

long n;

char ** p;

enum ConsoleColor
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};

void generator()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Red));
    puts("---------------------------------------------");
    puts("|                 GENERATOR                 |");
    puts("---------------------------------------------");
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Yellow));
    printf(" Wprowadz liczebnosc zbioru:  ");
    scanf("%ld",&n);
    while(n<1 || n>259500)
    {
        printf("Wprowadz liczebnosc zbioru ponownie: ");
        scanf("%ld",&n);
    }
    char c;
    long MAS[n],array[n+1];
    long k=0,i=0,g=0,u=n;
    int rdm=32767,j=1;
    for (g=0; g<n+1; g++)
    {
        array[g]=0;
    }
    srand(time(NULL));

    printf("\nLiczby musza powtarzac sie? y/n: ");
    scanf("%c",&c);
    while(c!='y' && c!='n' && c!='Y' && c!='N')
    {
        scanf("%c",&c);
    }
    time_start();
    if(c=='n' || c=='N')
    {

        k=rand()%n;
        for (i=0; i < n; i++)
        {
            while(1)
            {
                if(u<rdm*j)
                {
                    k=rand()%(n-rdm*(j-1))+1+rdm*(j-1);
                    if(u<rdm*j)j--;
                }
                else j++;

                if ( array[k] == 0 )
                {
                    array[k] = 1;
                    MAS[i] = k;
                    u--;
                    break;
                }
            }
        }
    }
    else
    {
        for (i=0; i < n; i++)
        {
            MAS[i] = rand()%RAND_MAX;
        }
    }
    times = time_stop();
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Cyan));
    printf ("\nAlgorytm dzialal %ld mks.\n",times);
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Yellow));
    FILE *file = fopen("gen_ciag.txt","w");
    fprintf(file,"Zgenerowano liczb: %ld\n\n",n);
    for(i=0; i<n; i++)
        fprintf(file,"%ld ",MAS[i]);
    if(fclose(file))
        perror("fclose()");
    printf("\nZgenerowany ciag zapisany do:\n\"gen_ciag.txt\"\n");
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Green));
}

int wybor()
{
    FILE *file = fopen("gen_ciag.txt","r");
    fscanf(file,"%*s%*s %ld\n\n",&n);
    long MAS[n],i;
    for(i=0; i<n; i++)
    {
        fscanf(file,"%ld ",&MAS[i]);
    }
    if(fclose(file))
        perror("fclose()");
    char s;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Red));
    puts("---------------------------------------------");
    puts("|        WYBOR ALGORYTMU SORTOWANIA         |");
    puts("---------------------------------------------");
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Yellow));
    printf("    a - Sortowanie SHELL'a\n");
    printf("    b - Sortowanie QUICKSORT\n");
    while(s!='a' && s!='b' && s!='A' && s!='B')
    {
        scanf("%s",&s);
        puts("");
    }
    if(s=='a' || s=='A')
    {
        char *nazwa_alg[][60]= {"Sortowanie metoda Shella","sort_Shell_ciag.txt","\nZgenerowany ciag zapisany do:\n\"sort_Shell_ciag.txt\"\n\n"};
        p = (char **)nazwa_alg;
        time_start();
        shell(MAS);
    }
    else
    {
        char *nazwa_alg[][60]= {"Sortowanie metoda QuickSort","quick_sort_ciag.txt","\nZgenerowany ciag zapisany do:\n\"quick_sort_ciag.txt\"\n\n"};
        p = (char **)nazwa_alg;
        time_start();
        quick(MAS,0,n-1);
    }
    times = time_stop();
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | LightBlue));
    printf("\t%s\t\n",*(p+0));
    puts("---------------------------------------------");
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Yellow));
    FILE *file2 = fopen(*(p+1),"w");
    fprintf(file2,"%s dzialalo %ld mks.\n",*(p+0),times);
    fprintf(file2,"Posortowano liczb: %ld\n\n",n);
    for(i=0; i<n; i++)
    {
        fprintf(file2,"%ld ",MAS[i]);
    }
    if(fclose(file2))
    {
        perror("fclose()");
    }
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Yellow));
    printf(*(p+2));
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Cyan));
    printf ("\nAlgorytm dzialal %ld mks.\n",times);
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Green));
}

int shell(long *MAS)
{
    int h,i,j,x;
    for(h = 1; h < n; h = 3 * h + 1);
    h /= 9;
    if(!h)
        h++;
    while(h)
    {
        for(j = n - h - 1; j >= 0; j--)
        {
            x = MAS[j];
            i = j + h;
            while((i < n) && (x > MAS[i]))
            {
                MAS[i - h] = MAS[i];
                i += h;
            }
            MAS[i - h] = x;
        }
        h /= 3;
    }
    return *MAS;
}

int quick(long *MAS,long lewy,long prawy)
{
    long v=MAS[(lewy+prawy)/2];
    long i, j, x;
    i=lewy;
    j=prawy;
    do
    {
        while(MAS[i]<v) i++;
        while(MAS[j]>v) j--;
        if (i<=j)
        {
            x=MAS[i];
            MAS[i]=MAS[j];
            MAS[j]=x;
            i++;
            j--;
        }
    }
    while (i<=j);

    if(j>lewy) quick(MAS,lewy,j);
    if(j<prawy) quick(MAS,i,prawy);
    return *MAS;
}

int main()
{
    system ("mode con cols=46 lines=30");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char i;
    do{
        system("cls");
        SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Red));
        puts("*********************************************");
        puts("|            Algorytmy sortowania           |");
        puts("*********************************************");
        SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Yellow));
        printf("\t1) Generator;\n\t2) Wybor sortowania;\n\t3) Exit;\n");
        SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Red));
        puts("---------------------------------------------");
        i=getch();
        switch (i)
        {
            case '1':
                generator();
                break;
            case '2':
                wybor();
                break;
                default: continue; break;
        }
        system("pause");
    }while(i!='500');
    printf("\n...................KONIEC....................\n");
    SetConsoleTextAttribute(hConsole, (WORD) ((DarkGray) | Yellow));
    return 0;
}
