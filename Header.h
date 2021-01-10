# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <dirent.h>
# include <errno.h>
# define nullstring " "


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


/* It copies all the files that the directory "dir" has.
 * 
 * src: source path.
 * dst: destination path.
 * dir: Directory pointer.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int CopyFiles(char * src, char * dst, DIR * dir);


/* It creates a new folder and copies it's content.
 * 
 * src: source path.
 * dst: destination path.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int CopyFolder(char * src, char * dst, char * Next);


/* It checks if a path is a file.
 * 
 * src: source path.
 *
 * Return:
 *      If the path is a symbolic link it returns 2.
 *      If the path is a file it returns 1.
 *      If the path is a directory it returns 0.
 *      In case of something going wrong it returns -1.
*/
int FileType(char * src);


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


/* It adds to the destination path the file that needs to be created, in order to copy to it the source file.
 *
 * src: source file path.
 * dst: destination file path.
 *
 * Return:
 *      In case of success it returns the new destination path.
 *      In case of something going wrong it returns nullstring.
*/
char * PathMaker(char * src, char * dst);