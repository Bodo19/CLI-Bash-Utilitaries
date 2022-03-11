#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Citire(int *nr_fields, int *nr_linii, char *delim, int field[], char *delim_out)
{
	int i = 0;
	//In aceasta functie citesc delimitatorul din text, nr de campuri, sirul de campuri, delimitatorul nou 
	//Si numarul de linii de text
	scanf("%s\n", delim);
    scanf("%d\n", nr_fields);
    for (i = 0; i < (*nr_fields); i++)
	{
		scanf("%d,", &field[i]);
	}
    scanf("%s\n",delim_out);
    scanf("%d\n", nr_linii);
}

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
    	fgets(sir,200,stdin);
    	(*Mat)[i] = (char *) malloc ((strlen(sir) + 1) * sizeof(char));
    	//Am citit matricea folosindu-ma de un string ajutator
    	strcpy((*Mat)[i],sir);
    	while(sir[j])
    	{
    		//Eliberez stringul ajutator
    		sir[j] = '\0';
    		j++;
    	}
    	j=0;
    }
}

void Sortare(int *vec, int nr_fields)
{
   int i = 0, j = 0;
   int aux;
   //In acasta functie sortez vectorul de campuri in ordine crescatoare
   for(i = 0; i < nr_fields - 1; i++)
    {
    	for ( j = i; j < nr_fields; j++)
    	{
            if(vec[i] > vec[j])
            {
	            aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
        }
        
    }
}

void Cut(char **Mat, int nr_lin, char *delim, char *delim_out, int nr_fields, int *vec)
{
    int i = 0, j = 0, contor = 0;
    char *cuv, *cuv2;
    int lungdel = strlen(delim_out);
    //Aflu lungimea delimitatorului nou
    
    for (i = 0; i < nr_lin; i++)
    {
    	//Folosesc un for pt a naviga pe liniile matricei
    	int lungsir = 0;
    	char sir[200] = {'\0'};
    	//Sirul pe care scriu initial
    	char sir2[200] = {'\0'};
    	//Sirul pe care scriu pentru a elimina repetarea delimitatorului nou
	    cuv = strtok(Mat[i], delim);
	    //Selectez elemente de pe liniile matricei pana la delimitator
	    contor++;
	    //un contor care imi spune cate selectii am facut pe o linie pentru a-mi reprezenta campurile
	    while(cuv != NULL)
	    {
	    	for (j = 0; j < nr_fields; j++)
	    	{
	    		//Merg prin toate elementele vectorului si verific daca se potrivesc cu val contorul la care ma aflu
	    	    if(contor == vec[j])
	         	{ 
	         		//Concatenez campul cerut cu noul delimitator pe stringul sir
	    	      	strcat(sir, cuv);
                    strcat(sir, delim_out);	    	      		
	        	}
	        }
	    	cuv = strtok(NULL, delim);
	    	contor++;
	    	//Trec la elementul urmator si cresc si contorul pentru a verifica campul urmator
	    }
	    //Rescriu sirul 1 in sirul 2 pentru a elimina posibilile greseri
        cuv2 = strtok(sir, delim_out);
        //Iau primul element din sirul 1 pana la noul delimitator
        while(cuv2 != NULL )
        {
            if ((int)(*cuv2)==10)
            {
            	break;
            	//Daca val intreaga a pointerului cuv doi e 10 inseamna ce e '\n' si ies bucla
            }
        	strcat(sir2, cuv2);
        	strcat(sir2, delim_out);
        	cuv2=strtok(NULL, delim_out);
        	//Concatenez la sirul 2 elementul cu tot cu noul delimitator apoi trec la elemntul urmator
        }
        lungsir = strlen(sir2);
        //Aflu lungimea sirului 2
        sir2[lungsir - lungdel] = '\0';
        //Elimin ultima catenare a delimitatorului  care nu convine cerintei
        //Ex: Ana::18::Verde::Mere::Bucuresti:: si elimin ultima pereche de :
        lungsir = strlen(sir2);
        //Reinitializez lungimea sirului 2 dupa modificari
        printf("%s", sir2);
        //Afisez linia cautat
	    if(lungsir == 0 || sir2[lungsir - 1] != 10)
	    //Daca lungimea sirului 2 e 0 sau ultimul element al sirului nu e '\n' il adaug
	    printf("\n");
	    contor = 0;
	    //Reinitializez contorul cu 0 pentru verificarea urmatoarelor linii
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
    char del[10], out_del[10];
    char **c;
    int n, m, i = 0;
    int fields[100];
    
    Citire(&n, &m, del, fields, out_del);
    Alocare_Text(&c, m);
    Populare_Text(&c, m);
    Sortare(fields, n);
    //Sortez elementele vectorului in ordine crescatoare
    for (i = 0; i < n - 1; i++)
    {
    	//Elimin elementele care se repet din vector prin in citirea pe pozitia lor a ultimului element
    	//Apoi scad numarul de elemente ale vectorului pentru a scapa de spatiul liber 
    	if (fields[i] == fields[i+1])
    	{
    		fields[i] = fields[n-1];
    		n = n - 1;
    	}
    }
    Sortare(fields, n);
    //Sortez din nou vectorul pentru a pune in ordine elemente care si-au schimbat pozitia
    for (i = 0; i < n - 1; i++)
    {
    	//Ma asigur ca am eliminat toate elemnetele care se repeta folosind aceeasi metoda
    	if (fields[i] == fields[i+1])
    	{
    		fields[i] = fields[n-1];
    		n = n - 1;
    	}
    } 
    Sortare(fields, n);
    //Le sortez din nou
    Cut(c, m, del, out_del, n, fields);
   
    Eliberare_Text(&c, m);
	return 0;
}