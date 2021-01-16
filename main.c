# include "Header.h"


int main(int argc, char * argv[])
{
    bool Vflag=false, Dflag=false, Lflag=false;

    char * dst=(char*)calloc(2*strlen(argv[argc-1]), sizeof(char));
    char * src=(char*)calloc(2*strlen(argv[argc-2]), sizeof(char));
    strcpy(dst, argv[argc-1]); strcpy(src, argv[argc-2]);

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
    int src_fd=open(src, O_RDONLY);
    int check;

    // Check if the destination as given exists.
    DIR * dir= opendir(dst);
    if (errno == ENOENT){    
        check=DeepCopy(src, dst, Vflag, Dflag, Lflag);
    }
    else if (errno == 0){
        check=DeepCopy(src, dst, Vflag, Dflag, Lflag);
    }
    

    if(check == -1){
        printf("DeepCopy error\n"); return 1;
    }
    
    free(src); free(dst);
    free(dir);
    printf("\n");
    return 0;
}