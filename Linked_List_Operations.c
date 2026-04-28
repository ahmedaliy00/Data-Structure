#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int num ;
    struct node *next;
}node;

node * head = NULL;
node * tail = NULL;
int value;
int NumOfNode=0;
void creat (int n)
{
    for (int i = 1 ; i<=n; i++)
    {
        node *newnode = malloc (sizeof(node));
        printf("enter the value of node: %d\n", i);
        while(scanf("%d", &newnode->num) != 1)
        {
            printf("Invalid! enter a number: ");
            while(getchar() != '\n');
        }
        newnode->next= NULL;
        if (head==NULL)
        {
            head= newnode;
            tail =newnode;
        }
        else 
        {
            tail->next= newnode;
            tail= newnode;
        }
    }
    NumOfNode=n;
}
void insert(int newItems)
{
    int choose ;
    printf("would you like insert your node?\n1-in the first:\n2-in the last: \n3-specific position you want\n");
    while(scanf("%d", &choose) != 1)
    {
        printf("Invalid! enter a number: ");
        while(getchar() != '\n');
    }
    node * newnode = malloc(sizeof(node));
    newnode -> num = newItems;
    if (head==NULL)
    {
        head= newnode;
        tail =newnode;
        newnode->next = NULL;
        NumOfNode++;
        return;
    }

    switch(choose)
    {
        case 1:
        newnode->next = head ;
        head= newnode;
        NumOfNode++;
        break;
        case 2:
        tail->next =newnode;
        newnode->next=NULL;
        tail=newnode;
        NumOfNode++;
        break;
        case 3:
        int pos;
        printf("Enter the position you want isert to : ");
        while(scanf("%d", &pos) != 1)
        {
            printf("Invalid! enter a number: ");
            while(getchar() != '\n');
        }

        if (pos >0 && pos<= NumOfNode+1)
            if(pos==1)
            {
                newnode->next = head ;
                head= newnode;
                NumOfNode++;
                
            }
            else
            {
                node *temp = head;
                for (int i = 1 ;temp!= NULL && i < pos - 1 ;i++)
                temp =temp->next;
                newnode->next = temp-> next ;
                temp->next =newnode;
                NumOfNode++;
               
            }
        else
        printf("you choose wrong position try again\n");
        break;
        default:
        printf("your choose is very wrong.......try again ya sedy\n");

    }
}
void Deletion()
{
    int d;
    node * temp= head;
    node *ItemDelet;
    printf("Enter the position you want deleing:\n");
        while(scanf("%d", &d) != 1)
        {
            printf("Invalid! enter a number: ");
            while(getchar() != '\n');
        }
    
    if (d>0 && d<=NumOfNode)
    {
        if (d==1)
        {
          head = head -> next ;
          free(temp);
          NumOfNode--;
        }
        else{
        
        for(int i =1 ; temp!=NULL&& i<d-1; i++)
        temp=temp->next;
        node *ItemDelet =temp->next;
        temp->next= ItemDelet->next;
        NumOfNode--;
        free(ItemDelet);
        }

    }
    else
    printf("you choose wrong position try again\n");

}

void Display()
{
    node *current =head ;
    while(current!= NULL )
    {
        printf("%d\n",current -> num);
        current =current -> next ;
    } 
}
void DisplayReverse(node *current)
{
    if (current == NULL)  // Base case
        return;
    
        DisplayReverse(current->next);
        printf("-> %d", current->num);  
}
int main ()
{ 
    int nodes;
    printf("Enter the number of nodes you want: ");
    while(scanf("%d", &nodes) != 1)
        {
            printf("Invalid! enter a number: ");
            while(getchar() != '\n');
        }
    creat(nodes);
    int newItems,choose;
    do
    {
        printf("Enter the process you want to do with your linked list: \n1-insert new node\n2-deletion\n3-display reverse\n4-exit\n");
        while(scanf("%d", &choose) != 1)
        {
            printf("Invalid! enter a number: ");
            while(getchar() != '\n');
        }
        switch(choose)
        {
            case 1:
            printf("Enter the value of new node: ");
            while(scanf("%d", &newItems) != 1)
            {
                printf("Invalid! enter a number: ");
                 while(getchar() != '\n');
            }

            insert(newItems);
            Display();
            break;
            case 2:
            Deletion();
            Display();
            break;
            case 3:
            DisplayReverse(head);
            printf("\n");
            break;
            case 4:
            free(head);
            free(tail);
            printf("Exiting the program...\n");
            break;
            default:
            printf("Invalid choice, please try again.\n");
        }
       
        
    } while (choose != 4);
    return 0;
}