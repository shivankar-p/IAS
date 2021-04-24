#include <stdio.h>
#include <stdlib.h>

static int ac[40], mbr[40], mar[12], ibr[20], ir[8], pc;

int ins[2000] = {0}, data[2000] = {0};



void load()
{
    int x = 0;
    for(int i = 0; i < 12; i++)
    {
        x = x*2+mar[i];
    }


    for(int i = 0; i < 40; i++)
    {
        mbr[i] = data[x+i];
    }

    //mbr->ac
    for(int i = 0; i < 40; i++)
    {
        ac[i] = mbr[i];
    }


}

int main()
{
    //initialization
    //first location
    ins[7] = 1;
    ins[25] = 1; ins[27] = 1;
    ins[39] = 1;
    //second location
    ins[42] = 1;
    ins[47] = 1;
    ins[58] = 1;
    //data
    data[39] = 1; //a = 1
    data[78] = 1; // b = 2    storing in c
    
    //fetch cycle
    //pc->mar
    int tmp_pc = pc;
    for(int i = 11; i >= 0; i--)
    {
        mar[i] = tmp_pc%2;
        tmp_pc /= 2;
    }

    //mar->mem
    int adr = 0;
    for(int i = 0; i < 12; i++)
    {
        adr = adr*2+mar[i];
    }

    //mem->mbr
    for(int i = 0; i < 40; i++)
    {
        mbr[i] = ins[adr+i];
    }

    //mbr->ibr
    for(int i = 20; i < 40; i++)
    {
        ibr[i-20] = mbr[i];
    }

    //mbr->ir
    for(int i = 0; i < 8; i++)
    {
        ir[i] = mbr[i];
    }

    //mbr->mar
    for(int i = 8; i < 20; i++)
    {
        mar[i-8] = mbr[i];
    }
    //fetch cycle ends

    pc += 1;

    //decode cycle
    int op = 0;
    for(int i = 0; i < 8; i++)
    {
        op = op*2+ir[i];
    }
    switch(op)
    {
        case 1:
            load();

    }
    
    //debug
    for(int i = 0; i < 40; i++)
    {
        printf("%d ", ac[i]);
    }
    printf("\n");

    return 0;
}