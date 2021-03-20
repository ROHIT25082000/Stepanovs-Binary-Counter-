#include<stdio.h>
#include<stdlib.h>
#include"assignment_2.h"
#include<math.h>
// use -l flag for execution 

struct node     // Node of the list.
{
    int value;
    struct node * link;
};
typedef struct node Node;

struct List                     // List structure
{
    Node * head;
};
typedef struct List List;

void init(List*sll);            // Initializes the adjacency list.
void init(List*sll)
{
    sll->head = NULL;
}

int isNull(List*sll);
int isNull(List*sll)
{
    if(sll->head == NULL)
        return 1;
    else 
        return 0;
}

List * match(Node *first,Node * second);
void insert(List*sll,int v);
void cascade(List myList[],int i,int n,List * initiator);



void cascade(List myList[],int i,int n,List * initiator)
{
    if(i==n)
    {
        return;
    }
    if(myList[i].head==NULL)
    {
        myList[i] = *initiator;
        /*if(myList[i].head->link==NULL)
        {
            List * result = &myList[i];
            cascade(myList,i+1,n,result);
            myList[i].head = NULL;
        }*/
    }
    else if(myList[i].head!=NULL)
    {
        List * result = match(myList[i].head,initiator->head);
        myList[i].head = NULL;
        cascade(myList,i+1,n,result);
    }    
}
List * match(Node *first,Node * second)     //          Conducts the match between the elements and also prints the output
{
    Node * temp1 = first;
    Node * copy1 = first;
    Node * temp2 = second;
    Node * copy2 = second;

    List * newresult = (List*)malloc(sizeof(List));         //  used to generate a new list after the match is over 
    init(newresult);
    while(temp1!=NULL)
    {
        printf("%d ",temp1->value);
        temp1 = temp1->link;
    }
    printf(" x ");
    while(temp2!=NULL)
    {
        printf("%d ",temp2->value);
        temp2 = temp2->link;
    }
    printf(" =  ");

    if(copy1->value > copy2->value)         // generating the resultant array.
    {
        insert(newresult,copy1->value);
        insert(newresult,copy2->value);
        copy1 = copy1->link;
        while(copy1!=NULL)
        {
            insert(newresult,copy1->value);
            copy1 = copy1->link;
        }
    }
    else if(copy1->value < copy2->value)
    {
        insert(newresult,copy2->value);
        insert(newresult,copy1->value);
        copy2 = copy2->link;
        while(copy2!=NULL)
        {
            insert(newresult,copy2->value);
            copy2 = copy2->link;
        }
    }
    Node * ans = newresult->head;       // Displays the result 
    while(ans!=NULL)
    {
        printf("%d ",ans->value);
        ans = ans->link;
    }
    printf("\n");
    return newresult;
}
void insert(List*sll,int v)                             // insert the element in the linked list.
{

    Node * new = (Node *)malloc(sizeof(Node));
    new->value = v;
    new->link = NULL;
    if(sll->head==NULL)
    {
        sll->head = new;
        new->link = NULL;
    }
    else if(sll->head!=NULL)
    {
        Node * temp = sll->head;
        while(temp->link!=NULL)
        {
            temp = temp->link;
        }
        temp->link = new;
    }
}

void find_second_greatest(int *numbers, int length)
{
    int boxSize = (int)ceil((log(length)/log(2)));
    int actual = boxSize+1;                                                        
    int n = actual;

    List myList[n];
    for(int i=0;i<n;i++)        // creates an array of pointer of the size (log n) so is used for the and the lists can upto log n size 
    {                           // so it proportional to log n ^2.
        init(&myList[i]);
    }
    for(int i=0;i<length;i++)
    {
        int element = numbers[i];
        if(1==isNull(&myList[0]))           // inserts the new element in the start of the list in the array of list
        {
            insert(&myList[0],element);
            if(i== length-1 && length%2==1)
            {
                Node * new = (Node *)malloc(sizeof(Node));
                new->value = element;
                new->link = NULL;
                List * result = (List*)malloc(sizeof(List));
                result->head = new;
                myList[0].head = NULL;
                cascade(myList,1,n,result);
            }
            
        }
        else if(0==isNull(&myList[0]))
        {
            Node * new = (Node *)malloc(sizeof(Node));
            new->value = element;
            new->link = NULL;
            List * result = match(myList[0].head,new);
            myList[0].head = NULL;
            cascade(myList,1,n,result);
        }
    }
    int x = 0;                                          // flush the array of pointers to know 
    int i =0;                                           // the answer and also make sure  nothing is left out 
    for(i=1;i<n-1;i++)
    {
        if(myList[i].head!=NULL)
        {
            x++;
            cascade(myList,i+1,n,&myList[i]);
        }
        
    }
   // printf("%d",x);
    //printf("Answer\n");
    Node * tell = myList[n-1].head->link;       // does the last n - 2 comparision for the second max , 
    int max = tell->value;                      //thats why I skipped first element in last list.
    while(tell!=NULL)
    {
        if(tell->value > max)
        {
            max = tell->value;
        }
        tell = tell->link;
    }
    printf("\n%d\n",max);       // prints the second largest element.
}




