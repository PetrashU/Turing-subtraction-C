#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int dlugosc;		
int flaga;
int stan;
int poz;

void wypisz(char *tasma)
{
	int i;
	for (i = 0; i < poz; i++)
		printf("%c ", tasma[i]);
	printf(" q%d ", stan);
	for (i = poz; i < dlugosc; i++)
		printf("%c ", tasma[i]);
	printf("\n");
}

void przejscie(char* tasma) {

	if (poz == (dlugosc)) {
		dlugosc += 1;
		tasma = (char*)realloc(tasma, dlugosc * sizeof(char));
		strcat(tasma, "B");
	}
	if (poz == -1) {
		dlugosc += 1;
		tasma = (char*)realloc(tasma, dlugosc * sizeof(char));
		char tmp[dlugosc];
		tmp[0] = 'B';
		strcat(tmp, tasma);
		strcpy (tasma, tmp);
		poz = 0;
	}


        if ((poz == -1) || (tasma[poz] == 0)) {
                printf("BŁĄD: Wyszłem za granicy taśmy. Proszę sprawdzić kod\n");
                exit(1);
	} 
	switch (stan)
	{
	case 0:
		if (tasma[poz] == '0') {
			stan = 1;
			tasma[poz] = 'B';
			poz += 1;
		}
		else if (tasma[poz] == '1') {
			stan = 5;
			tasma[poz] = 'B';
			poz += 1;
		}
		else if (tasma[poz] == 'B') {
			flaga = -1;
	}
		break;
	case 1:
		if (tasma[poz] == '0') {
			stan = 1;
			tasma[poz] = '0';
			poz += 1;
		}
		else if (tasma[poz] == '1') {
			stan = 2;
			tasma[poz] = '1';
			poz += 1;
		}
		else if (tasma[poz] == 'B') {
			flaga = -1;
		}
		break;
	case 2:
		if (tasma[poz] == '0') {
			stan = 3;
			tasma[poz] = '1';
			poz += -1;
		}
		else if (tasma[poz] == '1') {
			stan = 2;
			tasma[poz] = '1';
			poz += 1;
		}
		else if (tasma[poz] == 'B') {
			stan = 4;
			tasma[poz] = 'B';
			poz += -1;
		}
		break;
	case 3:
		if (tasma[poz] == '0') {
			stan = 3;
			tasma[poz] = '0';
			poz += -1;
		}
		else if (tasma[poz] == '1') {
			stan = 3;
			tasma[poz] = '1';
			poz += -1;
		}
		else if (tasma[poz] == 'B') {
			stan = 0;
			tasma[poz] = 'B';
			poz += 1;
		}
		break;
	case 4:
		if (tasma[poz] == '0') {
			stan = 4;
			tasma[poz] = '0';
			poz += -1;
		}
		else if (tasma[poz] == '1') {
			stan = 4;
			tasma[poz] = 'B';
			poz += -1;
		}
		else if (tasma[poz] == 'B') {
			stan = 6;
			tasma[poz] = '0';
			poz += 1;
		}
		break;
	case 5:
		if (tasma[poz] == '0') {
			stan = 5;
			tasma[poz] = 'B';
			poz += 1;
		}
		else if (tasma[poz] == '1') {
			stan = 5;
			tasma[poz] = 'B';
			poz += 1;
		}
		else if (tasma[poz] == 'B') {
			stan = 6;
			tasma[poz] = 'B';
			poz += 1;
		}
		break;
	case 6:
			flaga = -1;
			break;
	}
}

void generuj_tasme(int m, int n, char* tasma) {
	int i;
	for (i = 0; i < m; i++) {
		strcat(tasma, "0");
	}
	strcat(tasma,"1");
	for (i = 0; i < n; i++) {
		strcat(tasma,"0");
	}
	strcat(tasma, "1");
}

void opis_maszyny() 
{
	printf("\t\tEmulator maszyny Turinga obliczającej roznicę wlasciwą\n");
	printf("\tProgram działa w trybie wsadowym, przyjmuje argumenty m > 0 i n > 0");
	printf("\n");
	printf("Dla m >= n\tm - n = m - n\n");
	printf("Dla m < n\tm - n = 0\n");
	
	printf("\tPostać maszyny Turinga:\n");
	printf("M = ({q0, q1, q2, q3, q4, a5, a6}, {0, 1}, {0, 1, B}, d, q0, B, 0)\n");
	printf("dla\n");
	printf("\t    0\t\t   1\t\t    B\n");
	printf("\n");
	printf("q0	(q1,B,P)	(q5,B,P)	    -\n");
	printf("q1	(q1,0,P)	(q2,1,P)            -\n");
	printf("q2	(q3,1,L)	(q2,1,P)	(q4,B,L)\n");
	printf("q3	(q3,0,L)	(q3,1,L)	(q0,B,P)\n");
	printf("q4	(q4,0,L)	(q4,B,L)	(q6,0,P)\n");
	printf("q5	(q5,B,P)	(q5,B,P)	(q6,B,P)\n");
	printf("q6	    -		    -		    -	\n");
}

int main(int argc, char *argv[]) 
{
	if (argc != 3)
	{
		printf("\tBŁĄD: Niepoprawna liczba argumentów wywołania\n");
		opis_maszyny();	
		return 1;
	}
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	if ((m < 0) || (n < 0))
	{
		printf("\tBŁĄD: Niepoprawny typ danych\n");
		opis_maszyny();
		return 2;
	}

	opis_maszyny();
	dlugosc = m + n + 2 ;
	char *tasma;
	tasma = (char*)malloc((dlugosc) * sizeof(char));
	generuj_tasme(m, n, tasma);
	printf("Taśma wejsciowa: %s\n", tasma);
	poz = 0;
	stan = 0;
	flaga = 0;
	wypisz(tasma);
	while (flaga != -1) {
		przejscie(tasma);
		if (flaga != -1)
			wypisz(tasma);
	}
	int i, r = 0;
	for (i = 0; i < dlugosc; i++) {
		if (tasma[i] == '0')
			r++;
	}
	printf ("Różnica właściwa wynosi: %d\n", r);
	free(tasma);
	return 0;
}
