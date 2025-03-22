#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s file_name text_to_append\n", argv[0]);
        return 1;
    }

    int errno;
    int deskryptor;
    int kod_bledu;
    errno = 0;
    deskryptor = open(argv[1], O_CREAT | O_RDWR | O_APPEND, 0777);

    if (deskryptor < 1) {
        switch (errno) {
        case EACCES:
            perror("BLAD: PROBLEM Z PRAWAMI DOSTEPU\n");
            return 5;
        default:
            perror("BLAD: NIEZNANY PROBLEM\n");
            return 1;
        }
    } else {

        int status = write(deskryptor, argv[2], sizeof(argv[2]));
        if (status == -1) {
            perror("BLAD: NIE UDALO SIE ZAPISAC DO PLIKU\n");
            return 1;
        } else {
            printf("Zapisano %d bajtów\n", status);
        }
    }

    close(deskryptor);

}