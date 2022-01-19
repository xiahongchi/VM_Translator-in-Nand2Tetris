#include <stdio.h>
#include <cstring>
#include<iostream>
#include<io.h>
using namespace std;
class FunctionTable{
    struct Node{
        Node*next;
        char fName[20];
        int times;
        Node(const char*str){
            strcpy(fName,str);
            times=1;
            next=NULL;
        }
        Node(){
            next=NULL;
        }
    };
    Node*head;
public:
    FunctionTable(){
        head=new Node();
    }
    int inc(const char*str){
        Node*p=head->next,*q=head;
        while(p){
            if(strcmp(p->fName,str)==0){
                p->times++;
                return p->times;
            }
            p=p->next;
            q=q->next;
        }
        q->next=new Node(str);
        return 1;
    }
};
FunctionTable ft;
int neq=0,ngt=0,nlt=0,npt=0,nfl=0;
class File{

    struct Node{
        Node* next;
        char code[40];
    };
    Node*head;
    char filename[10];

    static FunctionTable ft;
    static int neq;
    static int ngt;
    static int nlt;
    static int npt;
    static int nfl;
public:

    File(){
        head=new Node;
        head->next=NULL;
        nfl++;
        filename[0]='f';
        filename[1]='i';
        filename[2]='l';
        filename[3]='e';
        filename[9]='\0';
        int k=8,num=nfl;
        for(;k>=4;k--){
            filename[k]=num%10+'0';
            num/=10;
        }
    }

    void BuildFile(const char* FileAddress){

        Node*p=head;

        FILE *fp;
        if ( (fp=fopen(FileAddress,"rt")) == NULL ) {
            puts("Fail to open file!");
        }

        char ch;

        while( (ch=fgetc(fp)) != EOF ){
            if(ch=='/') SkipLine(fp);
            else if(ch=='\n') continue;
            else{
                int k=0;
                p=p->next=new Node;
                p->next=NULL;
                while(k<39&&ch!='\n'&&ch!='/'&&ch!=EOF){
                    p->code[k]=ch;
                    ch=fgetc(fp);
                    k++;
                }
                p->code[k]='\0';
                if(ch=='\n') continue;
                if(ch=='/') {SkipLine(fp);continue;}
                if(ch!=EOF) SkipLine(fp);
                else break;
            }
        }
    }

    void PrintFile(FILE*fp){
        Node*p=head->next;
        while(p){
            fprintf(fp,p->code);
            fprintf(fp,"\n");
            p=p->next;
        }
    }

    void PrintFile2Screen(){
        Node*p=head->next;
        while(p){
            printf(p->code);
            printf("\n");
            p=p->next;
        }
    }

    void SkipLine(FILE *fp){
        char ch;
        while( (ch=fgetc(fp)) != '\n' ){}
    }

    void WriteCode(FILE*fp){
        Node*p=head->next;
        while(p){
            WriteLine(p,fp);
            p=p->next;
        }
    }

