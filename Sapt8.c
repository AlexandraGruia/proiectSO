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
#include <sys/wait.h>

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


void fisierBMP(char *dir, char *numeFisierBMP) 
{
    struct stat st;
    stat(dir,&st);
    char path[256];
    sprintf(path, "%s/%s_statistica.txt", dir, numeFisierBMP);
    int fisier1= open(numeFisierBMP, O_RDONLY);
    if (fisier1 == -1) 
    {
        perror("EROARE");
        exit(-1);
    }
    int lungime = 0;
    int inaltime = 0;
    lseek(fisier1, 18, SEEK_SET);  // Poziționare la începutul informațiilor despre imagine
    read(fisier1,&inaltime,4);
    read(fisier1,&lungime,4);
    
    if(S_ISREG(st.st_mode))
	{
      printf("Este fisier BMP!\n");

    int fisier2 = open(path,  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWOTH | S_IROTH);
    if (fisier2 == -1) 
    {
        perror("EROARE");
        exit(-1);
    }

    char timp[20];
    char buffer[256];
    int n;
    strftime(timp, sizeof(timp), "%d.%m.%Y", localtime(&st.st_mtime));

    write(fisier2, "nume fisier BMP: ", 13);
    write(fisier2, numeFisierBMP, strlen(numeFisierBMP));
    write(fisier2, "\n", 1);

    n = sprintf(buffer, "inaltime: %d\n", inaltime);
    write(fisier2, buffer, n);

    n = sprintf(buffer, "lungime: %d\n", lungime);
    write(fisier2, buffer, n);

    n = sprintf(buffer, "dimensiune: %ld octeti\n", st.st_size);
    write(fisier2, buffer, n);

    n = sprintf(buffer, "identificatorul utilizatorului: %d\n", st.st_uid);
    write(fisier2, buffer, n);

    n = sprintf(buffer, "timpul ultimei modificari: %s\n", timp);
    write(fisier2, buffer, n);

    n = sprintf(buffer, "contorul de legaturi: %d\n", st.st_nlink);
    write(fisier2, buffer, n);
   
    user(st, fisier2);
    grup(st, fisier2);
    altii(st, fisier2);

    close(fisier2);

	}else printf("EROARE\n");
 
    
}


void fisier(char *dir, char *numeFisier) 
{
    struct stat st;
    stat(numeFisier,&st);
    char path[256];
    sprintf(path, "%s/%s_statistica.txt", dir, numeFisier);
    int fisier1= open(numeFisier, O_RDONLY);
    if (fisier1 == -1) 
    {
        perror("EROARE");
        exit(-1);
    }
    lseek(fisier1, 18, SEEK_SET); 
   
	if(S_ISREG(st.st_mode))
	{
      printf("Este fisier!\n");
     char timp[20];
    char buffer[256];
    int n;
    strftime(timp, sizeof(timp), "%d.%m.%Y", localtime(&st.st_mtime));

    int fisier2 = open(path,  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWOTH | S_IROTH);
    if (fisier2 == -1) 
    {
        perror("EROARE");
        exit(-1);
    }

    write(fisier2, "nume fisier: ", 13);
    write(fisier2, numeFisier, strlen(numeFisier));
    write(fisier2, "\n", 1);

    n = sprintf(buffer, "dimensiune: %ld octeti\n", st.st_size);
    write(fisier2, buffer, n);

    n = sprintf(buffer, "identificatorul utilizatorului: %d\n", st.st_uid);
    write(fisier2, buffer, n);

    n = sprintf(buffer, "timpul ultimei modificari: %s\n", timp);
    write(fisier2, buffer, n);

    n = sprintf(buffer, "contorul de legaturi: %d\n", st.st_nlink);
    write(fisier2, buffer, n);
   
    user(st, fisier2);
    grup(st, fisier2);
    altii(st, fisier2);

    close(fisier2);

	}else printf("EROARE\n");
 
    
}

void director(char *dir, char *numeDirector) 
{
    struct stat st;
    stat(numeDirector,&st);
    char path[256];
    sprintf(path, "%s/%s_statistica.txt", dir, numeDirector);
    int fisier1= open(numeDirector, O_RDONLY);
    if (fisier1 == -1) 
    {
        perror("EROARE");
        exit(-1);
    }
    
	if(S_ISDIR(st.st_mode))
	{
      printf("Este director!\n");
     char buffer[256];
    int n;

    int fisier2 = open(path,  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWOTH | S_IROTH);
    if (fisier2 == -1) 
    {
        perror("EROARE");
        exit(-1);
    }

    write(fisier2, "nume director: ", 13);
    write(fisier2, numeDirector, strlen(numeDirector));
    write(fisier2, "\n", 1);

    n = sprintf(buffer, "identificatorul utilizatorului: %d\n", st.st_uid);
    write(fisier2, buffer, n);
   
    user(st, fisier2);
    grup(st, fisier2);
    altii(st, fisier2);

    close(fisier2);

	}else printf("EROARE\n");
 
    
}

