#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NBTEAMS 2048  /*2, 8, 256, 2048, 1024*/
#define PERTEAM 4  /*4, 128*/
#define INFINITE 32767
#define INPUT_FILEPATH "data4_4.txt"
#define OUTPUT_FILEPATH "output4_4.txt"

static unsigned short testteam[PERTEAM];
static unsigned short randindexs[PERTEAM];

unsigned compute_team_time(const unsigned short team[]){
    unsigned short i;
    unsigned time, dt;
    time = team[0];
    for (i=1; i<PERTEAM; i++){
        dt = team[i] > team[i-1] ? team[i] - team[i-1] : team[i-1] - team[i];
        time += team[i] + (dt*dt)/100;
    }
    return time;
}

void random_vector(short unsigned vector[], const unsigned short size) {
    unsigned short i, j, temp;
    for (i = 0; i < size; i++)
        vector[i] = i;
    for (i = 0; i < size; i++){
        j = rand() % size;
        temp = vector[i];
        vector[i] = vector[j];
        vector[j] = temp;
    }
}



void populate(unsigned short teams[NBTEAMS][PERTEAM]){
    unsigned short i, j;
    FILE *file;
    file = fopen(INPUT_FILEPATH, "r");
    for(i=0; i<NBTEAMS; i++){
        for(j=0; j<PERTEAM; j++){
            fscanf(file, "%hu", &(teams[i][j]));
        }
    }
    fclose(file);
}


unsigned short evaluate_solution(const unsigned short teams[NBTEAMS][PERTEAM]){
    unsigned short i, min, max, new;
    min = INFINITE;
    max = 0;
    for (i=0; i<NBTEAMS; i++){
        new = compute_team_time(teams[i]);
        min = min < new ? min : new;
        max = new < max ? max : new;
    }
    return max - min;
}


int shuffle_team(unsigned short team[PERTEAM], const unsigned short desired_time){
    /* This functions shuffles the team such it stays as near as possible of desired time
    This function returns the error */
    unsigned short i, j, time, testtime, dtime, dtesttime;
    time = compute_team_time(team);
    if (time == desired_time)
        return 0;
    dtime = time > desired_time ? time - desired_time : desired_time - time;
    for(i=0; i<PERTEAM;i++)
        testteam[i] = team[i];
    for(i=0; i<100; i++){
        random_vector(randindexs, PERTEAM);
        for(j=0; j<PERTEAM; j++)
            testteam[j] = team[randindexs[j]];
        testtime = compute_team_time(testteam);
        dtesttime = testtime > desired_time ? testtime - desired_time : desired_time - testtime;
        if(dtesttime < dtime){
            printf("    dtime/desired = %hu/%hu\n", dtesttime, desired_time);
            dtime = dtesttime;
            for(j=0; j<PERTEAM; j++)
                team[j] = testteam[j];
            if(!dtesttime)
                return 0;
        }
    }
    return testtime;
}


void shuffle_pair(unsigned short teama[PERTEAM],
                  unsigned short teamb[PERTEAM],
                  const unsigned short desired_time){
    /*This function makes the time of teama and timeb be the nearest as possible of desired time*/
    unsigned short i, timea, timeb, temp;
    timea = compute_team_time(teama);
    timeb = compute_team_time(teamb);
    if((timea == desired_time) && (timeb == desired_time))
        return;
    for(i=0; i<PERTEAM; i++){
        temp = teama[i];
        teama[i] = teamb[i];
        teamb[i] = temp;
        i++;
    }
    shuffle_team(teama, desired_time);
    shuffle_team(teamb, desired_time);
}

void recursive_decreasing(unsigned short teams[NBTEAMS][PERTEAM],
                          const unsigned short sta,
                          const unsigned short end,  
                          const unsigned short desired_time){
    if(end-sta == 2)
        return shuffle_pair(teams[sta], teams[sta+1], desired_time);
    recursive_decreasing(teams, sta, (sta+end)/2, desired_time);
    recursive_decreasing(teams, (sta+end)/2, end, desired_time);
}



int save_table(const unsigned short teams[NBTEAMS][PERTEAM], char *filepath){
    unsigned short i, j;
    FILE *file;
    file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Unable to open file.\n");
        for(i=0; i<NBTEAMS; i++)
            for(j=0; j<PERTEAM; j++)
                printf("%hu ", teams[i][j]);
        return 1;
    }
    else{
        for(i=0; i<NBTEAMS; i++)
            for(j=0; j<PERTEAM; j++)
                fprintf(file, "%hu ", teams[i][j]);
        fclose(file);
    }
    return 0;
}

void compute(unsigned short fixed_teams[NBTEAMS][PERTEAM]){
    unsigned short mintime, maxtime, auxtime, curtime;
    unsigned short i, j, totalsize;
    unsigned short randinds[NBTEAMS*PERTEAM];
    unsigned short tempo_teams[NBTEAMS][PERTEAM];
    unsigned short *fixed_place, *tempo_place;
    
    totalsize = NBTEAMS * PERTEAM;
    mintime = INFINITE;
    fixed_place = &(fixed_teams[0][0]);
    tempo_place = &(tempo_teams[0][0]);
    for(i=0; i<totalsize; i++){
        auxtime = *(fixed_place + i);
        mintime = mintime < auxtime ? mintime : auxtime;
    }
    for(i=0; i<totalsize; i++)
        *(fixed_place + i) -= mintime;
    curtime = evaluate_solution(fixed_teams);

    while(mintime > 0){
        random_vector(randinds, totalsize);
        for(i=0; i<totalsize; i++)
            *(tempo_place + i) = *(fixed_place + randinds[i]);
        auxtime = evaluate_solution(tempo_teams);
        if(auxtime < curtime){
            curtime = auxtime;
            printf("Current time: %hu\n", curtime);
            for(i=0; i<totalsize; i++)
                *(fixed_place + i) = *(tempo_place + i);
            save_table(fixed_teams, OUTPUT_FILEPATH);
            if(!curtime)
                break;
        }
    }
    
    for(i=0; i<NBTEAMS; i++)
        for(j=0; j<PERTEAM; j++)
            fixed_teams[i][j] += mintime;
    
    mintime = INFINITE;
    maxtime = 0;
    for(i=0; i<NBTEAMS; i++){
        auxtime = compute_team_time(fixed_teams[i]);
        mintime = mintime > auxtime ? auxtime : mintime;
        maxtime = maxtime > auxtime ? maxtime : auxtime;
        printf("Team %hu - %hu:", i, auxtime);
        for(j=0; j<PERTEAM; j++)
            printf(" %hu", fixed_teams[i][j]);
        printf("\n");
    }
    printf("Final pontuation:\n");
    printf("    Slower: %hu\n", mintime);
    printf("    Faster: %hu\n", maxtime);
    return;
}



int main(){
    srand(time(0));
    unsigned short teams[NBTEAMS][PERTEAM];
    
    populate(teams);
    printf("Current delta time: %hu\n", evaluate_solution(teams));

    compute(teams);
    printf("Current delta time: %hu\n", evaluate_solution(teams));
    save_table(teams, "output_4final_solution.txt");


    printf("\n\nFinished\n");

    return 0;
}