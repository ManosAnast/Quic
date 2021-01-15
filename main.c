# include "Header.h"

// IT WORKS FOR FILES BUT NOT FOR FOLDERS.

int main(int argc, char * argv[])
{
    char * dst=(char*)calloc(2*strlen(argv[argc-1]), sizeof(char));
    char * src=(char*)calloc(2*strlen(argv[argc-2]), sizeof(char));
    strcpy(dst, argv[argc-1]); strcpy(src, argv[argc-2]);

    //I need to do read and write implementation
    int src_fd=open(src, O_RDONLY);
    int check;

    // Check if the destination as given exists.
    DIR * dir= opendir(dst);
    if (errno == ENOENT){    
        check=DeepCopy(src, dst);
    }
    else if (errno == 0)
    {
        check=DeepCopy(src, dst);
    }
    

    if(check == -1){
        printf("DeepCopy error\n"); return 1;
    }
    
    free(src); free(dst);
    free(dir);
    return 0;
}