void legaturaSimbolica(char *dir, char *numeLegatura) 
{
    struct stat st;
    struct stat sta;
    stat(numeLegatura,&st);
    lstat(numeLegatura,&sta); //se aplica oricarui tip de fisier ce nu este legatura simbolica.
    char path[256];
    sprintf(path, "%s/%s_statistica.txt", dir, numeLegatura);
    int fisier1= open(numeLegatura, O_RDONLY);
    if (fisier1 == -1) 
    {
        perror("EROARE");
        exit(-1);
    }
    
    char buffer[256];
    int n;

    int fisier2 = open(path,  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWOTH | S_IROTH);
    if (fisier2 == -1) 
    {
        perror("EROARE");
        exit(-1);
    }

    write(fisier2, "nume fisier: ", 13);
    write(fisier2, numeLegatura, strlen(numeLegatura));
    write(fisier2, "\n", 1);

    n = sprintf(buffer, "dimensiune: %ld octeti\n", st.st_size);
    write(fisier2, buffer, n);

    n = sprintf(buffer, "dimensiune fisier: %ld octeti\n", sta.st_size);
    write(fisier2, buffer, n);

    user(st, fisier2);
    grup(st, fisier2);
    altii(st, fisier2);

    close(fisier2);

}

void imagineProces(char *numeImagine)
{
    struct stat st;
    stat(numeImagine, &st);
    int fisier= open(numeImagine, O_RDONLY);
    if (fisier == -1) 
    {
        perror("EROARE");
        exit(-1);
    }
    int lungime = 0;
    int inaltime = 0;
    lseek(fisier, 18, SEEK_SET);  // Poziționare la începutul informațiilor despre imagine
    read(fisier,&inaltime,4);
    read(fisier,&lungime,4);

    int numarPixeli = lungime * inaltime;
    char pixeli[3];
    
    for(int i=0; i < numarPixeli; i++)
    {
        read(fisier,pixeli,sizeof(pixeli));
        int gri = 0.299 * pixeli[0] + 0.587 * pixeli[1] + 0.114 * pixeli[2];
        pixeli[0] = gri;
        pixeli[1] = gri;
        pixeli[2] = gri;
        lseek(fisier, -3, SEEK_CUR); //Mută poziția pointerului fișierului în locația dată.
        write(fisier, pixeli, sizeof(pixeli));
    }

    close(fisier);
}

void tipFisier(char *dir, char *nume)
{
    struct stat st;
    int nrLinii=0;
    
    DIR *d = opendir(nume);
    if(d==NULL){
        printf("Nu este ceea ce ne trebuie!\n");
        exit(-1);
    }

   struct dirent *in;
 
    while((in = readdir(d)) !=NULL)//va returna un pointer catre o structura de tip struct dirent
    {
        
         lstat(in->d_name, &st);
        if(strcmp(in->d_name,".") == 0 || strcmp(in->d_name,"..") == 0)
                continue;
        
        pid_t pid = fork();
        
        if(pid == 0){
            if (S_ISDIR(st.st_mode)) {
                director(dir, in->d_name);
                nrLinii++;
            }else if (S_ISLNK(st.st_mode)) {
            legaturaSimbolica(dir, in->d_name);
            nrLinii++;
        } else if (S_ISREG(st.st_mode) && strstr(in->d_name, ".bmp") != NULL) {
                pid_t pidd = fork();
                if(pidd == 0){
                    imagineProces(in->d_name);
                    exit(-1);
                }
                int status;
                pid_t pid;
                while((pid = waitpid(-1, &status, 0)) > 0){
                    if(WIFEXITED(status)){
                        nrLinii = WEXITSTATUS(status);
                        printf("S-a încheiat procesul cu pid-ul %d și codul %d\n", pid, nrLinii);
                    }
                }
                
                fisierBMP(dir,in->d_name);
                nrLinii++;
        } else {
            fisier(dir, in->d_name);
            nrLinii++;
        }
        exit(nrLinii);
        }else if(pid < 0){
            perror("Eroare");
            exit(1);
    }
}
}

int main(int argc,char *argv[])
{
	if(argc==3)
	{
	   printf("Argumentele sunt: %s %s\n",argv[0],argv[1],argv[2]);
	}else printf("EROARE\n");

   tipFisier(argv[1],argv[2]);

	return 0;
}