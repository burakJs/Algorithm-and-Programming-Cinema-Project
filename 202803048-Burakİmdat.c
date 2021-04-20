#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define OGR_UCRET 20
#define TAM_UCRET 30

enum SalonNames
{
    RED,
    GREEN,
    BLUE
};

struct User
{
    char name[20];
    char password[20];
} user;

struct Salon
{
    enum SalonNames name;
    int matine[5][50];
} Red, Green, Blue;

int HASILAT = 0;
int MATINELER[3][5]; //[0] => RED | [1] => GREEN  | [2] => BLUE

void Login();
int fileExists(char *filename);
void menu();
void hasilatiYaz(int hasilat);
void hasilatiOku();
void kayitOlMenu();
void kayitOlRed(int matineDeger);
void kayitOlGreen(int matineDeger);
void kayitOlBlue(int matineDeger);
void init();
void degerOku(enum SalonNames salonName);
void degerYaz(enum SalonNames salonName);
void salonDetay();

int main()
{
    int secenek;
    Red.name = RED;
    Green.name = GREEN;
    Blue.name = BLUE;
    init();
    if (fileExists("Log.txt"))
        hasilatiOku();
    else
        hasilatiYaz(HASILAT);

    printf("******* SINEMAMIZA HOSGELDINIZ *******\n\n");
    Login();
    return 0;
}

void Login()
{
    int checkWhile = 0;

    FILE *file;
    int exist = fileExists("sifre.txt");
    while (checkWhile == 0)
    {
        printf("Username : ");
        scanf("%s", user.name);
        printf("\n");

        printf("Password : ");
        scanf("%s", user.password);
        printf("\n");

        if (exist)
        {
            char a[255];
            strcat(user.name, " ");
            strcat(user.name, user.password);
            file = fopen("sifre.txt", "r");
            fgets(a, 255, file);

            if (strcmp(a, user.name) == 0)
            {
                checkWhile = 1;
                fclose(file);
                menu();
            }
            else
            {
                printf("Wrong credentials\n");
            }
        }
        else
        {
            file = fopen("sifre.txt", "w");
            fprintf(file, "%s %s", user.name, user.password);
            fclose(file);
            checkWhile = 1;
            menu();
        }
    }
}

