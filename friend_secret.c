#include <stdio.h>
#include <utmp.h>
#include <sys/types.h> 	//lseek.stat
#include <sys/stat.h>	//stat
#include <sys/uio.h>
#include <unistd.h> 	//close.read.write.lseek.stat
#include <fcntl.h> 		//open
#include <pwd.h>
#include <string.h>


int main()
{
    FILE *fp = NULL;

    fp = fopen("/home/lhl/.friend", "wt+");
    fprintf(fp, "%s\r\n", "user1");
    fprintf(fp, "%s\r\n", "user2");
    fprintf(fp, "%s\r\n", "lhl");
    fclose(fp);

    fp = fopen("/home/lhl/.secret", "wt+");
    fprintf(fp, "%s\r\n", "Hello My Friend.");
    fclose(fp);
}
