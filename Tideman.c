#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

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
{
    // loop to get the number of votes per candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Generate the matrix of preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int column = i + 1; column < candidate_count; column++)
        {
            preferences[ranks[i]][ranks[column]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Compare between pairs of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair pair_candidates = {i, j};
                pairs[pair_count] = pair_candidates;
                pair_count++;
            }
        }
    }
    return;
}

int pair_comparison(i)
{
    int pair_winner = pairs[i].winner;
    int pair_loser = pairs[i].loser;
    return preferences[pair_winner][pair_loser];
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // sort pairs to know who get more votes
    for (int i = pair_count - 1; i >= 0; i--)
    {
        int min_comparison = pair_comparison(i);
        int min_indice = i;
        for (int k = i - 1; k >= 0; k--)
        {
            if (pair_comparison(k) < min_comparison)
            {
                min_comparison = pair_comparison(k);
                min_indice = k;
            }
        }
        pair order = pairs[min_indice];
        pairs[min_indice] = pairs[i];
        pairs[i] = order;
    }

    return;
}

// Test for cycle by checking arrow coming into each candidate
bool cycleRecursive(int start, int end)
{
    // Return true if there is a cycle created
    if (end == start)
    {
        return true;
    }
    // Loop through candidates using recursive function
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (cycleRecursive(start, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loop through pairs of candidates
    for (int i = 0; i < pair_count; i++)
    {
        // condition if the recursive function returns false, lock the pair of candidates
        if (!cycleRecursive(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // from candidates locked get the winner
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}
