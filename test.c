#include <stdio.h>

#include <errno.h>  /* errno */
#include <string.h> /* strerror() */

#include <fcntl.h>     /* open() */
#include <sys/ioctl.h> /* ioctl() */
#include <sys/time.h>  /* timeval */
#include <unistd.h>    /* close() */

#define EV_BUF_SIZE 16

/* in order for this to work cross platform, we define input_event
 * here. */

struct input_event {
    struct timeval time;
    unsigned short type;
    unsigned short code;
    signed int value;
};

void obtainInfo(int fd) {
    int sz;
    unsigned i;

    /* A few examples of information to gather */
    unsigned version;
    unsigned short id[4]; /* or use struct input_id */
    char name[256] = "N/A";

    struct input_event ev[EV_BUF_SIZE]; /* Read up to N events ata time */

    ioctl(fd, 0x01, &version);
    ioctl(fd, 0x02, id);
    ioctl(fd, 0x06, name);

    fprintf(stderr,
            "Name      : %s\n"
            "Version   : %d.%d.%d\n"
            "ID        : Bus=%04x Vendor=%04x Product=%04x Version=%04x\n"
            "----------\n",
            name,

            version >> 16, (version >> 8) & 0xff, version & 0xff,

            id[0],  // bustype
            id[1],  // vendor
            id[2],  // product
            id[3]   // version
    );
}

int main(int argc, char *argv[]) {
    int fd;
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        fprintf(stderr,
                "ERR %d:\n"
                "Unable to open `%s'\n"
                "%s\n",
                errno, argv[1], strerror(errno));
    }

    obtainInfo(fd);
}
