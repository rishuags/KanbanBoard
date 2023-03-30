#include <stdio.h>

//Function Definitions
void displayMenu();
int main() {
   displayMenu();
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
