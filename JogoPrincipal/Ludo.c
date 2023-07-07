#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void imprimirTabuleiro(char tabuleiro[][15]);
void Cordado(char tabdado[][3],int dado);
void movimento(char tabuleiro[][15],char *boneco,int dado,int *jg1,int *mov,int *win1,int *win2,int *win3,int *win4,int *li,int *co,char *torre,int numjog);

void movimentocima(char tabuleiro[][15],char *boneco,int dado,int *li,int *co,int *mov,int *jg1,char novotabuleiro[][15],int liant,int coant,char *torre,int numjog);
void movimentodireita(char tabuleiro[][15], char *boneco,int dado,int *li,int *co,int *mov,int *jg1,char novotabuleiro[][15],int liant,int coant,char *torre,int numjog);
void movimentobaixo(char tabuleiro[][15], char *boneco,int dado,int *li,int *co,int *mov,int *jg1,char novotabuleiro[][15],int liant,int coant,char *torre,int numjog);
void movimentoesquerda(char tabuleiro[][15], char *boneco,int dado,int *li,int *co,int *mov,int *jg1,char novotabuleiro[][15],int liant,int coant,char *torre,int numjog);

void movimentovitoriaverde(char tabuleiro[][15], char *boneco,int dado,int *li, int *co, int *mov,int *win1,char novotabuleiro[][15],int liant,int coant,char *torre);
void movimentovitoriaamarelo(char tabuleiro[][15], char *boneco,int dado,int *li, int *co, int *mov,int *win2,char novotabuleiro[][15],int liant,int coant,char *torre);
void movimentovitoriaazul(char tabuleiro[][15], char *boneco,int dado,int *li, int *co, int *mov,int *win3,char novotabuleiro[][15],int liant,int coant,char *torre);
void movimentovitoriavermelho(char tabuleiro[][15], char *boneco,int dado,int *li, int *co, int *mov,int *,char novotabuleiro[][15],int liant,int coant,char *torre);

void comer(char tabuleiro[][15],char *bonecocomido,int *jg1,int numjog);
void movimentopulo(char tabuleiro[][15],char *boneco,int dado,int *li,int *co,int *mov,int *jg1,char novotabuleiro[][15],int liant,int coant,char *torre,int numjog);
void torreABCD(char tabuleiro[][15],char *torre,char *boneco,char *bonecocomido,int *li,int *co);
void torreEFGH(char tabuleiro[][15],char *torre,char *boneco,char *bonecocomido,int *li,int *co);
void torreIJKL(char tabuleiro[][15],char *torre,char *boneco,char *bonecocomido,int *li,int *co);
void torreMNOP(char tabuleiro[][15],char *torre,char *boneco,char *bonecocomido,int *li,int *co);
void desfaztorre(char tabuleiro[][15],char novotabuleiro[][15],char *boneco,char *torre,int *li,int *co,int liant,int coant);

typedef struct jogador{
    int cor;
}jogador;
typedef struct seis{
    int verde;
    int amarelo;
    int azul;
    int vermelho;
}tresseis;

