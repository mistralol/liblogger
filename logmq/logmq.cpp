
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <string>

static void print_help(FILE *fp, char *app)
{
        fprintf(fp, "Usage: %s (<options>)\n", app);
        fprintf(fp, "\n");
        fprintf(fp, " -h Print this help\n");
        fprintf(fp, "\n");
}

int main(int argc, char **argv) {
    std::string QName = "/liblogger";
    const char *ops = "hq?";
    int opt = 0;

    while( (opt = getopt(argc, argv, ops)) != -1) {
        switch(opt) {
            case 'h':
                print_help(stdout, argv[0]);
                exit(EXIT_SUCCESS);
                break;
            case 'q':
                QName = optarg;
                break;
            default:
                printf("Unknown option '%c'\n", opt);
                print_help(stderr, argv[0]);
                exit(EXIT_FAILURE);
                break;
        }
    }
    
    mq_unlink(QName.c_str());

    mqd_t qid = mq_open(QName.c_str(), O_RDONLY | O_CREAT | O_EXCL, 0644, NULL);
    if (qid < 0) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    size_t buflen = 65535;
    char *buf = (char *) malloc(buflen);

    bool running = true;
    do {
        unsigned int prio = 0;
        ssize_t ret = mq_receive(qid, buf, buflen - 2, &prio);
        if (ret > 3) {
            buf[ret] = 0;
            const int type = atoi(buf);
            const char *msg = &buf[1];
            printf("GOT MSG %d %s\n", type, msg);

        } else {
            perror("mq_receive");
            running = false;
        }

    } while(running);

    if (mq_close(qid) < 0) {
        perror("mq_close");
        abort();
    }

    free(buf);

    return EXIT_SUCCESS;
}
