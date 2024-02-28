#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
struct Fabrica
{
	char* denumire;
	int nrAngajati;
	float* salarii;
	int anInfiintare;
};
struct Fabrica initializareFabrica(const char* denumire, int nrAngajati, float* salarii, int anInfiintare)
{
	struct Fabrica fabrica;
	fabrica.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(fabrica.denumire, denumire);
	fabrica.nrAngajati = nrAngajati;
	fabrica.salarii = malloc(sizeof(float) * nrAngajati);
	for (int i = 0; i < nrAngajati; ++i)
	{
		fabrica.salarii[i] = salarii[i];
	}
	fabrica.anInfiintare = anInfiintare;
	return fabrica;
}
struct Fabrica citesteFabrica()
{
	struct Fabrica fabrica;
	printf("\nDenumirea fabricii: ");
	char aux[20];
	scanf("%s", aux);
	fabrica.denumire = (char*)malloc(strlen(aux) + 1);
	strcpy(fabrica.denumire, aux);
	printf("\nNumarul de angajati: ");
	scanf("%i", &fabrica.nrAngajati);
	fabrica.salarii = malloc(sizeof(float) * fabrica.nrAngajati);
	printf("\nSalariile angajatilor: ");
	for (int i = 0; i < fabrica.nrAngajati; ++i)
	{
		printf("\ns[%i]=", i);
		scanf("%f", &fabrica.salarii[i]);
	}
	printf("\nAnul infiintarii: ");
	scanf("%i", &fabrica.anInfiintare);
	return fabrica;
}
void afiseazaFabrica(struct Fabrica f)
{
	printf("\nDenumire: ");
	if (f.denumire != NULL)
	{
		printf("%s", f.denumire);
	}
	else
	{
		printf("-");
	}
	printf("\nNr. angajati: %i", f.nrAngajati);
	printf("\nSalariile angajatilor: ");
	if (f.salarii == NULL && f.nrAngajati == 0)
	{
		printf("-");
	}
	else
	{
		for (int i = 0; i < f.nrAngajati; ++i)
		{
			printf("%5.2f ", f.salarii[i]);
		}
	}
	printf("\nAnul infiintarii este: %i", f.anInfiintare);
}
void afiseazaVectorFabrici(struct Fabrica* fabrici, int nrFabrici)
{
	if (fabrici != NULL)
	{
		for (int i = 0; i < nrFabrici; ++i)
		{
			printf("\n");
			afiseazaFabrica(fabrici[i]);
		}
	}
}
void dezalocare(struct Fabrica** fabrici, int* nrFabrici)
{
	if ((*fabrici) != NULL)
	{
		for (int i = 0; i < *nrFabrici; ++i)
		{
			free((*fabrici)[i].denumire);
			free((*fabrici)[i].salarii);
		}
		free(*fabrici);
		*nrFabrici = 0;
		*fabrici = NULL;
	}
}
void copiazaFabriciNoi(struct Fabrica* fabrici, int nrFabrici, int anPrag, struct Fabrica** fabriciNoi, int* nrNou)
{
	if ((*fabriciNoi) != NULL)
	{
		dezalocare(fabriciNoi, nrNou);
	}
	else
	{
		*nrNou = 0;
	}
	for (int i = 0; i < nrFabrici; ++i)
	{
		if (fabrici[i].anInfiintare > anPrag)
		{
			(*nrNou)++;
		}
	}
	*fabriciNoi = (struct Fabrica*)malloc(sizeof(struct Fabrica) * (*nrNou));
	int k = 0;
	for (int i = 0; i < nrFabrici; ++i)
	{
		if (fabrici[i].anInfiintare > anPrag)
		{
			(*fabriciNoi)[k++] = initializareFabrica(fabrici[i].denumire, fabrici[i].nrAngajati, fabrici[i].salarii, fabrici[i].anInfiintare);
		}
	}
}
void copiazaFabriciDeLaAceeasiCompanie(struct Fabrica* fabrici, int nrFabrici, const char* companie, struct Fabrica** fabriciNoi, int* nrNou)
{
	if ((*fabriciNoi) != NULL)
	{
		dezalocare(fabriciNoi, nrNou);
	}
	else
	{
		*nrNou = 0;
	}
	for (int i = 0; i < nrFabrici; ++i)
	{
		if (strcmp(fabrici[i].denumire, companie)==0)
		{
			(*nrNou)++;
		}
	}
	*fabriciNoi = (struct Fabrica*)malloc(sizeof(struct Fabrica) * (*nrNou));
	int k = 0;
	for (int i = 0; i < nrFabrici; ++i)
		if (strcmp(fabrici[i].denumire, companie) == 0)
		{
			(*fabriciNoi)[k++] = initializareFabrica(fabrici[i].denumire, fabrici[i].nrAngajati, fabrici[i].salarii, fabrici[i].anInfiintare);
		}
}
struct Fabrica* concatenareFabrici(struct Fabrica* fabrici1, int nr1, struct Fabrica* fabrici2, int nr2)
{
	struct Fabrica* fabriciConcat;
	int nrConcat = nr1 + nr2;
	fabriciConcat = (struct Fabrica*)malloc(sizeof(struct Fabrica) * nrConcat);
	for (int i = 0; i < nr1; ++i)
	{
		fabriciConcat[i] = initializareFabrica(fabrici1[i].denumire, fabrici1[i].nrAngajati, fabrici1[i].salarii, fabrici1[i].anInfiintare);
	}
	for (int i = nr1; i < nrConcat; ++i)
	{
		fabriciConcat[i] = initializareFabrica(fabrici2[i-nr1].denumire, fabrici2[i-nr1].nrAngajati, fabrici2[i-nr1].salarii, fabrici2[i-nr1].anInfiintare);
	}
	return fabriciConcat;
}	
void dezalocareFabrica(struct Fabrica* f)
{
	if (f->denumire != NULL)
	{
		free(f->denumire);
	}
	if (f->salarii != NULL)
	{
		free(f->salarii);
	}
	f->denumire = NULL;
	f->salarii = NULL;
}
void main()
{
	float* vector1 = malloc(sizeof(float) * 3);
	vector1[0] = 3453;
	vector1[1] = 7543.2;
	vector1[2] = 5638;

	float* vector2 = malloc(sizeof(float) * 4);
	for (int i = 0; i < 4; ++i)
	{
		vector2[i] = i * 400 + 230 * (7 - i);
	}
	
	int nrFabrici = 6;
	struct Fabrica* fabrici = (struct Fabrica*)malloc(sizeof(struct Fabrica) * nrFabrici);
	for (int i = 0; i < nrFabrici; ++i)
	{
		if (i % 2)
		{
			fabrici[i] = initializareFabrica("Tanex", 3, vector1, 1990+(10-i*2));
		}
		else
		{
			fabrici[i] = initializareFabrica("Danone", 4, vector2, 1991-(i*3));
		}
	}
	afiseazaVectorFabrici(fabrici, nrFabrici);

	struct Fabrica* fabriciNoi = NULL;
	int nrFabriciNoi = 0;
	copiazaFabriciNoi(fabrici, nrFabrici, 1990, &fabriciNoi, &nrFabriciNoi);
	printf("\n\n===================Fabricile infiintate dupa 1990: ==========================");
	afiseazaVectorFabrici(fabriciNoi, nrFabriciNoi);
	
	struct Fabrica* fabriciCompanie = NULL;
	int nrFabriciCompanie = 0;
	copiazaFabriciDeLaAceeasiCompanie(fabrici, nrFabrici, "Danone", &fabriciCompanie, &nrFabriciCompanie);
	printf("\n\n===============Fabricile Danone: =====================");
	afiseazaVectorFabrici(fabriciCompanie, nrFabriciCompanie);

	float* vector3 = malloc(sizeof(float) * 2);
	vector3[0] = 8634;
	vector3[1] = 2432.4;
	int nrFabrici1 = 2;
	struct Fabrica* fabrici1 = (struct Fabrica*)malloc(sizeof(struct Fabrica) * nrFabrici1);
	fabrici1[0] = initializareFabrica("Napolact", 2, vector3, 2001);
	fabrici1[1] = initializareFabrica("Astra", 2, vector3, 2003);

	struct Fabrica* fabriciConcat = concatenareFabrici(fabrici, nrFabrici, fabrici1, nrFabrici1);
	int dimConcat = nrFabrici + nrFabrici1;
	printf("\n\n============Concatenare: =====================");
	afiseazaVectorFabrici(fabriciConcat, dimConcat);

	dezalocare(&fabrici, &nrFabrici);
	dezalocare(&fabrici1, &nrFabrici1);
	dezalocare(&fabriciNoi, &nrFabriciNoi);
	dezalocare(&fabriciCompanie, &nrFabriciCompanie);
	dezalocare(&fabriciConcat, &dimConcat);
}
