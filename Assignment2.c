#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CYLINDER_SIZE 5000
#define REQUEST_SIZE 1000

int requests[REQUEST_SIZE];

void read_requests(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }
    for (int i = 0; i < REQUEST_SIZE; i++)
    {
        if (fscanf(file, "%d", &requests[i]) != 1)
        {
            fprintf(stderr, "Error reading request.\n");
            exit(1);
        }
    }
    fclose(file);
}

int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int calculate_total_movement(int *arr, int size, int initial_pos)
{
    int total_movement = abs(initial_pos - arr[0]);
    for (int i = 1; i < size; i++)
    {
        total_movement += abs(arr[i] - arr[i - 1]);
    }
    return total_movement;
}

void fcfs(int *req, int size, int initial_pos)
{
    int original_movement = calculate_total_movement(req, size, initial_pos);
    int optimized_movement = abs(initial_pos - req[size - 1]);
    for (int i = size - 1; i > 0; i--)
    {
        optimized_movement += abs(req[i] - req[i - 1]);
    }
    printf("FCFS Original Total Head Movements: %d\n", original_movement);
    printf("FCFS Optimized Total Head Movements: %d\n", optimized_movement);
}

void scan(int *req, int size, int initial_pos)
{
    int sorted_requests[REQUEST_SIZE];
    memcpy(sorted_requests, req, sizeof(int) * REQUEST_SIZE);
    qsort(sorted_requests, size, sizeof(int), compare);
    int start_index = 0;
    while (start_index < size && sorted_requests[start_index] < initial_pos)
    {
        start_index++;
    }
    int total_movement = abs(initial_pos - sorted_requests[start_index % size]);
    for (int i = start_index; i < size - 1; i++)
    {
        total_movement += abs(sorted_requests[i + 1] - sorted_requests[i]);
    }
    total_movement += abs(sorted_requests[size - 1] - sorted_requests[0]);
    for (int i = 0; i < start_index - 1; i++)
    {
        total_movement += abs(sorted_requests[i + 1] - sorted_requests[i]);
    }
    printf("SCAN Original Total Head Movements: %d\n", total_movement);
    total_movement = abs(initial_pos - sorted_requests[start_index % size]);
    for (int i = start_index; i < size - 1; i++)
    {
        total_movement += abs(sorted_requests[i + 1] - sorted_requests[i]);
    }
    printf("SCAN Optimized Total Head Movements: %d\n", total_movement);
}

void cscan(int *req, int size, int initial_pos)
{
    int sorted_requests[REQUEST_SIZE];
    memcpy(sorted_requests, req, sizeof(int) * REQUEST_SIZE);
    qsort(sorted_requests, size, sizeof(int), compare);
    int start_index = 0;
    while (start_index < size && sorted_requests[start_index] < initial_pos)
    {
        start_index++;
    }
    int total_movement = abs(initial_pos - sorted_requests[start_index % size]);
    for (int i = start_index; i < size - 1; i++)
    {
        total_movement += abs(sorted_requests[i + 1] - sorted_requests[i]);
    }
    total_movement += abs(CYLINDER_SIZE - 1 - sorted_requests[size - 1]);
    total_movement += CYLINDER_SIZE - 1;
    total_movement += sorted_requests[0];
    for (int i = 0; i < start_index - 1; i++)
    {
        total_movement += abs(sorted_requests[i + 1] - sorted_requests[i]);
    }
    printf("C-SCAN Original Total Head Movements: %d\n", total_movement);
    total_movement = abs(initial_pos - sorted_requests[start_index % size]);
    for (int i = start_index; i < size - 1; i++)
    {
        total_movement += abs(sorted_requests[i + 1] - sorted_requests[i]);
    }
    total_movement += abs(CYLINDER_SIZE - 1 - sorted_requests[size - 1]);
    total_movement += CYLINDER_SIZE - 1;
    printf("C-SCAN Optimized Total Head Movements: %d\n", total_movement);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <initial head position> <file name>\n", argv[0]);
        return 1;
    }
    int initial_pos = atoi(argv[1]);
    read_requests(argv[2]);
    fcfs(requests, REQUEST_SIZE, initial_pos);
    scan(requests, REQUEST_SIZE, initial_pos);
    cscan(requests, REQUEST_SIZE, initial_pos);
    return 0;
}
