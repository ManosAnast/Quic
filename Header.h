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
int DeepCopy(char * src, char * dst, bool Vflag, bool Dflag, bool Lflag);


/* It copies all the files from the source path to the destination path.
 * 
 * src: source path.
 * dst: destination path.
 * dir: Directory pointer.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int DeepCopyFiles(char * src, char * dst, DIR * dir, bool Vflag, bool Dflag, bool Lflag);


/* It copies all the files from the source path, that have changed, to the destination path.
 * 
 * src: source path.
 * dst: destination path.
 * dir: Directory pointer.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int CopyFiles(char * src, char * dst, DIR * dir, bool Vflag, bool Dflag, bool Lflag);


/* It checks if a path is a file.
 * 
 * src: source path.
 * Lflag: flag for -l.
 *
 * Return:
 *      If the path is a hard link it returns 3.
 *      If the path is a symbolic link it returns 2.
 *      If the path is a file it returns 1.
 *      If the path is a directory it returns 0.
 *      In case of something going wrong it returns -1.
*/
int FileType(char * src, bool Lflag);


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


/* It checks if the 2 files are equal.
 * It takes under consideration all the cases.
 * 
 * src_fd: file descriptor of the source file.
 * dst_fd: file descriptor of the destination file.
 *
 * Return:
 *      If the files are equal returns the 1.
 *      If the files aren't equal returns the 0.
*/
int isEqual(char * src_fd, char * dst_fd);


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


/* Delete a file/directory, if it needs to be deleted.
 * 
 * src: source path.
 * dst: destination path.
 *
 * Return:
 *      In case of success it returns the 0.
 *      In case of something going wrong it returns -1
*/
int Delete(char * src, char * dst, bool Vflag);



int Link(char * src, char * dst);