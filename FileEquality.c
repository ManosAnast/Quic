# include "Header.h"


int CopyFiles(char * src, char * dst, DIR * dir, bool Vflag, bool Dflag, bool Lflag)
{
    if(dir == NULL){
        perror("CopyFile"); return -1;
    }

    struct dirent * ent;
    int counter=0;
    while ( (ent = readdir(dir)) != NULL){
        if(strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0 ){
            
            src=FrontTrack(src, ent->d_name);
            dst=FrontTrack(dst, ent->d_name);
            
            int Type=FileType(src, Lflag);
            if(Type == 0){ //Directory
                opendir(dst);
                if( DeepCopy(src, dst, Vflag, Dflag, Lflag) == -1 ){
                    return -1;
                }
            }
            else if(Type == 1){ //File
                int src_fd=open(src, O_RDONLY);
                int dst_fd=open(dst, O_WRONLY);
                if(dst_fd == -1){
                    dst_fd=creat(dst, S_IRWXU);
                }
                if( !EqualSize(src_fd, dst_fd) || !SameDate(src_fd, dst_fd)){
                    if(Vflag){
                        printf("%s\n",src);
                    }
                    Copy(src_fd, dst_fd);
                }
                close(src_fd); close(dst_fd);
            }
            else if (Type == 2){ //Symbolic link
                int src_fd=open(src, O_RDONLY);
                int dst_fd=open(dst, O_WRONLY);
                if( !EqualSize(src_fd, dst_fd) || !SameDate(src_fd, dst_fd) || dst_fd == -1){
                    if(Vflag){
                        printf("%s\n",src);
                    }
                    char buf[100];
                    readlink(src, buf, sizeof(buf));
                    if(symlink(buf, dst) == -1){
                        perror("Symlink");
                    }
                }
            }
            else if (Type == 3){ //Hard link
                int src_fd=open(src, O_RDONLY);
                int dst_fd=open(dst, O_WRONLY);
                if( !EqualSize(src_fd, dst_fd) || !SameDate(src_fd, dst_fd) || dst_fd == -1){
                    if(Vflag){
                        printf("%s\n",src);
                    }
                    if(link(src, dst) == 0){
                        perror("Link"); 
                    }
                }
            }

            src=BackTrack(src);
            dst=BackTrack(dst);   
        }
    }
    // free(src); free(dst);
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
    else if(src_buff.st_mtime > dst_buff.st_mtime){
        return 0;
    }
    return 1;
}


int Delete(char * src, char * dst, bool Vflag)
{
    DIR * dir=opendir(dst);
    if(dir == NULL){
        perror("CopyFile"); return -1;
    }

    struct dirent * ent;
    int counter=0;
    while ( (ent = readdir(dir)) != NULL){
        if(strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0 ){
            
            dst=FrontTrack(dst, ent->d_name);
            src=FrontTrack(src, ent->d_name);
            
            int Type=FileType(src, false);
            if(Type == 1){
                int src_fd=open(src, O_RDONLY);
                int dst_fd=open(dst, O_WRONLY);
                if(src_fd == -1){
                    if(remove(dst) == -1){
                        perror("Remove"); return -1;
                    }
                    if(Vflag){
                        printf("Delete: %s\n",dst);
                    }
                }
            }
            else{
                int src_fd=open(src,O_RDONLY);
                if(src_fd == -1){
                    if(Delete(src, dst, Vflag) == -1){
                        return -1;
                    }
                    if(remove(dst) == -1){
                        perror("Remove"); return -1;
                    }
                    if(Vflag){
                        printf("Delete: %s\n",dst);
                    }
                }
            }
            
            src=BackTrack(src);
            dst=BackTrack(dst);   
        }
    }
    free(dir);
    return 0;
}


int Link(char * src, char * dst)
{
    
}