#include <dirent.h>
#include "helper.h"

int main(int argc, char *argv[]) {
    struct dirent *pdirent;
    DIR *pd;
    int fd;
    if (argc < 2) {
        printf("Usage: findkeyb <dirname>\n");
        return 1;
    }

    // open the directory, which returns a descriptor
    pd = opendir(argv[1]);

    if (pd == NULL) {
        printf("Cannot open directory");
        return 1;
    }

    // loop through the items in the directory
    while ((pdirent = readdir(pd)) != NULL) {
        if ((fd = open(pdirent->d_name, O_RDONLY)) < 0) {
            printf("Unable to open %s \n ", pdirent->d_name);
        } else {
            printf("%s \n ", pdirent->d_name);
            obtainInfo(fd);
        }
    }
}
