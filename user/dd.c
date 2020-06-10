#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "kernel/lseek.h"
#include "user.h"

#define NULL 0

char* strstr(char *str, char *substr)
{
	  while (*str) 
	  {
		    char *begin = str;
		    char *pattern = substr;
		    
		    while (*str && *pattern && *str == *pattern) 
			{
			      str++;
			      pattern++;
		    }
		    if (!*pattern)
		    	  return begin;
		    	  
		    str = begin + 1;
	  }
	  return 0;
}

char* substring (const char* input, int offset, int len, char* dest)
{
  int input_len = strlen (input);

  if (offset + len > input_len)
  {
     return 0;
  }

  strncpy (dest, input + offset, len);
  return dest;
}

int strspn(const char *s1, const char *s2)
{
    int ret=0;
    while(*s1 && strchr(s2,*s1++))
        ret++;
    return ret;    
}

int strcspn(const char *s1, const char *s2)
{
    int ret=0;
    while(*s1)
        if(strchr(s2,*s1))
            return ret;
        else
            s1++,ret++;
    return ret;
}

char *strtok(char *str, const char *delim)
{
    static char* p=0;
    if(str)
        p=str;
    else if(!p)
        return 0;
    str=p+strspn(p,delim);
    p=str+strcspn(str,delim);
    if(p==str)
        return p=0;
    p = *p ? *p=0,p+1 : 0;
    return str;
}

int
main(int argc, char *argv[])
{
	int fdi = 0, fdo = 1, bs = 512, count, skip = 0, seek = 0, i;
    char *iname, *oname;

    for (i = 1; i < argc; i ++)
    {
        char *currArg = argv[i];
        if (strstr(currArg, "if="))
        {
            char *token = strtok(currArg, "=");
            token = strtok(NULL, "=");
            iname = token;
        }
        else if (strstr(currArg, "of="))
        {
            char *token = strtok(currArg, "=");
            token = strtok(NULL, "=");
            oname = token;
        }
        else if (strstr(currArg, "bs="))
        {
            char *token = strtok(currArg, "=");
            token = strtok(NULL, "=");
            bs = atoi(token);
        }
        else if (strstr(currArg, "count="))
        {
            char *token = strtok(currArg, "=");
            token = strtok(NULL, "=");
            count = atoi(token);
        }
        else if (strstr(currArg, "skip="))
        {
            char *token = strtok(currArg, "=");
            token = strtok(NULL, "=");
            skip = atoi(token);
        }
        else if (strstr(currArg, "seek="))
        {
            char *token = strtok(currArg, "=");
            token = strtok(NULL, "=");
            seek = atoi(token);
        }
    }

    if(iname != 0 && (fdi = open(iname, O_RDONLY)) < 0){
        printf("dd input: cannot open %s\n", iname);
        exit();
    }

    if(oname != 0 && (fdo = open(oname, O_RDWR)) < 0){
        fdo = open(oname, O_RDWR | O_CREATE);
        if (fdo < 0) {
            printf("dd output: cannot open %s\n", oname);
            exit();
        }
    }

    char buff[bs];

    lseek(fdi, skip, SEEK_SET);

    int n = read(fdi, buff, bs);
    if (n < 0) {
        printf("read error");
        exit();
    }

    lseek(fdi, seek, SEEK_SET);

    n = write(fdo, buff, bs);
    if (n != bs) {
        printf("write error");
        exit();
    }

    printf("\ndd: %d bytes written\n", n);

    close(fdi);
    close(fdo);
	exit();
}