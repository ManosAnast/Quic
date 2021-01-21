# include "Header.h"

bool Vflag=false, Dflag=false, Lflag=false;

int main(int argc, char * argv[])
{
    char * dst=(char*)calloc(2*strlen(argv[argc-1]), sizeof(char));
    char * src=(char*)calloc(2*strlen(argv[argc-2]), sizeof(char));
    strcpy(dst, argv[argc-1]); strcpy(src, argv[argc-2]);

    if(argc == 1){
        printf("./quic -l -v -d sourcepath destinationpath");
        return 0;
    }

    if (argc > 3){
        for (int i = 1; i < argc-2; i++){
            if ( !strcmp(argv[i], "-v")){
                Vflag=true;       
            }
            else if ( !strcmp(argv[i], "-d")){
                Dflag=true;
            }
            else if ( !strcmp(argv[i], "-l")){
                Lflag=true;
            }
            
        }
        
    }
    

    //I need to do read and write implementation
    int check;

    clock_t time;
    time = clock();
    check=DeepCopy(src, dst);
    
    time = clock() - time;
    double time_taken= ((double)time)/CLOCKS_PER_SEC;

    if(check == -1){
        printf("DeepCopy error\n"); return 1;
    }
    printf("copied/deleted %d bytes in %fsec at %f bytes/sec\n", check, time_taken, (double)check/time_taken);
    
    free(src); free(dst);
    printf("\n");
    return 0;
}