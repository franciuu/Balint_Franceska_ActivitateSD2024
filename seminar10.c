//arbori binari de cautare
//SRD, RSD, SDR
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Cinema Cinema;
typedef struct Nod Nod;
struct Cinema
{
	int id;
	int nrFilme;
	char** filme;
};
struct Nod
{
	Cinema info;
	Nod* st;
	Nod* dr;
};

void inserareInArbore(Nod** radacina, Cinema c)
{
	if (*radacina)
	{
		if ((*radacina)->info.id > c.id)
		{
			inserareInArbore(&((*radacina)->st), c);
		}
		else
		{
			inserareInArbore(&((*radacina)->dr), c);
		}
	}
	else
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod) * 1);
		nod->dr = NULL;
		nod->st = NULL;
		nod->info = c;
		*radacina = nod;
	}
}

void afisareCinema(Cinema cinema)
{
	printf("Cinematograful cu id-ul %d are in derulare %d filme:", cinema.id, cinema.nrFilme);
	for (int i = 0; i < cinema.nrFilme; ++i)
	{
		printf("%s, ", cinema.filme[i]);
	}
	printf("\n");
}
void afisareArborePreordine(Nod* rad) //RSD
{
	if (rad)
	{
		afisareCinema(rad->info);
		afisareArborePreordine(rad->st);
		afisareArborePreordine(rad->dr);
	}
}

void afisareArboreInordine(Nod* rad) //SRD
{
	if (rad)
	{
		afisareArboreInordine(rad->st);
		afisareCinema(rad->info);
		afisareArboreInordine(rad->dr);
	}
}

int calculNrFilmeRedate(Nod* rad)
{
	if (rad)
	{
		int suma = rad->info.nrFilme;
		suma += calculNrFilmeRedate(rad->st);
		suma += calculNrFilmeRedate(rad->dr);
		return suma;
	}
	else
	{
		return 0;
	}
}

Cinema citireCinema(FILE* f)
{
	Cinema cinema;
	fscanf(f, "%d", &cinema.id);
	fscanf(f, "%d", &cinema.nrFilme);
	if (cinema.nrFilme != 0)
	{
		cinema.filme = (char**)malloc(sizeof(char*) * cinema.nrFilme);
		for (int i = 0; i < cinema.nrFilme; ++i)
		{
			char buffer[100];
			fscanf(f, "%s", &buffer);
			cinema.filme[i] = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy(cinema.filme[i], buffer);
		}
	}
	else
	{
		cinema.filme = NULL;
	}
	return cinema;
}

Nod* citireFisier(const char* numeFisier)
{
	Nod* arbore = NULL;
	if (numeFisier != NULL && strlen(numeFisier) > 0)
	{
		FILE* f = fopen(numeFisier, "r");
		if (f)
		{
			int dim = 0;
			fscanf(f, "%d", &dim);
			for (int i = 0; i < dim; ++i)
			{
				Cinema cinema = citireCinema(f);
				inserareInArbore(&arbore, cinema);
			}
		}
	}
	return arbore;
}

void main()
{
	Nod* arbore = NULL;
	arbore = citireFisier("cinema.txt");
	afisareArboreInordine(arbore);

	printf("\n\nNumar filme: %d", calculNrFilmeRedate(arbore));
}
