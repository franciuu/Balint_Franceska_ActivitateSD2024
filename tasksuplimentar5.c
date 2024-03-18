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
struct Nod
{
    struct Fabrica info;
    struct Nod* next;
};
struct Nod* inserareInceput(struct Nod* cap, struct Fabrica f)
{
    struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
    nou->info = f;
    nou->next = cap;
    return nou;
}
struct Fabrica* salvareVectorConditie(struct Nod* lista, int pragAn, int* nrElemente) 
{
    *nrElemente = 0;
    struct Nod* temp = lista;
    while (temp != NULL) 
    {
        if (temp->info.anInfiintare > pragAn) 
        {
            (*nrElemente)++;
        }
        temp = temp->next;
    }

    struct Fabrica* vector = malloc(sizeof(struct Fabrica) * (*nrElemente));
    int contor = 0;
    temp = lista;
    while (temp != NULL) 
    {
        if (temp->info.anInfiintare > pragAn) 
        {
            vector[contor].denumire = malloc(sizeof(char) * (strlen(temp->info.denumire) + 1));
            strcpy(vector[contor].denumire, temp->info.denumire);
            vector[contor].nrAngajati = temp->info.nrAngajati;
            vector[contor].salarii = malloc(sizeof(int) * temp->info.nrAngajati);
            for (int i = 0; i < temp->info.nrAngajati; ++i) 
            {
                vector[contor].salarii[i] = temp->info.salarii[i];
            }
            vector[contor].anInfiintare = temp->info.anInfiintare;
            contor++;
        }
        temp = temp->next;
    }
    return vector;
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
void afisareVectorFabrici(struct Fabrica* f, int nrFabrici)
{
    if (f != NULL)
    {
        for (int i = 0; i < nrFabrici; ++i)
            afisareFabrica(f[i]);
    }
}
void afisareLista(struct Nod* cap)
{
    while (cap!=NULL)
    {
        afisareFabrica(cap->info);
        cap = cap->next;
    }
}  
void stergereNodPozitie(struct Nod** lista, int pozitie) 
{
    struct Nod* prezent = *lista;
    struct Nod* anterior = NULL;

    for (int i = 0; i < pozitie && prezent != NULL; ++i) 
    {
        anterior = prezent;
        prezent = prezent->next;
    }
    if (prezent != NULL) 
    {
        if (anterior == NULL) 
        {
            *lista = prezent->next;
        }
        else 
        {
            anterior->next = prezent->next;
        }
        free(prezent->info.denumire);
        free(prezent->info.salarii);
        free(prezent);
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
struct Nod* citireFisier(const char* numeFisier)
{
    if (numeFisier != NULL && strlen(numeFisier) > 0)
    {
        FILE* f = fopen(numeFisier, "r");
        if (f != NULL)
        {
            struct Nod* lista = NULL;
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
                lista = inserareInceput(lista, fabrica);
            }
            fclose(f);
            return lista;
        }
    }
}
void interschimbareElemente(struct Nod* cap, int pozitie1, int pozitie2)
{
    struct Nod* nod1 = cap;
    struct Nod* nod2 = cap;
    struct Fabrica temp;

    for (int i = 0; i < pozitie1 && nod1 != NULL; ++i)
        nod1 = nod1->next;

    for (int i = 0; i < pozitie2 && nod2 != NULL; ++i)
        nod2 = nod2->next;

    if (nod1 != NULL && nod2 != NULL && nod1 != nod2)
    {
        temp = nod1->info;
        nod1->info = nod2->info;
        nod2->info = temp;
    }
}
void dezalocare(struct Nod** cap)
{
    while (*cap)
    {
        free((*cap)->info.denumire);
        free((*cap)->info.salarii);
        struct Nod* aux = (*cap)->next;
        free((*cap));
        (*cap) = aux;
    }
}
void main()
{
    /*int* vector1 = malloc(sizeof(float) * 3);
    vector1[0] = 3453;
    vector1[1] = 7543;
    vector1[2] = 5638;
    struct Fabrica f = initializareFabrica("Abc", 3, vector1, 1832);
    struct Fabrica f2 = initializareFabrica("Cde", 3, vector1, 1915);

    struct Nod* cap = NULL;
    cap = inserareInceput(cap, f);
    cap = inserareInceput(cap, f2);

    afisareLista(cap);*/
    struct Nod* cap = citireFisier("fabrici.txt");
    stergereNodPozitie(&cap, 2);
    afisareLista(cap);
    int nrElemente = 10;
    struct Fabrica* fabrici = malloc(sizeof(struct Fabrica) * nrElemente);
    fabrici = salvareVectorConditie(cap, 1950, &nrElemente);
    printf("\nVectorul de obiecte: \n");
    afisareVectorFabrici(fabrici, nrElemente);
    interschimbareElemente(cap, 2, 3);
    printf("\nDupa interschimbare: \n");
    afisareLista(cap);
    dezalocare(&cap);
}
