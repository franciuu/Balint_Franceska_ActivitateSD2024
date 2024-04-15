#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
typedef struct Fabrica Fabrica;
typedef struct Nod Nod;
typedef struct NodSimplu NodSimplu;
typedef struct ListaDubla ListaDubla;

struct Fabrica
{
    char* denumire;
    int nrAngajati;
    int anInfiintare;
};
struct Nod
{
    Nod* anterior;
    Nod* urmator;
    Fabrica info;
};
struct NodSimplu
{
    NodSimplu* next;
    Fabrica info;
};
struct ListaDubla
{
    Nod* cap;
    Nod* coada;
};
Fabrica initializareFabrica(const char* denumire, int nrAngajati, int anInfiintare)
{
    Fabrica f;
    f.denumire = malloc(strlen(denumire) + 1);
    strcpy(f.denumire, denumire);
    f.nrAngajati = nrAngajati;
    f.anInfiintare = anInfiintare;
    return f;
}
void afisareFabrica(Fabrica f)
{
    printf("\nDenumire: %s \t Nr angajati: %d \t An infiintare: %d", f.denumire, f.nrAngajati, f.anInfiintare);
}
void inserareOrdonata(ListaDubla* ld, Fabrica f)
{
    Nod* nod = malloc(sizeof(Nod));
    nod->info = f;
    if (ld->cap == NULL)
    {
        ld->cap = nod;
        ld->coada = nod;
        nod->anterior = NULL;
        nod->urmator = NULL;
    }
    else
    {
        Nod* aux = ld->cap;
        while (aux && aux->info.anInfiintare < f.anInfiintare)
        {
            aux = aux->urmator;
        }
        if (aux)
        {
            if (aux->anterior == NULL)
            {
                nod->urmator = aux;
                nod->anterior = NULL;
                aux->anterior = nod;
                ld->cap = nod;
            }
            else
            {
                nod->urmator = aux;
                nod->anterior = aux->anterior;
                aux->anterior = nod;
            }
        }
        else
        {
            nod->anterior = ld->coada;
            nod->urmator = NULL;
            ld->coada->urmator = nod;
            ld->coada = nod;
        }
    }
}
void citesteDinFisier(const char* caleFisier, ListaDubla* ld)
{
    if (caleFisier != NULL)
    {
        FILE* f = fopen(caleFisier, "r");
        if (f)
        {
            char buffer[100];
            char delim[] = ",\n";
            while (fgets(buffer, 99, f))
            {
                Fabrica f;
                char* token = strtok(buffer, delim);
                f.denumire = malloc(strlen(token) + 1);
                strcpy(f.denumire, token);
                token = strtok(NULL, delim);
                f.nrAngajati = atoi(token);
                token = strtok(NULL, delim);
                f.anInfiintare = atoi(token);
                inserareOrdonata(ld, f);
            }
        }
    }
}
void afisareLista(ListaDubla ld)
{
    Nod* nod = ld.cap;
    while (nod)
    {
        afisareFabrica(nod->info);
        nod = nod->urmator;
    }
}
void afisareListaDescrescatoare(ListaDubla ld)
{
    Nod* nod = ld.coada;
    while (nod)
    {
        afisareFabrica(nod->info);
        nod = nod->anterior;
    }
}
NodSimplu* inserareListaSimpla(Nod* lista, Fabrica f)
{
    NodSimplu* nou = malloc(sizeof(NodSimplu));
    nou->next = lista;
    nou->info = f;
    return nou;
}
Nod* salvareListaSimpla(ListaDubla ld, int prag)
{
    Nod* nod = ld.cap;
    if (nod)
    {
        Nod* listaSimpla = NULL;
        while (nod)
        {
            if (nod->info.nrAngajati < prag)
            {
                listaSimpla = inserareListaSimpla(listaSimpla, initializareFabrica(nod->info.denumire, nod->info.nrAngajati, nod->info.anInfiintare));
            }
            nod = nod->urmator;
        }
        return listaSimpla;
    }
    return NULL;
}
ListaDubla interschimbare(ListaDubla ld, int poz1, int poz2)
{
    Nod* nod1 = ld.cap;
    Nod* nod2 = ld.cap;
    int i = 0, j = 0;
    while (nod1 && i < poz1)
    {
        i++;
        nod1 = nod1->urmator;
    }
    while (nod2 && j < poz2)
    {
        j++;
        nod2 = nod2->urmator;
    }
    if (nod1 && nod2)
    {
        Fabrica aux = nod1->info;
        nod1->info = nod2->info;
        nod2->info = aux;
    }
    return ld;
}
void dezalocareLista(ListaDubla* ld)
{
    Nod* nod = ld->cap;
    while (nod)
    {
        Nod* aux = nod;
        nod = nod->urmator;
        free(aux->info.denumire);
        free(aux);
    }
    ld->cap = NULL;
    ld->coada = NULL;
}
void main()
{
    ListaDubla listaDubla;
    listaDubla.cap = NULL;
    listaDubla.coada = NULL;
    citesteDinFisier("date.txt", &listaDubla);
    afisareLista(listaDubla);
    printf("\n");
    afisareListaDescrescatoare(listaDubla);
    printf("\nLISTA SIMPLA\n");
    NodSimplu* listaSimpla = salvareListaSimpla(listaDubla, 10);
    if (listaSimpla)
    {
        while (listaSimpla)
        {
            afisareFabrica(listaSimpla->info);
            listaSimpla = listaSimpla->next;
        }
    }
    interschimbare(listaDubla, 0, 1);
    printf("\nDUPA INTERSCHIMBARE\n");
    afisareLista(listaDubla);
    dezalocareLista(&listaDubla);
}
