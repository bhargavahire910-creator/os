#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

// Comparison function for qsort (built-in is easier here)
int compare(const void * a, const void * b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1) return 1;
    
    // Using VLA for simplicity
    int arr[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    // Parent sorts array first
    qsort(arr, n, sizeof(int), compare);
    printf("\n[PARENT] Sorted array: ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");

    pid_t pid = fork();

    if (pid == 0) {
        // --- CHILD PROCESS ---
        printf("[CHILD] I will now EXECVE into the 'reverse' program.\n");

        // Prepare arguments for execve
        // We need: program name + n numbers + NULL terminator = n + 2 slots
        char *args[n + 2];
        args[0] = "./rever"; 

        // Convert integers to strings for command line args
        for (int i = 0; i < n; i++) {
            args[i+1] = malloc(12); // 12 bytes is enough for a 32-bit int string
            sprintf(args[i+1], "%d", arr[i]);
        }
        args[n+1] = NULL; // List must end with NULL

        // Replace current process with ./reverse
        // IF THIS FAILS: make sure you compiled reverse.c into an executable named 'reverse'
        // and it is in the SAME folder as this program.
        execve(args[0], args, NULL);
        
        // If we get here, execve failed!
        perror("execve failed");
        exit(1);
    } 
    else if (pid > 0) {
        // --- PARENT PROCESS ---
        wait(NULL); // Wait for child (which is now the 'reverse' program) to finish
        printf("[PARENT] Child finished. Main program exiting.\n");
    }
    else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}
