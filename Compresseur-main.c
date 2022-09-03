/*!
 *\file Compresseur-main.c
 *\brief Fichier de la fonction principal, inclus le fichier Compresseur.h, le main exécute la fonction compressionHuff(char*,char*)
 *\author Yanis Bouallouche ; Ophélia Benin 
 *
 *Cette partie concerne le compresseur
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Compresseur.h"

/*!
 *\n FONCTION main
 *\brief Vérifie d'abord si le nombre d'arguments entrés en paramètre est égale à deux, sion elle renvoie un message d'erreur. Si la condition est remplie alors la fonction main appelle la fonction compressionHuff qui vas s'occuper de la compression
 */ 
int main(int argc, char** argv){

  if(argc!=3){
    printf("Utilisation du programme Huffman\n");
    printf("Requiert deux fichiers entrés en paramètre");
    exit(1);
  }

  compressionHuff(argv[1], argv[2]);
  
  return 0;
}
