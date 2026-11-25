#include <stdio.h>
#include <stdlib.h>
unsigned long long int chitayu(unsigned long long int* a, char* vhod)
{
    FILE* fin = fopen(vhod, "r");
    if (fin)
    {
        if (fscanf(fin, "%llu", a) > 0 && *a > 0) //v skanfe &*a = a;
        {
            fclose(fin);
            return *a;
        }
        fclose(fin); //teper tochno zakrivayet 
    }
    return 0;
}
void vivod(unsigned long long int a, char* vihod)
{
    FILE* fout = fopen(vihod, "w");
    if (fout)
    {
        if (a)
        {
            unsigned long long int k = a;
            unsigned long long one = 1;
            for (int i = 0; i < (one << a); i++)
            {
                k = a;
                while (k > 0)
                {
                    if (i & (one << (k - 1)))
                    {
                        fprintf(fout, "%llu ", k);
                        k--;
                        continue;
                    }
                    fprintf(fout, "0 ");
                    k--;
                }
                fprintf(fout, "\n");
            }
        }
        else fprintf(fout, "0");
        fclose(fout);//zakrila
    }
}
int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        unsigned long long int a = chitayu(&a, argv[1]);
        vivod(a, argv[2]);
    }
    return 0;
}