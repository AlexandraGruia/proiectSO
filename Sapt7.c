#define _XOPEN_SOURCE //spune compilatorului sa includă definiții pentru unele funcții suplimentare
#define _GNU_SOURCE //acces la o mulțime de funcții de extensie GNU/Linux nestandard
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include <stdint.h>

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


void fisierBMP(char *numeFisierBMP) 
{
    struct stat st;
    stat(numeFisierBMP,&st);
    int fisierulNecesar = open(numeFisierBMP, O_RDONLY);
    int lungime = 0;
    int inaltime = 0;
    lseek(fisierulNecesar, 18, SEEK_SET);  // Poziționare la începutul informațiilor despre imagine
    read(fisierulNecesar,&inaltime,4);
    read(fisierulNecesar,&lungime,4);
	if(S_ISREG(st.st_mode))
	{
      printf("Este fisier BMP!\n");
     char timp[20];
    char buffer[256];
    int n;
    strftime(timp, sizeof(timp), "%d.%m.%Y", localtime(&st.st_mtime));

    int fisierul = open("statistica.txt",  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWOTH | S_IROTH);
    if (fisierul == -1) 
    {
        perror("EROARE");
        exit(-1);
    }

    write(fisierul, "nume fisier BMP: ", 13);
    write(fisierul, numeFisierBMP, strlen(numeFisierBMP));
    write(fisierul, "\n", 1);

    n = sprintf(buffer, "inaltime: %d\n", inaltime);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "lungime: %d\n", lungime);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "dimensiune: %ld octeti\n", st.st_size);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "identificatorul utilizatorului: %d\n", st.st_uid);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "timpul ultimei modificari: %s\n", timp);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "contorul de legaturi: %d\n", st.st_nlink);
    write(fisierul, buffer, n);
   
    user(st, fisierul);
    grup(st, fisierul);
    altii(st, fisierul);

    close(fisierul);
	}else printf("EROARE\n");
 
    

}


void fisier(char *numeFisier) 
{
    struct stat st;
    stat(numeFisier,&st);
    int fisierulNecesar = open(numeFisier, O_RDONLY);
    lseek(fisierulNecesar, 18, SEEK_SET); 
   
	if(S_ISREG(st.st_mode))
	{
      printf("Este fisier!\n");
       char timp[20];
    char buffer[256];
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

    n = sprintf(buffer, "dimensiune: %ld octeti\n", st.st_size);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "identificatorul utilizatorului: %d\n", st.st_uid);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "timpul ultimei modificari: %s\n", timp);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "contorul de legaturi: %d\n", st.st_nlink);
    write(fisierul, buffer, n);
   
    user(st, fisierul);
    grup(st, fisierul);
    altii(st, fisierul);

    close(fisierul);
	}else printf("EROARE\n");
 
  

}

void director(char *numeDirector) 
{
    struct stat st;
    stat(numeDirector,&st);
    char buffer[256];
    int n;
	if(S_ISDIR(st.st_mode))
	{
      printf("Este director!\n");
  

    int fisierul = open("statistica.txt",  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWOTH | S_IROTH);
    if (fisierul == -1) 
    {
        perror("EROARE");
        exit(-1);
    }

    write(fisierul, "nume director: ", 13);
    write(fisierul, numeDirector, strlen(numeDirector));
    write(fisierul, "\n", 1);

    n = sprintf(buffer, "identificatorul utilizatorului: %d\n", st.st_uid);
    write(fisierul, buffer, n);
   
    user(st, fisierul);
    grup(st, fisierul);
    altii(st, fisierul);

    close(fisierul);

	}else printf("EROARE\n");
 
    
}

void legaturaSimbolica(char *numeLegatura) 
{
    char buffer[256];
    int n;
    struct stat st;
    struct stat sta;
    stat(numeLegatura,&st);
    lstat(numeLegatura,&sta);
    int fisierul = open("statistica.txt",  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWOTH | S_IROTH);
    if (fisierul == -1) 
    {
        perror("EROARE");
        exit(-1);
    }

    write(fisierul, "nume fisier: ", 13);
    write(fisierul, numeLegatura, strlen(numeLegatura));
    write(fisierul, "\n", 1);

    n = sprintf(buffer, "dimensiune: %ld octeti\n", st.st_size);
    write(fisierul, buffer, n);

    n = sprintf(buffer, "dimensiune fisier: %ld octeti\n", sta.st_size);
    write(fisierul, buffer, n);

    user(st, fisierul);
    grup(st, fisierul);
    altii(st, fisierul);

    close(fisierul);

}

void tipFisier(char *nume)
{
    struct stat st;
    DIR *d = opendir(nume);
    if(d==NULL){
        printf("Nu este ceea ce ne trebuie!\n");
        exit(-1);
    }

    struct dirent *in;
    
    while((in=readdir(d))!=NULL) //// va returna un pointer catre o structura de tip struct dirent
    {
        lstat(in->d_name, &st);
      if(strcmp(in->d_name,".") == 0 || strcmp(in->d_name,"..") == 0)
                continue;
      if (S_ISDIR(st.st_mode)) {
            director(in->d_name);
        } else if (S_ISLNK(st.st_mode)) {
            legaturaSimbolica(in->d_name);
        } else if (S_ISREG(st.st_mode) && strstr(in->d_name, ".bmp") != NULL) {
            fisierBMP(in->d_name);
        } else {
            fisier(in->d_name);
        }
    }
}

int main(int argc,char *argv[])
{
	if(argc==2)
	{
	   printf("Argumentele sunt: %s %s\n",argv[0],argv[1]);
	}else printf("EROARE\n");

    tipFisier(argv[1]);

	return 0;
}
