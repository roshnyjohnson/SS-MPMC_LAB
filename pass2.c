#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  MAXBUFF 1024
int main()
{
        int i,tlen=0;
        char l1[100],address[100],label[100],opcode[100],operand[100],start[100];
        char code[100],mne[100],sym[100],add[100],text_start[100];
        char objcode[MAXBUFF]="";

        FILE *f1,*f2,*f3,*f4,*f5,*f6;
        f1=fopen("intermediate.txt","r");
        f2=fopen("length.txt","r");
        f3=fopen("symtab.txt","r");
        f4=fopen("optab.txt","r");
        f5=fopen("assembly.txt","w");
        f6=fopen("obj.txt","w");

        fscanf(f1,"%s%s%s",label,opcode,operand);
        fprintf(f5,"%s\t%s\t%s\n",label,opcode,operand);
        if(strcmp(opcode,"START")==0)
        {
                strcpy(start,operand);
                fscanf(f2,"%s",l1);
                fprintf(f6,"H^%-6s^00%s^00%s\n",label,start,l1);
                fscanf(f1,"%s%s%s%s",address,label,opcode,operand);
        }
        strcpy(text_start,address);
        while(strcmp(opcode,"END")!=0)
        {
                char temp[100]="";
                rewind(f4);
                while(fscanf(f4,"%s%s",code,mne)!=EOF)
                {
                        //rewind(f4);
                        if(strcmp(opcode,code)==0)
                        {
                                rewind(f3);
                                while(fscanf(f3,"%s%s",sym,add)!=EOF)
                                {
                                        //rewind(f3);
                                        if(strcmp(operand,sym)==0)
                                        {
                                                sprintf(temp,"%s%s",mne,add);
                                                fprintf(f5,"%s\t%s\t%s\t%s\t%s\n",address,label,opcode,operand,temp);
                                                break;
                                        }
                                }
                                break;
                        }
                }
                if(strcmp(opcode,"WORD")==0)
                {
                        sprintf(temp,"%06X",atoi(operand));
                        fprintf(f5,"%s\t%s\t%s\t%s\t%s\n",address,label,opcode,operand,temp);
                }
                else if(strcmp(opcode,"BYTE")==0)
                {
                        if(operand[0]=='C')
                        {
                                char hex[5];
                                for(i=2;i<strlen(operand)-1;i++)
                                {
                                        sprintf(hex,"%02X",operand[i]);
                                        strcat(temp,hex);
                //                      fprintf(f5,"%s%s%s%s%s",address,label,opcode,operand,temp);
                                }
                        }
                        else if(operand[0]=='X')
                        {

                                        strncpy(temp,operand+2,strlen(operand)-3);
                                        temp[strlen(operand)-3]='\0';
                  //                      fprintf(f5,"%s%s%s%s%s",address,label,opcode,operand,temp);
                        }
                        fprintf(f5,"%s\t%s\t%s\t%s\t%s\n",address,label,opcode,operand,temp);
                }
                else if(strcmp(opcode,"RESW")==0||strcmp(opcode,"RESB")==0)
                {
                        if (tlen>0)
                        {
                                fprintf(f6,"T^00%s^%02X^%s\n",text_start,tlen,objcode);
                                tlen=0;
                                strcpy(objcode,"");
                        }
                        strcpy(text_start,address);
                        fprintf(f5,"%s\t%s\t%s\t%s\t%s\n",address,label,opcode,operand,temp);
                        //fscanf(f1,"%s%s%s%s",address,label,opcode,operand);
                }
                if(strlen(temp)>0)
                {
                        strcat(objcode,temp);
                        strcat(objcode,"^");
                        tlen+=strlen(temp)/2;
                }
                 fscanf(f1,"%s%s%s%s",address,label,opcode,operand);

        }
        if(tlen>0)
        {
                 fprintf(f6,"T^00%s^%02X^%s\n",text_start,tlen,objcode);
        }
        fprintf(f6,"E^00%s",start);
        fprintf(f5,"%s%s%s%s",address,label,opcode,operand);
        fclose(f1);
        fclose(f2);
        fclose(f3);
        fclose(f4);
        fclose(f5);
         fclose(f6);

        return 0;
}
