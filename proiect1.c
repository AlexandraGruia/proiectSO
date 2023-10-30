#include <stdio.h>
#include <sys/stat.h>


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
