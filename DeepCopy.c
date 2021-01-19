# include "Header.h"


int DeepCopy(char * src, char * dst)
{
    int counter, copied=0, bytes=0;

    int dst_fd=open(dst, O_RDONLY);
    if(dst_fd == -1){
        mkdir(dst, 0700);

        // Copy the content of the source path to the destination path
        if (( counter = DeepCopyFiles(src, dst, &copied, &bytes)) == -1){
            return -1;
        }
    }
    else{
        if (( counter = CopyFiles(src, dst, &copied, &bytes)) == -1){
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


int DeepCopyFiles(char * src, char * dst, int * copied, int * bytes)
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
                if( ( counter += DeepCopyFiles(src, dst, copied, bytes) ) == -1 ){
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
                Copy(src_fd, dst_fd);
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


int Copy(int src_fd, int dst_fd)
{
    unsigned char buffer[4096];
    int err, n, counter =0;
    
    while (1) {
        err = read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("Error reading file.\n");
            exit(1);
        }
        n = err;
        counter += n;

        if (n == 0) break;

        err = write(dst_fd, buffer, n);
        if (err == -1) {
            printf("Error writing to file.\n");
            exit(1);
        }
    }
    return counter;
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