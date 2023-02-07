/********************************************************************************* 
* Alfonso Luis Del Rosario, 1698802
* 2023 Winter CSE101 PA3
* List.c
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"

typedef struct NodeObj* Node;

typedef struct NodeObj{
    ListElement data;
    Node prev;
    Node next;
}NodeObj;

typedef struct ListObj { //member variables
    Node front;
    Node back;
    Node cursor;
    int index;
    int length;
}ListObj;

// Constructors-Destructors ---------------------------------------------------

List newList(void)
{
    List L = malloc(sizeof(ListObj));
    assert(L!=NULL);
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;   
    L->index = -1;
    L->length = 0;
    return L;
}

void freeList(List* pL) //fix
{
    Node curr = (*pL)->front;

    if(*pL == NULL)
    {
        printf("List Error: calling freeList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(pL != NULL && *pL != NULL)
    {
        while(curr!=NULL)
        {
            Node delete_node = curr;
            curr=curr->next;
            free(delete_node);
            delete_node = NULL;
        }
        curr=NULL;
        free(*pL);
        (*pL)=NULL;
    }
}

// Access functions -----------------------------------------------------------

int length(List L)
{   
    if(L == NULL)
    {
        printf("List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

int index(List L)
{
    if(L == NULL)
    {
        printf("List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->index >= 0)
    {
        return L->index;
    }
    return -1;
}

int front(List L)
{
    if(L==NULL)
    {
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->length <= 0)
    {
        printf("List Error: calling front() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    return L->front->data;
}

int back(List L)
{
    if(L==NULL)
    {
        printf("List Error: calling back() on NULL List reference\n");   
        exit(EXIT_FAILURE);

    }

    if(L->length <= 0)
    {
        printf("List Error: calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    return L->back->data;
}

int get(List L)
{
    if(L==NULL)
    {
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->length > 0 && index(L) >= 0)
    {
        return L->cursor->data;
    }

    return -1;  
    
} //QUESTION: when get is called with no cursor or empty list

bool equals (List A, List B)
{
    if(A == NULL || B == NULL) 
    {
        printf("List Error: calling equals() on NULL List reference(s)\n");
        exit(EXIT_FAILURE);
    }

    if(A->length != B->length)
    {
        return false;
    }
    
    int index = 0;
    int length = A->length;
    Node tempA = A->front, tempB = B->front;
    while(index != length)
    {
        if(tempA->data != tempB->data)
        {
            return false;
        }
        tempA = tempA->next; 
        tempB = tempB->next;
        index++;
    }

    return true;
} 

// Manipulation procedures ----------------------------------------------------

void clear(List L)
{
    if(L==NULL)
    {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->length > 0)
    {
        Node curr = L->front;
        while(curr != NULL)
        {
            Node delete_node = curr;
            curr = curr->next;
            free(delete_node);
            delete_node = NULL;
        }
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->length = 0;
        L->index = -1;
    }
}

void set(List L, int x)
{
    if(L==NULL)
    {
        printf("List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    if(L->length > 0 && L->index >= 0)
    {
        L->cursor->data = x;
    }
}//QUESTION: output if length = 0 or index = -1

void moveFront(List L)
{
    if(L==NULL)
    {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->length > 0)
    {
        L->cursor = L->front;
        L->index = 0;
    }
}//QUESTION: output if length == 0

void moveBack(List L)
{
    if(L==NULL)
    {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->length > 0)
    {
        L->cursor = L->back;
        L->index = L->length-1;
    }
}//QUESTION: output if length == 0

void movePrev(List L)
{
    if(L==NULL)
    {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor != NULL)
    {
        if(L->cursor == L->front)
        {
            L->cursor = NULL;
            L->index = -1;
        }
        else
        {
            L->cursor = L->cursor->prev;
            L->index--;
        }
    }
}

void moveNext(List L)
{
    if(L==NULL)
    {
        printf("List Error: calling moveNext() on NULL List reference\n");
    }

    if(L->cursor != NULL)
    {
        if(L->cursor == L->back)
        {
            L->cursor = NULL;
            L->index = -1;
        }
        else
        {
            L->cursor = L->cursor->next;
            L->index++;
        }
    }
}

void prepend(List L, int x)
{
    if(L==NULL)
    {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node new_node = malloc(sizeof(NodeObj));
    new_node->data = x;
    new_node->next = new_node->prev = NULL;

    if(L->index >= 0)
    {
        L->index++;
    }

    if(L->length > 0)
    {
        new_node->next = L->front;
        L->front->prev = new_node;
        L->front = new_node;
    }
    else
    {
        L->front = L->back = new_node;  
    }

    L->length++;
}
 
void append(List L, int x)
{
    if(L==NULL)
    {
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node new_node = malloc(sizeof(NodeObj));
    new_node->data = x;
    new_node->prev = new_node->next = NULL;

    if(L->length > 0)
    {
        new_node->prev = L->back;
        L->back->next = new_node;
        L->back = new_node;
    }
    else
    {
        L->front = L->back = new_node;
    }

    L->length++;
}

void insertBefore(List L, int x)
{
    if(L==NULL)
    {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->index == 0)
    {
        prepend(L,x);
        return;
    }

    if(L->length > 0 && L->index >= 0)
    {
        Node new_node = malloc(sizeof(NodeObj));
        new_node->data = x;
        new_node->next = L->cursor;
        new_node->prev = L->cursor->prev;
        new_node->prev->next = new_node;
        L->cursor->prev = new_node;
        L->index++;
        L->length++;
    }
} //QUESTION: output if function called but no cursor

void insertAfter(List L, int x)
{

    if(L==NULL)
    {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->index == L->length-1)
    {
        append(L, x);
        return;
    }

    if(L->length > 0 && L->index >= 0)
    {
        Node new_node = malloc(sizeof(NodeObj));
        new_node->data = x;
        new_node->next = L->cursor->next;
        new_node->prev = L->cursor;
        L->cursor->next = new_node;
        new_node->next->prev = new_node;
        L->length++;
    }
} //QUESTION: output if function called but no cursor

void deleteFront(List L) 
{   
    if(L==NULL)
    {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->length > 0)
    {
        if(L->index <= 0)
        {
            L->cursor = NULL;
            L->index = -1;
        }
        else 
        {
            L->index--;
        }

        if(L->length == 1)
        {
            Node delete_node = L->front;
            L->front = NULL;
            L->back = NULL;
            free(delete_node);
            delete_node = NULL;
            L->length--;
        }
        else
        {
            Node delete_node = L->front;
            L->front = L->front->next;
            L->front->prev = NULL;
            free(delete_node);
            delete_node = NULL;
            L->length--;
        }
    }
}

void deleteBack(List L)
{
    if(L==NULL)
    {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->length > 0)
    {
        if(L->index == length(L)-1)
        {
            L->index = -1;
            L->cursor = NULL;
        }

        if(L->length == 1)
        {
            Node delete_node = L->back;
            L->back = NULL;
            L->front = NULL;
            free(delete_node);
            delete_node = NULL;
            L->length--;
        }
        else
        {
            Node delete_node = L->back;
            L->back = L->back->prev;
            L->back->next = NULL;
            free(delete_node);
            delete_node = NULL;
            L->length--;
        }
    }
}

void delete(List L)
{
    if(L==NULL)
    {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->index == 0)
    {
        deleteFront(L);
        return;
    }

    if(L->index == L->length-1)
    {
        deleteBack(L);
        return;
    }

    if(L->length != 0 && L->index >= 0)
    {
        Node curr_node = L->cursor;
        Node next_node = L->cursor->next;
        Node prev_node = L->cursor->prev;

        prev_node->next = next_node;
        next_node->prev = prev_node;
        free(curr_node);

        curr_node = prev_node = next_node = NULL;

        L->cursor = NULL;
        L->index = -1;
        L->length--;
    }
    return;
}

void printList(FILE* out, List L)
{
    if(L==NULL)
    {
        printf("List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->length > 0)
    {
        Node temp = L->front;
        while(temp != NULL)
        {
            fprintf(out, "%d ", temp->data);
            temp = temp->next;
        }
        temp = NULL;
    }
}

List copyList(List L)
{
    if(L==NULL)
    {
        printf("List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->length <= 0)
    {
        List empty_list = newList();
        return empty_list;
    }

    int saved_state = L->index;

    List new_list = newList();
    new_list->index = -1;

    moveFront(L);
    for(int i = 0; i < L->length; i++)
    {
        append(new_list, get(L));
        moveNext(L);
    }

    if(saved_state == -1)
    {
        L->index = -1;
        L->cursor = NULL;
    }
    else
    {
        int i = 0;
        moveFront(L);
        while(i!=saved_state)
        {
            moveNext(L);
        }
    }

    return new_list;
}

