#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define path "exo5dat.txt"

// Construction de la matrice de distance entre individus
void mdi( char*** tab, int p, int n )
{
    //!\ La matrice est symétrique 
    float mdi[p][p];

    // Calcul des valeurs de la matrice 
    for( int i = 0; i < p; i++ )
    {
        for( int j = 0; j < i; j++ )
        {
            mdi[i][j] = 0.0;

            for( int k = 0; k < n; k++ )
                mdi[i][j] += ( strcmp(tab[i][k], tab[j][k]) != 0 );
            
            mdi[i][j] /= n;
        }
    }

    // Impression de la matrice dans un fichier "mdi.txt"
    FILE* w = fopen("mdi.txt", "w");

    for( int i = 0; i < p; i++ )
    {
        for( int j = 0; j < i; j++ )
        {
            fprintf(w, " %.1f  |", mdi[i][j]);
        }
        fprintf(w, " --- \n");
    }

    fclose(w);
}


// Construction de la matrice de distance entre variable
void mdv ( char*** tab, int p, int n )
{
    //!\ La matrice est symétrique 
    float mdv[n][n];

    // Calcul des valeurs de la matrice 
    for( int i = 0; i < n; i++ )
    {
        for( int j = 0; j < i; j++ )
        {
            mdv[i][j] = 0.0;

            for( int k = 0; k < p; k++ )
                mdv[i][j] += ( strcmp(tab[k][i], tab[k][j]) != 0 );
            
            mdv[i][j] /= p;
        }
    }

    // Impression de la matrice dans un fichier "mdv.txt"
    FILE* w = fopen("mdv.txt", "w");

    for( int i = 0; i < n; i++ )
    {
        for( int j = 0; j < i; j++ )
        {
            fprintf(w, " %f  |", mdv[i][j]);
        }
        fprintf(w, " -------- \n");
    }

    fclose(w);
}


void main()
{
    int p; // Tapez 54
    int n; // Tapez 5

    printf("\nNombre d'individus ?\n\n");
    scanf("%d", &p);

    printf("\nNombre de valeurs ?\n\n");
    scanf("%d", &n);
        
    int indexP = 0;
    int indexN = 0;

    char c = '\0';
    char* entry;

    FILE* f = fopen( path, "r");
    if( !f )
    {
        printf("%s\n", strerror(errno));
        return;
    }
    
    // Allocation à deux dimensions de chaînes de caractères
    char*** tab = malloc(sizeof(char**)*p);
    if( !***tab )
        return;

    for( int i = 0; i < p; i++ )
    {
        tab[i] = malloc(sizeof(char*)*n);
        if( !tab[i] )
            return;
    }

    // On ignore la première ligne où il y a le nom des colonnes 
    while( c != '\n' )
        fscanf(f, "%c", &c);

    char* nb = malloc(sizeof(char)*128); // On stocke la veleur courante lu dans cette variable 
    memset(nb, '\0', 128); // On met toutes les valeurs du tableau nb à '\0'

    // Lecture entière du fichier 
    for( int i = 0; fscanf(f, "%c", &c) != EOF; i++ )
    {
        if( c == '\n' )
        {
            // Copie de la valeur courante dans le tableau et réinitialisation de la valeur courante 
            tab[indexP][indexN-1] = malloc(sizeof(char)*(strlen(nb)+1));
            tab[indexP][indexN-1] = memcpy( tab[indexP][indexN-1], nb, strlen(nb)+1);
            memset(nb, '\0', 128);

            // Mises à jour appropriées des index
            i = -1;
            indexP++;
            indexN = 0;
        }
        else
        {
            if( c == ' ' ) // On adopte deux comportements quand on rencontre un espace 
            {
                if ( fscanf(f, "%c", &c) == EOF )
                    goto exit;

                if( c == ' ' ) // Si le caractère suivant est aussi un espace, alors la valeur courante est une valeur qui doit être copiée dans le tableau 
                {
                    while( c == ' ' )
                        fscanf(f, "%c", &c);
                    
                    // Si e nom de l'individu, qui ne doit pas être capturé, est dans la valeur courante 
                    // Alors on ne copie pas la valeur courante dans le tableau
                    // Le nom de l'individu est rencontré après un '\n' où indexN est égale à 0
                    // Par conséquent, la valeur courante à indexN doit être copiée à l'index indexN-1 dans le tableau 
                    if( indexN ) 
                    {   
                        tab[indexP][indexN-1] = malloc(sizeof(char)*(strlen(nb)+1));
                        tab[indexP][indexN-1] = memcpy( tab[indexP][indexN-1], nb, strlen(nb)+1);
                    }
                    
                    memset(nb, '\0', 128);
                    indexN++;
                    i = 0;
                    nb[i] = c;
                }
                else // Sinon, l'espace qu'on a rencontré est dans le nom d'un des individus 
                {
                    nb[i] = ' ';
                    i++;
                    nb[i] = c;
                }
            }
            else
            {
                nb[i] = c;
            }
        }
    }

    free(nb);

    exit : 
    
    // Impression du tableau dans le terminal 
    printf("\n");
    for( int i = 0; i < p; i++ )
    {
        for( int j = 0; j < n; j++ )
            printf("%3s | ", tab[i][j]);
        
        printf("\n");
    }
    printf("\n");

    fclose(f);

    mdi(tab, p, n);

    mdv(tab, p, n);

    // Libération de la mémoire 
    for( int i = 0; i < p; i++ )
    {
        for( int j = 0; j < n; j++ )
        {
            free(tab[i][j]);
        }
        free(tab[i]);
    }

    free(tab);
}