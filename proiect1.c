#include <stdio.h>
#include <sys/stat.h>

void user(struct stat st)
{
	printf("Drepturile de acces pentru useri: ");
	if(st.st_mode & S_IRUSR) printf("R");
   	else printf("-");
	if(st.st_mode & S_IWUSR) printf("W");
   	else printf("-");
	if(st.st_mode & S_IXUSR) printf("X");
    	else printf("-");
   	printf("\n");
}

void grup(struct stat st)
{
 	printf("Drepturile de acces pentru grup: ");
   	if(st.st_mode & S_IRGRP) printf("R");
   	else printf("-");
	if(st.st_mode & S_IWGRP) printf("W");
   	else printf("-");
	if(st.st_mode & S_IXGRP) printf("X");
   	else printf("-");
   	printf("\n");
}

void altii(struct stat st)
{
	printf("Drepturile de acces pentru altii: ");
	if (st.st_mode & S_IROTH) printf("R");
	else printf("-");
	if (st.st_mode & S_IWOTH) printf("W");
	else printf("-");
	if (st.st_mode & S_IXOTH) printf("X");
	else printf("-");
	printf("\n");
}

int main(int argc,char *argv[])
{
	struct stat st;
	if(argc==2)
	{
		printf("Argumentele sunt: %s %s\n",argv[0],argv[1]);	
	}else printf("EROARE\n");

	stat(argv[1],&st);
	if(S_ISREG(st.st_mode))
	{
		printf("Este fisier!\n");
       		user(st);
		grup(st);
		altii(st);
	}else printf("EROARE\n");
	
	return 0;
}
