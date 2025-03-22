#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s file_name n_bytes_to_read\n", argv[0]);
        return 1;
    }

    int errno;
    int deskryptor;
    int kod_bledu;
    errno = 0;
    deskryptor = open(argv[1], O_RDONLY);

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
        int number_of_bytes = atoi(argv[2]);
        if (number_of_bytes < 1) {
            printf("BLAD: NIEPOPRAWNA LICZBA BAJTOW DO ODCZYTU\n");
            return 1;
        }
        printf("Odczytuje %d bajtow\n", number_of_bytes);

        char* buffer = malloc(number_of_bytes * sizeof(char));
        if (buffer == NULL) {
            perror("BLAD: NIE UDALO SIE ZAALOKOWAC PAMIECI\n");
            return 1;
        }

        int status = read(deskryptor, buffer, number_of_bytes);
        if (status == -1) {
            perror("BLAD: NIE UDALO SIE ODCZYTAC Z PLIKU\n");
            free(buffer);
            return 1;
        } else {
            if (status < number_of_bytes) {
                buffer[status] = '\0';
            }
            printf("Odczytano %d bajtów\n", status);
            printf("Zawartość pliku: %.*s\n", number_of_bytes, buffer);
        }
        free(buffer);
    }

    close(deskryptor);
}