#ifndef FILE_INPUT
#define FILE_INPUT
#include <iostream>
#include <fstream>
#include <string.h>
#include "structs.h"



char* sanitise(char * word)
{
    char * cleanWord = new char[30];
    int pos = 0;
    for (int i =0; i < 30; i++){
        if (word[i] > 64 && word[i] < 91){
            cleanWord[pos++] = (word[i]+32);
        }
        if(word[i] > 96 && word[i] < 123){
            cleanWord[pos++] = word[i];
        }
        if (word[i] == 45){
            cleanWord[pos++] = word[i];
        }
        if (word[i] == '\0'){
            cleanWord[pos++] = '\0';
            return cleanWord;
        }     
    }
    return cleanWord;
}


Array* processFile(char * fileName)
{
    Array * array = newArray();
    std::ifstream file;
    file.open(fileName);
    if (file.fail()){
        std::cerr << "Failed to open file.";
        return array;
    }

    char word[30];
    while (file >> word)
    {
        addToArray(array, sanitise(word));
    }
    file.close();
    return array;
}

void testPrint(char * fileName)
{
    std::ifstream file;
    file.open(fileName);
    char word[30];
    while(file >> word)
    {
        std::cout << sanitise(word) << std::endl;
    }
}

void print(Array * a)
{
    Node * current;
    for (int i = 0; i < 26; i++){
        current = a->head[i];
        while (true){
            if (current == nullptr){
                std::cout << std::endl;
                break;
            }
            std::cout << current->data << " : " << current->count << " |  ";
            current = current->next;
        }
    }
}

void printNode(Node * a)
{
    while (true){
        if (a == nullptr){
            std::cout << std::endl;
            break;
        }
        std::cout << a->data << " : " << a->count << " |  ";
        a = a->next;
    }
}

#endif