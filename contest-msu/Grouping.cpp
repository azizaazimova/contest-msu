#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
double* chitayu(int* size, char* vhod)
{
    FILE* fin = fopen(vhod, "r");
    double* arr = NULL;
    if (fin)
    {
        if (fscanf(fin, "%d", size) && *size > 0)
        {
            int lsize = *size;
            arr = (double*)malloc(sizeof(double) * lsize);
            if (arr)
            {
                int i = 0;
                while (i < lsize)
                {
                    if (fscanf(fin, "%lf", &arr[i]) != 1)
                    {
                        if ((lsize >= 1) && (i == 0))
                        {
                            *size = 0;
                            free(arr);
                            return NULL;
                        }
                        break;
                    }
                    else i++;
                }
                if (i < lsize)
                {
                    double* temp = (double*)realloc(arr, sizeof(double) * i);
                    if (temp)
                    {
                        arr = temp;
                        temp = NULL;
                        *size = i;
                    }
                    else
                    {
                        *size = 0; //тогда в выводе он перестанет обращаться к пустому массиву
                        free(arr);
                        fclose(fin);
                        return NULL;
                    }
                }
                fclose(fin);
                return arr;
            }
        }
        fclose(fin);
    }
    *size = 0;
    return NULL;
}
void peredelka(double* arr, int size)
{
    if (arr)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] >= 0)
            {
                int j = i;
                while (j > 0 && (arr[j - 1] < 0))
                {
                    double tmp = arr[j - 1];
                    arr[j - 1] = arr[j];
                    arr[j] = tmp;
                    j--;
                }
            }
        }
    }
}
void vivod(double* arr, int size, char* vihod)
{
    FILE* fout = fopen(vihod, "w");
    if (fout)
    {
        if (size > 0)
        {
            fprintf(fout, "%d ", size);
            for (int i = 0; i < size; i++)
            {
                fprintf(fout, "%lf ", arr[i]);
            }
        }
        else fprintf(fout, "0");
        fclose(fout);
    }
}
int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        int razmer;
        double* arr = chitayu(&razmer, argv[1]);
        peredelka(arr, razmer);
        vivod(arr, razmer, argv[2]);
        if (arr) free(arr);
    }
    return 0;
}