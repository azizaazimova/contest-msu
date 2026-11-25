#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
void vivod(int** pari, int q, int n, char* vihod)
{
    int otvet = -1;
    FILE* fout = fopen(vihod, "w");
    if (fout)
    {
        for (int i = 0; i < q - 1; i++)
        {
            for (int j = i + 1; j < q; j++)
            {
                if (i != j && pari[j - 1][i] != 1)
                {
                    for (int k = 0; k < n; k++)
                    {
                        if (i & (1 << (n - k - 1)))
                        {
                            fprintf(fout, "1");
                        }
                        else fprintf(fout, "0");
                    }
                    fprintf(fout, " ");
                    for (int k = 0; k < n; k++)
                    {
                        if (j & (1 << (n - k - 1)))
                        {
                            fprintf(fout, "1");
                        }
                        else fprintf(fout, "0");
                    }
                    fprintf(fout, " ");
                    otvet++;
                }
                else { continue; }
            }
        }
        if (otvet < 0)
        {
            fprintf(fout, "%d", otvet);
        }
        fclose(fout);
    }
}
int chislo(int** arr1, int n, int i)
{
    int number = 0;
    for (int j = 0; j < n; j++)
    {
        if (arr1[n - j - 1][i])
        {
            number += 1 << j;
        }
    }
    return number;
}
int solver(int i, int j, int** arr1, int** arr2)
{
    int nexti = 0;
    int nextj = 0;    
    int tmp = 0;
    for (int in = 0; in < 2; in++)
    {
        if (arr1[(i * 2) + in][1] != arr1[(j * 2) + in][1])
        {
            arr2[j - 1][i] = 1;
            return 1;
        }
        nexti = arr1[(i * 2) + in][0];
        nextj = arr1[(j * 2) + in][0];
        if (nextj < nexti)
        {
            tmp = nextj; 
            nextj = nexti;
            nexti = tmp;
        }
        if ((nexti != nextj) && (arr2[nextj - 1][nexti] == 1))
        {
            arr2[j - 1][i] = 1;
            return 1;
        }
    }
    return 0;
}
void freememory(int** arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(arr[i]);
    }
    free(arr);
}
int** chitayu(int* q, char* vhod)
{
    FILE* fin = fopen(vhod, "r");
    int n = 0;
    int count = 0;
    char musor = '0';
    if (fin)
    {
        if (fscanf(fin, "%d", &n) == 1)
        {
            *q = n;
            while (fscanf(fin, "%c", &musor) == 1 && count < n)
            {
                if (musor == '1' || musor == '0')
                {
                    count++;
                }
            }
            count = 0;
            int vektor = 1 << (n + 1);
            int** arr1 = (int**)malloc(sizeof(int*) * (n + 1));
            if (arr1) 
            {
                for (int i = 0; i < n + 1; i++)
                {
                    arr1[i] = (int*)malloc(sizeof(int) * vektor);
                    if (arr1[i])
                    {
                        while (fscanf(fin, "%c", &musor) == 1 && count < 2)
                        {
                            if (int(musor) >= 48)
                            {
                                count++;
                            }
                        }
                        count = 0;
                        while (fscanf(fin, "%c", &musor) == 1 && count < vektor)
                        {
                            if (musor == '1' || musor == '0')
                            {
                                arr1[i][count] = (int(musor)) - 48;
                                count++;
                            }
                        }
                        count = 0;
                        continue;
                    }
                    else { freememory(arr1, i - 1); fclose(fin); return NULL; }
                }
                int** arr2 = (int**)malloc(sizeof(int*) * vektor);
                if (arr2)
                {
                    for (int i = 0; i < vektor; i++)
                    {
                        arr2[i] = (int*)malloc(sizeof(int) * 2);
                        if (arr2[i])
                        {
                            arr2[i][0] = chislo(arr1, n, i);
                            arr2[i][1] = arr1[n][i];
                        }
                        else { freememory(arr2, i - 1); fclose(fin); return NULL; }
                    }                    
                }
                freememory(arr1, n + 1);
                fclose(fin);
                return arr2;
            }
        }
        fclose(fin);
    }
    return NULL;
}
void chekayu(int n, int q, int** arr1, int** arr2)
{
    int flag = 0;
    while (1)
    {
        for (int i = 0; i < q - 1; i++)
        {
            for (int j = i + 1; j < q; j++)
            {
                if (arr2[j - 1][i] != 1)
                {
                    flag += solver(i, j, arr1, arr2);
                }               
            }
        }
        if (flag)
        {
            flag = 0; continue;
        }
        else break;
    }
}
int main(int argc, char* argv[])
{    
    if (argc == 3)
    {
        int n;
        int** table = chitayu(&n, argv[1]);
        if (table)
        {
            int q = 1 << n;
            int** pari = (int**)malloc(sizeof(int*) * q - 1);
            if (pari)
            {
                for (int i = 0; i < q - 1; i++)
                {
                    pari[i] = (int*)calloc(i + 1, sizeof(int));
                    if (pari[i])
                    {
                        continue;
                    }
                    else { freememory(pari, i - 1); }
                }
                chekayu(n, q, table, pari);
                vivod(pari, q, n, argv[2]);
                freememory(pari, q - 1);
            }
            freememory(table, 1 << (n + 1));
        }
    }
    return 0;
}