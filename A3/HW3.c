//
//  HW3.c
//
//
//  Created by Lili Peng on 9/26/17.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


char* get_start(int i, int num_per_fork)
{
    
    int start = i * sizeof(int) * num_per_fork;
    
    char* start_str = malloc(sizeof(int) + 1);
    
    sprintf(start_str, "%i", start);
    
    return start_str;
}

char* get_end(char* start, int num_per_fork)
{
    int end = atoi(start) + sizeof(int) * num_per_fork;
    
    char* end_str = malloc(sizeof(int) + 1);
    
    sprintf(end_str, "%i", end);
    
    return end_str;
}

void free_ptr(char* start, char* end)
{
    free(start);
    free(end);
}


int main (int argc, char *argv[]) // Example command: HW3 4 test.txt
{
    if (argc != 3)
    {
        printf("Error: Incorrect number of arguments, you should execute this program with command like this \"HW3 4 test.txt\".\n");
    }
    else
    {
        // Print out my name
        printf("Lili Peng\n");
        
        int num_forks = atoi(argv[1]);
        printf("Number of Fork: %s\n", argv[1] );
        
        if (num_forks != 1 && num_forks != 4)
        {
            printf ("Error: You can only choose 1 or 4 forks to process.\n");
        }
        else
        {
            FILE * ft = fopen(argv[2], "rb");
            
            if (!ft)
            {
                printf("Error: Could not open file.\n");
            }
            else
            {
                // Prepare to record time
                clock_t t;
                
                // Create a pipe
                int cp[2];
                if (pipe(cp) < 0)
                {
                    printf("Error: pipe couldn't be established.\n");
                    return -1;
                }
                
                // Calculate the size of the file
                fseek(ft, 0, SEEK_END);
                int size = ftell(ft);
                
                // Calculate the number of integer contains in this file
                int num = (int)size / (int)sizeof(int);
                fclose(ft);
                
                
                int num_per_fork = num / 4;
                
                int pid = fork();
                if (pid == 0)
                {
                    close(1); //close stdout
                    dup2(cp[1],1); //move stdout to pipe of cp[1]
                    close(0); //close stdin
                    close(cp[0]); //close pipe in
                    
                    if (num_forks == 1)
                    {
                        char end[sizeof(size) + 1];
                        sprintf(end, "%i", size);
                        
                        t = clock();
                        execl("findMinMax", "findMinMax", argv[2], "0", end, (char *) 0);
                    }
                    else
                    {
                        pid = fork();
                        if (pid == 0)
                        {
                            char* start = get_start(0, num_per_fork);
                            char* end = get_end(start, num_per_fork);
                            
                            t = clock();
                            execl("findMinMax", "findMinMax", argv[2], start, end, (char *) 0);
                            
                            free_ptr(start, end);
                        }
                        else
                        {
                            pid = fork();
                            if (pid == 0)
                            {
                                char* start = get_start(1, num_per_fork);
                                char* end = get_end(start, num_per_fork);
                                
                                execl("findMinMax", "findMinMax", argv[2], start, end, (char *) 0);
                                
                                free_ptr(start, end);
                            }
                            else
                            {
                                pid = fork();
                                if (pid == 0)
                                {
                                    char* start = get_start(2, num_per_fork);
                                    char* end = get_end(start, num_per_fork);
                                    
                                    execl("findMinMax", "findMinMax", argv[2], start, end, (char *) 0);
                                    
                                    free_ptr(start, end);
                                }
                                else
                                {
                                    int start = 3 * sizeof(int) * num_per_fork;
                                    int end = start + sizeof(int) * num_per_fork;
                                    
                                    // When the number of integer is not able to divided by 4
                                    if (num % 4 != 0)
                                    {
                                        end = size;
                                    }
                                    
                                    char start_str[sizeof(start) + 1];
                                    char end_str[sizeof(end + 1)];
                                    
                                    // Convert the integers to strings
                                    sprintf(start_str, "%i", start);
                                    sprintf(end_str, "%i", end);
                                    
                                    execl("findMinMax", "findMinMax", argv[2], start_str, end_str, (char *) 0);
                                }
                            }
                        }
                    }
                }
                else
                {
                    t = clock() - t;
                    close(cp[1]);
                    
                    int min = 0;
                    int max = 0;
                    
                    int BUFF_SIZE = 32;
                    
                    char buff[BUFF_SIZE];
                    
                    // Initialize the buffer
                    for (int i = 0; i < sizeof(buff); i++) {
                        buff[i] = 0;
                    }
                    
                    char ch;
                    int count = 0;
                    int i = 0;
                    
                    while( read(cp[0], &ch, 1) == 1)
                    {
                        // When we fond a number
                        if (ch == '\n')
                        {
                            int temp = atoi(buff);

                            // Clean up the buffer
                            for (int j = 0; j < i; j++)
                                buff[j] = 0;
                            
                            i = 0;
                            
                            //int temp = atoi(buff);
                            
                            if (count == 0){
                                max = temp;
                            }
                            else if (count == 1){
                                min = temp;
                            }
                            
                            if (min > temp)
                            {
                                min  = temp;
                            }
                            else if (max < temp)
                            {
                                max = temp;
                            }
                            count++;
                            
                        }
                        else
                        {
                            buff[i++] = ch;
                        }
                        
                    }
                    
                    double time_taken = ((double)t)/CLOCKS_PER_SEC;
                    printf("Processed Time: %f seconds\n", time_taken);
                    
                    printf("Max: %i\n", max);
                    printf("Min: %i\n", min);
                }
                
            }
            
        }
        
        
    }
    return 0;
}
