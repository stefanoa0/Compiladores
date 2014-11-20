#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include <stdarg.h>

#define VOIDVALUE "-1"
#define PROFUNDIDADE 5
#define LARGURA 12
#define CHUNK 33
#define SIZE 4096
#define varSize 16
#define T 4096
#define NTERMIMAL(x) x == "E" || x == "M" || x == "A" || x == "C"
#define Digit(x) x>= '0' && x <= '9'
#define Letra(x) x>= 'a' && x <= 'z' || x>= 'A' && x <= 'Z'
#define Variavel(x) x == 'a' || x == 'b' || x == 'c' || x == 'x' || x == 'y' || x == 'z'
#define SEP(x) x == ',' || x ==';' || x == ' ' || x == '='
#define OP(x) x == "+" || x == "-" || x == "*" || x == "/"
#define NT(x) x == '\t' || x == ' ' ||x == '\n'

struct keyWord{
        char *lexeme;
        int column;
        int line;
        char value[16];
        struct keyWord *collision;
        int Tree;
    };

    typedef struct keyWord * kw;

    struct Tpilha
    {
        char *elem;
        struct Tpilha *prox;
    }; typedef struct Tpilha p;

    struct Tfila{
        char *elem;
        struct Tfila *prox;
    }; typedef struct Tfila f;

    struct TpilhaInt{
        int elem;
        struct TpilhaInt *prox;
    }; typedef struct TpilhaInt pInt;

    struct Tstruct
    {
        char *elem;
    }; typedef struct Tstruct node;

    struct Tstruct2
{
    //o índice do elemento na árvore N
    int elem;

    //formato da árvore

    //    (paidoselementos)
    //     /  |      |   \
    //    /   |      |    \
    //(fil1)  (fil2) (fil3) (fil4)  (fil5) ( fil6)
    struct Tstruct2 *fil1;
    struct Tstruct2 *fil2;
    struct Tstruct2 *fil3;
    struct Tstruct2 *fil4;
    struct Tstruct2 *fil5;
    struct Tstruct2 *fil6;
}; typedef struct Tstruct2 no;


    void inserirArvBQ(no **pai, no *filho, ...);
    void preorder(no **arvBQ);
    void inorderIfWhile(no **arvBQ);
    void inorderFor(no **arvBQ);
    void alocarNo(no **arv, int elem);

    void pushInt(pInt **s, int elem);
    int popInt(pInt **s);

    void insere(f **s, char elem[]);
    char* recupera(f **s);
    int getSize(char *s);

    void push(p **s, char elem[]);
    char* pop(p **s);
    int getTam(char *s);
    char* top(p **s);
    void increase(int);
    void makeQueue();
    void retorna_erro(int linha, int coluna);
    void erro(int erro);
    void alocarArvoreN(node **arvN);
    void inserirArvoreN(node **arvN, char *elem, int pai);
    void iniciarFilhosDeElem(node **arvN, int elem);
    void imprimirNivel(node **arvN, int nivel);
    int getPai(node **arvN, int elem);


    struct keyWord * queue;

    int linha;
    int coluna;
    int vet[100], vetInd = 0;
    FILE *fpObj;

