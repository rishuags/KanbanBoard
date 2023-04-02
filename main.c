#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Function Definitions
void displayMenu();
void displayBoard();
void loadData();

struct listNode {

    char user_name[30];
    struct item*first_item;

    struct listNode *next;
    struct listNode *prev;
};
typedef struct listNode ListNode;

struct item{
    char item_name[30];

    struct item *next;
    struct item *prev;
};
typedef struct item Item;

int main() {
    displayMenu();
    return 0;
}


/*void loadData(){
    ListNode* list1 = malloc(sizeof(ListNode));
    strcpy(list1->item_name, "Abey:");
    list1->next = NULL;
}*/
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
            printf("Enter your choice(1-5): ");
            scanf("%d", &choice);
        }
        else{
            printf("Invalid Input. Please try again: \n");
            printf("Enter your choice(1-5): ");
            scanf("%d", &choice);
        }
        flag++;
    }
    while(choice>6||choice<1);

    if(choice == 1){
        displayBoard();
    }


}

void displayBoard(){

    ListNode *name1 = malloc(sizeof(ListNode));
    strcpy(name1-> user_name, "Abey");
    name1->next = NULL;

    Item*item1_1 = malloc(sizeof(Item));
    strcpy(item1_1->item_name,"Oculus Pro");
    Item*item1_2 = malloc(sizeof(Item));
    strcpy(item1_2->item_name,"Oculus Quest 1");

    item1_2->next = NULL;
    name1->first_item = item1_1;
    item1_1->next = item1_2;

    ListNode *name2 = malloc(sizeof(ListNode));
    strcpy(name2-> user_name, "Dante");
    name2->next = name1;

    Item*item2_1 = malloc(sizeof(Item));
    strcpy(item2_1->item_name,"Oculus Quest 1");
    Item*item2_2 = malloc(sizeof(Item));
    strcpy(item2_2->item_name,"3070 RTX");

    item2_2->next = NULL;
    name2->first_item = item2_1;
    item2_1->next = item2_2;

     ListNode *name3 = malloc(sizeof(ListNode));
    strcpy(name3->user_name,"Tim");
    name3->next = name2;

    Item*item3_1 =malloc(sizeof(Item));
    strcpy(item3_1->item_name,"Oculus Quest 2");
    name3 ->first_item = item3_1;
    item3_1->next = NULL;

    ListNode*name4 = malloc(sizeof(ListNode));
    strcpy(name4->user_name, "Nick");
    name4->next = name3;

    Item* item4_1 = malloc(sizeof(Item));
    strcpy(item4_1->item_name, "3070 RTX");

    name4->first_item = item4_1;
    item4_1->next = NULL;

    name4->first_item = item4_1;
    name4->next = name3;
    name1->prev = name2;
    name2->prev = name3;
    name3->prev = name4;
    name4->prev = NULL;

    ListNode* current_node = name4;
    Item* current_item;

while (current_node != NULL) {
    printf("\n");
    printf("%s:\n", current_node->user_name);

    current_item = current_node->first_item;
    while (current_item != NULL) {
        printf("    %s\n", current_item->item_name);
        current_item = current_item->next;
    }

    current_node = current_node->next;
}

}

