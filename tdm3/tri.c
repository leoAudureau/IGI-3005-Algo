/* tri.c (IGI-3005)

  JCG 15/09/2008
  maj 07/12/2017
  DV  2024-11-22
  
  fonctions de tri
*/
#include <stdio.h>


/* utilitaires */

/* permutation de deux doubles */
void permute(double *x, double *y) {
    double tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}




int tri_echange(double t[], int n) {
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            /* si t[i] > t[j], i < j, échanger */
            if (t[i] > t[j]) {
                permute(&t[i], &t[j]);
            }
        }
    }
    return 0;
}

/********************************************
*                 TRI BULLE                 *
********************************************/


/*
  tri bulle de base : n-1 balayages 
  le balayage n°i ne compare que n-i couples 
*/
int tri_bulle_1(double t[], int n) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    for(int b = 0; b<n-1; b++){
      for(int i = 0; i<n-b-1; i++){
        if(t[i+1]<t[i]){
          permute(&t[i], &t[i + 1]);
          
        }
      }
    }
    return 0;
}


/*
  tri bulle optimise : n-1 balayages au maximum
  le balayage n°i ne compare que n-i couples 
  des que le tableau est trie, on termine le programme
*/
int tri_bulle_2(double t[], int n) {
    int fini = 0; // Faux par défaut (0 = Faux, 1 = Vrai)
    while (!fini) { // Tant que le tableau n'est pas trié
        fini = 1; // On suppose que le tableau est trié
        for (int i = 0; i < n - 1; i++) { // Parcourir les paires
            if (t[i + 1] < t[i]) { // Si la paire est mal triée
                permute(&t[i], &t[i + 1]); // Permuter les deux éléments
                fini = 0; // On a effectué un échange, donc le tableau n'est pas encore trié
            }
        }
        n--; // Réduire la taille de la partie non triée
    }
    return 0; // Indiquer que le tri est terminé
}





/********************************************
*               TRI SELECTION               *
********************************************/

int indicemax(double t[], int n) {
    int p = 0; // Initialiser avec le premier indice
    for (int i = 1; i < n; i++) { // Parcourir de 1 à n-1
        if (t[i] > t[p]) {
            p = i; // Mettre à jour l'indice de l'élément maximal
        }
    }
    return p; // Retourner l'indice de l'élément maximal
}



int tri_selection(double *v, int n) {
    while (n > 1) { // Tant qu'il reste plus d'un élément à trier
        int p = indicemax(v, n); // Trouver l'indice de l'élément maximal
        permute(&v[p], &v[n - 1]); // Placer cet élément à la fin
        n--; // Réduire la partie non triée
    }
    return 0; // Tri terminé avec succès
}






/********************************************
*               TRI INSERTION               *
********************************************/

/*
  trouve place dichotomique d'un double dans un tableau trie 
*/
/*
  Trouve la position d'insertion d'un double dans un tableau trié.
  Retourne l'indice où insérer x pour maintenir l'ordre du tableau.
*/
int trouve_place_dicho(double x, double t[], int n) {
    int gauche = 0;       // Bord inférieur
    int droite = n;       // Bord supérieur (hors tableau)
    int milieu;           // Milieu du tableau

    while (gauche < droite) {
        milieu = (gauche + droite) / 2; // Calcul de l'indice du milieu
        if (t[milieu] < x) {
            gauche = milieu + 1;       // x est dans la partie droite
        } else {
            droite = milieu;           // x est dans la partie gauche
        }
    }
    return gauche; // `gauche` donne la position d'insertion
}


/*
  Trouve la position d'insertion d'un double dans un tableau trié.
  Utilise une recherche séquentielle.
*/
int trouve_place_seq(double x, double t[], int n) {
    int pos = 0;

    // Parcourir le tableau jusqu'à trouver l'endroit où insérer
    while (pos < n && t[pos] < x) {
        pos++;
    }

    return pos; // Retourne l'indice où insérer x
}

/*
  decalage droite de p a q inclus
  [p..q] -> [p+1..q+1]
*/
void decaleD(double t[], int p, int q) {
    /* a ecrire */
    for(int i= q;i>=p; i--){
      t[i+1]=t[i];
    }
    return;
} 

