#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Fabrica
{
    char* denumire;
    int nrAngajati;
    int* salarii;
    int anInfiintare;
};
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
void afisareFabrica(struct Fabrica f)
{
    printf("\nDenumire: %s, Nr angajati: %i", f.denumire, f.nrAngajati);
    if (f.nrAngajati > 0)
    {
        printf(" Salariile angajatilor: ");
        for (int i = 0; i < f.nrAngajati; ++i)
            printf("%i, ", f.salarii[i]);
    }
    printf("Anul infiintarii: %i", f.anInfiintare);
}
void afisareVectorFabrici(struct Fabrica* fabrici, int dim)
{
    for (int i = 0; i < dim; ++i)
        afisareFabrica(fabrici[i]);
}
struct Fabrica** creeazaMatrice(struct Fabrica* fabrici, int dim, int* nrLinii, int** nrCol, int pragAn)
{
    struct Fabrica** matrice;
    *nrLinii = 2;
    matrice = malloc(sizeof(struct Fabrica*) * (*nrLinii));
    *nrCol = malloc(sizeof(int) * (*nrLinii));
    for (int i = 0; i < (*nrLinii); ++i)
    {
        (*nrCol)[i] = 0;
        matrice[i] = NULL;
    }
    for (int i = 0; i < dim; ++i)
    {
        if (fabrici[i].anInfiintare > pragAn)
        {
            inserareFabrica(&(matrice[0]), &((*nrCol)[0]), fabrici[i]);
        }
        else
        {
            inserareFabrica(&(matrice[1]), &((*nrCol)[1]), fabrici[i]);
        }
    }

    return matrice;
}
void afiseazaMatrice(struct Fabrica** matrice, int nrLinii, int* nrColoane)
{
    for (int i = 0; i < nrLinii; ++i)
    {
        afisareVectorFabrici(matrice[i], nrColoane[i]);
        printf("\n\n");
    }
}
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
struct Fabrica* citireFisier(const char* numeFisier, int* nrFabrici)
{
    if (numeFisier != NULL && strlen(numeFisier) > 0)
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
    if (numeFisier != NULL && strlen(numeFisier) > 0)
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
    if (numeFisier != NULL && strlen(numeFisier) > 0)
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
void swap(struct Fabrica** a, struct Fabrica** b, int* nrColoaneA, int* nrColoaneB) {
    struct Fabrica* aux = *a;
    *a = *b;
    *b = aux;

    int aux1 = *nrColoaneA;
    *nrColoaneA = *nrColoaneB;
    *nrColoaneB = aux1;
}

void sortareLinii(struct Fabrica*** matrice, int nrLinii, int* nrColoane) {
    for (int i = 0; i < nrLinii - 1; ++i) {
        for (int j = 0; j < nrLinii - i - 1; ++j) {
            if (nrColoane[j] > nrColoane[j + 1]) {
                swap(&(*matrice) + j, &(*matrice) + j + 1, &nrColoane[j], &nrColoane[j + 1]);
            }
        }
    }
}

void main()
{
    struct Fabrica* fabrici = NULL;
    int dim = 0;
    int nrLinii = 0;
    int* vectorColoane = NULL;
    fabrici = citireFisier("fabrici.txt", &dim);
    // afisareVectorFabrici(fabrici, dim);

    int* vector2 = malloc(sizeof(int) * 4);
    for (int i = 0; i < 4; ++i)
    {
        vector2[i] = (i + 2) * 100 + (500 - i * 22);
    }
    struct Fabrica fabrica1 = initializareFabrica("Napolact", 4, vector2, 2001);
    salvareFisier("fabrica.txt", fabrica1);
    salvareVectorFisier("fabriciSalvate.txt", fabrici, dim);

    struct Fabrica** matrice = creeazaMatrice(fabrici, dim, &nrLinii, &vectorColoane, 1950);
    afiseazaMatrice(matrice, nrLinii, vectorColoane);
    sortareLinii(matrice, nrLinii, vectorColoane);
    printf("\n\nMatricea dupa sortare:\n");
    afiseazaMatrice(matrice, nrLinii, vectorColoane);
}
