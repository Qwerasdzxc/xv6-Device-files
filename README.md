# Device files

The goal of the project was to modify the xv6 system to support various new device files, a user tool to manipulate them, and system calls that allow its implementation.
Following is the list of new device files:

* /dev/null - Discards all data written to it but reports that the write operation succeeded
* /dev/zero - Provides as many null characters (ASCII NUL, 0x00) as are read from it
* /dev/kmesg - Provides userspace access to the kernel's log buffer
* /dev/random - Files that serve as pseudorandom number generator. It allows access to environmental noise collected from device drivers and other sources
* /dev/disk - Abstraction over hard drive. Read and write operations on this file operate directly on disk blocks, bypassing the file system

To support some of the operations a new system call was added:

* int lseek (int fd, int offset, int whence);

read () and write () operations on open files add to the internal offset the file structure for that file in that process the number of bytes that have been successfully read / printed.
 
The lseek () system call allows users to manually modify the offset of an open fd file. The behavior of a system call depends on the whence argument. The whence argument is passed one of the following symbolic constants:
SEEK_SET - the offset file is set to the absolute value of the offset argument
SEEK_CUR - the offset of the file is added to the argument offset (negative value leads to rewinding)
SEEK_END - the offset file is set to the sum of the file size and the offset argument


xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern x86-based multiprocessor using ANSI C.

BUILDING AND RUNNING XV6

To build xv6 on an x86 ELF machine (like Linux or FreeBSD), run
"make". On non-x86 or non-ELF machines (like OS X, even on x86), you
will need to install a cross-compiler gcc suite capable of producing
x86 ELF binaries (see https://pdos.csail.mit.edu/6.828/).
Then run "make TOOLPREFIX=i386-jos-elf-". Now install the QEMU PC
simulator and run "make qemu".
