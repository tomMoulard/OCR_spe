#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
// https://openclassrooms.com/courses/apprenez-a-programmer-en-c/lire-et-ecrire-dans-des-fichiers
 
#define LG_REC 101
#define LG_DATA 100
#define LG_MAX 1000
 
 
char lgOK = 'I';
char lgKO = 'D';
 
int insert(FILE*, char[30]);
 
int main(int argc, char *argv[])
{
// int i;
// for (i=0; i < argc; i++) {
    // printf("argv[ %ld  ]: %s \n", i, argv[i]);
// }
 
if (argc != 4){
    printf ("Oups!!! pour appeler : %s <filename> <insert|insertEnd|delete|recherche|dump> mot \n", argv[0]);
    printf ("exemple : ./a.exe fichier.txt insert Guillaume \n");
    return -1;
} else {
    printf("%s %s %s %s \n", argv[0],argv[1],argv[2],argv[3]);
}   
    
    
FILE* fichier = NULL;
fichier = fopen(argv[1], "rb+");
 
if (strcmp (argv[2] , "insertEnd" ) == 0 )     insertEnd(fichier, argv[3]);
if (strcmp (argv[2] , "insert"    ) == 0 )     insert(fichier, argv[3]);
if (strcmp (argv[2] , "delete"    ) == 0 )     delete(fichier, argv[3]);
if (strcmp (argv[2] , "dump"      ) == 0 )       dump(fichier, argv[3]);
if (strcmp (argv[2] , "recherche" ) == 0 )  recherche(fichier, argv[3]);
 
fclose(fichier);
return EXIT_SUCCESS;
}
 
int insertEnd(FILE* fic, char mot [LG_REC]  ){
    char ecrit[LG_REC];
   
    memset(ecrit, ' ', LG_REC);
    strncpy(ecrit, mot, strlen(mot));
    fseek(fic, 0, SEEK_END);  
    fputc (lgOK, fic );
    ecrit[LG_REC] = '\0';
    fprintf(fic, "%s", ecrit);
    return EXIT_SUCCESS;
}
 
int dump(FILE* fic, char mot [LG_REC]  ){
    char lu[LG_REC];
    char format[100];
    int cpt = 1 ;
   
    sprintf(format, "%%%ds",LG_DATA);
    while ( fscanf(fic, format, lu)>0) {
        printf("%d : %s\n", cpt++,  lu);
    }
    return EXIT_SUCCESS;   
}
 
int recherche(FILE* fic, char mot [LG_REC]  ){
    char lu[LG_REC];
    char format[100];
    char motrecherche[LG_REC];
    int cpt = 1 ;
   
    sprintf(format, "%%%ds",LG_DATA);
    sprintf(motrecherche, "%c%s", lgOK, mot);
    while ( fscanf(fic, format, lu)>0) {
        if (strcmp(lu, motrecherche)==0) {
            printf("good %d-%s\n", cpt,  lu);
        }
    cpt++;
    }
    return EXIT_SUCCESS;       
}
 
 
int delete(FILE* fic, char mot [LG_REC]  ){
    char lu[LG_REC];
    char format[100];
    char motrecherche[LG_REC];
    int cpt = 1 ;
   
    sprintf(format, "%%%ds",LG_DATA);
    sprintf(motrecherche, "%c%s", lgOK, mot);
    while ( fscanf(fic, format, lu)>0) {
        if (strcmp(lu, motrecherche)==0) {
            fseek(fic, -1 * strlen(motrecherche),  SEEK_CUR);  
            fputc (lgKO, fic );
            printf("Delete record %d\n", cpt);
            return EXIT_SUCCESS;       
        }
    cpt++;
    }
}
 
int insert(FILE* fic, char mot [LG_REC]  ){
    char lu[LG_REC];
    char ecrit[LG_REC];
    char format[100];
    char motrecherche[LG_REC];
    int cpt = 1 ;
 
    memset(ecrit, ' ', LG_REC);
    strncpy(ecrit, mot, strlen(mot));
   
    sprintf(format, "%%%ds",LG_DATA);
    while ( fscanf(fic, format, lu)>0) {
        if (lu[0] == lgKO) {
            fseek(fic, -1 * strlen(lu),  SEEK_CUR);  
            fputc (lgOK, fic );
            fprintf(fic, "%s", ecrit);
            printf("Ecrit %d\n", cpt);
            return EXIT_SUCCESS;       
        }
    cpt++;
    }
fputc (lgOK, fic );
fprintf(fic, "%s", ecrit);
return EXIT_SUCCESS;
}