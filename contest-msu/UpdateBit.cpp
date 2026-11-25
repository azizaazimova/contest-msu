//zapis
#include <stdio.h>
#include <stdlib.h>
unsigned long long int chitayu(unsigned long long int* d, unsigned long long int* p, int* b, char* vhod)
{
    FILE* fin = fopen(vhod, "r");
    if (fin && fscanf(fin, "%llu", d) && *d > 0)
    {
        if (fscanf(fin, "%llu", p) && *p >= 0)
        {
            if (fscanf(fin, "%d", b))
            {
                if (*b == 1 || *b == 0)
                {
                    fclose(fin);
                    return *d;
                }
            }
        }
        fclose(fin);
    }
    return 0;
}
unsigned long long int zapis(unsigned long long int d, unsigned long long int p, int b)
{
    int num = 0;
    unsigned long long int one = 1;
    if (d & (one << p))
    {
        num = 1;
    }
    if (num == b)
    {
        return d;
    }
    else
    {
        unsigned long long int d2 = d ^ (one << p);
        return d2;
    }

}
void vivod(unsigned long long int d, char* vihod)
{
    FILE* fout = fopen(vihod, "w");
    if (fout)
    {
        fprintf(fout, "%llu", d);
        fclose(fout);
    }
}
int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        unsigned long long int chislo;
        unsigned long long int chislo2 = 0;
        unsigned long long int position;
        int b;
        unsigned long long int a = chitayu(&chislo, &position, &b, argv[1]);
        if(a!=0) chislo2 = zapis(a, position, b);        
        vivod(chislo2, argv[2]);
    }
    return 0;
}
