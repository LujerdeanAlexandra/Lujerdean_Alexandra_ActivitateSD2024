#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

//inOrdine-SRD
//preOrdine-RSD
//postOrdine-SDR

typedef struct Cinema Cinema;
typedef struct Nod Nod;

struct Cinema {
	int id;
	int nrFilme;
	char** listaFilme;
};

struct Nod {
	Cinema info;
	Nod* st;
	Nod* dr;
};

//p1
void inserareInArbore(Nod** radacina, Cinema c) {
	if (*radacina) {
		if ((*radacina)->info.id > c.id) {
			inserareInArbore(&((*radacina)->st), c);
		}
		else {
			inserareInArbore(&((*radacina)->dr), c);
		}
	}
	else {
		Nod* nod = malloc(sizeof(Nod));
		nod->dr = NULL;
		nod->st = NULL;
		nod->info = c;
		*radacina = nod;
	}
}
//p2 fac fisierul cinema.txt

//p4 o functie care sa ne citeasca doar un cinema din fisierul txt
Cinema citireCinema(FILE* f) {
	Cinema c;
	fscanf(f, "%d", &c.id);
	fscanf(f, "%d", &c.nrFilme);
	if (c.nrFilme != 0) {
		c.listaFilme = malloc(sizeof(char*) * c.nrFilme);
		for (int i = 0; i < c.nrFilme; i++) {
			char buffer[100];
			fscanf(f, "%s", buffer);
			c.listaFilme[i] = malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy(c.listaFilme[i], buffer);
		}
	}
	else {
		c.listaFilme = NULL;
	}
	return c;
}

//p3
Nod* citireFisier(const char* fisier) {
	Nod* radacina = NULL;
	if (fisier != NULL && strlen(fisier) != 0) {
		FILE* f = fopen(fisier, "r");
		if (f != NULL) {
			int dim = 0;
			fscanf(f, "%d", &dim);
			for (int i = 0; i < dim; i++) {
				Cinema cinema;
				cinema = citireCinema(f);
				inserareInArbore(&radacina, cinema);
			}
		}
	}
	return radacina;
}

//p7
void afisareCinema(Cinema c) {
	printf("Cinematograful cu id-ul %d are in derulare %d filme:", c.id, c.nrFilme);
	for (int i = 0; i < c.nrFilme; i++) {
		printf("%s ", c.listaFilme[i]);
	}
	printf("\n");
}
//p6

void afisareArborePreordine(Nod* rad) {
	if (rad) {
		afisareCinema(rad->info);
		afisareArborePreordine(rad->st);
		afisareArborePreordine(rad->dr);
	}
}

//p9
void afisareArboreInordine(Nod* rad) {
	if (rad) {
		afisareArboreInordine(rad->st);
		afisareCinema(rad->info);
		afisareArboreInordine(rad->dr);
	}
}

//p10-cate filme sunt in derulare in toate cinematografele
int calculNrFilmeRedate(Nod* rad) {
	if (rad) {
		int suma = rad->info.nrFilme;
		suma += calculNrFilmeRedate(rad->st);
		suma += calculNrFilmeRedate(rad->dr);
		return suma;
	}
	else {
		return 0;
	}
}


void main()
{
	//identificam un arbore
	Nod* arbore = NULL;
	//p5
	arbore = citireFisier("cinema.txt");
	//p8
	afisareArboreInordine(arbore);

	//p11
	printf("\n\nNumar filme: %d", calculNrFilmeRedate(arbore));
}