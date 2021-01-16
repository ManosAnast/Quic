# include "Header.h"


int CopyFiles(char * src, char * dst, DIR * dir)
{
    if(dir == NULL){
        perror("CopyFile"); return -1;
    }

    struct dirent * ent;
    int counter=0;
    while ( (ent = readdir(dir)) != NULL){
        if(strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0 ){
            
            src=FrontTrack(src, ent->d_name);
            

            if(FileType(src) == 1){
                dst=FrontTrack(dst, ent->d_name);
                int src_fd=open(src, O_RDONLY);
                int dst_fd=open(dst, O_WRONLY);
                if(EqualSize(src_fd, dst_fd) || !SameDate(src_fd, dst_fd)){
                    printf("%s\n",src);
                    Copy(src_fd, dst_fd);
                }
            }
            src=BackTrack(src);
            dst=BackTrack(dst);   
        }
    }
    free(dir);
    return 0;
}


int EqualSize(int src_fd, int dst_fd)
{
    struct stat src_buff;
    struct stat dst_buff;

    //Take inode information for the source file
    if (fstat(src_fd, &src_buff) == -1){
        perror("Fstat"); return 0;
    }

    //Take inode information for the destination file
    if (fstat(dst_fd, &dst_buff) == -1){
        perror("Fstat"); return 0;
    }

    //Check if files are the same size
    if (src_buff.st_size == dst_buff.st_size){
        return 1;
    }
    else{
        return 0;
    }
}


int SameDate(int src_fd, int dst_fd)
{
    struct stat src_buff;
    struct stat dst_buff;

    //Take inode information for the source file
    if (fstat(src_fd, &src_buff) == -1){
        perror("Fstat"); return 1;
    }

    //Take inode information for the destination file
    if (fstat(dst_fd, &dst_buff) == -1){
        perror("Fstat"); return 1;
    }

    //Check if files are the same size
    if (src_buff.st_mtime == dst_buff.st_mtime){
        return 1;
    }
    else{
        return 0;
    }
}