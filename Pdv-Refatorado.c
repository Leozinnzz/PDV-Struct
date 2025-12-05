/*
============= Leozinzz =================
============= CachyOS --%d/%m/%Y-- =================
============= LI4ever ======================
============= Made-by-Leozinzz-Desktop ===============
*/

#include <stdio.h>
#include <stdlib.h>
#include "input.h"


typedef struct {
	int codigo;
	char descricao[100];
	float valor;
	int estoque;
}Produto; 

typedef struct {
	Produto lista[100];
	int cont;
}dsProdutos;

int produtoRepet(int cod, dsProdutos *estoque);

dsProdutos criarEstoque(){
	dsProdutos novoEstoque;
	novoEstoque.cont = 0;
	return novoEstoque;
}


int interface(){
	printf("\n1 - Cadastrar Produto\n");
	printf("2 - Vender Produto\n");
	printf("3 - Consultar Produto\n");
	printf("4 - Imprimir Estoque\n");
	printf("5 - Fechamento de Caixa\n");
	printf("0 - SAIR DO PROGRAMA\n");
	int opc; 
	printf("Informe a Opção Desejada: ");
	scanf(" %d", &opc); 
	return opc;
}

Produto setProduto(){
	Produto p;
	input(INT, "Codigo de barras: ", &p.codigo);
	
	input(STR, "Descrição: ", p.descricao);
	input(FLOAT, "preço unitario:  ", &p.valor);
	input(INT, "quantidade: ", &p.estoque);
	return p;
}


void cadastrarProduto(Produto p, dsProdutos *estoque){
	if(!produtoRepet(p.codigo, estoque)) {
		printf("Produto ja cadastrado! Tente novamente...\n");
		return;
	}
	estoque->lista[estoque->cont] = p;
	estoque->cont++;
}

void printProduto(Produto p){
	printf("Codigo de barras: %d\n", p.codigo);
	printf("Descrição: %s\n", p.descricao);
	printf("Preco unitario: %.2f\n", p.valor);
	printf("Quantidade: %d\n", p.estoque);
}

void listarEstoque(dsProdutos estoque){
	for(int i = 0; i < estoque.cont; i++)
		printProduto(estoque.lista[i]);
}

Produto *buscarItem(int cod, dsProdutos *estoque){
	for(int i = 0; i < estoque->cont; i++) {
		if(cod == estoque->lista[i].codigo)
			return &estoque->lista[i];
	}
	return NULL;
}

void ConsultarProduto(dsProdutos *estoque){
	int cod;
	printf("Digite o codigo para consulta: ");
	scanf(" %d", &cod);
	
	if(cod == 0) {
		printf("Produto inesxistente\n");
		return;
	}
	 Produto  *item = buscarItem(cod, estoque);
	 
	 if(!item){
		 printf("Produto nao encontrado");
		 return;
	 }
	 
	 printProduto(*item);
}

float venderProdutos(dsProdutos *estoque) {
	float subtotal = 0;
	do {
		int cod;
		printf("Digite o codigo: ");
		scanf(" %d", &cod);
		if(!cod) {
			printf("Codigo inexistente! Tente novamente.\n");
			return subtotal;
		}
		
		
		Produto *alvo = buscarItem(cod, estoque);
		if(!alvo){
			printf("Esse item nao existe... Tente novamente\n");
			continue;
		}
		printProduto(*alvo);
		
		printf("Quantas unidades voce deseja? ");
		int qtde;
		scanf(" %d", &qtde);
		
		if(alvo->estoque < qtde){
			printf("Quantide indisponivel.\n");
			continue;
		}
			
		alvo->estoque -= qtde;
		subtotal += qtde * alvo->valor;
		
		printf("\nItem adicionado no carrinho! Subtotal ficou de %.2f$\n", subtotal);
		printf("Deseja continuar ? (1 - Sim 0 - Não): ");
		
		int resp;
		scanf(" %d", &resp);
		
		if(resp)
			continue;
			
		else
			printf("Total do carrinho: %.2f$ \n", subtotal);
			
		float valorP, troco;
		
		printf("Digite o valor para pagar: ");
		scanf(" %f", &valorP);
		
		if(valorP < subtotal) { 
			printf("Dinheiro insuficiente! Não vendemos fiado! faltam %.2f$\n", subtotal - valorP);
			return subtotal;
		}
	
		troco = valorP - subtotal;
		printf("Seu troco %.2f$\n", troco);
		 
		return subtotal;
	}while(1);
}

int produtoRepet(int cod, dsProdutos* estoque){
	for(int i = 0; i < estoque->cont; i++) {
		if(estoque->lista[i].codigo == cod)
			return 0;
		}
	return 1;
}

void relatorio(int *qtde, float* faturamento){
	
	printf("Vendas realizadas: %d\n", *qtde);
	printf("Faturamento do dia: %.2f\n", *faturamento);
}


int main() {
    
    dsProdutos estoque = criarEstoque();
    float caixa = 0;
    int qtdeVendas = 0;
    float faturamento = 0;
    do {
		switch(interface()) {
			case 1: 
				Produto p = setProduto();
				cadastrarProduto(p, &estoque);
				break;
				
			case 2: 
				float valorVenda = venderProdutos(&estoque);
				caixa += valorVenda;
				faturamento += valorVenda;
				qtdeVendas++;
				break;
			case 3: 
				ConsultarProduto(&estoque);
				break;
			case 4: 
				listarEstoque(estoque);
				break;
			case 5: 
				printf("\n====Fechamento do caixa====\n");
				printf("Total do arrecadado: %.2f\n", caixa);
				printf("Total de produtos vendidos: %d\n", qtdeVendas);
				break;
			case 0:
				printf("\n====Relatorio final====\n");
				relatorio(&qtdeVendas, &faturamento);
				printf("\nPrograma encerrado:\n");
				return 0;
			default: 
				printf("Digite um valor válido:\n");
		}
		
		
	}while(1);

    //the destroyer of codes
}


