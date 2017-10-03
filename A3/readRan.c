//
//  readRan.c
//  
//
//  Created by Lili Peng on 9/26/17.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char * argv[])
{
    const char * filename="test.txt";
    FILE * ft= fopen(filename, "rb") ;
    if (ft) {
        int pid = getpid();
        fseek (ft,0,SEEK_END); //go to end of file
        long size = ftell(ft); //what byte in file am I at?
        fseek (ft,0,SEEK_SET); //go to beginning of file
        int num = (int)size / (int)sizeof(int);
        printf("size of the file: %li ,sizeof(int) = %i\n, the number of numbers = %i\n\n", size, (int) sizeof(int), num);
        int i;
        for(i = 0; i < num; i++){
            int temp = 0;
            fread(&temp,sizeof(int),1,ft);
            printf("%i: %i\t",pid,temp);
        }
        fclose( ft ) ;
    }
    printf("\n");
    return 0;
}

