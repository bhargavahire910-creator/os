# include <stdio.h>
 int main(){
    int pages[30], frames[10], n, frameCount, front = 0, pageFaults = 0;
    printf("Enter the No. of Pages: ");
    scanf("%d", &n);
    printf("Enter the Reference String: ");
    for(int i = 0;i < n;i++){
        scanf("%d", &pages[i]);
    }
    printf("Enter the No. of Frames (min 3): ");
    scanf("%d", &frameCount);
    for(int i = 0;i < frameCount;i++){
        frames[i] = -1;
    }
    printf("\nFCFS PAGE REPLACEMENT: \n");
    for(int i = 0; i < n;i++){
        int found = 0;
        for(int j = 0; j < frameCount; j++){
            if(frames[j] == pages[i]){
                found = 1;
                break;
            }
        }
        if(!found){
            frames[front] = pages[i];
            front = (front + 1) % frameCount;
            pageFaults++;
        }
        printf("Step %d: ",i + 1);
        for(int j = 0;j < frameCount;j++){
            if(frames[j] != -1){
                printf("%d ",frames[j]);
            }
        }
        printf("\n");
    }
    printf("Total Page Faults = %d\n",pageFaults);
    return 0;
 }