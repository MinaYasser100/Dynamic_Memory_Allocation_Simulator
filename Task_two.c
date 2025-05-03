#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Function prototypes
void fcfs(int queue[], int size, int head, int cylinders);
void scan(int queue[], int size, int head, int cylinders, int direction);
void cscan(int queue[], int size, int head, int cylinders, int direction);
void sort(int arr[], int size);
int get_direction();

int main() {
    int cylinders = 5000; // Total number of cylinders (0-4999)
    int head, size, algorithm_choice, direction;
    int *queue;
    
    printf("Enter the number of requests (1-1000): ");
    scanf("%d", &size);
    
    if (size < 1 || size > 1000) {
        printf("Invalid number of requests. Please enter between 1 and 1000.\n");
        return 1;
    }
    
    queue = (int *)malloc(size * sizeof(int));
    if (queue == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    
    printf("Enter the request queue (%d numbers between 0-4999):\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &queue[i]);
        if (queue[i] < 0 || queue[i] >= cylinders) {
            printf("Invalid cylinder number. Must be between 0-4999.\n");
            free(queue);
            return 1;
        }
    }
    
    printf("Enter the initial head position (0-4999): ");
    scanf("%d", &head);
    if (head < 0 || head >= cylinders) {
        printf("Invalid head position. Must be between 0-4999.\n");
        free(queue);
        return 1;
    }
    
    printf("\nSelect disk scheduling algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SCAN\n");
    printf("3. C-SCAN\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &algorithm_choice);
    
    if (algorithm_choice < 1 || algorithm_choice > 3) {
        printf("Invalid algorithm choice.\n");
        free(queue);
        return 1;
    }
    
    if (algorithm_choice == 2 || algorithm_choice == 3) {
        direction = get_direction();
    }
    
    printf("\nResults:\n");
    printf("Request queue: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", queue[i]);
    }
    printf("\nInitial head position: %d\n", head);
    
    switch (algorithm_choice) {
        case 1:
            printf("Algorithm: FCFS\n");
            fcfs(queue, size, head, cylinders);
            break;
        case 2:
            printf("Algorithm: SCAN\n");
            printf("Direction: %s\n", direction == 1 ? "Right (toward higher cylinders)" : "Left (toward lower cylinders)");
            scan(queue, size, head, cylinders, direction);
            break;
        case 3:
            printf("Algorithm: C-SCAN\n");
            printf("Direction: %s\n", direction == 1 ? "Right (toward higher cylinders)" : "Left (toward lower cylinders)");
            cscan(queue, size, head, cylinders, direction);
            break;
    }
    
    free(queue);
    return 0;
}

int get_direction() {
    int direction;
    printf("Select head movement direction:\n");
    printf("1. Right (toward higher cylinders)\n");
    printf("2. Left (toward lower cylinders)\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &direction);
    
    if (direction != 1 && direction != 2) {
        printf("Invalid direction choice. Defaulting to Right (1).\n");
        return 1;
    }
    
    return direction;
}

void fcfs(int queue[], int size, int head, int cylinders) {
    int total_movement = 0;
    int current = head;
    
    printf("\nOrder of service:\n%d ", current);
    for (int i = 0; i < size; i++) {
        total_movement += abs(current - queue[i]);
        current = queue[i];
        printf("%d ", current);
    }
    
    printf("\nTotal head movement: %d\n", total_movement);
}

void scan(int queue[], int size, int head, int cylinders, int direction) {
    int total_movement = 0;
    int current = head;
    int *sorted_queue = (int *)malloc((size + 1) * sizeof(int));
    
    // Copy the queue and add the head position for sorting
    memcpy(sorted_queue, queue, size * sizeof(int));
    sorted_queue[size] = head;
    sort(sorted_queue, size + 1);
    
    int head_index = 0;
    while (head_index < size + 1 && sorted_queue[head_index] != head) {
        head_index++;
    }
    
    printf("\nOrder of service:\n%d ", current);
    
    if (direction == 1) { // Right (toward higher cylinders)
        // Service requests to the right
        for (int i = head_index + 1; i < size + 1; i++) {
            total_movement += abs(current - sorted_queue[i]);
            current = sorted_queue[i];
            printf("%d ", current);
        }
        
        // Go to the end if not already there
        if (current != cylinders - 1) {
            total_movement += abs(current - (cylinders - 1));
            current = cylinders - 1;
            printf("%d ", current);
        }
        
        // Service requests to the left
        for (int i = head_index - 1; i >= 0; i--) {
            total_movement += abs(current - sorted_queue[i]);
            current = sorted_queue[i];
            printf("%d ", current);
        }
    } else { // Left (toward lower cylinders)
        // Service requests to the left
        for (int i = head_index - 1; i >= 0; i--) {
            total_movement += abs(current - sorted_queue[i]);
            current = sorted_queue[i];
            printf("%d ", current);
        }
        
        // Go to the beginning if not already there
        if (current != 0) {
            total_movement += abs(current - 0);
            current = 0;
            printf("%d ", current);
        }
        
        // Service requests to the right
        for (int i = head_index + 1; i < size + 1; i++) {
            total_movement += abs(current - sorted_queue[i]);
            current = sorted_queue[i];
            printf("%d ", current);
        }
    }
    
    printf("\nTotal head movement: %d\n", total_movement);
    free(sorted_queue);
}

void cscan(int queue[], int size, int head, int cylinders, int direction) {
    int total_movement = 0;
    int current = head;
    int *sorted_queue = (int *)malloc((size + 1) * sizeof(int));
    
    // Copy the queue and add the head position for sorting
    memcpy(sorted_queue, queue, size * sizeof(int));
    sorted_queue[size] = head;
    sort(sorted_queue, size + 1);
    
    int head_index = 0;
    while (head_index < size + 1 && sorted_queue[head_index] != head) {
        head_index++;
    }
    
    printf("\nOrder of service:\n%d ", current);
    
    if (direction == 1) { // Right (toward higher cylinders)
        // Service requests to the right
        for (int i = head_index + 1; i < size + 1; i++) {
            total_movement += abs(current - sorted_queue[i]);
            current = sorted_queue[i];
            printf("%d ", current);
        }
        
        // Go to the end if not already there
        if (current != cylinders - 1) {
            total_movement += abs(current - (cylinders - 1));
            current = cylinders - 1;
            printf("%d ", current);
        }
        
        // Jump to the beginning (no movement counted)
        total_movement += 0; // Just to show we're accounting for it
        current = 0;
        printf("%d ", current);
        
        // Continue servicing from the beginning
        for (int i = 0; i < head_index; i++) {
            total_movement += abs(current - sorted_queue[i]);
            current = sorted_queue[i];
            printf("%d ", current);
        }
    } else { // Left (toward lower cylinders)
        // Service requests to the left
        for (int i = head_index - 1; i >= 0; i--) {
            total_movement += abs(current - sorted_queue[i]);
            current = sorted_queue[i];
            printf("%d ", current);
        }
        
        // Go to the beginning if not already there
        if (current != 0) {
            total_movement += abs(current - 0);
            current = 0;
            printf("%d ", current);
        }
        
        // Jump to the end (no movement counted)
        total_movement += 0; // Just to show we're accounting for it
        current = cylinders - 1;
        printf("%d ", current);
        
        // Continue servicing from the end
        for (int i = size; i > head_index; i--) {
            total_movement += abs(current - sorted_queue[i]);
            current = sorted_queue[i];
            printf("%d ", current);
        }
    }
    
    printf("\nTotal head movement: %d\n", total_movement);
    free(sorted_queue);
}

void sort(int arr[], int size) {
    // Simple bubble sort
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
