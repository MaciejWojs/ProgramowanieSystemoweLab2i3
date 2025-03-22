#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int errno;
    int deskryptor;
    int kod_bledu;
    errno = 0;
    deskryptor = open(argv[1], O_RDWR);
    kod_bledu = errno;

    if (deskryptor < 1) {
        switch (kod_bledu) {
        case EACCES:
            perror("BLAD: PROBLEM Z PRAWAMI DOSTEPU\n");
            return 5;
        default:
            perror("BLAD: NIEZNANY PROBLEM\n");
            return 1;
        }
    } else {
        printf("Jest OK\n");
    }

    close(deskryptor);

    return 0;
}