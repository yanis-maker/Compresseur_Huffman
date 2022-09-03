/*!
 *\file Compresseur.c
 *\brief Fichier pour le compresseur contenant le code des toutes les fontions présentes dans le fichier d'en tête
 *\author Yanis Bouallouche ; Ophélia Benin 
 *
 *Cette partie concerne le compresseur
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "Compresseur.h"

/*!
 *\n FONCTION affiche
 *\param[in] int*  Un tableau d'entier contenant le nombre d'occurence de chaque caractère
 *\return Ne retourne rien
 *\brief Fonction qui affiche le nombre d'occurence de chaque caractère et sa probabilité
 */
void affiche(int* occurence){

  /*!Cette fonction calcule d'abord le nombre total de caractère, et ensuite elle affiche ce dernier ainsi que le nombre d'occurence et la probabilté de chaque caractère*/ 
  float total=0;
  for(int i=0;i<ASCII;i++){
    if(occurence[i]>0){
      total+=occurence[i];
    }
  }

  printf("TOTAL CARACTÈRE =======>%f\n",total);
  printf("<------------------------------------------------------->\n");
  printf("PROBABILITES & NOMBRE D'OCCURENCE\n");
  printf("<------------------------------------------------------>\n");
  for(int i=0;i<ASCII;i++){
    if(occurence[i]>0){
      printf("Caractère %c(%i) Nb ocuurence: %i ; Probabilité : %f\n",i,i,occurence[i],occurence[i]/total);
    }
  }
}

/*---------------------------------------------------------------*/

/*
*FONCTION: afficheArbre
*PARAMETRE: ne prend aucun paramètre
*RETURN: ne retourne rien
*fonction qui affiche les noeud de l'arbre
*/ 
void afficheArbre(){


  /*!Cette fonction affiche l'arbre de huffman, pour chaque feuilles,le nombre d'occurences et l'indice du noeud pere est affiché*/
  /*!Et pour chaque noeud le nombre d'occurence, l'indice du noeud pere de l'enfant gauche ainsi que l'enfant D est affiché*/
  printf("\n");
  printf("<----------------------------------------------------->\n");
  printf("ARBRE BINAIRE\n");
  printf("<----------------------------------------------------->\n");
  for(int i=0;i<NOEUD;i++){

    if(arbre[i].nbOc != 0){

      if(i<ASCII){
        printf("Feuille %i(%c): Nb occurence: %i ; pere: %i \n",i,i,arbre[i].nbOc,arbre[i].pere);
      }

      if(i>=ASCII){
        printf("Noeud %i: Nb occurence: %i ; pere: %i ; Enfant Gauche: %i ;  Enfant Droit: %i\n",i,arbre[i].nbOc,arbre[i].pere,arbre[i].enfant_G,arbre[i].enfant_D);
      }
    }
  }
}

/*---------------------------------------------------------------*/

/*
*FONCTION: afficheCode
*PARAMETRE: ne prend aucun paramètre
*RETURN: ne retourne racine
*fonction qui affiche le code binaire de chaque caractère
*/ 
void afficheCode(){


  /*!Cette fonction affiche le code binaire de chaque feuille */
  printf("\n");
  printf("<----------------------------------------------------------------->\n");
  printf("CODE BINAIRE\n");
  printf("<----------------------------------------------------------------->\n");
  for(int i=0;i<ASCII;i++){
    if(*(code+i)!=NULL){
      printf("Code binaire de %c(%i): %s\n",i,i,code[i]);
    }
  }
  printf("\n");
}

/*---------------------------------------------------------------*/

/*
*FONCTION: afficheLg
*PARAMETRE: float : la longueur moyenne
*RETURN: ne retourne rien 
*fonction qui affiche la longeur moyenne du codage
*/
void afficheLg(float lg){

  printf("<----------------------------------------------------------------->\n");
  printf("LONGUEUR MOYENNE\n");
  printf("<----------------------------------------------------------------->\n");
  printf("La longueur moyenne du codage est: %f",lg);
  printf("\n");
}

/*---------------------------------------------------------------*/

