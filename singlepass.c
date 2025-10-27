#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXBUFF 1024

int main()
{
        char l1[100],start[100],label[100],opcode[100],address[100],operand[100];
        char code[50],mne[50],sym[50],add[50],text_start[100],temp[100];
        int i,tlen=0;
        int locctr=0;
        int startadd=0;

        FILE *f1,*f2,*f3,*f4,*f5,*f6;
        f1=fopen("input.txt","r");
        f2=fopen("symtab2.txt","w");
        f3=fopen("intermediate2.txt","w");
        f4=fopen("length2.txt","w");

        if(!f1||!f2||!f3||!f4)
        {
                //printf("haha");
                return 1;
        }
        fscanf(f1,"%s%s%s",label,opcode,operand);
        if(strcmp(opcode,"START")==0)
        {
                startadd=strtol(operand,NULL,16);
                locctr=startadd;
                fprintf(f3,"%s\t%s\t%s\n",label,opcode,operand);
                fscanf(f1,"%s%s%s",label,opcode,operand);
        }

        while(strcmp(opcode,"END")!=0)
        {
                fprintf(f2,"%s\t%X\n",label,locctr);
                fprintf(f3,"%X\t",locctr);
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
                        {
                                locctr+=(strlen(operand)-3);
                        }
                        else if(operand[0]=='X')
                        {
                                locctr+=(strlen(operand)-3+2)/2;
                        }

                }
                else locctr+=3;
                fprintf(f3,"%s\t%s\t%s\n",label,opcode,operand);
                fscanf(f1,"%s%s%s",label,opcode,operand);

        }
        fprintf(f3,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        fprintf(f4,"%06X",locctr-startadd);

        fclose(f1);
        fclose(f2);
        fclose(f3);
        fclose(f4);




        f1=fopen("intermediate2.txt","r");
        f2=fopen("length2.txt","r");
        f3=fopen("symtab2.txt","r");
        f4=fopen("optab.txt","r");
        f5=fopen("assembly2.txt","w");
        f6=fopen("obj2.txt","w");
        char obj[MAXBUFF]="";

        if(!f1||!f2||!f3||!f4||!f5||!f6)
        {
                //printf("haha");
                return 1;
        }

        fscanf(f1,"%s%s%s",label,opcode,operand);
        fprintf(f5,"%s\t%s\t%s\n",label,opcode,operand);



        if(strcmp(opcode,"START")==0)
        {
                fscanf(f2,"%s",l1);
                strcpy(start,operand);
                fprintf(f6,"H^%-6s00%s%s\n",label,start,l1);
                fscanf(f1,"%s%s%s%s",address,label,opcode,operand);
                strcpy(text_start,address);
                strcpy(obj,"");
        }
        while(strcmp(opcode,"END")!=0)
        {
                strcpy(temp,"");
                rewind(f4);
                while(fscanf(f4,"%s%s",code,mne)!=EOF)
                {
                        if(strcmp(opcode,code)==0)
                        {
                                rewind(f3);
                                while(fscanf(f3,"%s%s",sym,add)!=EOF)
                                {
                                        if(strcmp(operand,sym)==0)

                                        {
                                                sprintf(temp,"%s%s",mne,add);
                                                fprintf(f5,"%s\t%s\t%s\t%s\t%s\n",address,label,opcode,operand,temp);
                                                int found=1;
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
                                }
                        }
                        else if(operand[0]=='X')
                        {
                                strncpy(temp,operand+2,strlen(operand)-3);
                                temp[strlen(operand)-3]='\0';
                        }
                        fprintf(f5,"%s\t%s\t%s\t%s\t%s\n",address,label,opcode,operand,temp);
                }
                else if(strcmp(opcode,"RESW")==0 ||strcmp(opcode,"RESB")==0 )
                {
                        if(tlen>0){
                                fprintf(f6,"T^00%s^%02X^%s\n",text_start,tlen,obj);
                                //fscanf(f1,"%s%s%s%s",address,label,opcode,operand);
                                tlen=0;
                                strcpy(obj,"");
                        }
                        fprintf(f5,"%s\t%s\t%s\t%s\n",address,label,opcode,operand);
                        strcpy(text_start,address);
                }
                /*else{
                        fprintf(f5,"%s\t%s\t%s\t%s\n",address,label,opcode,operand);
                }*/

                if (strlen(temp)>0)
                {
                        strcat(obj,temp);
                        strcat(obj,"^");
                        tlen+=strlen(temp)/2;
                }
                fscanf(f1,"%s%s%s%s",address,label,opcode,operand);
        }
        if(tlen>0){
                fprintf(f6,"T^00%s^%02X%s\n",text_start,tlen,obj);

                }
        fprintf(f6,"E^00%s\n^",start);
        fprintf(f5,"%s\t%s\t%s\t%s\n",address,label,opcode,operand);

        fclose(f1);
        fclose(f2);
        fclose(f3);
        fclose(f4);
        fclose(f5);
        fclose(f6);
return 0;

}
