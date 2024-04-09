#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Cafenea Cafenea;//typedef inlocuieste struct cafenea cu cafenea
typedef struct Nod Nod;

struct Cafenea {
	char* nume;
	int nrLocuri;
	float suprafata;
};

struct Nod {
	Cafenea info;
	Nod* next;
};

Cafenea initializare(const char* nume, int nrLocuri, float suprafata) {
	Cafenea c;
	c.nume = malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(c.nume, nume);
	c.nrLocuri = nrLocuri;
	c.suprafata = suprafata;
	return c;
}

void afisare(Cafenea c) {
	printf("Denumire: %s. Nr locuri: %d. Suprafata: %.2f", c.nume, c.nrLocuri, c.suprafata);
	printf("\n");
}

void afisareCafenele(Nod* lista) {
	while (lista != NULL) {
		afisare(lista->info);
		lista = lista->next;
	}
}

Nod* inserareInceput(Cafenea c, Nod* cap) {
	Nod* nou = malloc(sizeof(Nod));
	nou->next = cap;
	nou->info = c;
	nou->info = initializare(c.nume, c.nrLocuri, c.suprafata);
	return nou;
}

//numele cafenelei cu densitatea cea mai mica
char* numeCafeneaCuDensitateMinima(Nod* lista) {
	if (lista != NULL) {
		if (lista->info.suprafata != 0) {
			float minim = (lista->info.nrLocuri) / (lista->info.suprafata);
			Nod* adresa = lista;
			lista = lista->next;
			while (lista != NULL) {
				if (lista->info.nrLocuri / lista->info.suprafata < minim) {
					minim = lista->info.nrLocuri / lista->info.suprafata;
					adresa = lista;
				}
				lista = lista->next;
			}
			char* nume = malloc(sizeof(char) * (strlen(adresa->info.nume)+1));
			strcpy(nume, adresa->info.nume);
			return nume;
		}
	}
}

void stergereListaNoduri(Nod** nod) {
	while (*nod != NULL) {
		Nod* aux;
		aux = *nod;
		*nod = (*nod)->next;
		free(aux->info.nume);
		free(aux);
	}
	*nod = NULL;
}

void inserareLaSfarsit(Nod** lista,Cafenea c)
{
	if ((*lista) == NULL) {
		(*lista) = inserareInceput(c,*lista);
	}
	else {
		Nod* curent = (*lista);
		while (curent->next!=NULL) {
			curent = curent->next;
		}
		Nod* n = malloc(sizeof(Nod));
		n->info = initializare(c.nume, c.nrLocuri, c.suprafata);
		n->next = NULL;
		curent->next = n;
	}
}
void main() {
	Nod* cap = NULL;
	Cafenea cafenea=initializare("Tucano", 12, 20);
	Cafenea cafenea2 = initializare("Teds", 17, 17.3);
	Cafenea cafenea3 = initializare("Urban", 19, 33);
	cap = inserareInceput(cafenea, cap);
	cap = inserareInceput(cafenea2, cap);
	cap = inserareInceput(cafenea3, cap);
	afisareCafenele(cap);
	char* numeMinim = numeCafeneaCuDensitateMinima(cap);
	printf("\nCafeneaua cu densitate minima: %s\n",numeMinim);

	Cafenea cafenea4 = initializare("5ToGo", 5, 10);
	inserareLaSfarsit(&cap, cafenea4);
	afisareCafenele(cap);

	stergereListaNoduri(&cap);
	afisareCafenele(cap);

	free(cafenea.nume);
	cafenea.nume = NULL;

	free(cafenea2.nume);
	cafenea2.nume = NULL;

	free(cafenea3.nume);
	cafenea3.nume = NULL;

	free(numeMinim);
}