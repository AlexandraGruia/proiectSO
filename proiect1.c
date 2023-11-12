#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>


void user(struct stat st, FILE *fisierul)
{
   fprintf(fisierul, "Drepturile de acces pentru useri: ");
   if(st.st_mode & S_IRUSR) fprintf(fisierul, "R");
     else fprintf(fisierul, "-");
   if(st.st_mode & S_IWUSR) fprintf(fisierul, "W");
     else fprintf(fisierul, "-");
   if(st.st_mode & S_IXUSR) fprintf(fisierul, "X");
     else fprintf(fisierul, "-");
   fprintf(fisierul, "\n");
}

void grup(struct stat st, FILE *fisierul)
{
    fprintf(fisierul, "Drepturile de acces pentru grup: ");
    if(st.st_mode & S_IRGRP) fprintf(fisierul, "R");
      else fprintf(fisierul, "-");
    if(st.st_mode & S_IWGRP) fprintf(fisierul, "W");
      else fprintf(fisierul, "-");
    if(st.st_mode & S_IXGRP) fprintf(fisierul, "X");
      else fprintf(fisierul, "-");
    fprintf(fisierul, "\n");
}

void altii(struct stat st, FILE *fisierul)
{
    fprintf(fisierul, "Drepturile de acces pentru altii: ");
    if (st.st_mode & S_IROTH) fprintf(fisierul, "R");
      else fprintf(fisierul, "-");
    if (st.st_mode & S_IWOTH) fprintf(fisierul, "W");
      else fprintf(fisierul, "-");
    if (st.st_mode & S_IXOTH) fprintf(fisierul, "X");
      else fprintf(fisierul, "-");
    fprintf(fisierul, "\n");
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
