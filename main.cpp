#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "fileInput.h"
#include "structs.h"

// Main
int main(int argc, char *argv[])
{
    Array * array = processFile(argv[1]);
    for (int i = 0; i < 26; i++){
        mergeSort(&(array)->head[i]);
        printNode(array->head[i]);
    }
    return 0;
}

