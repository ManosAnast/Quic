# include "Header.h"

int DeepCopy(int src_fd, char * src, char * dst)
{
    
    // Create the destination path since we enter this function if the destination path doesn't exit
    // and add the last part of the source path, which is the file.
    mkdir(dst, 0700);
    dst=PathMaker(src,dst);

    //Create the file at the destination path
    int dst_fd=creat(dst, S_IRWXU);
    if (dst_fd == -1){
        perror("DeepCopy"); return dst_fd;
    }

    // Copy the content of the source path to the destination path
    if (Copy(src_fd, dst_fd) == -1){
        return -1;
    }
    close(src_fd); close(dst_fd);

    return dst_fd;
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