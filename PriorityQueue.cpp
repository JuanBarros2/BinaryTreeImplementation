/*

  INSTITUTO FEDERAL DA PARAÍBA
  CAMPUS CAMPINA GRANDE
  SOFTWARE CRIADO POR: JUAN VICTOR LYRA BARROS E BARROS
  PROFESSOR: MARCELO SIQUEIRA
  DISCIPLINA: LINGUAGEM DE PROGRAMAÇÃO E ESTRUTURA DE DADOS
  TURMA: 2º ANO "A"
  CURSO: INFORMÁTICA

  Programa criado para simular uma fila de banco onde
  idosos acima de 60 anos e grávidas tem preferência.
  O programa contém um menu com as principais funções


  */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MASC 1 //VALOR REFERENTE AO MASCULINO
#define FEM 2//VALOR REFERENTE AO FEMININO

typedef struct usuario{
	char nome[30];
	int idade;
	int sexo;
    int *estagravida;
	struct usuario *prox;
}usuario;

usuario *inicio=NULL;

char menu_principal();
void mensagemerro();
void inserir();
void exibirtodas();
void exibir(usuario *aux);
void remover();
void localizar();
void exibirjovem();
void tamanho();
void exibirquantgravidas();
void exibirquantidosos();

int main(){
    system("title FILA DO BANCO ");
	setlocale(LC_ALL,"Portuguese");
	system("color 1f");
	do{
		switch(menu_principal()){  //RECEBERÁ O VALOR RETORNADO DA FUNÇÃO
			case 0:{ //FINALIZARÁ O PROGRAMA
			    return 0;
				break;
			}
			case 1:{ //INSERE UM USUÁRIO NA FILA
				inserir();
				break;
				}
			case 2:{ //REMOVE O USUÁRIO DA FILA
				remover();
				break;
				}
            case 3:{ //EXIBE TODA A FILA
				exibirtodas();
				break;
				}
			case 4:{ //LOCALIZA E EXIBE O CLIENTE
				localizar();
				break;
				}
			case 5:{ //LOCALIZA E EXIBE O(S) CLIENTE(S) MAIS NOVO(S)
				exibirjovem();
				break;
				}
			case 6:{ //EXIBE O TAMANHO DA FILA
				tamanho();
				break;
				}
			case 7:{ //EXIBE QUANTIDADE DE GRÁVIDAS DA FILA
				exibirquantgravidas();
				break;
				}
			case 8:{ //EXIBE QUANTIDADE DE PESSOAS ACIMA OU IGUAL A 60 ANOS
				exibirquantidosos();
				break;
				}
			default:{  //EXIBE MENSAGEM DE ERRO QUANDO O USUÁRIO TECLAR QUALQUER OUTRA TECLA
				mensagemerro();
			}
		}
	}while(1);
	return 0;
}

char menu_principal(){//IMPRIME O MENU INICIAL E RETORNA A OPÇÃO
	system("cls");
	printf("\n\n\n\t-----------------------------MENU-----------------------------\n");
	printf("\n\n\t1-Inserir na fila\t\t5-Exibir pessoa mais jovem");
	printf("\n\n\t2-Remover na fila\t\t6-Exibir tamanho da fila");
	printf("\n\n\t3-Exibir toda a fila\t\t7-Exibir quantidade de grávidas");
	printf("\n\n\t4-Procurar pessoa (pelo nome)\t8-Exibir quantidade de idosos");
	printf("\n\n\t0-Finalizar programa");
	printf("\n\n\n\t-------------------------------------------------------------");
	printf("\n\t\tDigite a opção: ");
	{
		int op;
		scanf("%d",&op);
		fflush(stdin);
		system("cls");
		return (op);
	}
}

void mensagemerro(){//EXIBE UMA MENSAGEM DE ERRO POR OPÇÃO INVÁLIDA
    printf("\n\n    Opção Inválido! Pressione qualquer tecla para continuar!");
    system("pause>>null");
}

