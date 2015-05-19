/*
* @author: Victor Santos
* @date: 05/2015
* @ systema para loja, cadastro de produto, e venda
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef WIN32
	#define so 1
#else
	#define so 0
#endif

void painel(void);
void menu(void);
void cadastrar(void);
void listar(void);
void vender(void);
void saldo(void);
void alterarCor(void);
void fecharLoja(void);
void getNomoeLoja(void);
void verificaArquivo(void);
void gravarArquivo(char produtoNome[250],float produtoValor);
void limpaTela(void);
void orderFile(char type);

int i = 0, dia = 0, mes = 0, ano = 0, error = 0;
char nomeLoja[250];

int main(){
	getNomoeLoja();
	menu();
	return 0;
}

void painel(){
	limpaTela();
	printf("|--------------------------------------------------|\n");
	printf("|1)Sair\t\t\t\t\t\t|\n");
	printf("|__________________________________________________|\n");
}
/*
* @author: Victor Santos
* @date: 05/2015
* @ Pega o nome da loja e data das operações
*/
void getNomoeLoja(){
	printf("Digite o nome da loja: ");
	gets(nomeLoja);
	do{
		if(error == 1){
			printf("Data operacional invalda !!!\n");
		}
		printf("Digite a data operacional [ ex: 10/01/2015 ]: ");
		scanf("%i/%i/%i",&dia,&mes,&ano);
		error = 1;
	}while(dia > 31 || dia < 1 || mes < 1 || mes > 12);
	verificaArquivo(); //check File loja
	error = 0;
}
/*
* @author: Victor Santos
* @date: 05/2015
* @ Imprime o menu de opções na tel
*/
void menu(){
	
	limpaTela();
	
	do{
		i = 0;
		printf("|--------------------------------------------------|\n");
		printf("|Loja:%s\t\tData Operacional:%i/%i/%i\n",nomeLoja,dia,mes,ano);
		printf("|Sistema:%s\tUltima Operacao:%i/%i/%i\n",so == 1?"Windows":"Linux",dia,mes,ano);
		printf("|__________________________________________________|\n");
		printf("|1)Vender\t\t\t2)Listar\t   |\n");
		printf("|3)Cadastrar Produto\t\t4)Saldo do Estoque |\n");
		printf("|5)Ordenar Crescente\t\t6)Ordenar Decrescete |\n");
		printf("|7)Fechar a Loja\t\t8)Sair do programa |\n");		
		printf("|__________________________________________________|\n");
		if(error == 1){
			printf("|Operacao invalida !!!\t\t|\n");
			printf("|__________________________________________________|\n");
			error = 0;
		}
		scanf("%i",&i);
		switch(i){
			//cadastrar
			case 1:
				vender();
			break;
			
			//Listar
			case 2:
				listar();
			break;
			//vender
			case 3:
				cadastrar();
				limpaTela();
			break;

			//saldo estque
			case 4:
				saldo();
			break;

			//alterar cor
			case 5:
				orderFile('c');
			break;

			//saldo estque
			case 6:
				orderFile('d');
			break;

			//saldo estque
			case 7:
				fecharLoja();
			break;

			default:
				error = 1;
			break;
		}
	}while(i != 8);
	error = 0;
	limpaTela();
}
/*
* @author: Victor Santos
* @date: 05/2015
* Cadstro de produto
*/
void cadastrar(){

	char produtoNome[200];
	float produtoValor=0;

	do{
		painel();
		printf("Nome do produto: ");
		scanf("%s",&produtoNome);
		//gets(produtoNome);
		//fflush();
		//Se difitou sair ou 1, nem pede o valor do produto, ja sai do cadastro
		if(strcmp(produtoNome,"sair") == -1 && strcmp(produtoNome,"1") != 0){
			do{
				printf("Valor do produto: ");
				scanf("%f",&produtoValor);	
			}while(produtoValor <= 0);
			gravarArquivo(produtoNome,produtoValor);
		}
	}while(strcmp(produtoNome,"sair") == -1 && strcmp(produtoNome,"1") != 0);

	/*
	* Se escreveu menu vamos ao menus
	* caso não, sai do programa
	*/
	if(strcmp(produtoNome,"menu") == 0){
		menu();
	}
}

