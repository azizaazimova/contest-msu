//поиск 11                                                                                                                                                                                                                                                                                             #include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
double* chitayu(int* size, double* x, int* flag, char* vhod)
{
    FILE* fin = fopen(vhod, "r");
    double* arr = NULL;
    if (fin)
    {
        if (fscanf(fin, "%lf", x) > 0)
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
                                fclose(fin); //teper zakrivayet
                                return NULL;
                            }
                            break;
                        }
                        else i++;
                    }
                    if (i < lsize && i!=0)//mne kajetsa nolik i ne zashel bi v realok, v 29 stroke  ya zakanchivayu funksiyu
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
                            free(arr);
                            fclose(fin);
                            return NULL;
                        }
                    }
                    fclose(fin);
                    return arr;
                }
            }
        }
        else *flag = 0;
        fclose(fin);
    }   
    *size = 0;
    return NULL;
}
int vstavka(double* arr, int size, double x, int flag)
{
    if (arr)
    {
        int lev = 0, prav = size - 1;
        int mid = 0;
        while (lev < prav)
        {
            mid = (lev + prav) / 2;
            if (arr[mid] < x && arr[mid + 1] >= x)
            {
                return mid + 2;
            }
            if (arr[mid] >= x)
            {
                prav = mid;
            }
            else
            {
                lev = mid + 1;
                if (mid == size - 2)
                {
                    return lev + 2;
                }
            }
        }
        if (size == 1 && arr[lev] < x)
        {
            return lev + 2;
        }
        return lev + 1;
    }
    if (flag == 0) //пустой файл
    {
        return 0;
    }
    return 1;
}
void vivod(int n, char* vihod)
{
    FILE* fout = fopen(vihod, "w");
    if (fout)
    {
        fprintf(fout, "%d", n);
        fclose(fout);
    }
}
int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        int razmer, position, flag = 1; double x;
        double* arr = chitayu(&razmer, &x, &flag, argv[1]);
        position = vstavka(arr, razmer, x, flag);
        vivod(position, argv[2]);
        if (arr) free(arr);
    }
    return 0;
}