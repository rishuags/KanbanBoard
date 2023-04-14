#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX_LIST_NAME_LENGTH 50
#define MAX_ITEM_NAME_LENGTH 50
#define MAX_LENGTH 1000
#define MAX_NUMBER_OF_LISTS 100
#define MAX_NUMBER_OF_ITEMS 100

typedef struct Item{
    char itemName[MAX_ITEM_NAME_LENGTH];

    struct Item *nextItem;
    struct Item *prevItem;

}Item;

typedef struct List{
    char listName[MAX_LIST_NAME_LENGTH];

    struct Item *firstItem;

    struct List *nextList;
    struct List *prevList;

}List;

bool search(struct List* headOfList, char* searchName);

int main()
{
List *list1 = malloc(sizeof(List));
strcpy(list1->listName, "Abey:");
list1->nextList=NULL;
list1->prevList = NULL;
list1->firstItem = NULL;

Item *item1_1 = malloc(sizeof(Item));
strcpy(item1_1->itemName,"Oculus Pro");
Item *item1_2 = malloc(sizeof(Item));
strcpy(item1_2->itemName, "Oculus Quest 1");

item1_1->nextItem=item1_2; // Set nextItem of item1_1 to item1_2
item1_2->nextItem=NULL; // Set nextItem of item1_2 to NULL

list1->firstItem=item1_1;


List *list2 = malloc(sizeof(List));
strcpy(list2->listName, "Dante:");
list2->nextList=list1;
list2->prevList = NULL;
list2->firstItem = NULL;

Item *item2_1 = malloc(sizeof(Item));
strcpy(item2_1->itemName, "Oculus Quest 1");
Item *item2_2  = malloc(sizeof(Item));
strcpy(item2_2->itemName, "3070 RTX");

item2_1->nextItem=item2_2; // Set nextItem of item2_1 to item2_2
item2_2->nextItem = NULL; // Set nextItem of item2_2 to NULL

list2->firstItem=item2_1;


List *list3 = malloc(sizeof(List));
strcpy(list3->listName, "Tim:");
list3->nextList=list2;
list3->prevList = NULL;
list3->firstItem = NULL; // Set firstItem to NULL initially


Item *item3_1 = malloc(sizeof(Item));
strcpy(item3_1->itemName, "Oculus Quest 2");

item3_1->nextItem=NULL; // Set nextItem of item3_1 to NULL

list3->firstItem=item3_1;


List *list4 = malloc(sizeof(List));
strcpy(list4->listName, "Nick:");
list4->nextList=list3;
list4->prevList = NULL;
list4->firstItem = NULL; // Set firstItem to NULL initially

Item *item4_1 = malloc(sizeof(Item));
strcpy(item4_1->itemName, "3070 RTX");

item4_1->nextItem=NULL; // Set nextItem of item4_1 to NULL

list4->firstItem=item4_1;

char searchName[30];
    printf("Enter the name of the list to edit:\n");
    scanf("%s", searchName);
   // struct List* list4 = NULL;  // Initialize list4 to NULL

    bool listFound = search(list4, searchName);
if (listFound) {
    printf("Yes\n");
} else {
    printf("No\n");
}
    return 0;
}

bool search(struct List* headOfList, char* searchName)
{
    struct List* current = headOfList; // Start from the head of the list
    while (current != NULL) {
        if (strcmp(current->listName, searchName) == 0)
            return true;
        current = current->nextList;
    }
    return false;
}



    current_node = current_node->next;
}

}