    void WriteLine(Node*p,FILE*fp){
        //PrintIntendent

        //JudgeSort

        //Arith

        //add
        if(p->code[0]=='a'&&p->code[1]=='d'&&p->code[2]=='d'){
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=D+M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");
        }
        //sub
        else if(p->code[0]=='s'&&p->code[1]=='u'&&p->code[2]=='b'){
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=M-D\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");
        }
        //neg
        else if(p->code[0]=='n'&&p->code[1]=='e'&&p->code[2]=='g'){
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=-M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");
        }

        //Logic

        //eq
        else if(p->code[0]=='e'&&p->code[1]=='q'){
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");

            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M-D\n");

            fprintf(fp,"@EQ_iftrue%d\n",neq);
            fprintf(fp,"D;JEQ\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=0\n");
            fprintf(fp,"@EQ_iffalse%d\n",neq);
            fprintf(fp,"0;JMP\n");
            fprintf(fp,"(EQ_iftrue%d)\n",neq);
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=-1\n");
            fprintf(fp,"(EQ_iffalse%d)\n",neq);

            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");

            neq++;
        }
        //gt
        else if(p->code[0]=='g'&&p->code[1]=='t'){
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");

            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M-D\n");

            fprintf(fp,"@GT_iftrue%d\n",ngt);
            fprintf(fp,"D;JGT\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=0\n");
            fprintf(fp,"@GT_iffalse%d\n",ngt);
            fprintf(fp,"0;JMP\n");
            fprintf(fp,"(GT_iftrue%d)\n",ngt);
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=-1\n");
            fprintf(fp,"(GT_iffalse%d)\n",ngt);

            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");

            ngt++;
        }
        //lt
        else if(p->code[0]=='l'&&p->code[1]=='t'){
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");

            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M-D\n");

            fprintf(fp,"@LT_iftrue%d\n",nlt);
            fprintf(fp,"D;JLT\n");

            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");

            fprintf(fp,"M=0\n");
            fprintf(fp,"@LT_iffalse%d\n",nlt);
            fprintf(fp,"0;JMP\n");
            fprintf(fp,"(LT_iftrue%d)\n",nlt);

            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");

            fprintf(fp,"M=-1\n");
            fprintf(fp,"(LT_iffalse%d)\n",nlt);

            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");

            nlt++;
        }
        //and
        else if(p->code[0]=='a'&&p->code[1]=='n'&&p->code[2]=='d'){
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=D&M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");
        }
        //or
        else if(p->code[0]=='o'&&p->code[1]=='r'){
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");

            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");

            fprintf(fp,"M=D|M\n");

            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");
        }
        //not
        else if(p->code[0]=='n'&&p->code[1]=='o'&&p->code[2]=='t'){
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=!M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");
        }

        //Memory access

        //pop
        else if(p->code[0]=='p'&&p->code[1]=='o'&&p->code[2]=='p'&&p->code[3]==' '){
            //start from 4
            //this 4-7
            if(p->code[4]=='t'&&p->code[5]=='h'&&p->code[6]=='i'){
                int num=ReadNum(p,9);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@THIS\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=D+A\n");

                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=M\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
            }
            //that 4-7
            else if(p->code[4]=='t'&&p->code[5]=='h'&&p->code[6]=='a'){
                int num=ReadNum(p,9);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@THAT\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=D+A\n");

                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=M\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
            }
            //temp
            else if(p->code[4]=='t'&&p->code[5]=='e'&&p->code[6]=='m'){
                int num=ReadNum(p,9);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@5\n");
                fprintf(fp,"D=D+A\n");

                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=M\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");

            }
            //local 4-8
            else if(p->code[4]=='l'&&p->code[5]=='o'&&p->code[6]=='c'){
                int num=ReadNum(p,10);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@LCL\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=D+A\n");

                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=M\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
            }
            //static 4-9
            else if(p->code[4]=='s'&&p->code[5]=='t'&&p->code[6]=='a'){
                int num=ReadNum(p,11);
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=M\n");
                fprintf(fp,"@%s.%d\n",filename,num);
                fprintf(fp,"M=D\n");
            }
            //pointer 4-10
            else if(p->code[4]=='p'&&p->code[5]=='o'&&p->code[6]=='i'){
                int num=ReadNum(p,12);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@PT_iffalse%d\n",npt);
                fprintf(fp,"D;JEQ\n");

                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=M\n");
                fprintf(fp,"@THAT\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@PT_iftrue%d\n",npt);
                fprintf(fp,"0;JMP\n");

                fprintf(fp,"(PT_iffalse%d)\n",npt);
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=M\n");
                fprintf(fp,"@THIS\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"(PT_iftrue%d)\n",npt);

                npt++;
            }
            //argument 4-11
            else if(p->code[4]=='a'&&p->code[5]=='r'&&p->code[6]=='g'){
                int num=ReadNum(p,13);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@ARG\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=D+A\n");

                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"D=M\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M-1\n");
            }
        }

        //push
        else if(p->code[0]=='p'&&p->code[1]=='u'&&p->code[2]=='s'&&p->code[3]=='h'&&p->code[4]==' '){
            //this 5-8
            if(p->code[5]=='t'&&p->code[6]=='h'&&p->code[7]=='i'){
                int num=ReadNum(p,10);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@THIS\n");
                fprintf(fp,"A=D+M\n");
                fprintf(fp,"D=M\n");

                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
            }
            //that
            else if(p->code[5]=='t'&&p->code[6]=='h'&&p->code[7]=='a'){
                int num=ReadNum(p,10);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@THAT\n");
                fprintf(fp,"A=D+M\n");
                fprintf(fp,"D=M\n");

                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
            }
            //temp
            else if(p->code[5]=='t'&&p->code[6]=='e'&&p->code[7]=='m'){
                int num=ReadNum(p,10);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@5\n");
                fprintf(fp,"A=D+A\n");
                fprintf(fp,"D=M\n");

                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
            }
            //local 5-9
            else if(p->code[5]=='l'&&p->code[6]=='o'&&p->code[7]=='c'){
                int num=ReadNum(p,11);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@LCL\n");
                fprintf(fp,"A=D+M\n");
                fprintf(fp,"D=M\n");

                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
            }
            //static 5-10
            else if(p->code[5]=='s'&&p->code[6]=='t'&&p->code[7]=='a'){
                int num=ReadNum(p,12);
                fprintf(fp,"@%s.%d\n",filename,num);
                fprintf(fp,"D=M\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
            }
            //pointer 5-11
            else if(p->code[5]=='p'&&p->code[6]=='o'&&p->code[7]=='i'){
                int num=ReadNum(p,13);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@PT_iffalse%d\n",npt);
                fprintf(fp,"D;JEQ\n");

                fprintf(fp,"@THAT\n");
                fprintf(fp,"D=M\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@PT_iftrue%d\n",npt);
                fprintf(fp,"0;JMP\n");

                fprintf(fp,"(PT_iffalse%d)\n",npt);
                fprintf(fp,"@THIS\n");
                fprintf(fp,"D=M\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"(PT_iftrue%d)\n",npt);

                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");

                npt++;
            }
            //constant 5-12
            else if(p->code[5]=='c'&&p->code[6]=='o'&&p->code[7]=='n'){
                int num=ReadNum(p,14);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
            }
            //argument
            else if(p->code[5]=='a'&&p->code[6]=='r'&&p->code[7]=='g'){
                int num=ReadNum(p,14);
                fprintf(fp,"@%d\n",num);
                fprintf(fp,"D=A\n");
                fprintf(fp,"@ARG\n");
                fprintf(fp,"A=D+M\n");
                fprintf(fp,"D=M\n");

                fprintf(fp,"@SP\n");
                fprintf(fp,"A=M\n");
                fprintf(fp,"M=D\n");
                fprintf(fp,"@SP\n");
                fprintf(fp,"M=M+1\n");
            }
        }

        //Branches

        //goto label
        else if(p->code[0]=='g'&&p->code[1]=='o'&&p->code[2]=='t'&&p->code[3]=='o'&&p->code[4]==' '){
            char label[20];
            FetchLabel(p,label,5);
            fprintf(fp,"@%s\n",label);
            fprintf(fp,"0;JMP\n");
        }

        //if-goto label
        else if(p->code[0]=='i'&&p->code[1]=='f'&&p->code[2]=='-'&&p->code[3]=='g'&&p->code[4]=='o'
                &&p->code[5]=='t'&&p->code[6]=='o'&&p->code[7]==' '){
            char label[20];
            FetchLabel(p,label,8);
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@%s\n",label);
            fprintf(fp,"D;JNE\n");
        }

        //label label
        else if(p->code[0]=='l'&&p->code[1]=='a'&&p->code[2]=='b'
                &&p->code[3]=='e'&&p->code[4]=='l'&&p->code[5]==' '){
            char label[20];
            FetchLabel(p,label,6);
            fprintf(fp,"(%s)\n",label);
        }

        //Functions

        //call fName nArgs

        else if(p->code[0]=='c'&&p->code[1]=='a'&&p->code[2]=='l'&&p->code[3]=='l'&&p->code[4]==' '){

            char fName[20];
            int nArgs=0;
            int k=5,i=0; //start=k=5
            while(p->code[k]!=' '){
                fName[i]=p->code[k];
                k++;
                i++;
            }
            fName[i]='\0';
            k++;
            while(p->code[k]>='0'&&p->code[k]<='9'){
                nArgs=nArgs*10+p->code[k]-'0';
                k++;
            }

            int times=ft.inc(fName);

            fprintf(fp,"@%s_RT%d\n",fName,times);
            fprintf(fp,"D=A\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=D\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");

            fprintf(fp,"@LCL\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=D\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");

            fprintf(fp,"@ARG\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=D\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");

            fprintf(fp,"@THIS\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=D\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");

            fprintf(fp,"@THAT\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=D\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");

            fprintf(fp,"@SP\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@5\n");
            fprintf(fp,"D=D-A\n");
            fprintf(fp,"@%d\n",nArgs);
            fprintf(fp,"D=D-A\n");
            fprintf(fp,"@ARG\n");
            fprintf(fp,"M=D\n");

            fprintf(fp,"@SP\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@LCL\n");
            fprintf(fp,"M=D\n");

            fprintf(fp,"@%s\n",fName);
            fprintf(fp,"0;JMP\n");
            fprintf(fp,"(%s_RT%d)\n",fName,times);

        }

        //function fName nVars

        else if(p->code[0]=='f'&&p->code[1]=='u'&&p->code[2]=='n'&&p->code[3]=='c'){

            char fName[20];
            int nVars=0;
            int k=9,i=0; //start=k=9
            while(p->code[k]!=' '){
                fName[i]=p->code[k];
                k++;
                i++;
            }
            fName[i]='\0';
            k++;
            while(p->code[k]>='0'&&p->code[k]<='9'){
                nVars=nVars*10+p->code[k]-'0';
                k++;
            }



            //...
            fprintf(fp,"(%s)\n",fName);
            fprintf(fp,"@%d\n",nVars);
            fprintf(fp,"D=A\n");
            fprintf(fp,"(%s_RP1)\n",fName);
            fprintf(fp,"@%s_RP0\n",fName);
            fprintf(fp,"D;JEQ\n");
            fprintf(fp,"D=D-1\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=0\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");
            fprintf(fp,"@%s_RP1\n",fName);
            fprintf(fp,"0;JMP\n");
            fprintf(fp,"(%s_RP0)\n",fName);

        }

        //return

        else if(p->code[0]=='r'&&p->code[1]=='e'&&p->code[2]=='t'&&p->code[3]=='u'){

            //LCL=LCL-1
            fprintf(fp,"@LCL\n");
            fprintf(fp,"M=M-1\n");

            //THAT=*LCL
            fprintf(fp,"@LCL\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@THAT\n");
            fprintf(fp,"M=D\n");

            //LCL=LCL-1
            fprintf(fp,"@LCL\n");
            fprintf(fp,"M=M-1\n");

            //THIS=*LCL
            fprintf(fp,"@LCL\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@THIS\n");
            fprintf(fp,"M=D\n");

            //*LCL=*(LCL-3)
            fprintf(fp,"@LCL\n");
            fprintf(fp,"A=M-1\n");
            fprintf(fp,"A=A-1\n");
            fprintf(fp,"A=A-1\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@LCL\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=D\n");

            //*ARG=pop();
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M-1\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@ARG\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=D\n");

            //SP=ARG
            fprintf(fp,"@ARG\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=D\n");

            //LCL--
            fprintf(fp,"@LCL\n");
            fprintf(fp,"M=M-1\n");

            //ARG=*LCL
            fprintf(fp,"@LCL\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@ARG\n");
            fprintf(fp,"M=D\n");

            //*LCL=*(LCL-1)
            fprintf(fp,"@LCL\n");
            fprintf(fp,"A=M-1\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@LCL\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=D\n");

            //SP++
            fprintf(fp,"@SP\n");
            fprintf(fp,"M=M+1\n");

            //*SP=*(LCL+1)
            fprintf(fp,"@LCL\n");
            fprintf(fp,"A=M+1\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"M=D\n");

            //LCL=*LCL
            fprintf(fp,"@LCL\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"D=M\n");
            fprintf(fp,"@LCL\n");
            fprintf(fp,"M=D\n");

            //goto
            fprintf(fp,"@SP\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"A=M\n");
            fprintf(fp,"0;JMP\n");

        }

    }

    int ReadNum(Node*p,int start){
        int k=start,num=0;
        while(p->code[k]>='0'&&p->code[k]<='9'){
            num=num*10+p->code[k]-'0';
            k++;
        }
        return num;
    }

    void FetchLabel(Node*p,char label[],int start){
        int k=start,i=0;
        while(p->code[k]!=' '&&p->code[k]!='\0'){
            label[i]=p->code[k];
            k++;
            i++;
        }
        label[i]='\0';
    }

    ~File(){
        Node*p=head->next;
        while(p){
            head->next=p->next;
            delete p;
            p=head->next;
        }
        delete head;
    }
};

int File::neq = 0;
int File::ngt = 0;
int File::nlt = 0;
int File::npt = 0;
int File::nfl = 0;
FunctionTable File::ft;

int main()
{

    _finddata_t fileDir;
    long lfDir;
    FILE*fp;

    char dir[]="D:\\ComputerScience\\nand2tetris\\nand2tetris\\projects\\08\\FunctionCalls\\StaticsTest\\*.vm";
    char path[]="D:\\ComputerScience\\nand2tetris\\nand2tetris\\projects\\08\\FunctionCalls\\StaticsTest\\";

    fp=fopen("D:\\ComputerScience\\nand2tetris\\nand2tetris\\projects\\08\\FunctionCalls\\StaticsTest\\StaticsTest.asm","wt");
    char*filepath=new char[strlen(dir)+20];
    strcpy(filepath,path);
    strcat(filepath,"Sys.vm");
    File fl;
    fl.BuildFile(filepath);
    fl.WriteCode(fp);
    delete [] filepath;

    if((lfDir = _findfirst(dir,&fileDir))==-1l)
      printf("No file is found\n");
    else{
      printf("file list:\n");
        do{
        printf("%s\n",fileDir.name);
        int k=0;
        while(fileDir.name[k]!='.') k++;
        if(fileDir.name[0]=='S'&&fileDir.name[1]=='y'&&fileDir.name[2]=='s'&&fileDir.name[3]=='.') continue;
        else{
            char*filepath=new char[strlen(dir)+20];
            strcpy(filepath,path);
            strcat(filepath,fileDir.name);
            File fl;
            fl.BuildFile(filepath);
            fl.WriteCode(fp);
            delete [] filepath;
        }
      }while( _findnext( lfDir, &fileDir ) == 0 );
    }
    _findclose(lfDir);

    return 0;
}
