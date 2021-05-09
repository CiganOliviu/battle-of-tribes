#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER_OF_PEOPLE 1000

typedef struct
{
    char Name[40];
    char Tribe[20];
    char Function[20];
    float PowerWhenRains;
    float PowerWhenIsSunny;
} TribeMember;

FILE * OpenFile(const char * FileName)
{
    FILE * File = fopen(FileName, "r");

    return File;
}

FILE * ValidateFile(const char * FileName)
{
    FILE * File = OpenFile(FileName);

    if (!File)
    {
        printf("File not found.");
        exit(5);
    }

    return File;
}

int GetNumberOfTribeMembers(FILE * File)
{
    int NumberOfTribeMembers = 0;

    char Line[50];

    while (fgets(Line, 50, File))
        NumberOfTribeMembers += 1;

    return NumberOfTribeMembers;
}

void GetPositionInStruct(TribeMember * TribeMembers, int Index, int Position, char * Word)
{
    if (Position == 1)
        strcpy(TribeMembers[Index].Name, Word);

    if (Position == 2)
        strcpy(TribeMembers[Index].Tribe, Word);

    if (Position == 3)
        strcpy(TribeMembers[Index].Function, Word);

    if (Position == 4)
        TribeMembers[Index].PowerWhenRains = (float)strtod(Word, NULL);

    if (Position == 5)
        TribeMembers[Index].PowerWhenIsSunny = (float)strtod(Word, NULL);
}

TribeMember * GetTribeMembers(FILE * File)
{
    TribeMember * TribeMembers =
            (TribeMember *)malloc(MAX_NUMBER_OF_PEOPLE * sizeof(TribeMember));

    char Line[50];
    int Index = 0;

    while (fgets(Line, 50, File))
    {
        int Position = 1;
        char * Word = strtok(Line, ",");

        while (Word != NULL)
        {
            GetPositionInStruct(TribeMembers, Index, Position, Word);

            Position += 1;
            Word = strtok(NULL, ",");
        }

        Index += 1;
    }

    return TribeMembers;
}

char * GetWeather(FILE * File)
{
    char * Weather = (char *)malloc(50 * sizeof(char));
    fgets(Weather, 50, File);

    return Weather;
}

int CountRainyDays(char * Weather)
{
    int RainyDays = 0;

    for (int i = 0; i < strlen(Weather); ++i)
        if (Weather[i] == 'r')
            RainyDays += 1;

    return RainyDays;
}

int CountSunnyDays(char * Weather)
{
    int SunnyDays = 0;

    for (int i = 0; i < strlen(Weather); ++i)
        if (Weather[i] == 's')
            SunnyDays += 1;

    return SunnyDays;
}

float GetTotalPower(char * Weather, TribeMember Member)
{
    int RainyDays = CountRainyDays(Weather);
    int SunnyDays = CountSunnyDays(Weather);

    float TotalPower = (RainyDays * Member.PowerWhenRains) + (SunnyDays * Member.PowerWhenIsSunny);

    return TotalPower;
}

void ShowAllMembers(TribeMember * TribeMembers, int NumberOfTribeMembers)
{
    for (int i = 0; i < NumberOfTribeMembers; ++i)
        printf("%s %s %s %0.2f %0.2f \n", TribeMembers[i].Name, TribeMembers[i].Tribe, TribeMembers[i].Function,
               TribeMembers[i].PowerWhenRains, TribeMembers[i].PowerWhenIsSunny);

    printf("\n");
}

int main()
{

    return 0;
}
