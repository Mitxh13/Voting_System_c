#include<stdio.h>
#include<string.h>
#include<math.h>
#include "counting.c"
#include "input_vote.c"
#include "admin_login.c"
#define MAX_LINE 150


//This functions will help the user to vote and view the results.
void user_choice(int voter_id){
    char choice;
    printf("Please enter:-\n'V' for voting \n'R' for results\n");
    scanf(" %c",&choice);
    switch (choice)
    {
    case 'R':
        results_check();
        break;
    case 'V':
        vote_input_main(voter_id);
        break;
    default:
        printf("Invalid choice");
        break;
    }
}

// This is function is used check is the user account exists or not
void logindata(int voter_id, char *password) {
    FILE *file;
    file = fopen("voter_log.csv", "r");
    char line[MAX_LINE],password_from_file[100];
    int id_from_file,found = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        //This will take the whole line as string from file then compare them
        if (sscanf(line, "%d    %s", &id_from_file, password_from_file) == 2) {
            if (id_from_file == voter_id && strcmp(password,password_from_file)==0) {
                printf("Login successful!\n");
                user_choice(voter_id);
                break;
            }
        }
    }
    if (!found) {
        printf("Invalid voter ID or password.\n");
        }

}

// This the main function in this file which allows user to login into their account
void login(){
    int voter_id;
    char password[100];
    printf("Please enter your voter id(only numbers) and password:\n");
    printf("PLEASE ENTER YOUR VOTER ID:");
    scanf("%d",&voter_id);
    printf("PLEASE ENTER YOUR PASSWORD:");
    scanf("%s",&password);
    logindata(voter_id,password);
}