int main(){
    int i,j,x,y,numjog=0;
    char tabuleiro[15][15],tabdado[3][3];
    jogador jog[4];
    tresseis seis;
    int win1=0,win2=0,win3=0,win4=0;
    int jg1,dado,jafoi=0,jafoi2=0,jafoi3=0,jafoi4=0,movim=0;
    char boneco[3];
    int li=-1,co=-1;
    char torre[20];

    seis.verde=0; //INICIA COM ZERO PRA CONTAR CORRETAMENTE
    seis.amarelo=0;
    seis.azul=0;
    seis.vermelho=0;

    printf("\n");
    printf("BEM VINDO AO JOGO LUDO!\n");
    printf("\n");
    sleep(2);

    for(i=0;i<15;i++){ //INICIA O TABULEIRO
        for(j=0;j<15;j++){
            tabuleiro[i][j] = ' ';
        }
    }
    for(i=0;i<3;i++){  //INICIA O DADO
        for(j=0;j<3;j++){
            tabdado[i][j] = '_';
        }
    }

    imprimirTabuleiro(tabuleiro); //MOSTRA O TABULEIRO NA TELA , PARA MOSTRAR AO USUARIO
    printf("\n");
    sleep(2);

    //NUMEROS DE JOGADORES E SUAS CORES
    printf("Insira quantos jogadores serao(2 ou 4)");
    scanf("%d",&numjog);

    if(numjog==4){
        printf("Digite qual cor cada jogador sera: \nO jogo conta com 4 cores:\n1-Verde\n2-Amarelo\n3-Azul\n4-Vermelho\n");
        printf("Insira a cor do jogador 1: ");
        scanf("%d",&jog[0].cor);
        printf("Insira a cor do jogador 2: ");
        scanf("%d",&jog[1].cor);
        printf("Insira a cor do jogador 3: ");
        scanf("%d",&jog[2].cor);
        printf("Insira a cor do jogador 4: ");
        scanf("%d",&jog[3].cor);

        for(i=1;i!=2;i++){ //PARA CASO O JOGADOR INSIRA NUMEROS REPETIDOS OU DIFERENTES DE 1234
            if(jog[0].cor<1||jog[0].cor>4||jog[1].cor<1||jog[1].cor>4||jog[2].cor<1||jog[2].cor>4||jog[3].cor<1||jog[3].cor>4||jog[0].cor==jog[1].cor||jog[0].cor==jog[2].cor||jog[0].cor==jog[3].cor||jog[1].cor==jog[2].cor||jog[1].cor==jog[3].cor||jog[2].cor==jog[3].cor){
                printf("Cada um com sua cor!\n");
                printf("Insira a cor do jogador 1: ");
                scanf("%d",&jog[0].cor);
                printf("Insira a cor do jogador 2: ");
                scanf("%d",&jog[1].cor);
                printf("Insira a cor do jogador 3: ");
                scanf("%d",&jog[2].cor);
                printf("Insira a cor do jogador 4: ");
                scanf("%d",&jog[3].cor);
                i--;
            }
        }
    }
    printf("\n");
    sleep(1);

    if(numjog==2){
        printf("ATENCAO, COMO SERAO APENAS DOIS JOGADORES, AS CORES SERAO AMARELO E VERMELHO\n");
        sleep(3);
        printf("BOA SORTE A TODOS!!!\n");
    }else if(numjog==4){
        printf("\nATENCAO: O JOGO VAI COMECAR, SE ORGANIZEM, POIS A ORDEM DE JOGADAS VAI SER:\nVERDE,AMARELO,AZUL E VERMELHO\n");
        sleep(1);
        printf("BOA SORTE A TODOS!!!\n");
    }


    for(i=0;i<15;i++){ //inicio
        for(j=0;j<15;j++){
            if(numjog==2){
                if(i==1&&j==10){//amarelo
                    tabuleiro[i][j]= 'E';
                }if(i==2&&j==11){
                    tabuleiro[i][j]= 'F';
                }if(i==3&&j==12){
                    tabuleiro[i][j]= 'G';
                }if(i==4&&j==13){
                    tabuleiro[i][j]= 'H';
                }
                if(i==10&&j==1){//vermelho
                    tabuleiro[i][j]= 'M';
                }if(i==11&&j==2){
                    tabuleiro[i][j]= 'N';
                }if(i==12&&j==3){
                    tabuleiro[i][j]= 'O';
                }if(i==13&&j==4){
                    tabuleiro[i][j]= 'P';
                }
            }
            else if(numjog==4){
                if(i==1&&j==1){//verde
                    tabuleiro[i][j]= 'A';
                }if(i==2&&j==2){
                    tabuleiro[i][j]= 'B';
                }if(i==3&&j==3){
                    tabuleiro[i][j]= 'C';
                }if(i==4&&j==4){
                    tabuleiro[i][j]= 'D';
                }

                if(i==1&&j==10){//amarelo
                    tabuleiro[i][j]= 'E';
                }if(i==2&&j==11){
                    tabuleiro[i][j]= 'F';
                }if(i==3&&j==12){
                    tabuleiro[i][j]= 'G';
                }if(i==4&&j==13){
                    tabuleiro[i][j]= 'H';
                }

                if(i==10&&j==10){//azul
                    tabuleiro[i][j]= 'I';
                }if(i==11&&j==11){
                    tabuleiro[i][j]= 'J';
                }if(i==12&&j==12){
                    tabuleiro[i][j]= 'K';
                }if(i==13&&j==13){
                    tabuleiro[i][j]= 'L';
                }

                if(i==10&&j==1){//vermelho
                    tabuleiro[i][j]= 'M';
                }if(i==11&&j==2){
                    tabuleiro[i][j]= 'N';
                }if(i==12&&j==3){
                    tabuleiro[i][j]= 'O';
                }if(i==13&&j==4){
                    tabuleiro[i][j]= 'P';
                }
            }
        }
    }
    imprimirTabuleiro(tabuleiro); //MOSTRO O TABULEIRO JA COM AS PEÇAS

    //COMEÇAR O JOGO
    
    if(numjog==2){
        for(i=0;i<15;i++){
            for(j=0;j<15;j++){
                while(win2!=4||win4!=4){
                    srand(time(NULL));
                    for(jg1=2;jg1<=6;jg1=jg1+2){ //CONTAGEM PARA OS JOGADORES 2 E 4 , AMARELO E VERMELHO
                        if(jg1!=6){
                            printf("O dado esta girando!\n");
                            sleep(1);
                            dado=rand()%6+1;
                            Cordado(tabdado,dado); //MOSTRA O DADO
                            printf("\n");
                            movim=0;
                        }
                        if(jg1==2){
                            seis.vermelho=0; //controlador de tres seis seguidos
                            printf("Turno do Amarelo!\nPECAS:EFGH\nTORRES:124680\n");
                            if(dado==6){
                                seis.amarelo++;
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                Cordado(tabdado,dado);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(li==6&&co==7){//SE A PEÇA JA ESTIVER GANHADO
                                    printf("Nao e possivel mover essa peça pois ela ja chegou ao ponto de chegada!");
                                    
                                }
                                if(li==-1&&co==-1){
                                    if(boneco[0]=='E'||boneco[0]=='F'||boneco[0]=='G'||boneco[0]=='H'){
                                        if(torre[3]=='1'||torre[3]=='2'||torre[3]=='4'||torre[4]=='6'||torre[5]=='8'||torre[4]=='0'){
                                            movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                        }    
                                    }
                                }
                                if((li==1&&co==10)||(li==2&&co==11)||(li==3&&co==12)||(li==4&&co==13)){
                                    if((boneco[0]=='E')||(boneco[0]=='F')||(boneco[0]=='G')||(boneco[0]=='H')){
                                        if(tabuleiro[1][8]!=' '){
                                            if((boneco[0]=='E'||boneco[0]=='F') && (tabuleiro[1][8]=='E'||tabuleiro[1][8]=='F')){
                                                tabuleiro[1][8]='1';
                                                torre[3]='1';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='E'||boneco[0]=='G') && (tabuleiro[1][8]=='E'||tabuleiro[1][8]=='G')){
                                                tabuleiro[1][8]='2';
                                                torre[3]='2';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='E'||boneco[0]=='H') && (tabuleiro[1][8]=='E'||tabuleiro[1][8]=='H')){
                                                tabuleiro[1][8]='4';
                                                torre[3]='4';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='F'||boneco[0]=='G') && (tabuleiro[1][8]=='F'||tabuleiro[1][8]=='G')){
                                                tabuleiro[1][8]='6';
                                                torre[4]='6';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='F'||boneco[0]=='H') && (tabuleiro[1][8]=='F'||tabuleiro[1][8]=='H')){
                                                tabuleiro[1][8]='8';
                                                torre[4]='0';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='G'||boneco[0]=='H') && (tabuleiro[1][8]=='G'||tabuleiro[1][8]=='H')){
                                                tabuleiro[1][8]='8';
                                                torre[5]='8';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }
                                        }if(tabuleiro[1][8]==' '){
                                            tabuleiro[1][8]=boneco[0];
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                            jafoi2++;
                                        }
                                    }
                                }
                                else if(boneco[0]=='E'||boneco[0]=='F'||boneco[0]=='G'||boneco[0]=='H'){
                                    movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                    movim=0;
                                }
                                jg1--; // lança novamente o dado, pois repete a vez do jogador
                                if(seis.amarelo==4){
                                    jg1++;
                                }
                            }
                            if(dado!=6&&jafoi2>0){
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(boneco[0]=='E'||boneco[0]=='F'||boneco[0]=='G'||boneco[0]=='H'){
                                    movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                    movim=0;
                                }
                            }
                        }
                        if(jg1==4){
                            seis.amarelo=0;
                            printf("Turno do Vermelho!\nPECAS:MNOP\nTORRES:+=/!?&\n");
                            if(dado==6){
                                seis.vermelho++;
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                Cordado(tabdado,dado);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(li==8&&co==7){//SE A PEÇA JA ESTIVER GANHADO
                                    printf("Nao e possivel mover essa peça pois ela ja chegou ao ponto de chegada!");
                                }
                                if(li==-1&&co==-1){
                                    if(boneco[0]=='M'||boneco[0]=='N'||boneco[0]=='O'||boneco[0]=='P'){
                                        if(torre[9]=='+'||torre[9]=='='||torre[9]=='/'||torre[10]=='!'||torre[10]=='?'||torre[11]=='&'){
                                            movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                        }    
                                    }
                                }
                                if((li==10&&co==1)||(li==11&&co==2)||(li==12&&co==3)||(li==13&&co==4)){
                                    if(tabuleiro[13][6]!=' '){
                                        if((boneco[0]=='M'||boneco[0]=='N') && (tabuleiro[13][6]=='M'||tabuleiro[13][6]=='N')){
                                            tabuleiro[13][6]='+';
                                            torre[9]='+';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }if((boneco[0]=='M'||boneco[0]=='O') && (tabuleiro[13][6]=='M'||tabuleiro[13][6]=='O')){
                                            tabuleiro[13][6]='=';
                                            torre[9]='=';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }if((boneco[0]=='M'||boneco[0]=='P') && (tabuleiro[13][6]=='M'||tabuleiro[13][6]=='P')){
                                            tabuleiro[13][6]='/';
                                            torre[9]='/';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }if((boneco[0]=='N'||boneco[0]=='O') && (tabuleiro[13][6]=='N'||tabuleiro[13][6]=='O')){
                                            tabuleiro[13][6]='!';
                                            torre[10]='!';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }if((boneco[0]=='N'||boneco[0]=='P') && (tabuleiro[13][6]=='N'||tabuleiro[13][6]=='P')){
                                            tabuleiro[13][6]='?';
                                            torre[10]='?';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }if((boneco[0]=='O'||boneco[0]=='P') && (tabuleiro[13][6]=='O'||tabuleiro[13][6]=='P')){
                                            tabuleiro[13][6]='&';
                                            torre[11]='&';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }
                                    }if(tabuleiro[13][6]==' '){
                                        if((boneco[0]=='M')||(boneco[0]=='N')||(boneco[0]=='O')||(boneco[0]=='P')){
                                            tabuleiro[13][6]=boneco[0];
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                            jafoi4++;
                                        }
                                    }
                                }
                                else if(boneco[0]=='M'||boneco[0]=='N'||boneco[0]=='O'||boneco[0]=='P'){
                                    movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                    movim=0;
                                }
                                jg1--; // lança novamente o dado, pois repete a vez do jogador
                                if(seis.vermelho==3){
                                    jg1++;
                                }
                            }
                            if(dado!=6&&jafoi4>0){
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(boneco[0]=='M'||boneco[0]=='N'||boneco[0]=='O'||boneco[0]=='P'){
                                    movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                    movim=0;
                                }
                            }
                        }
                        if(jg1==6){
                            jg1=0;
                        }
                    }
                }
                if(win2==4){
                    printf("O jogador amarelo venceu!!!");
                }
                if(win4==4){
                    printf("O jogador vermelho venceu!!!");
                }
            }
        }
    }
    
    else if(numjog==4){
        for(i=0;i<15;i++){
            for(j=0;j<15;j++){
                while(win1!=4||win2!=4||win3!=4||win4!=4){
                    srand(time(NULL));
                    for(jg1=1;jg1<=5;jg1++){
                        if(jg1>0&&jg1<5){
                            printf("O dado esta girando!\n");
                            sleep(1);
                            dado=rand()%3+4;
                            Cordado(tabdado,dado); //MOSTRA O DADO
                            printf("\n");
                            movim=0;
                        }
                        if(jg1==1){
                            seis.azul=0;
                            seis.vermelho=0;
                            seis.amarelo=0;
                            printf("Turno do Verde!\nPECAS:ABCD\nTORRES:QRSTUV\n");
                            if(dado==6){
                                seis.verde++;
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                Cordado(tabdado,dado);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(li==7&&co==5){//SE A PEÇA JA ESTIVER GANHADO
                                    printf("Nao e possivel mover essa peça pois ela ja chegou ao ponto de chegada!");
                                }
                                if(li==-1&&co==-1){
                                    if(boneco[0]=='A'||boneco[0]=='B'||boneco[0]=='C'||boneco[0]=='D'){
                                        if(torre[0]=='Q'||torre[0]=='R'||torre[0]=='S'||torre[1]=='T'||torre[1]=='U'||torre[3]=='V'){
                                            movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                        }    
                                    }
                                }else if((li==1&&co==1)||(li==2&&co==2)||(li==3&&co==3)||(li==4&&co==4)){
                                    if((boneco[0]=='A')||(boneco[0]=='B')||(boneco[0]=='C')||(boneco[0]=='D')){
                                        if(tabuleiro[6][1]!=' '){
                                            if((boneco[0]=='A'||boneco[0]=='B') && (tabuleiro[6][1]=='A'||tabuleiro[6][1]=='B')){
                                                tabuleiro[6][1]='Q';
                                                torre[0]='Q';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='A'||boneco[0]=='C') && (tabuleiro[6][1]=='A'||tabuleiro[6][1]=='C')){
                                                tabuleiro[6][1]='R';
                                                torre[0]='R';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='A'||boneco[0]=='D') && (tabuleiro[6][1]=='A'||tabuleiro[6][1]=='D')){
                                                tabuleiro[6][1]='S';
                                                torre[0]='S';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='B'||boneco[0]=='C') && (tabuleiro[6][1]=='B'||tabuleiro[6][1]=='C')){
                                                tabuleiro[6][1]='T';
                                                tabuleiro[li][co]=' ';
                                                torre[1]='T';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='B'||boneco[0]=='D') && (tabuleiro[6][1]=='B'||tabuleiro[6][1]=='D')){
                                                tabuleiro[6][1]='V';
                                                torre[1]='V';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='C'||boneco[0]=='D') && (tabuleiro[6][1]=='C'||tabuleiro[6][1]=='D')){
                                                tabuleiro[6][1]='U';
                                                torre[2]='U';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }
                                        }if(tabuleiro[6][1]==' '){
                                            tabuleiro[6][1]=boneco[0];
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                            jafoi++;
                                        }
                                    }
                                }else if(boneco[0]=='A'||boneco[0]=='B'||boneco[0]=='C'||boneco[0]=='D'){
                                movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                movim=0;
                                }
                                jg1--; // lança novamente o dado, pois repete a vez do jogador
                                if(seis.verde==4){
                                    jg1++;
                                }
                                printf("%d\n",seis.verde);
                            }
                            if(dado!=6&&jafoi>0){
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(boneco[0]=='A'||boneco[0]=='B'||boneco[0]=='C'||boneco[0]=='D'){
                                    printf("td certo\n");
                                    movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                    movim=0;
                                }
                            }
                        }if(jg1==2){
                            seis.verde=0;
                            seis.azul=0;
                            seis.vermelho=0;
                            printf("Turno do Amarelo!\nPECAS:EFGH\nTORRES:124680\n");
                            if(dado==6){
                                seis.amarelo++;
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                Cordado(tabdado,dado);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(li==6&&co==7){//SE A PEÇA JA ESTIVER GANHADO
                                    printf("Nao e possivel mover essa peça pois ela ja chegou ao ponto de chegada!");
                                }
                                if(li==-1&&co==-1){
                                    if(boneco[0]=='E'||boneco[0]=='F'||boneco[0]=='G'||boneco[0]=='H'){
                                        if(torre[3]=='1'||torre[3]=='2'||torre[3]=='4'||torre[4]=='6'||torre[5]=='8'||torre[4]=='0'){
                                            movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                        }    
                                    }
                                }
                                if((li==1&&co==10)||(li==2&&co==11)||(li==3&&co==12)||(li==4&&co==13)){
                                    if((boneco[0]=='E')||(boneco[0]=='F')||(boneco[0]=='G')||(boneco[0]=='H')){
                                        if(tabuleiro[1][8]!=' '){
                                            if((boneco[0]=='E'||boneco[0]=='F') && (tabuleiro[1][8]=='E'||tabuleiro[1][8]=='F')){
                                                tabuleiro[1][8]='1';
                                                torre[3]='1';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='E'||boneco[0]=='G') && (tabuleiro[1][8]=='E'||tabuleiro[1][8]=='G')){
                                                tabuleiro[1][8]='2';
                                                torre[3]='2';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='E'||boneco[0]=='H') && (tabuleiro[1][8]=='E'||tabuleiro[1][8]=='H')){
                                                tabuleiro[1][8]='4';
                                                torre[3]='4';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='F'||boneco[0]=='G') && (tabuleiro[1][8]=='F'||tabuleiro[1][8]=='G')){
                                                tabuleiro[1][8]='6';
                                                torre[4]='6';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='F'||boneco[0]=='H') && (tabuleiro[1][8]=='F'||tabuleiro[1][8]=='H')){
                                                tabuleiro[1][8]='8';
                                                torre[4]='0';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='G'||boneco[0]=='H') && (tabuleiro[1][8]=='G'||tabuleiro[1][8]=='H')){
                                                tabuleiro[1][8]='8';
                                                torre[5]='8';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }
                                        }if(tabuleiro[1][8]==' '){
                                            tabuleiro[1][8]=boneco[0];
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                            jafoi2++;
                                        }
                                    }
                                }
                                else if(boneco[0]=='E'||boneco[0]=='F'||boneco[0]=='G'||boneco[0]=='H'){
                                    movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                    movim=0;
                                }
                                jg1--; // lança novamente o dado, pois repete a vez do jogador
                                if(seis.amarelo==3){
                                    jg1++;
                                }
                            }
                            if(dado!=6&&jafoi2>0){
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(boneco[0]=='E'||boneco[0]=='F'||boneco[0]=='G'||boneco[0]=='H'){
                                    movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                    movim=0;
                                }
                            }
                        }if(jg1==3){
                            seis.verde=0;
                            seis.vermelho=0;
                            seis.amarelo=0;
                            printf("Turno do Azul!\nPECAS:IJKL\nTORRES:WXYZ79\n");
                            if(dado==6){
                                seis.azul++;
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                Cordado(tabdado,dado);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(li==7&&co==8){//SE A PEÇA JA ESTIVER GANHADO
                                    printf("Nao e possivel mover essa peça pois ela ja chegou ao ponto de chegada!");
                                }
                                if(li==-1&&co==-1){
                                    if(boneco[0]=='I'||boneco[0]=='J'||boneco[0]=='K'||boneco[0]=='L'){
                                        if(torre[6]=='W'||torre[6]=='X'||torre[6]=='Y'||torre[7]=='Z'||torre[7]=='7'||torre[8]=='9'){
                                            movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                        }    
                                    }
                                }
                                if((li==10&&co==10)||(li==11&&co==11)||(li==12&&co==12)||(li==13&&co==13)){
                                    if((boneco[0]=='I')||(boneco[0]=='J')||(boneco[0]=='K')||(boneco[0]=='L')){
                                        if(tabuleiro[8][13]!=' '){
                                            if((boneco[0]=='I'||boneco[0]=='J') && (tabuleiro[8][13]=='I'||tabuleiro[8][13]=='J')){
                                                tabuleiro[8][13]='W';
                                                torre[6]='W';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='I'||boneco[0]=='K') && (tabuleiro[8][13]=='I'||tabuleiro[8][13]=='K')){
                                                tabuleiro[8][13]='X';
                                                torre[6]='X';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='I'||boneco[0]=='L') && (tabuleiro[8][13]=='I'||tabuleiro[8][13]=='L')){
                                                tabuleiro[8][13]='Y';
                                                torre[6]='Y';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='J'||boneco[0]=='K') && (tabuleiro[8][13]=='J'||tabuleiro[8][13]=='K')){
                                                tabuleiro[8][13]='Z';
                                                torre[7]='Z';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='J'||boneco[0]=='L') && (tabuleiro[8][13]=='J'||tabuleiro[8][13]=='L')){
                                                tabuleiro[8][13]='7';
                                                torre[7]='7';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }if((boneco[0]=='K'||boneco[0]=='L') && (tabuleiro[8][13]=='K'||tabuleiro[8][13]=='L')){
                                                tabuleiro[8][13]='9';
                                                torre[8]='9';
                                                tabuleiro[li][co]=' ';
                                                imprimirTabuleiro(tabuleiro);
                                            }
                                        }if(tabuleiro[8][13]==' '){
                                            tabuleiro[8][13]=boneco[0];
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                            jafoi3++;
                                        }
                                    }
                                }
                                else if(boneco[0]=='I'||boneco[0]=='J'||boneco[0]=='K'||boneco[0]=='L'){
                                    movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                    movim=0;
                                }
                                jg1--; // lança novamente o dado, pois repete a vez do jogador
                                if(seis.azul==3){
                                    jg1++;
                                }
                            }
                            if(dado!=6&&jafoi3>0){
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(boneco[0]=='I'||boneco[0]=='J'||boneco[0]=='K'||boneco[0]=='L'){
                                    movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                    movim=0;
                                }
                            }
                        }if(jg1==4){
                            seis.verde=0;
                            seis.azul=0;
                            seis.amarelo=0;
                            printf("Turno do Vermelho!\nPECAS:MNOP\nTORRES:+=/!?&\n");
                            if(dado==6){
                                seis.vermelho++;
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                Cordado(tabdado,dado);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(li==8&&co==7){//SE A PEÇA JA ESTIVER GANHADO
                                    printf("Nao e possivel mover essa peça pois ela ja chegou ao ponto de chegada!");
                                }
                                if(li==-1&&co==-1){
                                    if(boneco[0]=='M'||boneco[0]=='N'||boneco[0]=='O'||boneco[0]=='P'){
                                        if(torre[9]=='+'||torre[9]=='='||torre[9]=='/'||torre[10]=='!'||torre[10]=='?'||torre[11]=='&'){
                                            movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                        }    
                                    }
                                }
                                if((li==10&&co==1)||(li==11&&co==2)||(li==12&&co==3)||(li==13&&co==4)){
                                    if(tabuleiro[13][6]!=' '){
                                        if((boneco[0]=='M'||boneco[0]=='N') && (tabuleiro[13][6]=='M'||tabuleiro[13][6]=='N')){
                                            tabuleiro[13][6]='+';
                                            torre[9]='+';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }if((boneco[0]=='M'||boneco[0]=='O') && (tabuleiro[13][6]=='M'||tabuleiro[13][6]=='O')){
                                            tabuleiro[13][6]='=';
                                            torre[9]='=';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }if((boneco[0]=='M'||boneco[0]=='P') && (tabuleiro[13][6]=='M'||tabuleiro[13][6]=='P')){
                                            tabuleiro[13][6]='/';
                                            torre[9]='/';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }if((boneco[0]=='N'||boneco[0]=='O') && (tabuleiro[13][6]=='N'||tabuleiro[13][6]=='O')){
                                            tabuleiro[13][6]='!';
                                            torre[10]='!';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }if((boneco[0]=='N'||boneco[0]=='P') && (tabuleiro[13][6]=='N'||tabuleiro[13][6]=='P')){
                                            tabuleiro[13][6]='?';
                                            torre[10]='?';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }if((boneco[0]=='O'||boneco[0]=='P') && (tabuleiro[13][6]=='O'||tabuleiro[13][6]=='P')){
                                            tabuleiro[13][6]='&';
                                            torre[11]='&';
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                        }
                                    }if(tabuleiro[13][6]==' '){
                                        if((boneco[0]=='M')||(boneco[0]=='N')||(boneco[0]=='O')||(boneco[0]=='P')){
                                            tabuleiro[13][6]=boneco[0];
                                            tabuleiro[li][co]=' ';
                                            imprimirTabuleiro(tabuleiro);
                                            jafoi4++;
                                        }
                                    }
                                }
                                else if(boneco[0]=='M'||boneco[0]=='N'||boneco[0]=='O'||boneco[0]=='P'){
                                    movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                    movim=0;
                                }
                                jg1--; // lança novamente o dado, pois repete a vez do jogador
                                if(seis.vermelho==3){
                                    jg1++;
                                }
                            }
                            if(dado!=6&&jafoi4>0){
                                imprimirTabuleiro(tabuleiro);
                                printf("\n");
                                printf("Digite qual boneco deseja mover: \n");
                                fgets(boneco,3,stdin);
                                boneco[strlen(boneco)-1] = '\0';
                                printf("\n");
                                li=-1;
                                co=-1;
                                for(x=0;x<15;x++){
                                    for(y=0;y<15;y++){
                                        if(tabuleiro[x][y]==boneco[0]){
                                            li=x;
                                            co=y;
                                        }
                                    }
                                }
                                if(boneco[0]=='M'||boneco[0]=='N'||boneco[0]=='O'||boneco[0]=='P'){
                                    movimento(tabuleiro,boneco,dado,&jg1,&movim,&win1,&win2,&win3,&win4,&li,&co,torre,numjog);
                                    movim=0;
                                }
                            }
                        }
                    }
                }
                if(win1==4){
                    for(i=0;i<4;i++){
                        if(jog[i].cor==1){
                        printf("O jogador %d ganhou!",i+1);
                        }
                    }
                }if(win2==4){
                    for(i=0;i<4;i++){
                        if(jog[i].cor==2){
                        printf("O jogador %d ganhou!",i+1);
                        }
                    }
                }if(win3==4){
                    for(i=0;i<4;i++){
                        if(jog[i].cor==3){
                        printf("O jogador %d ganhou!",i+1);
                        }
                    }
                }if(win4==4){
                    for(i=0;i<4;i++){
                        if(jog[i].cor==4){
                        printf("O jogador %d ganhou!",i+1);
                        }
                    }
                }
            }
        }
    }

    printf("ESSE FOI O JOGO LUDO!\nJOGUE NOVAMENTE!");
    
    return 0;
}

