/*!
 * \file Compresseur.h
 * \brief Fichier d'en tête pour le compresseur contenant la signature de toutes les fonctions ainsi que la déclaration d'une structure 
 *\author Yanis Bouallouche ; Ophélia Benin 
 *
 *Cette partie concerne le compresseur
 */


#ifndef __COMPRES__H
#define __COMPRES__H
#include<stdlib.h>
#include<stdio.h>

///ASCII correspond au nombre maximal de caractère différent
#define ASCII 256

///NOEUD correspond au plus grand nombre de noeud possible 
#define NOEUD 511


/*---------------------------------------------------------------*/
/*!
 *\n FONCTION affiche
 *\param[in] int*  Un tableau d'entier contenant le nombre d'occurence de chaque caractère
 *\return Ne retourne rien
 *\brief Fonction qui affiche le nombre d'occurence de chaque caractère et sa probabilité
 */
void affiche(int*);

/*---------------------------------------------------------------*/

/*!
 *\n FONCTION: afficheArbre
 *\param[in] void ne prend aucun paramètre
 *\return ne retourne rien
 *\brief fonction qui affiche les noeud de l'arbre
*/ 
void afficheArbre();

/*---------------------------------------------------------------*/

/*!
 *\n FONCTION: afficheCode
 *\param[in] void ne prend aucun paramètre 
 *\return  ne retourne rien
 *\brief Fonction qui affiche le code binaire de chaque caractère
*/ 
void afficheCode();

/*---------------------------------------------------------------*/

/*!
 *\n FONCTION: afficheLg
 *\param[in] float la longueur moyenne
 *\retur ne retourne rien 
 *\brief Fonction qui affiche la longeur moyenne du codage
*/
void afficheLg(float);

/*---------------------------------------------------------------*/

/*!
 *\n FONCTION: afficheTaille
 *\param[in] float* tableau de float contenant la taille original, la taille compresser sans et avec l'abre et le gain de la compression pour les deux cas
 *\return ne retourne rien
 *\brief Fonction qui affiche la taille original, la taille compresser sans et avec l'arbre et le gain de la compression pour les deux cas
*/
void afficheTaille(float*);

/*---------------------------------------------------------------*/

/*!
 *\n FONCTION: lgmoyenne
 *\param[in] int* Un tableau d'entier contenant le nombre d'occurence de chaque caractère
 *\return  float ;  La longueur moyenne du codage  
 *\brief Fonction qui calcule la longueur moyenne du codage
*/
float lgmoyenne(int*);

/*---------------------------------------------------------------*/

/*!
 *\n FONCTION: tailleEtgain
 *\param[in] char* un pointeur vers un char qui représente le fichier source 
 *\param[in] char* un pointeur vers un char qui représente le fichier destinataire
 *\param[in] int* un tableau d'entier contenant le nombre d'occurence de chaque caractère  
 *\return  float ; tableau de float contenant la taille original, la taille compresser sans et avec l'arbre et le gain de la compression pour les deux cas
 *\brief Fonction qui calcule la taille original, la taille compresser sans et avec l'arbre et le gain en pourcentage de la compression pour les deux cas en octetet et les stocke dans un tableau 
*/ 
float* tailleEtgain(char* ,char*,int* );

/*---------------------------------------------------------------*/

///Tableau de chaine de caractère qui vas contenir le code binaire de chaque caractère
char *code[ASCII];


/*---------------------------------------------------------------*/


///Structeur noeud: composer du nombre d'occurence, d'un pere, d'un enfant droit et d'un enfant gauche
typedef struct noeud{int nbOc, pere,enfant_G, enfant_D;}noeud;

///Tableau de noeud pouvant avoir jusqu'à 511 noeud, ce tableau représentera l'arbre de huffman.
noeud arbre[NOEUD];



/*---------------------------------------------------------------*/

/*!
 *\n FONCTION: Comptage
 *\param[in] char* Prend un fichier(le fichier source) comme paramètre
 *\return int* ;  Un tableau d'entier qui contient le nombre d'encurronce de chaque caractère
 *\brief fonction qui compte le nombre d'occurence de chaque caractère
*/
int* comptage(char*);

/*---------------------------------------------------------------*/

/*!
 *\n FONCTION: constructionArbre
 *\param[in] int* Prend un tableau d'entier contenant le nombre d'occurence de chaque caractère 
 *\return int ; la racine de l'arbre
 *\brief Fonction qui construit l'abre à partir d'un tableau d'entier contenant le nombre d'occurence de chaque  caractère et renvoie la racine 
*/
int constructionArbre(int *);

/*---------------------------------------------------------------*/

/*!
 *\n FONCTION: parcoursarbre
 *\param[in] int un entier qui représente la racine de l'arbre
 *\param[in] char* une chaine de caractère vide
 *\return void ne retourne rien
 *\brief Fonction recursive qui parcours l'abre en commençant par la racine
 *\ Attribut un 0 si on vas à gauche et attribut un 1 si on vas à droite et sauvegarde le résultat dans une chaîne de caractère et une fois qu'on tombe sur une feuille on copie le tableau qui contient le code d'un caractère dans le tableau char* code[256]
*/
void parcoursarbre(int, char*);

/*---------------------------------------------------------------*/

/*!
 *\n FONCTION: compression
 *\param[in] char* un pointeur char, qui doit être le fichier source 
 *\param[in] char* un pointeur char, qui doit être le fichier destinataire 
 *\return void ne retourne rien
 *\brief Fonction qui appelle les trois fonction comptage,constructionArbre et parcours arbre, et qui modifie le flux binaire du fichier destination
*/
void compression(char*, char*);

/*---------------------------------------------------------------*/

/*!
 *\n FONCTION: compressionHuff
 *\param[in] char* un pointeur char, qui doit être le fichier source
 *\param[in] char* un pointeur char, qui doit être le fichier destinataire   
 *\return void ne retourne rien 
 *\brief Fonction qui fait la compression en quatre étapes et qui appelle toutes les précédente fonction 
*/
void compressionHuff(char*, char*);

#endif