void listar(){
	
	char nomeArquivo[120], linha[400];
	
	FILE *arq; //Variavel arq do tipo File

	sprintf(nomeArquivo,"%s_estoque.txt",nomeLoja);

	arq = fopen(nomeArquivo,"r");

	limpaTela();
	i = 1;
	while(fgets(linha,400,arq)!=NULL){
		printf("%i] %s",i,linha);
		i++;
	}
	printf("\n|Total de produtos cadastrados: %i\n\n\n",i-1);
	i = 0;
	fclose(arq);
}

void vender(){
	printf("Vender\n");
}
void saldo(){
	printf("Saldo\n");
}
void alterarCor(){
	printf("Alterar Cor\n");
}
void fecharLoja(){
	printf("fechar a loja\n");
}
/*
* @author: Victor Santos
* @date: 05/2015
* @ Verifica e existe arquivo de estoque para a loja,
* caso não exista ainda, cria.
*/
void verificaArquivo(){

	char nomeArquivo[120];
	FILE *arq; //Variavel arq do tipo File

	sprintf(nomeArquivo,"%s_estoque.txt",nomeLoja);

	arq = fopen(nomeArquivo,"r");
	if(arq == NULL){
		arq = fopen(nomeArquivo,"w");
		char cabecalho[250];
		//sprintf(cabecalho,"Data Operacional: %i/%i/%i\nsair\n",dia,mes,ano);
		//fprintf(arq,cabecalho);
	}else{
		arq = fopen(nomeArquivo,"a");
		char cabecalho[250];
		//sprintf(cabecalho,"Data Operacional: %i/%i/%i\nsair\n",dia,mes,ano);
		//fprintf(arq,cabecalho);
	}
	fclose(arq);
}
/*
* @author: Victor Santos
* @date: 05/2015
* @ Injeta uma string em um arquivo
*/
void gravarArquivo(char produtoNome[250],float produtoValor){

	char nomeArquivo[120];

	FILE *arq; //Variavel arq do tipo File

	sprintf(nomeArquivo,"%s_estoque.txt",nomeLoja);
	
	arq = fopen(nomeArquivo,"a");

	fprintf(arq,"%s\t%f\n",produtoNome,produtoValor);

	fclose(arq);
}
/*
* @author: Victor Santos
* @date: 05/2015
* @ Limpa a tela de acordo com o sistema operacional
*/
void limpaTela(){
	if(so == 1 )
		system("cls");
	else
		system("clear");
}
/*
* @author: Victor Santos
* @date: 05/2015
* @ Ordena os arquivos no arquivo
*/
void orderFile(char type){
	
	char nomeArquivo[120];
	char lNomeP[999][250], auxLNomeP[250];
	float lValorP[999], aux = 0;
	int y = 0;
	
	FILE *arq; //Variavel arq do tipo File

	sprintf(nomeArquivo,"%s_estoque.txt",nomeLoja);

	arq = fopen(nomeArquivo,"r");
	
	limpaTela();

	while( (fscanf(arq,"%s %f\n", &lNomeP[y], &lValorP[y]))!=EOF ){
		y++;
	}

	int tamanho = y;

	for (i = 0; i < tamanho; i++)
	{
		for (y = 0; y < tamanho; y++)
		{
			if(type == 'c'){ //condião para ordenar crescente
				if(lValorP[i] > lValorP[y]){
					aux = lValorP[y];
					strcpy(auxLNomeP, lNomeP[y]);
					lValorP[y] = lValorP[i];
					strcpy(lNomeP[y],lNomeP[i]);
					lValorP[i] = aux;
					strcpy(lNomeP[i],auxLNomeP);
				}
			}else{ //se não é crescente é decrecente
				if(lValorP[i] < lValorP[y]){
					aux = lValorP[y];
					strcpy(auxLNomeP, lNomeP[y]);
					lValorP[y] = lValorP[i];
					strcpy(lNomeP[y],lNomeP[i]);
					lValorP[i] = aux;
					strcpy(lNomeP[i],auxLNomeP);
				}
			}
		}
	}

	arq = fopen(nomeArquivo,"w");
	fclose(arq);

	for (i = 0; i < tamanho; ++i)
	{
		gravarArquivo(lNomeP[i],lValorP[i]);
	}
}
