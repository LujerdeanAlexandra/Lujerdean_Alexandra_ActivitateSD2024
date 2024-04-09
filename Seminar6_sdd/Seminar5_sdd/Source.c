#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Cafenea Cafenea;//typedef inlocuieste struct cafenea cu cafenea
typedef struct NodLdi NodLdi;
typedef struct ListaDubla ListaDubla;

struct Cafenea {
	char* nume;
	int nrLocuri;
	float suprafata;
};

struct NodLdi {
	NodLdi* anterior;
	Cafenea cafenea;
	NodLdi* urmator;
};

struct ListaDubla {
	NodLdi* cap;
	NodLdi* coada;
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

void afisareListaDublaDeLaInceput(ListaDubla lista) {
	NodLdi* aux = lista.cap;
	while (aux != NULL) {
		afisare(aux->cafenea);
		aux = aux->urmator;
	}
	printf("\n\n");
}

void inserareInceput(ListaDubla* listaDubla,Cafenea cafenea) {
	NodLdi* nou = malloc(sizeof(NodLdi));
	nou->anterior = NULL;
	nou->cafenea = cafenea;
	nou->urmator = listaDubla->cap;
	if (listaDubla->cap != NULL) {
		listaDubla->cap->anterior = nou;
		listaDubla->cap = nou;
	}
	else {
		listaDubla->cap = nou;
		listaDubla->coada = nou;
	}
}

//parcurgem lista de la coada la cap
int nrTotalLocuri(ListaDubla lista) {
	if (lista.cap == NULL) {
		return 0;
	}
	int nrLocuri = 0;
	NodLdi* nod = lista.coada;
	while (nod != NULL) {
		nrLocuri += nod->cafenea.nrLocuri;
		nod = nod->anterior;
	}
	return nrLocuri;
}

//stergere cafenea dupa numele ei
ListaDubla stergereCafeneaDupaNume(ListaDubla listaDubla,const char* nume) {
	if (nume == NULL) {
		return listaDubla;
	}
	NodLdi* nod = listaDubla.cap;
	while (nod && strcmp(nod->cafenea.nume, nume) != 0) {
		nod = nod->urmator;
	}
	if (nod != NULL) {
		if (nod->urmator == NULL && nod->anterior == NULL) {
			listaDubla.cap = NULL;
			listaDubla.coada = NULL;
		}
		else {
			if (nod->anterior == NULL) {
				listaDubla.cap = nod->urmator;
				listaDubla.cap->anterior = NULL;
			}
			else if(nod->urmator==NULL){
				listaDubla.coada = nod->anterior;
				listaDubla.coada->urmator = NULL;
			}
			else {
				nod->anterior->urmator = nod->urmator;
				nod->urmator->anterior = nod->anterior;
			}
		}
		free(nod->cafenea.nume);
		free(nod);
	}
	return listaDubla;
}

ListaDubla stergereLista(ListaDubla listaDubla) {
	while (listaDubla.cap != NULL) {
		free(listaDubla.cap->cafenea.nume);
		NodLdi* temp = listaDubla.cap;
		listaDubla.cap = listaDubla.cap->urmator;
		free(temp);
	}
	listaDubla.cap = NULL;
	listaDubla.coada = NULL;
	return listaDubla;
}

void main() {
	Cafenea cafenea=initializare("Tucano", 12, 20);
	Cafenea cafenea2 = initializare("Teds", 17, 17.3);
	Cafenea cafenea3 = initializare("Urban", 19, 33);
	
	ListaDubla listaDubla;
	listaDubla.cap = NULL;
	listaDubla.coada = NULL;
	inserareInceput(&listaDubla, cafenea2);
	inserareInceput(&listaDubla, cafenea);
	inserareInceput(&listaDubla, cafenea3);
	afisareListaDublaDeLaInceput(listaDubla);

	/*listaDubla = stergereCafeneaDupaNume(listaDubla,"Teds");
	afisareListaDublaDeLaInceput(listaDubla);
	listaDubla = stergereCafeneaDupaNume(listaDubla,"Tucano");
	afisareListaDublaDeLaInceput(listaDubla);
	listaDubla = stergereCafeneaDupaNume(listaDubla,"Starbacks");
	afisareListaDublaDeLaInceput(listaDubla);
	listaDubla = stergereCafeneaDupaNume(listaDubla, "5ToGo");
	afisareListaDublaDeLaInceput(listaDubla);
	listaDubla = stergereCafeneaDupaNume(listaDubla, "Urban");
	afisareListaDublaDeLaInceput(listaDubla);*/

	int nr = nrTotalLocuri(listaDubla);
	printf("\nNr locuri: %d", nr);

	listaDubla = stergereLista(listaDubla);
	printf("\nDupa stergere: ");
	afisareListaDublaDeLaInceput(listaDubla);
}