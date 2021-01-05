# include "Header.h"

int DeepCopy(int src_fd, char * src, char * dst)
{
    
    // Create the destination path since we enter this function if the destination path doesn't exit
    // and add the last part of the source path, which is the file.
    mkdir(dst, 0700);
    dst=PathMaker(src,dst);

    //Create the file at the destination path
    int dst_fd=creat(dst, S_IRWXU);

    // Copy the content of the source path to the destination path
    if (CopyFiles(src_fd, src, dst, opendir(src)) == -1){
        return -1;
    }
    close(src_fd); close(dst_fd);

    return 0;
}

int CopyFiles(int src_fd, char * src, char * dst, DIR * dir)
{
    if(dir == NULL){
        perror("CopyFile"); return -1;
    }

    struct dirent * ent;
    char * src_dummy = (char *)calloc(strlen(src), sizeof(char));
    char * dst_dummy = (char *)calloc(strlen(src), sizeof(char));
    int counter=0;
    // Here the string doesn't work as it should.
    strcpy(dst_dummy, dst); strcpy(src_dummy, src);
    while ( (ent = readdir(dir)) != NULL){
        if(strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0 /*&& strcmp(ent->d_name, ".git") != 0*/ ){
            printf("%s\n",ent->d_name);
            int dst_fd=creat(strcat(dst_dummy, ent->d_name), S_IRWXU);
            strcat(src_dummy, ent->d_name);
            if(FileType(src_dummy) == 0){
                strcat(src_dummy, "/");
                int err=DeepCopy(open(src_dummy, O_RDONLY), src_dummy, dst_dummy);
                if(err == -1){
                    printf("Fuck\n"); return 1;
                }
            }
            Copy(open(src_dummy, O_RDONLY), dst_fd);
            strcpy(dst_dummy, dst); strcpy(src_dummy, src);
        }
    }
    printf("\n\n");
    return 0;
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


char * PathMaker(char * src, char * dst)
{
    int i;
    for (i = strlen(src); i > 0 ; i--){
        if (src[i] == '/'){
            break;
        }
        
    }
    int filelength= strlen(src)-i;
    char * file=(char *)calloc(filelength, sizeof(char));

    int j=0;
    for ( i++; i < strlen(src); i++){
        file[j++]=src[i];
    }
    strcat(dst, file);
    
    free(file);
    return dst;
}