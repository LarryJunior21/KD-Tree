#include"taj.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define coluna 50
#define linha 50

struct No
{
	int x, y;
	struct No *esq, *dir;
};
typedef struct No no;

void init(no **r)
{
	*r = NULL;
}

void exibe(no *r , int a, int b, int dist)
{
	if(r != NULL)
	{
		gotoxy(a,b);

		printf("(%d,%d)",r -> x, r -> y);
		if(r->esq!=NULL)
		{
			gotoxy(a - dist / 2, b + 1);
			printf("/");
		}
		if(r->dir!=NULL)
		{
			gotoxy(a + dist / 2 + 2, b + 1);
			printf("\\");
		}

		exibe(r -> esq, a - dist, b + 2, dist - dist / 2 + 2);
		exibe(r -> dir, a + dist, b + 2, dist - dist / 2 + 2);
	}
}

no* criano(int x, int y)
{
	no *niu = (no *)malloc(sizeof(no));
	niu -> x = x;
	niu -> y = y;
	niu -> esq = NULL;
	niu -> dir = NULL;

	return niu;
}

float distancia_nodo(int x1, int y1, int x2, int y2)
{
	float dist;
	dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

	return dist;
}

void busca(no *r, int x, int y)
{

	float dist, distMenor;
	int nivel = 0;
	no  *aux;

	if(r == NULL)
		printf("FATAL ERROR: *Empty Tree*");
	else
	{
		aux = r;
		distMenor = distancia_nodo(x, y, r -> x, r -> y);
		if(distMenor == 0)
		{
			gotoxy(60,4);
			printf("Coordenada encontrada (%d,%d)", aux -> x, aux -> y);
		}
		else
		{
			while(r != NULL)
			{
				if(nivel % 2 == 0)//nivel x
				{
					if(x < r -> x)//esq
						r = r -> esq;
					else //dir
						r = r -> dir;
				}
				else// nivel y
				{
					if(y < r -> y)//esq
						r = r -> esq;
					else//dir
						r = r -> dir;
				}
				if(r != NULL)
				{
					dist = distancia_nodo(x, y, r -> x, r -> y);
					if(dist < distMenor)
					{
						distMenor = dist;
						aux = r;
					}
				}
				nivel++;
			}
		}
		gotoxy(60,3);
        textcolor(12);
        printf("Coordenada (%d,%d)",x,y);
        textcolor(15);
		if(distMenor == 0)
		{
			gotoxy(60,4);
			printf("Coordenada encontrada (%d,%d)", aux -> x, aux -> y);
		}
		else
		{
			gotoxy(60,4);
			printf("Coordenada nao encontrada ");
			gotoxy(60,5);
			printf("Vizinho proximo -> : (%d,%d)", aux -> x, aux -> y);
		}



	}

}

void insert(no **r, int x, int y)
{
	no *novo, *aux, *ant;
	novo = criano(x, y);
	int nivel = 0;
	char lado;

	if(*r == NULL)
		*r = novo;
	else
	{
		ant = aux = *r;
		while(aux != NULL)
		{

			if(nivel % 2 == 0)// é par, nivel X
			{
				if(novo -> x > aux -> x)
				{
					aux = aux -> dir;
					lado = 'd';
				}
				else
				{
					aux = aux -> esq;
					lado = 'e';
				}
			}
			else// é impar, nivel Y
			{
				if(novo -> y > aux -> y)
				{
					aux = aux -> dir;
					lado = 'd';
				}
				else
				{
					aux = aux -> esq;
					lado = 'e';
				}
			}

			if(aux == NULL)
			{
				if(lado == 'd')
					ant -> dir = novo;
				else
					ant -> esq = novo;
			}
			ant = aux;
			nivel ++;
		}
	}
}

void menu(no *r)
{
    int x,y;
    do
    {
        printf("[1] Vizinho Proximo\n[2] Inserir na arvore\n[0] SAIR\nSELECIONAR: ");
        scanf("%d",&x);
        Sleep(400);
        switch(x)
        {
            case 1:
                clrscr();
                exibe(r, 40, 1, 5);
                gotoxy(60,1);
                printf("**Vizinho proximo, digite um x e um y para ");
                gotoxy(60,2);
                printf("buscar na arvore ao lado****");
                gotoxy(60,3);
                printf("X: ");
                scanf("%d",&x);
                gotoxy(60,4);
                printf("Y: ");
                scanf("%d",&y);
                busca(r, x, y);
                getch();
                clrscr();
            break;
            case 2:
                clrscr();
                gotoxy(60,1);
                printf("**Digite um X e um Y para inserir na arvore**");
                gotoxy(60,2);
                printf("X: ");
                scanf("%d",&x);
                gotoxy(60,3);
                printf("Y: ");
                scanf("%d",&y);
                insert(&r, x, y);
                gotoxy(60,4);
                printf("*INSERIDO* PRESSIONE ALGUMA TECLA PARA VER A ARVORE");
                getch();
                exibe(r, 40, 1, 6);
                getch();
                clrscr();
        }
    }while(x!=0);
}

int main()
{
	no *r;
	init(&r);
	int x, y, i, aux, aux2;
    srand(time(NULL));
    ///insere automaticamente 13 valores para a arvore
    insert(&r, 10, 9);
    insert(&r, 8, 7);
    insert(&r, 1, 3);
    insert(&r, 5, 6);
    insert(&r, 7, 8);
    insert(&r, 10, 10);
    insert(&r, 11, 13);
    insert(&r, 10, 12);
    insert(&r, 12, 14);
    menu(r);
	//exibe_magic(r, 40, 2, 79);
}