void inserir(){//RECEBE E ORDENA UM NOVO USUÁRIO NA FILA
     usuario *novo;
     novo= (usuario*) malloc(sizeof(usuario));
     novo->estagravida=NULL;
     printf("\n\n\t\tInsira o nome: ");
     scanf("%[^\n]s",novo->nome);
     system("cls");
     fflush(stdin);

     for(usuario *aux=inicio;aux!=NULL;aux=aux->prox)//COMPARA NOME PARA GARANTIR QUE SÓ EXISTA UM NOME
        if(0==strcmp(novo->nome,aux->nome)){
           printf("\n\n\t\tNome já existente!");
           system("pause>>null");
           return;
           }

     printf("\n\n\t\tInsira sua idade: ");
     scanf("%d",&novo->idade);
     system("cls");

     do{
        printf("\n\n\t\t-----------------------------------------------");
        printf("\n\n\t\tInsira o número correspondente ao sexo:");
        printf("\n\n\t\t%d-Masculino",MASC);
        printf("\n\t\t%d-Feminino\n\t\t",FEM);
        printf("\n\n\t\t-----------------------------------------------\n\t\tOpção: ");
        scanf("%d",&novo->sexo);
        system("cls");
        if ((novo->sexo!=MASC)&&(novo->sexo!=FEM)){
            mensagemerro();
        }
    }while((novo->sexo!=MASC)&&(novo->sexo!=FEM));

     if (novo->sexo==FEM){ //SE FOR MULHER ENTÃO PERGUNTARÁ SE ESTÁ GRAVIDA
        int op;
        printf("\n\n\t\t-----------------------------------------------");
        printf("\n\n\t\tEstá grávida:");
        printf("\n\n\t\t1-Sim\n\t\t2-Não");
        printf("\n\n\t\t-----------------------------------------------\n\t\tOpção: ");
        scanf("%d",&op);
        system("cls");
        if (op==1){//SE MARCAR COMO GRÁVIDA
           novo->estagravida= (int*) malloc(sizeof(int));
           system("cls");
           printf("\n\n\t\tQuantos meses de gestão: ");
           scanf("%d",novo->estagravida);//AMARRA A GESTAÇÃO COM O PONTEIRO
        }
     }

     if (inicio==NULL){
        inicio=novo;
        inicio->prox=NULL;
     }
     else{
        for (usuario *aux=inicio,*ant=NULL; aux!=NULL ; ant=aux , aux=aux->prox){
            if(novo->estagravida!=NULL){//SE USUARIO ESTIVER GRAVIDA
                if((aux->estagravida!=NULL)&&(*novo->estagravida <= *aux->estagravida)){
                //SE ESTIVER GRAVIDA NA VEZ E A GESTAÇÃO FOR MAIOR QUE A DA NOVA GRAVIDA
                    if(aux->prox==NULL){
                        aux->prox=novo;
                        novo->prox=NULL;
                        break;
                    }
                }
                else{//Caso contrario é adicionado a grávida
                        novo->prox=aux;
                        if(ant==NULL)
                            inicio=novo;
                        else
                            ant->prox=novo;
                        break;
                    }
                }
            else {//SE NÃO ESTIVER GRÁVIDA
                if (novo->idade >=60){//SE FOR MAIOR QUE 60 ANOS
                    if((aux->estagravida!=NULL)||(novo->idade <= aux->idade)){//SE USUARIO DA VEZ ESTIVER GRÁVIDA OU IDADE DO OUTRO FOR MENOR QUE ATUAL
                        if(aux->prox==NULL){
                                aux->prox=novo;
                                novo->prox=NULL;
                                break;
                            }
                            continue;
                    }
                    else {
                        novo->prox=aux;
                        if(ant==NULL)
                            inicio=novo;
                        else
                            ant->prox=novo;
                        break;
                        }
                }
                else
                    if( aux->prox==NULL){
                        aux->prox=novo;
                        novo->prox=NULL;
                        break;
                        }
                }
            }
        }
     system("cls");
     printf("\n\n\t\tUsuário adicionado com sucesso!\n\n\t\t");
     system("pause");
     fflush(stdin);
     }

void exibirtodas(){//EXIBE TODAS OS USUARIOS

    if(inicio==NULL){
        printf("\n\n\t\tNenhum usuário na fila!");
        system("pause>>null");
        return;
    }
    printf("\n\n\t\t-----------------------------------------------");
    printf("\n\t\t                 FILA COMPLETA");
    printf("\n\t\t-----------------------------------------------\n");
    for(usuario *auxiliar=inicio;auxiliar!=NULL;auxiliar=auxiliar->prox){
        exibir(auxiliar);
    }
    printf("\n\n\t\t-----------------------------------------------");
    system("pause>>null");
    return;
}

void remover(){//REMOVE UM USUÁRIO POR VEZ
    usuario *aux=inicio;
    if (aux==NULL){
        printf("\n\n\t\tNenhum usuário na fila!");
        system("pause>>null");
        return;
    }
    printf("\n\n\t\t-----------------------------------------------");
    printf("\n\n\t\t%s ",inicio->nome);
    inicio=inicio->prox;
    free(aux);
    printf("foi atendido(a)");
    printf("\n\n\t\t-----------------------------------------------");
    system("pause>>null");
}

