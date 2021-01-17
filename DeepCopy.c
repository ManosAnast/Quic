# include "Header.h"

int DeepCopy(char * src, char * dst, bool Vflag, bool Dflag, bool Lflag)
{
    
    if(errno == ENOENT){
        // Create the destination path since we enter this function if the destination path doesn't exit
        // and add the last part of the source path, which is the file.
        mkdir(dst, 0700);

        // Copy the content of the source path to the destination path
        if (DeepCopyFiles(src, dst, opendir(src), Vflag, Dflag, Lflag) == -1){
            return -1;
        }
    }
    else if (errno == 0)
    {
        if (CopyFiles(src, dst, opendir(src), Vflag, Dflag, Lflag) == -1){
            return -1;
        }
        if ( Dflag ){
            if(Delete(src, dst, Vflag) == -1){
                return -1;
            }
        }
    }
    
    return 0;
}

int DeepCopyFiles(char * src, char * dst, DIR * dir, bool Vflag, bool Dflag, bool Lflag)
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
            
            if(Vflag){
                printf("%s\n",src);
            }

            int Type=FileType(src, Lflag);
            if (Type == 0){ //Directory
                mkdir(dst, 0700);
                if( DeepCopyFiles(src, dst, opendir(src), Vflag, Dflag, Lflag) == -1 ){
                    return -1;
                }
            }
            else if(Type == 1){ //File
                int src_fd=open(src, O_RDONLY);
                int dst_fd=creat(dst, S_IRWXU);
                Copy(src_fd, dst_fd);
                close(src_fd); close(dst_fd);
            }
            else if (Type == 2){ //Symbolic link
                char buf[strlen(src)];
                int result=readlink(src, buf, sizeof(buf));
                buf[result-1]='\0';
                if(symlink(buf, dst) == -1){
                    perror("Symlink");
                }
            }
            else if (Type == 3){ //Hard link
                if(link(src, dst) == -1){
                    perror("Link"); 
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
    // src =(char *)realloc(src, length+strlen(Next)+2);
    // strcpy(file, src);
    if( src[length-1] != '/'){
        // src =(char *)realloc(src, length+strlen(Next)+2);
        strcat(src, "/");
        strcat(src, Next);
    }
    else{
        // src =(char *)realloc(src, length+strlen(Next)+1);
        strcat(src, Next);
    }
    // strcpy(src, file);
    // free(file);
    return src;
}


int FileType(char * src, bool Lflag)
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
    int err, n;
    
    while (1) {
        err = read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("Error reading file.\n");
            exit(1);
        }
        n = err;

        if (n == 0) break;

        err = write(dst_fd, buffer, n);
        if (err == -1) {
            printf("Error writing to file.\n");
            exit(1);
        }
    }
    return 0;
}