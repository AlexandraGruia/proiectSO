#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>



void user(struct stat st, int fisierul)
{
   write(fisierul, "Drepturile de acces pentru useri: ", 33);
   if(st.st_mode & S_IRUSR) write(fisierul, "R", 1);
     else write(fisierul, "-", 1);
   if(st.st_mode & S_IWUSR) write(fisierul, "W", 1);
     else write(fisierul, "-", 1);
   if(st.st_mode & S_IXUSR) write(fisierul, "X", 1);
     else write(fisierul, "-", 1);
   write(fisierul, "\n", 1);
}

void grup(struct stat st, int fisierul)
{
    write(fisierul, "Drepturile de acces pentru grup: ", 33);
    if(st.st_mode & S_IRGRP) write(fisierul, "R", 1);
      else write(fisierul, "-", 1);
    if(st.st_mode & S_IWGRP) write(fisierul, "W", 1);
      else write(fisierul, "-", 1);
    if(st.st_mode & S_IXGRP) write(fisierul, "X", 1);
      else write(fisierul, "-", 1);
    write(fisierul, "\n", 1);
}

void altii(struct stat st, int fisierul)
{
    write(fisierul, "Drepturile de acces pentru altii: ", 34);
    if (st.st_mode & S_IROTH) write(fisierul, "R", 1);
      else write(fisierul, "-", 1);
    if (st.st_mode & S_IWOTH) write(fisierul, "W", 1);
      else write(fisierul, "-", 1);
    if (st.st_mode & S_IXOTH) write(fisierul, "X", 1);
      else write(fisierul, "-", 1);
    write(fisierul, "\n", 1);
}


void fisier(char *numeFisier, int inaltime, int lungime, char *userId, int nrLegaturi) 
{
    struct stat st;
    stat(numeFisier,&st);
	if(S_ISREG(st.st_mode))
	{
	   printf("Este fisier!\n");
	}else printf("EROARE\n");

    char timp[20];
    strftime(timp, sizeof(timp), "%d.%m.%Y", localtime(&st.st_mtime));

    FILE *fisierul = fopen("statistica.txt", "w");
    if (fisierul == NULL) 
    {
        perror("EROARE");
        exit(-1);
    }

    fprintf(fisierul, "nume fisier: %s\n", numeFisier);
    fprintf(fisierul, "inaltime: %d\n", inaltime);
    fprintf(fisierul, "lungime: %d\n", lungime);
    fprintf(fisierul, "dimensiune: %ld octeti\n", st.st_size);
    fprintf(fisierul, "identificatorul utilizatorului: %s\n", userId);
    fprintf(fisierul, "timpul ultimei modificari: %s\n", timp);
    fprintf(fisierul, "contorul de legaturi: %d\n", nrLegaturi);
    user(st, fisierul);
    grup(st, fisierul);
    altii(st, fisierul);

    fclose(fisierul);
}


int main(int argc,char *argv[])
{

	if(argc==2)
	{
	   printf("Argumentele sunt: %s %s\n",argv[0],argv[1]);
	}else printf("EROARE\n");
	
    fisier(argv[1], 1920, 1280, "<user id>", 5);

	return 0;
}
