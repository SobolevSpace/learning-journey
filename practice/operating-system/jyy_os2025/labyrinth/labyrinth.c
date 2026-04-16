#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <testkit.h>
#include "labyrinth.h"

const char* dirs[] = {"up", "down", "left", "right"};
static const Position deltas[] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
};

int isValidDirection(const char* dir) {
    for (int i=0;i<sizeof(dirs)/sizeof(char*);i++) {
        if (strcmp(dirs[i], dir) == 0) return i;
    }
    return -1;
}


void printUsage(void) {
    printf("Usage:\n");
    printf("  labyrinth --map map.txt --player id\n");
    printf("  labyrinth -m map.txt -p id\n");
    printf("  labyrinth --map map.txt --player id --move direction\n");
    printf("  labyrinth --version\n");
}

int main(int argc, char *argv[]) {
    Labyrinth labyrinth;
    char curPlayer = '0';
    const char* filename = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--version") == 0) {
            printf("Labyrinth Game Version: 1.0\n");
        } else if (i < argc - 1 && (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--map") == 0)) {
            i++;
            if (!loadMap(&labyrinth, argv[i])) {
                printf("Load Map Failed.\n");
                printUsage();
                return 1;
            }
            filename = argv[i];
        } else if (i < argc - 1 && (strcmp(argv[i], "--player") == 0 || strcmp(argv[i], "-p") == 0)) {
            i++;
            if (strlen(argv[i]) != 1 || !isValidPlayer(argv[i][0])) {
                printf("Unknown player.\n");
                printUsage();
                return 1;
            } else {
                curPlayer = argv[i][0];
                for (int r = 0; r < labyrinth.rows; r++) {
                    printf("%s\n", labyrinth.map[r]);
                }
            }
        } else if (i < argc - 1 && (strcmp(argv[i], "--move") == 0)) {
            i++;
            if (isValidDirection(argv[i]) == -1 || !movePlayer(&labyrinth, curPlayer, argv[i])) {
                printf("Move Not Valid.\n");
                printUsage();
                return 1;
            }
            saveMap(&labyrinth, filename);
        } else {
            printf("Unknown Parameters.\n");
            printUsage();
            return 1;
        }
    }
    return 0;
}

bool isValidPlayer(char playerId) {
    return playerId >= '0' && playerId <= '9';
}

bool loadMap(Labyrinth *labyrinth, const char *filename) {
    FILE* file = fopen(filename, "r");
    labyrinth->rows = 0;
    labyrinth->cols = 0;
    memset(labyrinth->map, 0, sizeof(labyrinth->map));
    if (file != NULL) {
        while (fscanf(file, "%s", labyrinth->map[labyrinth->rows]) == 1) {
            labyrinth->rows++;
        }
        labyrinth->cols = strlen(labyrinth->map[0]);
        fclose(file);
        return isConnected(labyrinth);
    } else {
        printf("cannot open file.\n");
    }
    return false;
}

Position findPlayer(Labyrinth *labyrinth, char playerId) {
    Position pos = {-1, -1};
    for (int i = 0; i<labyrinth->rows;i++) {
        for (int j=0;j<labyrinth->cols;j++) {
            if (labyrinth->map[i][j] == playerId) {
                pos.row = i;
                pos.col = j;
            }
        }
    }
    return pos;
}


bool isEmptySpaceOrPlayer(Labyrinth *labyrinth, int row, int col) {
    return row >= 0 && row < labyrinth->rows && col >=0 && col < labyrinth->cols && (labyrinth->map[row][col] == '.' || (labyrinth->map[row][col] >= '0' && labyrinth->map[row][col] <= '9'));
}

Position findFirstEmptySpace(Labyrinth *labyrinth) {
    Position pos = {-1, -1};
    for (int i=0;i<labyrinth->rows;i++) {
        for (int j=0;j<labyrinth->cols;j++) {
            if (pos.row == -1 && isEmptySpaceOrPlayer(labyrinth, i, j)) {
                pos.row = i;
                pos.col = j;
            }
        }
    }
    return pos;
}

bool isEmptySpace(Labyrinth *labyrinth, int row, int col) {
    return row >= 0 && row < labyrinth->rows && col >=0 && col < labyrinth->cols && labyrinth->map[row][col] == '.';
}


bool movePlayer(Labyrinth *labyrinth, char playerId, const char *direction) {
    Position curPlayerPos = findPlayer(labyrinth, playerId);
    if (curPlayerPos.row == -1) {
        curPlayerPos = findFirstEmptySpace(labyrinth);
        labyrinth->map[curPlayerPos.row][curPlayerPos.col] = playerId;
    }
    int dirId = isValidDirection(direction);
    Position newPos = deltas[dirId];
    newPos.row += curPlayerPos.row;
    newPos.col += curPlayerPos.col;
    if (isEmptySpace(labyrinth, newPos.row, newPos.col)) {
        labyrinth->map[curPlayerPos.row][curPlayerPos.col] = '.';
        labyrinth->map[newPos.row][newPos.col] = playerId;
        return true;
    }
    return false;
}

bool saveMap(Labyrinth *labyrinth, const char *filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return false;
    for (int i = 0; i < labyrinth->rows; i++) {
        fprintf(file, "%s\n", labyrinth->map[i]);
    }
    fclose(file);
    return true;
}

// Check if all empty spaces are connected using DFS
void dfs(Labyrinth *labyrinth, int row, int col, bool visited[MAX_ROWS][MAX_COLS]) {
    if (isEmptySpaceOrPlayer(labyrinth, row, col)) {
        visited[row][col] = true;
    }
    for (int deltaId = 0; deltaId < 4; deltaId++) {
        int newRow = row + deltas[deltaId].row;
        int newCol = col + deltas[deltaId].col;
        if (isEmptySpaceOrPlayer(labyrinth, newRow, newCol) && !visited[newRow][newCol]) {
            dfs(labyrinth, newRow, newCol, visited);
        }
    }
}

bool isConnected(Labyrinth *labyrinth) {
    bool visited[MAX_ROWS][MAX_COLS];
    memset(visited, 0, sizeof(visited));
    Position start = findFirstEmptySpace(labyrinth);
    dfs(labyrinth, start.row, start.col, visited);
    for (int i=0;i<labyrinth->rows;i++) {
        for (int j=0;j<labyrinth->cols;j++) {
            if (labyrinth->map[i][j] != '#' && !visited[i][j])  {
                return false;
            }
        }
    }
    return true;
}
