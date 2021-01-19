# include "Header.h"


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
    else if(src_buff.st_mtime > dst_buff.st_mtime){
        return 0;
    }
    return 1;
}


char * BackTrack(char * src)
{
    int i, length=strlen(src);
    for (i = length; i > 0 ; i--){
        if (src[i] == '/' && i !=length-1 ){
            src[i+1]='\0';
            break;
        }
    }
    return src;
}


char * FrontTrack(char * src, char * Next)
{
    int length=strlen(src);
    if( src[length-1] != '/'){
        strcat(src, "/");
        strcat(src, Next);
    }
    else{
        strcat(src, Next);
    }
    return src;
}


int FileType(char * src)
{
    struct stat path_stat;
    if( lstat(src, &path_stat) == -1){
        perror("Stat");
        return -1;
    }

    if( (path_stat.st_mode & S_IFMT) == S_IFLNK){ //Symbolic link
        if(Lflag){
            return 2;
        }
        return 1;
    }
    else if( (path_stat.st_mode & S_IFMT) == S_IFREG){ //File
        if (path_stat.st_nlink > 1 && Lflag){
            return 3;
        }
        
        return 1;
    }
    else if( (path_stat.st_mode & S_IFMT) == S_IFDIR){ //Directory
        return 0;
    }
    return -1;
}


int getSize(char * dst)
{
    int dst_fd=open(dst, O_RDONLY);
    struct stat dst_buff;
    
    //Take inode information for the destination file
    if (fstat(dst_fd, &dst_buff) == -1){
        perror("Fstat"); return -1;
    }
    return dst_buff.st_size;
}