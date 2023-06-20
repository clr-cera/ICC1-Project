#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Esta função insere os produtos nos vetores, 
 ela copia os valores passados para o item no indice nos vetores passados
*/
void insere_produto(char* nome, int quantidade, float preco, char** nomes, int* quantidades, float* precos, int indice){ 
  nomes[indice] = (char *) malloc(100 * sizeof(char)); //Cria o vetor do nome dentro de nomes
  for (int i = 0; i < 100; i++) 
    nomes[indice][i] = nome[i]; //Copia o nome, do vetor passado (nome) para o vetor criado (nomes)


  quantidades[indice] = quantidade; //Recebe a quantidade
  precos[indice] = preco; //Recebe o preco
}

// Esta função aumenta a quantidade do produto do codigo informado
void aumenta_estoque(int codigo, int quantidade, int* quantidades){
  quantidades[codigo] += quantidade;  
}

// Esta função altera o preço do produto do codigo informado
void modifica_preco(int codigo, float preco, float* precos){
  precos[codigo] = preco;
}

// Esta funcao vende produtos
float venda(int codigo, float saldo, float* precos, char** nomes, int* quantidades,float* total){ //Ela recebe o codigo do produto que foi vendido, o vetor de precos e o vetor de nomes

  if (codigo != -1){ //Se o codigo nao for -1 ele vai vender o produto (aumentar o saldo, aumentar o total da venda, e diminuir 1 da quantidade)
  saldo += precos[codigo];
  *total += precos[codigo];
  quantidades[codigo] -= 1;
  
  
  printf("%s %.2f\n", nomes[codigo], precos[codigo]); //imprime a venda
  }
  else printf("Total: %.2f\n", *total); //Se o codigo for -1 ele imprime o saldo resultante

  return saldo; //Retorna o saldo apos estas operações
}

//Essa função apresenta o estoque de produtos com suas
void consulta_estoque(char **nomes, int *quantidades, int indice){
  for(int codigo = 0; codigo<indice; codigo++){ 
    //Apresenta na tela os valores conforme cada produto (indexado pelo código)
    printf("%d %s %d\n", codigo, nomes[codigo], quantidades[codigo]); 
  }
}

//Essa função apresenta o saldo total
void consultar_saldo(int saldo){
  printf("Saldo: %d", saldo);
}

int main(void){
  float saldo = 100;
  int estoque;
  int indice = 0; //Este é o índice para a inserção de novos produtos (o código dele)

  char** nomes; //Vetores para dicionario
  int* quantidades;
  float* precos;

  scanf("%d", &estoque); //Recebe numero de diferentes tipos de produtos

  //Alocação dos vetores:
  nomes = (char **) malloc(estoque * sizeof(char*)); 
  quantidades = (int *) malloc(estoque * sizeof(int));
  precos = (float *) malloc(estoque * sizeof(float));


  while(1){
    char comando[3]; //apesar do comando ter apenas 2 caracteres, o computador insere o /0 no final.
    scanf("%s", comando);
    
    if(strcmp(comando, "IP")==0) // COMANDO DE INSERIR PRODUTO
    {
      char nome[100]; int quantidade; float preco;
      scanf("%s %d %f", nome, &quantidade, &preco); //Recebe os valores
      
      insere_produto(nome, quantidade, preco, nomes, quantidades, precos, indice); //Insere os valores nos vetores 
      indice++; //Aumenta o índice para a proxima inserção

    }
    
    if(strcmp(comando, "AE")==0) // COMANDO DE AUMENTAR ESTOQUE
    {
      int codigo; int quantidade;
      scanf("%d %d", &codigo, &quantidade); //Recebe os valores

      aumenta_estoque(codigo, quantidade, quantidades); //Coloca no vetor quantidades
    }
    
    if(strcmp(comando, "MP")==0) // COMANDO DE MODIFCAR PREÇO
    {
      int codigo; float preco;
      scanf("%d %f", &codigo, &preco); //Recebe os valores

      modifica_preco(codigo, preco, precos); //Coloca no vetor precos
    }
    
    if(strcmp(comando, "VE")==0) // COMANDO DE VENDER PRODUTOS
    {
      int codigo = 0;
      float total = 0;
      
      while(codigo != -1){ //Quando receber o codigo -1, vai executar pela ultima vez
        scanf("%d", &codigo);

        saldo = venda(codigo, saldo, precos, nomes, quantidades, &total); //A função vai retornar sempre o saldo apos vender uma unidade do produto, aumentar o total da venda alterar a quantidade no estoque e imprimir a saída necessária, caso o codigo seja -1, irá apenas imprimir o saldo
      }

      printf("--------------------------------------------------\n"); 
    }
    
    if(strcmp(comando, "CE")==0) // COMANDO DE CONSULTAR ESTOQUE
    {
      consulta_estoque(nomes, quantidades, indice); //Recebe os parametros necessários para a função void apresentar os valores
      printf("--------------------------------------------------\n"); 
    }
    
    if(strcmp(comando, "CS")==0) // COMANDO DE CONSULTAR SALDO
    {
      consulta_saldo(saldo); //O saldo é passado por paramêtro apenas para apresenta-lo na função
      printf("--------------------------------------------------\n"); 
    }

    if(strcmp(comando, "FE")==0) // COMANDO PARA FINALIZAR A EXECUÇÃO
    {
      break;
    }
  }
  //Liberação da memória alocada dinamicamente na Heap
  free(precos); 
  free(quantidades);
  for(int i = 0; i < indice; i++)
    free(nomes[i]);
  free(nomes);
  
  return 0;
}
