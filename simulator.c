#include <stdio.h>

#define PAGE_SIZE 1024 // 1kb
#define TOTAL_PAGES 8  // local memory pages
#define TOTAL_FRAMES 4 // local memory frames

int main()
{

    int pageTable[TOTAL_PAGES];
    int frameTable[TOTAL_FRAMES];
    int logicalAddress[10];
    int n, i, pageNum, offset;
    int nextFreeFrame = 0;

    // Initialize page table and frame table
    // initialize page table to -1 (indicating no pages are loaded)
    for (i = 0; i < TOTAL_PAGES; i++)
    {
        pageTable[i] = -1;
    }

    // initialize all frames as free (indicating no frames are occupied)
    for (i = 0; i < TOTAL_FRAMES; i++)
    {
        frameTable[i] = 0; // 0 indicates free frame
    }

    printf("Enter number of logical addresses (maximum is 10): ");
    scanf("%d", &n);

    if (n > 10 || n <= 0)
    {
        printf("Error: Invalid amount. Try again.\n");
        return 0;
    }

    // add max range argument
    printf("Enter %d logical addresses (0 - %d):\n", n, TOTAL_PAGES * PAGE_SIZE - 1);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &logicalAddress[i]);
    }

    printf("\n----------Output of Virtual Memory Simulation----------\n");

    for (i = 0; i < n; i++)
    {

        pageNum = logicalAddress[i] / PAGE_SIZE;
        offset = logicalAddress[i] % PAGE_SIZE;

        printf("\n+-----------------------------------------------+\n");
        printf("Logical Address: %d\n", logicalAddress[i]); // show the memory value
        printf("Page Number: %d, Offset: %d\n", pageNum, offset);

        // Checking if the page number is valid or not
        if (pageNum >= TOTAL_PAGES)
        {
            printf("Error: Invalid logical address. Page number %d does not exist.\n", pageNum);
            continue;
        }

        // Check if the page is already loaded in a frame
        if (pageTable[pageNum] != -1)
        {
            printf("Page %d is already loaded in Frame %d.\n", pageNum, pageTable[pageNum]);
        }
        else
        {
            // Page fault occurs
            printf("Page Fault! Page %d is not loaded in any frame.\n", pageNum);

            if (nextFreeFrame < TOTAL_FRAMES)
            {
                // Load the page into the next free frame
                pageTable[pageNum] = nextFreeFrame;
                frameTable[nextFreeFrame] = 1; // Mark frame as occupied
                printf("Loading Page %d into Frame %d.\n", pageNum, nextFreeFrame);
                nextFreeFrame++;
            }
            else
            {
                printf("No free frames available. Cannot load Page %d.\n", pageNum);
                continue;
            }
        }

        // Physical address calculation
        int frameNum = pageTable[pageNum];
        int physicalAddress = frameNum * PAGE_SIZE + offset;
        printf("Physical Address: %d\n", physicalAddress);
    }

    printf("\nSimulation completed. Press Enter to exit...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input

    return 0;
}
