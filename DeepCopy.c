# include "Header.h"

int DeepCopy(int src_fd, char * src, char * dst)
{
    
    // Create the destination path since we enter this function if the destination path doesn't exit
    // and add the last part of the source path, which is the file.
    mkdir(dst, 0700);
    // dst=PathMaker(src,dst);

    //Create the file at the destination path
    // int dst_fd=creat(dst, S_IRWXU);

    // Copy the content of the source path to the destination path
    if (CopyFiles(src, dst) == -1){
        return -1;
    }
    close(src_fd); 

    return 0;
}

int CopyFiles(char * src, char * dst)
{
    DIR * dir = opendir(src);
    if(dir == NULL){
        perror("CopyFile"); return -1;
    }

    struct dirent * ent;
    int counter=0;
    while ( (ent = readdir(dir)) != NULL){
        if(strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0 ){
            printf("%s\n",ent->d_name);
            strcat(src, ent->d_name);
            if(FileType(src) == 1){
                int src_fd=open(src, O_RDONLY);
                strcat(dst, ent->d_name);
                int dst_fd=creat(dst, S_IRWXU);
                Copy(src_fd, dst_fd);
            }
            else{
                // strcat(src, "/");
                CopyFolder(src, FrontTrack(dst, ent->d_name));
            }
            src=BackTrack(src);
            dst=BackTrack(dst);   
        }
    }
    printf("\n\n");
    return 0;
}
// int CopyFiles(char * src, char * dst, DIR * dir)
// {
//     if(dir == NULL){
//         perror("CopyFile"); return -1;
//     }

//     struct dirent * ent;
//     while ( (ent = readdir(dir)) != NULL){
//         if(strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0 ){
//             if(FileType(FrontTrack(src, ent->d_name))==1){
//                 int dst_fd=creat(FrontTrack(dst, ent->d_name), S_IRWXU);
//                 Copy(open(FrontTrack(src, ent->d_name), O_RDONLY), dst_fd);
//             }
//             else{
//                 strcat(src, "/");
//                 CopyFolder(src, dst);
//             }
//         }
//     }
//     return 0;
// }


int CopyFolder(char * src, char * dst)
{
    // dst=PathMaker(src, dst);
    mkdir(dst, 0700);

    if(CopyFiles(src, dst) == -1){
        return -1;
    }

    return 0;
}


char * BackTrack(char * src)
{
    int i, length=strlen(src);
    for (i = length; i > 0 ; i--){
        if (src[i] == '/' && i !=length ){
            src[i+1]='\0';
            break;
        }
    }
    return src;
}


char * FrontTrack(char * src, char * Next)
{
    int length=strlen(src);
    char * file =(char *)malloc(sizeof(char)*strlen(src));
    strcpy(file, src);
    if( file[length-1] != '/'){
        strcat(file, "/");
        strcat(file, Next);
    }
    else{
        strcat(file, Next);
    }
    strcat(file, "/");
    return file;
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