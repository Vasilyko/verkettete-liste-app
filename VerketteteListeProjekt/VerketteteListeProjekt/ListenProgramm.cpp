#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef struct Person
{
	char vorname[15];
	char nachname[15];
	int jahrgang;
	struct Person* pNext;
} struPerson;



void Output(struPerson* pListStart) {
	if (pListStart != NULL) {
		for (struPerson* pOut = pListStart; pOut != NULL; pOut = pOut->pNext) {
			printf("Person: %s, %s, %i\n", pOut->vorname, pOut->nachname, pOut->jahrgang);
		}
	}
	else {
		printf("Keine Elemente in der Liste vorhanden!\n");
	}

	system("pause");

}

// Erstellt ein Zufallsgeneriertes Jahr
int randomiseYear() 
{
	int randomInt = 1900 + (rand() % 119);
	return randomInt;
}

char randomiseLetter() {
	char randomChar = 'A' + (rand() % 26);
	return randomChar;
}

struPerson *Create(const int Anzahl) {
	struPerson *pStart = NULL;
	struPerson *pLast = NULL;

	for (int i = 0; i < Anzahl; i++)
	{
		struPerson *pNew = (struPerson *)malloc(sizeof(struPerson));
		pNew->vorname[0] = randomiseLetter();
		pNew->vorname[1] = '\0';
		pNew->nachname[0] = randomiseLetter();
		pNew->nachname[1] = '\0';
		pNew->jahrgang = randomiseYear();
		pNew->pNext = NULL;

		if (pLast != NULL)
		{
			pLast->pNext = pNew;
		}

		pLast = pNew;

		if (pStart == NULL)
		{
			pStart = pNew;
		}
	}
	return pStart;
}

void main() {
	srand((unsigned)time(NULL));

	int anzahlPersonen = 0;
	printf("Personenkartei> ");
	scanf_s("%i", &anzahlPersonen);
	struPerson *pStart = Create(anzahlPersonen);
	Output(pStart);




}
