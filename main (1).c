#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <ctype.h>

//STRUCT PARA DEFINIR O TIPO 'STRUCT COORDENADAS'
//Esse tipo é um array de dois inteiros.
struct coordenadas{
    int coor[2];
};
//essa funçao do tipo struct recebe um string e retorna um vetor de dois inteiros
struct coordenadas conversor(char casa[3]){
    int i=0, j=0;
    switch(tolower(casa[0])){
        case 'a': j = 0; break;
        case 'b': j = 1; break;
        case 'c': j = 2; break;
        case 'd': j = 3; break;
        case 'e': j = 4; break;
        case 'f': j = 5; break;
        case 'g': j = 6; break;
        case 'h': j = 7; break;
        case 'i': j = 8; break;
    }
    switch(casa[1]){
        case '1': i = 0; break;
        case '2': i = 1; break;
        case '3': i = 2; break;
        case '4': i = 3; break;
        case '5': i = 4; break;
        case '6': i = 5; break;
        case '7': i = 6; break;
        case '8': i = 7; break;
        case '9': i = 8; break;
    }
    struct coordenadas lc = {{i, j}};
    return lc;
};
void exibeTabuleiro(char matriz[9][9], int turno, char peca){
	system("cls");
	printf("\n\n");
	printf("    %dº TURNO\n\n                     VEZ DO JOGADOR %c!\n\n", turno/2, peca);
    int i, j;
    printf("              A   B   C   D   E   F   G   H   I\n");
    printf("            +~~~+~~~+~~~+~~~+~~~+~~~+~~~+~~~+~~~+\n");
    for(i=0; i<9; i++){
        if(i==0) printf("          1 ");
        else if(i==1) printf("          2 ");
        else if(i==2) printf("          3 ");
        else if(i==3) printf("          4 ");
        else if(i==4) printf("          5 ");
        else if(i==5) printf("          6 ");
        else if(i==6) printf("          7 ");
        else if(i==7) printf("          8 ");
        else if(i==8) printf("          9 ");
        printf("|");
        for(j=0; j<9; j++){
            printf(" %c |", matriz[i][j]);
        }
        printf("\n            ");
        for(j=0; j<9; j++){
            if(j == 0) printf("+~~~+");
            else printf("~~~+");
        }
        printf("\n");
    }
}
char naCasa(struct coordenadas coo, char matriz[9][9]){
    int i = coo.coor[0];
    int j = coo.coor[1];
    return matriz[i][j];
}
int validaMovimento(struct coordenadas coop, struct coordenadas cood, char matriz[9][9]){  //saber: onde ta; pra onde vai; o que tem onde vai; se tem algo no caminho
//verificar se peca se moveu na horznt, vertcl ou diagns
    int i = coop.coor[0]; //linha casa de partida
    int j = coop.coor[1]; //coluna casa de partida
    int a = cood.coor[0]; //linha casa de destino
    int b = cood.coor[1]; //coluna casa de destino
    int caso;
    if((i == a)&&(j == b)) return 0;
    else if(i == a)caso = 1;            //mesma linha
    else if(j == b)caso = 2;            //mesma coluna
    else if((i+j) == (a+b))caso = 3;    //mesma diagonal secun
    else if((a-i) == (b-j))caso = 4;    //mesma diagonal princ
    else return 0;                      //movimento inválido
//verificar se casa de destino está vazia
    if(naCasa(cood, matriz) != ' ')return 0;    //movimento inválido
//verificar se tem peca no meio do caminho
    else{
        int linha;
        int coluna;
        switch(caso){
            case 1: //usar um for pra verificar da casa onde ele ta pra casa onde ele vai
                if(j<b){
                    for(coluna = j + 1; coluna<b; coluna++){
                        if((matriz[i][coluna] == 'X')||(matriz[i][coluna] == 'O'))return 0;
                        else continue;
                    }}
                else if(j>b){
                    for(coluna = j - 1; coluna>b; coluna--){
                        if((matriz[i][coluna] == 'X')||(matriz[i][coluna] == 'O'))return 0;
                        else continue;
                    }}
                break;
            case 2:
                if(i<a){
                    for(linha = i + 1; linha<a; linha++){
                        if((matriz[linha][j] == 'X')||(matriz[linha][j] == 'O'))return 0;
                        else continue;
                    }}
                else if(i>a){
                    for(linha = i - 1; linha>a; linha--){
                        if((matriz[linha][j] == 'X')||(matriz[linha][j] == 'O'))return 0;
                        else continue;
                    }}
                break;
            case 3:
                if(j<b){
                    for(linha = i - 1, coluna = j + 1; coluna<b; linha--, coluna++){
                        if((matriz[linha][coluna] == 'X')||(matriz[linha][coluna] == 'O'))return 0;
                        else continue;
                    }}
                else if(j>b){
                    for(linha = i + 1, coluna = j - 1; coluna>b; linha++, coluna--){
                        if((matriz[linha][coluna] == 'X')||(matriz[linha][coluna] == 'O'))return 0;
                        else continue;
                    }}
                break;
            case 4:
                if(i<a){
                    for(linha = i + 1, coluna = j + 1; linha<a; linha++, coluna++){
                        if((matriz[linha][coluna] == 'X')||(matriz[linha][coluna] == 'O'))return 0;
                        else continue;
                    }}
                else if(i>a){
                    for(linha = i - 1, coluna = j - 1; linha>a; linha--, coluna--){
                        if((matriz[linha][coluna] == 'X')||(matriz[linha][coluna] == 'O'))return 0;
                        else continue;
                    }}
            break;
        }
    }
    return 1;
}
int validaPeca(struct coordenadas coop, char cont, char peca, char matriz[9][9]){
    struct coordenadas cood;
    if(cont != peca) return 2;
    for (cood.coor[0] = 0 ; cood.coor[0] < 9 ; cood.coor[0]++)
        for (cood.coor[1] = 0 ; cood.coor[1] < 9 ; cood.coor[1]++)
            if (validaMovimento(coop, cood, matriz)) return 1;
return 3;
}
void movimento(char *part, char *dest){
    char partida = *part;
    *part = ' ';
    *dest = partida;
}
void verificaConversao(struct coordenadas coop, struct coordenadas cood, char matriz[9][9]){
//verificar se peca se moveu na horznt, vertcl ou diagns
    int i = coop.coor[0];    //linha casa de partida
    int j = coop.coor[1];    //coluna casa de partida
    int a = cood.coor[0];    //linha casa de destino
    int b = cood.coor[1];    //coluna casa de destino
    int linha, coluna;
    char *p;
    int caso;
    if(i == a)caso = 1;                 //mesma linha
    else if(j == b)caso = 2;            //mesma coluna
    else if((i+j) == (a+b))caso = 3;    //mesma diagonal secun
    else if((a-i) == (b-j))caso = 4;    //mesma diagonal princ

    switch(caso){
        case 1:
            linha = i;
            if (j < b){
                for (coluna = j+1; coluna < b; coluna++){
                    if (matriz[linha][coluna] == '*'){
                        p = &matriz[linha][coluna];
                        *p = '°';
                    }else if(matriz[linha][coluna] == '°'){
                        p = &matriz[linha][coluna];
                        *p = '*';
                    }
                }
            }else if (j > b){
                for(coluna = j-1; coluna > b; coluna--){
                    if(matriz[linha][coluna] == '*'){
                        p = &matriz[linha][coluna];
                        *p = '°';
                    }else if(matriz[linha][coluna] == '°'){
                        p = &matriz[linha][coluna];
                        *p = '*';
                    }
                }
            }
            break;

        case 2:
            coluna = j;
            if(i < a){
                for(linha = i+1; linha < a; linha++){
                    if(matriz[linha][coluna] == '*'){
                        p = &matriz[linha][coluna];
                        *p = '°';
                    }else if(matriz[linha][coluna] == '°'){
                        p = &matriz[linha][coluna];
                        *p = '*';
                    }
                }
            }else if(i > a){
                for(linha = i-1; linha > a; linha--){
                    if(matriz[linha][coluna] == '*'){
                        p = &matriz[linha][coluna];
                        *p = '°';
                    }else if(matriz[linha][coluna] == '°'){
                        p = &matriz[linha][coluna];
                        *p = '*';
                    }
                }
            }
            break;

        case 3:
            if(j < b){
                for(linha = i-1, coluna = j+1; coluna < b; linha--, coluna++){
                    if(matriz[linha][coluna] == '*'){
                        p = &matriz[linha][coluna];
                        *p = '°';
                    }else if(matriz[linha][coluna] == '°'){
                        p = &matriz[linha][coluna];
                        *p = '*';
                    }
                }
            }else if(j > b){
                for(linha = i+1, coluna = j-1; coluna > b; linha++, coluna--){
                    if(matriz[linha][coluna] == '*'){
                        p = &matriz[linha][coluna];
                        *p = '°';
                    }else if(matriz[linha][coluna] == '°'){
                        p = &matriz[linha][coluna];
                        *p = '*';
                    }
                }
            }
            break;

        case 4:
            if(i < a){
                for(linha = i+1, coluna = j+1; linha < a; linha++, coluna++){
                    if(matriz[linha][coluna] == '*'){
                        p = &matriz[linha][coluna];
                        *p = '°';
                    }else if(matriz[linha][coluna] == '°'){
                        p = &matriz[linha][coluna];
                        *p = '*';
                    }
                }
            }else if(i > a){
                for(linha = i-1, coluna = j-1; linha > a; linha--, coluna--){
                    if(matriz[linha][coluna] == '*'){
                        p = &matriz[linha][coluna];
                        *p = '°';
                    }else if(matriz[linha][coluna] == '°'){
                        p = &matriz[linha][coluna];
                        *p = '*';
                    }
                }
            }
            break;
    }
}
int verificaVitoria(char matriz [9][9], char peca, int turno){
    int i, j, a, b, linha, coluna;
    int cont=0, contx=0, conto=0, x=0, o=0;

    struct coordenadas coop;
    struct coordenadas cood;
// o verificavitoria retorna 0 caso nenhum dos dois tenha vencido, 1 na vitoria do X, 2 na vitoria do O, 3 caso empate, e em falta de movimento 4 na vitoria do O ou 5 na vitoria do X
//verifica vitória nas linhas
    for (i = 0 ; i < 9 ; i++){
        for (j = 0 ; j <= 4 ; j++){
            contx=0, conto=0;
            for(cont = 0, b = j; cont<5; cont++, b++){
                if(matriz[i][b] == '*')contx++;
                else if(matriz[i][b] == '°')conto++;
            }
            if (contx == 5) x=1;
            if (conto == 5) o=2;
        }
    }
//verifica vitória nas colunas
    for (j = 0 ; j < 9 ; j++){
        for (i = 0 ; i <= 4 ; i++){
            contx=0, conto=0;
            for(cont = 0, a = i; cont < 5; cont++, a++){
                if(matriz[a][j] == '*') contx++;
                else if(matriz[a][j] == '°') conto++;
            }
            if (contx == 5) x=1;
            if (conto == 5) o=2;
        }
    }

//verifica vitória nas diagon secund
    //essa parte só pega "metade do tabuleiro"
    for (i = 4; i < 9; i++){
        for(a = i, b = 0; a >= 4; a--, b++){
            contx = 0, conto = 0;
            for(cont = 0, linha = a, coluna = b; cont < 5; linha--, coluna++, cont++){
                if(matriz[linha][coluna] == '*')contx++;
                else if(matriz[linha][coluna] == '°')conto++;
            }
            if(contx == 5) x=1;
            if(conto == 5) o=2;
        }
    }
    //outra metade do tabuleiro
    for (j = 4; j > 0; j--){
        for(b = j, a = 8; b <= 4; b++, a--){
            contx = 0, conto = 0;
            for(cont = 0, linha = a, coluna = b; cont < 5; linha--, coluna++, cont++){
                if(matriz[linha][coluna] == '*')contx++;
                else if(matriz[linha][coluna] == '°')conto++;
            }
            if (contx == 5) x=1;
            if (conto == 5) o=2;
        }
    }

//verifica vitória nas diagon princp
    //essa parte só pega metade do tabuleiro
    for (i = 4; i < 9; i++){
        for (a = i, b = 8; a >= 4; a--, b--){
            contx = 0, conto = 0;
            for (cont = 0, linha = a, coluna = b; cont < 5; linha--, coluna--, cont++){
                if (matriz[linha][coluna] == '*')contx++;
                else if (matriz[linha][coluna] == '°')conto++;
            }
            if (contx == 5) x=1;
            if (conto == 5) o=2;
        }
    }
    //essa parte pega a outra metade do tabuleiro
    for (j = 4; j < 8; j++){
        for (b = j, a = 8; b >= 4; b--, a--){
            contx = 0, conto = 0;
            for (cont = 0, linha = a, coluna = b; cont < 5; linha--, coluna--, cont++){
                if (matriz[linha][coluna] == '*')contx++;
                else if (matriz[linha][coluna] == '°')conto++;
            }
            if (contx == 5) x=1;
            if (conto == 5) o=2;
        }
    }
    if (x+o > 0) return x+o;
        for (coop.coor[0] = 0 ; coop.coor[0] < 9 ; coop.coor[0]++)
            for (coop.coor[1] = 0 ; coop.coor[1] < 9 ; coop.coor[1]++)
                if(matriz[coop.coor[0]][coop.coor[1]] == peca){
                    for (cood.coor[0] = 0 ; cood.coor[0] < 9 ; cood.coor[0]++)
                        for (cood.coor[1] = 0 ; cood.coor[1] < 9 ; cood.coor[1]++)
                            if (validaMovimento(coop, cood, matriz)) return 0;
}
return 4+(turno%2);
}
int main(){
    system("color 0E");
    char  destino[3], partida[3], matriz[9][9], peca, aliado, enter;
    int i, j, turno = 1, a, b, count;
    struct coordenadas coop, cood;
	setlocale(LC_ALL, "Portuguese");
	printf("\n\n     VAMOS COMEÇAR O JOGO!\n");
    printf("\n     --------------------------------------------------");
	printf("\n     Jogador X - aliados *  (o jogador X começa o jogo)");
    printf("\n     Jogador O - aliados °");
    printf("\n     --------------------------------------------------");
    printf("\n\n     APERTE ENTER PRA INICIAR");
    setbuf(stdin, NULL);
    scanf("%c", &enter);
//  Para gerar aleatoriamente as primeiras peças
    srand(time(NULL));
    for (i = 0 ; i < 9 ; i++)
        for (j = 0 ; j < 9 ; j++)
                matriz[i][j] = ' ';
    peca = 'O';
// Gerando as peças
    for(count = 0; count<10;){
        if (count == 5) peca = 'X';
        a = rand() % 9;
        b = rand() % 9;
        if(matriz[a][b] == ' '){
            matriz[a][b] = peca;
            count++;
        }
    }

//  Rodadas
    while (1){
        turno++;
        if(turno%2){ peca = 'O'; aliado = '°';} else {peca = 'X'; aliado = '*';}
        if (verificaVitoria(matriz, peca, turno)) break;
        while(1){
            exibeTabuleiro(matriz, turno, peca);
            printf("\n\n     Selecione Uma Peça  -> ");
            setbuf(stdin, NULL);
            fgets(partida, 3, stdin);
            while(getchar() != '\n');
            coop = conversor(partida);
            if((validaPeca(coop, naCasa(coop, matriz), peca, matriz) == 1)&&((tolower(partida[0]) >= 'a' && tolower(partida[0]) <= 'i')&&(partida[1] >= '1' && partida[1] <= '9')))break;
            exibeTabuleiro(matriz, turno, peca);
            if(validaPeca(coop, naCasa(coop, matriz), peca, matriz) == 3){
                printf("\n     SELECIONE UMA PEÇA %c QUE POSSA SE MOVIMENTAR\n", peca);
                printf("\n     ENTER PRA CONTINUAR");
                setbuf(stdin, NULL);
                scanf("%c", &enter);
            }else{
                printf("\n     SELECIONE UMA CASA QUE POSSUA UMA PEÇA %c!\n", peca);
                printf("\n     ENTER PRA CONTINUAR");
                setbuf(stdin, NULL);
                scanf("%c", &enter);
            }}
        while(1){
            exibeTabuleiro(matriz, turno, peca);
            printf("\n\n     Selecione Uma Peça  -> %s\n", partida);
            printf("     Selecione O Destino -> ");
            setbuf(stdin, NULL);
            fgets(destino, 3, stdin);
            while(getchar() != '\n');
            cood = conversor(destino);
            if((validaMovimento(coop, cood, matriz))&&((tolower(destino[0]) >= 'a' && tolower(destino[0]) <= 'i')&&(destino[1] >= '1' && destino[1] <= '9')))break;
            exibeTabuleiro(matriz, turno, peca);
            printf("\n     MOVIMENTO INVÁLIDO! ESCOLHA UM DESTINO POSSÍVEL!\n");
            printf("\n     ENTER PRA CONTINUAR");
            setbuf(stdin, NULL);
            scanf("%c", &enter);
        }
        movimento(&matriz[coop.coor[0]][coop.coor[1]], &matriz[cood.coor[0]][cood.coor[1]]);
        matriz[coop.coor[0]][coop.coor[1]] = aliado;
        verificaConversao(coop, cood, matriz);
}
    if (verificaVitoria(matriz, peca, turno)==1){ exibeTabuleiro(matriz, turno, peca); printf("\n     Vitória do X no %dº turno\n\n", turno/2);}
    if (verificaVitoria(matriz, peca, turno)==2){ exibeTabuleiro(matriz, turno, peca); printf("\n     Vitória do O no %dº turno\n\n", turno/2);}
    if (verificaVitoria(matriz, peca, turno)==3){ exibeTabuleiro(matriz, turno, peca); printf("\n     Empate no %dº turno\n\n", turno/2);}
    if (verificaVitoria(matriz, peca, turno)==4){ exibeTabuleiro(matriz, turno, peca); printf("\n     Vitória do O no %dº turno por falta de movimento do adversário\n\n",turno/2);}
    if (verificaVitoria(matriz, peca, turno)==5){ exibeTabuleiro(matriz, turno, peca); printf("\n     Vitória do X no %dº turno por falta de movimento do adversário\n\n",turno/2);}
system("pause");
}
