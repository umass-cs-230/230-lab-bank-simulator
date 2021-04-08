#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int cookie_maker(int read_pipe, int write_pipe) {
    char message[25];
    int num_bytes;

    // Cookie Maker reading a string from Cookie Monster
    if ((num_bytes = read(read_pipe, message, 25)) == -1) {
        perror("Cookie Maker failed to read from pipe");
        return 1;
    }
    printf("Cookie Maker read: %s (%d bytes)\n", message, num_bytes);

    // Cookie Maker writes a string to Cookie Monster
    strcpy(message, "You got cookies!");
    num_bytes = strlen(message) + 1;
    printf("Cookie Maker writing: %s (%d bytes)\n", message, num_bytes);
    if ((num_bytes = write(write_pipe, message, num_bytes)) == -1) {
        perror("Cookie Maker failed to write to pipe");
        return 1;
    }

    return 0;
}


int cookie_monster(int read_pipe, int write_pipe) {
    char message[25];
    int num_bytes;

    // Cookie Monster writes a string to Cookie Maker
    strcpy(message, "I want cookies!");
    num_bytes = strlen(message) + 1;
    printf("Cookie Monster writing: %s (%d bytes)\n", message, num_bytes);
    if ((num_bytes = write(write_pipe, message, num_bytes)) == -1) {
        perror("Cookie Monster failed to write to pipe");
        return 1;
    }

    // Cookie Monster reads a string from Cookie Maker
    if ((num_bytes = read(read_pipe, message, 25)) == -1) {
        perror("Cookie Monster failed to read from pipe");
        return 1;
    }
    printf("Cookie Monster read: %s (%d bytes)\n", message, num_bytes);

    return 0;
}

int main() {
    int one_to_two[2];
    int two_to_one[2];

    if (pipe(one_to_two) == -1) {
        perror("could not create pipe one_to_two");
        exit(1);
    }

    if (pipe(two_to_one) == -1) {
        perror("could not create pipe two_to_one");
        exit(1);
    }

    if (fork() == 0) {
        // Child 1

        // First, we close the read end of the pipe.
        close(one_to_two[0]);

        // Next, we close the write end of the other pipe.
        close(two_to_one[1]);

        // Lastly, we pass the read and write ends of the different
        // pipes to the child_one function.
        exit(cookie_maker(two_to_one[0], one_to_two[1]));
    }

    if (fork() == 0) {
        // Child 2

        // First, we close the read end of the pipe.
        close(two_to_one[0]);

        // Next, we close the write end of the other pipe.
        close(one_to_two[1]);

        // Lastly, we pass the read and write ends of the different
        // pipes to the child_two function.
        exit(cookie_monster(one_to_two[0], two_to_one[1]));
    }

    wait(NULL);
    printf("The parent cleaned up the cookie mess!\n");
}
