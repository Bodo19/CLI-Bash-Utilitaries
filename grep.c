#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Alocare_Text(char ***Mat, int nr_lin)
{
	//Creez vectorul de pointeri
	*Mat = (char **) malloc (nr_lin * sizeof(char *));
}

void Populare_Text(char ***Mat, int nr_lin)
{
	int i = 0, j = 0;
	char sir[200];
	
	for (i = 0; i < nr_lin; i++)
    {
    	fgets(sir, 200, stdin);
    	(*Mat)[i] = (char *) malloc ((strlen(sir) + 1) * sizeof(char));
    	//Am citit matricea folosindu-ma de un string ajutator
    	strcpy((*Mat)[i], sir);
    	while(sir[j])
    	{
    		//Eliberez stringul ajutator
    		sir[j] = '\0';
    		j++;
    	}
    	j = 0;
    }
}

void Grep(char **Mat, int nr_lin, char *sir)
{
	int i = 0, ok = 0, lung = 0;
	char *g;
	g = strtok(sir,"\n");
	//Folosesc un pointer pentru a salva sirul cautat pana la new line 
	lung = strlen(g);
	//Salvez lungimea sirului cautat 
	for (i = 0; i < nr_lin; i++)
	{
	 	char *lin = Mat[i];
	 	//Salvez in pointer cate o linie din matrice
	 	char linie[200] = {'\0'};
	 	//Initializez un string alocat static pentru a putea prelucra linia matricei in el 
	 	while(strstr(lin, g))
	 		{
	 			ok = 1;
	 			//Folosesc un semafor pentru a verifica daca am sirul cautat pe acea linie
	 			int cuv = strstr(lin, g) - lin;
	 			//Aflu pozitia de la care incepe sirul cautat 
	 			strncat(linie, lin, cuv);
	 			strcat(linie,"\e[0;31m");
	 			strcat(linie, g);
	 			strcat(linie,"\e[m");
                //Concatenez in string ul alocat static linia pana la sirul cautat apoi concatenez si sirul colorat rosu 
	 			lin = lin + lung + cuv;
	 			//Adun pozitia la care se gaseste sirul apoi adaug si lungimea sirului pentru a verifica daca 
	 			//mai gasesc sirul cautat inca odata fara a lua in considerare la verificare prima gasire a sirului
	 		}
	 		strcat(linie, lin);
            //Trec la linia urmatoare din matrice
            if (ok)
            {
            	//Daca ok e 1 inseamna ca am gasit macar odata sirul si afisez stringul
	 		    printf("%s", linie);
	 	    }
	 	ok = 0;
	 	//Reinitializez semaforul cu 0 pentru urmatoarele verificari
	} 
}


void Eliberare_Text(char ***Mat, int nr_lin)
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
	int n;
    char grep[30];    
    char **c;
    
    fgets(grep, 30, stdin);
    //Citesc sirul cautat
    scanf("%d\n", &n);
    //Citesc numarul de linii de text 
    
    Alocare_Text(&c, n);
    Populare_Text(&c, n);
    Grep(c, n, grep);
    Eliberare_Text(&c, n);
	return 0;
}