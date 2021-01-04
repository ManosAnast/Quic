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
 * src_fd: source file descriptor.
 * src: source path.
 * dst: destination path.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int DeepCopy(int src_fd, char * src, char * dst);


/* It copies all the files that the directory "dir" has.
 * 
 * src_fd: source file descriptor.
 * src: source path.
 * dst: destination path.
 * dir: A DIR stream that points to the directory that you want to copy it's files.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int CopyFiles(int src_fd, char * src, char * dst, DIR * dir);


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