int main(int argc, char *argv[]){
    FILE *fp, *fp1;
    int te = pow(LARGURA, PROFUNDIDADE);
    int paiRaiz = -1, treeId=0;
    int filhosDeRaiz = 0;
    node *arvN;
    char file[256], var[varSize], varValue[varSize];
    char *codigo_fonte;
    f *q=NULL;
    pInt *q2=NULL;
    pInt *st=NULL;
    pInt *lh=NULL;
    int countQueue = CHUNK, i, fileSize, varCount=0, valueCount=0, count=0, hash, k, VarFlag, flag=0, flagPop=0;
    codigo_fonte = (char*) malloc(sizeof(char)*SIZE);
    p *s=NULL;
    char elem[T];
    alocarArvoreN(&arvN);

    //--------------------------------
    for(vetInd=0;vetInd<100;vetInd++)
        vet[vetInd]=-1;
    vetInd = 0;
    //--------------------------------

    if(argc != 2){
        printf("Digite o nome do arquivo: ");
        gets(file);
        codigo_fonte = file;
    }
    else{
        codigo_fonte = argv[1];
    }

    if((fp=fopen(codigo_fonte, "r"))== NULL){
            printf("Erro! Seu arquivo esta vazio!");
            exit(1);
    }


    for(i=0;!feof(fp);i++)
        fscanf(fp, "%c", &codigo_fonte[i]);
    fileSize=i;
    fclose(fp);
    codigo_fonte[++fileSize] = 0;
    puts(codigo_fonte);
    printf("\nTamanho do arquivo :%d\n", fileSize);

    makeQueue();
    //para não ficar sem valores na hash
    for (k=0; k<CHUNK;k++)
        queue[k].lexeme = "--" ;

    char variavel[17];
    int var_cont = 0;
    linha=0;
    coluna=0;
    int indice = 0;
    int var_linha = 0;
    int var_coluna = 0;

    int valor_linha = 0;
    int valor_coluna = 0;

    int while_linha = 0;
    int while_coluna = 0;

    int main_linha = 0;
    int main_coluna = 0;

    int for_linha = 0;
    int for_coluna = 0;

    int aparen_linha = 0;
    int aparen_coluna = 0;

    int fparen_linha = 0;
    int fparen_coluna = 0;

    int achave_linha = 0;
    int achave_coluna = 0;

    int fchave_linha = 0;
    int fchave_coluna = 0;

    int if_linha = 0;
    int if_coluna = 0;

    int ptvirg_linha = 0;
    int ptvirg_coluna = 0;

    int igual_linha;
    int igual_coluna;

    int soma_linha;
    int soma_coluna;

    int mult_linha;
    int mult_coluna;

    int subtra_linha;
    int subtra_coluna;

    int divis_linha;
    int divis_coluna;

    int return_linha;
    int return_coluna;


    //initializing stack
    push(&s, "M");
    inserirArvoreN(&arvN, "M", paiRaiz);

    while(flag == 0 && s){while(s){

        while(codigo_fonte[indice] == 10){
            linha++;
            coluna=0; //salto de linha
            indice++;
            //break;
        }//else

        // caracteres ignorados
        while(codigo_fonte[indice]==' ' || codigo_fonte[indice]=='\t'){
            indice++;
            coluna++;
            //break;
        }
        /*if(strcmp(top(&s),reader[i]) == 0){
                pop(&s);
        }*/

        // main
        if ((strcmp(top(&s),"M") == 0)){
            //while(codigo_fonte[indice] == ' '){ indice++;coluna++;}
            pop(&s);
            push(&s,"}");
            push(&s,";");
            push(&s,")");
            push(&s,"E");
            push(&s,"(");
            push(&s,"return");
            push(&s,";");
            push(&s,"C");
            push(&s,"{");
            push(&s,")");
            push(&s,"(");
            push(&s,"main");
            insere(&q, "main");

            inserirArvoreN(&arvN, "main", filhosDeRaiz);
            inserirArvoreN(&arvN, "(", filhosDeRaiz);
            inserirArvoreN(&arvN, ")", filhosDeRaiz);
            inserirArvoreN(&arvN, "{", filhosDeRaiz);
            inserirArvoreN(&arvN, "C", filhosDeRaiz);
            inserirArvoreN(&arvN, ";", filhosDeRaiz);
            inserirArvoreN(&arvN, "return", filhosDeRaiz);
            inserirArvoreN(&arvN, "(", filhosDeRaiz);
            inserirArvoreN(&arvN, "E", filhosDeRaiz);
            inserirArvoreN(&arvN, ")", filhosDeRaiz);
            inserirArvoreN(&arvN, ";", filhosDeRaiz);
            inserirArvoreN(&arvN, "}", filhosDeRaiz);

            pushInt(&q2, 8);
            pushInt(&q2, 4);

            pushInt(&st, 11);
            pushInt(&st, 3);
            pushInt(&lh, 1);


            if(codigo_fonte[indice]== 'm'){
                while(codigo_fonte[indice] == ' '){ indice++;coluna++;}
                main_linha = linha;
                main_coluna = coluna;
                if(codigo_fonte[++indice] == 'a'){coluna++;
                    if(codigo_fonte[++indice] == 'i'){coluna++;
                        if(codigo_fonte[++indice]== 'n'){coluna++;
                            queue[countQueue].column = main_coluna;
                            queue[countQueue].line = main_linha;
                            queue[countQueue].lexeme = "TK_main";
                            queue[countQueue].value[0] = '-';
                            queue[countQueue].collision= NULL;
                            queue[countQueue].Tree = 0;
                            countQueue++;

                            printf("\nTK_main, %d, %d\n", main_linha, main_coluna);
                            indice++;
                            coluna++;
                        }
                        else{
                            retorna_erro(main_linha,main_coluna+3);
                            }
                    }
                    else{
                        retorna_erro(main_linha,main_coluna+2);
                        }
                }
                else{
                    retorna_erro(main_linha,++main_coluna);
                }
               // break;
            }
        }
        else
        if ((strcmp(top(&s),"C") == 0) && (codigo_fonte[indice] != ' ')){
            // while
            if(codigo_fonte[indice]== 'w'){
                while_linha = linha;
                while_coluna = coluna;
                if(codigo_fonte[++indice] == 'h'){coluna++;
                    if(codigo_fonte[++indice]== 'i'){coluna++;
                        if(codigo_fonte[++indice]=='l'){coluna++;
                            if(codigo_fonte[++indice]=='e'){coluna++;
                                paiRaiz = popInt(&q2);
                                queue[countQueue].column = while_coluna;
                                queue[countQueue].line = while_linha;
                                queue[countQueue].lexeme = "TK_while";
                                queue[countQueue].value[0] = '-';
                                queue[countQueue].collision= NULL;
                                queue[countQueue].Tree= paiRaiz;

                                printf("\n%s, %d, %d\n", queue[countQueue].lexeme, queue[countQueue].line, queue[countQueue].column);

                                indice++;
                                coluna++;
                                countQueue++;
                                pop(&s);
                                push(&s, "}");
                                push(&s, ";");
                                push(&s, "C");
                                push(&s, "{");
                                push(&s, ")");
                                push(&s, "E");
                                push(&s, "(");
                                push(&s, "while");

                                insere(&q, "while");

                                inserirArvoreN(&arvN, "while", paiRaiz);
                                inserirArvoreN(&arvN, "(", paiRaiz );
                                inserirArvoreN(&arvN, "E", paiRaiz );
                                inserirArvoreN(&arvN, ")", paiRaiz );
                                inserirArvoreN(&arvN, "{", paiRaiz );
                                inserirArvoreN(&arvN, "C", paiRaiz );
                                inserirArvoreN(&arvN, ";", paiRaiz );
                                inserirArvoreN(&arvN, "}", paiRaiz );

                                pushInt(&q2, paiRaiz*12+5);
                                pushInt(&q2, paiRaiz*12+2);
                                pushInt(&st, paiRaiz*12+4);
                                pushInt(&st, paiRaiz*12+7);
                            }
                            else{
                                retorna_erro(while_linha,while_coluna+4);
                            }
                        }
                        else{
                            retorna_erro(while_linha,while_coluna+3);
                            }
                    }
                    else{
                        retorna_erro(while_linha,while_coluna+2);
                    }
                }
                else{
                    retorna_erro(while_linha,++while_coluna);
                }
                //break;
            }
            else
            // for
            if(codigo_fonte[indice] == 'f'){
                for_linha = linha;
                for_coluna = coluna;
                if(codigo_fonte[++indice] == 'o'){coluna++;
                    if(codigo_fonte[++indice] == 'r'){coluna++;
                        paiRaiz = popInt(&q2);
                        queue[countQueue].column = for_coluna;
                        queue[countQueue].line = for_linha;
                        queue[countQueue].lexeme = "TK_for";
                        queue[countQueue].value[0] = '-';
                        queue[countQueue].collision= NULL;
                        queue[countQueue].Tree = paiRaiz;

                        printf("\nTK_for, %d, %d\n", for_linha, for_coluna);
                        indice++;
                        coluna++;
                        countQueue++;
                        pop(&s);
                        push(&s, "}");
                        push(&s, ";");
                        push(&s, "C");
                        push(&s, "{");
                        push(&s, ")");
                        push(&s, "E");
                        push(&s, ";");
                        push(&s, "E");
                        push(&s, ";");
                        push(&s, "E");
                        push(&s, "(");
                        push(&s, "for");

                        insere(&q, "for");

                        inserirArvoreN(&arvN, "for", paiRaiz);
                        inserirArvoreN(&arvN, "(", paiRaiz );
                        inserirArvoreN(&arvN, "E", paiRaiz );
                        inserirArvoreN(&arvN, ";", paiRaiz );
                        inserirArvoreN(&arvN, "E", paiRaiz );
                        inserirArvoreN(&arvN, ";", paiRaiz );
                        inserirArvoreN(&arvN, "E", paiRaiz );
                        inserirArvoreN(&arvN, ")", paiRaiz );
                        inserirArvoreN(&arvN, "{", paiRaiz );
                        inserirArvoreN(&arvN, "C", paiRaiz );
                        inserirArvoreN(&arvN, ";", paiRaiz );
                        inserirArvoreN(&arvN, "}", paiRaiz );

                        // ñ terminais
                        pushInt(&q2, 12*paiRaiz+9);
                        pushInt(&q2, 12*paiRaiz+6);
                        pushInt(&q2, 12*paiRaiz+4);
                        pushInt(&q2, 12*paiRaiz+2);

                        pushInt(&st, paiRaiz*12+8);
                        pushInt(&st, paiRaiz*12+11);
                    }
                    else{
                        retorna_erro(for_linha,for_coluna+2);
                    }
                }
                else{
                    retorna_erro(for_linha,++for_coluna);
                }
                //break;
            }else
            // if
            if(codigo_fonte[indice] == 'i'){
                if_linha = linha;
                if_coluna = coluna;
                if(codigo_fonte[++indice] == 'f'){coluna++;
                    paiRaiz = popInt(&q2);
                    queue[countQueue].column = if_coluna;
                    queue[countQueue].line = if_linha;
                    queue[countQueue].lexeme = "TK_if";
                    queue[countQueue].value[0] = '-';
                    queue[countQueue].Tree= paiRaiz;
                    queue[countQueue].collision= NULL;
                    printf("\nTk_If, %d, %d\n", if_linha, if_coluna);
                    indice++;
                    coluna++;
                    countQueue++;

                    pop(&s);
                    push(&s, "}");
                    push(&s, ";");
                    push(&s, "C");
                    push(&s, "{");
                    push(&s, ")");
                    push(&s, "E");
                    push(&s, "(");
                    push(&s, "if");

                    insere(&q, "if");
                    pushInt(&st, paiRaiz*12+4);
                    pushInt(&st, paiRaiz*12+7);

                    inserirArvoreN(&arvN, "if", paiRaiz);
                    inserirArvoreN(&arvN, "(", paiRaiz );
                    inserirArvoreN(&arvN, "E", paiRaiz );
                    inserirArvoreN(&arvN, ")", paiRaiz );
                    inserirArvoreN(&arvN, "{", paiRaiz );
                    inserirArvoreN(&arvN, "C", paiRaiz );
                    inserirArvoreN(&arvN, ";", paiRaiz );
                    inserirArvoreN(&arvN, "}", paiRaiz );

                    pushInt(&q2, LARGURA*paiRaiz+5);
                    pushInt(&q2, LARGURA*paiRaiz+2);

                }
                else{
                    retorna_erro(if_linha,++if_coluna);
                }

                //break;
            }else
            //--------------------------var--------------------------------------
            if(Variavel(codigo_fonte[indice])){
                varCount=0;
                var_coluna = coluna;
                var_linha = linha;
                while(Letra(codigo_fonte[indice]) || Digit(codigo_fonte[indice])){
                    if(SEP(codigo_fonte[indice])) break;
                    var[varCount] = codigo_fonte[indice];
                    indice++;
                    varCount++;
                    coluna++;

                }
                paiRaiz = popInt(&q2);

				var[varCount] = '\0';
				hash = (int) var%CHUNK;
				//colocando variavel na hash
                queue[hash].column = var_coluna;
                queue[hash].line = var_linha;
                queue[hash].lexeme = "TK_ident";
                queue[hash].value[0] = '-';
                queue[hash].collision= NULL;
                queue[hash].Tree= paiRaiz;

                pop(&s);
				push(&s, var);
				insere(&q, var);
                printf("\n%s, %d, %d, %s \n",queue[hash].lexeme, queue[hash].line, queue[hash].column, queue[hash].value);

                indice++;
                coluna++;
                countQueue++;

                inserirArvoreN(&arvN, var, paiRaiz);

			}else

				//constante
				if(Digit(codigo_fonte[indice])){
					valor_coluna = coluna;
					valor_linha = linha;
					valueCount = 0;
					while(Digit(codigo_fonte[indice])){
						varValue[valueCount] = codigo_fonte[indice];
						indice++; valueCount++; coluna++;
					}
					//countQueue--;

					paiRaiz=popInt(&q2);

					indice--;coluna--;
					varValue[valueCount] = '\0';

					//colocando variavel na hash
                    queue[countQueue].column = valor_coluna;
                    queue[countQueue].line = valor_linha;
                    queue[countQueue].lexeme = "TK_const";
                    strcpy(queue[countQueue].value, varValue);
                    queue[countQueue].collision= NULL;
                    queue[countQueue].Tree = paiRaiz;

					pop(&s);
					push(&s, varValue);
					insere(&q, varValue);
					printf("\n%s, %d, %d, %s\n",queue[countQueue].lexeme, queue[countQueue].line, queue[countQueue].column, queue[countQueue].value);

                    inserirArvoreN(&arvN, varValue, paiRaiz);

					indice++;
                    coluna++;
                    countQueue++;

				}else
				if(codigo_fonte[indice] =='('){
                    pop(&s);
                    push(&s, ")");
                    push(&s, "A");
                    push(&s, "(");

                    insere(&q, "(");

                    paiRaiz = popInt(&q2);

                    inserirArvoreN(&arvN, "(", paiRaiz );
                    inserirArvoreN(&arvN, "A", paiRaiz );
                    inserirArvoreN(&arvN, ")", paiRaiz );

                    pushInt(&q2, paiRaiz*12+1);

                    aparen_coluna = coluna;
					aparen_linha = linha;
                    queue[countQueue].column = aparen_coluna;
                    queue[countQueue].line = aparen_linha;
                    queue[countQueue].lexeme = "TK_APar";
                    queue[countQueue].value[0] = '-';
                    queue[countQueue].collision= NULL;

                    printf("\n%s, %d, %d\n",queue[countQueue].lexeme, queue[countQueue].line, queue[countQueue].column);

                    indice++;
                    coluna++;
                    countQueue++;
				}

    }else
        if ((strcmp(top(&s),"A") == 0 )){
            if(Variavel(codigo_fonte[indice])){
                varCount=0;
                var_coluna = coluna;
                var_linha = linha;
                while(Letra(codigo_fonte[indice]) || Digit(codigo_fonte[indice])){
                    if(SEP(codigo_fonte[indice])) break;
                    var[varCount] = codigo_fonte[indice];
                    indice++;
                    varCount++;
                    coluna++;
                }
                paiRaiz = popInt(&q2);
                //lê espaço em branco
                while(codigo_fonte[indice] == ' ') indice++;
                if( codigo_fonte[indice] == '=') {
                    VarFlag++;
                    queue[countQueue].column = coluna;
                    queue[countQueue].line = linha;
                    queue[countQueue].lexeme = "TK_igual";
                    queue[countQueue].value[0] = '-';
                    queue[countQueue].collision= NULL;
                    queue[countQueue].Tree= (int)paiRaiz/12;

                    indice++; coluna++;
                    valueCount=0;
                    //lê espaço em branco
                    while(codigo_fonte[indice] == ' ') {indice++; coluna++;}
                    if(Digit(codigo_fonte[indice])){
                        valor_coluna = coluna;
                        valor_linha = linha;

                        while(Digit(codigo_fonte[indice])){
                            varValue[valueCount] = codigo_fonte[indice];
                            indice++; valueCount++; coluna++;
                        }
                    }
                    else{
                        flag = 2;
                        break;
                    }
                }
                else{
                    flag = 2;
                    break;
                }
                indice--;coluna--;
                varValue[valueCount] = '\0';
                var[varCount] = '\0';

                //---stack----
                    pop(&s);
                    push(&s, "E");
                    push(&s, "=");
                    push(&s, var);

                    insere(&q, var);
                    insere(&q, "=");
                    insere(&q, "E");

                    //queue[countQueue].Tree = paiRaiz*LARGURA+1;

                    inserirArvoreN(&arvN, var, paiRaiz);
                    inserirArvoreN(&arvN, "=", paiRaiz );
                    inserirArvoreN(&arvN, varValue, paiRaiz );
                    char var1[16];
                    strcpy(var1,varValue);

                //---stack----
                hash = (int) var%CHUNK;
                //colocando digito na tabela
                countQueue++;
                queue[countQueue].column = valor_coluna;
                queue[countQueue].line = valor_linha;
                queue[countQueue].lexeme = "TK_const";
                strcpy(queue[countQueue].value, var1);
                queue[countQueue].collision= NULL;
                queue[countQueue].Tree = paiRaiz;

                //colocando variavel na hash
                queue[hash].column = var_coluna;
                queue[hash].line = var_linha;
                queue[hash].lexeme = "TK_ident";
                strcpy(queue[hash].value, var1);
                queue[hash].collision= NULL;
                queue[hash].Tree= paiRaiz+1;

                pushInt(&lh, paiRaiz*LARGURA);
                pushInt(&lh, paiRaiz*LARGURA+1);
                pushInt(&lh, paiRaiz*LARGURA+2);

                printf("\n%s, %d, %d, %s \n",queue[hash].lexeme, queue[hash].line, queue[hash].column, queue[hash].value);
                printf("\n%s, %d, %d\n",queue[countQueue-1].lexeme, queue[countQueue-1].line, queue[countQueue-1].column);
                printf("\n%s, %d, %d\n",queue[countQueue].lexeme, queue[countQueue].line, queue[countQueue].column);

                countQueue++;
                indice++;
                coluna++;
            }

        }else
        if (strcmp(top(&s),"E") == 0){
            //(EXE)
            if(codigo_fonte[indice] == '('){
                pop(&s);
                push(&s, ")");
                push(&s, "E");
                push(&s, "X");
                push(&s, "E");
                push(&s, "(");

                insere(&q, "(");

                paiRaiz = popInt(&q2);

                inserirArvoreN(&arvN, "(", paiRaiz );
                inserirArvoreN(&arvN, "E", paiRaiz );
                inserirArvoreN(&arvN, "X", paiRaiz );
                inserirArvoreN(&arvN, "E", paiRaiz );
                inserirArvoreN(&arvN, ")", paiRaiz );

                pushInt(&q2, paiRaiz+3);
                pushInt(&q2, paiRaiz+2);
                pushInt(&q2, paiRaiz+1);

                aparen_coluna = coluna;
                aparen_linha = linha;
                queue[countQueue].column = aparen_coluna;
                queue[countQueue].line = aparen_linha;
                queue[countQueue].lexeme = "TK_APar";
                queue[countQueue].value[0] = '-';
                queue[countQueue].collision= NULL;
                queue[countQueue].Tree= paiRaiz*LARGURA;

                printf("\n%s, %d, %d\n",queue[countQueue].lexeme, queue[countQueue].line, queue[countQueue].column);

                indice++;
                coluna++;
                countQueue++;
            }else
            //digito
            if(Digit(codigo_fonte[indice])){
                valor_coluna = coluna;
                valor_linha = linha;
                valueCount=0;
                while(Digit(codigo_fonte[indice])){
                    varValue[valueCount] = codigo_fonte[indice];
                    indice++; valueCount++; coluna++;
                }
                indice--; coluna--;
                varValue[valueCount] = '\0';

                char var2[16];

                strcpy(var2, varValue);

                //stack-------
                pop(&s);
                push(&s, varValue);
                insere(&q, varValue);
                //stack-------
                paiRaiz = popInt(&q2);

                inserirArvoreN(&arvN, varValue, paiRaiz);

                //colocando variavel na hash
                queue[countQueue].column = valor_coluna ;
                queue[countQueue].line = valor_linha;
                queue[countQueue].lexeme = "TK_const";
                strcpy(queue[countQueue].value, var2);
                queue[countQueue].collision= NULL;
                queue[countQueue].Tree= paiRaiz;

                printf("\n%s, %d, %d, %s\n",queue[countQueue].lexeme, queue[countQueue].line, queue[countQueue].column, varValue);
                countQueue++;
                indice++; coluna++;

            }else
            //var
            if(Letra(codigo_fonte[indice])){
                varCount=0;
                var_coluna = coluna;
                var_linha = linha;
                while(Letra(codigo_fonte[indice]) || Digit(codigo_fonte[indice])){
                    if(SEP(codigo_fonte[indice])) break;
                    var[varCount] = codigo_fonte[indice];
                    indice++;
                    varCount++;
                    coluna++;
                }
                indice--;coluna--;
                var[varCount] = '\0';
                //stack-------
                pop(&s);
                push(&s, var);
                insere(&q, var);
                //stack-------

                paiRaiz = popInt(&q2);

                inserirArvoreN(&arvN, var, paiRaiz);

                hash = (int) var%CHUNK;
                //colocando variavel na hash
                queue[hash].column = var_coluna;
                queue[hash].line = var_linha;
                queue[hash].lexeme = "TK_ident";
                queue[hash].value[0] = '-';
                queue[hash].collision= NULL;
                queue[hash].Tree= paiRaiz;

                printf("\n%s, %d, %d, %s \n",queue[hash].lexeme, queue[hash].line, queue[hash].column, queue[hash].value);
                indice++; coluna++;
            }
        }else
        // +
        if ((strcmp(top(&s),"X") == 0 )&& (codigo_fonte[indice] != ' ')){
            if(codigo_fonte[indice] == '+'){
                pop(&s);
                push(&s, "+");
                insere(&q, "+");

                paiRaiz = popInt(&q2);

                inserirArvoreN(&arvN, "+", paiRaiz);

                soma_linha = linha;
                soma_coluna = coluna;
                queue[countQueue].column = soma_coluna;
                queue[countQueue].line = soma_linha;
                queue[countQueue].lexeme = "TK_soma";
                queue[countQueue].value[0] = '-';
                queue[countQueue].collision= NULL;
                queue[countQueue].Tree= paiRaiz;
                printf("\nTk_Soma, %d, %d\n", soma_linha, soma_coluna);
                indice++;
                coluna++;
                countQueue++;
                //break;
            }else
            // *
            if(codigo_fonte[indice] == '*'){
                pop(&s);
                push(&s, "*");
                insere(&q, "*");

                paiRaiz = popInt(&q2);

                inserirArvoreN(&arvN, "*", paiRaiz);

                mult_linha = linha;
                mult_coluna = coluna;
                queue[countQueue].column = mult_coluna;
                queue[countQueue].line = mult_linha;
                queue[countQueue].lexeme = "TK_mult";
                queue[countQueue].value[0] = '-';
                queue[countQueue].collision= NULL;
                queue[countQueue].Tree= paiRaiz;
                printf("\nTk_Mult, %d, %d\n", mult_linha, mult_coluna);
                indice++;
                coluna++;
                countQueue++;
                //break;
            }else
            // -
            if(codigo_fonte[indice] == '-'){
                pop(&s);
                push(&s, "-");
                insere(&q, "-");

                paiRaiz = popInt(&q2);

                inserirArvoreN(&arvN, "-", paiRaiz);

                subtra_linha = linha;
                subtra_coluna = coluna;
                queue[countQueue].column = subtra_coluna;
                queue[countQueue].line = subtra_linha;
                queue[countQueue].lexeme = "TK_subtra";
                queue[countQueue].value[0] = '-';
                queue[countQueue].collision= NULL;
                queue[countQueue].Tree= paiRaiz;
                printf("\nTk_Subt, %d, %d\n", subtra_linha, subtra_coluna);
                indice++;
                coluna++;
                countQueue++;
                //break;
            }else
            // /
            if(codigo_fonte[indice] == '/'){
                pop(&s);
                push(&s, "/");
                insere(&q, "/");

                paiRaiz = popInt(&q2);

                inserirArvoreN(&arvN, "/", paiRaiz);

                divis_linha = linha;
                divis_coluna = coluna;
                queue[countQueue].column = divis_coluna;
                queue[countQueue].line = divis_linha;
                queue[countQueue].lexeme = "TK_divis";
                queue[countQueue].value[0] = '-';
                queue[countQueue].collision= NULL;
                queue[countQueue].Tree= paiRaiz;
                printf("\nTk_Divs, %d, %d\n", divis_linha, divis_coluna);
                indice++;
                coluna++;
                countQueue++;
                //break;
            }
        }else
        //return
        if(strcmp(top(&s),"return")==0){
        if(codigo_fonte[indice]== 'r'){
            return_linha = linha;
            return_coluna = coluna;
            if(codigo_fonte[++indice] == 'e'){coluna++;
                if(codigo_fonte[++indice]== 't'){coluna++;
                    if(codigo_fonte[++indice]=='u'){coluna++;
                        if(codigo_fonte[++indice]=='r'){coluna++;
                            if(codigo_fonte[++indice] = 'n'){
                                queue[countQueue].column = return_coluna;
                                queue[countQueue].line = return_linha;
                                queue[countQueue].lexeme = "TK_return";
                                queue[countQueue].value[0] = '-';
                                queue[countQueue].collision= NULL;

                                printf("\n%s, %d, %d\n",queue[countQueue].lexeme, queue[countQueue].line, queue[countQueue].column);

                                indice++;
                                coluna++;
                                countQueue++;

                                insere(&q, "return");
                            }
                            else{
                                retorna_erro(return_linha,return_coluna+5);
                            }
                        }
                        else{
                            retorna_erro(return_linha,return_coluna+4);
                        }
                    }
                    else{
                        retorna_erro(return_linha,return_coluna+3);
                        }
                }
                else{
                    retorna_erro(return_linha,return_coluna+2);
                }
            }
            else{
                retorna_erro(return_linha,++return_coluna);
            }
            //break;
        }
    }else
        // (
        if(codigo_fonte[indice] == '('){
            aparen_linha = linha;
            aparen_coluna = coluna;
            queue[countQueue].column = aparen_coluna;
            queue[countQueue].line = aparen_linha;
            queue[countQueue].lexeme = "TK_aparen";
            queue[countQueue].value[0] = '-';
            queue[countQueue].collision= NULL;
            printf("\nTk_APar, %d, %d\n", aparen_linha, aparen_coluna);
            indice++;
            coluna++;
            countQueue++;

            insere(&q, "(");
            //break;
        }else
        // )
        if(codigo_fonte[indice] == ')'){
            fparen_linha = linha;
            fparen_coluna = coluna;
            queue[countQueue].column = fparen_coluna;
            queue[countQueue].line = fparen_linha;
            queue[countQueue].lexeme = "TK_fparen";
            queue[countQueue].value[0] = '-';
            queue[countQueue].collision= NULL;
            printf("\nTk_FPar, %d, %d\n", fparen_linha, fparen_coluna);

            insere(&q, ")");
            indice++;
            coluna++;
            countQueue++;
            //break;
        }else
        // {
        if(codigo_fonte[indice] == '{'){
            paiRaiz=popInt(&st);
            achave_linha = linha;
            achave_coluna = coluna;
            queue[countQueue].column = achave_coluna;
            queue[countQueue].line = achave_linha;
            queue[countQueue].lexeme = "TK_achave";
            queue[countQueue].value[0] = '-';
            queue[countQueue].Tree= paiRaiz;
            queue[countQueue].collision= NULL;
            printf("\nTk_AChave, %d, %d\n", achave_linha, achave_coluna);
            indice++;
            coluna++;
            countQueue++;

            pushInt(&lh, paiRaiz);

            insere(&q, "{");
            //break;
        }else
        // }
        if(codigo_fonte[indice] == '}'){
            paiRaiz=popInt(&st);
            fchave_linha = linha;
            fchave_coluna = coluna;
            queue[countQueue].column = fchave_coluna;
            queue[countQueue].line = fchave_linha;
            queue[countQueue].lexeme = "TK_fchave";
            queue[countQueue].value[0] = '-';
            queue[countQueue].collision= NULL;
            queue[countQueue].Tree= paiRaiz;
            printf("\nTk_FChave, %d, %d\n", fchave_linha, fchave_coluna);
            indice++;
            coluna++;
            countQueue++;

            pushInt(&lh, paiRaiz);

            insere(&q, "}");
            //break;
        }else
        // =
        if(codigo_fonte[indice] == '='){
            igual_linha = linha;
            igual_coluna = coluna;
            queue[countQueue].column = igual_coluna;
            queue[countQueue].line = igual_linha;
            queue[countQueue].lexeme = "TK_igual";
            queue[countQueue].value[0] = '-';
            queue[countQueue].collision= NULL;
            printf("\n%s, %d, %d\n",queue[countQueue].lexeme, queue[countQueue].line, queue[countQueue].column);
            indice++;
            coluna++;
            countQueue++;

            insere(&q, "=");
            //break;
        }else
        // ;
        if(codigo_fonte[indice] == ';'){
            ptvirg_linha = linha;
            ptvirg_coluna = coluna;
            queue[countQueue].column = ptvirg_coluna;
            queue[countQueue].line = ptvirg_linha;
            queue[countQueue].lexeme = "TK_ptvirg";
            queue[countQueue].value[0] = '-';
            queue[countQueue].collision= NULL;
            printf("\nTk_PtVirg, %d, %d\n", ptvirg_linha, ptvirg_coluna);
            indice++;
            coluna++;
            countQueue++;

            insere(&q, ";");
            //break;
        }else

        // Salto de linha
        if(codigo_fonte[indice] == 10){
            linha++;
            coluna=0; //salto de linha
            indice++;
            //break;
        }else
        // caracteres ignorados
        if(codigo_fonte[indice]==' ' || codigo_fonte[indice]=='\t'){
            indice++;
            coluna++;
            //break;
        }


       // getchar();
        if(codigo_fonte[indice] != '\0')
    //    printf("\nFonte %c\t\n", codigo_fonte[indice]);
        if(s);
        else {flag = 1; break;}
        if(q);
        else {flag=2; break;}

    if(flagPop > 3){
        flag = 2;
        break;
    }

    if(s && q){
        if(strcmp(q->elem, top(&s)) == 0){
            pop(&s);
            recupera(&q);
            flagPop=0;
        }
    }

    //puts(q->elem);
//    indice++;
 //   coluna++;
    flagPop++;
    }
    // final do arquivo
    //if(codigo_fonte[indice] == 0){

        if((fp1=fopen("TokenTable.txt", "w"))== NULL){
            printf("erro");
            exit(2);
        }
        fprintf(fp1, "Lexeme\t\tLinha\tColuna\tValor\tTree\tindice\n\n");
        for (k=0; k<countQueue;k++){
            if(queue[k].lexeme != "--"){
                if(queue[k].Tree > te )
                    queue[k].Tree = -2;
                fprintf(fp1, "%s\t %d\t %d\t %s\t %d\t %d\n", queue[k].lexeme, queue[k].line, queue[k].column, queue[k].value, queue[k].Tree, k);
            }
        }
        fclose(fp1);


        //fclose(fp1);
       // puts("pilha\n");
       // while(s) puts(pop(&s));
      //  puts("fila\n");
     //   while(s) puts(recupera(&q));
 //       return 0;
   // }
}
            if(flag == 1){
                printf("erro na pilha");
            }
            if(flag == 2){
                printf("\n\nEntrada incorreta\n");
                printf("erro na:\n\t linha %d \n\tcoluna %d", linha, coluna);

                printf("\nPilha:\t");
                while(s){
                    printf("%s",pop(&s));
                }
            }


            if(flag == 0){
                printf("\n\nParse correto\n");

            int paiAtual=0;
            int countPai=1;
            int fila[6], countFila=0, i2, nextFather=0;
            no *arv, *f1, *f2, *f3, *f4, *f5, *f6, *aux;
            alocarNo(&arv, 33);
            aux = arv;
            printf("\npai atual %d\n", paiAtual);
            for (i=0; i<countQueue && countPai<countQueue;i++){
                for (k=0; k<countQueue;k++){
                    if(queue[k].lexeme != "--")
                        if (queue[k].Tree > 0 && queue[k].Tree<te){
                            if(queue[k].Tree >= paiAtual*12 && queue[k].Tree <= 12*(paiAtual+1)){
                            printf("Lexeme %s tree: %d \n", queue[k].lexeme, queue[k].Tree);
                            fila[countFila]=k;
                            if(queue[k].lexeme == "TK_if" || queue[k].lexeme  == "TK_while" || queue[k].lexeme  == "TK_for" || queue[k].lexeme  == "TK_soma" || queue[k].lexeme  == "TK_subtra" || queue[k].lexeme  == "TK_mult" || queue[k].lexeme  == "TK_divis" || queue[k].lexeme  == "TK_igual"){
                                nextFather = countFila;
                            }
                             countFila++;

                        }

                    }
                }
                printf("countFila = %d", countFila);
                    if(countFila == 2){
                        alocarNo(&f1, fila[0]);
                        alocarNo(&f2, fila[1]);
                        inserirArvBQ(&aux, f1, f2, NULL);
                    }else
                    if(countFila == 3){
                        alocarNo(&f1, fila[0]);
                        alocarNo(&f2, fila[1]);
                        alocarNo(&f3, fila[2]);
                        inserirArvBQ(&aux, f1, f2, f3, NULL);
                    }else
                    if(countFila == 4){
                        alocarNo(&f1, fila[0]);
                        alocarNo(&f2, fila[1]);
                        alocarNo(&f3, fila[2]);
                        alocarNo(&f4, fila[3]);
                        inserirArvBQ(&aux, f1, f2, f3, f4, NULL);
                    }else
                    if(countFila == 5){
                        alocarNo(&f1, fila[0]);
                        alocarNo(&f2, fila[1]);
                        alocarNo(&f3, fila[2]);
                        alocarNo(&f4, fila[3]);
                        alocarNo(&f5, fila[4]);
                        inserirArvBQ(&aux, f1, f2, f3, f4, f5, NULL);
                    }else
                    if(countFila == 6){
                        alocarNo(&f1, fila[0]);
                        alocarNo(&f2, fila[1]);
                        alocarNo(&f3, fila[2]);
                        alocarNo(&f4, fila[3]);
                        alocarNo(&f5, fila[4]);
                        alocarNo(&f6, fila[5]);
                        inserirArvBQ(&aux, f1, f2, f3, f4, f5, f6, NULL);
                    }

                    if(nextFather== 0){ aux = aux->fil1;}
                    else if(nextFather== 1){aux = aux->fil2;}
                    else if(nextFather == 2){aux = aux->fil3;}
                    else if(nextFather == 3){aux = aux->fil4;}
                    else if(nextFather == 4){aux = aux->fil5;}
                    else if(nextFather == 5){aux = aux->fil6;}

                    countFila = 0;
                    printf("\n");
                    countPai++;
                    //novo pai
                for (; countPai<countQueue;countPai++){
                    if(queue[countPai].lexeme != "--")
                        if (queue[countPai].Tree > 0 && queue[countPai].Tree<te){
                            if(queue[countPai].lexeme == "TK_if" || queue[countPai].lexeme == "TK_while" || queue[countPai].lexeme == "TK_for" || queue[countPai].lexeme == "TK_soma" || queue[countPai].lexeme == "TK_subtra" || queue[countPai].lexeme == "TK_mult" || queue[countPai].lexeme == "TK_divis" || queue[countPai].lexeme == "TK_igual"){
                                paiAtual=queue[countPai].Tree;
                                printf("\npai atual %d\n", paiAtual);
                            //    return 0;
                                break;
                            }

                        }
                }
            }

            preorder(&arv);

            for (i=0;i<20;i++)
                imprimirNivel(&arvN, i);

            if((fpObj=fopen("Obj.txt", "w+"))== NULL){
                printf("erro");
                exit(3);
            }
            p *fluxo;
            pInt *lineJPC;
            fluxo=NULL;
            lineJPC=NULL;

            for(vetInd=0;vetInd<100;vetInd++)
                if(vet[vetInd] == -1)
                    break;
                vet[vetInd-2]=-1;

            int memInd = 3, linhaObj=0, chave = 0;
            for(vetInd=0;vetInd<100;vetInd++){
                if(vet[vetInd] != -1){
                    if(queue[vet[vetInd]].lexeme == "TK_if" || queue[vet[vetInd]].lexeme == "TK_while"){
                        if(queue[vet[vetInd]].lexeme == "TK_while")
                            push(&fluxo,"w");
                        if(queue[vet[vetInd]].lexeme == "TK_if"){
                            push(&fluxo,"i");
                        }
                        vetInd++;
                        while(queue[vet[vetInd]].lexeme != "TK_achave"){
                            if(queue[vet[vetInd]].lexeme == "TK_const"){
                                fprintf(fpObj, "lit,0,%s\n", queue[vet[vetInd]].value);
                                fprintf(fpObj, "sto,0,%d\n",memInd);
                                fprintf(fpObj, "lod,0,%d\n",memInd);
                                memInd++;linhaObj+=3;
                            }
                            if(queue[vet[vetInd]].lexeme == "TK_ident"){
                                fprintf(fpObj, "lit,0,%s\n", queue[vet[vetInd]].value);
                                fprintf(fpObj, "sto,0,%d\n",memInd);
                                fprintf(fpObj, "lod,0,%d\n",memInd);
                                memInd++;linhaObj+=3;
                            }
                            vetInd++;
                        }

                        if(fluxo){
                            if(strcmp(top(&fluxo), "w") == 0) fprintf(fpObj, "jpc,0,%d\n", 5+linhaObj++);
                            else fprintf(fpObj, "jpc,0,%d\n", 4+linhaObj++);

                        }
                    }
                    if(queue[vet[vetInd]].lexeme == "TK_const"){
                        fprintf(fpObj, "lit,0,%s\n", queue[vet[vetInd]].value);
                        fprintf(fpObj, "sto,0,%d\n",memInd);
                        fprintf(fpObj, "lod,0,%d\n",memInd);
                        memInd++;linhaObj+=3;

                    }
                    if(queue[vet[vetInd]].lexeme == "TK_ident"){
                        fprintf(fpObj, "lit,0,%s\n", queue[vet[vetInd]].value);
                        fprintf(fpObj, "sto,0,%d\n",memInd);
                        fprintf(fpObj, "lod,0,%d\n",memInd);
                        memInd++;linhaObj+=3;
                    }
                    if(queue[vet[vetInd]].lexeme == "TK_fchave"){
                            //printf("ok2");
                        if(fluxo){
                            if(strcmp(top(&fluxo), "i") == 0) {
                                pushInt(&lineJPC, linhaObj);
                                //fprintf(fpObj, "%d\n", linhaObj);
                            }
                            if(strcmp(top(&fluxo), "w") == 0) {
                                fprintf(fpObj, "jmp,0,%d\n", linhaObj-4);
                                //fprintf(fpObj, "jpc,0,%d\n", 2+linhaObj++);
                                pop(&fluxo);
                            }
                        }
                    }
                }
            }
            fprintf(fpObj, "opr,0,0");
            fclose(fpObj);

        }//parse correto
    return 0;
}

    void increase(int plus){
        queue = (kw) realloc (queue, (plus+2*CHUNK)*sizeof(struct keyWord));
		if (queue==NULL)
		{
			printf("Error reallocating memory!");
			free (queue);
			exit (2);
		}
    }

    void makeQueue(){
        queue = (kw) malloc (2*CHUNK*sizeof(struct keyWord));
		if ((queue==NULL))
		{
			printf("Error allocating memory!");
			exit (1);
		}
    }

    void retorna_erro(int linha, int coluna){
        printf("Caracter nao esperado na linha [%d] e proximo a coluna [%d]", linha, coluna);
        exit(1);
    }


