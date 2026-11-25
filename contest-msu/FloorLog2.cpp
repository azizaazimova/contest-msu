//starshina
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
unsigned long long int chitayu(unsigned long long int* d, char* vhod)
{
    FILE* fin = fopen(vhod, "r");
    if (fin && fscanf(fin, "%llu", d))
    {
        fclose(fin);
        return *d;
    }
    return 0;
}
int starshina(unsigned long long int d)
{
    int position = 0;
    for (int i = 0; d != 0; i++)
    {
        d >>= 1; 
        position++;
    }
    return position-1;
}
void vivod(int p, char* vihod)
{
    FILE* fout = fopen(vihod, "w");
    if (fout)
    {
        fprintf(fout, "%d", p);
        fclose(fout);
    }
}
int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        unsigned long long int chislo = chitayu(&chislo, argv[1]);
        int position = starshina(chislo);
        vivod(position, argv[2]);
    }
    return 0;
}
