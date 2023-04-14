#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_LIST_NAME_LENGTH 100
#define MAX_ITEM_NAME_LENGTH 100
#define MAX_LENGTH 100
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

typedef struct Board{
    struct List *firstList;
}Board;


//Making Default Board Global


//Making List Global
List *headOfList;

Board *myBoard;

//Function Definitions
void mainMenu();
void displayBoard(List *listHead);
void useSampleBoard();
void loadFile();
void editList();
void addItem(List *currentListPtr);
bool search(struct List* headOfList, char* searchName);

//Main Function
int main(void){

    mainMenu();
}

//Displays Initial Menu
void mainMenu(){

    int choice; //"choice" is the variable used to allow the user to choose the operation to perform

    //Running Main Menu until quit is entered
    do{
        //Printing Menu
        printf("\nMenu:\n ");
        printf("1. Display board:\n ");
        printf("2. Load board from a file:\n ");
        printf("3. Edit list: \n ");
        printf("4. Edit Board: \n ");
        printf("5. Save board to a file: \n ");
        printf("6. Quit: \n");

        printf("Enter your choice(1-6):\n");

        //Error Handling to invalidate incorrect entries
        int flag=0; //counts number of times the exit condition for do-while loop not met
        do{
            if(flag==0){
                while(scanf("%d", &choice)==0) //while scanf does not scan an integer
                {
                    printf("Invalid Input. Please try again: \n");
                    int c;
                    while((c=getchar())!='\n' && c!=EOF); //clearing the standard input
                }
            }
            else{
                printf("Invalid Input. Please try again: \n");
                while(scanf("%d", &choice)==0) //while scanf does not scan an integer
                {
                    printf("Invalid Input. Please try again: \n");
                    int c;
                    while((c=getchar())!='\n' && c!=EOF); //clearing the standard input
                }
            }
            flag++;
        }
        while(choice>6||choice<1);
        //printf("%d", choice); (Testing)

        //Choosing Function to run depending on choice entered by user
        switch(choice) {
            case 1:
                useSampleBoard();
                break;
            case 2:
                loadFile();
                break;
            case 3:
                //printf("Edit List: \n");
                editList();
                break;
            case 4:
                printf("Edit Board: \n");
                break;
            case 5:
                printf("Save Board to a file: \n");
                break;

            default:
                printf("\nQuitting...\n");
        }
    }
    while(choice!=6);

    printf(" \"¯\\_(ツ)_/¯\"");

    exit(0);

}

//Allows user to use a sample board
void useSampleBoard(){
    List *list1 = malloc(sizeof(List));
    strcpy(list1->listName, "Abey:");
    list1->nextList=NULL;

    Item *item1_1 = malloc(sizeof(Item));
    strcpy(item1_1->itemName,"Oculus Pro");
    Item *item1_2 = malloc(sizeof(Item));
    strcpy(item1_2->itemName, "Oculus Quest 1");

    item1_2->nextItem=NULL;
    list1->firstItem=item1_1;
    item1_1->nextItem=item1_2;


    List *list2 = malloc(sizeof(List));
    strcpy(list2->listName, "Dante:");
    list2->nextList=list1;

    Item *item2_1 = malloc(sizeof(Item));
    strcpy(item2_1->itemName, "Oculus Quest 1");
    item2_1->nextItem = NULL;
    Item *item2_2  = malloc(sizeof(Item));
    strcpy(item2_2->itemName, "3070 RTX");
    item2_2->nextItem =NULL;

    list2->firstItem=item2_1;
    item2_1->nextItem=item2_2;

    List *list3 = malloc(sizeof(List));
    strcpy(list3->listName, "Tim:");
    list3->nextList=list2;

    Item *item3_1 = malloc(sizeof(Item));
    strcpy(item3_1->itemName, "Oculus Quest 2");
    list3->firstItem=item3_1;
    item3_1->nextItem=NULL;


    List *list4 = malloc(sizeof(List));
    strcpy(list4->listName, "Nick:");
    Item *item4_1 = malloc(sizeof(Item));
    strcpy(item4_1->itemName, "3070 RTX");
    item4_1->nextItem=NULL;

    list4->firstItem=item4_1;
    list4->nextList=list3;
    list1->prevList = list2;
    list2->prevList = list3;
    list3->prevList = list4;
    list4->prevList = NULL;

    displayBoard(list4);


    //Printing Board (Within Function)
    //List *currentList;
    //Item *currentItem;
    //currentList=list4;
    /*while (currentList != NULL) {
        printf("\n");
        printf("%s:\n", currentList->listName);

        currentItem = currentList->firstItem;
        while (currentItem != NULL) {
            printf("    %s\n", currentItem->itemName);
            currentItem = currentItem->nextItem;
        }

        currentList = currentList->nextList;
    }*/

}

