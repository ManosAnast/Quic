# include "Header.h"

// IT WORKS FOR FILES BUT NOT FOR FOLDERS.

int main(int argc, char * argv[])
{
    //I need to do read and write implementation
    int src_fd=open(argv[argc-2], O_RDONLY), dst_fd=open(argv[argc-1], O_WRONLY);

    if(dst_fd == -1){
        dst_fd=DeepCopy(src_fd, PathMaker(argv[argc-2], argv[argc-1]));
    }
    else{
        //Here we are coping the files that are not copied
        Copy(src_fd, dst_fd);
    }
    

    if(dst_fd == -1){
        printf("DeepCopy error\n"); return 1;
    }

    return 0;
}