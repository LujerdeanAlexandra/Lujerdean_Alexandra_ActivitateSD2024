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

void afisareCinema(Cinema c) {
	printf("Cinematograful cu id-ul %d are in derulare %d filme:", c.id, c.nrFilme);
	for (int i = 0; i < c.nrFilme; i++) {
		printf("%s ", c.listaFilme[i]);
	}
	printf("\n");
}

void afisareArborePreordine(Nod* rad) {
	if (rad) {
		afisareCinema(rad->info);
		afisareArborePreordine(rad->st);
		afisareArborePreordine(rad->dr);
	}
}

void afisareArboreInordine(Nod* rad) {
	if (rad) {
		afisareArboreInordine(rad->st);
		afisareCinema(rad->info);
		afisareArboreInordine(rad->dr);
	}
}

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

Nod* rotireDreapta(Nod* radacina) {
	if (radacina) {
		Nod* aux = radacina->st;
		radacina->st = aux->dr;
		aux->dr = radacina;
		return aux;
	}
	else {
		return radacina;
	}
}

Nod* rotireStanga(Nod* radacina) {
	if (radacina) {
		Nod* aux = radacina->dr;
		radacina->dr = aux->st;
		aux->st = radacina;
		return aux;
	}
	else {
		return radacina;
	}
}

int calculInaltime(Nod* radacina) {
	if (radacina) {
		int inaltimeStanga = calculInaltime(radacina->st);
		int inaltimeDreapta = calculInaltime(radacina->dr);

		if (inaltimeStanga > inaltimeDreapta) {
			return 1 + inaltimeStanga;
		}
		else {
			return 1 + inaltimeDreapta;
		}
	}
	else {
		return 0;
	}
}

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

void inserareInArbore(Nod** radacina, Cinema c) {
	if (*radacina) {
		if ((*radacina)->info.id > c.id) {
			inserareInArbore(&((*radacina)->st), c);
		}
		else {
			inserareInArbore(&((*radacina)->dr), c);
		}
		int grad = calculGradEchilibru(*(radacina));
		if (grad == 2) {
			//dezechilibru in partea stanga
			int gradCopil = calculGradEchilibru((*radacina)->st);
			if (gradCopil ==-1) {
				(*radacina)->st = rotireStanga((*radacina)->st);
			}
			else {
				*radacina = rotireDreapta(*radacina);
			}
		}else if(grad==-2){
			//dezechilibru in partea dreapta
			int gradCopil = calculGradEchilibru((*radacina)->dr);
			if (gradCopil == -1) {
				(*radacina)->dr = rotireDreapta((*radacina)->dr);
			}
			else {
				*radacina = rotireStanga(*radacina);
			}
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

int calculGradEchilibru(Nod* radacina) {
	if (radacina) {
		int inaltimeSubarboreStanga = calculInaltime(radacina->st);
		int inaltimeSubarboreDreapta = calculInaltime(radacina->dr);
		return inaltimeSubarboreStanga - inaltimeSubarboreDreapta;
	}
}

void stergereArbore(Nod** radacina) {
	if (*radacina) {
		stergereArbore(&((*radacina)->st));
		stergereArbore(&((*radacina)->dr));
		if ((*radacina)->info.listaFilme) {
			for (int i = 0; i < (*radacina)->info.nrFilme; i++) {
				free((*radacina)->info.listaFilme[i]);
			}
			free((*radacina)->info.listaFilme);
		}
		free(*radacina);
		*radacina = NULL;
	}
}

Cinema calculCinemaCuNrMax(Nod* radacina) {
	if (radacina) {
		Cinema cinemaStanga = calculCinemaCuNrMax(radacina->st);
		Cinema cinemaDreapta = calculCinemaCuNrMax(radacina->dr);
		Cinema cinemaMax;
		if (radacina->info.nrFilme>cinemaStanga.nrFilme && 
			radacina->info.nrFilme>cinemaDreapta.nrFilme) {
			cinemaMax = radacina->info;
		}
		else if (cinemaStanga.nrFilme > cinemaDreapta.nrFilme) {
			cinemaMax = cinemaStanga;
		}
		else
		{
			cinemaMax = cinemaDreapta;
		}
		return cinemaMax;
	}
	else {
		Cinema c;
		c.id = -1;
		c.listaFilme = NULL;
		c.nrFilme = 0;
	}
}

void main()
{
	Nod* arbore = NULL;
	arbore = citireFisier("cinema.txt");
	afisareArborePreordine(arbore);

	printf("\n\nNumar filme: %d", calculNrFilmeRedate(arbore));

	Cinema cinema = calculCinemaCuNrMax(arbore);
	afisareCinema(cinema);

	stergereArbore(&arbore);
	afisareArborePreordine(arbore);
}