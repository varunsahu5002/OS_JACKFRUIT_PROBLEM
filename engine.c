#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mount.h>

#define STACK_SIZE (1024 * 1024)

char *rootfs;
char *cmd;

/* ================= CHILD PROCESS ================= */
int child_func(void *arg) {
    // Set hostname (optional)
    sethostname("container", 9);

    // Change root filesystem
    if (chroot(rootfs) != 0) {
        perror("chroot failed");
        return 1;
    }

    chdir("/");

    // Mount proc for ps inside container
    mount("proc", "/proc", "proc", 0, NULL);

    // Execute command
    char *args[] = {"/bin/sh", "-c", cmd, NULL};
    execvp("/bin/sh", args);

    perror("exec failed");
    return 1;
}

/* ================= MAIN ================= */
int main(int argc, char *argv[]) {

    /* ================= PS COMMAND ================= */
    if (argc >= 2 && strcmp(argv[1], "ps") == 0) {
        printf("=== Running Containers ===\n");
        system("ps aux | grep './engine start' | grep -v grep");
        return 0;
    }

    /* ================= LOGS COMMAND ================= */
    if (argc >= 3 && strcmp(argv[1], "logs") == 0) {
        char filename[100];
        sprintf(filename, "log_%s.txt", argv[2]);

        printf("=== Logs for %s ===\n", argv[2]);

        char command[150];
        sprintf(command, "cat %s", filename);
        system(command);

        return 0;
    }

    /* ================= START COMMAND ================= */
    if (argc < 5) {
        printf("Usage:\n");
        printf("  ./engine start <name> <rootfs> <command>\n");
        printf("  ./engine ps\n");
        printf("  ./engine logs <name>\n");
        return 1;
    }

    if (strcmp(argv[1], "start") != 0) {
        printf("Unknown command\n");
        return 1;
    }

    rootfs = argv[3];
    cmd = argv[4];

    char *stack = malloc(STACK_SIZE);
    if (!stack) {
        perror("malloc failed");
        return 1;
    }

    pid_t pid = clone(child_func, stack + STACK_SIZE,
        CLONE_NEWPID | CLONE_NEWUTS | CLONE_NEWNS | SIGCHLD, NULL);

    if (pid < 0) {
        perror("clone failed");
        return 1;
    }

    printf("container started pid=%d\n", pid);

    waitpid(pid, NULL, 0);

    return 0;
}
