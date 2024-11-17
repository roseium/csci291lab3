// Header files
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Constants
#define NUM_TEAMS 10
#define SQUAD_SIZE 20
#define MAX_NAME_LENGTH 25
#define MAX_TEAM_NAME 20

// Struct definitions
typedef struct
{
    int day, month, year;
} age_t;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int kit_number;
    char club[MAX_TEAM_NAME];
    age_t age;
    char position[20];
} player_t;

typedef struct
{
    char team_name[MAX_TEAM_NAME];
    player_t players[SQUAD_SIZE];
    int active_size;
} team_t;

// Function prototypes
void display_menu();
void enroll_club(team_t teams[], int num_teams[]);
void add_player(team_t teams[], int num_teams);
void search_update(team_t teams[], int num_teams);
void display_club_statistics(team_t teams[], int num_teams);
void handle_error(char message[]);
int get_valid_int(char prompt[], int min, int max);

// Main function
int main()
{
    team_t teams[NUM_TEAMS];
    int num_teams = 0;
    int choice;

    while (1)
    {
        display_menu();
        choice = get_valid_int("Enter your choice: ", 0, 4);

        switch (choice)
        {
            case 1:
                enroll_club(teams, &num_teams);
                break;

            case 2:
                add_player(teams, num_teams);
                break;

            case 3:
                search_update(teams, num_teams);
                break;

            case 4:
                display_club_statistics(teams, num_teams);
                break;

            case 0:
                printf("Exiting program. Goodbye!\n");
                return 0;
        }
    }
}

// Function to display the menu
void display_menu() {
    printf("\nMenu Options:\n");
    printf("1. Enroll a club\n");
    printf("2. Add a player\n");
    printf("3. Search and update a player\n");
    printf("4. Display club statistics\n");
    printf("0. Exit\n");
}

// Function to get a valid integer input
int get_valid_int(char prompt[],int min,int max)
{
    int value;
    char term; // For invalid characters
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d%c", &value, &term) != 2 || term != '\n' || value < min || value > max)
        {
            while (getchar() != '\n'); // Clear invalid input
            printf("Invalid input! Please enter a number between %d and %d.\n", min, max);
        }

        else
        {
            return value;
        }
    }
}


// Function to enroll a club
void enroll_club(team_t teams[], int num_teams[])
{
    if (num_teams[0] >= NUM_TEAMS)
    {
        char message[50] = "Maximum number of teams reached.";
        handle_error(message);
        return;
    }

    printf("Enter club name: ");
    scanf(" %[^\n]", teams[num_teams[0]].team_name);
    teams[num_teams[0]].active_size = 0;
    num_teams[0]++;
    printf("Club enrolled successfully.\n");
}

// Function to add a player to a club
void add_player(team_t teams[], int num_teams)
{
    if (num_teams == 0)
    {
        char message[40] = "No clubs available. Enroll a club first.";
        handle_error(message);
        return;
    }

    // List clubs
    printf("Select a club:\n");
    for (int i = 0; i < num_teams; i++)
    {
        printf("%d. %s\n", i + 1, teams[i].team_name);
    }

    int choice = get_valid_int("Enter the club number: ", 1, num_teams);

    if (teams[choice - 1].active_size >= SQUAD_SIZE)
    {
        char message[20] = "Squad is full.";
        handle_error(message);
        return;
    }

    // Input player details
    player_t new_player;
    printf("Enter player name: ");
    scanf(" %[^\n]", new_player.name);

    // Check for duplicates
    for (int i = 0; i < teams[choice - 1].active_size; i++)
    {
        if (strcmp(teams[choice - 1].players[i].name, new_player.name) == 0)
        {
            char message[30] = "Duplicate player name.";
            handle_error(message);
            return;
        }
    }

    new_player.kit_number = get_valid_int("Enter kit number (1-99): ", 1, 99);

    printf("Enter date of birth (DD MM YYYY): ");
    while (scanf("%d %d %d", &new_player.age.day, &new_player.age.month, &new_player.age.year) != 3 ||
           new_player.age.day < 1 || new_player.age.day > 31 ||
           new_player.age.month < 1 || new_player.age.month > 12 ||
           new_player.age.year < 1900)
    {
        printf("Invalid date. Enter again (DD MM YYYY): ");
        while (getchar() != '\n'); // Clear invalid input
    }

    printf("Enter position: ");
    scanf(" %[^\n]", new_player.position);

    teams[choice - 1].players[teams[choice - 1].active_size] = new_player;
    teams[choice - 1].active_size++;
    printf("Player added successfully.\n");
}

// Function to search and update player information
void search_update(team_t teams[], int num_teams)
{
    if (num_teams == 0)
    {
        char message[30] = "No clubs available.";
        handle_error(message);
        return;
    }

    char search_term[MAX_NAME_LENGTH];
    printf("Enter player name to search: ");
    scanf(" %[^\n]", search_term);

    // Search for the player
    for (int i = 0; i < num_teams; i++)
    {
        for (int j = 0; j < teams[i].active_size; j++)
        {
            if (strcasecmp(teams[i].players[j].name, search_term) == 0)
            {
                printf("Player found: %s, Kit Number: %d\n",
                       teams[i].players[j].name, teams[i].players[j].kit_number);
                int update = get_valid_int("Update player details? (1 for Yes, 0 for No): ", 0, 1);
                if (update == 1)
                {
                    printf("Enter new position: ");
                    scanf(" %[^\n]", teams[i].players[j].position);
                    printf("Player details updated successfully.\n");
                }
                return;
            }
        }
    }

    char message[20] = "Player not found.";
    handle_error(message);
}

// Function to display club statistics
void display_club_statistics(team_t teams[], int num_teams)
{
    if (num_teams == 0)
    {
        char message[30] = "No clubs available.";
        handle_error(message);
        return;
    }

    for (int i = 0; i < num_teams; i++)
    {
        printf("\nClub: %s\n", teams[i].team_name);
        printf("Number of players: %d\n", teams[i].active_size);

        for (int j = 0; j < teams[i].active_size; j++)
        {
            printf("Player %d: %s, Kit Number: %d, Position: %s\n",
                   j + 1, teams[i].players[j].name, teams[i].players[j].kit_number, teams[i].players[j].position);
        }
    }
}

// Function to handle errors
void handle_error(char message[])
{
    printf("Error: %s\n", message);
}
