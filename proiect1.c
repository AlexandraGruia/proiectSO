#include <stdio.h>
#include <sys/stat.h>


void user(struct stat st)
{
	if(st.st_mode & S_IRWXU)
		printf("drepturi de acces user: RWX\n");
	else if(st.st_mode & S_IRUSR)
		printf("drepturi de acces user: R--\n");
	else if(st.st_mode & S_IWUSR)
		printf("drepturi de acces user: -W-\n");
	else if(st.st_mode & S_IXUSR)
		printf("drepturi de acces user: --X\n");
	else printf("---\n");
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

	}else printf("EROARE\n");
	
		
	
	return 0;
}
