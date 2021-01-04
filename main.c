# include "Header.h"

// IT WORKS FOR FILES BUT NOT FOR FOLDERS.

int main(int argc, char * argv[])
{
    char * dst=argv[argc-1];
    char * src=argv[argc-2];

    //I need to do read and write implementation
    int src_fd=open(src, O_RDONLY), dst_fd=open(dst, O_WRONLY);

    // Check if the destination as given exists.
    DIR * dir= opendir(dst);
    if (errno == ENOENT){    
        dst_fd=DeepCopy(src_fd, src, dst);
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