/*
*FONCTION: afficheTaille
*PARAMETRE: tableau de float contenant la taille originale et compressée et le gain 
*RETURN: ne retourne rien
*fonction qui affiche la taille original et compressée ainsi que le gain
*/
void afficheTaille(float* T){


  /*!Cette fonction prend un tableau de float où on a stocké la taille du fichier original, celle du fichier compressé avec et sans l'arbre ainsi que le gain dans les deux cas, donc elle prend un tableau de taille 5 .*/
  /*! Le tableau de float est le résultat de la fonction float* tailleEtGain(char*,char*,int*) */
  int TO=T[0];
  int TCAA=T[1];
  float TCSA=T[2];
  float GAA=T[3];
  float GSA=T[4];
  char a='%';

  printf("\n");
  printf("<----------------------------------------------------------------->\n");
  printf("TAILLE ET GAIN AVEC ARBRE\n");
  printf("<----------------------------------------------------------------->\n");
  printf("Taille fichier original : %i \n",TO);
  printf("Taille fichier compressé : %i \n",TCAA);
  printf("Gain : %f%c\n",GAA,a);
  printf("<----------------------------------------------------------------->\n");
  printf("TAILLE ET GAIN SANS ARBRE\n");
  printf("<----------------------------------------------------------------->\n");
  printf("Taille fichier original : %i \n",TO);
  printf("Taille fichier compressé : %f \n",TCSA);
  printf("Gain : %f%c\n",GSA,a);
  printf("\n");
}

/*---------------------------------------------------------------*/

/*
*FONCTION: lgmoyenne
*PARAMETRE: ne prend rien en paramètre
*RETURN: float 
*fonction qui calcule la longueur moyenne du codage
*/
float lgmoyenne(int *TabOccu){
  float length=0;
  int j=0;
  float total=0;
  /*!Cette fonction calcule la longueur moyenne du codage en aditionnant la probabilité multiplié par le nombre de bits du code de chaque chaque feuille */
  for(int i=0;i<ASCII;i++){
    if(TabOccu[i]>0){
      total+=TabOccu[i];
    }
  }

  for(int i=0;i<ASCII;i++){
    if(code[i]!=NULL){
      while (code[i][j]!='\0'){
        j++;
      }
      length+=(TabOccu[i]/total)*j;
      j=0;
    }
  }
  return length;
}

/*---------------------------------------------------------------*/

/*
*FONCTION: tailleEtgain
*PARAMETRE: un tableau d'entier contenant le nombre d'occurencede chaque caractère
*RETURN: tableau de float 
*fonction qui calcule la taille du fichier original et du fichier compresser en octet
*et le gain en pourcentage et les stocke dans un tableau 
*/ 
float* tailleEtgain(char* source,char* dest,int* Tab){

  /*!strcuture nécaissaire pour la fonction qui calcule la taille d'un fichier
   *\n struct stat st;
   */ 
  struct stat st;
  float *result=(float*)malloc(sizeof(float)*5);
  float tailleOrig;
  float tailleComprAvecArbre;
  float tailleComprSansArbre=0;


  //pour utiliser cette fonction il faut fire un #include <sys/stat.h>
  //et aussi créer une structure struct stat st;
  ///Calcule la taille du fichier source 
  stat(source, &st);
  tailleOrig = st.st_size;

  ///Calcule la taille du fichier compresser avec l'arbre 
  stat(dest,&st);
  tailleComprAvecArbre=st.st_size;

  ///Calcule la taille du fichier compresser sans l'arbre
  int j=0;
  for(int i=0;i<ASCII;i++){
    if(code[i]!=NULL && Tab[i]!=0){
      while(code[i][j]!='\0'){
        j++;
      }
      tailleComprSansArbre+=(Tab[i]*j);
      j=0;
    }
  }

  tailleComprSansArbre=tailleComprSansArbre/8;
  //Calculer le gain
  float gainAvecArbre;
  float gainSansArbre;
  ///Calcule le gain avec arbre 
  gainAvecArbre=((tailleOrig-tailleComprAvecArbre)*100)/tailleOrig;
  ///Calcule le gain sans arbre
  gainSansArbre=((tailleOrig-tailleComprSansArbre)*100)/tailleOrig;

  ///Stocke tout les résultat dans un tableau float
  result[0]=tailleOrig;
  result[1]=tailleComprAvecArbre;
  result[2]=tailleComprSansArbre;
  result[3]=gainAvecArbre;
  result[4]=gainSansArbre;

  return result;
}

/*---------------------------------------------------------------*/

/*
*FONCTION: Comptage
*PARAMETRE: Prend un fichier comme paramètre
*RETURN: Un tableau d'entier qui contient le nombre d'encurronce de chaque caractère
*fonction qui compte le nombre d'occurence de chaque caractère
*/
int* comptage(char* file){

  FILE* read=fopen(file,"r");
  int ascii;

  /*!Les indices du tableau qui vas contenir le nombre d'occurences de chaque caractère correspondent au code ASCII de chaque caractère*/
  /*!Allocation dynamique pour ne pas désalouer les valeurs à la sortie de la fonction*/
  int* nbOccu=(int*)malloc((ASCII) * sizeof(int));
  /*!Initialisation des valeurs du tableau à zero*/ 
  for(int i=0;i<ASCII;i++){//être sûre que les valeurs sont initialisées à O
    nbOccu[i]=0;
  }

  while((ascii=fgetc(read))!= EOF){
    nbOccu[ascii]++;
  }
  return nbOccu;
}

