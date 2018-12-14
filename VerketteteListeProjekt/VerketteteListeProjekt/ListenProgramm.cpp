#include "stdio.h"
#include "stdlib.h"
#include "time.h"

/**
 Person:

 Personen-Objekt welches für die Liste
 wichtig ist. Personen werden erstellt und
 in die Liste eingetragen.
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

 COMMAND_NAME: SHOW
*/
void outputList(struPerson* pListStart) {
	if (pListStart != NULL) {
		for (struPerson* pOut = pListStart; pOut != NULL; pOut = pOut->pNext) {
			printf("Person: %s, %s, %i\n", pOut->vorname, pOut->nachname, pOut->jahrgang);
		}
	}
	else {
		printf("Die Liste ist leer.!\nErstellen Sie neue Personen mit dem Command: 'CREATE'");
	}

	system("pause");

}

/**
 randomiseYear:
 	
 Diese Methode gibt eine zufallsgenerierte
 Zahl zwischen 1900 und 2018 zurück.
 
 returns: int randomInt
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

 COMMAND_NAME: CREATE
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

bool commandComparator(char *input, char check[10])
{
	int i = 0;
	for (input; *input != '\0'; input++)
	{

		if (*input != check[i])
		{
			return false;
		}
	}
	return true;
}

/**
 main:

 Ist die Main-Methode des Programms.
 Steuert den ganzen Programmlauf.
*/
void main() {
	srand((unsigned)time(NULL));
	// Versuch mit Commands
	/*
	bool program = true;
	char command[10];
	char *pCommand = &command[10];

	char createCommandCheck[10] = "CREATE";

	while(program) 
	{
		
		printf("Personenkartei> ");
		scanf_s("%c", &command);

		if (commandComparator(pCommand, createCommandCheck)) {
			
		}

	}
	*/
	int anzahlPersonen = 0;
	printf("Personenkartei/create> ");
	scanf_s("%i", &anzahlPersonen);
	struPerson *pStart = create(anzahlPersonen);
	outputList(pStart);

}