#include<stdio.h>
#include<string.h>
#include "voterlogin.c"
#include "newvoter.c"

// In this program we will using 3 files with code and 2 csv files
void importedfiles(){
    login();
    add_user();
    admin_login();

}
int main(){
    while(1){
    printf("\nWelcome to VotIQ!!\n");
    printf("Please enter your choice:-\n");
    printf("press 1 for login in your account\npress 2 for new user account\npress 'A' for admin login\n");
    printf("press 'q' to exit the program\n");
    char choice;
    scanf(" %c",&choice);
    // We will be using switch case.So it will easy for coding and the user to enter the choice accordingly.
    switch (choice){
        case '1': // This case refers to login to existing account
            login();
            break;
        case '2': // This case refers to create new account
            add_user();
            break;
        case 'A': //This case for Admins who can see the results and read the voting data but cannot edit
            admin_login();
            break;
        case 'q': // This case is for exiting the program
            printf("You have closed the program");
            return 0;
        default:
            printf("Invalid choice");
            break;
        }
    }
    return 0;
}
