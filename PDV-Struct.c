#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

#define MAX 100

typedef struct{
	int codigo;//chave
	char descricao[100];
	float valor;
	int estoque;
}Produto;

int cadrastarProduto(Produto *p){
	printf("\n========================================CADRASTO========================================\n");
	input(INT, "Qual codigo do produto: ", &p->codigo);
	
	if(p->codigo == 0) return p->codigo;
		
	input(FLOAT, "Digite o valor do produto: ", &p->valor);
	input(STR, "Digite a descrição do produto: ", p->descricao);
	input(INT, "Digite quantas unidades você vai querer cadrastar: ", &p->estoque);
	return p->codigo;
}



Produto* validacao(int codigo, Produto cadrastro[], int* cont) {
	//verificar se o produto existe
	int flag = 0;
	for(int i = 0; i < cont; i++){
		if(codigo == cadrastro[i].codigo) { 
			return cadrastro[i];
		}
	}
	return NULL;
}

int main(){
	
	Produto p;
	Produto cadrasto[MAX];

	int cont = 0;
	int qtd;
	float totalCar;
	float faturamento = 0.0f;
	
	
	while(cont < MAX) {
		
		cadrastarProduto(&p);
		
		if(p.codigo == 0)
			break;

		int repetido = 0;
		//verificar se o numero esta se repetindo
		for(int i = 0; i < cont; i++) {
			if(cadrasto[i].codigo == p.codigo || strcmp(cadrasto[i].descricao, p.descricao) == 0) { 
				repetido = 1;
				break; 
			}
		}
		
		if(repetido) printf("\nProduto ja cadastrado! Tente novamente...\n");
		else cadrasto[cont++] = p;
		system("clear");
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
		
		int flag = validacao(p.codigo, cadrasto, idx);
		printf("\n");
		
		if(!flag) {
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
	printf("\n=====================================RELATORIO FINAL====================================\n");
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

