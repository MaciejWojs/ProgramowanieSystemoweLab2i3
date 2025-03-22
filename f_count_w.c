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

        ssize_t ret;
        char buf[2048];
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

        int words_count = 0;
        int in_word = 0;
        size_t read_size = ptr - buf; // Calculate how much was actually read

        for (size_t i = 0; i < read_size; i++) {
            if (buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\t' && buf[i] != '\0') {
                if (!in_word) {
                    words_count++;
                    in_word = 1;
                }
            } else {
                in_word = 0;
            }
        }

        printf("Words count: %d\n", words_count);
    }

    close(deskryptor);

    return 0;
}