void imprimirTabuleiro(char tabuleiro[][15]) {
    int i, j;
    for(i=0;i<15;i++){
        for(j=0;j<15;j++){

            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            SMALL_RECT rect;
            rect.Left = 0;
            rect.Top = 0;
            rect.Right = 89;
            rect.Bottom = 29;

            SetConsoleWindowInfo(console, TRUE, &rect);
            // CASAS DA BASE( ONDE OS PEOS FICAM ANTES DE JG)

            if((i==10&&j==1)||(i==11&&j==2)||(i==12&&j==3)|(i==13&&j==4)){ //inferior esquerd
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_BLUE | BACKGROUND_GREEN);
                printf("%c",tabuleiro[i][j]);
            }
            else if((i==1&&j==1)||(i==2&&j==2)||(i==3&&j==3)||(i==4&&j==4)){ // superior esquerdo
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |  BACKGROUND_BLUE | BACKGROUND_GREEN);
                printf("%c",tabuleiro[i][j]);
            }
            else if((i==1&&j==10)||(i==2&&j==11)||(i==3&&j==12)||(i==4&&j==13)){ // superior direito
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN);
                printf("%c",tabuleiro[i][j]);
            }
            else if((i==10&&i==j)||(i==11&&i==j)||(i==12&&i==j)||(i==13&&i==j)){ // inferior direito
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |  BACKGROUND_BLUE | BACKGROUND_GREEN);
                printf("%c",tabuleiro[i][j]);
            }

            //PRINCIPAL - BASE E CAMINHOS
            else if((i<=5&&j<=5)||(i==6&&j==1)||(j>=1&&i==7&&j<=6)){ // canto superior esquerdo e caminho do verde
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_GREEN);
                printf("%c",tabuleiro[i][j]);
            } else if((i<=5&&j>=9)||(i==1&&j==8)||(i>=1&&j==7&&i<=6)){ // canto superior direito e caminho do amarelo
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
                printf("%c",tabuleiro[i][j]);
            } else if((i>=9&&j<=5)||(i==13&&j==6)||(i<=13&&j==7&&i>=8)){ // canto inferior esquerdo e caminho do vermelho
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED );
                printf("%c",tabuleiro[i][j]);
            } else if((i>=9&&j>=9)||(i==8&&j==13)||(j<=13&&i==7&&j>=8)){ // canto inferior direito e caminho do azul
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_BLUE);
                printf("%c",tabuleiro[i][j]);
            }
            // FIM DA PRINCIPAL
            // MEIO
            else if((i==6&&j==6)||(i==6&&j==8)||(i==8&&j==6)||(i==8&&j==8)||(i==7&&j==7)){ // CASAS MEIO
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);
                printf("%c",tabuleiro[i][j]);
            }
            //CASAS SEGURAS
            else if((i==2&&j==6)||(i==6&&j==12)||(i==8&&j==2)||(i==12&&j==8)){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);
                printf("%c",tabuleiro[i][j]);
            }
            else{
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                printf("%c",tabuleiro[i][j]);
            }
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        printf("\n");
    }
};

void Cordado(char tabdado[][3],int dado) {
    int i,j;

    for(i=0;i<3;i++){
        for(j=0;j<3;j++){

            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

            SMALL_RECT rect;
            rect.Left = 0;
            rect.Top = 0;
            rect.Right = 79;
            rect.Bottom = 29;

            SetConsoleWindowInfo(console, TRUE, &rect);
            // CASAS DA BASE( ONDE OS PEOS FICAM ANTES DE JG)
            
            if(dado==1){
                if(i==1&&j==1){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_RED);
                    printf("%c", tabdado[i][j]);
                }else{
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_BLUE);
                    printf("%c", tabdado[i][j]);
                }
            }
            if(dado==2){
                if((i==1&&j==0 )||(i==1&&j==2)){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_RED);
                    printf("%c", tabdado[i][j]);
                }else{
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_BLUE);
                    printf("%c", tabdado[i][j]);
                }
            }
            if(dado==3){
                if((i==0&&j==0) || (i==1&&j==1)|| (i==2&&j==2)){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_RED);
                    printf("%c", tabdado[i][j]);
                }else{
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_BLUE);
                    printf("%c", tabdado[i][j]);
                }
            }
            if(dado==4){
                if((i==0&&j==1) || (i==1&&j==0)||(i==1&&j==2)|| (i==2&&j==1)){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_RED);
                    printf("%c", tabdado[i][j]);
                }else{
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_BLUE);
                    printf("%c", tabdado[i][j]);
                }
            }
            if(dado==5){
                if((i==0&&j==0) || (i==0&&j==2)||(i==1&&j==1)|| (i==2&&j==0)|| (i==2&&j==2)){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_RED);
                    printf("%c", tabdado[i][j]);
                }else{
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_BLUE);
                    printf("%c", tabdado[i][j]);
                }
            }
            if(dado==6){
                if((i==0&&j==0) || (i==0&&j==2)||(i==1&&j==0)||(i==1&&j==2)|| (i==2&&j==0)|| (i==2&&j==2)){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_RED);
                    printf("%c", tabdado[i][j]);
                }else{
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_INTENSITY |BACKGROUND_BLUE);
                    printf("%c", tabdado[i][j]);
                }
            }
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        printf("\n");
    }
};

