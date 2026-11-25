#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
double* chitayu(int* size, char* vhod)
{
    FILE* fin = fopen(vhod, "r");
    double* arr = NULL;
    if (fin)
    {
        if (fscanf(fin, "%d", size) > 0 && *size > 0)
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
                        *size = 0;
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
double* novmasiv(int size, double* arr)
{
    if (arr)
    {
        double* newarr = (double*)malloc(sizeof(double) * size); // пустой массив
        if (newarr)
        {
            newarr[0] = arr[0];
            if (size > 1)
            {
                int p = 0;
                int j = 0;
                for (int i = 1; i < size; i++)
                {
                    for (j = 0; j < i; j++) //тут сравниваю элемент с первым, вторым,... элементом нового массива
                    {
                        if (arr[i] < newarr[j])
                        {
                            p = j;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                    if (j == i)
                    {
                        newarr[j] = arr[i];
                    }
                    else
                    {
                        double temp = arr[i];
                        for (int k = i; k > p; k--)
                        {
                            newarr[k] = newarr[k - 1];
                        }
                        newarr[j] = temp;
                    }
                }
            }
            return newarr;
        }          
    }
    return NULL;
}
void vivod(double* newarr, int size, char * vihod)
{
    FILE* fout = fopen(vihod, "w");
    if(fout)
    {
        if (size > 0 && newarr!= NULL) //выделился ли массив
        {
            fprintf(fout, "%d ", size);
            for (int i = 0; i < size; i++)
            {
                fprintf(fout, "%lf ", newarr[i]);
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
        double* newarr = novmasiv(razmer, arr);
        vivod(newarr, razmer, argv[2]);
        if (arr) free(arr);
        if (newarr) free(newarr);
    }  
    return 0;
}