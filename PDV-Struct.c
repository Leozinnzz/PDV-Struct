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
	
	int opc;
	int cont = 0;
	Produto estoque[MAX];
	
	
	while(cont < MAX) {
		
		
		printf("\n=======OPÇÕES========\n"); 
		printf("1 - Cadrastar Produto \n");
		printf("2 - Vender Produto \n");
		printf("3 - Novo carrinho de compras\n");
		
		printf("\nEscolha uma das opções: ");
		scanf(" %d", &opc);
		
		switch(opc) {
			//cadrastar produto
			case 1:
				printf("Digite o codigo do produto ");
				scanf("%d", &p.codigo);
				
				//encerrar o loop
				if(p.codigo <= 0) {
					printf("\nPROGRAMA ENCERRADO\n");
					break;
				}
				
				printf("Qual produto vc vai querer? ");
				scanf(" %[^\n]s ", p.descricao);
				
				
				int repetido = 0;
				//verificar se o numero esta se repetindo
				for(int i = 0; i < cont; i++) {
					if(cadrasto[i].codigo == p.codigo) { 
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
					cadrasto[cont].estoque++;
				}
				break;
			case 2: 
				//fase de vendas
				printf("Digite o codigo do produto para a venda: ");
				scanf(" %d", &p.codigo);
				
				//verificar se o produto existe
				int existe = 0;
				for(int i = 0; i < cont; i++ ){
					if(p.codigo == cadrasto[i].codigo) { 
						existe = 1;
						break;
					}
				}
				
				if(existe) {
					//imprimir os dados
					for(int i = 0; i < cont; i++) { 
						printf("Codigo do produto: %d\n",cadrasto[i].codigo);
						printf("Item: %s\n", cadrasto[i].descricao);
					}
				}
				
				else { 
					printf("\nCodigo não existente! Tente novamente \n");
					break;
				}
					
				break;
			case 3: 
				printf("\nNovo carrinho de compras\n");
		}
		
	}
	
}