void movimento(char tabuleiro[][15],char *boneco,int dado,int *jg1,int *mov,int *win1,int *win2,int *win3,int *win4,int *li,int *co,char *torre,int numjog){

    int x,y;
    char novotabuleiro[15][15];
    int liant=0,coant=0;

    for (x = 0; x < 15; x++) {
        for (y = 0; y < 15; y++) {
            novotabuleiro[x][y] = tabuleiro[x][y];
        }
    }
    *li=-1;
    *co=-1;
    for(x=0;x<15;x++){
        for(y=0;y<15;y++){
            if(tabuleiro[x][y]==boneco[0]){
                (*li)=x;
                (*co)=y;
                liant=x;   //GUARDA ONDE TA MINHA PEÇA ANTES DE MECHER
                coant=y;
                break;
            }
        }
    }

    if(*li==-1&&*co==-1){
        desfaztorre(tabuleiro,novotabuleiro,boneco,torre,li,co,liant,coant);
    }

    if(*win1!=4&&*li!=-1&&*co!=-1){
        if(*jg1==1){
            if ((*li != 1 || *co != 1) && (*li != 2 || *co != 2) && (*li != 3 || *co != 3) && (*li != 4 || *co != 4)) { // não está na casa de início
                while(*mov!=dado&&*mov<dado){
                    printf("Li=%d co=%d",*li,*co);
                    if(*co==0&&*li==8){  //condiçoes de subir
                        movimentocima(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*co==6&&(*li==14||*li==13||*li==12||*li==11||*li==10||*li==1||*li==2||*li==3||*li==4||*li==5)){
                        movimentocima(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if((*li==0&&*co==6)||(*li==0&&*co==7)){//condiçoes de direita
                        movimentodireita(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*li==6&&(*co==0||*co==1||*co==2||*co==3||*co==4||*co==9||*co==10||*co==11||*co==12||*co==13)){
                        movimentodireita(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if((*co==14&&*li==6)||(*co==14&&*li==7)){//condições de descer
                        movimentobaixo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*co==8&&(*li==0||*li==1||*li==2||*li==3||*li==4||*li==9||*li==10||*li==11||*li==12||*li==13)){
                        movimentobaixo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if((*li==14&&*co==8)||(*li==14&&*co==7)){//comando esquerda
                        movimentoesquerda(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*li==8&&(*co==14||*co==13||*co==12||*co==11||*co==10||*co==1||*co==2||*co==3||*co==4||*co==5)){
                        movimentoesquerda(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }//nao passa, condições de pulo
                    else if((*li==6&&*co==5)||(*li==5&&*co==8)||(*li==8&&*co==9)||(*li==9&&*co==6)){
                        movimentopulo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }

                    //caminho da vitoria verde
                    else if((*li==7&&*co==0&&dado<=6)||(*li==7&&*co==1&&dado<=5)||(*li==7&&*co==2&&dado<=4)||(*li==7&&*co==3&&dado<=3)||(*li==7&&*co==4&&dado<=2)||(*li==7&&*co==5&&dado==1)){
                        movimentovitoriaverde(tabuleiro,boneco,dado,li,co,mov,win1,novotabuleiro,liant,coant,torre);
                        if(numjog==2){
                            *jg1=*jg1-2;
                        }
                        if(numjog==4){
                            (*jg1)--;
                        }
                    }
                    else{
                        return;
                    }
                }
                if(*mov>dado){
                    return;
                }
            }
        }
    }
    if(*win2!=4&&*li!=-1&&*co!=-1){
        if(*jg1==2){
            if ((*li!=1||*co!=10)&&(*li!=2||*co!=11)&&(*li!=3||*co!=12)&&(*li!=4||*co!=13)) {
                while(*mov!=dado&&*mov<dado){
                    printf("Li=%d co=%d",*li,*co);
                    if((*co==0&&*li==8)||(*co==0&&*li==7)){  //condiçoes de subir
                        movimentocima(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*co==6&&(*li==14||*li==13||*li==12||*li==11||*li==10||*li==1||*li==2||*li==3||*li==4||*li==5)){
                        movimentocima(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if((*li==0&&*co==6)){//condiçoes de direita
                        movimentodireita(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*li==6&&(*co==0||*co==1||*co==2||*co==3||*co==4||*co==9||*co==10||*co==11||*co==12||*co==13)){
                        movimentodireita(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if((*co==14&&*li==6)||(*co==14&&*li==7)){//condições de descer
                        movimentobaixo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*co==8&&(*li==0||*li==1||*li==2||*li==3||*li==4||*li==9||*li==10||*li==11||*li==12||*li==13)){
                        movimentobaixo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if((*li==14&&*co==8)||(*li==14&&*co==7)){//comando esquerda
                        movimentoesquerda(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*li==8&&(*co==14||*co==13||*co==12||*co==11||*co==10||*co==1||*co==2||*co==3||*co==4||*co==5)){
                        movimentoesquerda(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }//nao passa, condições de pulo
                    else if((*li==6&&*co==5)||(*li==5&&*co==8)||(*li==8&&*co==9)||(*li==9&&*co==6)){
                        movimentopulo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    //caminho da vitoria amarelo
                    else if((*li==0&&*co==7&&dado<=6)||(*li==1&&*co==7&&dado<=5)||(*li==2&&*co==7&&dado<=4)||(*li==3&&*co==7&&dado<=3)||(*li==4&&*co==7&&dado<=2)||(*li==5&&*co==7&&dado<=1)){
                        movimentovitoriaamarelo(tabuleiro,boneco,dado,li,co,mov,win2,novotabuleiro,liant,coant,torre);
                        if(numjog==2){
                            *jg1=*jg1-2;
                        }
                        if(numjog==4){
                            (*jg1)--;
                        }
                    }
                    else{
                        return;
                    }
                }
                if(*mov>dado){
                    return;
                }
            }
        }
    }
    if(*win3!=4&&*li!=-1&&*co!=-1){
        if(*jg1==3){
            if ((*li != 10 || *co != 10) && (*li != 11 || *co != 11) && (*li != 12 || *co != 12) && (*li != 13 || *co != 13)) {
                while(*mov!=dado&&*mov<dado){
                    if((*co==0&&*li==8)||(*co==0&&*li==7)){  //condiçoes de subir
                        movimentocima(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*co==6&&(*li==14||*li==13||*li==12||*li==11||*li==10||*li==1||*li==2||*li==3||*li==4||*li==5)){
                        movimentocima(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if((*li==0&&*co==6)||(*li==0&&*co==7)){//condiçoes de direita
                        movimentodireita(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*li==6&&(*co==0||*co==1||*co==2||*co==3||*co==4||*co==9||*co==10||*co==11||*co==12||*co==13)){
                        movimentodireita(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*co==14&&*li==6){//condições de descer
                        movimentobaixo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*co==8&&(*li==0||*li==1||*li==2||*li==3||*li==4||*li==9||*li==10||*li==11||*li==12||*li==13)){
                        movimentobaixo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if((*li==14&&*co==8)||(*li==14&&*co==7)){//comando esquerda
                        movimentoesquerda(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*li==8&&(*co==14||*co==13||*co==12||*co==11||*co==10||*co==1||*co==2||*co==3||*co==4||*co==5)){
                        movimentoesquerda(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }//nao passa, condições de pulo
                    
                    else if((*li==6&&*co==5)||(*li==5&&*co==8)||(*li==8&&*co==9)||(*li==9&&*co==6)){
                        movimentopulo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    //caminho da vitoria azul
                    else if ((*li==7&&*co==14&&dado<=6)||(*li==7&&*co==13&&dado<=5)||(*li==7&&*co==12&&dado<=4)||(*li==7&&*co==11&&dado<=3)||(*li==7&&*co==10&&dado<=2)||(*li==7&&*co==9&&dado<=1)){
                        movimentovitoriaazul(tabuleiro,boneco,dado,li,co,mov,win3,novotabuleiro,liant,coant,torre);
                        if(numjog==2){
                            *jg1=*jg1-2;
                        }
                        if(numjog==4){
                            (*jg1)--;
                        }
                    }
                    else{
                        return;
                    }
                }
                if(*mov>dado){
                    return;
                }
            }
        }
    }
    if(*win4!=4&&*li!=-1&&*co!=-1){
        if(*jg1==4){
            if ((*li != 10 || *co != 1) && (*li != 11 || *co != 2) && (*li != 12 || *co != 3) && (*li != 13 || *co != 4)) {
                while(*mov!=dado&&*mov<dado){
                    if((*co==0&&*li==8)||(*co==0&&*li==7)){  //condiçoes de subir
                        movimentocima(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*co==6&&(*li==14||*li==13||*li==12||*li==11||*li==10||*li==1||*li==2||*li==3||*li==4||*li==5)){
                        movimentocima(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if((*li==0&&*co==6)||(*li==0&&*co==7)){//condiçoes de direita
                        movimentodireita(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*li==6&&(*co==0||*co==1||*co==2||*co==3||*co==4||*co==9||*co==10||*co==11||*co==12||*co==13)){
                        movimentodireita(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if((*co==14&&*li==6)||(*co==14&&*li==7)){//condições de descer
                        movimentobaixo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*co==8&&(*li==0||*li==1||*li==2||*li==3||*li==4||*li==9||*li==10||*li==11||*li==12||*li==13)){
                        movimentobaixo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*li==14&&*co==8){//comando esquerda
                        movimentoesquerda(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    else if(*li==8&&(*co==14||*co==13||*co==12||*co==11||*co==10||*co==1||*co==2||*co==3||*co==4||*co==5)){
                        movimentoesquerda(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }//nao passa, condições de pulo
                    
                    else if((*li==6&&*co==5)||(*li==5&&*co==8)||(*li==8&&*co==9)||(*li==9&&*co==6)){
                        movimentopulo(tabuleiro,boneco,dado,li,co,mov,jg1,novotabuleiro,liant,coant,torre,numjog);
                    }
                    
                    //caminho da vitoria vermelho
                    else if((*li==14&&*co==7&&dado<=6)||(*li==13&&*co==7&&dado<=5)||(*li==12&&*co==7&&dado<=4)||(*li==11&&*co==7&&dado<=3)||(*li==10&&*co==7&&dado<=2)||(*li==9&&*co==7&&dado==1)){
                        movimentovitoriavermelho(tabuleiro,boneco,dado,li,co,mov,win4,novotabuleiro,liant,coant,torre);
                        if(numjog==2){
                            *jg1=*jg1-2;
                        }
                        if(numjog==4){
                            (*jg1)--;
                        }
                    }
                    else{
                        return;
                    }
                }
                if(*mov>dado){
                    return;
                }
            }
        }
    }
};

void movimentocima(char tabuleiro[][15],char *boneco,int dado,int *li,int *co,int *mov,int *jg1,char novotabuleiro[][15],int liant,int coant,char *torre,int numjog){

    int x,y,a=0,entroutorre;
    char bonecocomido[3];
    entroutorre=0;

    if(*co==0&&*li==8){
        while(*mov!=dado&&*mov<dado&&a<1){
            tabuleiro[8][0]=' ';
            tabuleiro[7][0]=boneco[0];
            (*mov)++;
            *li=7;
            *co=0;
            a++;
        }
    }
    a=0;
    if(*co==0&&*li==7&&*jg1!=1){
        while(*mov!=dado&&*mov<dado&&a<1){
            tabuleiro[7][0]=' ';
            tabuleiro[6][0]=boneco[0];
            (*mov)++;
            *li=6;
            *co=0;
            a++;
        }
    }
    if(*co==6){
        if(*li==14||*li==13||*li==12||*li==11||*li==10||*li==1||*li==2||*li==3||*li==4||*li==5){
            while ((*mov != dado && *mov < dado && *li <= 14 && *li > 9) || (*mov != dado && *mov < dado && *li <= 5 && *li > 0)) {
                *li=-1;
                *co=-1;
                for(x=0;x<15;x++){
                    for(y=0;y<15;y++){
                        if(tabuleiro[x][y]==boneco[0]){
                            *li=x;
                            *co=y;
                        }
                        
                    }
                }
                tabuleiro[*li][*co]=' ';
                (*li)--;
                *co=6;
                tabuleiro[*li][*co]=boneco[0];
                (*mov)++;
            }
        }
    }
    if(*mov==dado){
        for (x = 0; x < 15; x++) {
            for (y = 0; y < 15; y++) {
                tabuleiro[x][y]=novotabuleiro[x][y];
            }
        }
        tabuleiro[liant][coant]=' ';//TEM AS EXCESSOES COMO: CASA SEGURA E TORRES
        tabuleiro[*li][*co]=boneco[0];
        if(novotabuleiro[*li][*co]!=' '/*&&((*li!=2&&*co!=6)||(*li!=6&&*co!=12)||(*li!=12&&*co!=8)||(*li!=8&&*co!=2)||(*li!=6&&*co!=1)||(*li!=1&&*co!=8)||(*li!=8&&*co!=13)||(*li!=13&&*co!=6))*/){//COMER PEÇAS TIRANDO AS CASAS SEGURAS
            if((novotabuleiro[*li][*co]=='A'&&*jg1!=1)||(novotabuleiro[*li][*co]=='B'&&*jg1!=1)||(novotabuleiro[*li][*co]=='C'&&*jg1!=1)||(novotabuleiro[*li][*co]=='D'&&*jg1!=1)||(novotabuleiro[*li][*co]=='E'&&*jg1!=2)||(novotabuleiro[*li][*co]=='F'&&*jg1!=2)||(novotabuleiro[*li][*co]=='G'&&*jg1!=2)||(novotabuleiro[*li][*co]=='H'&&*jg1!=2)||(novotabuleiro[*li][*co]=='I'&&*jg1!=3)||(novotabuleiro[*li][*co]=='J'&&*jg1!=3)||(novotabuleiro[*li][*co]=='K'&&*jg1!=3)||(novotabuleiro[*li][*co]=='L'&&*jg1!=3)||(novotabuleiro[*li][*co]=='M'&&*jg1==4)||(novotabuleiro[*li][*co]=='N'&&*jg1==4)||(novotabuleiro[*li][*co]=='O'&&*jg1==4)||(novotabuleiro[*li][*co]=='P'&&*jg1==4)){
                bonecocomido[0]=novotabuleiro[*li][*co];
                comer(tabuleiro,bonecocomido,jg1,numjog);
            }
        }
        if((novotabuleiro[*li][*co]=='A'&&*jg1==1)||(novotabuleiro[*li][*co]=='B'&&*jg1==1)||(novotabuleiro[*li][*co]=='C'&&*jg1==1)||(novotabuleiro[*li][*co]=='D'&&*jg1==1)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreABCD(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='E'&&*jg1==2)||(novotabuleiro[*li][*co]=='F'&&*jg1==2)||(novotabuleiro[*li][*co]=='G'&&*jg1==2)||(novotabuleiro[*li][*co]=='H'&&*jg1==2)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreEFGH(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='I'&&*jg1==3)||(novotabuleiro[*li][*co]=='J'&&*jg1==3)||(novotabuleiro[*li][*co]=='K'&&*jg1==3)||(novotabuleiro[*li][*co]=='L'&&*jg1==3)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreIJKL(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='M'&&*jg1==4)||(novotabuleiro[*li][*co]=='N'&&*jg1==4)||(novotabuleiro[*li][*co]=='O'&&*jg1==4)||(novotabuleiro[*li][*co]=='P'&&*jg1==4)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreMNOP(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if(entroutorre==0){
            imprimirTabuleiro(tabuleiro);
        }
    }
};

void movimentodireita(char tabuleiro[][15], char *boneco,int dado,int *li,int *co,int *mov,int *jg1,char novotabuleiro[][15],int liant,int coant,char *torre,int numjog){

    int x,y,a=0,entroutorre;
    char bonecocomido[3];
    entroutorre=0;

    if(*li==0&&*co==6){
        while(*mov!=dado&&*mov<dado&&*co<8&&a<1){
            tabuleiro[0][6]=' ';
            tabuleiro[0][7]=boneco[0];
            (*mov)++;
            *li=0;
            *co=7;
            a++;
        }
    }
    a=0;
    if(*co==7&&*li==0&&*jg1!=2){
        while(*mov!=dado&&*mov<dado&&a<1){
            tabuleiro[0][7]=' ';
            tabuleiro[0][8]=boneco[0];
            (*mov)++;
            *li=0;
            *co=8;
            a++;
        }
    }
    if(*li==6){
        if(*co==0||*co==1||*co==2||*co==3||*co==4||*co==9||*co==10||*co==11||*co==12||*co==13){
            while ((*mov != dado && *mov < dado && (*co >= 0 && *co < 5)) || (*mov != dado && *mov < dado && (*co >= 9 && *co < 14))){
                *li=-1;
                *co=-1;
                for(x=0;x<15;x++){
                    for(y=0;y<15;y++){
                        if(tabuleiro[x][y]==boneco[0]){
                            *li=x;
                            *co=y;
                        }
                    }
                }
                tabuleiro[*li][*co]=' ';
                *li=6;
                (*co)++;
                tabuleiro[*li][*co]=boneco[0];
                (*mov)++;
            }
        }
    }
    if(*mov==dado){
        for (x = 0; x < 15; x++) {
            for (y = 0; y < 15; y++) {
                tabuleiro[x][y]=novotabuleiro[x][y];
            }
        }
        tabuleiro[liant][coant]=' ';//TEM AS EXCESSOES COMO: CASA SEGURA E TORRES
        tabuleiro[*li][*co]=boneco[0];
        if(novotabuleiro[*li][*co]!=' '/*&&((*li!=2&&*co!=6)||(*li!=6&&*co!=12)||(*li!=12&&*co!=8)||(*li!=8&&*co!=2)||(*li!=6&&*co!=1)||(*li!=1&&*co!=8)||(*li!=8&&*co!=13)||(*li!=13&&*co!=6))*/){//COMER PEÇAS TIRANDO AS CASAS SEGURAS
            if((novotabuleiro[*li][*co]=='A'&&*jg1!=1)||(novotabuleiro[*li][*co]=='B'&&*jg1!=1)||(novotabuleiro[*li][*co]=='C'&&*jg1!=1)||(novotabuleiro[*li][*co]=='D'&&*jg1!=1)||(novotabuleiro[*li][*co]=='E'&&*jg1!=2)||(novotabuleiro[*li][*co]=='F'&&*jg1!=2)||(novotabuleiro[*li][*co]=='G'&&*jg1!=2)||(novotabuleiro[*li][*co]=='H'&&*jg1!=2)||(novotabuleiro[*li][*co]=='I'&&*jg1!=3)||(novotabuleiro[*li][*co]=='J'&&*jg1!=3)||(novotabuleiro[*li][*co]=='K'&&*jg1!=3)||(novotabuleiro[*li][*co]=='L'&&*jg1!=3)||(novotabuleiro[*li][*co]=='M'&&*jg1==4)||(novotabuleiro[*li][*co]=='N'&&*jg1==4)||(novotabuleiro[*li][*co]=='O'&&*jg1==4)||(novotabuleiro[*li][*co]=='P'&&*jg1==4)){
                bonecocomido[0]=novotabuleiro[*li][*co];
                comer(tabuleiro,bonecocomido,jg1,numjog);
            }
        }
        if((novotabuleiro[*li][*co]=='A'&&*jg1==1)||(novotabuleiro[*li][*co]=='B'&&*jg1==1)||(novotabuleiro[*li][*co]=='C'&&*jg1==1)||(novotabuleiro[*li][*co]=='D'&&*jg1==1)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreABCD(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='E'&&*jg1==2)||(novotabuleiro[*li][*co]=='F'&&*jg1==2)||(novotabuleiro[*li][*co]=='G'&&*jg1==2)||(novotabuleiro[*li][*co]=='H'&&*jg1==2)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreEFGH(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='I'&&*jg1==3)||(novotabuleiro[*li][*co]=='J'&&*jg1==3)||(novotabuleiro[*li][*co]=='K'&&*jg1==3)||(novotabuleiro[*li][*co]=='L'&&*jg1==3)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreIJKL(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='M'&&*jg1==4)||(novotabuleiro[*li][*co]=='N'&&*jg1==4)||(novotabuleiro[*li][*co]=='O'&&*jg1==4)||(novotabuleiro[*li][*co]=='P'&&*jg1==4)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreMNOP(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if(entroutorre==0){
            imprimirTabuleiro(tabuleiro);
        }
    }
};

void movimentobaixo(char tabuleiro[][15], char *boneco,int dado,int *li,int *co,int *mov,int *jg1,char novotabuleiro[][15],int liant,int coant,char *torre,int numjog){

    int x,y,a=0,entroutorre;
    char bonecocomido[3];
    entroutorre=0;

    if(*co==14&&*li==6){
        while(*mov!=dado&&*mov<dado&&*li<8&&a<1){
            tabuleiro[6][14]=' ';
            tabuleiro[7][14]=boneco[0];
            (*mov)++;
            *li=7;
            *co=14;
            a++;
        }
    }
    a=0;
    if(*co==14&&*li==7&&*jg1!=3){
        while(*mov!=dado&&*mov<dado&&a<1){
            tabuleiro[7][14]=' ';
            tabuleiro[8][14]=boneco[0];
            (*mov)++;
            *li=8;
            *co=14;
            a++;
        }
    }
    if(*co==8){
        if(*li==0||*li==1||*li==2||*li==3||*li==4||*li==5||*li==9||*li==10||*li==11||*li==12||*li==13){
            printf("entrou no if final3\n");
            while ((*mov != dado && *mov < dado && *li >= 0 && *li < 5) || (*mov != dado && *mov < dado && *li >= 8 && *li < 14)){
                *li=-1;
                *co=-1;
                for(x=0;x<15;x++){
                    for(y=0;y<15;y++){
                        if(tabuleiro[x][y]==boneco[0]){
                            *li=x;
                            *co=y;
                        }
                    }
                }
                tabuleiro[*li][*co]=' ';
                (*li)++;
                *co=8;
                tabuleiro[*li][*co]=boneco[0];
                (*mov)++;
            }
        }
    }
    if(*mov==dado){
        for (x = 0; x < 15; x++) {
            for (y = 0; y < 15; y++) {
                tabuleiro[x][y]=novotabuleiro[x][y];
            }
        }
        tabuleiro[liant][coant]=' ';//TEM AS EXCESSOES COMO: CASA SEGURA E TORRES
        tabuleiro[*li][*co]=boneco[0];
        if(novotabuleiro[*li][*co]!=' '/*&&((*li!=2&&*co!=6)||(*li!=6&&*co!=12)||(*li!=12&&*co!=8)||(*li!=8&&*co!=2)||(*li!=6&&*co!=1)||(*li!=1&&*co!=8)||(*li!=8&&*co!=13)||(*li!=13&&*co!=6))*/){//COMER PEÇAS TIRANDO AS CASAS SEGURAS
            if((novotabuleiro[*li][*co]=='A'&&*jg1!=1)||(novotabuleiro[*li][*co]=='B'&&*jg1!=1)||(novotabuleiro[*li][*co]=='C'&&*jg1!=1)||(novotabuleiro[*li][*co]=='D'&&*jg1!=1)||(novotabuleiro[*li][*co]=='E'&&*jg1!=2)||(novotabuleiro[*li][*co]=='F'&&*jg1!=2)||(novotabuleiro[*li][*co]=='G'&&*jg1!=2)||(novotabuleiro[*li][*co]=='H'&&*jg1!=2)||(novotabuleiro[*li][*co]=='I'&&*jg1!=3)||(novotabuleiro[*li][*co]=='J'&&*jg1!=3)||(novotabuleiro[*li][*co]=='K'&&*jg1!=3)||(novotabuleiro[*li][*co]=='L'&&*jg1!=3)||(novotabuleiro[*li][*co]=='M'&&*jg1==4)||(novotabuleiro[*li][*co]=='N'&&*jg1==4)||(novotabuleiro[*li][*co]=='O'&&*jg1==4)||(novotabuleiro[*li][*co]=='P'&&*jg1==4)){
                bonecocomido[0]=novotabuleiro[*li][*co];
                comer(tabuleiro,bonecocomido,jg1,numjog);
            }
        }
        if((novotabuleiro[*li][*co]=='A'&&*jg1==1)||(novotabuleiro[*li][*co]=='B'&&*jg1==1)||(novotabuleiro[*li][*co]=='C'&&*jg1==1)||(novotabuleiro[*li][*co]=='D'&&*jg1==1)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreABCD(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='E'&&*jg1==2)||(novotabuleiro[*li][*co]=='F'&&*jg1==2)||(novotabuleiro[*li][*co]=='G'&&*jg1==2)||(novotabuleiro[*li][*co]=='H'&&*jg1==2)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreEFGH(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='I'&&*jg1==3)||(novotabuleiro[*li][*co]=='J'&&*jg1==3)||(novotabuleiro[*li][*co]=='K'&&*jg1==3)||(novotabuleiro[*li][*co]=='L'&&*jg1==3)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreIJKL(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='M'&&*jg1==4)||(novotabuleiro[*li][*co]=='N'&&*jg1==4)||(novotabuleiro[*li][*co]=='O'&&*jg1==4)||(novotabuleiro[*li][*co]=='P'&&*jg1==4)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreMNOP(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if(entroutorre==0){
            imprimirTabuleiro(tabuleiro);
        }
    }
};

void movimentoesquerda(char tabuleiro[][15], char *boneco,int dado,int *li,int *co,int *mov,int *jg1,char novotabuleiro[][15],int liant,int coant,char *torre,int numjog){

    int x,y,a=0,entroutorre;
    char bonecocomido[3];
    entroutorre=0;

    if(*li==14&&*co==8){
        while(*mov!=dado&&*mov<dado&&*co>6&&a<1){
            tabuleiro[14][8]=' ';
            tabuleiro[14][7]=boneco[0];
            *li=14;
            *co=7;
            (*mov)++;
            a++;
        }
    }
    a=0;
    if(*co==7&&*li==14&&*jg1!=4){
        while(*mov!=dado&&*mov<dado&&a<1){
            tabuleiro[14][7]=' ';
            tabuleiro[14][6]=boneco[0];
            (*mov)++;
            *li=14;
            *co=6;
            a++;
        }
    }
    else if(*li==8){
        if(*co==14||*co==13||*co==12||*co==11||*co==10||*co==0||*co==1||*co==2||*co==3||*co==4||*co==5){
            while ((*mov != dado && *mov < dado && *co > 0 && *co < 6) || (*mov != dado && *mov < dado && *co > 9 && *co <= 14)){
                for(x=0;x<15;x++){
                    for(y=0;y<15;y++){
                        if(tabuleiro[x][y]==boneco[0]){
                            *li=x;
                            *co=y;
                        }
                        if(*li!=-1&&*co!=-1){
                            
                            break;
                        }
                    }
                }
                tabuleiro[*li][*co]=' ';
                *li=8;
                (*co)--;
                tabuleiro[*li][*co]=boneco[0];
                (*mov)++;
            }
        }
    }
    if(*mov==dado){
        for (x = 0; x < 15; x++) {
            for (y = 0; y < 15; y++) {
                tabuleiro[x][y]=novotabuleiro[x][y];
            }
        }
        tabuleiro[liant][coant]=' ';//TEM AS EXCESSOES COMO: CASA SEGURA E TORRES
        tabuleiro[*li][*co]=boneco[0];
        if(novotabuleiro[*li][*co]!=' '/*&&((*li!=2&&*co!=6)||(*li!=6&&*co!=12)||(*li!=12&&*co!=8)||(*li!=8&&*co!=2)||(*li!=6&&*co!=1)||(*li!=1&&*co!=8)||(*li!=8&&*co!=13)||(*li!=13&&*co!=6))*/){//COMER PEÇAS TIRANDO AS CASAS SEGURAS
            if((novotabuleiro[*li][*co]=='A'&&*jg1!=1)||(novotabuleiro[*li][*co]=='B'&&*jg1!=1)||(novotabuleiro[*li][*co]=='C'&&*jg1!=1)||(novotabuleiro[*li][*co]=='D'&&*jg1!=1)||(novotabuleiro[*li][*co]=='E'&&*jg1!=2)||(novotabuleiro[*li][*co]=='F'&&*jg1!=2)||(novotabuleiro[*li][*co]=='G'&&*jg1!=2)||(novotabuleiro[*li][*co]=='H'&&*jg1!=2)||(novotabuleiro[*li][*co]=='I'&&*jg1!=3)||(novotabuleiro[*li][*co]=='J'&&*jg1!=3)||(novotabuleiro[*li][*co]=='K'&&*jg1!=3)||(novotabuleiro[*li][*co]=='L'&&*jg1!=3)||(novotabuleiro[*li][*co]=='M'&&*jg1==4)||(novotabuleiro[*li][*co]=='N'&&*jg1==4)||(novotabuleiro[*li][*co]=='O'&&*jg1==4)||(novotabuleiro[*li][*co]=='P'&&*jg1==4)){
                bonecocomido[0]=novotabuleiro[*li][*co];
                comer(tabuleiro,bonecocomido,jg1,numjog);
            }
        }
        if((novotabuleiro[*li][*co]=='A'&&*jg1==1)||(novotabuleiro[*li][*co]=='B'&&*jg1==1)||(novotabuleiro[*li][*co]=='C'&&*jg1==1)||(novotabuleiro[*li][*co]=='D'&&*jg1==1)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreABCD(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='E'&&*jg1==2)||(novotabuleiro[*li][*co]=='F'&&*jg1==2)||(novotabuleiro[*li][*co]=='G'&&*jg1==2)||(novotabuleiro[*li][*co]=='H'&&*jg1==2)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreEFGH(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='I'&&*jg1==3)||(novotabuleiro[*li][*co]=='J'&&*jg1==3)||(novotabuleiro[*li][*co]=='K'&&*jg1==3)||(novotabuleiro[*li][*co]=='L'&&*jg1==3)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreIJKL(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='M'&&*jg1==4)||(novotabuleiro[*li][*co]=='N'&&*jg1==4)||(novotabuleiro[*li][*co]=='O'&&*jg1==4)||(novotabuleiro[*li][*co]=='P'&&*jg1==4)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreMNOP(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if(entroutorre==0){
            imprimirTabuleiro(tabuleiro);
        }
    }
};

void movimentovitoriaverde(char tabuleiro[][15], char *boneco,int dado,int *li, int *co, int *mov,int *win1,char novotabuleiro[][15],int liant,int coant,char *torre){

    int x,y,entroutorre=0;
    char bonecocomido[3];

    while(*mov!=dado&&*mov<dado&&*li==7&&*co>=0&&*co<7){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]==boneco[0]){
                    *li=x;
                    *co=y;
                }
            }
        }
        tabuleiro[*li][*co]=' ';
        *li=7;
        (*co)++;
        tabuleiro[*li][*co]=boneco[0];
        (*mov)++;
        if(*li==7&&*co==6){//venceu
            (*win1)++;
        }
    }
    if(*mov==dado){
        for (x = 0; x < 15; x++) {
            for (y = 0; y < 15; y++) {
                tabuleiro[x][y]=novotabuleiro[x][y];
            }
        }
        tabuleiro[liant][coant]=' ';//TEM AS EXCESSOES COMO: CASA SEGURA E TORRES
        tabuleiro[*li][*co]=boneco[0];
        if((novotabuleiro[*li][*co]=='A')||(novotabuleiro[*li][*co]=='B')||(novotabuleiro[*li][*co]=='C')||(novotabuleiro[*li][*co]=='D')){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreABCD(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if(entroutorre==0){
            imprimirTabuleiro(tabuleiro);
        }
    }
};

void movimentovitoriaamarelo(char tabuleiro[][15], char *boneco,int dado,int *li, int *co, int *mov,int *win2,char novotabuleiro[][15],int liant,int coant,char *torre){

    int x,y,entroutorre=0;
    char bonecocomido[3];

    while(*mov!=dado&&*mov<dado&&*co==7&&*li>=0&&*li<7){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]==boneco[0]){
                    *li=x;
                    *co=y;
                }
            }
        }
        tabuleiro[*li][*co]=' ';
        (*li)++;
        *co=7;
        tabuleiro[*li][*co]=boneco[0];
        (*mov)++;
        if(*li==6&&*co==7){//venceu
            (*win2)++;
        }
    }
    if(*mov==dado){
        for (x = 0; x < 15; x++) {
            for (y = 0; y < 15; y++) {
                tabuleiro[x][y]=novotabuleiro[x][y];
            }
        }
        tabuleiro[liant][coant]=' ';//TEM AS EXCESSOES COMO: CASA SEGURA E TORRES
        tabuleiro[*li][*co]=boneco[0];
        if((novotabuleiro[*li][*co]=='E')||(novotabuleiro[*li][*co]=='F')||(novotabuleiro[*li][*co]=='G')||(novotabuleiro[*li][*co]=='H')){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreEFGH(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if(entroutorre==0){
            imprimirTabuleiro(tabuleiro);
        }
    }
};

void movimentovitoriaazul(char tabuleiro[][15], char *boneco,int dado,int *li, int *co, int *mov,int *win3,char novotabuleiro[][15],int liant,int coant,char *torre){

    int x,y,entroutorre=0;
    char bonecocomido[3];

    while(*mov!=dado&&*mov<dado&&*li==7&&*co<=14&&*co>7){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]==boneco[0]){
                    *li=x;
                    *co=y;
                }
            }
        }
        tabuleiro[*li][*co]=' ';
        *li=7;
        (*co)--;
        tabuleiro[*li][*co]=boneco[0];
        (*mov)++;
        if(*li==7&&*co==8){//venceu
            win3++;
        }
    }
    if(*mov==dado){
        for (x = 0; x < 15; x++) {
            for (y = 0; y < 15; y++) {
                tabuleiro[x][y]=novotabuleiro[x][y];
            }
        }
        tabuleiro[liant][coant]=' ';//TEM AS EXCESSOES COMO: CASA SEGURA E TORRES
        tabuleiro[*li][*co]=boneco[0];
        if((novotabuleiro[*li][*co]=='I')||(novotabuleiro[*li][*co]=='J')||(novotabuleiro[*li][*co]=='K')||(novotabuleiro[*li][*co]=='L')){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreIJKL(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if(entroutorre==0){
            imprimirTabuleiro(tabuleiro);
        }
    }
};

void movimentovitoriavermelho(char tabuleiro[][15], char *boneco,int dado,int *li, int *co, int *mov,int *win4,char novotabuleiro[][15],int liant,int coant,char *torre){

    int x,y,entroutorre=0;
    char bonecocomido[3];

    while(*mov!=dado&&*mov<dado&&*co==7&&*li<=14&&*li>7){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]==boneco[0]){
                    *li=x;
                    *co=y;
                }
            }
        }
        tabuleiro[*li][*co]=' ';
        (*li)--;
        *co=7;
        tabuleiro[*li][*co]=boneco[0];
        (*mov)++;
        if(*li==8&&*co==7){//venceu
            (*win4)++;
        }
    }
    if(*mov==dado){
        for (x = 0; x < 15; x++) {
            for (y = 0; y < 15; y++) {
                tabuleiro[x][y]=novotabuleiro[x][y];
            }
        }
        tabuleiro[liant][coant]=' ';//TEM AS EXCESSOES COMO: CASA SEGURA E TORRES
        tabuleiro[*li][*co]=boneco[0];
        if((novotabuleiro[*li][*co]=='M')||(novotabuleiro[*li][*co]=='N')||(novotabuleiro[*li][*co]=='O')||(novotabuleiro[*li][*co]=='P')){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreMNOP(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if(entroutorre==0){
            imprimirTabuleiro(tabuleiro);
        }
    }
};

void comer(char tabuleiro[][15],char *bonecocomido,int *jg1,int numjog){

    int comeu=0;
    while(1){
        if(*jg1!=1&&bonecocomido[0]=='A'){
            tabuleiro[1][1]='A';
        }if(*jg1!=1&&bonecocomido[0]=='B'){
            tabuleiro[2][2]='B';
        }if(*jg1!=1&&bonecocomido[0]=='C'){
            tabuleiro[3][3]='C';
        }if(*jg1!=1&&bonecocomido[0]=='D'){
            tabuleiro[4][4]='D';
        }
        if(*jg1!=2&&bonecocomido[0]=='E'){
            tabuleiro[1][10]='E';
        }if(*jg1!=2&&bonecocomido[0]=='F'){
            tabuleiro[2][11]='F';
        }if(*jg1!=2&&bonecocomido[0]=='G'){
            tabuleiro[3][12]='G';
        }if(*jg1!=2&&bonecocomido[0]=='H'){
            tabuleiro[4][13]='H';
        }
        if(*jg1!=3&&bonecocomido[0]=='I'){
            tabuleiro[10][10]='I';
        }if(*jg1!=3&&bonecocomido[0]=='J'){
            tabuleiro[11][11]='J';
        }if(*jg1!=3&&bonecocomido[0]=='K'){
            tabuleiro[12][12]='K';
        }if(*jg1!=3&&bonecocomido[0]=='L'){
            tabuleiro[13][13]='L';
        }
        if(*jg1!=4&&bonecocomido[0]=='M'){
            tabuleiro[10][1]='M';
        }if(*jg1!=4&&bonecocomido[0]=='N'){
            tabuleiro[11][2]='N';
        }if(*jg1!=4&&bonecocomido[0]=='O'){
            tabuleiro[12][3]='O';
        }if(*jg1!=4&&bonecocomido[0]=='P'){
            tabuleiro[13][4]='P';
        }
        comeu++;
        break;
    }
    if(comeu>0){
        if(numjog==2){
            *jg1=*jg1-2;
        }
        if(numjog==4){
            (*jg1)--;
        };//O dado roda dnv, pq ocorreu uma captura de peça
    }
};

void movimentopulo(char tabuleiro[][15],char *boneco,int dado,int *li,int *co,int *mov,int *jg1,char novotabuleiro[][15],int liant,int coant,char *torre,int numjog){

    int x,y,entroutorre=0;
    char bonecocomido[3];
    
    if(*li==6&&*co==5&&*mov<6){//superior esquerdo
        tabuleiro[6][5]=' ';
        tabuleiro[5][6]=boneco[0];
        (*mov)++;
        *li=5;
        *co=6;
    }
    if(*li==5&&*co==8&&*mov<6){//superior direito
        tabuleiro[5][8]=' ';
        tabuleiro[6][9]=boneco[0];
        (*mov)++;
        *li=6;
        *co=9;
    }
    if(*li==8&&*co==9&&*mov<6){//inferior direito
        tabuleiro[8][9]=' ';
        tabuleiro[9][8]=boneco[0];
        (*mov)++;
        *li=9;
        *co=8;
    }
    if(*li==9&&*co==6&&*mov<6){//inferior esquerdo
        tabuleiro[9][6]=' ';
        tabuleiro[8][5]=boneco[0];
        (*mov)++;
        *li=8;
        *co=5;
    }
    if(*mov==dado){
        for (x = 0; x < 15; x++) {
            for (y = 0; y < 15; y++) {
                tabuleiro[x][y]=novotabuleiro[x][y];
            }
        }
        tabuleiro[liant][coant]=' ';//TEM AS EXCESSOES COMO: CASA SEGURA E TORRES
        tabuleiro[*li][*co]=boneco[0];
        if(novotabuleiro[*li][*co]!=' '){//COMER PEÇAS
            bonecocomido[0]=novotabuleiro[*li][*co];
            comer(tabuleiro,bonecocomido,jg1,numjog);
        }if((novotabuleiro[*li][*co]=='A'&&*jg1==1)||(novotabuleiro[*li][*co]=='B'&&*jg1==1)||(novotabuleiro[*li][*co]=='C'&&*jg1==1)||(novotabuleiro[*li][*co]=='D'&&*jg1==1)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreABCD(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='E'&&*jg1==2)||(novotabuleiro[*li][*co]=='F'&&*jg1==2)||(novotabuleiro[*li][*co]=='G'&&*jg1==2)||(novotabuleiro[*li][*co]=='H'&&*jg1==2)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreEFGH(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='I'&&*jg1==3)||(novotabuleiro[*li][*co]=='J'&&*jg1==3)||(novotabuleiro[*li][*co]=='K'&&*jg1==3)||(novotabuleiro[*li][*co]=='L'&&*jg1==3)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreIJKL(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if((novotabuleiro[*li][*co]=='M'&&*jg1==4)||(novotabuleiro[*li][*co]=='N'&&*jg1==4)||(novotabuleiro[*li][*co]=='O'&&*jg1==4)||(novotabuleiro[*li][*co]=='P'&&*jg1==4)){
            bonecocomido[0]=novotabuleiro[*li][*co];
            torreMNOP(tabuleiro,torre,boneco,bonecocomido,li,co);
            entroutorre++;
        }
        if(entroutorre==0){
            imprimirTabuleiro(tabuleiro);
        }
    }
};

void torreABCD(char tabuleiro[][15],char *torre,char *boneco,char *bonecocomido,int *li,int *co){
        
    if(boneco[0]=='A'&&bonecocomido[0]=='B'){
        tabuleiro[*li][*co]='Q';
        torre[0]='Q';
    }if(boneco[0]=='B'&&bonecocomido[0]=='A'){
        tabuleiro[*li][*co]='Q';
        torre[0]='Q';
    }if(boneco[0]=='A'&&bonecocomido[0]=='C'){
        tabuleiro[*li][*co]='R';
        torre[0]='R';
    }if(boneco[0]=='C'&&bonecocomido[0]=='A'){
        tabuleiro[*li][*co]='R';
        torre[0]='R';
    }if(boneco[0]=='A'&&bonecocomido[0]=='D'){
        tabuleiro[*li][*co]='S';
        torre[0]='S';
    }if(boneco[0]=='D'&&bonecocomido[0]=='A'){
        tabuleiro[*li][*co]='S';
        torre[0]='S';
    }if(boneco[0]=='B'&&bonecocomido[0]=='C'){
        tabuleiro[*li][*co]='T';
        torre[1]='T';
    }if(boneco[0]=='C'&&bonecocomido[0]=='B'){
        tabuleiro[*li][*co]='T';
        torre[1]='T';
    }if(boneco[0]=='C'&&bonecocomido[0]=='D'){
        tabuleiro[*li][*co]='U';
        torre[2]='U';
    }if(boneco[0]=='D'&&bonecocomido[0]=='C'){
        tabuleiro[*li][*co]='U';
        torre[2]='U';
    }if(boneco[0]=='B'&&bonecocomido[0]=='D'){
        tabuleiro[*li][*co]='V';
        torre[1]='V';
    }if(boneco[0]=='D'&&bonecocomido[0]=='B'){
        tabuleiro[*li][*co]='V';
        torre[1]='V';
    }
    imprimirTabuleiro(tabuleiro);
};
void torreEFGH(char tabuleiro[][15],char *torre,char *boneco,char *bonecocomido,int *li,int *co){
        
    if(boneco[0]=='E'&&bonecocomido[0]=='F'){//E+F 1 3
        tabuleiro[*li][*co]='1';
        torre[3]='1';
    }if(boneco[0]=='F'&&bonecocomido[0]=='E'){//E+F 1 3
        tabuleiro[*li][*co]='1';
        torre[3]='1';
    }if(boneco[0]=='E'&&bonecocomido[0]=='G'){//E+G 2 3
        tabuleiro[*li][*co]='2';
        torre[3]='2';
    }if(boneco[0]=='G'&&bonecocomido[0]=='E'){//E+G 2 3
        tabuleiro[*li][*co]='2';
        torre[3]='2';
    }if(boneco[0]=='E'&&bonecocomido[0]=='H'){//E+H 4 3
        tabuleiro[*li][*co]='4';
        torre[3]='4';
    }if(boneco[0]=='H'&&bonecocomido[0]=='E'){//E+H 4 3
        tabuleiro[*li][*co]='4';
        torre[3]='4';
    }if(boneco[0]=='F'&&bonecocomido[0]=='G'){//F=G 6 4
        tabuleiro[*li][*co]='6';
        torre[4]='6';
    }if(boneco[0]=='G'&&bonecocomido[0]=='F'){//F=G 6 4
        tabuleiro[*li][*co]='6';
        torre[4]='6';
    }if(boneco[0]=='G'&&bonecocomido[0]=='H'){//G=H 8 5
        tabuleiro[*li][*co]='8';
        torre[5]='8';
    }if(boneco[0]=='H'&&bonecocomido[0]=='G'){//G+H 8 5
        tabuleiro[*li][*co]='8';
        torre[5]='8';
    }if(boneco[0]=='F'&&bonecocomido[0]=='H'){//F+H 0 4
        tabuleiro[*li][*co]='0';
        torre[4]='0';
    }if(boneco[0]=='H'&&bonecocomido[0]=='F'){//F+H 0 4
        tabuleiro[*li][*co]='0';
        torre[4]='0';
    }
    imprimirTabuleiro(tabuleiro);
};
void torreIJKL(char tabuleiro[][15],char *torre,char *boneco,char *bonecocomido,int *li,int *co){
        
    if(boneco[0]=='I'&&bonecocomido[0]=='J'){
        tabuleiro[*li][*co]='W';
        torre[6]='W';
    }if(boneco[0]=='J'&&bonecocomido[0]=='I'){
        tabuleiro[*li][*co]='W';
        torre[6]='W';
    }if(boneco[0]=='I'&&bonecocomido[0]=='K'){
        tabuleiro[*li][*co]='X';
        torre[6]='X';
    }if(boneco[0]=='K'&&bonecocomido[0]=='I'){
        tabuleiro[*li][*co]='X';
        torre[6]='X';
    }if(boneco[0]=='I'&&bonecocomido[0]=='L'){
        tabuleiro[*li][*co]='Y';
        torre[6]='Y';
    }if(boneco[0]=='L'&&bonecocomido[0]=='I'){
        tabuleiro[*li][*co]='Y';
        torre[6]='Y';
    }if(boneco[0]=='J'&&bonecocomido[0]=='K'){
        tabuleiro[*li][*co]='Z';
        torre[7]='Z';
    }if(boneco[0]=='K'&&bonecocomido[0]=='J'){
        tabuleiro[*li][*co]='Z';
        torre[7]='Z';
    }if(boneco[0]=='J'&&bonecocomido[0]=='L'){
        tabuleiro[*li][*co]='7';
        torre[7]='7';
    }if(boneco[0]=='L'&&bonecocomido[0]=='J'){
        tabuleiro[*li][*co]='7';
        torre[7]='7';
    }if(boneco[0]=='K'&&bonecocomido[0]=='L'){
        tabuleiro[*li][*co]='9';
        torre[8]='9';
    }if(boneco[0]=='L'&&bonecocomido[0]=='K'){
        tabuleiro[*li][*co]='9';
        torre[8]='9';
    }
    imprimirTabuleiro(tabuleiro);
};
void torreMNOP(char tabuleiro[][15],char *torre,char *boneco,char *bonecocomido,int *li,int *co){
        
    if(boneco[0]=='M'&&bonecocomido[0]=='N'){
        tabuleiro[*li][*co]='+';
        torre[9]='+';
    }if(boneco[0]=='N'&&bonecocomido[0]=='M'){
        tabuleiro[*li][*co]='+';
        torre[9]='+';
    }if(boneco[0]=='M'&&bonecocomido[0]=='O'){
        tabuleiro[*li][*co]='=';
        torre[9]='=';
    }if(boneco[0]=='O'&&bonecocomido[0]=='M'){
        tabuleiro[*li][*co]='=';
        torre[9]='=';
    }if(boneco[0]=='M'&&bonecocomido[0]=='P'){
        tabuleiro[*li][*co]='/';
        torre[9]='/';
    }if(boneco[0]=='P'&&bonecocomido[0]=='M'){
        tabuleiro[*li][*co]='/';
        torre[9]='/';
    }if(boneco[0]=='N'&&bonecocomido[0]=='O'){
        tabuleiro[*li][*co]='!';
        torre[10]='!';
    }if(boneco[0]=='O'&&bonecocomido[0]=='N'){
        tabuleiro[*li][*co]='!';
        torre[10]='!';
    }if(boneco[0]=='N'&&bonecocomido[0]=='P'){
        tabuleiro[*li][*co]='?';
        torre[10]='?';
    }if(boneco[0]=='P'&&bonecocomido[0]=='N'){
        tabuleiro[*li][*co]='?';
        torre[10]='?';
    }if(boneco[0]=='O'&&bonecocomido[0]=='P'){
        tabuleiro[*li][*co]='&';
        torre[11]='&';
    }if(boneco[0]=='P'&&bonecocomido[0]=='O'){
        tabuleiro[*li][*co]='&';
        torre[11]='&';
    }
    imprimirTabuleiro(tabuleiro);
};
void desfaztorre(char tabuleiro[][15],char novotabuleiro[][15],char *boneco,char *torre,int *li,int *co,int liant,int coant){

int x,y;

    if((boneco[0]=='A'&&torre[0]=='Q')||(boneco[0]=='B'&&torre[0]=='Q')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='Q'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }
        if(boneco[0]=='A'){
            tabuleiro[*li][*co]='A';
            novotabuleiro[liant][coant]='B';
        }if(boneco[0]=='B'){
            tabuleiro[*li][*co]='B';
            novotabuleiro[liant][coant]='A';
        }torre[0]=' ';
    }
    if((boneco[0]=='A'&&torre[0]=='R')||(boneco[0]=='C'&&torre[0]=='R')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='R'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='A'){
            tabuleiro[*li][*co]='A';
            novotabuleiro[liant][coant]='C';
        }if(boneco[0]=='C'){
            tabuleiro[*li][*co]='C';
            novotabuleiro[liant][coant]='A';
        }torre[0]=' ';
    }
    if((boneco[0]=='A'&&torre[0]=='S')||(boneco[0]=='D'&&torre[0]=='S')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='S'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='A'){
            tabuleiro[*li][*co]='A';
            novotabuleiro[liant][coant]='D';
        }if(boneco[0]=='D'){
            tabuleiro[*li][*co]='D';
            novotabuleiro[liant][coant]='A';
        }torre[0]=' ';
    }
    if((boneco[0]=='B'&&torre[1]=='T')||(boneco[0]=='C'&&torre[1]=='T')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='T'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='B'){
            tabuleiro[*li][*co]='B';
            novotabuleiro[liant][coant]='C';
        }if(boneco[0]=='C'){
            tabuleiro[*li][*co]='C';
            novotabuleiro[liant][coant]='B';
        }torre[1]=' ';
    }
    if((boneco[0]=='C'&&torre[2]=='U')||(boneco[0]=='D'&&torre[2]=='U')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='U'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='C'){
            tabuleiro[*li][*co]='C';
            novotabuleiro[liant][coant]='D';
        }if(boneco[0]=='D'){
            tabuleiro[*li][*co]='D';
            novotabuleiro[liant][coant]='C';
        }torre[2]=' ';
    }
    if((boneco[0]=='D'&&torre[1]=='V')||(boneco[0]=='B'&&torre[1]=='V')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='V'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='D'){
            tabuleiro[*li][*co]='D';
            novotabuleiro[liant][coant]='B';
        }if(boneco[0]=='B'){
            tabuleiro[*li][*co]='B';
            novotabuleiro[liant][coant]='D';
        }torre[1]=' ';
        
    }
    //EFGH
    if((boneco[0]=='E'&&torre[3]=='1')||(boneco[0]=='F'&&torre[3]=='1')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='1'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }
        if(boneco[0]=='E'){
            tabuleiro[*li][*co]='E';
            novotabuleiro[liant][coant]='F';
        }if(boneco[0]=='F'){
            tabuleiro[*li][*co]='F';
            novotabuleiro[liant][coant]='E';
        }torre[3]=' ';
    }
    if((boneco[0]=='E'&&torre[3]=='2')||(boneco[0]=='G'&&torre[3]=='2')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='2'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='E'){
            tabuleiro[*li][*co]='E';
            novotabuleiro[liant][coant]='G';
        }if(boneco[0]=='G'){
            tabuleiro[*li][*co]='G';
            novotabuleiro[liant][coant]='E';
        }torre[3]=' ';
    }
    if((boneco[0]=='E'&&torre[3]=='4')||(boneco[0]=='H'&&torre[3]=='4')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='4'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='E'){
            tabuleiro[*li][*co]='E';
            novotabuleiro[liant][coant]='H';
        }if(boneco[0]=='H'){
            tabuleiro[*li][*co]='H';
            novotabuleiro[liant][coant]='E';
        }torre[3]=' ';
    }
    if((boneco[0]=='F'&&torre[4]=='6')||(boneco[0]=='G'&&torre[4]=='6')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='6'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='F'){
            tabuleiro[*li][*co]='F';
            novotabuleiro[liant][coant]='G';
        }if(boneco[0]=='G'){
            tabuleiro[*li][*co]='G';
            novotabuleiro[liant][coant]='F';
        }torre[4]=' ';
    }
    if((boneco[0]=='G'&&torre[5]=='8')||(boneco[0]=='H'&&torre[5]=='8')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='8'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='G'){
            tabuleiro[*li][*co]='G';
            novotabuleiro[liant][coant]='H';
        }if(boneco[0]=='H'){
            tabuleiro[*li][*co]='H';
            novotabuleiro[liant][coant]='G';
        }torre[5]=' ';
    }
    if((boneco[0]=='H'&&torre[4]=='0')||(boneco[0]=='F'&&torre[4]=='0')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='0'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='H'){
            tabuleiro[*li][*co]='H';
            novotabuleiro[liant][coant]='F';
        }if(boneco[0]=='F'){
            tabuleiro[*li][*co]='F';
            novotabuleiro[liant][coant]='H';
        }torre[4]=' ';
        
    }
    //IJKL
    if((boneco[0]=='I'&&torre[6]=='W')||(boneco[0]=='J'&&torre[6]=='W')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='W'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }
        if(boneco[0]=='I'){
            tabuleiro[*li][*co]='I';
            novotabuleiro[liant][coant]='J';
        }if(boneco[0]=='J'){
            tabuleiro[*li][*co]='J';
            novotabuleiro[liant][coant]='I';
        }torre[6]=' ';
    }
    if((boneco[0]=='I'&&torre[6]=='X')||(boneco[0]=='K'&&torre[6]=='X')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='X'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='I'){
            tabuleiro[*li][*co]='I';
            novotabuleiro[liant][coant]='K';
        }if(boneco[0]=='K'){
            tabuleiro[*li][*co]='K';
            novotabuleiro[liant][coant]='I';
        }torre[6]=' ';
    }
    if((boneco[0]=='I'&&torre[6]=='Y')||(boneco[0]=='L'&&torre[6]=='Y')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='Y'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='I'){
            tabuleiro[*li][*co]='I';
            novotabuleiro[liant][coant]='L';
        }if(boneco[0]=='L'){
            tabuleiro[*li][*co]='L';
            novotabuleiro[liant][coant]='I';
        }torre[6]=' ';
    }
    if((boneco[0]=='J'&&torre[7]=='Z')||(boneco[0]=='K'&&torre[7]=='Z')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='Z'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='J'){
            tabuleiro[*li][*co]='J';
            novotabuleiro[liant][coant]='K';
        }if(boneco[0]=='K'){
            tabuleiro[*li][*co]='K';
            novotabuleiro[liant][coant]='J';
        }torre[7]=' ';
    }
    if((boneco[0]=='K'&&torre[8]=='9')||(boneco[0]=='L'&&torre[8]=='9')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='9'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='K'){
            tabuleiro[*li][*co]='K';
            novotabuleiro[liant][coant]='L';
        }if(boneco[0]=='L'){
            tabuleiro[*li][*co]='L';
            novotabuleiro[liant][coant]='K';
        }torre[8]=' ';
    }
    if((boneco[0]=='L'&&torre[7]=='7')||(boneco[0]=='J'&&torre[7]=='7')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='7'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='L'){
            tabuleiro[*li][*co]='L';
            novotabuleiro[liant][coant]='J';
        }if(boneco[0]=='J'){
            tabuleiro[*li][*co]='J';
            novotabuleiro[liant][coant]='L';
        }torre[7]=' ';
        
    }
    //MNOP
    if((boneco[0]=='M'&&torre[9]=='+')||(boneco[0]=='N'&&torre[9]=='+')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='+'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }
        if(boneco[0]=='M'){
            tabuleiro[*li][*co]='M';
            novotabuleiro[liant][coant]='N';
        }if(boneco[0]=='N'){
            tabuleiro[*li][*co]='N';
            novotabuleiro[liant][coant]='M';
        }torre[9]=' ';
    }
    if((boneco[0]=='M'&&torre[9]=='=')||(boneco[0]=='O'&&torre[9]=='=')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='='){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='M'){
            tabuleiro[*li][*co]='M';
            novotabuleiro[liant][coant]='O';
        }if(boneco[0]=='O'){
            tabuleiro[*li][*co]='O';
            novotabuleiro[liant][coant]='M';
        }torre[9]=' ';
    }
    if((boneco[0]=='M'&&torre[9]=='/')||(boneco[0]=='P'&&torre[9]=='/')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='/'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='M'){
            tabuleiro[*li][*co]='M';
            novotabuleiro[liant][coant]='P';
        }if(boneco[0]=='P'){
            tabuleiro[*li][*co]='P';
            novotabuleiro[liant][coant]='M';
        }torre[9]=' ';
    }
    if((boneco[0]=='N'&&torre[10]=='!')||(boneco[0]=='O'&&torre[10]=='!')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='!'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='N'){
            tabuleiro[*li][*co]='N';
            novotabuleiro[liant][coant]='O';
        }if(boneco[0]=='O'){
            tabuleiro[*li][*co]='O';
            novotabuleiro[liant][coant]='N';
        }torre[10]=' ';
    }
    if((boneco[0]=='O'&&torre[11]=='&')||(boneco[0]=='P'&&torre[11]=='&')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='&'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='O'){
            tabuleiro[*li][*co]='O';
            novotabuleiro[liant][coant]='P';
        }if(boneco[0]=='P'){
            tabuleiro[*li][*co]='P';
            novotabuleiro[liant][coant]='O';
        }torre[11]=' ';
    }
    if((boneco[0]=='P'&&torre[10]=='?')||(boneco[0]=='N'&&torre[10]=='?')){
        for(x=0;x<15;x++){
            for(y=0;y<15;y++){
                if(tabuleiro[x][y]=='?'){
                    *li=x;
                    *co=y;
                    liant=x;
                    coant=y;
                }
            }
        }if(boneco[0]=='P'){
            tabuleiro[*li][*co]='P';
            novotabuleiro[liant][coant]='N';
        }if(boneco[0]=='N'){
            tabuleiro[*li][*co]='N';
            novotabuleiro[liant][coant]='P';
        }torre[10]=' ';
    }
};