#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Locuinta
{
	int id;
	char* strada;
	int numar;
};
void inserareLocuinta(struct Locuinta** locuinte, int* dim, struct Locuinta locuinta)
{
	struct Locuinta* copie;
	copie = (struct Locuinta*)malloc(sizeof(struct Locuinta) * (++(*dim)));
	for (int i = 0; i < (*dim) - 1; ++i)
	{
		copie[i] = (*locuinte)[i];
	}
	copie[(*dim) - 1] = locuinta;
	if ((*locuinte) != NULL)
	{
		free((*locuinte));
	}
	(*locuinte) = copie;
}
void citesteFisier(const char* nume_fisier, struct Locuinta** vector, int* dim)
{
	if (nume_fisier != NULL && strlen(nume_fisier) > 0)
	{
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL)
		{
			(*dim) = 0;
			char buffer[100];
			char delim[] = ",\n";
			while (fgets(buffer, 100, f) != NULL)
			{
				char* token = strtok(buffer, delim);
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delim);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delim);
				locuinta.numar = atoi(token);
				inserareLocuinta(vector, dim, locuinta);
			}
		}
		fclose(f);
	}
}

void citesteMatriceFisier(const char* nume_fisier, struct Locuinta** matrice, int nrLinii, int* nrColoane)
{
	if (nume_fisier != NULL && strlen(nume_fisier) > 0)
	{
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL)
		{
			char buffer[100];
			char delim[] = ",\n";
			while (fgets(buffer, 100, f) != NULL)
			{
				char* token = strtok(buffer, delim);
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delim);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delim);
				locuinta.numar = atoi(token);
				int pozitie = locuinta.numar % 2;
				inserareLocuinta(&(matrice[pozitie]), &(nrColoane[pozitie]), locuinta);
			}
		}
		fclose(f);
	}
}

void afisareLocuinta(struct Locuinta l)
{
	printf("Id-ul: %i\tStrada: %s numarul %i\t", l.id, l.strada, l.numar);
}
void afisareVectorLocuinte(struct Locuinta* locuinte, int dim)
{
	for (int i = 0; i < dim; ++i)
	{
		afisareLocuinta(locuinte[i]);
	}
}
void stergeLocuinta(struct Locuinta** vector, int* dim, int id)
{
	char flag = 0;
	for (int i = 0; i < (*dim); ++i)
	{
		if ((*vector)[i].id == id)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		struct Locuinta* copie = (struct Locuinta*)malloc(sizeof(struct Locuinta) * ((*dim) - 1));
		int j = 0;
		for (int i = 0; i < (*dim); ++i)
		{
			if ((*vector)[i].id != id)
			{
				copie[j++] = (*vector)[i];
			}
		}
		(*dim)--;
		if ((*vector) != NULL)
		{
			free((*vector));
		}
		(*vector) = copie;
	}
}
void afisareMatrice(struct Locuinta** mat, int nrLinii, int* nrColoane)
{
	for (int i = 0; i < nrLinii; ++i)
	{
		for (int j = 0; j < nrColoane[i]; ++j)
		{
			afisareLocuinta(mat[i][j]);
		}
		printf("\n");
	}
}
void afisareIdDePeOParte(int paritate, struct Locuinta** matrice, int nrLinii, int* nrColoane)
{
	paritate = paritate % 2;
	for(int j = 0; j < nrColoane[paritate]; ++j)
	{
		printf("%d ", matrice[paritate][j].id);
	}
}
//cautare locuinta dupa id
struct Locuinta cautareDupaId(int idCautat, struct Locuinta** matrice, int nrLinii, int* nrColoane)
{
	for (int i = 0; i < nrLinii; ++i)
	{
		for (int j = 0; j < nrColoane[i]; ++j)
		{
			if (matrice[i][j].id == idCautat)
				return matrice[i][j];
		}
	}
	struct Locuinta copie;
	copie.id = -1;
	copie.numar = -1;
	copie.strada = NULL;
	return copie;
}
void dezalocareMatrice(struct Locuinta*** matrice, int* nrLinii, int** nrColoane)
{
	for (int i = 0; i < (*nrLinii); ++i)
	{
		for (int j = 0; j < (*nrColoane)[i]; ++j)
		{
			free((*matrice)[i][j].strada);
			(*matrice)[i][j].strada = NULL;
		}
		free((*matrice)[i]);
	}
	free(*matrice);
	(*matrice) = NULL;

	(*nrLinii) = 0;
	free((*nrColoane));
	(*nrColoane) = NULL;
}

void schimbareNumarLocuinta(struct Locuinta** matrice, int nrLinii, int* nrColoane, int nrLocuinta)
{
	int pozitie = nrLocuinta % 2;
	int idLocuinta = -1;
	int indexInVector = -1;
	for (int i = 0; i < nrColoane[pozitie]; ++i)
	{
		if (matrice[pozitie][i].numar == nrLocuinta)
		{
			matrice[pozitie][i].numar++;
			idLocuinta = matrice[pozitie][i].id;
			indexInVector = i;
		}
	}
	if (idLocuinta != -1)
	{
		int index = (nrLocuinta + 1) % 2;
		inserareLocuinta(&(matrice[index]), &(nrColoane[index]), matrice[pozitie][indexInVector]);
		stergeLocuinta(&(matrice[pozitie]), &(nrColoane[pozitie]), idLocuinta);
	}
}
void main()
{
	int nrLinii;
	int* nrColoane;
	struct Locuinta** matrice;

	nrLinii = 2;
	nrColoane = (int*)malloc(sizeof(int) * nrLinii);
	matrice = (struct Locuinta**)malloc(sizeof(struct Locuinta*) * nrLinii);
	for (int i = 0; i < nrLinii; ++i)
	{
		matrice[i] = NULL;
		nrColoane[i] = 0;
	}
	citesteMatriceFisier("locuinte.txt", matrice, nrLinii, nrColoane);
	afisareMatrice(matrice, nrLinii, nrColoane);
	afisareIdDePeOParte(11, matrice, nrLinii, nrColoane);
	struct Locuinta locuinta1 = cautareDupaId(22, matrice, nrLinii, nrColoane);
	afisareLocuinta(locuinta1);
	schimbareNumarLocuinta(matrice, nrLinii, nrColoane, 5);
	printf("\n\n dupa mutare\n");
	afisareMatrice(matrice, nrLinii, nrColoane);
	dezalocareMatrice(&matrice, &nrLinii, &nrColoane);
}
