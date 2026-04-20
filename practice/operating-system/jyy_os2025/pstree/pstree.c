#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>

#define MAXNAME 256
const int MAXPROC = 2048;

struct Proc{
    int pid;
    int ppid;
    char name[MAXNAME];
};
typedef struct Proc Proc;

int BuildTree(int* cnt, Proc* data);
void dfs(int cnt, Proc* procs, int curId, bool sortByPid, bool showPid, int depth);

int main(int argc, char* argv[]) {
    bool showPid = false;
    bool sortByPid = false;
    for (int i=1;i<argc;i++) {
        if (strcmp(argv[i], "-V") == 0 || strcmp(argv[i], "--version") == 0) {
            printf("mypstree 1.0");
            return 0;
        } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--show-pids") == 0) {
            showPid = true;
        } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--numeric-sort") == 0) {
            sortByPid = true;
        } else {
            printf("invalid Parameters. Usage: ./pstree [-V --version] [-p --show-pids] [-n --numeric-sort]\n");
            return -1;
        }
    }
    int cnt = 0;
    Proc* data = (Proc*)malloc(MAXPROC * sizeof(Proc));
    BuildTree(&cnt, data);
    dfs(cnt, data, 1, sortByPid, showPid, 0);
    return 0;
}

bool isDigit(char* c);
Proc readProcStatus(char* id);
int cmp_name(const void* a, const void* b);
int cmp_pid(const void* a, const void* b);

void dfs(int cnt, Proc* procs, int curId, bool sortByPid, bool showPid, int depth) {
    int index = -1;
    for (int i=0;i<cnt;i++) {
        if (procs[i].pid == curId) {
            index = i;
            break;
        }
    }
    for (int i=0;i<depth;i++) {
        printf("\t");
    }
    if (showPid) {
        printf("%s(%d)\n", procs[index].name, procs[index].pid);
    } else {
        printf("%s\n", procs[index].name);
    }

    int childrenCnt = 0;
    for (int i=0;i<cnt;i++) {
        if (procs[i].ppid == curId) {
            childrenCnt++;
        }
    }
    Proc* children = (Proc*)malloc(childrenCnt * sizeof(Proc));
    childrenCnt = 0;
    for (int i=0;i<cnt;i++) {
        if (procs[i].ppid == curId) {
            children[childrenCnt++] = procs[i];
        }
    }

    if (sortByPid) {
        qsort(children, childrenCnt, sizeof(Proc), cmp_pid);
    } else {
        qsort(children, childrenCnt, sizeof(Proc), cmp_name);
    }

    for (int i=0;i<childrenCnt;i++) {
        dfs(cnt, procs, children[i].pid, sortByPid, showPid, depth+1);
    }
}

int cmp_name(const void* a, const void* b) {
    return strcmp(((Proc*)a)->name, ((Proc*)a)->name);
}

int cmp_pid(const void* a, const void* b) {
    return ((Proc*)a)->pid - ((Proc*)b)->pid;
}

// return value: 0 for success, other for wrong
int BuildTree(int* cnt, Proc* data) {
    DIR* d = opendir("/proc/");
    if (!d) {
        perror("cannot open directory.\n");
        return -1;
    } 
    
    struct dirent *ent;
    *cnt = 0;
    while ((ent = readdir(d)) != NULL) {
        if (strlen(ent->d_name) > 0 && isDigit(ent->d_name)) {
            data[*cnt] = readProcStatus(ent->d_name);
            (*cnt)++;
        }
    }
    if (closedir(d) == -1) { 
        perror("cannot close dir.\n");
        return -1;
    }
    return 0;
}

bool isDigit(char* c) {
    while (*c != 0) {
        if (*c < '0' || *c > '9') {
            return false;
        }
        c++;
    }
    return true;
}

Proc readProcStatus(char* id) {
    char buffer[100];
    sprintf(buffer, "/proc/%s/status", id);
    FILE* file = fopen(buffer, "r");
    Proc ret;
    ret.pid = ret.ppid = -1;
    if (file == NULL) {
        perror("cannot read proc status file");
        return ret;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Name:", 5) == 0) {
            sscanf(line, "Name:%s", ret.name);
        }
        if (strncmp(line, "Pid:", 4) == 0) {
            sscanf(line, "Pid:%d", &ret.pid);
        }
        if (strncmp(line, "PPid:", 5) == 0) {
            sscanf(line, "PPid:%d", &ret.ppid);
        }
    }
    fclose(file);
    return ret;
}