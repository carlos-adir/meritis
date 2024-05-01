#include <stdio.h>
#define MAXINT 40000000
#define NUMBER_ENTRIES 250
#define INPUT_FILEPATH "input/sorted_data.txt"

typedef struct Interval {
    unsigned lower, upper;
} Interval;

unsigned count(const Interval intervals[NUMBER_ENTRIES]){
    return 0;
}

void upload_from_file(Interval intervals[NUMBER_ENTRIES]){
    unsigned i;
    FILE *file;
    
    file = fopen(INPUT_FILEPATH, "r");
    if(file == NULL)
        return;
    for(i=0; i<NUMBER_ENTRIES; i++)
        fscanf(file, "%*u,%u,%u", &(intervals[i].lower), &(intervals[i].upper));
    fclose(file);
    return;
}

int main(){
    unsigned number;
    Interval intervals[NUMBER_ENTRIES];
    upload_from_file(intervals);
    bubble_sort(intervals);

    number = count(intervals);
    printf("Minimal number: %u\n", number);

    return 0;
}