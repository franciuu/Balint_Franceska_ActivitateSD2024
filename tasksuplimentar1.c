#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
struct Fabrica 
{
	char* denumire;
	int nrAngajati;
	float* salarii;
};
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
	fabrica.salarii = (char*)malloc(sizeof(float) * fabrica.nrAngajati);
	printf("\nSalariile angajatilor: ");
	for (int i = 0; i < fabrica.nrAngajati; ++i)
	{
		printf("\ns[%i]=", i);
		scanf("%f", &fabrica.salarii[i]);
	}
	return fabrica;
}
struct Fabrica* modificaDenumire(struct Fabrica* f, const char* denNoua)
{
	if (denNoua != NULL)
	{
		free(f->denumire);
		f->denumire = NULL;
		f->denumire = malloc(strlen(denNoua) + 1);
		strcpy(f->denumire, denNoua);
	}
	return f;
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
}
float medieSalarii(struct Fabrica f)
{
	float medie = 0;
	if (f.nrAngajati != 0 && f.salarii != NULL)
	{
		for (int i = 0; i < f.nrAngajati; ++i)
		{
			medie += f.salarii[i];
		}
		medie /= f.nrAngajati;
	}
	return medie;
}
void dezalocareFabrica(struct Fabrica *f)
{
	if (f->denumire != NULL)
	{
		free(f->denumire);
	}
	f->denumire = NULL;
}
void main()
{
	struct Fabrica f;
	f.denumire = (char*)malloc(strlen("Croco") + 1);
	strcpy(f.denumire, "Croco");
	f.nrAngajati = 4;
	f.salarii = malloc(sizeof(float) * f.nrAngajati);
	for (int i = 0; i < f.nrAngajati; ++i)
	{
		f.salarii[i] = i * 200 + 4 + 0.48*(100-i);
	}
	afiseazaFabrica(f);
	printf("\nMedia salariilor este: %5.2f ", medieSalarii(f));
	dezalocareFabrica(&f);
	printf("\n\n============Fabrica citita de la tastatura==========");
	struct Fabrica f2 = citesteFabrica();
	modificaDenumire(&f2, "Magura");
	afiseazaFabrica(f2);
	dezalocareFabrica(&f2);
}
