#include <stdio.h>
#include <string.h>

int counting_votes() 
{
    // Define party names (case-sensitive)
    char party1[] = "partyA";
    char party2[] = "partyB";
    char party3[] = "partyC";
    char party4[] = "partyD";

    // Vote counters
    int party1_votes = 0;
    int party2_votes = 0;
    int party3_votes = 0;
    int party4_votes = 0;
    int invalid_votes = 0;

    // Open the CSV file
    FILE *file;
    file = fopen("votedata.csv", "r");

    if (file == NULL) 
    {
        printf("Error: Could not open the file.\n");
        return 1;
    }

    char line[1000];  // to store votes in each line

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) 
    {
        // Skip the header line
        if (strstr(line, "voter_id") != NULL)//strstr(string1, string2) looks for string2 inside string1
            continue;//If "voter_id" is found in the line, we skip the rest of the loop using continue

       // Split the line by comma and only use the second part (party)
        char *voted_party = strtok(line, " ");   // First part: voter ID (not used)
        voted_party = strtok(NULL, " ");         // Second part: party name

        // If party is found
        if (voted_party != NULL) 
        {
            // Remove newline character at the end of the party name
            int i = 0;
            while (voted_party[i] != '\0')
            {
                if (voted_party[i] == '\n' || voted_party[i] == '\r') 
                {
                    voted_party[i] = '\0';
                    break;
                }
                i++;
            }

            // Compare and count votes
            if (strcasecmp(voted_party, party1) == 0) 
            {
                party1_votes++;
            } 
            else if (strcasecmp(voted_party, party2) == 0) 
            {
                party2_votes++;
            } 
            else if (strcasecmp(voted_party, party3) == 0) 
            {
                party3_votes++;
            } 
            else if (strcasecmp(voted_party, party4) == 0) 
            {
                party4_votes++;
            } 
            else 
            {
                invalid_votes++;
            }
        }
    }

    // Close the file
    fclose(file);

    // Display the results
    printf("Election Results:\n");
    printf("party1: %d votes\n", party1_votes);
    printf("party2: %d votes\n",party2_votes);
    printf("party3: %d votes\n", party3_votes);
    printf("party4: %d votes\n", party4_votes);
    printf("Invalid Votes: %d\n", invalid_votes);

// Find the maximum votes to detect the winner or tie
int maxVotes = party1_votes;
if (party2_votes > maxVotes) 
{
    maxVotes = party2_votes;
}
if (party3_votes > maxVotes) 
{
    maxVotes = party3_votes;
}
if (party4_votes > maxVotes) 
{
    maxVotes = party4_votes;
}

// Check if there's a tie

if (maxVotes == 0) 
{
    printf("No valid votes cast\n");
}
else if (party1_votes == maxVotes && party2_votes == maxVotes && party3_votes == maxVotes && party4_votes == maxVotes) 
{
    printf("It's a tie between all four parties\n");
}
else if (party1_votes == maxVotes && party2_votes == maxVotes && party3_votes == maxVotes) 
{
    printf("It's a tie between %s, %s, and %s\n", party1, party2, party3);
} 
else if (party1_votes == maxVotes && party2_votes == maxVotes && party4_votes == maxVotes) 
{
    printf("It's a tie between %s, %s, and %s\n", party1, party2, party4);
} 
else if (party1_votes == maxVotes && party3_votes == maxVotes && party4_votes == maxVotes) 
{
    printf("It's a tie between %s, %s, and %s\n", party1, party3, party4);
} 
else if (party2_votes == maxVotes && party3_votes == maxVotes && party4_votes == maxVotes) 
{
    printf("It's a tie between %s, %s, and %s\n", party2, party3, party4);
}
else if (party1_votes == maxVotes && party2_votes == maxVotes) 
{
    printf("It's a tie between %s and %s\n", party1, party2);
}  
else if (party1_votes == maxVotes && party3_votes == maxVotes) 
{
    printf("It's a tie between %s and %s\n", party1, party3);
}  
else if (party1_votes == maxVotes && party4_votes == maxVotes) 
{
    printf("It's a tie between %s and %s\n", party1, party4);
} 
else if (party2_votes == maxVotes && party3_votes == maxVotes) 
{
    printf("It's a tie between %s and %s\n", party2, party3);
} 
else if (party2_votes == maxVotes && party4_votes == maxVotes) 
{
    printf("It's a tie between %s and %s\n", party2, party4);
} 
else if (party3_votes == maxVotes && party4_votes == maxVotes) 
{
    printf("It's a tie between %s and %s\n", party3, party4);
} 
//print winner if there is no tie
else if (party1_votes == maxVotes) 
{
    printf("Winner: %s with %d votes\n", party1, maxVotes);
} 
else if (party2_votes == maxVotes) 
{
    printf("Winner: %s with %d votes\n", party2, maxVotes);
} 
else if (party3_votes == maxVotes) 
{
    printf("Winner: %s with %d votes\n", party3, maxVotes);
} 
else if (party4_votes == maxVotes) 
{
    printf("Winner: %s with %d votes\n", party4, maxVotes);
}

return 0;
}
