/*!
 *\file Decompresseur.c
 *\brief Code source du décompresseur
 *\author Yanis Bouallouche ; Ophélia Bénin 
 *
 *Cette partie concerne le decompresseur
 */


#include <stdio.h>
#include <stdlib.h>


///Une nouvelle strcuture noeud 
typedef struct noeud{int nbOcc,pere, enfantG, enfantD ; }noeud;
/// Un tableau de noeud où on vas stocker l'arbre qui se trouve dans le fichier à décompresser
noeud arbre[511];


/*!
 *\n FONCTION decompression 
 *\param[in] char* Un pointeur vers un char qui doit être le fichier compresser
 *\return void ne retourne rien 
 *\brief Cette fonction décompresse le fichier compresser et renvoie le résultat vers la sortie standard et égaleent dans un fichier unzip
 */
void decompression(char* fichier){

  ///On recupère l'arbre dans le fichier compresser puis on la mets dans le tableau arbre 
  FILE* read = fopen(fichier,"rb");
  fread(arbre, sizeof(noeud),511,read);


  
  int racine = 511 ;
  while(arbre[racine].nbOcc==0){
    racine -- ;
  }
  int nc = racine ;
  
  FILE* write = fopen("unzip","a"); 
  char octet ;
  int cpt = 0 ;//compte char
  int cpt2 = 0 ;//compte bits de l'octet
  
  while(cpt<arbre[racine].nbOcc){
    /*!On utilise fgetc pour lire le fichier en mode binaire*/
    octet=fgetc(read);
    while(cpt<arbre[racine].nbOcc && cpt2<8){
      /*!Si le caractère lu est plus grand que 0(vu que les octet sont lu en complément à 2) donc on par vers la gauche*/
      if(octet>=0 && arbre[nc].enfantG!=-1){
	nc = arbre[nc].enfantG;
	octet = octet<<1;
	cpt2++;
      }
      /*!Si le caractère lu est plus petit que 0(vu que les octet sont lu en complément à 2) donc on par vers droite*/
      else if(octet<0 && arbre[nc].enfantD!=-1){
	nc = arbre[nc].enfantD;
	octet = octet<<1;
	cpt2++;
      }
      if(arbre[nc].enfantD==-1){
	fputc(nc,write);
	fputc(nc,stdout);
	nc = racine ;
	cpt++;
      }     
    }
    cpt2 = 0 ;
  }
  fclose(write);
  fclose(read);
}


/*!
 *\n FONCTION main 
 *\brief Cette fonction verifie d'abord si le nombre de paramètre entrés est égale à 1. Si le fichier à décompresser est vide renvoie un message d'erreur, sinon si ces conditions sont remplies alors elle appelle la fonction décompression, qui vas décompresser le fichier
 */

int main(int argc, char** argv){
  if(argc!=2){
    fprintf(stderr,"Erreur %s \nSaisir un unique fichier à décompresser.\n",argv[0]);
    exit(1);
  }
  
  FILE* read=fopen(argv[1],"r");
  char s;
  if((s=fgetc(read))==EOF){
    fprintf(stderr,"ATTENTION! Le fichier cible est vide\n");
    exit(1);
    fclose(read);
  }
    
    else{
    decompression(argv[1]);
  }
  return 0 ;
}
