# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <dirent.h>
# include <errno.h>
# include <stdbool.h>
# include <time.h>
# define nullstring " "

extern bool Vflag, Dflag, Lflag;


/* It makes a deepcopy of the source to the destination, which means that copies the cp -r command.
 * At the end it closes the files.
 * 
 * src: source path.
 * dst: destination path.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int DeepCopy(char * src, char * dst);


/* It copies all the files from the source path to the destination path.
 * 
 * src: source path.
 * dst: destination path.
 * copied: Is a pointer to int that keeps the number of files/directories that have been copied.
 * bytes:  Is a pointer to int that keeps the number of bytes that have been copied.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int DeepCopyFiles(char * src, char * dst, int * copied, int * bytes);


/* It copies all the content of the source to the destination path.
 *
 * src_fd: source file descriptor.
 * dst_fd: destination file descriptor.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int Copy(int src_fd, int dst_fd);


/* It copies all the files from the source path, that have changed, to the destination path.
 * 
 * src: source path.
 * dst: destination path.
 * copied: Is a pointer to int that keeps the number of files/directories that have been copied.
 * bytes:  Is a pointer to int that keeps the number of bytes that have been copied.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int CopyFiles(char * src, char * dst, int * copied, int * bytes);


/* Delete a file/directory, if it needs to be deleted.
 * 
 * src: source path.
 * dst: destination path.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int Delete(char * src, char * dst);


/* It checks if the 2 files have the same size.
 * 
 * src_fd: file descriptor of the source file.
 * dst_fd: file descriptor of the destination file.
 *
 * Return:
 *      If the files have the same size, it returns the 1.
 *      If the files don't have the same size, it returns the 0.
*/
int EqualSize(int src_fd, int dst_fd);


/* It checks if the 2 files are modified at the same time.
 * 
 * src_fd: file descriptor of the source file.
 * dst_fd: file descriptor of the destination file.
 *
 * Return:
 *      If the files are modified at the same time, it returns the 1.
 *      If the files aren't modified at the same time, it returns the 0.
*/
int SameDate(int src_fd, int dst_fd);


/* It mimics the "cp .." command. Takes a path and takes one step back.
 *
 * pth: File path that we want to change.
 *
 * Return:
 *      In case of success it returns the new path.
*/
char * BackTrack(char * pth);


/* It adds to the file path, the file/directory that we want to go.
 *
 * pth: File path that we want to change.
 * Next: File or directory that we want to go to.
 *
 * Return:
 *      In case of success it returns the new path.
*/
char * FrontTrack(char * pth, char * Next);


/* It checks the type of the path.
 * 
 * src: source path.
 *
 * Return:
 *      If the path is a hard link it returns 3.
 *      If the path is a symbolic link it returns 2.
 *      If the path is a file it returns 1.
 *      If the path is a directory it returns 0.
 *      In case of something going wrong it returns -1.
*/
int FileType(char * src);


/* Get the size of a given path.
 * 
 * dst: the path that we want the size of.
 *
 * Return:
 *      In case of success it returns the size of the path.
 *      In case of something going wrong it returns -1.
*/
int getSize(char * dst);