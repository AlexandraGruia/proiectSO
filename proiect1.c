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


void fisier(char *numeFisier, int inaltime, int lungime, int userId, int nrLegaturi) 
{
    struct stat st;
    stat(numeFisier,&st);
	if(S_ISREG(st.st_mode))
	{
	   printf("Este fisier!\n");
	}else printf("EROARE\n");

    char timp[20],buffer[256];
    int n;
    strftime(timp, sizeof(timp), "%d.%m.%Y", localtime(&st.st_mtime));

    int fisierul = open("statistica.txt",  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWOTH | S_IROTH);
    if (fisierul == -1) 
    {
        perror("EROARE");
        exit(-1);
    }

    write(fisierul, "nume fisier: ", 13);
    write(fisierul, numeFisier, strlen(numeFisier));
    write(fisierul, "\n", 1);

    n = sprintf(buffer, "inaltime: %d\n", inaltime);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "lungime: %d\n", lungime);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "dimensiune: %ld octeti\n", st.st_size);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "identificatorul utilizatorului: %d\n", userId);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "timpul ultimei modificari: %s\n", timp);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "contorul de legaturi: %d\n", nrLegaturi);
    write(fisierul, buffer, n);

    user(st, fisierul);
    grup(st, fisierul);
    altii(st, fisierul);

    close(fisierul);

}


int main(int argc,char *argv[])
{
	if(argc==2)
	{
	   printf("Argumentele sunt: %s %s\n",argv[0],argv[1]);
	}else printf("EROARE\n");
	
  int userID = getpid();

  fisier(argv[1], 1920, 1280, userID, 5);

	return 0;
}
