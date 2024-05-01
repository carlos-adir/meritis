#include <stdio.h>
#include <stdlib.h>

#define MAXINT 4294967295
#define LENGHT 1000000
#define SIZESOL 5002



int recursive(const unsigned int m,
               const unsigned int s,
               const unsigned int v,
               const unsigned int numbers[],
               const short int lenghts[],
               unsigned int response[],
               FILE *file){
   /*
   Returns -1 if there isn't a subsequence such is deacreasing
   If not, it returns the index of the point
   */
   int i, j;
   for(i=s; i<LENGHT; i++){
        if(lenghts[i] != m)
            continue;
        if (v <= numbers[i])
            continue;
        response[m] = numbers[i];
        if(m == 0){
            j = 1;
            fprintf(file, "%u", response[0]);
            while(response[j] > 0){
                fprintf(file, " %u", response[j]);
                j++;
            }
            fprintf(file, "\n");
            return 0;
            continue;
        }
        j = recursive(m-1, i+1, response[m], numbers, lenghts, response, file);
        if (j == 0)
            return 0;
   }
   return -1;
}

void solve(const unsigned int numbers[], FILE *file){
    int i, n, m;
    short int lenghts[LENGHT];
    unsigned int response[SIZESOL];
    for(i=0; i<LENGHT; i++)
        lenghts[i] = -1;
    for(i=0; i<SIZESOL; i++)
        response[i] = 0;
    for(n = LENGHT-1; n >= 0; n--){
        for(i=n+1; i<LENGHT; i++)
            if(numbers[n] > numbers[i])
                lenghts[n] = lenghts[n] > lenghts[i] ? lenghts[n] : lenghts[i];
        lenghts[n] += 1;
    }
        
    m = 0;
    for(i=0; i<LENGHT; i++)
        m = m > lenghts[i] ? m : lenghts[i];
    printf("\n lenghts = %d\n", m);
    printf("\n\n");
    printf("recursive:\n");
    recursive(m, 0, MAXINT, numbers, lenghts, response, file);
}


int main(){
    int i;
    FILE *file;
    unsigned int numbers[LENGHT];
    
    file = fopen("data2.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }
    for(i=0; i <LENGHT; i++){
        fscanf(file, "%u", numbers + i);
    }
    fclose(file);

    file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    solve(numbers, file);
    fclose(file);


    return 0;
}
