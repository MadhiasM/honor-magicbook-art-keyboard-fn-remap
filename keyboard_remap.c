#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *dev = "/dev/input/event3"; // Passe ggf. an
    if (argc > 1) {
        dev = argv[1];
    }

    int fd = open(dev, O_RDONLY);
    if (fd < 0) {
        perror("Opening device");
        return 1;
    }

    struct input_event ev;
    printf("Listening on %s ...\n", dev);

    while (1) {
        ssize_t n = read(fd, &ev, sizeof(ev));
        if (n == (ssize_t)sizeof(ev)) {
            if (ev.type == EV_KEY) {
                printf("EV_KEY code=0x%x value=%d\n", ev.code, ev.value);
            } else if (ev.type == EV_MSC && ev.code == MSC_SCAN) {
                printf("EV_MSC MSC_SCAN scan code=0x%x\n", ev.value);
            } else {
                printf("type=%d code=%d value=%d\n", ev.type, ev.code, ev.value);
            }
        } else if (n < 0) {
            if (errno == EINTR) continue;
            perror("read");
            break;
        } else {
            fprintf(stderr, "Short read\n");
            break;
        }
    }

    close(fd);
    return 0;
}
