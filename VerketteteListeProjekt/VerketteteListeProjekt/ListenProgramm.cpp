#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "ctype.h"

/**
 Person:

 Personen-Objekt welches für die Liste
 wichtig ist. Personen werden erstellt und
 in die Liste eingetragen.

 @David Gataric und Vasily Kozlov bnghjm
*/
typedef struct Person
{
	char vorname[15];
	char nachname[15];
	int jahrgang;
	struct Person* pNext;
} struPerson;


/**
 outputList:

 Liest alle Personen aus der Liste aus und
 gibt sie anschliessend in der Konsole aus.

 COMMAND_NAME: L

 @David Gataric
*/
void outputList(struPerson* pListStart) {
	if (pListStart != NULL) {
		for (struPerson* pOut = pListStart; pOut != NULL; pOut = pOut->pNext) {
			printf("Person: %s, %s, %i\n", pOut->vorname, pOut->nachname, pOut->jahrgang);
		}
	}
	else {
		printf("Die Liste ist leer.! Erstellen Sie neue Personen mit dem Command: 'C'\n");
	}

}

/**
 randomiseYear:
 	
 Diese Methode gibt eine zufallsgenerierte
 Zahl zwischen 1900 und 2018 zurück.
 
 returns: int randomInt

 @David Gataric und Vasily Kozlov
*/
int randomiseYear() 
{
	int randomInt = 1900 + (rand() % 119);
	return randomInt;
}

/**
 randomiseLetter:
 	
 Diese Methode gibt ein zufalls Char zwischen
 A und Z zurück.
 
 returns: char randomChar	

 @David Gataric und Vasily Kozlov
*/
char randomiseLetter() {
	char randomChar = 'A' + (rand() % 26);
	return randomChar;
}

/**
 create:

 Erstellt eine verkettete Liste von Personen.
 Es werden so viele Personen erstellt, wie sie
 angegeben werden.

 parameter: int anzahl (Personen)

 returns: struPerson pStart

 COMMAND_NAME: C

 @David Gataric
*/
struPerson *create(const int anzahl) {
	struPerson *pStart = NULL;
	struPerson *pLast = NULL;

	for (int i = 0; i < anzahl; i++)
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

/**
 createList:

 Methode, welche eine Liste mit Personen (struPersonen)
 erstellt. Die Anzahl Personen werden angegeben.

  returns: struPerson pStart

  @David Gataric
*/
struPerson* createList()
{
	int anzahlPersonen = 0;
	printf("Personenkartei/create> ");
	scanf_s("%i", &anzahlPersonen);
	struPerson *pStart = create(anzahlPersonen);
	return pStart;
}

/**
 main:

 Ist die Main-Methode des Programms.
 Steuert den ganzen Programmlauf.

 @David Gataric und Vasily Kozlov
*/
void main() {
	srand((unsigned)time(NULL));

	struPerson *pStart = NULL;
	bool program = true;
	char command;

	while (program)
	{
		do {
			printf("Personenkartei> ");
			do { command = getchar(); } while (command == '\n');

			command = toupper(command);
			switch (command) {
			case 'C': pStart = createList(); break;
			case 'L': outputList(pStart); break;
			case 'D': break;
			case 'Q': program = false; break;

			default: printf("Unbekannter Command!\n"); break;
			}
		} while (command != 'Q');
		printf("\n");
	}

	}