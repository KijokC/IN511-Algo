#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define path "exo4dat.txt"

void main()
{
    FILE* f = fopen( path, "r");
    if( !f )
    {
        printf("%s\n", strerror(errno));
        return;
    }

    int index = 0; // compteur de valeurs compris dans le fichier 
    float max = -99999.99; 
    float min = 99999.99;
    double sum = 0.0; // somme de toutes les valeurs lu
    float c; // stocke le caractère lu du fichier 

    for( int i = 0; fscanf(f, "%f", &c) != EOF; i++ )
    {
        sum += c;

        if( c < min )
            min = c;
        else if ( c > max )
            max = c;
            
        index++;
    }
    
    fclose(f);

    if( index != 2 ) // On ne peut pas diviser par 0 
        printf("Trimmed mean : %f\n", (sum-max-min)/(index-2)); // La valeur donné par RStudio est 79.875
}