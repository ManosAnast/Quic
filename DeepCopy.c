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
        if (Dflag && Delete(src, dst, Vflag) == -1){
            return -1;
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
            
            if(Vflag){
                printf("%s\n",src);
            }

            if(FileType(src) == 1){
                int src_fd=open(src, O_RDONLY);
                dst=FrontTrack(dst, ent->d_name);
                int dst_fd=creat(dst, S_IRWXU);
                Copy(src_fd, dst_fd);
            }
            else{
                dst=FrontTrack(dst, ent->d_name);
                mkdir(dst, 0700);
                if( DeepCopyFiles(src, dst, opendir(src), Vflag, Dflag, Lflag) == -1 ){
                    return -1;
                }
            }
            src=BackTrack(src);
            dst=BackTrack(dst);   
        }
    }
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
    char * file =(char *)calloc(length+strlen(Next)+2, sizeof(char));
    strcpy(file, src);
    if( file[length-1] != '/'){
        strcat(file, "/");
        strcat(file, Next);
    }
    else{
        strcat(file, Next);
    }
    strcpy(src, file);
    free(file);
    return src;
}


int FileType(char * src)
{
    struct stat path_stat;
    if( stat(src, &path_stat) == -1){
        perror("Stat");
        return -1;
    }

    if( (path_stat.st_mode & S_IFMT) == S_IFREG){
        return 1;
    }
    else if( (path_stat.st_mode & S_IFMT) == S_IFLNK){
        return 1;
    }
    else if( (path_stat.st_mode & S_IFMT) == S_IFDIR){
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