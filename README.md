# Goal:
Quic is a program that copies directories when the copy is repeated. It is called quick incremental copy, in simple terms quic.
It does the same job as the cp command with the difference that it checks if the files that you want to copy at a specified directory have already been copied.

# Program call:
  First compile the code with:
    
    make

  Then, the program is called with this format:
    
    ./quic -v -d -l origindir destdir όπου

    – quick ,

    – origindir is the source path. 

    – destdir is the destination path.


  – Flags:
  
    -v (verbose) when this flag is given, prints the choices/actions that the program makes for the copy/delete of the files.

    -d (deleted) when this flag is given, delete the files from the destdir that have been deleted from the origindir.

    -l (links) when this flag is given, the program takes under cosideration if a file is a link, otherwise it treats it as a file.


# Rules:
-There must be 2 arguments: the directory that is going to be copied
(source directory) and the destination directory. If the arguments are not correct, the program prints an error. 
If the destination directory doesn't exist, the program creates it.

-Lets assume that there is a source directory A and a destination directory T. The
program traverse A, gets informations at the i-nodes and for every a i-node at the A, it searches for a t i-node at the T. 
There are 4 cases:
1. There is no t at the T: t should be created at the correct T position and copies a to t.
If i-node corresponds to a file, the file data should be copied too.
2. t exist at the T but is not the same with a at the A directory. See below for «same» explantion.
In this case, the content of the a i-node should be copied at the t. If the a i-nodes and t are files, their data should be copied too.
3. t exist at the T and is the same as a at A: In this case the program exits.
This is the case that quic is faster than cp.
4. t exist at the T but it doesn't correspond to any a from the A directory: This is the case that a file has been deleted. 
 Therefore, t is getting deleted.
 If the i-nodes, a and t, corresponds to directories, the previous steps should be implemented recursively.

# Same Files:
1. If one of a and t corresponds to a directory and the other to a file, then they are not same.
2. If both a and t corresponds to a directory, we assume that a and t are tha same but this doesn't mean that their directory content is the same. 
In order to find out if their content is the same, their individual contents should be check recursively.
3. If both a and t corresponds to files but their size is different, the files are different.
4. If both a and t corresponds to files with the same size but t has been modified before a has, then they are different.
5. In any other case, the files are the same.

Soft links should refer at the same path. 
For hard links, their data shouldn't be copied more than once.
For example, if the i-nodes a1 and a2 refer to the same file, the copy must have t1 and t2 nodes that refer to the same file blocks.
