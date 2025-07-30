#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name) //update if name matches
{
// compare if name is equal to any of the candidates
//for every candidate check if name is the same
    for (int i = 0; i < candidate_count; i++)
    {
        if ((strcmp(candidates[i].name, name) == 0))
        {
            //if it is update the current rank and voter preference for the vote in i index (candidate[0] will be a name)
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // loop every voter
    for (int i = 0; i < voter_count; i++)
    {

        //loop every voter choice for each candidate (ranked)
        for (int j = 0; j < candidate_count; j++)
        {
            //a candidate[n] n is given by the value of [preferences[i][j]] since this is equal to one of the numbers of the names
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes += 1;
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // calculate number of votes needed
    int half_votes = round(voter_count / 2);

    //loop every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //if any candidate has more than half print name and true else return false
        if (candidates[i].votes > half_votes)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // loop through every candidate
    int min = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        //skip candidates who are eliminated
        if (candidates[i].eliminated == true)
        {
            continue;
        }
        //override minimum for candidates who are still running
        if (candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }

    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int current_candidates = candidate_count;
    int all_tie = 0;
    //Loop all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //if not in game skip
        if (candidates[i].eliminated == true)
        {
            current_candidates--;
            continue;
        }
        //if tie between rest - true
        if (candidates[i].votes == min)
        {
            all_tie++;
        }
    }

    if (all_tie == current_candidates)
    {
        return true;
    }

    else
    {
        return false;
    }

}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    //loop for every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //candidate with votes equal to min should be eliminated
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}