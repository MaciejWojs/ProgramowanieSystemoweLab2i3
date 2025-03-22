#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s file_name perms\n", argv[0]);
        return 1;
    }
    int errno;
    int deskryptor;
    int kod_bledu;
    errno = 0;
    kod_bledu = errno;

    deskryptor = open(argv[1], O_CREAT, argv[2]);

    if (deskryptor == -1) {
        switch (errno) {
        case EACCES:
            perror("BLAD: PROBLEM Z PRAWAMI DOSTEPU");
            return 5;
        default:
            perror("BLAD: NIEZNANY PROBLEM");
            return 1;
        }
    } else {
        printf("Jest OK\n");
    }

    close(deskryptor);
}