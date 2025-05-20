#include<stdio.h>
#include<string.h>
#define MAX_LINE 150

//This function is used to add the data of new user into the database
void write_new_data(int id,char *password,char *email){
    FILE *file;
    file = fopen("voter_log.csv","a");
    fprintf(file,"\n%d    %s    %s",id,password,email);
    fclose(file);
}
void unique_check_fail(int voter_id);
// This function is used to check if the id created is unique or not.. If the id is already taken then user hv to create new one
void unique_check(int voter_id){
    FILE *file = fopen("voter_log.csv", "r");
    char line[MAX_LINE];
    char pass[100],email[1000];
    int id_from_file,found = 0;;
    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        //This removes newline character if present
        line[strcspn(line, "\n")] = '\0';
        // Parse line (format: id password)
        if (sscanf(line, "%d", &id_from_file) == 1) {
            if ((id_from_file == voter_id)) {
                printf("The id has already been taken,Please create another one!!\n");
                found = 1;
                unique_check_fail(voter_id);
            }
        }
    }
    if (!found) {
        printf("PLEASE ENTER YOUR PASSWORD: ");
        scanf("%s",&pass);
        printf("PLEASE ENTER YOUR EMAIL ID: ");
        scanf("%s",&email);
        write_new_data(voter_id,pass,email);
        printf("New account created successful!!");
    }
    fclose(file);
}

//This function will excute if the user id created already taken by someone else, 
//then the user need not run the program again we will be directly calling this funtion so user can reenter his/her data
void unique_check_fail(int voter_id){
    printf("PLEASE ENTER YOUR NEW VOTER ID: ");
        scanf("%d",&voter_id);
        //Creating temp_check and temp_id variables to check if the id created by user is equal or more than 5 digits
        int temp_check = 0,temp_id = voter_id;
        for(int i = 0;i<6;i++){
            if(temp_id>0){
                temp_id /= 10;
                temp_check++;
            }
        }
        // This will execute if all rules followed
        if(temp_check>=5){
            unique_check(voter_id);
        }
        //Else this will execute if id created does not follow the rules
        else{
            printf("The voter id must be more than 5 digits");

        }
    }

//This function check if the user is 18+ years or not,Then allows to create the account
void add_user(){
    printf("Welcome to VotIQ\n");
    int voter_id,age;
    char pass[100],email[1000];
    printf("Please enter your age to proceed:");
    scanf("%d",&age);
    if(age>=18){
        printf("***CAUTION*** The voter id must contain only number and must be more than 5 digits & ID should not start from 0\n");
        printf("Please enter your deatails to create account \n");
        printf("PLEASE ENTER YOUR VOTER ID: ");
        scanf("%d",&voter_id);
        //Creating temp_check and temp_id variables to check if the id created by user is equal or more than 5 digits
        int temp_check = 0,temp_id = voter_id;
        for(int i = 0;i<6;i++){
            if(temp_id>0){
                temp_id /= 10;
                temp_check++;
            }
        }
        // This will execute if all rules followed
        if(temp_check>=5){
            unique_check(voter_id);
        }
        //Else this will execute if id created does not follow the rules
        else{
            printf("The voter id must be more than 5 digits\n");
            add_user();
        }
    }
    //This executes when a minor tries to create account
    else{
        int valid_age = 18-age;
        printf("Your NOT eligible to vote., Please wait for %d more yrs to Vote\n",valid_age);
        printf("Thank you!!!");
    }
}