/*
  tri par insertion (recherche sequentielle)
*/
int tri_insertion_seq(double t[], int n) {
    for (int i = 1; i < n; i++) {
        double x = t[i]; // Élément à insérer
        int j = i;

        // Décaler les éléments pour insérer `x` à sa position correcte
        while (j > 0 && t[j - 1] > x) {
            t[j] = t[j - 1];
            j--;
        }
        t[j] = x; // Insérer `x` à la position trouvée
    }
    return 0; // Tri terminé
}


/*
  tri par insertion (recherche dichotomique)
*/
int tri_insertion_dicho(double t[], int n) {
    for (int i = 1; i < n; i++) {
        double x = t[i]; // Élément à insérer
        int p = trouve_place_dicho(x, t, i); // Trouver la position d'insertion

        // Décaler les éléments pour faire de la place à `x`
        decaleD(t, p, i - 1);

        t[p] = x; // Insérer `x` à la position trouvée
    }
    return 0; // Tri terminé
}






/********************************************
*                 TRI SHELL                 *
********************************************/
int tri_shell(double t[], int n) {
    int ecart, sous_tableau, i, j;
    for (ecart = n / 2 ; ecart > 0 ; ecart /= 2)  /* comp. éléments distants de ecart*/
        for (sous_tableau = 0 ; sous_tableau < ecart ; ++sous_tableau ) /* il y 'ecart' sous-tableaux distants de 'ecart' */
            for (i = sous_tableau ; i + ecart < n  ; i += ecart)
                for (j = i ; j >= 0 && t[j] > t[j + ecart] ; j -= ecart)  
                    permute(&t[j], &t[j + ecart]);
    return 0;
}





/********************************************
*                 TRI RAPIDE                *
********************************************/

/*
  la partition vue en cours
*/
int partition(double t[], int d, int f) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return pos 
        (la frontiere entre petits et grands ) */
    return -1;
}


/*
  quicksort version de base
*/
int tri_rapide_1(double t[], int n) { 
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    return -1;
}


/*
  quick sort améliore si n<=6, on fait un shell sort 
*/
int tri_rapide_2(double t[], int n) { 
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    return -1;
} 





/********************************************
*                TRI PAR TAS                *
********************************************/

/*
  retablir un tas
  tous les arbres sous 'pere_a_retablir' sont des tas sauf peut etre 'pere_a_retablir'
 */
void retablir_tas(double t[], int n, int pere_a_retablir) {
    int pere = pere_a_retablir;
    int fils_le_plus_grand = 2 * pere + 1; /* le fils gauche */

    /* 
      On va comparer l'élément à la position 'pere' à ses fils, 
      si inférieur a un des fils, permuter avec le plus grand.
      Si on permute, il faut en plus verifier le nouveau fils "recursivement"
    */
    while (fils_le_plus_grand < n) {
        /* si le fils droit existe et est plus grand, c'est lui que l'on compare au pere */
        if (fils_le_plus_grand + 1 < n && t[fils_le_plus_grand + 1] >= t[fils_le_plus_grand]) {
            ++fils_le_plus_grand;
        }
        if (t[fils_le_plus_grand] > t[pere]) {
            permute(&t[fils_le_plus_grand], &t[pere]);
            /* Verifier position 'fils_le_plus_grand' */
            pere = fils_le_plus_grand;
            fils_le_plus_grand = 2*pere+1;
        }
        else { /* le pere est plus grand que ses fils  */
            break;
        }
    }
}

/*
  Convertit un tableau en un tas (en format tableau), en place
*/
void convertir_en_tas(double t[], int n) {
    /* 
      Appeler retablir_tas pour chaque indice de n-1 a 0
      Inutile de verifier les indices jusqu'à (n-1)/2,
      parce qu'ils ont pas de fils */
    for (int i=(n-1)/2; i>=0; i--)
        retablir_tas(t, n, i);
}

/*
  Extrait l'élément maximal et le place à la position n
*/
void extraire_max(double t[], int n) {
    /* L'élément maximal est à position 0, permute-le avec t[n] 
       À partir de ce point, on considère que la taille est n-1
    */
    permute(&t[n-1], &t[0]);
    /* On a probablement détruit la propriété du tas, 
       appeler retablir_tas pour la rétablir à la position changée */
    retablir_tas(t, n-1, 0);
}

int tri_tas(double t[], int n) {
    /* a ecrire, une fois ecrit modifiez le return -1 en return 0 */
    return -1;
}
