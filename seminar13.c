#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Camion Camion;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
typedef struct NodCoada NodCoada;

struct Camion {
	int serie;
	char* marca;
	float greutate;
};

struct NodPrincipal {
	Camion info;
	NodSecundar* vecini;
	NodPrincipal* next;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

struct NodCoada {
	int serie;
	NodCoada* next;
};

void afisareCamion(Camion c) {
	printf("\n%d. Camionul %s are greutatea %.2f", c.serie, c.marca, c.greutate);
}

//inserare in lista principala la inceput 
NodPrincipal* inserarePrincipala(NodPrincipal* graf, Camion c) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = c;
	nou->next = graf;
	nou->vecini = NULL;
	return nou;
}
//functie de cautare NodPrincipal dupa serie camion
NodPrincipal* cautaNodDupaSerie(NodPrincipal* graf, int serie) {
	while (graf && graf->info.serie != serie) {
		graf = graf->next;
	}
	return graf;
}

//inserare la sfarsit pentru lista secundara
void inserareSecundara(NodSecundar** cap, NodPrincipal* nod) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->nod = nod;
	nou->next = NULL;
	if (*cap) {
		NodSecundar* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

//inserare muchie in lista
void inserareMuchie(NodPrincipal* graf, int serieStart, int serieStop) {
	NodPrincipal* nodStart = cautaNodDupaSerie(graf, serieStart);
	NodPrincipal* nodStop = cautaNodDupaSerie(graf, serieStop);
	inserareSecundara(&(nodStart->vecini), nodStop);
	inserareSecundara(&(nodStop->vecini), nodStart);
}

Camion creareCamion(int serie, const char* marca, float greutate) {
	Camion c;
	c.serie = serie;
	c.greutate = greutate;
	c.marca = (char*)malloc(strlen(marca) + 1);
	strcpy_s(c.marca, strlen(marca) + 1, marca);
	return c;
}
void afisareListaSecundara(NodSecundar* cap) {
	while (cap) {
		printf("%d\n", cap->nod->info.serie);
		cap = cap->next;
	}
}
void afisareListaPrincipala(NodPrincipal* cap) {
	while (cap) {
		afisareCamion(cap->info);
		afisareListaSecundara(cap->vecini);
		cap = cap->next;
	}
}

#pragma region fifo lifo

void pushCoada(NodCoada** coada, int serie) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada) * 1);
	nou->serie = serie;
	nou->next = NULL;
	if (*coada) {
		NodCoada* temp = *coada;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		*coada = nou;
	}
}

void pushStiva(NodCoada** stiva, int serie) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada) * 1);
	nou->serie = serie;
	nou->next = *stiva;
	*stiva = nou;
}

int popCoada(NodCoada** coada) {
	if (*coada) {
		int rez = (*coada)->serie;
		NodCoada* aux = *coada;
		*coada = (*coada)->next;
		free(aux);
		return rez;
	}
	return -1;
}

int popStiva(NodCoada** stiva) {
	return popCoada(stiva);
}

#pragma endregion

int calculNoduriGraf(NodPrincipal* graf) {
	int nr = 0;
	while (graf) {
		nr++;
		graf = graf->next;
	}
	return nr;
}
void afisarePrinParcurgereLatime(NodPrincipal* graf, int serieStart) {
	if (graf) {
		NodCoada* coada = NULL;
		int nrNoduri = calculNoduriGraf(graf);
		char* vizitat = (char*)malloc(sizeof(char) * nrNoduri);
		for (int i = 0; i < nrNoduri; ++i) {
			vizitat[i] = 0;
		}
		vizitat[serieStart] = 1;
		pushCoada(&coada, serieStart);
		while (coada) {
			int serieCurenta = popCoada(&coada);
			NodPrincipal* nodCurent = cautaNodDupaSerie(graf, serieCurenta);
			afisareCamion(nodCurent->info);
			NodSecundar* vecini = nodCurent->vecini;
			while (vecini) {
				if (vizitat[vecini->nod->info.serie] == 0) {
					vizitat[vecini->nod->info.serie] = 1;
					pushCoada(&coada, vecini->nod->info.serie);
				}
				vecini = vecini->next;
			}
		}
		if (vizitat) {
			free(vizitat);
		}
	}
}

void afisarePrinParcurgereAdancime(NodPrincipal* graf, int serieStart) {
	if (graf) {
		NodCoada* stiva = NULL;
		int nrNoduri = calculNoduriGraf(graf);
		char* vizitat = (char*)malloc(sizeof(char) * nrNoduri);
		for (int i = 0; i < nrNoduri; ++i) {
			vizitat[i] = 0;
		}
		vizitat[serieStart] = 1;
		pushStiva(&stiva, serieStart);
		while (stiva) {
			int serieCurenta = popStiva(&stiva);
			NodPrincipal* nodCurent = cautaNodDupaSerie(graf, serieCurenta);
			afisareCamion(nodCurent->info);
			NodSecundar* vecini = nodCurent->vecini;
			while (vecini) {
				if (vizitat[vecini->nod->info.serie] == 0) {
					vizitat[vecini->nod->info.serie] = 1;
					pushStiva(&stiva, vecini->nod->info.serie);
				}
				vecini = vecini->next;
			}
		}
		if (vizitat) {
			free(vizitat);
		}
	}
}

void stergereListaVecini(NodSecundar** vecini) {
	while (*vecini) {
		NodSecundar* aux = *vecini;
		*vecini = aux->next;
		free(aux);
	}
}

void stergereGraf(NodPrincipal** graf) {
	while (*graf) {
		NodPrincipal* p = *graf;
		free(p->info.marca);
		stergereListaVecini(&(p->vecini));
		(*graf) = p->next;
		free(p);
	}
}

void main() {
	NodPrincipal* graf = NULL;
	//inseram 5 noduri cu id-urile 0 1 2 3 4
	graf = inserarePrincipala(graf, creareCamion(4, "Scania", 20));
	graf = inserarePrincipala(graf, creareCamion(3, "Volvo", 30));
	graf = inserarePrincipala(graf, creareCamion(2, "Renault", 25));
	graf = inserarePrincipala(graf, creareCamion(1, "MAN", 15));
	graf = inserarePrincipala(graf, creareCamion(0, "Mercedes", 40));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 0, 3);
	inserareMuchie(graf, 3, 4);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 1, 3);

	afisarePrinParcurgereLatime(graf, 4);
	printf("\n\n");
	afisarePrinParcurgereAdancime(graf, 4);

	stergereGraf(&graf);
}
