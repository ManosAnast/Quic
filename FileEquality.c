# include "Header.h"

int isEqual(int src_fd, int dst_fd)
{
    if(EqualSize(src_fd, dst_fd) /*&& SameDate(src_fd, dst_fd)*/){
        printf("Same size\n");
    }
}


int EqualSize(int src_fd, int dst_fd)
{
    struct stat * src_buff;
    struct stat * dst_buff;

    //Take inode information for the source file
    if (fstat(src_fd, src_buff) == -1){
        perror("Fstat");
    }

    //Take inode information for the destination file
    if (fstat(dst_fd, dst_buff) == -1){
        perror("Fstat");
    }

    //Check if files are the same size
    if (src_buff->st_size == dst_buff->st_size){
        return 1;
    }
    else{
        return 0;
    }
}


int SameDate(int src_fd, int dst_fd)
{
    struct stat * src_buff;
    struct stat * dst_buff;

    //Take inode information for the source file
    if (fstat(src_fd, src_buff) == -1){
        perror("Fstat");
    }

    //Take inode information for the destination file
    if (fstat(dst_fd, dst_buff) == -1){
        perror("Fstat");
    }

    //Check if files are the same size
    if (src_buff->st_mtime == dst_buff->st_mtime){
        return 1;
    }
    else{
        return 0;
    }
}