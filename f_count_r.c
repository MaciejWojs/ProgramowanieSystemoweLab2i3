#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
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

        int rows_count = 1;
        for (size_t i = 0; i < sizeof(buf); i++) {
            if (buf[i] == '\n') {
                rows_count++;
            }
        }
        printf("Rows count: %d\n", rows_count);
    }

    close(deskryptor);

    return 0;
}