
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

// --- Bubble Sort Function ---
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int main() {
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1) return 1;
    int arr[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    // Parent sorts array first using Bubble Sort
    bubbleSort(arr, n);

    printf("\n[PARENT] Sorted array: ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");

    pid_t pid = fork();

    if (pid == 0) {
        // --- CHILD PROCESS ---
        printf("[CHILD] I will now EXECVE into the 'reverse' program.\n");
        char *args[n + 2];
        args[0] = "./rever"; 

        for (int i = 0; i < n; i++) {
            args[i+1] = malloc(12);
            sprintf(args[i+1], "%d", arr[i]);
        }
        args[n+1] = NULL;

        execve(args[0], args, NULL);
        
        perror("execve failed");
        exit(1);
    } 
    else if (pid > 0) {
        // --- PARENT PROCESS ---
        wait(NULL);
        printf("[PARENT] Child finished. Main program exiting.\n");
    }
    else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}
