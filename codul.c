#define _CRT_SECURE_NO_WARNINGS //pentru a nu mai primi eroarea de la scanf/ putem sa adaugam 4996 la propietati
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *f;
// sublista cu vecinii si tarile
typedef struct vecini {
	char *nume_vecin;
	char *nume_culoare;
	struct vecini *urmator2;
}veci;

//lista mare de tari 
typedef struct tari {
	char *nume_tara;
	struct tari *urmator1;
	struct vecini *sublista;
}tar;
tar *primul = NULL;

veci *introducere_vecini(veci *lista, veci *aux)
{
	veci *q1, *q2;
	for (q1 = q2 = lista; q1 != NULL && strcmp(q1->nume_vecin, aux->nume_vecin) > 0; q2 = q1, q1 = q1->urmator2);
	if (q1 == q2)
	{
		aux->urmator2 - lista;
		lista = aux;
	}
	else {
		q2->urmator2 = aux; //daca il punem pe parcurs
		aux->urmator2 = q1;
	}
	return lista; //asa am adaugat numele vecinului in sublista


	for (q1 = q2 = lista; q1 != NULL && strcmp(q1->nume_culoare, aux->nume_culoare) > 0; q2 = q1, q1 = q1->urmator2);
	if (q1 == q2)
	{
		aux->urmator2 - lista;
		lista = aux;
	}
	else {
		q2->urmator2 = aux; //daca il punem pe parcurs
		aux->urmator2 = q1;
	}
	return lista; //asa am adaugat numele culorii in sublista
}
tar *introducere_tara(tar *lista, tar *aux, veci *aux_s)
{
	tar *a1, *a2;
	for (a1 = a2 = lista; a1 != NULL && strcmp(a1->nume_tara, aux->nume_tara) < 0; a2 = a1, a1 = a1->urmator1);
	if (a1 != NULL && strcmp(a1->nume_tara, aux->nume_tara) == 0) //daca nodul listei e null sau e la fel ca unul pe care l am adaugat deja
	{																//apelam functia de introducere a info in sublista de oferte
		a1->sublista = introducere_vecini(a1->sublista, aux_s);
		free(aux); //eliberam memoria alocata pt aux deoarece nu il vom folosii 
		return lista;//returnam lista de noduri in care au fost adaugate si nodurile sublistei mai sus
	}// daca nodul este inserat la inceputul listei 
	if (a1 == a2)
	{
		aux->urmator1 = lista;
		lista = aux;
	}
	//daca nodul este inserat pe parcurs 
	else
	{
		a2->urmator1 = aux;
		aux->urmator1 = a1;
	}
	aux->sublista = introducere_vecini(aux->sublista, aux_s);
	return lista;
}
void citire()
{
	tar *aux;
	veci *aux_s;
	char nume_tara[20], nume_vecini[20],nume_culoare[20];
	if ((f = fopen("tari.txt", "r")) == NULL) //incercam sa deschidem fisierul in care avem salvata informatia 
	{											  // il deschidem pentru citire de aceea avem nevoie de "r"
		printf("eroare la deschiderea fisierului\n");   // in cazul in care nu se poate afisam un mesaj de atentionare
		exit(1);	// iesim din program cu 1 care indica o eroare
	}
	while (!feof(f))//atat timp cat nu am ajuns la finalul fisierului citim informatii
	{
		fscanf(f, "%s%s%s", nume_tara, nume_vecini, nume_culoare);
		aux = (tar*)malloc(sizeof(tar));
		aux->nume_tara = (char*)malloc(strlen(nume_tara) + 1);
		strcpy(aux->nume_tara, nume_tara);
		aux->sublista = NULL;
		aux_s = (veci*)malloc(sizeof(veci));
		aux_s->nume_vecin = (char*)malloc(strlen(nume_vecini) + 1);
		strcpy(aux_s->nume_vecin, nume_vecini);
		//aux_s = (veci*)malloc(sizeof(veci));
		aux_s->nume_culoare = (char*)malloc(strlen(nume_culoare) + 1);
		strcpy(aux_s->nume_culoare, nume_culoare);
		primul = introducere_tara(primul, aux, aux_s);
	}
}
void afisare(tar *lista)
{
	tar *q;
	veci *p;
	for (q = lista;q != NULL; q = q->urmator1)
	{
		printf("Tara este:%s\n", q->nume_tara);
		for (p = q->sublista ; q != NULL && p!= NULL; p= p->urmator2)
		{
			printf("Vecina si culoarea sunt:%s,%s", p->nume_vecin, p->nume_culoare);
		}printf("\n");
	}

}
int main() {

	int opt,ok=0;
	while (1)
	{
		printf("\n");
		printf("0.iesire\n");
		printf("1.Incarca din fisier datele intr-o lista cu subliste\n");
		printf("2.afisarea datelor citite\n");
		printf("dati optiunea:\n");
		scanf("%d", &opt);// selectam optiunea prin citirea var "opt"
		printf("\n");
		switch (opt)
		{
		case 0: exit(1);
			break;
		case 1: ok++;
			citire();
			//afisare(primul);
			break;
		case 2: 
			if (ok == 0)
			{
				printf("mai intai trebuie selectata optiunea 1 pt a putea fi incarcate datele!\n"); 
			}
			afisare(primul);
			break;
		default:printf("dati o optiune valida!\n");
			break;
		}
	}
	system("pause");
	return 0;
}