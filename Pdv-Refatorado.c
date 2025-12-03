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

dsProdutos criarEstoque(){
	dsProdutos novo;
	novo.cont = 0;
	return novo;
}

int interface(){
	printf("1 - Cadastrar Produto\n");
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
	input(INT, "Digite o codigo do produto", &p.codigo);
	input(STR, "Digite a descrição do produto: ", p.descricao);
	input(STR, "Digite o valor do produto: ", &p.valor);
	input(STR, "Digite a quantidade: ", &p.estoque);
	return p;
}

void cadastrarProduto(Produto p, dsProdutos *estoque){
	estoque->lista[estoque->cont] = p;
	estoque->cont++;
}

void printProduto(Produto p){
	printf("Codigo: %d\n", p.codigo);
	printf("Descrição: %s\n", p.descricao);
	printf("Valor: %.2f\n", p.valor);
	printf("Quantidade: %d\n", p.estoque);
}

void listarEstoque(dsProdutos estoque){
	for(int i = 0; i < estoque.cont; i++)
		printProduto(estoque.lista[i]);
}

Produto *buscarItem(int cod, dsProdutos *estoque){
	for(int i = 0; i < estoque->cont; i++)
		if(cod == estoque->lista[i].codigo)
			return &estoque->lista[i];
	return NULL;
}

float venderProdutos(dsProdutos *estoque) {
	float subtotal = 0;
	do {
		printf("Digite o codigo: ");
		int cod;
		if(!cod)
			return subtotal;
		scanf(" %d", &cod);
		
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
	}while(1);
}


int main() {
    
    dsProdutos estoque = criarEstoque();
    int caixa = 0;
    
    do {
		switch(interface()) {
			case 1: 
				Produto p = setProduto();
				cadastrarProduto(p, &estoque);
				break;
				
			case 2: 
				caixa += venderProdutos(&estoque);
				break;
			case 3: 
				listarEstoque(estoque);
			case 0:
				return 0;
		}
		
		
	}while(1);

    //the destroyer of codes
}


