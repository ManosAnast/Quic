# include "Header.h"


int Identifier(char * src, char * dst)
{
    int counter, copied=0, bytes=0;

    int dst_fd=open(dst, O_RDONLY);
    if(dst_fd == -1){
        mkdir(dst, 0700);

        // Copy the content of the source path to the destination path
        if (( counter = DeepCopy(src, dst, &copied, &bytes)) == -1){
            return -1;
        }
    }
    else{
        if (( counter = UpdateFiles(src, dst, &copied, &bytes)) == -1){
            return -1;
        }
        if ( Dflag ){
            if(Delete(src, dst) == -1){
                return -1;
            }
        }
    }
    printf("There are %d files/directories in the hierarchy\n", counter);
    printf("Number of entries copied is %d \n", copied);
    return bytes;
}


int DeepCopy(char * src, char * dst, int * copied, int * bytes)
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
            if (Type == 0){ //Directory
                mkdir(dst, 0700);
                printf("Created directory %s\n",src);
                if( ( counter += DeepCopy(src, dst, copied, bytes) ) == -1 ){ 
                    return -1;
                }
                if(Vflag){
                    printf("%s\n",src);
                }
                *bytes += getSize(dst);
            }
            else if(Type == 1){ //File
                int src_fd=open(src, O_RDONLY);
                int dst_fd=creat(dst, S_IRWXU);
                if(Copy(src_fd, dst_fd) == -1){
                    return -1;
                }
                if(Vflag){
                    printf("%s\n",src);
                }
                *bytes += getSize(dst);
                close(src_fd); close(dst_fd);
            }
            else if (Type == 2){ //Symbolic link
                char buf[strlen(src)];
                int result=readlink(src, buf, sizeof(buf));
                buf[result]='\0';
                if(symlink(buf, dst) == -1){
                    perror("Symlink");
                }
                if(Vflag){
                    printf("%s\n",src);
                }
                *bytes += getSize(dst);
            }
            else if (Type == 3){ //Hard link
                if(link(src, dst) == -1){
                    perror("Link"); 
                }
                if(Vflag){
                    printf("%s\n",src);
                }
                *bytes += getSize(dst);
            }
            
            src=BackTrack(src);
            dst=BackTrack(dst);   
        }
    }
    *copied = counter;
    return counter;
}


int Copy(int src_fd, int dst_fd)
{
    unsigned char buffer[4096];
    int err, n, counter =0;
    
    while (1) {
        err = read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("Error reading file.\n");
            return -1;
        }
        n = err;
        counter += n;

        if (n == 0) break;

        err = write(dst_fd, buffer, n);
        if (err == -1) {
            printf("Error writing to file.\n");
            return -1;
        }
    }
    return counter;
}