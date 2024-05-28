#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functia pentru citirea fragmentului corect
void read_rules( char *str2 )
{
    char *str;
    FILE *fl = fopen("cod_rules.txt", "r");

    if(fl == NULL)
    {
        printf("Eroare la citire");
        exit(1);
    }

    while(fgets(str,100,fl))
        strcat(str2,str);

    fclose(fl);
}

// Functia pentru citirea fragmentului dat de utilizator
void read_frag( char *str1 )
{
    char *str;
    FILE *fl = fopen("frag.txt", "r");

    if(fl == NULL)
    {
        printf("Eroare la citire");
        exit(1);
    }

    while(fgets(str,100,fl))
        strcat(str1,str);

    fclose(fl);
}

// Functia de returnare a minimului din pozitiile alaturate
int min(int x, int y, int z)
{
    if (x < y && x < z)
        return x;
    else if (y < x && y < z)
        return y;
    else
        return z;
}

// Functia de gasire a minimului de operatii
int min_operatii(char *str1, char *str2)
{
    int n = strlen(str1);
    int m = strlen(str2);
    int dp[n + 1][m + 1];  // Matricea pentru gasirea greselilor

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {

            if (i == 0) // Adauga restul de caractere in cazul in care primul sir este gol
                dp[i][j] = j;
            else if (j == 0) // Sterge restul de caractere in cazul in care primul sir mai are
                dp[i][j] = i;
            else if (str1[i - 1] == str2[j - 1]) // Daca caracterele sunt identice trece mai departe
                dp[i][j] = dp[i - 1][j - 1];    // luand numarul minim de schimbari facute
            else{
                /*if(str1[i - 1] == str2[j] && str1[i] == str2[j - 1] && str1[i] != str2[i]) // Verifica daca caracterul se poate inlocui
                {                                                                         // cu un alt caracter
                    str1[i] = str2[j];
                }*/
                dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]);// Daca sunt diferite aduna 1
                                                                                // la cel mai mic numar de greseli gasite
            }
        }
    }
    return dp[n][m];
}

int main()
{
    char str1[100] = "\0"; // Initializarea vectorilor de caractere(string-urilor)
    char str2[100] = "\0";// cu '\0' pt curatarea acestora

    read_frag(str1);  // Citirea din fisiere
    read_rules(str2);// a fragmentelor

    printf("Numar minim de operatii: %d", min_operatii(str1, str2));

    return 0;
}

