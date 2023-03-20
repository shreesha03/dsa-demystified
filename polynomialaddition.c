#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int exponent;
    float coefficient;
    struct Node *next;
};


struct Node *add(struct Node*, int, float);
struct Node* create(struct Node*);
struct Node *sum(struct Node *,struct Node *);


int main()
{
    struct Node *head1 = (struct Node *)malloc(sizeof(struct Node));
    struct Node *head2 = (struct Node *)malloc(sizeof(struct Node));
    struct Node *head3 = (struct Node *)malloc(sizeof(struct Node));

    head1 = NULL;
    head2 = NULL;
    head3 = NULL;

    head1 = create(head1); //creates the linked list
    printf("Polynomial 1 : ");
    print(head1);
    head2 = create(head2);
    printf("Polynomial 2 : ");
    print(head2);

    head3 = sum(head1, head2);
    printf("The sum of the two polynomials is : ");
    print(head3);

}


int print(struct Node *head)
{

    if(head==NULL)
    {
        printf("No polynomial present!\n");
    }
    else
    {
        struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
        temp = head;
        while(temp!=NULL)
        {
            printf("(%.1fx^%d)", temp->coefficient, temp->exponent);
            temp = temp->next;

            if(temp!=NULL)
                printf(" + ");
            else
                printf("\n");
        }
        printf("\n");
    }
}


struct Node* create(struct Node *head)
{
    int n;
    int exp;
    float coeff;

    printf("Enter the number of elements : ");
    scanf("%d", &n);

    for(int i = 0; i<n ; i++)
    {
        printf("Enter the coefficient for the term %d : ", i+1);
        scanf("%f", &coeff);

        printf("Enter the exponent for the term %d : ", i+1);
        scanf("%d", &exp);

        head = add(head, exp, coeff);
    }

    return head;
}

struct Node *add(struct Node *head, int exp, float coeff)
{
     struct Node *newP = (struct Node*)malloc(sizeof(struct Node));
     newP->next = NULL;
     newP->exponent = exp;
     newP->coefficient = coeff;

     if(head == NULL || head->exponent < newP->exponent)
     {
         newP->next = head;
         head = newP;
     }
     else
     {
         struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
         temp = head;

         while(temp->next!= NULL && temp->next->exponent > newP->exponent)
            temp = temp->next;

         newP->next = temp->next;
         temp->next = newP;
     }

     return head;
}


struct Node *sum(struct Node *head1,struct Node *head2)
{
    struct Node *ptr1 = (struct Node *)malloc(sizeof(struct Node));
    struct Node *ptr2 = (struct Node *)malloc(sizeof(struct Node));
    struct Node *head3 = (struct Node *)malloc(sizeof(struct Node));

    ptr1 = head1;
    ptr2 = head2;
    head3 = NULL;

    while(ptr1!= NULL && ptr2!=NULL)
    {
        if(ptr1->exponent == ptr2->exponent)
        {
            head3 = add(head3, ptr1->exponent, ptr1->coefficient+ptr2->coefficient);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        else if(ptr1->exponent > ptr2->exponent)
        {
            head3 = add(head3, ptr1->exponent, ptr1->coefficient);
            ptr1 = ptr1->next;
        }
        else if(ptr2->exponent > ptr1->exponent)
        {
            head3 = add(head3, ptr2->exponent, ptr2->coefficient);
            ptr2 = ptr2->next;
        }
    }

    while(ptr1!=NULL)
    {
        head3 = add(head3, ptr1->exponent, ptr1->coefficient);
        ptr1 = ptr1->next;
    }

    while(ptr2!=NULL)
    {
        head3 = add(head3, ptr2->exponent, ptr2->coefficient);
        ptr2 = ptr2->next;
    }
    return head3;
}
