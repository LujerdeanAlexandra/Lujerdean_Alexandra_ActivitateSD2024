#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Quiz Quiz;
typedef struct Heap Heap;

struct Quiz {
	char* materie;
	int nrGileGresite;
};

struct Heap {
	Quiz* vector;
	int dimensiune;
	int dimensiuneTotala;
};

Heap initializareHeap(int nr) {
	Heap heap;
	heap.dimensiune = 0;
	heap.dimensiuneTotala = nr;
	heap.vector = malloc(sizeof(Quiz) * nr);
	return heap;
}

Quiz initializareQuiz(const char* materie, int nrGileGresite) {
	Quiz quiz;
	quiz.materie = malloc(sizeof(char) * (strlen(materie) + 1));
	strcpy(quiz.materie, materie);
	quiz.nrGileGresite = nrGileGresite;
	return quiz;
}

Heap adaugareQuizInHeap(Quiz quiz,Heap heap) {
	if (heap.dimensiune < heap.dimensiuneTotala) {
		heap.vector[heap.dimensiune] = quiz;
		heap.dimensiune++;
		//TO DO filtrare
	}
	return heap;
}

void afisareQuiz(Quiz quiz) {
	printf("\nMaterie: %s. Nr grile gresite: %d", quiz.materie, quiz.nrGileGresite);
	printf("\n");
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.dimensiune; i++) {
		afisareQuiz(h.vector[i]);
	}
}

void filtrareHeap(Heap heap,int pozRadacina) {
	int nodStanga = pozRadacina * 2 + 1;
	int nodDreapta = pozRadacina * 2 + 2;
	int pozMin = pozRadacina;
	if (nodStanga < heap.dimensiune && heap.vector[nodStanga].nrGileGresite<heap.vector[pozMin].nrGileGresite) {
		pozMin = nodStanga;
	}
	if (nodDreapta < heap.dimensiune && heap.vector[nodDreapta].nrGileGresite < heap.vector[pozMin].nrGileGresite) {
		pozMin = nodDreapta;
	}
	if (pozMin != pozRadacina) {
		Quiz aux;
		aux = heap.vector[pozRadacina];
		heap.vector[pozRadacina] = heap.vector[pozMin];
		heap.vector[pozMin] = aux;
		if (pozMin * 2 + 1 < heap.dimensiune - 1) {
			filtrareHeap(heap, pozMin);
		}
	}
}

Quiz extrageMinim(Heap* heap) {
	if (heap->dimensiune > 0) {
		Quiz aux;
		aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->dimensiune- 1];
		heap->vector[heap->dimensiune - 1] = aux;
		heap->dimensiune--;
		for (int i = (heap->dimensiune) / 2 - 1; i >= 0; i--) {
			filtrareHeap(*heap, i);
		}
		return aux;
	}
	else {
		return initializareQuiz("N/A", -1);
	}
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->dimensiuneTotala; i++) {
		free(heap->vector[i].materie);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->dimensiune = 0;
	heap->dimensiuneTotala = 0;
}

void main() {
	Heap heap;
	heap = initializareHeap(6);
	heap.vector[0] = initializareQuiz("Structuri de date", 3);
	heap.vector[1] = initializareQuiz("Progaramare multiparadigma", 7);
	heap.vector[2] = initializareQuiz("Baze de date", 5);
	heap.vector[3] = initializareQuiz("Atp", 2);
	heap.vector[4] = initializareQuiz("Poo", 9);
	heap.vector[5] = initializareQuiz("Analiza", 4);

	heap.dimensiune = 6;
	afisareHeap(heap);

	for (int i = (heap.dimensiune) / 2 - 1; i >= 0; i--) {
		afisareHeap(heap, i);
	}

	printf("\n\n");
	afisareQuiz(extrageMinim(&heap));
	afisareQuiz(extrageMinim(&heap));
	printf("\n\n");
	afisareHeap(heap);

	printf("\n\n");
	afisareQuiz(extrageMinim(&heap));
}