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

int Verif_Numar(char *c)
{
	int i = 0;
	//Verific daca *c este doar din cifre sau nu
	for (i = 0; c[i] != '\0' ; i++)
	{
		if((c[i] < 48 || c[i] > 57) && c[i] != 10)
		{
			//Daca nu e doar din cifre returnez 1 
			return 1;
	    }
	}	
	//Daca nu returnez 0
	return 0;
}

void Encrypt_Text(char **Mat, int nr_lin)
{
	int i = 0, j = 1;
	char *cuv;
	
	for (i = 0; i < nr_lin; i++)
    {
    char sir[200] = {'\0'};
    //Initializez un string alocat static in care voi crea mesajul 
	cuv = strtok(Mat[i], " ");
	//Selectez elemente de pe liniile matricei pana la spatiu
	while(cuv != NULL)
		{         
           if(Verif_Numar(cuv))
           {
           	    //Daca elementul selectat nu e formant doar din cifre il verific caracter cu caracter
			    for (j = 1; (j < 200 && cuv[j] != '\0'); j++)
			        {
			 	        if(cuv[j] == 10 || cuv[j] == 32)
			 		        {
			 		        	//Daca pozitia pe care ma aflu e spatiu sau '\n' nu ii fac nimic
			 			        cuv[j]=cuv[j];
			 		        }
			 	    else
			 	        {
			 	        	//Daca nu, codific elementul pe caractere in functie de prima pozitie din cuvant dupa 
			 	        	//cum cere cerinat
			 		        cuv[j] = (cuv[0] + cuv[j]) % 256;
			 	        }
			        }
	        }
            strcat(sir, cuv);
            //Concatenez cuvantul ls sir
            if(!strchr(cuv,'\n'))strcat(sir, " ");
			cuv = strtok(NULL," ");
			//Verific daca cuvantul are '\n' ,daca nu adaug un spatiu dupa acesta apoi trec la elementul urmator
		}
		int p = 0;
		while(sir[p])
		{   //Verific daca dupa ultimul element se afla spatiu sau '\n' si le modific pentru a se plia 
	        // cerintei de output
			if(sir[p] == ' ' && sir[p+1] == '\n')
			{
				sir[p+1] = '\0';
				sir[p] = '\n';
			}
			p++;
		}
		printf("%s", sir);
		//Afisez linia codoficata
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
    char **c;
    
    scanf("%d ", &n);
    //Citesc numarul de linii de text

    Alocare_Text(&c, n);
    Populare_Text(&c, n);
    Encrypt_Text(c, n);
    Eliberare_Text(&c, n);
	return 0;
}