//Displays a board
void displayBoard(List *listHead){

    printf("/*************************************************************/\n");
    printf("Displaying Board...\n\n");

    if(listHead==NULL){
        printf("Board is Empty: \n");
        exit(0);

    }
    List *currentListPtr=NULL;
    currentListPtr = listHead;

    while(currentListPtr!=NULL){
        //Printing List Name
        printf("%s\n", currentListPtr->listName);

        if(currentListPtr->firstItem==NULL){
            printf("List is Empty: \n");
            exit(0);
        }
        Item *currentItemPtr = NULL;
        currentItemPtr = currentListPtr->firstItem;

        //Printing Items Names
        while(currentItemPtr!=NULL){
            printf("\t%s\n", currentItemPtr->itemName);
            currentItemPtr=currentItemPtr->nextItem;
        }

        currentListPtr=currentListPtr->nextList;
    }
    printf("/*************************************************************/\n\n");
}

//Loading File
void loadFile(){
    printf("Loading Board File... \n\n");

    FILE *fp;
    //Opening File
    fp = fopen("Board.txt", "r");

    //Error Handling File
    if(fp==NULL){
        printf("Error: Failed to Open the File\n");
    }

    //Storing the File Contents in an 3D Array
    char data[MAX_NUMBER_OF_LISTS][MAX_NUMBER_OF_ITEMS][MAX_LENGTH];
    char line[MAX_ITEM_NAME_LENGTH*MAX_LIST_NAME_LENGTH];
    //String Tokenizer Variable
    char *token;
    //Rows and Columns
    int r=0,c=0;

    //Reading the file and storing it a 3D array
    while(fgets(line,MAX_ITEM_NAME_LENGTH*MAX_LIST_NAME_LENGTH,fp) && r < MAX_NUMBER_OF_LISTS){
        token = strtok(line, ",");
        while (token != NULL && c < MAX_NUMBER_OF_ITEMS) {
            strcpy(data[r][c], token);
            c++;
            token = strtok(NULL, ",");
        }
        r++;
        c=0;
    }
    fclose(fp);

    //Printing Board (testing)
    /*printf("\nPrinted Board: \n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_ITEMS; j++) {
            if (strlen(data[i][j]) > 0) {
                printf("\t%s ", data[i][j]);
            }
        }
        printf("\n");
    }*/

    //Checking where list names are stored in data array(testing)
    /*printf("%s\n", data[0][0]);
    printf("%s\n", data[1][0]);
    printf("%s\n", data[2][0]);
    printf("%s\n", data[3][0]);
    printf("%s\n", data[4][0]);*/


    /****Loading File into Linked Lists****/

    //Creating Head of List Pointer and Initializing it as NULL
    headOfList = NULL;


    int i=r-1;
    while(i>=0){
        //Creating a New List Pointer. //Allocating New Memory to New List Pointer
        List *newListPtr = malloc(sizeof(List));;
        //Giving New List Pointer the List Name
        strcpy(newListPtr->listName, data[i][0]);
        //Creating the Link between New List Pointer and Head of List Pointer
        newListPtr->nextList = headOfList;
        //Pointing Head of List Pointer to the New List Pointer
        headOfList = newListPtr;

        //Testing whether List Names are printed correctly
        //printf("%s:\n", newListPtr->listName);

        /*Checking where newListPtr points to
        printf("%s:\n", newListPtr->listName);
        (newListPtr still points to the same thing headOfList points to)
        */

        //Head Of Item List
        newListPtr->firstItem=NULL;

        int j=MAX_NUMBER_OF_ITEMS-1;
        while(j>=1){
            if(strlen(data[i][j])>0){
                //Creating a New Item List Pointer. //Allocating New Memory to New Item List Pointer
                Item *newItemPtr= malloc(sizeof(Item));
                //Giving New Item Pointer the Item Name
                strcpy(newItemPtr->itemName, data[i][j]);
                //Creating the Link between New Item Pointer and Head Of Item List Pointer
                newItemPtr->nextItem = newListPtr->firstItem;
                //Pointing Head Of Item List Pointer to the New Item Pointer
                newListPtr->firstItem = newItemPtr;

                //Testing whether Item Names are printed correctly
                //printf("\t%s\n", newListPtr->firstItem->itemName);
            }
            //decrementing j
            j--;
        }

        //decrementing i
        i--;
    }
    displayBoard(headOfList);

}

