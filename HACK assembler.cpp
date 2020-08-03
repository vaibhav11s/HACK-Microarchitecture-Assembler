#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxLength 20
#define MaxEntries 1024
#define MaxCharPerLine 100

struct SymbolTableEntry{
    char symbol[MaxLength];
    int address;
    };

struct SymbolTableEntry SymbolTable[MaxEntries];

void InitializeSymbolTable(){
    strcpy(SymbolTable[0].symbol,"SP");
    strcpy(SymbolTable[1].symbol,"LCL");
    strcpy(SymbolTable[2].symbol,"ARG");
    strcpy(SymbolTable[3].symbol,"THIS");
    strcpy(SymbolTable[4].symbol,"THAT");
    strcpy(SymbolTable[5].symbol,"R0");
    strcpy(SymbolTable[6].symbol,"R1");
    strcpy(SymbolTable[7].symbol,"R2");
    strcpy(SymbolTable[8].symbol,"R3");
    strcpy(SymbolTable[9].symbol,"R4");
    strcpy(SymbolTable[10].symbol,"R5");
    strcpy(SymbolTable[11].symbol,"R6");
    strcpy(SymbolTable[12].symbol,"R7");
    strcpy(SymbolTable[13].symbol,"R8");
    strcpy(SymbolTable[14].symbol,"R9");
    strcpy(SymbolTable[15].symbol,"R10");
    strcpy(SymbolTable[16].symbol,"R11");
    strcpy(SymbolTable[17].symbol,"R12");
    strcpy(SymbolTable[18].symbol,"R13");
    strcpy(SymbolTable[19].symbol,"R14");
    strcpy(SymbolTable[20].symbol,"R15");
    strcpy(SymbolTable[21].symbol,"SCREEN");
    strcpy(SymbolTable[22].symbol,"KBD");

    SymbolTable[0].address=0;
    SymbolTable[1].address=1;
    SymbolTable[2].address=2;
    SymbolTable[3].address=3;
    SymbolTable[4].address=4;
    SymbolTable[5].address=0;
    SymbolTable[6].address=1;
    SymbolTable[7].address=2;
    SymbolTable[8].address=3;
    SymbolTable[9].address=4;
    SymbolTable[10].address=5;
    SymbolTable[11].address=6;
    SymbolTable[12].address=7;
    SymbolTable[13].address=8;
    SymbolTable[14].address=9;
    SymbolTable[15].address=10;
    SymbolTable[16].address=11;
    SymbolTable[17].address=12;
    SymbolTable[18].address=13;
    SymbolTable[19].address=14;
    SymbolTable[20].address=15;
    SymbolTable[21].address=16384;
    SymbolTable[22].address=24576;

    for(int i=23;i<MaxEntries;i++){
        strcpy(SymbolTable[i].symbol,"\0");
        SymbolTable[i].address=-1;
    }
}

void addEntry(struct SymbolTableEntry item){
    int i=0;

    while((strcmp(SymbolTable[i].symbol,item.symbol)!=0)&&(strcmp(SymbolTable[i].symbol,"\0")!=0)&&(i<MaxEntries))i++;

    if(i>=MaxEntries){
        printf("ERROR\n");
    }    
    else if(strcmp(SymbolTable[i].symbol,"\0")==0){
        strcpy(SymbolTable[i].symbol,item.symbol);
        SymbolTable[i].address=item.address;
    }

    else if((strcmp(SymbolTable[i].symbol,item.symbol)==0)&&(SymbolTable[i].address==-1)){
        SymbolTable[i].address=item.address;
    }
}

int containGetAddress(char *symbol){
    int i=0;

    while((i<MaxEntries)&&(SymbolTable[i].address!=-1)){

        if(strcmp(SymbolTable[i].symbol,symbol)==0)
            return(SymbolTable[i].address);
        i++;
    }
    return -1;
}

