#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
int compr(const void *first, const void *sec);
void sort_pairs(void);
bool cyclic2(int ok, bool repeat[]);
bool cyclic(int ok);
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
    for (int i = 0; i < candidate_count; i++) //add each candidate from argv to candidate array
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
    // TODO
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            //update the ranks array to indicate that the voter has the candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.)
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i+1; j < candidate_count; j++) {

            preferences[ranks[i]][ranks[j]]++; //checks all other options ahead of ranks at i in array & updates preferences
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;

    for (int i = 0; i < candidate_count; i++) {
        for (int j = i+1; j < candidate_count; j++) { //j < candidate_count+1? test try
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;

            } else if (preferences[j][i] > preferences[i][j]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;

            }
        }
    }
}

int compr(const void *first, const void *sec) {
    pair tc1 = *(pair *)first;
    pair tc2 = *(pair *)sec;

    int win1 = preferences[tc1.winner][tc1.loser] - preferences[tc1.loser][tc1.winner]; //what each win strength is
    int win2 = preferences[tc2.winner][tc2.loser] - preferences[tc2.loser][tc2.winner];

    //return (preferences[tc2->winner][tc2->loser] - preferences[tc1->winner][tc1->loser]);

    return win2 - win1;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), compr);
}

bool cyclic2(int ok, bool repeat[]) {
    if (repeat[ok]) {
        return true;
    }
    repeat[ok] = true;

    for (int i = 0; i < candidate_count; i++) {
        if (locked[ok][i] && cyclic2(i, repeat)) {
            return true;
        }
    }
    return false; //no cycle!
}


bool cyclic(int ok) {
    bool repeat[candidate_count];

    for (int i = 0; i < candidate_count; i++) {
        repeat[i] = false;
    }

    return cyclic2(ok, repeat);
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        locked[pairs[i].winner][pairs[i].loser] = true;

        if (cyclic(i) == true) {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    int pos;

    for (int i = 0; i < candidate_count; i++)
    {
        pos = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                pos++;
            }
        }

        if (pos == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
}

