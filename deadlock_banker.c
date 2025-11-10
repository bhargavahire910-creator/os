#include <stdio.h>
#include <stdbool.h>

int main() {
    // n = number of processes, m = number of resource types
    int n, m, i, j, k;

    printf("Enter the number of Processes (n): ");
    if (scanf("%d", &n) != 1) return 1;
    printf("Enter the number of Resource Types (m): ");
    if (scanf("%d", &m) != 1) return 1;

    // Declare matrices for standard Banker's Algorithm structures.
    // alloc[i][j]: Number of resources of type j currently allocated to process i.
    // max[i][j]: Maximum resources of type j that process i may request in total.
    // need[i][j]: Resources process i still needs to complete (max - alloc).
    // avail[j]: Number of resources of type j currently free in the system.
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10];

    // --- 1. Input Allocation Matrix ---
    printf("\n--- Enter Allocation Matrix ---\n");
    for (i = 0; i < n; i++) {
        printf("Process P%d (enter %d values): ", i, m);
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // --- 2. Input Max Matrix & Calculate Need Matrix ---
    printf("\n--- Enter Max Matrix ---\n");
    for (i = 0; i < n; i++) {
        printf("Process P%d (enter %d values): ", i, m);
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            // Vital step: Need = Max - Allocation
            // This tells us how many MORE resources each process might ask for.
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // --- 3. Input Available Resources ---
    printf("\n--- Enter Available Resources ---\n");
    printf("Enter %d values: ", m);
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // =============================================================
    // === BANKER'S SAFETY ALGORITHM STARTS HERE ===
    // =============================================================

    // 'finish' array: keeps track of which processes have successfully "completed"
    bool finish[10] = {false}; 
    // 'safeSeq' array: stores the order of processes that guarantees safety
    int safeSeq[10];
    // 'work' array: a temporary copy of 'avail'. We use this to simulate 
    // resources being given out and returned without changing the real 'avail'.
    int work[10];
    
    // Initialize Work = Available initially
    for (i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0; // Counter for how many processes are in the safe sequence so far

    // Loop until all processes are finished (safe) or we get stuck (unsafe)
    while (count < n) {
        bool found = false; // Flag to check if we found ANY process in this pass

        // Iterate through all processes to find one that can finish
        for (i = 0; i < n; i++) {
            // Step A: Find a process that is NOT finished yet
            if (finish[i] == false) {
                
                // Step B: Check if this process's Needs can be met by current Work
                bool canAllocate = true;
                for (j = 0; j < m; j++) {
                    // If Need > Work for ANY resource type, we can't fulfill request
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                // Step C: If needs can be met, simulate execution
                if (canAllocate) {
                    // 1. Simulate process 'i' finishing and returning its current 
                    //    allocation back to the 'work' pool.
                    for (k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }
                    // 2. Add this process to our safe sequence
                    safeSeq[count++] = i;
                    // 3. Mark it as finished
                    finish[i] = true;
                    found = true;
                    // (Optional: printf("P%d can finish, new work available...\n", i));
                }
            }
        }

        // CRITICAL CHECK: If we went through the WHOLE list of processes 
        // and couldn't find even ONE that could finish, we are stuck.
        // This means the system is in an UNSAFE state (deadlock possible).
        if (found == false) {
            printf("\nSystem is in UNSAFE state! Deadlock is possible.\n");
            return 0; // Exit program immediately
        }
    }

    // If the loop finishes with count == n, we found a complete safe sequence.
    printf("\nSystem is in SAFE state.\nSafe Sequence is: ");
    for (i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if (i < n - 1) printf(" -> ");
    }
    printf("\n");

    return 0;
}
