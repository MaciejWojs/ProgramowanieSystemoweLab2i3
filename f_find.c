#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
// WORK IN PROGRESS

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Uzycie %s nazwa_pliku wzorzec \n", argv[0]);
        return 1;
    }
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
        case ENOENT:
            perror("BLAD: PLIK NIE ISTNIEJE\n");
            return 6;
        default:
            perror("BLAD: NIEZNANY PROBLEM\n");
            return 1;
        }
        close(deskryptor);
    } else {
        printf("Jest OK\n");


        ssize_t ret;
        char buf[1024];
        size_t len = sizeof(buf);
        char* ptr = buf;

        while (len != 0 && (ret = read(deskryptor, ptr, len)) != 0) {
            if (ret == -1) {
                if (errno == EINTR) {
                    continue;
                }
                perror("read");
                break;
            }
            len -= ret;
            ptr += ret;
        }
        close(deskryptor);

        printf("Read: %.*s\n", (int)len, buf);

        int current_found = 0;
        int size = strlen(argv[2]);
        printf("size: %d\n", size);
        for (size_t i = 0; i < sizeof(buf); i++) {
            // Sprawdzamy, czy mamy wystarczająco miejsca w buforze
            // if (i + size > sizeof(buf)) {
            //     printf("Nie znaleziono wzorca, jest on za duży\n");
            //     break;  // Koniec bufora, nie można znaleźć pełnego wzorca
            // }

            current_found = 0;  // Resetuj licznik na początku sprawdzania nowej pozycji

            // Sprawdź, czy wzorzec pasuje od pozycji i
            for (size_t j = 0; j < size; j++) {
                if (buf[i + j] == argv[2][j]) {
                    current_found++;
                } else {
                    break;  // Przerwij przy pierwszym niedopasowaniu
                }
            }

            // Jeśli znaleziono cały wzorzec
            if (current_found == size) {
                printf("Znaleziono wzorzec na pozycji %zu do %zu\n", i + 1, i + size + 1);
                break;
            }
        }

        if (current_found != size) {
            printf("Nie znaleziono wzorca\n");
        }
        return 0;
    }
}