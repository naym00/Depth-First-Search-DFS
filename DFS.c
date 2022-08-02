#include<stdio.h>
#include<string.h>
#include<stdbool.h>

typedef struct _node
{
    int data;
    struct _node *next;
    struct _node *previous;
} node;

typedef struct _nodeCarrier
{
    int identifier;
    bool isVisited;
    node *head;
    node *last;
    struct _nodeCarrier *next;
} nodeCarrier;
nodeCarrier *root = NULL, *last = NULL;

nodeCarrier *findIdentifier(int identifier)
{
    nodeCarrier *temporary = root;
    if(temporary!=NULL)
    {
        while(temporary!=NULL)
        {
            if(temporary->identifier == identifier)
            {
                break;
            }
            temporary = temporary->next;
        }
    }
    return temporary;
}

void extend_nodeCarrier(int identifier)
{
    nodeCarrier *newNode = (nodeCarrier*)malloc(sizeof(nodeCarrier));
    newNode->identifier = identifier;
    newNode->isVisited = false;
    newNode->head = NULL;
    newNode->last = NULL;
    newNode->next = NULL;

    if(root==NULL)
    {
        root=newNode;
        last=newNode;
    }
    else
    {
        last->next = newNode;
        last = newNode;
    }
}

void setIsVisitedDefaultValue()
{
    nodeCarrier *temporary = root;
    if(temporary != NULL)
    {
        while(temporary != NULL)
        {
            temporary->isVisited = false;
            temporary = temporary->next;
        }
    }
    else
    {
        printf("Root is NULL!\n");
    }
}

void insertSingle(int data, node **head, node **last)
{
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->previous = NULL;

    if(*head == NULL)
    {
        *head = newNode;
        *last = newNode;
    }
    else
    {
        newNode->previous = *last;
        (*last)->next = newNode;
        *last = newNode;
    }
}
void deleteLast(node **head, node **last)
{
    if(*head != NULL)
    {
        if(*head == *last)
        {
            *head = NULL;
            *last = NULL;
        }
        else if(*head == (*last)->previous)
        {

            (*head)->next = NULL;
            *last = *head;
        }
        else
        {
            (*last)->previous->next = NULL;
            *last = (*last)->previous;
        }
    }
    else
    {
        printf("Nothing To Delete!");
    }
}

void printLinkList(node **head, node **last, bool flag)
{
    if(head != NULL && last != NULL)
    {
        if(flag)
        {
            node *print = *head;
            while(print != NULL)
            {
                if(print->next == NULL)
                {
                    printf("%d\n", print->data);
                }
                else
                {
                    printf("%d ", print->data);
                }
                print = print->next;
            }
        }
        else
        {
            node *print = *last;
            while(print != NULL)
            {
                if(print->previous == NULL)
                {
                    printf("%d\n", print->data);
                }
                else
                {
                    printf("%d ", print->data);
                }
                print = print->previous;
            }
        }
    }
    else
    {
        printf("Link List is Empty!\n");
    }
}

void insertString(char string[], int identifier)
{
    int i, data = 0;

    nodeCarrier *temporary = findIdentifier(identifier);
    if(temporary!=NULL)
    {
        for(i=0; string[i]!='\0'; i++)
        {
            if(string[i]>='0' && string[i]<='9')
            {
                data = data*10 + string[i] - '0';
            }
            else
            {
                insertSingle(data, &(temporary->head), &(temporary->last));
                data = 0;
            }
        }
    }
    else
    {
        printf("Root is NULL or Node doesn't exist!\n");
    }
}

void TraverseDFS(int startNode, node **resulthead, node **resultlast)
{
    nodeCarrier *nodePtr = findIdentifier(startNode);
    if(nodePtr != NULL)
    {
        node *stackhead = NULL, *stacklast = NULL;
        insertSingle(startNode, &stackhead, &stacklast);
        insertSingle(startNode, &(*resulthead), &(*resultlast));
        nodePtr->isVisited = true;
        while(stacklast!=NULL)
        {
            node *ptr = findIdentifier(stacklast->data)->head;
            while(ptr!=NULL)
            {
                nodeCarrier *temporary = findIdentifier(ptr->data);
                if(temporary->isVisited == false)
                {
                    insertSingle(ptr->data, &stackhead, &stacklast);
                    insertSingle(ptr->data, &(*resulthead), &(*resultlast));
                    temporary->isVisited = true;
                    break;
                }
                ptr = ptr->next;
            }
            if(ptr == NULL)
            {
                deleteLast(&stackhead, &stacklast);
            }
        }
        setIsVisitedDefaultValue();
    }
    else
    {
        printf("Starting Node(%d) is Invalid!\n", startNode);
    }
}

int main()
{
    int i, totalNodes = 16, startNode = 1;
    for(i=1; i<=totalNodes; i++)
    {
        extend_nodeCarrier(i);
    }
    insertString("2,6,", 1);
    insertString("1,7,11,", 2);
    insertString("4,7,", 3);
    insertString("3,8,", 4);
    insertString("6,9,11,", 5);
    insertString("1,5,11,", 6);
    insertString("2,3,12,", 7);
    insertString("4,15,", 8);
    insertString("5,10,", 9);
    insertString("9,13,14,", 10);
    insertString("2,5,6,14,", 11);
    insertString("7,14,", 12);
    insertString("10,16,", 13);
    insertString("10,11,12,15,16,", 14);
    insertString("8,14,", 15);
    insertString("13,14,", 16);

    node *resulthead = NULL, *resultlast = NULL;
    TraverseDFS(1, &resulthead, &resultlast);
    printLinkList(&resulthead, &resultlast, true);

    return 0;
}

//    Another Input
//    insertString("2,3,", 1);
//    insertString("1,", 2);
//    insertString("1,4,7,", 3);
//    insertString("3,5,6,", 4);
//    insertString("4,", 5);
//    insertString("4,9,", 6);
//    insertString("3,", 7);
//    insertString("9,", 8);
//    insertString("6,8,10,", 9);
//    insertString("9,", 10);