/*---------------------------------------------------------------*/

/*
*FONCTION: constructionArbre
*PARAMETRE: Prend un tableau d'entier
*RETURN: la racine de l'arbre
*fonction qui construit l'abre à partir d'un tableau d'entier contenant le nombre d'occurence de chaque  caractère
*/
int constructionArbre(int* nbOccu){

  /*!Initialisation à zéro pour les nombre d'occurence et à -1 pour pere,enfant_D et enfant_G pour touts les élements de l'arbre */
  for(int i=0;i<NOEUD;i++){
    arbre[i].nbOc=0;
    arbre[i].pere=-1;
    arbre[i].enfant_D=-1;
    arbre[i].enfant_G=-1;
    /*!Mettre le nombre d'occurence des feuilles */
    if(i<256){arbre[i].nbOc=nbOccu[i];}
  }

  int racine;
  int j;
  int nbChar=0;
  for(int i=0;i<ASCII;i++){
    if(arbre[i].nbOc!=0){
      nbChar++;
      j=i;
    }
  }

  /*!Dans le cas où le fichier à compresser contient qu'un seul type de caractère alors la fonction renvoie le code ASCII de ce caractère */
  if(nbChar==1){
    racine=j;
  }



  if(nbChar>1){
    int imin1,imin2;
    int nbocmin1,nbocmin2;
    /*!last représente le prochain noeud*/
    int last= 255;
    do{
      /*!Recherche des deux plus petits nombre d'occurence dans l'abre */
      imin1=-1;imin2=-1;
      nbocmin1=999999 ;nbocmin2=999999;
      for(int i=0; i<=last; i++){
        if(arbre[i].nbOc>0 && arbre[i].pere==-1 && arbre[i].nbOc<nbocmin1){
          nbocmin1=arbre[i].nbOc;
          imin1=i;
      }
    }

    for(int j=0;j<=last;j++){
      if(arbre[j].nbOc>0 && arbre[j].pere==-1 && arbre[j].nbOc<nbocmin2 && j!=imin1){
        nbocmin2=arbre[j].nbOc;
        imin2=j;
      }
    }
    /*!On incrémente d'abord last puis on met dans ce noeud la somme des deux noeuds au plus petits nombre d'occurence et on modifie l'indice de l'enfant gauche et l'enfant droit du noeud à l'indice last ainsi que le père des deux neoud appareillés*/
    if(imin1!=-1 && imin2!=-1){
      last++;
      arbre[last].nbOc=arbre[imin1].nbOc + arbre[imin2].nbOc;
      arbre[last].enfant_G=imin1;
      arbre[last].enfant_D=imin2;
      arbre[imin1].pere=last;
      arbre[imin2].pere=last;
    }
    
  }while(imin1!=-1 && imin2!=-1);
  ///On répète tant qu'on va trouver 2 noeuds à joindre 
  //Le dernier noeud n'aura pas de père ce sera la racine
  racine = last;
  }
  printf("racine %i\n",racine);
  return racine;
}

/*---------------------------------------------------------------*/

/*
*FONCTION: parcoursarbre
*PARAMETRE: un entier et une chaine de caractère vide
*RETURN: ne retourne rien
*fonction recursive qui parcours l'arbre en commençant par la racine
*attribut un 0 si on vas à gauche et attribut un 1 si on vas à droite et sauvegarde le résultat dans un
*tableau et une fois qu'on tombe sur une feuille on copie le tableau qui contient le code d'un
*caractère dans le tableau char* code[256]
*/
void parcoursarbre(int racine, char* codebin){
  ///On créer le tableau en local on en aura plus besoin par la suite.
  //En effet c'est codeBin qui va récupérer l'adresse
  char ncodeBin[strlen(codebin)+2];
  strcpy(ncodeBin,codebin) ; ///Recopie ncodeBin dans codeBin

  if(arbre[racine].enfant_G !=-1){
    ///On positionne les 0 à gauche et les 1 à droite
    ///On met un '0' dans ncodebin 
    ncodeBin[strlen(codebin)] = '0' ;
    ncodeBin[strlen(codebin)+1] = '\0' ;
    ///Et on rappelle la fonction avec l'indice de l'enfant gauche et ncodebin ainsi de suite  
    parcoursarbre(arbre[racine].enfant_G, ncodeBin);
    ///On met un '1' dans ncodebin 
    ncodeBin[strlen(codebin)] = '1' ; 
    // On ne met pas \0 car le 1 qu'on positionne a remplacé le précédent 0
    ///Et on rappelle la fonction avec l'indice de l'enfant droit et ncodebin ainsi de suite
    parcoursarbre(arbre[racine].enfant_D, ncodeBin);}
    //sterlen ne compte pas \0
  else{
    /*!Des qu'on tombe sur un noeud qui n'as pas d'enfant alors on est arriver à une feuille et on copie le contenue de nbcodebin dans le tableau char* code[256] à l'indice de la feuille */
    code[racine]=(char*)malloc((strlen(ncodeBin))*sizeof(char));
    strcpy(code[racine],ncodeBin);
  }
}

