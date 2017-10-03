//
//  findMinMax.c
//  
//
//  Created by Lili Peng on 9/27/17.
//
//

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    // Example argument: findMinMax filename start end
    if (argc != 4)
    {
        printf("Error: Incorrect number of arguments, you should execute this program with command like this \"findMixMax test.txt 0 24\".\n");
    }
    else
    {
        int start = atoi(argv[2]);
        int end = atoi(argv[3]);
        
        FILE *ft = fopen(argv[1], "rb");
        
        if (!ft)
        {
            printf("Error: Could not open file.\n");
        }
        else
        {
            fseek(ft, start, SEEK_SET);
            long start_size = ftell(ft);
            
            fseek(ft, end, SEEK_SET);

            long size = ftell(ft) - start_size;
            
            // Get the number of integers within this block
            int num = (int)size / (int)sizeof(int);
            
            // Initialize the placeholders for min and max
            int min;
            int max;
            
            // Set the file pointer back to the start argument
            fseek(ft, start, SEEK_SET);
            
            for (int i = 0; i < num; i++)// 8 2 5 3 1 4 6
            {
                int temp = 0;
                fread(&temp, sizeof(int), 1, ft);
                
                // If this is looping the first time
                if (i == 0)
                {
                    min = temp;
                    max = temp;
                }
                
                if (temp > max)
                {
                    max = temp;
                }
                else if (temp < min)
                {
                    min = temp;
                }
                else
                {
                    continue;
                }
            }
            
            // Return the found min and max back to parent
            printf("%i\n", max);
            printf("%i\n", min);
        }
        fclose( ft );
    }
    return 5;
}
