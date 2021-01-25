#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX]; // if true, an edge exists from i to j

// Each pair has a winner, loser
typedef struct
{
    int winner; // candidate indices...
    int loser;
}
pair; // pair of candidates

typedef struct
{
    string candidate;
    int num_trues;
}
true_count;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2]; // n C r (where n = # of candidates, r = 2)

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int n, int m);
    
int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++) // looping through rows
    {
        for (int j = 0; j < candidate_count; j++) // looping through the columns in each row
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++) // looping through all voters
    {
        // ranks[i] is a single voter's ith preference (a new array is created for each voter)
        int ranks[candidate_count]; // ranks is a 1D array for each voter, of candidate INTs 

        // Query for each rank
        for (int j = 0; j < candidate_count; j++) // j == rank // looping through all candidates (ranks)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks); // called once for each voter

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}


// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{   /* 
    look for a candidate called name 
    if no candidates found, return false
    */

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
            {
                ranks[rank] = i; // add to ranks from candidates (ADD INDEX)!!!
                return true;
            }
    }
    return false;
}


// Update preferences (2D array) given one voter's ranks
void record_preferences(int ranks[]) // called once per voter 
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
            {
                (preferences[ranks[i]][ranks[j]])++; // add 1 to num of voters who prefer i over j
            }
    }
    return;
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // add each pair of candidates to the pairs array if one candidate is preferred over another
    pair_count = 0;

    for (int i = 0; i < candidate_count; i++) // loop through rows
        {
        for (int j = 0; j < candidate_count; j++) // loop through columns
            if ((preferences[i][j]) > (preferences[j][i]))
            {
                pairs[pair_count].winner = i; // need i (an int / index for a candidate) NOT A STRING
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }

    // TODO
    return;
}


// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    
    for (int k = 0; k < pair_count - 1; k++) // looping through all the passes
    {
        for (int n = 0; n < pair_count - 1; n++) // bubble sort // bubble the smallest margin to the end
        {
            int strength1 = preferences[pairs[n].winner][pairs[n].loser] - preferences[pairs[n].loser][pairs[n].winner]; // 2D ARRAY!!
            int strength2 = preferences[pairs[n+1].winner][pairs[n+1].loser] - preferences[pairs[n+1].loser][pairs[n].winner];
        
            if (strength1 < strength2)
            {
                pair temp = pairs[n];
                pairs[n] = pairs[n+1];
                pairs[n+1] = temp;
            }
        }
    }

    // TODO
    return;
}



// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    // lock the pairs into the candidate graph, as long as there is NO CYCLE

    
    for (int i = 0; i < pair_count; i++)    
    {
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
            locked[pairs[i].winner][pairs[i].loser] = true;
    }

    // TODO
    return;
}


bool check_cycle(int w, int l) // w = initial pair's winner, l = initial pair's loser
{
    // base case (stops recursion)
    if (locked[l][w] == true)
        return true;
    
    
    // recursive case
    else
    {
        for (int j = 0; j < candidate_count; j++) // looping through all potential candidates 
        {
            if (locked[j][w]) // if the current winner is a loser in another locked pair
            {
                return (check_cycle(j, l)); // check if there's a direct path from candidate j to the winner
            }
        }
    
    }
    return false; // no cycle created
}



// Print the winner of the election
void print_winner(void)
{
    // print the source of the graph 
    // - the candidate who has no arrows pointed towards them 


    bool loser;
    for (int i = 0; i < candidate_count; i++)  // looping through rows
    {
        loser = false;
        for (int j = 0; j < candidate_count; j++) // looping through columns
        {
            if (locked[j][i]) // if i is the loser of a pair in a row, they are not the winner
                loser = true;
        }
        
        if (!loser)
            printf("%s\n", candidates[i]);
    }

    // TODO
    return;
}