#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uzycie: %s nazwa_pliku\n", argv[0]);
        return 1;
    }

    int errno;
    int deskryptor;
    int kod_bledu;
    errno = 0;
    deskryptor = open(argv[1], O_RDONLY);
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
        ssize_t ret_test;
        char bufor1;
        int bytes_read = 0;
        // Pobranie ilości znaków/bajtow w pliku
        while ((ret_test = read(deskryptor, &bufor1, 1)) != 0) {
            if (ret_test == -1) {
                if (errno == EINTR) {
                    continue;
                }
                perror("read");
                break;
            }
            // printf("%c", bufor1);
            bytes_read++;
        }
        printf("Przeczytano %d bajtow z pliku %s\n", bytes_read, argv[1]);

        char buf[bytes_read];
        close(deskryptor);

        deskryptor = open(argv[1], O_RDONLY);
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
            read(deskryptor, &buf, bytes_read);

            int deskryptor2;
            int kod_bledu2;
            errno = 0;

            deskryptor2 = open("kopia.txt", O_RDWR | O_CREAT, 0777);
            kod_bledu2 = errno;
            if (deskryptor2 < 1) {
                switch (kod_bledu2) {
                case EACCES:
                    perror("BLAD: PROBLEM Z PRAWAMI DOSTEPU PLIK: kopia.txt\n");
                    return 5;
                default:
                    perror("BLAD: NIEZNANY PROBLEM\n");
                    return 1;
                }
            } else {

                int status = write(deskryptor2, buf, bytes_read);
                if (status == 0 || status == -1) {
                    perror("BLAD: NIE UDALO SIE ZAPISAC DO PLIKU\n");
                    return 1;
                }
                printf("Zapisano %d bajtow do pliku kopia.txt\n", status);

            }
            close(deskryptor2);
        }
    }
    close(deskryptor);
}