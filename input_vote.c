#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOTERS 100
#define MAX_PARTY_NAME 50

// Hardcoded list of available parties
const char *parties[] = {"PartyA", "PartyB", "PartyC", "PartyD"};
const int total_parties = 4;

typedef struct {
    int voter_id;
    char voted_party[MAX_PARTY_NAME];
} Voter;

// Function to check if file exists
int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return 0;
    fclose(file);
    return 1;
}

// Function to read existing voter data
void readCSV(Voter voters[], int *count) {
    FILE *file = fopen("votedata.csv", "r");
    if (file == NULL) {
        *count = 0;
        return;
    }

    *count = 0;
    // Skip header line
    fscanf(file, "%*[^\n]\n");

    while (*count < MAX_VOTERS && fscanf(file, "%d %49s", &voters[*count].voter_id, voters[*count].voted_party) == 2) {
        (*count)++;
    }

    fclose(file);
}

// Function to save a new vote
void saveSelection(int voter_id, const char *selected_option) {
    FILE *file;

    // If file doesn't exist, create and write header
    if (!fileExists("votedata.csv")) {
        file = fopen("votedata.csv", "w");
        if (file == NULL) {
            perror("Unable to create file");
            exit(EXIT_FAILURE);
        }
        fprintf(file, "VoterID  VotedParty");
        fclose(file);
    }

    // Now append vote
    file = fopen("votedata.csv", "a");
    if (file == NULL) {
        perror("Unable to open file for appending");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "\n%-8d %-10s", voter_id, selected_option); // Proper spacing
    fclose(file);
}

// Function to display available parties
void displayParties() {
    printf("Available Parties:\n");
    for (int i = 0; i < total_parties; i++) {
        printf("%d: %s\n", i + 1, parties[i]);
    }
}

int vote_input_main(int voter_id) {
    Voter voters[MAX_VOTERS];
    int count = 0;
    char selected_option[MAX_PARTY_NAME];

    // Read existing votes
    readCSV(voters, &count);

    // Check for duplicate vote
    for (int i = 0; i < count; i++) {
        if (voters[i].voter_id == voter_id) {
            printf("Error: Voter ID %d has already voted.\n", voter_id);
            return 1;
        }
    }
    // Display available parties
    displayParties();

    // Get user selection
    int party_choice;
    printf("Select the number corresponding to the party you want to vote for: ");
    scanf("%d", &party_choice);
    // Validate selection
    if (party_choice < 1 || party_choice > total_parties) {
        printf("Invalid selection. Please run the program again.\n");
        return 1;
    }
    // Save the vote
    strcpy(selected_option, parties[party_choice - 1]);
    saveSelection(voter_id, selected_option);
    printf("Your vote for %s has been recorded successfully!\n", selected_option);
    return 0;
}