void push(p **s, char *elem)
{
    int tam;//tamanho do elemento que será inserido na pilha
    p *novo;//o elemento que será inserido na pilha

    //criando o novo elemento
    novo = malloc(sizeof(p));
    tam = countTam(elem);
    novo->elem = malloc(sizeof(char)*tam);
    strcpy(novo->elem, elem);

    //mudando o topo da pilha
    novo->prox = *s;
    *s = novo;
}

int countTam(char *s)
{
    //-1 pois tira o '\0'
    int i=0;
    while(s[i++] != '\0');
    return i-1;
}

char* pop(p **s)
{
    char *res;
    p *toDel;

    toDel = *s;
    res=(*s)->elem;
    *s =(*s)->prox;
    free(toDel);

    return res;
}

char* top(p **s){
    char *elem;
    elem = pop(s);
    push(s, elem);
    return elem;
}
void insere(f **s, char *elem)
{
    int tam;//tamanho do elemento que será inserido na fila
    f *novo;//o elemento que será inserido na fila
    f *aux;
    //criando o novo elemento
    novo = malloc(sizeof(f));
    tam = countTam(elem);
    novo->elem = malloc(sizeof(char)*tam);
    strcpy(novo->elem, elem);
    //novo sempre será inserido no final
    novo->prox=NULL;


    //inserindo o elemento no final da fila
    if(*s == NULL)
        *s = novo;
    else
    {
        aux = *s;
        //definindo o último elemento
        while(aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
}


void pushInt(pInt **s, int elem)
{
    //int tam;//tamanho do elemento que será inserido na fila
    pInt *novo;//o elemento que será inserido na fila
    //pInt *aux;
    //criando o novo elemento
    novo = malloc(sizeof(pInt));
    //tam = countTam(elem);
 //   novo->elem = malloc(sizeof(int));
    //strcpy(novo->elem, elem);
    novo->elem = elem;
    //novo sempre será inserido no final
    //novo->prox=NULL;
    novo->prox = *s;
    *s = novo;

    //inserindo o elemento no final da fila
   /* if(*s == NULL)
        *s = novo;
    else
    {
        aux = *s;
        //definindo o último elemento
        while(aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }*/
}

int countSize(char *s)
{
    int i=0;
    while(s[i++] != '\0');

    //-1 pois tira o '\0'
    return i-1;
}

char* recupera(f **s)
{
    char *res;
    f *toDel;

    toDel = *s;
    res=(*s)->elem;
    *s =(*s)->prox;
    free(toDel);

    return res;
}

int popInt (pInt **s)
{
    int res;
    pInt *toDel;

    toDel = *s;
    res=(*s)->elem;
    *s =(*s)->prox;
    free(toDel);

    return res;
}


int getPai(node **arvN, int elem)
{
    if(elem)//elementos não-raiz
        return elem/LARGURA;
    return -1;
}

void erro(int erro)
{
    switch(erro)
    {
        case 1:
            printf("[ERRO]Alocacao de memoria falhou, execucao comprometida!\n");
            exit(0);
        default:
            printf("[ERRO]Algo muito errado aconteceu!\n");
            exit(0);
    }
}

void alocarArvoreN(node **arvN)
{
    int magnitude;
    magnitude = pow(LARGURA, PROFUNDIDADE);

    //sim, ocupa o número de níveis elevado ao número de níveis Espaços de memória
    *arvN = malloc(sizeof(node)*magnitude);
    if(!(*arvN))
        erro(1);

    for(;magnitude>0;magnitude--)
        (*arvN)[magnitude-1].elem = NULL;

}

void inserirArvoreN(node **arvN, char *elem, int pai)
{
    int localDoElem = pai*LARGURA;
    int localDosFilhosDeElem;
    int i;
    node *temp;

    //achando onde inserir, no vetor do pai
    if(localDoElem < 0)
        localDoElem = 0;
    else
    {
        while(strcmp((*arvN)[localDoElem++].elem, VOIDVALUE));
        localDoElem--;
    }

    //alocando o espaço para o ELEM no lugar
    (*arvN)[localDoElem].elem = realloc((*arvN)[localDoElem].elem, sizeof(char)*strlen(elem));
    if(!((*arvN)[localDoElem].elem))
        erro(1);

    //colocando o ELEM no lugar
    (*arvN)[localDoElem].elem = strcpy((*arvN)[localDoElem].elem, elem);

    //iniciando o vetor dos filhos de ELEM
    iniciarFilhosDeElem(&(*arvN), localDoElem);
}

void iniciarFilhosDeElem(node **arvN, int elem)
{
    int tamVoidValue = strlen(VOIDVALUE);
    int filhosDeElem = elem*LARGURA;
    int i;

    //the fucking raiz
    if(!filhosDeElem)
        filhosDeElem = 1;

    //passando o VOIDVALUE para todos os filhos de elem
    for(i=0;i<LARGURA;i++)
    {
        (*arvN)[filhosDeElem+i].elem = malloc(sizeof(char)*tamVoidValue);
        if(!(*arvN)[filhosDeElem].elem)
            erro(1);

        (*arvN)[filhosDeElem+i].elem = strcpy((*arvN)[filhosDeElem+i].elem, VOIDVALUE);
    }
}

void imprimirNivel(node **arvN, int nivel)
{
    int j;

    printf("\n\nimprimindo o nivel %d\n\n", nivel);
    for(j=0;j<LARGURA;j++)
        if((*arvN)[(nivel*LARGURA)+j].elem)
            printf("  %s  ", (*arvN)[(nivel*LARGURA)+j].elem);
    printf("\n\n\n");
}
void alocarNo(no **arv, int elem)
{
    *arv = malloc(sizeof(no));
    if(!(*arv))
        erro(1);
    (*arv)->elem = elem;

    (*arv)->fil1 = NULL;
    (*arv)->fil2 = NULL;
    (*arv)->fil3 = NULL;
    (*arv)->fil4 = NULL;
    (*arv)->fil5 = NULL;
    (*arv)->fil6 = NULL;
}
//---------------------------------
//IF E C | WHILE E C (if e while tem só dois filhos)
void inorderIf(no **arvBQ)
{
    printf("%d ", (*arvBQ)->elem);
    printf("%d ", (*arvBQ)->fil1->elem);
    printf("%d ", (*arvBQ)->fil2->elem);

    preorder(&((*arvBQ)->fil1->fil1));
    preorder(&((*arvBQ)->fil1->fil2));
    preorder(&((*arvBQ)->fil1->fil3));
    preorder(&((*arvBQ)->fil1->fil4));
    preorder(&((*arvBQ)->fil1->fil5));
    preorder(&((*arvBQ)->fil1->fil6));

    preorder(&((*arvBQ)->fil2->fil1));
    preorder(&((*arvBQ)->fil2->fil2));
    preorder(&((*arvBQ)->fil2->fil3));
    preorder(&((*arvBQ)->fil2->fil4));
    preorder(&((*arvBQ)->fil2->fil5));
    preorder(&((*arvBQ)->fil2->fil6));
}
//---------------------------------
// FOR S E S C (for tem quatro filhos)
void inorderFor(no **arvBQ)
{
    printf("%d ", (*arvBQ)->elem);
    printf("%d ", (*arvBQ)->fil1->elem);
    printf("%d ", (*arvBQ)->fil2->elem);
    printf("%d ", (*arvBQ)->fil3->elem);
    printf("%d ", (*arvBQ)->fil4->elem);

    preorder(&((*arvBQ)->fil1->fil1));
    preorder(&((*arvBQ)->fil1->fil2));
    preorder(&((*arvBQ)->fil1->fil3));
    preorder(&((*arvBQ)->fil1->fil4));
    preorder(&((*arvBQ)->fil1->fil5));
    preorder(&((*arvBQ)->fil1->fil6));

    preorder(&((*arvBQ)->fil2->fil1));
    preorder(&((*arvBQ)->fil2->fil2));
    preorder(&((*arvBQ)->fil2->fil3));
    preorder(&((*arvBQ)->fil2->fil4));
    preorder(&((*arvBQ)->fil2->fil5));
    preorder(&((*arvBQ)->fil2->fil6));

    preorder(&((*arvBQ)->fil3->fil1));
    preorder(&((*arvBQ)->fil3->fil2));
    preorder(&((*arvBQ)->fil3->fil3));
    preorder(&((*arvBQ)->fil3->fil4));
    preorder(&((*arvBQ)->fil3->fil5));
    preorder(&((*arvBQ)->fil3->fil6));

    preorder(&((*arvBQ)->fil4->fil1));
    preorder(&((*arvBQ)->fil4->fil2));
    preorder(&((*arvBQ)->fil4->fil3));
    preorder(&((*arvBQ)->fil4->fil4));
    preorder(&((*arvBQ)->fil4->fil5));
    preorder(&((*arvBQ)->fil4->fil6));
}
//---------------------------------
void preorder(no **arvBQ)
{
    if(*arvBQ)
    {
        if(0/*coloca a comparação do vetor aqui, tipo: if(!strcmp(arvN[(*arvBQ)->elem], "if"))*/)
            inorderIfWhile(&(*arvBQ));
        else if(0/*coloca a comparação do vetor aqui, tipo: if(!strcmp(arvN[(*arvBQ)->elem], "for"))*/)
            inorderFor(&(*arvBQ));
        else if(0/*coloca a comparação do vetor aqui, tipo: if(!strcmp(arvN[(*arvBQ)->elem], "while"))*/)
            inorderIfWhile(&(*arvBQ));
        else
        {
            //printf("\n%s ", queue[(*arvBQ)->elem].lexeme);//
            vet[vetInd++] = (*arvBQ)->elem;
            //fprintf(fpObj, "%s %d\n", queue[(*arvBQ)->elem].lexeme, (*arvBQ)->elem);

            printf("%d ", (*arvBQ)->elem);
            preorder(&((*arvBQ)->fil1));
            preorder(&((*arvBQ)->fil2));
            preorder(&((*arvBQ)->fil3));
            preorder(&((*arvBQ)->fil4));
            preorder(&((*arvBQ)->fil5));
            preorder(&((*arvBQ)->fil6));
        }
    }
}

//---------------------------------
void inserirArvBQ(no **pai, no *filho1, ...)
{
    va_list ap;
    no *i;
    //dois elementos, o mínino
    va_start(ap, filho1) ;
    alocarNo(&((*pai)->fil1),  filho1->elem);
    i = va_arg(ap, no*);
    alocarNo(&((*pai)->fil2), i->elem);
    i = va_arg(ap, no*);

    //caso não tenha seis elementos
    (*pai)->fil3 = NULL;
    (*pai)->fil4 = NULL;
    (*pai)->fil5 = NULL;
    (*pai)->fil6 = NULL;

    //três elementos
    if(i)
    {
        alocarNo((&(*pai)->fil3), i->elem);
        i= va_arg(ap, no*);
        //quatro elementos
        if(i)
        {
            alocarNo((&(*pai)->fil4), i->elem);
            i= va_arg(ap, no*);
            //cinco elementos
            if(i)
            {
                alocarNo((&(*pai)->fil5), i->elem);
                i= va_arg(ap, no*);
                //seis elementos
                if(i)
                {
                    alocarNo((&(*pai)->fil6), i->elem);
                    i= va_arg(ap, no*);
                }//if dos seis elementos
            }//if dos cinco elementos
        }//if dos quatro elementos
    }//if dos três elementos
    va_end(ap);
}
