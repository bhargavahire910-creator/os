#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // argc will be n + 1 (program name is argv[0])
    // argv[1] to argv[n] will be our sorted numbers as strings

    int n = argc - 1;
    int arr[n];

    // Convert string arguments back to integers
    for (int i = 1; i <= n; i++) {
        arr[i-1] = atoi(argv[i]);
    }

    printf("\n[EXECVE PROGRAM] I have been loaded! Reversing array...\n");
    printf("[EXECVE PROGRAM] Reversed Array: ");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
