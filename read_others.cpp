/*******************************************************************************
 *
 * to read other user's file
 *
 ******************************************************************************/
/*
#include <stdio.h>

int main(argc, argv)
	int argc;
	char *argv[];
{
	FILE *fp;
	char c;

	fp = fopen (argv[1], "r");
	while ((c=fgetc(fp))!=EOF)
		printf ("%c", c);

	return 0;
}//main()
*/

#include <utmp.h>
#include <stdio.h>
#include <sys/types.h> 	//lseek.stat
#include <sys/stat.h>	//stat
#include <sys/uio.h>
#include <unistd.h> 	//close.read.write.lseek.stat
#include <fcntl.h> 		//open
#include <pwd.h>
#include <string.h>
#include <errno.h>

struct userlist {
	int 	order;
	char 	user[32];
	char 	tty[8];
	
	userlist(){order=0;}
	void setuser(char *a){ for(int i=0;i<32;i++)user[i]=a[i]; }
	void settty(char *a){ for(int i=0;i<10;i++)tty[i]=a[i]; }
};
	
int main()
{
	int i, choice, read_s = 0;
	int list_length = 0, cmp_len;
	char tmpdir_secret[64], tmpdir_friend[64], buffer[128];

	struct utmp user_rec;
	struct passwd *self;

	FILE *fp;
	userlist *list = new userlist[100];
	

	self = getpwuid(getuid());
    printf("check : %s\n",self->pw_name);
	setuid(0);
    printf("check : %s\n",self->pw_name);

	fp = fopen ("/var/run/utmp", "r");

	// list all user on-line
	for(i = 0; fread(&user_rec, sizeof(struct utmp), 1, fp) > 0; i++){
		if(i > 1){		
			list[i-1].order = i - 1;
			list[i-1].setuser(user_rec.ut_user);
			list[i-1].settty(user_rec.ut_line);
			list_length++;
		}	
	}

	for(i = 1; i <= list_length; i++){
		printf("%02d %-10s %-5s\n", list[i].order, list[i].user, list[i].tty);
	}
	// ---------------------

	
	printf("\nWhom to query?\n");
	scanf("%d", &choice);
	sprintf(tmpdir_friend, "%s/%s/%s", (char *)"/home", list[choice].user, (char *)".friend");
	sprintf(tmpdir_secret, "%s/%s/%s", (char *)"/home", list[choice].user, (char *)".secret");
	fclose(fp);

    printf("tmpdir_friend : %s\n", tmpdir_friend);
    printf("tmpdir_secret : %s\n", tmpdir_secret);

	fp = fopen(tmpdir_friend, "rt+");
    if(fp == NULL){
        int errnum = errno;
        fprintf(stderr, "Value of errnum: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
        return 0;
    }

	while(fgets(buffer, sizeof(buffer), fp) != NULL){
        buffer[strlen(buffer) - 1] = '\0';
        buffer[strlen(buffer) - 1] = '\0';
        printf("buffer : %d\n", strlen(buffer));

		if(strlen(buffer) > strlen(self->pw_name)){
			cmp_len = strlen(buffer);
		}else{
			cmp_len = strlen(self->pw_name);
		}

        printf("self->pw_name : %s\n", self->pw_name);
        printf("buffer : %s\n", buffer);
		if(memcmp(buffer, self->pw_name, cmp_len) == 0){
            printf("same\n");
			read_s = 1;
			break;
		}
	}
    printf("check\n");
	fclose(fp);
	
	if(read_s == 1){
		fp = fopen(tmpdir_secret, "rt+");
        if(fp == NULL){
            int errnum = errno;
            fprintf(stderr, "Value of errnum: %d\n", errno);
            perror("Error printed by perror");
            fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
            return 0;
        }

		while(fgets(buffer, sizeof(buffer), fp) != NULL){
			printf("%s\n", buffer);
		}

		fclose(fp);
	}
	
	
	return 0;
}

















