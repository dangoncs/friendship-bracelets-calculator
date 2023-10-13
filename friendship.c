#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 100

typedef struct Node {
    char letter;
    int quantity;
    struct Node *next;
} Node;

Node *createNode(char letter) {
    Node *new = (Node *) malloc(sizeof(Node));
    if(new == NULL) {
        perror("Falha na execução do programa");
        exit(1);
    }

    new->letter = letter;
    new->quantity = 1;
    new->next = NULL;
    return new;
}

Node *searchNode(Node *list, char letter) {
    if(list == NULL)
        return NULL;

    if(list->letter == letter)
        return list;
    
    return searchNode(list->next, letter);
}

void insertNode(Node **list, char letter) {
    if(*list == NULL) {
        *list = createNode(letter);
        //printf("Inserting %c (%d) - 1st node\n", letter, letter);
        return;
    }

    if(letter < (*list)->letter) {
        //printf("inserting %c (%d) before %c (%d)\n", letter, letter, (*list)->letter, (*list)->letter);
        Node *new = createNode(letter);
        new->next = *list;
        *list = new;
        return;
    }

    Node *current = *list;
    Node *previous = *list;
    while(current != NULL) {
        if(letter < current->letter)
            break;
        
        previous = current;
        current = current->next;
    }

    //printf("inserting %c (%d) after %c (%d)\n", letter, letter, previous->letter, previous->letter);
    Node *new = createNode(letter);
    new->next = current;
    previous->next = new;
}

void printInfo(Node *list) {
    int total = 0;

    printf("According to our calculations, you are going to need for your bracelet:\n");
    while(list != NULL) {
        if(list->quantity == 1)
            printf("%c: 1 bead\n", list->letter);
        else
            printf("%c: %d beads\n", list->letter, list->quantity);

        total += list->quantity;
        list = list->next;
    }
    
    printf("Total: %d beads\n", total);
}

int main() {
    char buffer[BUFFER_SIZE];
    Node *charactersList = NULL;

    printf("============= FRIENDSHIP BRACELETS CALCULATOR  =============\n");
    printf("Type the words that you want to write using beads, pressing Enter after each word.\n");
    printf("Once you've finished typing all words, press 0 and Enter.\n");
    fgets(buffer, BUFFER_SIZE, stdin);

    while(strcmp(buffer, "0\n")) {
        int size = strlen(buffer);
        for(int i = 0; i < size; i++) {
            if(buffer[i] == '\n')
                break;

            if(buffer[i] > ' ') {
                Node *searchResult = searchNode(charactersList, toupper(buffer[i]));
                if(searchResult == NULL)
                    insertNode(&charactersList, toupper(buffer[i]));
                else
                    searchResult->quantity++;
            }
        }

        printf("Okay! You can continue typing new words, or press 0 and Enter to view your results now.\n");
        fgets(buffer, BUFFER_SIZE, stdin);
    }

    printInfo(charactersList);

    return 0;
}