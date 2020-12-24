#ifndef STRUCTS
#define STRUCTS
#include <string.h>
#include <math.h>

struct Node{
    char data[30];
    int count = 1;
    Node * next;
};

struct Array{
    Node * head[26];
};

// Functions

Node * newNode(char word[30])
{
    Node * node = new Node;
    strcpy(node->data, word);
    node->next = nullptr;
    return node;
};

Array * newArray()
{
    Array * a = new Array[26];
    for (int i = 0; i < 27; i++){
        a->head[i] = nullptr;
    }
    return a;
};

// Adds a word to the array
void addToArray(Array * array, char word[30])
{
    int index = (word[0])-97;
    if (index == -52 || index == -97){
        index = 26;
    }

    Node * current = array->head[index];

    if (array->head[index] == nullptr){
        array->head[index] = newNode(word);
    }
    else if (strcmp(current->data, word) == 0){
        current->count++;
        return;
    }
    else
    {
        while(true)
        {
            if (current->next != nullptr){
                if (strcmp(current->next->data, word) == 0){
                    current->next->count++;
                    return;
                }
            }
            else
            {
                break;
            }
            current = current->next;
        }
        current->next = newNode(word);
    }    
}

int getListLen(Node * head)
{
    int s = 0;
    Node * node = head;
    while(node){
        s++;
        node->next;
    }
    return s;
}

// Return 1 if word has an alphabetically lower value
// otherwise return 0
int stringcmp(char * word, char * word2)
{
    int max = fmax(strlen(word), strlen(word2));
    for (int i=0; i < max+1; i++){
        if (word[i] < word2[i])
            return 1;
        else if (word[i] > word2[i])
            return 0;
        else if (word[i] == '\0' && word2[i] != '\0')
            return 1;
        else if (word[i] != '\0' && word2[i] == '\0')
            return 0;
    }
    return 0;
}

// Compare two nodes
int compare(Node * a, Node * b)
{
    if (a->count > b->count)
        return 1;
    else if (a->count < b->count)
        return 0;
    else if (a->count == b->count){
        return stringcmp(a->data, b->data);
    }
    return 0;
}

// Merge the lists
Node * mergeSortedList(Node * a, Node * b)
{
    // Base case
    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    Node * result = nullptr;

    if (compare(a, b) == 1){
        result = a;
        result->next = mergeSortedList(a->next, b);
    }
    else
    {
        result = b;
        result->next = mergeSortedList(a, b->next);
    }
    return result;
}

// Splits the list
void splitList(Node * source, Node ** front, Node ** back)
{
    if (source == nullptr || source->next == nullptr){
        *front = source;
        *back = nullptr;
        return;
    }

    Node * slow = source;
    Node * fast = source->next;

    while(fast != nullptr){
        fast = fast->next;
        if (fast != nullptr){
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
    
}

void mergeSort(Node ** head)
{
    if ((*head == nullptr) || ((*head)->next == nullptr)){
        return;
    }

    Node * a;
    Node * b;

    splitList(*head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *head = mergeSortedList(a, b);
}


#endif