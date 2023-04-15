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


//Making List Global
List *headOfList;

//Board *myBoard;

//Function Definitions
void mainMenu();
void displayBoard();
void useDefaultBoard();
void loadFile();
void editList();
bool checkIfListExist(char* searchName);
List* findList(char *searchName);
void editItemName(List *currentListPtr);
void insertItem(char *newItemName, List *currentListPtr);
void deleteItem(char* nameOfItemToDelete, List *currentListPtr);

void editBoard();
void editListName(List* currentListPtr);
void insertList(char* newListName);
void deleteList(char* nameOfListToDelete);



//Main Function
int main(void){

    //Running Default Board Initially
    useDefaultBoard();
    mainMenu();
}

//Displays Initial Menu
void mainMenu(){


    int choice; //"choice" is the variable used to allow the user to choose the operation to perform

    //Running Main Menu until quit is entered
    do{
        //Printing Menu
        printf("\nMenu:\n ");
        printf("1. Display Board:\n ");
        printf("2. Load Board From A File:\n ");
        printf("3. Edit List: \n ");
        printf("4. Edit Board: \n ");
        printf("5. Save Board To A File: \n ");
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
                displayBoard();
                break;
            case 2:
                loadFile();
                break;
            case 3:
                //printf("Edit List: \n");
                editList();
                break;
            case 4:
                editBoard();
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
void useDefaultBoard(){
    headOfList = NULL;

    char data[MAX_NUMBER_OF_LISTS][MAX_NUMBER_OF_ITEMS][MAX_LENGTH]= { {"Abey", "Oculus Pro", "Oculus Quest 1"}, {"Dante", "Oculus Quest 1", "3070 RTX"}, {"Tim", "Oculus Quest 2"}, {"Nick", "3070 RTX"}};
    int r = 4;

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
    //displayBoard();
}

//Displays a board
void displayBoard(){

    printf("*************************************************************\n");
    printf("Displaying Board...\n\n");

    if(headOfList==NULL){
        printf("Board is Empty...Returning to Main Menu...\n");
        mainMenu();

    }
    List *currentListPtr=NULL;
    currentListPtr = headOfList;

    while(currentListPtr!=NULL){
        //Printing List Name
        printf("%s\n", currentListPtr->listName);

        if(currentListPtr->firstItem==NULL){
            printf("\nList %s is Empty...return to main menu to add something!\n\n", currentListPtr->listName);
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
    printf("*************************************************************\n\n");
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
        while (token != NULL && c < MAX_NUMBER_OF_ITEMS){
            //printf("%s\n", token);
            strcpy(data[r][c], token);
            data[r][c][strcspn(data[r][c], "\n")] = '\0';
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

    //Checking where data names are stored in data array(testing)
    /*printf("\nList Names:\n");
    printf("%s\n", data[0][0]);
    printf("%s\n", data[1][0]);
    printf("%s\n", data[2][0]);
    printf("%s\n", data[3][0]);
    printf("%s\n", data[4][0]);
    printf("\nItem Names:\n");
    printf("%s\n", data[0][1]);
    printf("%s\n", data[0][2]);*/

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
    printf("File Successfully Loaded... \n");
    //displayBoard();

}

//Edit List Function
void editList(){


    char searchListName[MAX_LIST_NAME_LENGTH];
    printf("Enter the name of the list to edit:\n");


    fgetc(stdin);//adding this statement to make sure that the new line created by scanf doesn't affect fgets
    fgets(searchListName, MAX_LIST_NAME_LENGTH, stdin);
    //Removing New Line Character
    searchListName[strcspn(searchListName, "\n")] = '\0';

    //Checking is list exists
    bool listFound = checkIfListExist(searchListName);
    if (!listFound) {//List Not Found then go to main menu
        printf("List Not Found... Going back to Main Menu...\n");
        mainMenu();
        //exit(0);
    }

    //Finding list - Works :)
    List *currentListPtr = NULL;
    currentListPtr = findList(searchListName);
    printf("\nList has been found. This is the list name: %s\n", currentListPtr->listName); //(Used for Testing Purposes to check if the right list was found)

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


        char newItemName[MAX_ITEM_NAME_LENGTH];
        char nameOfItemToBeDeleted[MAX_ITEM_NAME_LENGTH];



        //Choosing Function to run depending on choice entered by user
        switch(choice) {
            case 1:
                //printf("Edit Item Name: \n\n");
                editItemName(currentListPtr);
                break;
            case 2:
                printf("Enter the name of the item to be added: \n");

                fgetc(stdin);
                fgets(newItemName, MAX_ITEM_NAME_LENGTH, stdin);
                //Removing New Line Character
                newItemName[strcspn(newItemName, "\n")] = '\0';
                insertItem(newItemName, currentListPtr);
                break;
            case 3:
                //printf("Delete an Item: \n");
                printf("Enter name of item to delete:\n");
                fgetc(stdin);//adding this statement to make sure that the new line created by scanf doesn't affect fgets
                fgets(nameOfItemToBeDeleted, MAX_ITEM_NAME_LENGTH, stdin);
                nameOfItemToBeDeleted[strcspn(nameOfItemToBeDeleted, "\n")] = '\0';

                deleteItem(nameOfItemToBeDeleted, currentListPtr);

                break;
            default:
                printf("\nReturning to main menu...\n");
        }


    }
    while(choice!=4);

    //If choice = 4 return to main menu
    mainMenu();


}


bool checkIfListExist(char* searchName)
{
    struct List* current = headOfList; // Start from the head of the list
    while (current != NULL) {
        if (strcmp(current->listName, searchName) == 0)
            return true;
        current = current->nextList;
    }
    return false;
}

//Function to search List for list name and return the pointer if found
List* findList(char *searchName){
    List* current = headOfList;
    while(current!=NULL){
        if (strcmp(current->listName, searchName) == 0){
            return current;
        }
        current = current->nextList;
    }
}


void editItemName(List *currentListPtr) {
    //printf("\nItem name to be changed: %s\n",currentListPtr->listName); //(Used for Testing Purposes to check if the right list was found)

    char searchItemName[MAX_ITEM_NAME_LENGTH];
    char newItemName[MAX_ITEM_NAME_LENGTH];
    Item *currentItemPtr = currentListPtr->firstItem;


    printf("Enter the name of the item to edit\n");

    fgetc(stdin);//adding this statement to make sure that the new line created by scanf doesn't affect fgets
    fgets(searchItemName, MAX_LIST_NAME_LENGTH, stdin);
    //Removing New Line Character
    searchItemName[strcspn(searchItemName, "\n")] = '\0';

    printf("Enter the name of the new item\n");

    //fgetc(stdin);//adding this statement to make sure that the new line created by scanf doesn't affect fgets (Not Required here as there is no scanf before it)
    fgets(newItemName, MAX_LIST_NAME_LENGTH, stdin);
    //Removing New Line Character
    newItemName[strcspn(newItemName, "\n")] = '\0';



    bool found_item = false;

    //printf("First item of %s is %s\n", currentListPtr->listName, currentItemPtr->itemName); (Testing)
    //Checking if item exists
    while(currentItemPtr!=NULL){

        if(strcmp(currentItemPtr->itemName, searchItemName)==0){
            printf("Old Item Name: %s\n", currentItemPtr->itemName);
            found_item=true;
            strcpy(currentItemPtr->itemName, newItemName);

            printf("Changed Item Name: %s\n", currentItemPtr->itemName);
            printf("Item Name Successfully Changed... You can verify by displaying the board again :) \n");
            break;
        }
        currentItemPtr = currentItemPtr->nextItem;
    }

    //If Item Not Found then go to main menu
    if(!found_item){
        printf("Item Not Found...Going back to main menu\n");
        mainMenu();
    }
    /*
    //Checking if the first Item of a list has followed through (Testing)
    //printf("Current List: first Item: %s\n", currentListPtr->firstItem->itemName);
    if(currentListPtr->firstItem->itemName==NULL){
        printf("List is Empty\n");
        printf("Returning to main menu...\n");
        mainMenu();
    }*/

}

void insertItem(char *newItemName, List *currentListPtr)
{
    //Error handling to check whether item exists already
    Item *currentItemPtr = currentListPtr->firstItem;
    bool doesItemExist=false;
    while(currentItemPtr!=NULL){
        if(strcmp(currentItemPtr->itemName, newItemName)==0){
            doesItemExist=true;
            break;
        }
        currentItemPtr=currentItemPtr->nextItem;
    }
    //If Item does not Exist
    if(doesItemExist){
        printf("Item Already Exists...Going back to Main Menu\n");
        mainMenu();
    }
    //Else:

    //Creating a new Item
    Item *newItem = malloc(sizeof(Item));
    strcpy(newItem->itemName, newItemName); //Giving the New Item its Name
    newItem->nextItem = currentListPtr->firstItem; //Linking new Item to current Lists first Item
    currentListPtr->firstItem = newItem;

    printf("Item: %s, has been successfully added to List: %s, you can print the board again to check :)\n", currentListPtr->firstItem->itemName, currentListPtr->listName);

}

void deleteItem(char* nameOfItemToDelete, List *currentListPtr){

    Item *currentItemPtr = currentListPtr->firstItem;

    Item* prevItem = NULL;

    //Adding error handling block to make sure item exists
    Item *currentItemPtr2 = currentListPtr->firstItem;
    bool doesItemExist=false;
    while(currentItemPtr2!=NULL){
        if(strcmp(currentItemPtr2->itemName, nameOfItemToDelete)==0){
            doesItemExist=true;
            break;
        }
        currentItemPtr2=currentItemPtr2->nextItem;
    }
    //If Item does not Exist
    if(!doesItemExist){
        printf("Item Not Found...Going back to main menu\n");
        mainMenu();
    }
    //Else:


    // Find the item to be deleted (If Item doesn't exist this will run in an infinite loop, causing program to fail)
    while (currentItemPtr != NULL && strcmp(currentItemPtr->itemName, nameOfItemToDelete) != 0) {
        prevItem = currentItemPtr;
        currentItemPtr = currentItemPtr->nextItem;
    }


    // Update the nextItem pointer of the previous item
    if (prevItem == NULL) {
        // Item to be deleted is the first item in the list
        currentListPtr->firstItem = currentItemPtr->nextItem;
    } else {
        prevItem->nextItem = currentItemPtr->nextItem;
    }

    printf("Item: %s has been successfully deleted from List: %s, you can display the board again to check :)\n", currentItemPtr->itemName, currentListPtr->listName);


    // Free the memory of the item to be deleted
    free(currentItemPtr);
}

void editBoard()
{


    int choice;
    //Running Edit List while user does not request to go back to main menu (entering 4)
    do{

        printf("\nOptions: \n");
        printf("1. Edit the name of a list \n");
        printf("2. Add a new list \n");
        printf("3. Delete a list\n");
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

        char newListName[MAX_ITEM_NAME_LENGTH];
        char nameOfListToBeDeleted[MAX_ITEM_NAME_LENGTH];

        switch(choice) {
            case 1:
                //printf("Edit Item Name: \n\n");
                editListName(headOfList);
                break;
            case 2:
                printf("Enter the name of the list to be added: \n");

                fgetc(stdin);
                fgets(newListName, MAX_ITEM_NAME_LENGTH, stdin);
                //Removing New Line Character
                newListName[strcspn(newListName, "\n")] = '\0';

                insertList( newListName);
                break;
            case 3:
                //printf("Delete an Item: \n");
                printf("Enter name of list to delete:\n");
                fgetc(stdin);//adding this statement to make sure that the new line created by scanf doesn't affect fgets
                fgets(nameOfListToBeDeleted, MAX_ITEM_NAME_LENGTH, stdin);
                nameOfListToBeDeleted[strcspn(nameOfListToBeDeleted, "\n")] = '\0';

                deleteList(nameOfListToBeDeleted);

                break;
            default:
                printf("\nReturning to main menu...\n");
        }


    }
    while(choice!=4);

    //If choice = 4 return to main menu
    mainMenu();



}
void editListName(List* currentListPtr)
{
    char searchListName[MAX_ITEM_NAME_LENGTH];
    char newListName[MAX_LIST_NAME_LENGTH];

    printf("Enter the name of the list to edit\n");

    fgetc(stdin);//adding this statement to make sure that the new line created by scanf doesn't affect fgets
    fgets(searchListName, MAX_LIST_NAME_LENGTH, stdin);
    //Removing New Line Character
    searchListName[strcspn(searchListName, "\n")] = '\0';

    printf("Enter the new name for list \n");

    //fgetc(stdin);//adding this statement to make sure that the new line created by scanf doesn't affect fgets (Not Required here as there is no scanf before it)
    fgets(newListName, MAX_LIST_NAME_LENGTH, stdin);
    //Removing New Line Character
    newListName[strcspn(newListName, "\n")] = '\0';



    bool found_list = false;

    //printf("First item of %s is %s\n", currentListPtr->listName, currentItemPtr->itemName); (Testing: Ignore if not developer)
    while(currentListPtr!=NULL){
        if(strcmp(currentListPtr->listName, searchListName)==0){
            printf("Old List Name: %s\n", currentListPtr->listName);
            found_list=true;
            strcpy(currentListPtr->listName, newListName);

            printf("Changed List Name: %s\n", currentListPtr->listName);
            printf("List Name Successfully Changed... You can verify by displaying the board again :) \n");
            break;
        }
        currentListPtr = currentListPtr->nextList;
    }
    //displayBoard(headOfList);

    //If Item Not Found then go to main menu
    if(!found_list){
        printf("Item Not Found...Going back to main menu\n");
        mainMenu();
    }


}

void insertList(char* newListName)
{
    List *currentListPtr = headOfList;
    bool doesListExist=false;
    while(currentListPtr!=NULL){
        if(strcmp(currentListPtr->listName, newListName)==0){
            doesListExist=true;
            break;
        }
        currentListPtr=currentListPtr->nextList;
    }

    // If List already exists
    if(doesListExist){
        printf("List Already Exists...Going back to Main Menu\n");
        mainMenu();
        return;
    }
    //Else:

    //Creating a new List
    List *newList = malloc(sizeof(List));
    strcpy(newList->listName, newListName); //Giving the New Item its Name

    newList->nextList=headOfList;
    headOfList = newList;


    printf("List: %s, has been successfully added to the Board, you can print the board again to check :)\n", headOfList);

    //displayBoard(headOfList);
}


void deleteList(char* nameOfListToDelete)
{

    List *currentListPtr = headOfList;
    List* prevList = NULL;

    //Adding error handling block to make sure item exists
    List *currentListPtr2 = headOfList;

    bool doesListExist=false;
    while(currentListPtr2!=NULL){
        //printf("%s\n", currentListPtr2->listName);
        if(strcmp(currentListPtr2->listName, nameOfListToDelete)==0){
            doesListExist=true;
            break;
        }
        currentListPtr2=currentListPtr2->nextList;
    }

    // If List already exists
    if(!doesListExist){
        printf("List Not Found...Going back to main menu\n");
        mainMenu();
        return;
    }
    //Else:

    while (currentListPtr != NULL && strcmp(currentListPtr->listName, nameOfListToDelete) != 0) {
        prevList = currentListPtr;
        currentListPtr = currentListPtr->nextList;
    }

    if (prevList == NULL) {
        // List to be deleted is the first item in the list
        headOfList = currentListPtr->nextList;
    } else {
        prevList->nextList = currentListPtr->nextList;
    }

    printf("List: %s has been successfully deleted the Board you can display the board again to check :)\n", currentListPtr->listName);

    free(currentListPtr);
    //displayBoard(headOfList);
}
