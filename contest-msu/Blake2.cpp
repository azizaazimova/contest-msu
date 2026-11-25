// Во входном файле задана ДНФ.Найти ДНФ, получающуюся из нее применением всех возможных операций поглощения(конец алгоритма Блейка).
//В выходном файле строки, соответствующие ЭК, должны быть упорядочены лексикографически.

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
void vivod(char** arr, int stolb, int strok, int con, char* vihod)
{
    FILE* fout = fopen(vihod, "w");
    if (fout)
    {
        fprintf(fout, "%d", stolb);
        fprintf(fout, " %d\n", con);
        for (int i = 0; i < strok; i++)
        {
            if (arr[i][0] != 'x')
            {
                for (int j = 0; j < stolb; j++)
                {
                    if (arr[i][j] == '2')
                    {
                        fprintf(fout, "*");
                    }
                    else fprintf(fout, "%c", arr[i][j]);
                }
                fprintf(fout, "\n");
            }
        }
        fclose(fout);
    }
}
void sort(char** arr, int alt, int con)
{
    char* tmp;
    int flag = 0;
    for (int i = 0; i < con; i++)
    {
        if (arr[i][0] == 'x') continue;
        for (int j = 0; j < con; j++)
        {
            if (i == j || arr[j][0] == 'x') continue;
            else if (i > j)
            {
                if (arr[i][0] > arr[j][0]) continue;
                for (int k = 0; k < alt; k++)
                {
                    if (arr[i][k] == arr[j][k]) continue;
                    if (arr[i][k] > arr[j][k]) break;
                    tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                    break;
                }
            }
            else
            {
                for (int k = 0; k < alt; k++)
                {
                    if (arr[i][k] == arr[j][k]) continue;
                    if (arr[i][k] < arr[j][k]) break;
                    tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                    break;
                }
            }
        }
    }
}
void freememory(char** arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(arr[i]);
    }
    free(arr);
}
void chistka(char** arr, int stolb, int strok, int* con)
{
    int count = strok;
    int flag = 0;
    for (int i = 0; i < strok; i++)
    {
        for (int j = i + 1; j < strok; j++)
        {
            for (int k = 0; k < stolb; k++)
            {
                if (arr[i][k] == arr[j][k]) continue;
                else
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0 && arr[j][0] != 'x')
            {
                arr[j][0] = 'x';
                count--;
            }
            else flag = 0;
        }
    }
    *con = count;
}
void absorb(char* arr1, char* arr2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr1[i] ^ arr2[i]) //отличаются попеременно 
        {
            arr1[i] = '2';
            arr2[i] = '2';
        }
    }
}
void absorb2(char* arr1, char* arr2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if ((arr2[i] == '2')) //отличаются наличием звездочки
        {
            arr1[i] = '2';
        }
    }
}
int dvoyka(char* arr1, int alt)
{
    for (int i = 0; i < alt; i++)
    {
        if (arr1[i] == '2') return i;
    }
    return -1;
}
char** chitayu(int* alt, int* con, char* vhod)
{
    FILE* fin = fopen(vhod, "r");
    if (fin)
    {
        if (fscanf(fin, "%d %d", alt, con) == 2)
        {
            int strok = *con;
            int stolb = *alt;
            char tmp;
            int j = 0;
            char** arr = (char**)malloc(sizeof(char*) * strok);
            if (arr)
            {
                for (int i = 0; i < strok; i++)
                {
                    arr[i] = (char*)malloc(sizeof(char) * stolb);
                    if (arr[i])
                    {
                        while (j < stolb && fscanf(fin, "%c", &tmp) == 1)
                        {
                            if (tmp == '1' || tmp == '0' || tmp == '*')
                            {
                                if (tmp == '*')
                                {
                                    arr[i][j] = '2';
                                }
                                else arr[i][j] = tmp;
                                j++;
                            }
                            continue;
                        }
                        j = 0;
                        continue;
                    }
                    else { freememory(arr, i - 1); fclose(fin); return NULL; }
                }
                fclose(fin);
                return arr;
            }
        }
        fclose(fin);
    }
    return NULL;
}
void bleik2(char** arr, int alt, int con)
{
    int gde = 0;
    int flag = 1;
    char* fix;
    for (int i = 0; i < con; i++)
    {
        fix = arr[i];
        gde = dvoyka(arr[i], alt);
        for (int j = 0; j < con; j++)
        {
            if (j == i) continue;
            //нет звездочек
            if (gde < 0)
            {
                if (dvoyka(arr[j], alt) > 0)
                {
                    for (int k = 0; k < alt; k++)
                    {
                        if (arr[j][k] == '2') continue;
                        if (arr[i][k] == arr[j][k]) continue;
                        flag = 0;
                    }
                    if (flag) absorb2(arr[i], arr[j], alt);
                    flag = 1;
                    continue;
                }
                else
                {
                    for (int k = 0; k < alt; k++)
                    {
                        if (arr[i][k] == arr[j][k]) continue;
                        flag--;
                    }
                    if (flag == 0)//отличаются на одну переменную
                    {
                        absorb(arr[i], arr[j], alt);
                    }
                    flag = 1;
                    continue;
                }
            }
            //есть звезда ищу звездочку на том же разряде в другом конъюнкте
            if (arr[j][gde] == '2')
            {
                for (int k = 0; k < alt; k++)
                {
                    if (arr[i][k] == arr[j][k]) continue;
                    flag--;
                }
                if (flag == 0)//отличаются на одну переменную
                {
                    absorb(arr[i], arr[j], alt);
                    flag = 1;
                    continue;
                }
                else //отличаются на несколько переменных
                {
                    flag = 1;
                    for (int k = 0; k < alt; k++)
                    {
                        if (arr[i][k] == arr[j][k]) continue;
                        if (arr[j][k] != 2) flag = 0; break;
                    }
                    if (flag) absorb2(arr[i], arr[j], alt);
                    flag = 1;
                    continue;
                }
            }
        }
    }
}
int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        int alt, con, con2;
        char** value = chitayu(&alt, &con, argv[1]);
        if (value)
        {
            bleik2(value, alt, con);
            chistka(value, alt, con, &con2);
            sort(value, alt, con);
            vivod(value, alt, con, con2, argv[2]);
            freememory(value, con);
        }
    }    
    return 0;
}