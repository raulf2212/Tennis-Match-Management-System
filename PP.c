#include <stdio.h>
#include <string.h>

#define PLAYER_FILE "players.csv"
#define MATCH_FILE "matches.csv"

struct Player {
    char name[50];
    int wins;
    int losses;
};
struct Match {
    char p1name[50];
    char p2name[50];
    int p1score;
    int p2score;
};

struct Player players[50];
struct Match matches[50];
int matchCount=0;
int playerCount=0;

void LoadData() {
    FILE *file;

    file = fopen(PLAYER_FILE, "r");
    if (file) {
        while (fscanf(file, "%[^,],%d,%d\n", players[playerCount].name, &players[playerCount].wins, &players[playerCount].losses) == 3) {
            playerCount++;
        }
        fclose(file);
    }

    file = fopen(MATCH_FILE, "r");
    if (file) {
        while (fscanf(file, "%[^,],%[^,],%d,%d\n", matches[matchCount].p1name, matches[matchCount].p2name, &matches[matchCount].p1score, &matches[matchCount].p2score) == 4) {
            matchCount++;
        }
        fclose(file);
    }
}

void SaveData() {
    FILE *file;

    file = fopen(PLAYER_FILE, "w");
    if (file) {
        for (int i = 0; i < playerCount; i++) {
            fprintf(file, "%s,%d,%d\n", players[i].name, players[i].wins, players[i].losses);
        }
        fclose(file);
    }

    file = fopen(MATCH_FILE, "w");
    if (file) {
        for (int i = 0; i < matchCount; i++) {
            fprintf(file, "%s,%s,%d,%d\n", matches[i].p1name, matches[i].p2name, matches[i].p1score, matches[i].p2score);
        }
        fclose(file);
    }
}

void clearScreen() {
    int x;
    for ( x = 0; x < 10; x++ )
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
}

int getPlayerIndex(char *name) {
    for ( int i = 0; i < playerCount; i++ )
        if (strcmp( players[i].name, name ) == 0) return i;

    strcpy(players[playerCount].name, name);
    players[playerCount].wins = players[playerCount].losses = 0;
    return playerCount++;
}

void Header1() {
    printf("------------------\n");
    printf("1 - Add a match\n");
    printf("2 - Leaderboard\n");
    printf("3 - Look at a Player's history\n");
    printf("4 - Exit\n");
    printf("------------------\n");
}

void Header2() {
    printf("------------------------------------\n");
    printf("Please select a player to look at (Enter the number assigned to the player):\n");
    for ( int i = 0; i < playerCount; i++ ) {
        printf("%d - %s \n",i,players[i].name);
    }
    printf("%d - Exit\n",playerCount);
    printf("------------------------------------\n");
}

void subMenu(int option2) {
    clearScreen();
    int idx = -1;
        for (int i = 0; i < playerCount; i++) {
            if (strcmp(players[i].name,players[option2].name) == 0) {
                idx = i;
                break;
            }
        }
    if (idx>=0) {
        printf("\nMatch history for %s:\n", players[idx].name);
        for (int i = 0; i < matchCount; i++) {
            if (strcmp(matches[i].p1name, players[idx].name) == 0 || strcmp(matches[i].p2name, players[idx].name) == 0) {
                printf("\033[31m%s\033[0m \033[91m%d\033[0m / \033[94m%d\033[0m \033[34m%s\033[0m\n",
                       matches[i].p1name, matches[i].p1score, matches[i].p2score, matches[i].p2name);
            }
        }
        printf("\n\033[33mWins\033[0m: \033[33m%d\033[0m, \033[38;5;124mLosses\033[0m: \033[38;5;124m%d\033[0m\n",
               players[idx].wins, players[idx].losses);

        printf("Press Enter to return...");
        getchar(); getchar();
    }

}

int PlayerHistory() {
        int option2;
        do {
            clearScreen();
            Header2();
            scanf("%d", &option2);
            subMenu(option2);
        }while (option2>=0 && option2 < playerCount);
        return 0;
}

void AddMatch() {
    clearScreen();
    printf("Enter match (Format : \033[31mPlayer1\033[0m \033[91mScore1\033[0m / \033[94mScore2\033[0m \033[34mPlayer2\033[0m): \n");


    char p1name[50],p2name[50];
    int p1score,p2score;
    scanf("%s %d / %d %s",p1name,&p1score,&p2score,p2name);
    if (p1score<0 || p1score>21 || p2score<0 || p2score>21) {
        printf("Invalid Input\n");
    }else {
        strcpy(matches[matchCount].p1name, p1name);
        strcpy(matches[matchCount].p2name, p2name);
        matches[matchCount].p1score = p1score;
        matches[matchCount].p2score = p2score;
        matchCount++;
        int idx1 = getPlayerIndex(p1name);
        int idx2 = getPlayerIndex(p2name);

        if (p1score > p2score) {
            players[idx1].wins++;
            players[idx2].losses++;
        }
        else {
            players[idx2].wins++;
            players[idx1].losses++;
        }

        FILE *file = fopen(MATCH_FILE, "a");
        if (file) {
            fprintf(file, "%s,%s,%d,%d\n", p1name, p2name, p1score, p2score);
            fclose(file);
        }

        SaveData();

        printf("Match recorded!\nPress Enter to return...");
        }
    getchar(); getchar();
}

void Leaderboard() {
    clearScreen();
    struct Player temp;
    for (int i = 0; i < playerCount - 1; i++) {
        for (int j = 0; j < playerCount - i - 1; j++) {
            if (
                players[j].wins < players[j + 1].wins ||
                (players[j].wins == players[j + 1].wins && players[j].losses > players[j + 1].losses)
            ) {
                temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    printf("Leaderboard:\n%-15s \033[33mWins\033[0m  \033[31mLosses\033[0m\n", "Player");
    for (int i = 0; i < playerCount; i++)
        printf("%-15s \033[33m%d\033[0m     \033[31m%d\033[0m\n", players[i].name, players[i].wins, players[i].losses);


    printf("Press Enter to return...");
    getchar(); getchar();

}

void MainMenu(int option) {
    switch (option) {
        case 1:
            AddMatch();
        break;
        case 2:
            Leaderboard();
        break;
        case 3:
            PlayerHistory();
        break;
    }
}

int main() {
    LoadData();

    int option;
    do {
        clearScreen();
        Header1();
        printf("Enter your option: ");
        scanf("%d", &option);
        MainMenu(option);
    }while (option>0 && option <=3);

    SaveData();
    return 0;

}