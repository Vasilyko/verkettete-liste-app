#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "ctype.h"

/*
Person:
Personen-Objekt welches für die Liste
wichtig ist. Personen werden erstellt und
in die Liste eingetragen.

@David Gataric und Vasily Kozlov
*/
typedef struct Person
{
	char vorname[15];
	char nachname[15];
	int jahrgang;
	struct Person* pNext;
	struct Person* pLast;
} struPerson;


/*
outputList:

Liest alle Personen aus der Liste aus und
gibt sie anschliessend in der Konsole aus.

COMMAND_NAME: O

@David Gataric
*/
void outputList(struPerson* pListStart) {
	if (pListStart != NULL) {

		int anzAusgeben = 0;
		int momAusgabe = 0;
		printf("Personenkartei/ausgabe> ");
		scanf_s("%i", &anzAusgeben);

		for (struPerson* pOut = pListStart; pOut != NULL; pOut = pOut->pNext) {
			if (momAusgabe < anzAusgeben)
			{
				printf("Person: %s, %s, %i\n", pOut->vorname, pOut->nachname, pOut->jahrgang);
				momAusgabe++;
			}
		}
	}
	else {
		printf("Die Liste ist leer! Erstellen Sie neue Personen mit dem Command: 'C'\n");
	}

}

/*
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

/*
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

/*
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

/*
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

/*
deleteList:
Der pFirst Pointer wird jedes mal wenn die Schleife ausgeführt wird,
an das nächste Element in der Liste gesetzt, es wird dabei das Element
gelöscht, auf welches zuletzt pFirst gezeigt hat.

parameter: pStart

return: pFirst

COMMAND_Name: D

@David Gataric
*/
struPerson* deleteList(struPerson* pStart)
{
	if (pStart != NULL)
	{
		struPerson* pFirst = pStart;
		while (pFirst != NULL)
		{
			struPerson* pDel = pFirst;
			pFirst = pFirst->pNext;
			pDel->pLast = NULL;
			free(pDel);
		}
		return pFirst;
	}

	return NULL;

}

/*
deletePerson:
Der Benutzer gibt den Buchstaben für den Vor und
Nachnamen ein, von dem Element welches er löschen will.

Param: pStart, Vorname, Nachname

return: pStart

COMMAND_NAME: D

@Vasily Kozlov
*/
struPerson* deletePerson(struPerson* pStart, char firstname, char lastname) {
	struPerson* pPreviousPerson = pStart;

	while (pPreviousPerson->vorname[0] == firstname && pPreviousPerson->nachname[0] == lastname)
	{
		struPerson* pNext = pPreviousPerson->pNext;
		free(pPreviousPerson);

		pPreviousPerson = pNext;
		pStart = pNext;
		return pStart;
	}

	struPerson* pCurrentPerson = pPreviousPerson->pNext;
	while (pCurrentPerson != NULL)
	{
		struPerson* pNext = pCurrentPerson->pNext;
		if (pCurrentPerson->vorname[0] == firstname && pCurrentPerson->nachname[0] == lastname) {
			free(pCurrentPerson);
			pPreviousPerson->pNext = pNext;
		}
		else
		{
			pPreviousPerson = pCurrentPerson;
		}
		pCurrentPerson = pNext;
	}
	return pStart;
}

struPerson* deletePersonCaller(struPerson* pStart)
{
	char vorname;
	char nachname;

	printf("Personenkartei/delete/person>\n");
	getchar();
	printf("Parameter[0] (Vorname): ");
	scanf_s("%c", &vorname);
	getchar();
	printf("Parameter[1] (Nachname): ");
	scanf_s("%c", &nachname);

	return deletePerson(pStart, toupper(vorname), toupper(nachname));


}

/*

*/
void sort(struPerson* pStart)
{
	bool issorting = true;
	while (issorting) {
		//Endlose Schleife vermeiden
		issorting = false;
		//geht so lang bis er nicht alle Werte sortiert hat
		for (struPerson* pSort = pStart; pSort->pNext != NULL; pSort = pSort->pNext)
		{
			if (pSort->nachname != NULL) {
				if (strcmp(pSort->nachname, pSort->pNext->nachname) > 0) {
					char tmpname[5];
					strcpy_s(tmpname, pSort->nachname);
					strcpy_s(pSort->nachname, pSort->pNext->nachname);
					strcpy_s(pSort->pNext->nachname, tmpname);
					char tmpvorname[5];
					strcpy_s(tmpvorname, pSort->vorname);
					strcpy_s(pSort->vorname, pSort->pNext->vorname);
					strcpy_s(pSort->pNext->vorname, tmpvorname);
					int tmpjahr;
					tmpjahr = pSort->jahrgang;
					pSort->jahrgang = pSort->pNext->jahrgang;
					pSort->pNext->jahrgang = tmpjahr;
					issorting = true;
				}
			}
			//Geht so lang bis er alle Werte sortiert hat
			if (pSort->vorname != NULL) {
				//So sortiert er den Nahcnamen zuerst, bevor er den vornamen tauscht
				if (strcmp(pSort->nachname, pSort->pNext->nachname) == 0 && strcmp(pSort->vorname, pSort->pNext->vorname) > 0) {
					char tmpvorname[5];
					strcpy_s(tmpvorname, pSort->vorname);
					strcpy_s(pSort->vorname, pSort->pNext->vorname);
					strcpy_s(pSort->pNext->vorname, tmpvorname);
					char tmpname[5];
					strcpy_s(tmpname, pSort->nachname);
					strcpy_s(pSort->nachname, pSort->pNext->nachname);
					strcpy_s(pSort->pNext->nachname, tmpname);
					int tmpjahr;
					tmpjahr = pSort->jahrgang;
					pSort->jahrgang = pSort->pNext->jahrgang;
					pSort->pNext->jahrgang = tmpjahr;
					issorting = true;
				}
			}
		}
	}
}
/*
information:
Gibt die Information aus, mit allen möglichen Befehlen

@Vasily Kozlov
*/
void information()
{
	printf("C: + Anzahl Elemente eingeben und eine Liste wird erstellt(Cretae)\n");
	printf("O: fuer die Ausgabe der Liste(Output)\n");
	printf("D: wird benoetigt falls man die liste löschen moechte(komplett)\n");
	printf("Q: Um die Applikation zu schliessen\n");
	printf("S: Mit dieser Command-Line Sortieren Sie die Liste Alphabetisch (A-Z)\n");
	printf("P: um ein bestimmtes Element aus der Liste zu loeschen(Vorname und Nachname als Parameter)\n");
}


/*
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
			printf("\nPersonenkartei> ");
			do { command = getchar(); } while (command == '\n');

			command = toupper(command);
			switch (command) {
			case 'C': pStart = createList(); break;
			case 'O': outputList(pStart); break;
			case 'D': deleteList(pStart); break;
			case 'Q': program = false; break;
			case 'S': sort(pStart); break;
			case 'P': deletePersonCaller(pStart); break;
			case 'I': information(); break;



			default: printf("Unbekannter Command!\n"); break;
			}
		} while (command != 'Q');
		printf("\n");



	}

}