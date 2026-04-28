#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int num ;
    struct node *next;
    struct node *prev;
}node;

node * head = NULL;
node * tail = NULL;
int value;
int NumOfNode=0;
void creat (int n)
{
    for (int i = 1 ; i<=n; i++)
    {
        node *newnode = (node*)malloc (sizeof(node));
        printf("enter the value of node: %d\n", i);
        while(scanf("%d", &newnode->num) != 1)
        {
            printf("Invalid! enter a number: ");
            while(getchar() != '\n');
        }
        newnode->next= NULL;
        newnode->prev= NULL;
        if (head==NULL)
        {
            head= newnode;
            tail =newnode;
            head->prev = NULL;
        }
        else 
        {
            newnode->prev= tail;
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
        newnode->prev = NULL;
        NumOfNode++;
        return;
    }

    switch(choose)
    {
        case 1:
        newnode->next = head ;
        head->prev = newnode;
        head= newnode;
        NumOfNode++;
        break;
        case 2:
        tail->next =newnode;
        newnode->prev= tail;
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
                head->prev = newnode;
                newnode->prev = NULL;
                head= newnode;
                NumOfNode++;
                
            }
            else
            {
                node *temp = head;
                for (int i = 1 ;temp!= NULL && i < pos - 1 ;i++)
                temp =temp->next;
                newnode->next = temp-> next ;
                if(temp->next != NULL)
                    temp->next->prev = newnode;
                newnode->prev = temp;    
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
    int D;
    node * temp= head;
    node *ItemDelet;
    printf("Enter the position you want deleing:\n");
        while(scanf("%d", &D) != 1)
        {
            printf("Invalid! enter a number: ");
            while(getchar() != '\n');
        }
    
    if (D>0 && D<=NumOfNode)
    {
        if (D==1)
        {
            
          head = head -> next ;
          head->prev = NULL;
          free(temp);
          NumOfNode--;
        }
        else{
        
        for(int i =1 ; temp!=NULL&& i<D-1; i++)
        temp=temp->next;
        node *ItemDelet =temp->next;
        temp->next= ItemDelet->next;
        if(ItemDelet->next != NULL)
            ItemDelet->next->prev = temp;
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
    printf("The elements in the linked list are:\n");
    while(current!= NULL )
    {
        printf("%d\n",current -> num);
        current =current -> next ;
    } 
}
void Reverse()
{
    if (head == NULL)
        return;
    printf("The elements in the linked list are:\n");    
    node *current = tail;
    while(current != NULL)
    {
        printf("%d\n", current->num);
        current = current->prev;
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
            Reverse();
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