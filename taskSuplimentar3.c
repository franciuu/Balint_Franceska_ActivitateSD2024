#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
struct Fabrica
{
	char* denumire;
	int nrAngajati;
	int* salarii;
	int anInfiintare;
};
struct Fabrica initializareFabrica(const char* denumire, int nrAngajati, int* salarii, int anInfiintare)
{
	struct Fabrica fabrica;
	fabrica.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(fabrica.denumire, denumire);
	fabrica.nrAngajati = nrAngajati;
	fabrica.salarii = malloc(sizeof(int) * nrAngajati);
	for (int i = 0; i < nrAngajati; ++i)
	{
		fabrica.salarii[i] = salarii[i];
	}
	fabrica.anInfiintare = anInfiintare;
	return fabrica;
}
void afisareFabrica(struct Fabrica f)
{
	printf("\nDenumire: %s, Nr angajati: %i", f.denumire, f.nrAngajati);
	if (f.salarii > 0)
	{
		printf(" Salariile angajatilor: ");
		for (int i = 0; i < f.nrAngajati; ++i)
			printf("%i, ", f.salarii[i]);
	}
	printf("Anul infiintarii: %i\n", f.anInfiintare);
}
void afisareVectorFabrici(struct Fabrica* fabrici, int dim)
{
	for (int i = 0; i < dim; ++i)
		afisareFabrica(fabrici[i]);
}
void inserareFabrica(struct Fabrica** vector, int* dim, struct Fabrica f)
{
	struct Fabrica* copie;
	copie = malloc(sizeof(struct Fabrica) * (++(*dim)));
	for (int i = 0; i < (*dim) - 1; ++i)
		copie[i] = (*vector)[i];
	copie[(*dim) - 1] = f;
	if ((*vector) != NULL)
		free((*vector));
	(*vector) = copie;
}
struct Fabrica* citireFisier(const char* numeFisier, int* nrFabrici)
{
	if (numeFisier != NULL && numeFisier > 0)
	{
		FILE* f = fopen(numeFisier, "r");
		if (f != NULL)
		{
			(*nrFabrici) = 0;
			struct Fabrica* fabrici = NULL;
			char buffer[100];
			char delim[] = ",\n";
			while (fgets(buffer, 100, f) != NULL)
			{
				struct Fabrica fabrica;
				char* token;
				token = strtok(buffer, delim);
				fabrica.denumire = malloc(sizeof(char) * (strlen(buffer) + 1));
				strcpy(fabrica.denumire, buffer);
				token = strtok(NULL, delim);
				fabrica.nrAngajati = atoi(token);
				fabrica.salarii = malloc(sizeof(int) * fabrica.nrAngajati);
				for (int i = 0; i < fabrica.nrAngajati; ++i)
				{
					token = strtok(NULL, delim);
					fabrica.salarii[i] = atoi(token);
				}
				token = strtok(NULL, delim);
				fabrica.anInfiintare = atoi(token);
				inserareFabrica(&fabrici, nrFabrici, fabrica);
			}
			fclose(f);
			return fabrici;
		}
	}
}
void salvareFisier(const char* numeFisier, struct Fabrica fabrica)
{
	if (numeFisier != NULL && numeFisier > 0)
	{
		FILE* f = fopen(numeFisier, "w");
		if (f != NULL)
		{
			fprintf(f, "%s\n", fabrica.denumire);
			fprintf(f, "%i\n", fabrica.nrAngajati);
			for (int i = 0; i < fabrica.nrAngajati; ++i)
			{
				fprintf(f, "%i, ", fabrica.salarii[i]);
			}
			fprintf(f, "\n%i\n", fabrica.anInfiintare);
			fclose(f);
		}
	}
}
void salvareVectorFisier(const char* numeFisier, struct Fabrica* fabrici, int dim)
{
	if (numeFisier != NULL && numeFisier > 0)
	{
		FILE* f = fopen(numeFisier, "w");
		if (f != NULL)
		{
			for (int i = 0; i < dim; ++i)
			{
				fprintf(f, "%s ", fabrici[i].denumire);
				fprintf(f, "%i ", fabrici[i].nrAngajati);
				for (int j = 0; j < fabrici[i].nrAngajati; ++j)
				{
					fprintf(f, "%i, ", fabrici[i].salarii[j]);
				}
				fprintf(f, "%i\n", fabrici[i].anInfiintare);
			}
			fclose(f);
		}
	}
}

void main()
{
	struct Fabrica* fabrici = NULL;
	int dim = 0;
	fabrici = citireFisier("fabrici.txt", &dim);
	afisareVectorFabrici(fabrici, dim);
	int* vector2 = malloc(sizeof(int) * 4);
	for (int i = 0; i < 4; ++i)
	{
		vector2[i] = (i+2)*100 + (500-i*22);
	}
	struct Fabrica fabrica1 = initializareFabrica("Napolact", 4, vector2, 2001);
	salvareFisier("fabrica.txt", fabrica1);
	
	salvareVectorFisier("fabriciSalvate.txt", fabrici, dim);
}