void convertToBinary(int inpNum,char *b){
    for(int i=0;i<15;i++)
    {
     if(inpNum%2==0)b[i]='0'; else b[i]='1';
      inpNum=inpNum/2;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define lines 30000
#define CharPerLine 100
int main(){
    char str[lines][CharPerLine];
    char prs[lines][CharPerLine];
    char pre[lines][CharPerLine];
    int arr[lines];
    int i , ii , iii , j , k ,nlines  ,  t , jj ;
   
   
////////////////////////////////////scaning input mnemonics    
    for(i=0;i<lines;i++){
        str[i][0]='\0';
    }
    for(i=0;i<lines;i++){
        scanf(" %[^\n]%*c", str[i]);
    }
   
   
    for(i=0;i<lines;i++){
        arr[i]=strlen(str[i]);
    }
 
   
   
   
//for(i=0;i<lines;i++)printf("%s\n",str[i]);  
   
//////////////////////////////////////////////////////////////////////phase1 start  
///////////////////////////////removing spaces and
    for(i=0,ii=0;i<lines;i++,ii++){
        if(str[i][0]!='\0'){
            for(j=0,k=0;j<arr[i];j++,k++){
                if(str[i][j]!=' '){
                    prs[ii][k]=str[i][j];
                }
                else{
                    k--;
                }
                 
            }
            prs[ii][k]='\0';
        }
        else{
            ii--;
        }
    }
    prs[ii][0]='\0';
         
       
//for(i=0;i<ii;i++)printf("%s  %ld\n",prs[i], strlen(prs[i]));
   
   
   // printf("\n\n\n");

/////////////////////////////// remove comments
   
  for(i=0;i<ii;i++){
        arr[i]=strlen(prs[i]);
    }  

  k=ii;
    for(ii=0,iii=0;ii<k;ii++,iii++){
        if(prs[ii][0]=='/'&&prs[ii][1]=='/'){
            iii--;
        }
        else{
            for(i=0;i<arr[ii];i++){
                if(prs[ii][i]=='/'&&prs[ii][i+1]=='/'){
                    pre[iii][i]='\0';
                    break;
                }
                else if(prs[ii][i]=='\0'){
                     pre[iii][i]='\0';
                    break;
                }
                else{
                    pre[iii][i]=prs[ii][i];
                }
            }
        }
    }
    pre[iii][0]='\0';
   

  // for(i=0;i<iii;i++){printf("%s\n",pre[i]);}
   
//////////////////////////////////////////////////////////////////////////////////////////////


    nlines=iii;
    jj=nlines;
    //printf("%d\n",nlines);
    char symbo[100];
    int ctype[nlines];
    InitializeSymbolTable();
    struct SymbolTableEntry itemx;
    for(i=0,t=0;i<nlines;i++,t++){
       
        if(pre[i][0]=='@'){
            //printf("%c\n",pre[i][0]);
            ctype[i]=1;//A command
            if(pre[i][1]>'9'||pre[i][1]<'0'){
                for(j=0;pre[i][j];j++){
                    symbo[j]=pre[i][j+1];
                }
                strcpy(itemx.symbol,symbo);
                itemx.address=-1;
                addEntry(itemx);
            }
       
        }
        else if(pre[i][0]=='('){
            j=1;
            while(pre[i][j]!=')'){
                symbo[j-1]=pre[i][j];
                j++;
            }
            symbo[j-1]='\0';
            strcpy(itemx.symbol,symbo);            
           
            j++;
            if(pre[i][j]=='\0'){
                ctype[i]=3;//L COMMAND
                t--;
                jj--;
                itemx.address=t+1;
                addEntry(itemx);
            }
           
            else if(pre[i][j]=='@'){
                ctype[i]=4;//L AND A COMMAND
                itemx.address=t;
                addEntry(itemx);

                if(pre[i][j+1]>'9'||pre[i][j+1]<'0'){
                    for(k=0;pre[i][j];j++,k++){
                        symbo[k]=pre[i][j+1];
                    }
                    strcpy(itemx.symbol,symbo);
                    itemx.address=-1;
                    addEntry(itemx);
                }
            }
           
            else if(pre[i][0]=='M'||pre[i][0]=='A'||pre[i][0]=='D'||(pre[i][0]>'0'||pre[i][0]<'9')){
                ctype[i]=5;//L AND C COMMAND
                itemx.address=t;
                addEntry(itemx);
            }
           
            else{
                printf("COMMAND ERROR at instruction 1:%d\n",i+1);
                return 0;
            }
        }
        else if(pre[i][0]=='M'||pre[i][0]=='A'||pre[i][0]=='D'||pre[i][0]=='0'){
            ctype[i]=2;//C COMMAND
        }
        else{
            printf("COMMAND ERROR at instruction 2:%d\n",i+1);
            return 0;
        }
    }
    j=16;
    for(i=0;i<MaxEntries;i++){
        if(strcmp(SymbolTable[i].symbol,"\0")!=0&&(SymbolTable[i].address==-1))
            SymbolTable[i].address=j++;
        if(strcmp(SymbolTable[i].symbol,"\0")==0)break;
    }
j=0;
//while(1){printf("%s - %d\n",SymbolTable[j].symbol,SymbolTable[j].address);j++;if(strcmp(SymbolTable[j].symbol,"\0")==0)break;}






/////////////////////////////////////////////phase1 done



/////////////////////////////////////////////////////////////////////phase2 start
char bin[nlines][17];

char Dest[4];
char dest[4];
dest[3]='\0';
Dest[3]='\0';
char symb[16];
char comp[8];
char cmp[5];
char jmp[4];
int s=1;
    for(i=0;i<nlines;i++){
        if(ctype[i]==1){//A command
            bin[i][0]='0';
            t=pre[i][1];
            if(pre[i][1]>'9'||pre[i][1]<'0'){
                for(j=0;pre[i][j];j++){
                    symb[j]=pre[i][j+1];
                }
                j=0;
                while(1){
                    if(strcmp(SymbolTable[j].symbol,symb)==0){
                        t=SymbolTable[j].address;
                        s=0;
                        break;
                    }
                    j++;
                }
                if(s!=0){
                    printf("COMMAND ERROR at instruction 3:%d\n",i+1);
                    return 0;
                }
                for(k=15;k>=1;k--){
                    if(t%2==0)bin[i][k]='0'; else bin[i][k]='1';
                    t=t/2;
                }
            }
            else{t=0;
                for(jj=1;pre[i][jj];jj++)
                    t=(pre[i][jj]-'0')+t*10;
                for(k=15;k>=1;k--){
                    if(t%2==0)bin[i][k]='0'; else bin[i][k]='1';
                    t=t/2;
                }
            }
            bin[i][16]='\0';
           
            //done
        }
       
        else if(ctype[i]==2){//C COMMAND
       
            if(pre[i][1]==';'){
               
                if(pre[i][0]=='D')strcpy(comp,"0001100");
                else if(pre[i][0]=='A')strcpy(comp,"0110000");
                else if(pre[i][0]=='M')strcpy(comp,"1110000");
                else if(pre[i][0]>='0'&&pre[i][0]<='9')strcpy(comp,"0101010");
                else{
                    printf("COMMAND ERROR at instruction 4:%d\n",i+1);
                    return 0;
                }
               
                for(j=1;pre[i][j];j++){
                    cmp[j-1]=pre[i][j+1];
                }
               
                if       (strcmp(cmp,"JGT")==0) strcpy(jmp,"001");
                else if(strcmp(cmp,"JEQ")==0) strcpy(jmp,"010");
                else if(strcmp(cmp,"JGE")==0) strcpy(jmp,"011");
                else if(strcmp(cmp,"JLT")==0) strcpy(jmp,"100");
                else if(strcmp(cmp,"JNE")==0) strcpy(jmp,"101");
                else if(strcmp(cmp,"JLE")==0) strcpy(jmp,"110");
                else if(strcmp(cmp,"JMP")==0) strcpy(jmp,"111");
                else{
                    printf("COMMAND ERROR at instruction 5:%d\n",i+1);
                    return 0;
                }
                //
                bin[i][0]='1';
                bin[i][1]='1';
                bin[i][2]='1';
                bin[i][3]=comp[0];
                bin[i][4]=comp[1];
                bin[i][5]=comp[2];
                bin[i][6]=comp[3];
                bin[i][7]=comp[4];
                bin[i][8]=comp[5];
                bin[i][9]=comp[6];
                bin[i][10]='0';
                bin[i][11]='0';
                bin[i][12]='0';
                bin[i][13]=jmp[0];
                bin[i][14]=jmp[1];
                bin[i][15]=jmp[2];
                bin[i][16]='\0';
               
               
            }
           
            else{
                for(j=0;pre[i][j];j++){
                    if(pre[i][j]=='='){                        
                       
                        for(jj=0;pre[i][jj]!='=';jj++){
                            Dest[jj]=pre[i][jj];
                        }
                        Dest[jj]='\0';
                       
                        for(k=0;pre[i][jj];jj++,k++){
                            cmp[k]=pre[i][jj+1];
                        }
                       
                       
                        if      (strcmp (Dest,"M")  ==0) strcpy(dest,"001");
                        else if (strcmp (Dest,"D")  ==0) strcpy(dest,"010");
                        else if (strcmp (Dest,"MD") ==0) strcpy(dest,"011");
                        else if (strcmp (Dest,"DM") ==0) strcpy(dest,"011");
                        else if (strcmp (Dest,"A")  ==0) strcpy(dest,"100");
                        else if (strcmp (Dest,"AM") ==0) strcpy(dest,"101");
                        else if (strcmp (Dest,"MA") ==0) strcpy(dest,"101");
                        else if (strcmp (Dest,"AD") ==0) strcpy(dest,"110");
                        else if (strcmp (Dest,"DA") ==0) strcpy(dest,"110");
                        else if (strcmp (Dest,"AMD")==0) strcpy(dest,"111");
                        else if (strcmp (Dest,"ADM")==0) strcpy(dest,"111");
                        else if (strcmp (Dest,"MAD")==0) strcpy(dest,"111");
                        else if (strcmp (Dest,"MDA")==0) strcpy(dest,"111");
                        else if (strcmp (Dest,"DAM")==0) strcpy(dest,"111");
                        else if (strcmp (Dest,"DMA")==0) strcpy(dest,"111");
                        else{
                            printf("COMMAND ERROR at instruction 6:%d\n",i+1);
                            return 0;
                        }
                   
                        if       (strcmp(cmp,"0")==0)   strcpy(comp,"0101010");
                        else if(strcmp(cmp,"1")==0)   strcpy(comp,"0111111");
                        else if(strcmp(cmp,"-1")==0)  strcpy(comp,"0111010");
                        else if(strcmp(cmp,"D")==0)   strcpy(comp,"0001100");
                        else if(strcmp(cmp,"A")==0)   strcpy(comp,"0110000");
                        else if(strcmp(cmp,"M")==0)   strcpy(comp,"1110000");
                        else if(strcmp(cmp,"!D")==0)  strcpy(comp,"0001101");
                        else if(strcmp(cmp,"!A")==0)  strcpy(comp,"0110001");
                        else if(strcmp(cmp,"!M")==0)  strcpy(comp,"1110001");
                        else if(strcmp(cmp,"-D")==0)  strcpy(comp,"0001111");
                        else if(strcmp(cmp,"-A")==0)  strcpy(comp,"0110011");
                        else if(strcmp(cmp,"-M")==0)  strcpy(comp,"1110011");
                        else if(strcmp(cmp,"D+1")==0) strcpy(comp,"0011111");
                        else if(strcmp(cmp,"1+D")==0) strcpy(comp,"0011111");
                        else if(strcmp(cmp,"A+1")==0) strcpy(comp,"0110111");
                        else if(strcmp(cmp,"1+A")==0) strcpy(comp,"0110111");
                        else if(strcmp(cmp,"M+1")==0) strcpy(comp,"1110111");
                        else if(strcmp(cmp,"1+M")==0) strcpy(comp,"1110111");
                        else if(strcmp(cmp,"D-1")==0) strcpy(comp,"0001110");
                        else if(strcmp(cmp,"-1+D")==0)strcpy(comp,"0001110");
                        else if(strcmp(cmp,"A-1")==0) strcpy(comp,"0110010");
                        else if(strcmp(cmp,"-1+A")==0)strcpy(comp,"0110010");
                        else if(strcmp(cmp,"M-1")==0) strcpy(comp,"1110010");
                        else if(strcmp(cmp,"-1+M")==0)strcpy(comp,"1110010");
                        else if(strcmp(cmp,"D+A")==0) strcpy(comp,"0000010");
                        else if(strcmp(cmp,"A+D")==0) strcpy(comp,"0000010");
                        else if(strcmp(cmp,"M+D")==0) strcpy(comp,"1000010");
                        else if(strcmp(cmp,"D+M")==0) strcpy(comp,"1000010");
                        else if(strcmp(cmp,"D-A")==0) strcpy(comp,"0010011");
                        else if(strcmp(cmp,"-A+D")==0)strcpy(comp,"0010011");
                        else if(strcmp(cmp,"D-M")==0) strcpy(comp,"1010011");
                        else if(strcmp(cmp,"-M+D")==0)strcpy(comp,"1010011");
                        else if(strcmp(cmp,"A-D")==0) strcpy(comp,"0000111");
                        else if(strcmp(cmp,"-D+A")==0)strcpy(comp,"0000111");
                        else if(strcmp(cmp,"M-D")==0) strcpy(comp,"1000111");
                        else if(strcmp(cmp,"-D+M")==0)strcpy(comp,"1000111");
                        else if(strcmp(cmp,"D&A")==0) strcpy(comp,"0000000");
                        else if(strcmp(cmp,"A&D")==0) strcpy(comp,"0000000");
                        else if(strcmp(cmp,"M&D")==0) strcpy(comp,"1000000");
                        else if(strcmp(cmp,"D&M")==0) strcpy(comp,"1000000");
                        else if(strcmp(cmp,"D|A")==0) strcpy(comp,"0010101");
                        else if(strcmp(cmp,"A|D")==0) strcpy(comp,"0010101");
                        else if(strcmp(cmp,"M|D")==0) strcpy(comp,"1010101");
                        else if(strcmp(cmp,"D|M")==0) strcpy(comp,"1010101");
                        else {
                            printf("COMMAND ERROR at instruction 7:%d\n",i+1);
                            return 0;
                        }
                       
                        bin[i][0]='1';
                        bin[i][1]='1';
                        bin[i][2]='1';
                        bin[i][3]=comp[0];
                        bin[i][4]=comp[1];
                        bin[i][5]=comp[2];
                        bin[i][6]=comp[3];
                        bin[i][7]=comp[4];
                        bin[i][8]=comp[5];
                        bin[i][9]=comp[6];
                        bin[i][10]=dest[0];
                        bin[i][11]=dest[1];
                        bin[i][12]=dest[2];
                        bin[i][13]='0';
                        bin[i][14]='0';
                        bin[i][15]='0';
                        bin[i][16]='\0';
                       
                    break;  
                    }
                   
                }
                if(pre[i][j]=='\0'){
                    printf("COMMAND ERROR at instruction 8:%d\n",i+1);
                    return 0;
                }
                //
            }
       
           
           
           
        }
           
       
        else if(ctype[i]==3){//L COMMAND
            bin[i][0]='\0';
        }
       
        else if(ctype[i]==4){//L AND A COMMAND
            for(j=1;pre[i][j]!=')';j++){
                continue;
            }
            j++;
             //printf("%d",i);
            bin[i][0]='0';
            if(pre[i][j+1]>'9'||pre[i][j+1]<'0'){
                for(k=0;pre[i][j];k++,j++){
                    symb[k]=pre[i][j+1];
                }
                j=0;
                while(1){
                    if(strcmp(SymbolTable[j].symbol,symb)==0){
                        t=SymbolTable[j].address;
                        s=2;
                        break;
                    }
                    j++;
                }
                if(s!=2){
                    printf("COMMAND ERROR at instruction 9:%d\n",i+1);
                    return 0;
                }
                for(k=15;k>=1;k--){
                    if(t%2==0)bin[i][k]='0'; else bin[i][k]='1';
                    t=t/2;
                }
            }
            else if(pre[i][j+1]<'9'&&pre[i][j+1]>'0'){
                t=pre[i][j+1]-'0';
                for(k=15;k>=1;k--){
                    if(t%2==0)bin[i][k]='0'; else bin[i][k]='1';
                    t=t/2;
                }
            }
            else{
                printf("COMMAND ERROR at instruction 10:%d\n",i+1);
                return 0;
            }
            bin[i][16]='\0';
           
            //done
           
           
           
           
           
        }
       
        else if(ctype[i]==5){//L AND C COMMAND
           
            for(j=1;pre[i][j]!=')';j++){
                continue;
            }
            j++;
           
           
           
           
           
            if(pre[i][j+1]==';'){
               
                if(pre[i][j]=='D')strcpy(comp,"0001100");
                else if(pre[i][j]=='A')strcpy(comp,"0110000");
                else if(pre[i][j]=='M')strcpy(comp,"1110000");
                else if(pre[i][j]>='0'&&pre[i][j]<='9')strcpy(comp,"0101010");
                else{
                    printf("COMMAND ERROR at instruction 11:%d\n",i+1);
                    return 0;
                }
               
                for(k=j+1;pre[i][k];k++){
                    cmp[k-j-1]=pre[i][k+1];
                }
               
                if       (strcmp(cmp,"JGT")==0) strcpy(jmp,"001");
                else if(strcmp(cmp,"JEQ")==0) strcpy(jmp,"010");
                else if(strcmp(cmp,"JGE")==0) strcpy(jmp,"011");
                else if(strcmp(cmp,"JLT")==0) strcpy(jmp,"100");
                else if(strcmp(cmp,"JNE")==0) strcpy(jmp,"101");
                else if(strcmp(cmp,"JLE")==0) strcpy(jmp,"110");
                else if(strcmp(cmp,"JMP")==0) strcpy(jmp,"111");
                else{
                    printf("COMMAND ERROR at instruction 12:%d\n",i+1);
                    return 0;
                }
                //
                bin[i][0]='1';
                bin[i][1]='1';
                bin[i][2]='1';
                bin[i][3]=comp[0];
                bin[i][4]=comp[1];
                bin[i][5]=comp[2];
                bin[i][6]=comp[3];
                bin[i][7]=comp[4];
                bin[i][8]=comp[5];
                bin[i][9]=comp[6];
                bin[i][10]='0';
                bin[i][11]='0';
                bin[i][12]='0';
                bin[i][13]=jmp[0];
                bin[i][14]=jmp[1];
                bin[i][15]=jmp[2];
                bin[i][16]='\0';
               
               
            }
           
            else{
                ii=j;
                for(;pre[i][ii];ii++){
                    if(pre[i][ii]=='='){                        
                        ii++;
                        for(jj=j;pre[i][jj]!='=';jj++){
                            Dest[jj-j]=pre[i][jj];
                        }
                        Dest[jj]='\0';
                        //printf("%s \n ",Dest);
                        for(j=jj;pre[i][j];j++){
                            cmp[j-jj]=pre[i][j+1];
                        }
                        //printf("%s\n",cmp);
                       
                        if      (strcmp (Dest,"M")  ==0) strcpy(dest,"001");
                        else if (strcmp (Dest,"D")  ==0) strcpy(dest,"010");
                        else if (strcmp (Dest,"MD") ==0) strcpy(dest,"011");
                        else if (strcmp (Dest,"DM") ==0) strcpy(dest,"011");
                        else if (strcmp (Dest,"A")  ==0) strcpy(dest,"100");
                        else if (strcmp (Dest,"AM") ==0) strcpy(dest,"101");
                        else if (strcmp (Dest,"MA") ==0) strcpy(dest,"101");
                        else if (strcmp (Dest,"AD") ==0) strcpy(dest,"110");
                        else if (strcmp (Dest,"DA") ==0) strcpy(dest,"110");
                        else if (strcmp (Dest,"AMD")==0) strcpy(dest,"111");
                        else if (strcmp (Dest,"ADM")==0) strcpy(dest,"111");
                        else if (strcmp (Dest,"MAD")==0) strcpy(dest,"111");
                        else if (strcmp (Dest,"MDA")==0) strcpy(dest,"111");
                        else if (strcmp (Dest,"DAM")==0) strcpy(dest,"111");
                        else if (strcmp (Dest,"DMA")==0) strcpy(dest,"111");
                        else{
                            printf("COMMAND ERROR at instruction 13:%d\n",i+1);
                            return 0;
                        }
                   
                        if       (strcmp(cmp,"0")==0)   strcpy(comp,"0101010");
                        else if(strcmp(cmp,"1")==0)   strcpy(comp,"0111111");
                        else if(strcmp(cmp,"-1")==0)  strcpy(comp,"0111010");
                        else if(strcmp(cmp,"D")==0)   strcpy(comp,"0001100");
                        else if(strcmp(cmp,"A")==0)   strcpy(comp,"0110000");
                        else if(strcmp(cmp,"M")==0)   strcpy(comp,"1110000");
                        else if(strcmp(cmp,"!D")==0)  strcpy(comp,"0001101");
                        else if(strcmp(cmp,"!A")==0)  strcpy(comp,"0110001");
                        else if(strcmp(cmp,"!M")==0)  strcpy(comp,"1110001");
                        else if(strcmp(cmp,"-D")==0)  strcpy(comp,"0001111");
                        else if(strcmp(cmp,"-A")==0)  strcpy(comp,"0110011");
                        else if(strcmp(cmp,"-M")==0)  strcpy(comp,"1110011");
                        else if(strcmp(cmp,"D+1")==0) strcpy(comp,"0011111");
                        else if(strcmp(cmp,"1+D")==0) strcpy(comp,"0011111");
                        else if(strcmp(cmp,"A+1")==0) strcpy(comp,"0110111");
                        else if(strcmp(cmp,"1+A")==0) strcpy(comp,"0110111");
                        else if(strcmp(cmp,"M+1")==0) strcpy(comp,"1110111");
                        else if(strcmp(cmp,"1+M")==0) strcpy(comp,"1110111");
                        else if(strcmp(cmp,"D-1")==0) strcpy(comp,"0001110");
                        else if(strcmp(cmp,"-1+D")==0)strcpy(comp,"0001110");
                        else if(strcmp(cmp,"A-1")==0) strcpy(comp,"0110010");
                        else if(strcmp(cmp,"-1+A")==0)strcpy(comp,"0110010");
                        else if(strcmp(cmp,"M-1")==0) strcpy(comp,"1110010");
                        else if(strcmp(cmp,"-1+M")==0)strcpy(comp,"1110010");
                        else if(strcmp(cmp,"D+A")==0) strcpy(comp,"0000010");
                        else if(strcmp(cmp,"A+D")==0) strcpy(comp,"0000010");
                        else if(strcmp(cmp,"M+D")==0) strcpy(comp,"1000010");
                        else if(strcmp(cmp,"D+M")==0) strcpy(comp,"1000010");
                        else if(strcmp(cmp,"D-A")==0) strcpy(comp,"0010011");
                        else if(strcmp(cmp,"-A+D")==0)strcpy(comp,"0010011");
                        else if(strcmp(cmp,"D-M")==0) strcpy(comp,"1010011");
                        else if(strcmp(cmp,"-M+D")==0)strcpy(comp,"1010011");
                        else if(strcmp(cmp,"A-D")==0) strcpy(comp,"0000111");
                        else if(strcmp(cmp,"-D+A")==0)strcpy(comp,"0000111");
                        else if(strcmp(cmp,"M-D")==0) strcpy(comp,"1000111");
                        else if(strcmp(cmp,"-D+M")==0)strcpy(comp,"1000111");
                        else if(strcmp(cmp,"D&A")==0) strcpy(comp,"0000000");
                        else if(strcmp(cmp,"A&D")==0) strcpy(comp,"0000000");
                        else if(strcmp(cmp,"M&D")==0) strcpy(comp,"1000000");
                        else if(strcmp(cmp,"D&M")==0) strcpy(comp,"1000000");
                        else if(strcmp(cmp,"D|A")==0) strcpy(comp,"0010101");
                        else if(strcmp(cmp,"A|D")==0) strcpy(comp,"0010101");
                        else if(strcmp(cmp,"M|D")==0) strcpy(comp,"1010101");
                        else if(strcmp(cmp,"D|M")==0) strcpy(comp,"1010101");
                        else {
                            printf("COMMAND ERROR at instruction 14:%d\n",i+1);
                            return 0;
                        }
                       
                        bin[i][0]='1';
                        bin[i][1]='1';
                        bin[i][2]='1';
                        bin[i][3]=comp[0];
                        bin[i][4]=comp[1];
                        bin[i][5]=comp[2];
                        bin[i][6]=comp[3];
                        bin[i][7]=comp[4];
                        bin[i][8]=comp[5];
                        bin[i][9]=comp[6];
                        bin[i][10]=dest[0];
                        bin[i][11]=dest[1];
                        bin[i][12]=dest[2];
                        bin[i][13]='0';
                        bin[i][14]='0';
                        bin[i][15]='0';
                        bin[i][16]='\0';
                        break;
                       
                    }
                   
                }
                if(pre[i][ii]=='\0'){
                    printf("COMMAND ERROR at instruction 15:%d\n",i+1);
                    return 0;
                }
                //
            }
        }
       
    }
   
    for(i=0;i<nlines;i++){
       
            printf("%s\n",bin[i]);
       
       
    }
}