#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

//sistema pdv (ponto de venda)

/* REQUISITOS DA APLICAÇÃO

1- DEVE SER POSSÍVEL CADASTRAR ATÉ 100 PRODUTOS.
2- TODO PRODUTO DEVE TER CODIGO ÚNICO (GARANTIDO PELO SW).
3- SAÍDA DO CADASTRO DE PRODUTOS SERÁ CODIGO <= 0;

FASE DE VENDAS!
1- SOLICITAR CODIGO DE ITEM PARA VENDA:
	1.1- VERIFICAR SE ITEM EXISTE
		1.1.1- IMPRIMIR TODOS OS DADOS DO PRODUTO, OU
		1.1.2- CODIGO NÃO EXISTENTE! TENTAR NOVAMENTE.

	1.2. SOLICITAR QUANTIDADE DESTE MESMO ITEM NO CARRINHO
		1.2.1- VERIFICAR SE A QTDE. ESTÁ DISPONÍVEL
		1.2.2- ATUALIZAR ESTOQUE DO ITEM
		
2. REPETIR TODO PROCESSO DE VENDA DO CARRINHO ATÉ CÓDIGO <=0

3. INFORMAR TOTAL DA VENDA
4. INFORMAR VALOR PAGO
5. INFORMAR TROCO DA VENDA

6. PERGUNTAR SE HÁ NOVO CARRINHO DE COMPRAS
	6.1. REPETIR TODO PROCESSO PARA NOVO CARRINHO.

7. NÃO HAVENDO...
	7.1 RELATÓRIO ATUALIZADO DE TODOS OS PRODUTOS
	7.2 FATURAMENTO DO DIA (TOTAL DE VENDAS)
*/

typedef struct{
	int codigo;//chave
	char descricao[100];
	float valor;
	int estoque;
}Produto;


int main(){
	
	Produto p;
	Produto cadrasto[MAX];
	

	int cont = 0;
	int qtd;
	float totalCar;
	float faturamento = 0.0f;
	
	
	while(cont < MAX) {
		//cadrastar produto
		printf("\n========================================CADRASTO========================================\n");
		printf("\nDigite o codigo do produto (0-ENCERRAR): ");
		scanf("%d", &p.codigo);
		
		//encerrar o loop
		if(p.codigo <= 0) {
			printf("\nCADRASTO ENCERRADO\n");
			break;
		}
		
		printf("Qual produto vc vai querer? ");
		scanf(" %[^\n]s ", p.descricao);
		
		printf("Digite o valor do produto: ");
		scanf("%f", &p.valor);
	
		printf("Digite quantas unidades você vai querer cadrastar: ");
		scanf("%d", &p.estoque);
		
		int repetido = 0;
		//verificar se o numero esta se repetindo
		for(int i = 0; i < cont; i++) {
			if(cadrasto[i].codigo == p.codigo || strcmp(cadrasto[i].descricao, p.descricao) == 0) { 
				repetido = 1;
				break; 
			}
		}
		
		if(repetido) { 
			system("clear");
			printf("\nProduto ja cadastrado! Tente novamente...\n");
		}
		
		else { 
			cadrasto[cont++] = p;
		}
	}
	int idx = -1;
	
	while(1){
		totalCar = 0.0f;
		//fase de vendas
		printf("\n=========================================VENDAS=========================================\n");
		printf("Digite o codigo do produto para a venda: ");
		scanf(" %d", &p.codigo);
		
		if(p.codigo == 0) { 
			printf("FASE DE VENDAS ENCERRADO!");
			break;
		}
		
		printf("\n");
		
		//verificar se o produto existe
		int existe = 0;
		for(int i = 0; i < cont; i++ ){
			if(p.codigo == cadrasto[i].codigo) { 
				existe = 1;
				idx = i;
				break;
			}
		}
		
		if(!existe) {
			printf("\nCodigo não existente! Tente novamente \n");
			continue;
		}
		
		//imprimir os dados do produto
		printf("\nPRODUTO\n");
		printf("Codigo do produto: %d\n",cadrasto[idx].codigo);
		printf("Item: %s\n", cadrasto[idx].descricao);
		printf("Preco do produto: %.2fR$\n", cadrasto[idx].valor);
		printf("Quantidade: %d\n", cadrasto[idx].estoque);
	
		//carrinho de compras
		printf("\nDigite a quantidade Desejada: ");
		scanf("%d", &qtd);
		
		if(qtd <= 0)  {
			printf("Digite Quantidade maior do que 0\n");
			continue;
		}
		
		else if (qtd > cadrasto[idx].estoque) {
			printf("\nEstoque insuficiente! Tente novamente\n");
			continue;
		}
		
		cadrasto[idx].estoque -= qtd;
		float totalV = (float)qtd * cadrasto[idx].valor;
		totalCar += totalV;
		printf("\nItem adicionado! subtotal %.2f || Total do carrinho %.2f\n", totalV, totalCar);
		
		int add;
		printf("Deseja continuar comprando? (1 - sim) (0 - nao): ");
		scanf("%d", &add);
	
		if(add)
			continue;
			
		float totalP, troco;
		
		//valor total da venda
		do {
			printf("Valor a ser pago pelo cliente: ");
			scanf(" %f", &totalP);
			if(totalP < totalCar) { 
				printf("Dinheiro insuficiente! não vendemos fiado! faltam %.2fR$...\n", totalCar - totalP);
			}
			
		}while(totalP < totalCar);
		
		troco = totalP - totalCar;
		printf("Seu troco %.2f\n", troco);
		
		faturamento += totalCar;
		
		int resp;
		printf("Deseja fazer outro carrinho de compras? (1 - Sim) (0 - Nao) \n");
		scanf("%d", &resp);
		
		if(resp) 
			continue;
		else 
			break;
	}
	
	//RELATORIO FINAL
	printf("\n=========================================RELATORIO FINAL=========================================\n");
	for(int i = 0; i < cont; i++) {
		printf("\nPRODUTO %d\n", i+1);
		printf("Codigo do produto %d\n", cadrasto[i].codigo);
		printf("Item: %s\n", cadrasto[i].descricao);
		printf("Preco do produto: %.2fR$\n", cadrasto[i].valor);
		printf("Quantidade: %d\n", cadrasto[i].estoque);
	}

	printf("\nFaturamento do dia: %.2f\n", faturamento);
	
	return 0;
}

