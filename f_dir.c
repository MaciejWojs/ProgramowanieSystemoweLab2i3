#include <sys/types.h>
#include <errno.h> 
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uzycie: %s nazwa_katalogu\n", argv[0]);
        return 1;
    }

    struct stat st = { 0 };

    if (stat(argv[1], &st) == -1) {
        mkdir(argv[1], 0755);
    }

    return 0;
}