/*---------------------------------------------------------------*/

/*
*FONCTION: compression
*PARAMETRE: deux pointeurs sur char (fichier source,fichier destination)
*RETURN: ne retourne rien
*appelle comptage,constructionArbre et parcours arbre. Permet d'écrire le code
*adéquat dans le fichier destination
*/
void compression(char* source, char* destination){

  ///Positioner l'arbre en en-tête
  FILE* writeb=fopen(destination,"wb");
  fwrite(arbre,sizeof(noeud),NOEUD,writeb);
  fclose(writeb);

  FILE* read=fopen(source,"r");//on a besoin de lire le fichier source pour traduire chaque code lu
  FILE* write=fopen(destination,"a");//option écrire à la suite


  int ascii;
  int cpt=0;
  int nbrOctet=0;
  char octet='\0';
  int j=0;

  /*!On parcourt le fichier source en utilisant fgetc qui va lire les caractères un à un et qui vas les stocker dans la variable int ascii */
  while((ascii=fgetc(read))!=EOF){
    /*!On accede au code binaire correspondant au caractère lu. On s'arrête dés qu'on tombe sur '\0'  */
    while(code[ascii][j]!='\0'){
      /*!On modifie le flux binaire en utilisant l'opérateur binaire 'ou'*/
      octet= octet | (code[ascii][j] - '0');
      cpt++;
      /*!Si cpt est différent de 8 on décale à gauche*/
      if(cpt!=8){
        octet=octet<<1;
      }
      j++;
      /*!Sinon cela veut dire qu'un octet est rempli , on utilise donc fputc pour mettre cet octet dans le flux write, on remet le cpt à zero */
      if(cpt==8){
        fputc(octet, write);
        octet='\0';
        nbrOctet++;
        cpt=0;
      }
    }
    j=0;
  }
  while(cpt!=8){
    octet=octet | 0 ;
    cpt++;
    if(cpt!=8){octet=octet<<1;}
  }
  fputc(octet, write);
  fputc('\0',write);
  printf("Nombre d'octet: %i\n",nbrOctet);
  fclose(write);
  fclose(read);

}

/*---------------------------------------------------------------*/

/*
*FONCTION: compressionHuff
*PARAMETRE:deux pointeurs char, qui doivent être le fichier source et le fichier destination
*RETURN: ne retourne rien 
*fonction qui fait la compression en quatre étapes
*/
void compressionHuff(char* file_source, char* file_dest){

  FILE* read=fopen(file_source,"r");
  char s;
  if((s=fgetc(read))==EOF){
    fprintf(stderr,"ATTENTION! Le fichier cible est vide\n");
    exit(0);
  }
  fclose(read);


  ///ÉTAPE 1: Le comptage
  int* TabOccurence;
  TabOccurence=comptage(file_source);
  affiche(TabOccurence);

  ///ÉTAPE 2: La construction de l'arbre 
  int Racine;
  Racine=constructionArbre(TabOccurence);
  afficheArbre();

  ///ÉTAPE 3: Le parcours de l'arbre
  if(Racine<ASCII){
    code[Racine]=(char*)malloc(sizeof(char)*2);
    code[Racine][0]='1';
    code[Racine][1]='\0';
  }

  if(Racine>=ASCII){
    parcoursarbre(Racine,"");
  }
  afficheCode();

  ///Affichage de la longueur moyenne du codage 
  afficheLg(lgmoyenne(TabOccurence));

  ///ÉTAPE 4: La compression
  compression(file_source, file_dest);

  ///Affichage taille originale & compressée & gain de compression 
  afficheTaille(tailleEtgain(file_source,file_dest,TabOccurence));

}
