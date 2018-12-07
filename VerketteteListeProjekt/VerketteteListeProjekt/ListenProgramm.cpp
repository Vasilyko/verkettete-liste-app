#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void main() {

	typedef struct Person 
	{
		char vorname[15];
		char nachname[15];
		int jahrgang;
		struct Person* pNext;
	} struPerson;



}