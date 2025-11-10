#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void bubbleSort(int arr[], int n, char* who) {
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
    // exact output format you requested
    printf("[%s] Sorted elements: ", who);
    for (i = 0; i < n; i++) { printf("%d ", arr[i]); }
    printf("\n");
}

int main() {
    int n;
    printf("\nEnter number of integers: ");
    if (scanf("%d", &n) != 1) return 1;
    
    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    pid_t pid = fork();

    if (pid == 0) {
        // --- CHILD PROCESS ---
        // sleep(10); // UN-COMMENT THIS FOR ORPHAN DEMO
        
        printf("\n[CHILD] My Parent ID is: %d\n", getppid());
        bubbleSort(arr, n, "CHILD");
        printf("[CHILD] Finished and exiting.\n");
    } 
    else if (pid > 0) {
        // --- PARENT PROCESS ---
        printf("\n[PARENT] Created child with PID: %d\n", pid);
        
        printf("[PARENT] Sorting now... (Child may be a Zombie if it finishes first)\n");
        sleep(5); // COMMENT OUT FOR ORPHAN DEMO
        
        bubbleSort(arr, n, "PARENT");

        wait(NULL); // COMMENT OUT FOR ORPHAN DEMO
        printf("[PARENT] Finished and exiting.\n");
    }
    else {
        perror("Fork failed");
        return 1;
    }
    
    return 0;
}
