#include <stdio.h>
#include <stdlib.h>

static int ac[40], mbr[40], mar[12], ibr[20], ir[8], pc;

int ins[2000] = {0}, data[2000] = {0};

void add()
{
    //ac = ac+mbr add funcn
    int cin=0, cout = 0;
    for(int i = 39; i>=0; i--)
    {
        cout = (ac[i]+mbr[i]+cin)/2;                            
        ac[i] = (ac[i]+mbr[i]+cin)%2;
        cin = cout;         
    }
}

void loadfrmibr()
{
    //IBR->IR
    for(int i = 0; i < 8; i++)
    {
        ir[i] = ibr[i];
    }
    //ibr-mar
    for(int i = 8; i < 20; i++)
    {
        mar[i-8] = ibr[i];
    }
}

void fetch_data()
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
}

void store()
{
    int x = 0;
    for(int i = 0; i < 12; i++)
    {
        x = x*2+mar[i];
    }
    //ac->mbr
    for(int i = 0; i < 40; i++)
    {
        mbr[i] = ac[i];
    }
    //mbr -> memory
    for(int i = 0; i < 40; i++)
    {
        data[x+i] = mbr[i];
    }

}

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

void fetch_ins(int prog_c)
{
    
    pc = prog_c;
    //fetch cycle
    //pc->mar
    int tmp_pc = 40*pc;
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
    int i;
    for(i = 0; i < 8; i++)
    {
        if(mbr[i]!=0) break;
    }

    if(i != 8)
    {
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
    }
    else
    {
        //mbr->ir
        for(int i = 0; i < 8; i++)
        {
            ir[i] = mbr[20+i];
        }

        //mbr->mar
        for(int i = 0; i < 12; i++)
        {
            mar[i] = mbr[28+i];
        }
    }
    pc += 1;
    //fetch cycle ends
}

void decode()
{
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
            break;
        case 5:
            add();
            break;
        case 33:
            store();
            break;

    }
}

int main()
{
    //initialization
    //first location
    ins[7] = 1;
    ins[25] = 1; ins[27] = 1;
    ins[34] = 1;
    ins[36] = 1;
    //second location
    ins[62] = 1;
    ins[67] = 1;
    ins[73] = 1;
    ins[75] = 1;
    //data
    data[39] = 1; //a = 7
    data[38] = 1;
    data[37] = 1;
    data[79] = 1; // b = 7    storing in c
    data[78] = 1;
    data[77] = 1;

    fetch_ins(pc);
    decode();
    loadfrmibr();
    fetch_data();
    decode();
    fetch_ins(pc);
    decode();
    
    //debug
    for(int i=0; i < 40; i++)
    {
        printf("%d ", data[80+i]);
    }

    return 0;
}