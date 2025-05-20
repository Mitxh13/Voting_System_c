#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE1 1024

// Function declarations
int verify_admin_login(const char *username, const char *password);
void admin_menu();
void view_results();
void results_check();

void admin_login() {
    char username[50], password[50];
    printf("\n--- Admin Login ---\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (verify_admin_login(username, password)) {
        printf("Login successful!\n");
        admin_menu();
    } else {
        printf("Invalid credentials.\n");
    }
}

// Reads admin credentials from admin.csv and validates login
int verify_admin_login(const char *username, const char *password) {
    FILE *file = fopen("admin.csv", "r");
    if (file == NULL) {
        printf("Error: Could not open admin.csv\n");
        return 0;
    }

    char line[MAX_LINE1];
    char stored_username[50], stored_password[50];

    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line,"%s %s", &stored_username, &stored_password);
        if ((strcmp(username, stored_username) && strcmp(password, stored_password) ) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Admin menu options
int check_results =0; //0 = not released, 1 = released

void admin_menu() {
    int choice;
    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. Release Election Results\n");
        printf("2. View Election Results\n");
        printf("3. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                check_results = 1;
                printf("Results have been released.\n");
                break;
            case 2:
                printf("\nThe current Voting status is:- \n");
                counting_votes(); // make sure this exists
                break;
            case 3:
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}

void results_check(){
    if(check_results == 1){
        counting_votes();
    }
    else{
        printf("The ADMIN has not released the results yet.\n");
        printf("You have been logged out. Please re-login\n");
    }
}
