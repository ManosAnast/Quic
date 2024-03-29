# include "Header.h"


int UpdateFiles(char * src, char * dst, int * copied, int * bytes)
{
    DIR * dir=opendir(src);
    if(dir == NULL){
        perror("CopyFile"); return -1;
    }

    struct dirent * ent;
    int counter=0;
    while ( (ent = readdir(dir)) != NULL){
        if(strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0 ){
            counter +=1;
            src=FrontTrack(src, ent->d_name);
            dst=FrontTrack(dst, ent->d_name);
            
            int Type=FileType(src);
            if(Type == 0){ //Directory
                int dst_fd=open(dst, O_RDONLY);
                if(dst_fd == -1){
                    mkdir(dst, 0700);
                    printf("Created directory %s\n",src);
                    if ((counter += DeepCopy(src, dst, copied, bytes)) == -1){
                        return -1;
                    }
                    *copied += 1;
                }
                else
                {
                    if ((counter += UpdateFiles(src, dst, copied, bytes)) == -1){
                        return -1;
                    }
                }
                close(dst_fd);
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
                    if(Copy(src_fd, dst_fd) == -1){
                        return -1;
                    }
                    *bytes += getSize(dst);
                    *copied += 1;
                }
                close(src_fd); close(dst_fd);
            }
            else if (Type == 2){ //Symbolic link
                int dst_fd=open(dst, O_WRONLY);
                if(dst_fd == -1){
                    char buf[strlen(src)];
                    int result=readlink(src, buf, sizeof(buf));
                    buf[result]='\0';
                    if(symlink(buf, dst) == -1){
                        perror("Symlink");
                    }
                    *bytes += getSize(dst);
                }
            }
            else if (Type == 3){ //Hard link
                int dst_fd=open(dst, O_WRONLY);
                if(dst_fd == -1){
                    if(link(src, dst) == -1){
                        perror("Link"); 
                    }
                    *bytes += getSize(dst);
                }
            }
            src=BackTrack(src);
            dst=BackTrack(dst);   
        }
    }
    return counter;
}


int Delete(char * src, char * dst)
{
    DIR * dir=opendir(dst);
    if(dir == NULL){
        perror("CopyFile"); return -1;
    }

    struct dirent * ent;
    while ( (ent = readdir(dir)) != NULL){
        if(strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0 ){
            
            dst=FrontTrack(dst, ent->d_name);
            src=FrontTrack(src, ent->d_name);
            
            int Type=FileType(dst);
            if(Type ==0){ // Directory
                int src_fd=open(src,O_RDONLY);
                if(src_fd == -1){
                    if(Delete(src, dst) == -1){
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
            else if(Type == 1 || Type == 3){ // File or hard link
                int src_fd=open(src, O_RDONLY);
                if(src_fd == -1){
                    if(remove(dst) == -1){
                        perror("Remove"); return -1;
                    }
                    if(Vflag){
                        printf("Delete: %s\n",dst);
                    }
                }
            }
            else if (Type == 2){ //Symbolic link
                int src_fd=open(src,O_RDONLY);
                if(src_fd == -1){
                    if ( unlink(dst) == -1){
                        perror("Unlink"); return -1;
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
    return 0;
}