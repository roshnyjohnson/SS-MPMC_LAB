#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
        char label[20],opcode[20],operand[20];
        int startadd=0,locctr=0;
        FILE *f1,*f2,*f3,*f4;
        f1=fopen("iput.txt","r");
        f2=fopen("symtab.txt","w");
        f3=fopen("intermediate.txt","w");
        f4=fopen("length.txt","w");


        fscanf(f1,"%s%s%s",label,opcode,operand);
        if(strcmp(opcode,"START")==0)
        {
                startadd=strtol(operand,NULL,16);
                locctr=startadd;
                fprintf(f3,"%s\t%s\t%s\n",label,opcode,operand);
                fscanf(f1,"%s%s%s",label,opcode,operand);
        }
        else
                locctr=0;

        while(strcmp(opcode,"END")!=0)
        {
                fprintf(f3,"%X\t",locctr);
                if(strcmp(label,"-")!=0)
                {
                        fprintf(f2,"%s\t%X\n",label,locctr);
                }
                if(strcmp(opcode,"WORD")==0)
                {
                        locctr+=3;
                }
                else if(strcmp(opcode,"RESW")==0)
                {
                        locctr+=3*atoi(operand);
                }
                else if(strcmp(opcode,"RESB")==0)
                {
                        locctr+=atoi(operand);
                }
                else if(strcmp(opcode,"BYTE")==0)
                {
                        if(operand[0]=='C')
                        locctr+=strlen(operand)-3;
                        else if(operand[0]=='X')
                        {
                        locctr+=(strlen(operand)-3+1)/2;
                        }

                }
                else
                        locctr+=3;
                fprintf(f3,"%s\t%s\t%s\n",label,opcode,operand);
                fscanf(f1,"%s%s%s",label,opcode,operand);
        }
        fprintf(f3,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        fprintf(f4,"%04X",locctr-startadd);

        fclose(f1);
        fclose(f2);
        fclose(f3);
        fclose(f4);
}
