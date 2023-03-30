#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Function Definitions
void displayMenu();
void loadData();

struct listNode {
    char item_name[30];

    struct listNode *next;
    struct listNode *prev;
};
typedef struct listNode ListNode;

int main() {
    displayMenu();


}


void loadData(){
    ListNode* list1 = malloc(sizeof(ListNode));
    strcpy(list1->item_name, "Abey:");
    list1->next = NULL;
}
void displayMenu(){

    int choice;
    printf("Menu:\n ");
    printf("1. Display board:\n ");
    printf("2. Load board from a file:\n ");
    printf("3. Edit list: \n ");
    printf("4. Edit Board: \n ");
    printf("5. Save board to a file: \n ");
    printf("6. Quit: \n ");



    int flag=0;
    do{
        if(flag==0){
            printf("Enter your choice: \n");
            scanf("%d", &choice);
        }
        else{
            printf("Invalid Input. Please try again: \n");
            printf("Enter your choice: \n");
            scanf("%d", &choice);
        }
        flag++;
    }
    while(choice>6||choice<1);


}