int fileExists(char *filename)
{
    if (!access(filename, F_OK))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void hasilatiYaz(int hasilat)
{
    FILE *file;
    file = fopen("Log.txt", "w");
    fprintf(file, "%d", hasilat);
    fclose(file);
}

void hasilatiOku()
{
    FILE *file;
    file = fopen("Log.txt", "r");
    fscanf(file, "%d", &HASILAT);
    printf("HASILAT : %d \n\n", HASILAT);
    fclose(file);
}

void menu()
{
    int secenek;
    printf("1- HASILATI OGRENMEK\n");
    printf("2- SALON DETAYLARI\n");
    printf("3- KAYIT YAPMAK\n");
    scanf("%d", &secenek);
    if (secenek == 1)
    {
        hasilatiOku();
        menu();
    }
    else if (secenek == 2)
    {
        salonDetay();
    }
    else if (secenek == 3)
    {
        kayitOlMenu();
    }
    else
    {
        printf("Yanlis secenek\n");
        menu();
    }
}

void salonDetay()
{
    degerOku(RED);
    degerOku(GREEN);
    degerOku(BLUE);

    for (int i = 0; i < 3; i++)
    {
        switch (i)
        {
        case 0:
            printf("RED :\n");
            break;
        case 1:
            printf("GREEN :\n");
            break;
        case 2:
            printf("BLUE :\n");
            break;
        }
        for (int j = 0; j < 5; j++)
        {
            printf("%d matinesinde %d kisi bulunmaktadir \n", j + 1, MATINELER[i][j]);
        }
    }
    printf("\n");
    menu();
}

void kayitOlRed(int matineDeger)
{

    srand(time(NULL));
    int koltuk;
    int secenek = 0;
    while (secenek == 0)
    {
        koltuk = rand() % 50;
        if (*(*(Red.matine + matineDeger - 1) + koltuk) != 1)
        {
            printf("Red salonunda %d matinesinde %d nolu koltukta yeriniz hazir\n", matineDeger, koltuk);
            *(*(Red.matine + matineDeger - 1) + koltuk) = 1;
            degerOku(RED);
            *(*(MATINELER) + matineDeger - 1) = *(*(MATINELER) + matineDeger - 1) + 1;
            // MATINELER[0][matineDeger - 1] = MATINELER[0][matineDeger - 1] + 1;
            degerYaz(RED);
            secenek += 1;
        }
    }

    menu();
}

void kayitOlGreen(int matineDeger)
{

    srand(time(NULL));
    int koltuk;
    int secenek = 0;
    while (secenek == 0)
    {
        koltuk = rand() % 50;
        if (*(*(Green.matine + matineDeger - 1) + koltuk) != 1)
        {
            printf("Red salonunda %d matinesinde %d nolu koltukta yeriniz hazir\n", matineDeger, koltuk);
            *(*(Green.matine + matineDeger - 1) + koltuk) = 1;
            degerOku(GREEN);
            *(*(MATINELER + 1) + matineDeger - 1) = *(*(MATINELER + 1) + matineDeger - 1) + 1;
            // MATINELER[0][matineDeger - 1] = MATINELER[0][matineDeger - 1] + 1;
            degerYaz(GREEN);
            secenek += 1;
        }
    }

    menu();
}

void kayitOlBlue(int matineDeger)
{

    srand(time(NULL));
    int koltuk;
    int secenek = 0;
    while (secenek == 0)
    {
        koltuk = rand() % 50;
        if (*(*(Blue.matine + matineDeger - 1) + koltuk) != 1)
        {
            printf("Red salonunda %d matinesinde %d nolu koltukta yeriniz hazir\n", matineDeger, koltuk);
            *(*(Blue.matine + matineDeger - 1) + koltuk) = 1;
            degerOku(BLUE);
            *(*(MATINELER + 2) + matineDeger - 1) = *(*(MATINELER + 2) + matineDeger - 1) + 1;
            // MATINELER[0][matineDeger - 1] = MATINELER[0][matineDeger - 1] + 1;
            degerYaz(BLUE);
            secenek += 1;
        }
    }

    menu();
}

void kayitOlMenu()
{
    int secenek;
    int secenek2 = 0;
    int matineSecenek = 0;

    while (secenek > 3 || secenek < 1)
    {
        printf("Hangi salonu istersiniz ? \n");
        printf("1- Red\n");
        printf("2- Green\n");
        printf("3- Blue\n");
        scanf("%d", &secenek);
    }
    while (secenek2 > 2 || secenek2 < 1)
    {
        printf("Ogrenci isen 1 , Tam isen 2 \n");
        scanf("%d", &secenek2);
    }
    if (secenek2 == 1)
    {
        HASILAT += OGR_UCRET;
        hasilatiYaz(HASILAT);
    }
    else
    {
        HASILAT += TAM_UCRET;
        hasilatiYaz(HASILAT);
    }
    while (matineSecenek > 5 || matineSecenek < 1)
    {
        printf("Hangi matinede izlemek istersiniz (1,2,3,4,5) \n");
        scanf("%d", &matineSecenek);
    }

    switch (secenek)
    {
    case 1:
        kayitOlRed(matineSecenek);
        break;
    case 2:
        kayitOlGreen(matineSecenek);
        break;
    case 3:
        kayitOlBlue(matineSecenek);
        break;
    default:
        kayitOlMenu();
        break;
    }
}

void degerYaz(enum SalonNames salonName)
{
    FILE *file;
    switch (salonName)
    {
    case RED:
        file = fopen("red.txt", "w");
        break;
    case GREEN:
        file = fopen("green.txt", "w");
        break;
    case BLUE:
        file = fopen("blue.txt", "w");
        break;

    default:
        break;
    }

    for (int i = 0; i < 5; i++)
    {
        fprintf(file, "%d ", MATINELER[salonName][i]);
    }

    fclose(file);
}

void degerOku(enum SalonNames salonName)
{
    FILE *file;
    switch (salonName)
    {
    case RED:
        file = fopen("red.txt", "w");
        break;
    case GREEN:
        file = fopen("green.txt", "w");
        break;
    case BLUE:
        file = fopen("blue.txt", "w");
        break;

    default:
        break;
    }

    for (int i = 0; i < 5; i++)
    {
        fscanf(file, "%d", &MATINELER[salonName][i]);
    }
    fclose(file);
}

void init()
{
    FILE *file;
    file = fopen("red.txt", "w");
    fprintf(file, "%d %d %d %d %d", 0, 0, 0, 0, 0);
    fclose(file);
    file = fopen("green.txt", "w");
    fprintf(file, "%d %d %d %d %d", 0, 0, 0, 0, 0);
    fclose(file);
    file = fopen("blue.txt", "w");
    fprintf(file, "%d %d %d %d %d", 0, 0, 0, 0, 0);
    fclose(file);
}
