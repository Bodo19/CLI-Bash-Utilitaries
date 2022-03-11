#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Alocare_Matrice(float ***Mat, int nr_lin, int cap)
{
	int i = 0;
	//Creez vectorul de pointeri si initializez fiecare linie cu lungimea minima
	
	*Mat = (float **) malloc (nr_lin * sizeof(float *));
    for (i = 0; i < nr_lin; i++)
    {
    	(*Mat)[i] = (float *) malloc (cap * sizeof(float));
    }
}

void Populare_Matrice(float ***Mat, int nr_lin, int cap)
{
    int i = 0, j = 1;
    //Citesc elementele matricei de pe coloana j = 1 pentru ca pastrez prima coloana pentru medie
    for ( i = 0; i < nr_lin; i++) 
    {
    	scanf("%f", &(*Mat)[i][j]);
    	(*Mat)[i][0] = (*Mat)[i][j];
        while((*Mat)[i][j])
        {
        	j = j + 1;
        	if(j == cap)
        	//daca nr de elemente de pe o linie a ajuns la capat maresc memoria alocata cu 3
        	{
        		cap = cap + 3;
        		(*Mat)[i] = (float *) realloc ((*Mat)[i], cap * sizeof(float));
        	}
        	scanf("%f", &(*Mat)[i][j]);
        	(*Mat)[i][0] = (*Mat)[i][0] + (*Mat)[i][j];
            }
        (*Mat)[i][0] = (*Mat)[i][0] / (j - 1);
        //Fac media notelor pe prima coloana dupa ce am adunat aici toate celelalte elemnte
        j = 1;
        cap = 3;
        //Reinitializez j ul  si lungimea matricei cu cele initiale
    }
}

void Sortare(float **Mat, int nr_lin)
{
   int i, j;
   float *aux;
   //Sortez liniile matricei in ordine descrescatoare in functie de prima coloana
   for(i = 0; i < nr_lin - 1; i++)
    {
        for(j = 0; j < nr_lin - i - 1; j++)
        {
        	
            if(Mat[j][0] < Mat[j + 1][0])
	        {
		        aux = Mat[j];
                Mat[j] = Mat[j + 1];
                Mat[j + 1] = aux;
            }
        }
    }
}

void Afisare_Matrice(float **Mat, int nr_lin, int cap)
{
	int i = 0, j = 1;
	
	for (i = 0; i < nr_lin; i++)
	{
		//Afisez matricea cu spatiile cerute 
		if(Mat[i][0] < 10)
			printf("%.3f     ", Mat[i][0]);
		else
			printf("%.3f    ", Mat[i][0]);
		while(Mat[i][j])
		{
			printf("%.0f ", Mat[i][j]);
			j++;
		}
		j = 1;
		printf("\n");
	}
}

void Eliberare_Matrice(float ***Mat, int nr_lin)
{
	int i;
	//Am eliberat memoria ocupata de matricea alocata dinamic
	
	for (i = 0; i < nr_lin; i++)
    {
    	free((*Mat)[i]);
    }
    free(*Mat);
}

int main()
{
    int n, cap = 3;
	float **a;
	
	scanf("%d", &n);
	//Citesc numarul de medii
	
	Alocare_Matrice(&a, n, cap);
	Populare_Matrice(&a, n, cap);
	Sortare(a, n);
	Afisare_Matrice(a, n, cap);
	Eliberare_Matrice(&a, n);
	return 0;
}