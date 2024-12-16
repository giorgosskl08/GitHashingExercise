#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGINT
void sigint_handler(int sig) {
    printf("\nSIGINT signal caught!\n");
    exit(0); // Gracefully terminate the program
}

int main() {
    // Register the SIGINT handler
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("Error while setting signal handler");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for SIGINT (Press Ctrl+C to send SIGINT)...\n");

    // Infinite loop to keep the program running until Ctrl+C is pressed
    while (1) {
        pause(); // Wait for any signal
    }

    return 0;
}