//Edit List Function
void editList(){

    //printf("Enter the name of the list to edit:\n");

    //To add: (Find list name and link pointer to that list, if not just give an error message)
    char searchName[MAX_LIST_NAME_LENGTH];
    printf("Enter the name of the list to edit:\n");
    //scanf("%s", searchName);
    fgetc(stdin);
    fgets(searchName, MAX_LIST_NAME_LENGTH, stdin);

    //fgets(tasks[i].task_name,MAX_TASK_NAME_LENGTH,stdin);

    // remove the newline character
    //tasks[i].task_name[strcspn(tasks[i].task_name, "\n")] = '\0';

    //Removing New Line Character
    searchName[strcspn(searchName, "\n")] = '\0';

    // struct List* list4 = NULL;  // Initialize list4 to NULL

    bool listFound = search(headOfList, searchName);
    if (listFound) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    int choice;
    //Running Edit List while user does not request to go back to main menu (entering 4)
    do{

        printf("\nOptions: \n");
        printf("1. Edit an Item \n");
        printf("2. Add new Item \n");
        printf("3. Delete an Item \n");
        printf("4. Return to Main Menu \n");

        printf("Enter your choice(1-4):\n");

        //Error Handling to invalidate incorrect entries
        int flag=0; //counts number of times the exit condition for do-while loop not met
        do{
            if(flag==0){
                while(scanf("%d", &choice)==0) //while scanf does not scan an integer
                {
                    printf("Invalid Input. Please try again: \n");
                    int c;
                    while((c=getchar())!='\n' && c!=EOF); //clear the stdin
                }
            }
            else{
                printf("Invalid Input. Please try again: \n");
                while(scanf("%d", &choice)==0) //while scanf does not scan an integer
                {
                    printf("Invalid Input. Please try again: \n");
                    int c;
                    while((c=getchar())!='\n' && c!=EOF); //clear the stdin
                }
            }
            flag++;
        }
        while(choice>4 || choice <1);


        //Choosing Function to run depending on choice entered by user
        switch(choice) {
            case 1:
                printf("Edit Item Name: \n\n");
                break;
            case 2:
                printf("Add new Item: \n");
                break;
            case 3:
                printf("Delete an Item: \n");
                break;
            default:
                printf("\nReturning to main menu...\n");
        }


    }
    while(choice!=4);

    //If choice = 4 return to main menu
    mainMenu();


}

void addItem(List *currentListPtr){

    //Requesting item name to be entered from user
    char itemNameEntered[MAX_ITEM_NAME_LENGTH];
    scanf("%s", &itemNameEntered);
    printf("Item Name: ", itemNameEntered);

    Item *newPtr = malloc(sizeof (Item));

    strcpy(newPtr->itemName, itemNameEntered);
    newPtr->nextItem = NULL;

    newPtr->nextItem = currentListPtr->firstItem;
    currentListPtr->firstItem = newPtr;

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








