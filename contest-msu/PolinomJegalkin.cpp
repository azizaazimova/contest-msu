
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int* chitayu(int* bi, int* alt, char* vhod)
{
    FILE* fin = fopen(vhod, "r"); 
    if (fin)
    {
        if (fscanf(fin, "%d %d", bi, alt) == 2)
        {
            int* arr = (int*)malloc(sizeof(int) * (pow(*bi, *alt)));
            if (arr)
            {
                int i = 0;
                char tmp;
                while(fscanf(fin, "%c", &tmp) == 1)
                {
                    if(tmp == '1' || tmp == '0')
                    {
                        arr[i] = ((int)tmp - 48);
                        i++;
                    }                    
                }
                fclose(fin);
                return arr;
            }
        }
        fclose(fin);
    }
    return NULL;
}
int* polinom(int size, int* value)
{
    int* koef = (int*)malloc(sizeof(int) * size);
    if (koef)
    {
        koef[0] = value[0];
        for (int i = 1; i < size; i++)
        {
            koef[i] = value[i] ^ koef[0];
            for (int j = i - 1; j > 0; j--)
            {
                if (((i & j) != 0) && ((i | j) == i))
                {
                        koef[i] ^= koef[j];                 
                }
            }
        }
        return koef;
    }
    return NULL;
}
void vivod(int* koef, int* value, int k, int q, char* vihod)
{
    FILE* fout = fopen(vihod, "w");
    if (fout)
    {
        int size = pow(k, q);
        fprintf(fout, "%d %d ", k, q);
        int count_slogaemix = 0;
        for (int i = 0; i < size; i++)
        {
            if (koef[i])
            {
                count_slogaemix++;
            }
        }
        fprintf(fout, "%d \n", count_slogaemix);
        for (int i = 0; i < size; i++)
        {
            if (koef[i])
            {
                for (int j = q; j > 0; j--)
                {
                    if (i & (1 << j - 1))
                    {
                        fprintf(fout, "1");
                    }
                    else fprintf(fout, "0");
                }
                fprintf(fout, " %d \n", koef[i]);
            }
        }
        fclose(fout);
    }
}
int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        int k, q;
        int* value = chitayu(&k, &q, argv[1]);
        if (value)
        {
            int size = pow(k, q);
            int* koef = polinom(size, value);
            if (koef)
            {
                vivod(koef, value, k, q, argv[2]);
                free(koef);
            }
            free(value);
        }
    }
    return 0;
}

