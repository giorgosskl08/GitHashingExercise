#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Custom signal handler for SIGINT
void custom_sigint_handler(int sig) {
    static int sigint_count = 0; // Track how many times SIGINT was caught
    sigint_count++;
    
    printf("\nCaught SIGINT (signal number: %d) — count: %d\n", sig, sigint_count);
    
    if (sigint_count >= 2) {
        printf("Restoring default SIGINT behavior. Next SIGINT will terminate the program.\n");
        // Restore default handler for SIGINT
        if (signal(SIGINT, SIG_DFL) == SIG_ERR) {
            perror("Error while restoring default SIGINT handler");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    // Register the custom signal handler for SIGINT
    if (signal(SIGINT, custom_sigint_handler) == SIG_ERR) {
        perror("Error while setting signal handler");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for SIGINT (Press Ctrl+C to send SIGINT)...\n");

    // Infinite loop to keep the program running until Ctrl+C is pressed three times
    while (1) {
        pause(); // Wait for any signal
    }

    return 0;
}
