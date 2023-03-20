#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int coeff;
	int powx;
	int powy;
	struct node *next;
}NODE;

typedef struct plist
{
	struct node *head;
}POLYNOMIAL;
void initPolynomial(POLYNOMIAL *pl);
void createPolynomial(POLYNOMIAL *pl);
int addPolynomial(POLYNOMIAL *pl1,POLYNOMIAL *pl2,POLYNOMIAL *pl3);

int main()
{
	POLYNOMIAL pobj1,pobj2,pobj3;


	initPolynomial(&pobj1);
	initPolynomial(&pobj2);
	initPolynomial(&pobj3);

	printf("Polynomial1\n");
	createPolynomial(&pobj1);
	display(&pobj1);

	printf("Polynomial2\n");
	createPolynomial(&pobj2);
	display(&pobj2);

	addPolynomial(&pobj1,&pobj2,&pobj3);
	printf("\nResultant Polynomial\n");
	display(&pobj3);

	destroyPolynomial(&pobj1);
	destroyPolynomial(&pobj2);
	destroyPolynomial(&pobj3);
}

void initPolynomial(POLYNOMIAL *pl)
{
	pl->head=NULL;
}
void insertLast(POLYNOMIAL *pl,int cf,int px,int py)
{
	NODE *newNode=malloc(sizeof(NODE));
	newNode->coeff=cf;
	newNode->powx=px;
	newNode->powy=py;
	newNode->next=NULL;

	NODE *p=pl->head;
	if(pl->head==NULL)
	{
		pl->head=newNode;
	}
	else
	{
		while(p->next!=NULL)
			p=p->next;

		p->next=newNode;
	}
}
void createPolynomial(POLYNOMIAL *pl)
{
	int choice;
	int cf,px,py;

	do{
		printf("Enter coeff and power of x and power of y\n");
		scanf("%d %d %d",&cf,&px,&py);
		insertLast(pl,cf,px,py);

		printf("Do you want to add one more term\n");
		scanf("%d",&choice);

	}while(choice);
}
int addPolynomial(POLYNOMIAL *pl1,POLYNOMIAL *pl2,POLYNOMIAL *pl3)
{
	NODE *p=pl1->head;
	NODE *q=pl2->head;

	int cf,px,py;

	while(p!=NULL && q!=NULL)
	{
		if(p->powx == q->powx)
		{
			if (p->powy == q->powy)
			{
				cf=p->coeff+q->coeff;
				px=p->powx;
				py=p->powy;
				p=p->next;
				q=q->next;
			}
			else if (p->powy > q->powy)
			{
				cf=p->coeff;
				px=p->powx;
				py=p->powy;
				p=p->next;
			}
			else
			{
				cf=q->coeff;
				px=q->powx;
				py=q->powy;
				q=q->next;
			}
		}
		else if(p->powx > q->powx)
		{
			cf=p->coeff;
			px=p->powx;
			py=p->powy;
			p=p->next;
		}
		else
		{
			cf=q->coeff;
			px=q->powx;
			py=q->powy;
			q=q->next;
		}
		insertLast(pl3,cf,px,py);
	}
	while(p!=NULL)
	{
		insertLast(pl3,p->coeff,p->powx,p->powy);
		p=p->next;
	}
	while(q!=NULL)
	{
		insertLast(pl3,q->coeff,q->powx,q->powy);
		q=q->next;
	}
}

void display(POLYNOMIAL *pl)
{
	NODE *p=pl->head;

	while(p->next!=NULL)
	{
		printf("(%d x^%d y^%d)+",p->coeff,p->powx,p->powy);
		p=p->next;
	}
	printf("(%d x^%d y^%d)\n",p->coeff,p->powx,p->powy);
}

void destroyPolynomial(POLYNOMIAL *pl)
{
	NODE *p;

	while(pl->head!=NULL)
	{
		p=pl->head;
		pl->head=pl->head->next;
		free(p);
	}
}