void exibir(usuario *aux){//EXIBE UM USUÁRIO RECEBENDO SUA POSIÇÃO POR PARÂMETRO
    printf("\n\t\t------------------\n\t\tNome: %s",aux->nome);
    printf("\n\t\tIdade: %d Anos",aux->idade);
    if(aux->sexo==FEM){
        printf("\n\t\tSexo: Feminino");
        printf("\n\t\tGrávida: ");
        if (aux->estagravida!=NULL){
            printf("SIM");
            printf("\n\t\tGestação: %d meses",*aux->estagravida);
            }
        else
            printf("NÃO");
    }
    else
        printf("\n\t\tSexo: Masculino");
    printf("\n\t\t------------------");
    return;
    }

void localizar(){//LOCALIZA E EXIBE USUÁRIO PELO NOME
    char teste[30];
    if(inicio==NULL){
        printf("\n\n\t\tNenhum usuário na fila!");
        system("pause>>null");
        return;
    }
    printf("\n\n\t\tDigite o nome a ser pesquisado: ");
    scanf("%[^\n]s",&teste);
    fflush(stdin);
    system("cls");
    usuario *aux=inicio;
    while(aux!=NULL){//TESTA SE EXISTE O NOME NA FILA
        if(0==strcmp(teste,aux->nome)){
            exibir(aux);//SE EXISTIR ELE EXIBE E FINALIZA A FUNÇÃO
            system("pause>>null");
            return;
        }
        aux=aux->prox;
    };
    printf("\n\n\t\tUsuário não encontrado!");//SE CONTINUAR É PORQUE NÃO FOI ENCONTRADO E DEVE-SE MOSTRAR A MENSAGEM DO ERRO
    system("pause>>null");
    return;
}

void exibirjovem(){//EXIBE O USUARIO MAIS JOVEM
    usuario *aux=inicio;
    if(inicio==NULL){
        printf("\n\n\t\tNenhum usuário na fila!");
        system("pause>>null");
        return;
    }
    int menor=aux->idade;
    while(aux!=NULL){//ACHA O USUÁRIO MAIS JOVEM
        if(aux->idade < menor)
            menor=aux->idade;
        aux=aux->prox;
    }
    system("cls");
    printf("\n\n\t\t-----------------------------------------------");
    printf("\n\n\t\tO(s) usuário(s) mais novo(s) é(são):\n\n ");
    aux=inicio;
    while(aux!=NULL){//PERCORRE A FILA PARA ACHAR OS USUÁRIOS COM MENOR IDADE
        if(aux->idade == menor)
            exibir(aux);//SE SUA IDADE FOR IGUAL COM A DO MENOR É EXIBIDO NA TELA
        aux=aux->prox;
    }
    printf("\n\n\t\t-----------------------------------------------");
    system("pause>>null");
}

void tamanho(){//EXIBE O TAMANHO DA FILA
    if(inicio==NULL){
        printf("\n\n\t\tNenhum usuário na fila!");
        system("pause>>null");
        return;
    }
    usuario *aux=inicio;
    int cont=0;
    while(aux!=NULL){//CONTA AS POSIÇÕES COM UMA VARIAVEL CONTADORA
        cont++;
        aux=aux->prox;
    }
    printf("\n\n\t\t-----------------------------------------------");
    printf("\n\n\t\tFila com: %d posição(ões)!",cont);
    printf("\n\n\t\t-----------------------------------------------");
    system("pause>>null");
}

void exibirquantgravidas(){//EXIBE QUANTIDADE DE GRÁVIDA NA FILA
    if(inicio==NULL){
        printf("\n\n\t\tNenhum usuário na fila!");
        system("pause>>null");
        return;
    }
    usuario *aux=inicio;
    int cont=0;
    while(aux!=NULL){//CONTA AS POSIÇÕES COM UMA VARIAVEL CONTADORA
        if (aux->estagravida!=NULL)
            cont++;
        aux=aux->prox;
    }
    printf("\n\n\t\t-----------------------------------------------");
    printf("\n\n\t\t %d gestante(s) na fila!",cont);
    printf("\n\n\t\t-----------------------------------------------");
    system("pause>>null");
    }

void exibirquantidosos(){//EXIBIR QUANTIDADE DE PESSOAS ACIMA OU IGUAL A 60 ANOS
    if(inicio==NULL){
        printf("\n\n\t\tNenhum usuário na fila!");
        system("pause>>null");
        return;
    }
    usuario *aux=inicio;
    int cont=0;
    while(aux!=NULL){
        if (aux->idade>=60)
            cont++;
        aux=aux->prox;
    }
    printf("\n\n\t\t-----------------------------------------------");
    printf("\n\n\t\t %d idoso(s) na fila!",cont);
    printf("\n\n\t\t-----------------------------------------------");
    system("pause>>null");
}
