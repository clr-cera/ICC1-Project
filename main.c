#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _produto{ //Esse é o struct para um tipo de produto
  int quantidade;
  float preco;
  char* nome;
  int codigo;
}produto;

int contador_de_linhas(FILE *fp)
{
  char c; int linhas = 1;
  for(c = getc(fp); c!= EOF; c = getc(fp)){
    if(c=='\n')
      linhas++;
  }
  rewind(fp);
  return linhas;
}
/*
 Esta função insere os produtos nos vetores, 
 ela copia os valores passados para o item no indice nos vetores passados
*/
void insere_produto(char* nome, int quantidade, float preco, produto* produtoPonteiro, int indice){ 
  produtoPonteiro->nome = (char *) malloc(100 * sizeof(char)); //Cria o vetor do nome dentro do produto
  produtoPonteiro->codigo = indice;
  for (int i = 0; i < 100; i++) 
    produtoPonteiro->nome[i] = nome[i]; //Copia o nome, do vetor passado (nome) para o vetor criado dentro do produto


  produtoPonteiro->quantidade = quantidade; //Recebe a quantidade
  produtoPonteiro->preco = preco; //Recebe o preco
}

// Esta função aumenta a quantidade do produto do codigo informado
void aumenta_estoque(int quantidade, produto* produtoPonteiro){
  produtoPonteiro->quantidade += quantidade;  
}

// Esta função altera o preço do produto do codigo informado
void modifica_preco(float preco, produto* produtoPonteiro){
  produtoPonteiro->preco = preco;
}

// Esta funcao vende produtos
float venda(int codigo, float saldo, produto* produtoPonteiro, float* total){ //Ela recebe o codigo do produto que foi vendido, o vetor de precos e o vetor de nomes

  if (codigo != -1){ //Se o codigo nao for -1 ele vai vender o produto (aumentar o saldo, aumentar o total da venda, e diminuir 1 da quantidade)
    if(produtoPonteiro->quantidade >= 1){
      saldo += produtoPonteiro->preco;
      *total += produtoPonteiro->preco;
      produtoPonteiro->quantidade -= 1;
      printf("%s %.2f\n", produtoPonteiro->nome, produtoPonteiro->preco); //imprime a venda
    }
  }
  else printf("Total: %.2f\n", *total); //Se o codigo for -1 ele imprime o saldo resultante

  return saldo; //Retorna o saldo apos estas operações
}

//Essa função apresenta o estoque de produtos com suas
void consulta_estoque(produto* produtoLista, int indice){
  for(int i = 0; i<indice; i++){ 
    //Apresenta na tela os valores conforme cada produto (indexado pelo código)
    printf("%d %s %d\n", i, produtoLista[i].nome, produtoLista[i].quantidade); 
  }
}

//Essa função apresenta o saldo total
void consultar_saldo(float saldo){
  printf("Saldo: %.2f\n", saldo);
}

//Essa função extrai o estoque de um arquivo .txt;
produto* extrair_dados(int* quantidade_itens, float* saldo){

  produto *produtoVetor;
  FILE * arquivo;
  arquivo = fopen("arquivo.txt", "r");

  if(arquivo != NULL) {
    fscanf(arquivo, "%d %f", quantidade_itens, saldo);
    produtoVetor = (produto *)malloc((*quantidade_itens)*sizeof(produto)); //Criando espaço para o produto vetor do tamanho do estoque 
    
    for(int i = 0; i<(*quantidade_itens); i++){ //caso exista itens é feito a leitura de cada item e colocado no vetor
      if((((produtoVetor[i]).nome = (char*)malloc(100*sizeof(char)))==NULL))exit(1); //caso não tenha memória disponivel, termina o programa
      fscanf(arquivo, "%d %s %d %f", &(produtoVetor[i].codigo), (produtoVetor[i].nome), &(produtoVetor[i].quantidade), &(produtoVetor[i].preco));
  }
  }else{
    produtoVetor = (produto *)malloc(1*sizeof(produto)); //Criando espaço para o produto vetor do tamanho do estoque 
    
    //printf("Insira a quantidade de produtos:"); //DEBUG
    scanf("%d", quantidade_itens); //Recebe numero de diferentes tipos de produtos
    *quantidade_itens = 0; //
    //printf("Insira o saldo inicial"); //DEBUG
    scanf("%f", saldo);
  }
  fclose(arquivo);
  return produtoVetor;
}

//Essa função armazena os produtos do estoque no arquivo onde terá os dados do estoque;
void salvar_dados(produto * produtoVetor, int tam_produtoVetor, float saldo){
  FILE *arquivo;
  
  if((arquivo = fopen("arquivo.txt", "w")) == NULL){
    //Caso não seja possivel criar o arquivo devido a memória    
    exit(1);
  };
  fprintf(arquivo, "%d\n%f\n", tam_produtoVetor, saldo);
  for(int i = 0; i<tam_produtoVetor; i++){ //Onde é armazenado os dados do produto;
    fprintf(arquivo, "%d %s %d %f\n", produtoVetor[i].codigo, produtoVetor[i].nome, produtoVetor[i].quantidade, produtoVetor[i].preco);
  }

  fclose(arquivo);
}


int main(void){
  float saldo = 0;
  int indice = 0; //Este é o índice para a inserção de novos produtos (o código dele)

  produto* produtoVetor;

  produtoVetor = extrair_dados(&indice, &saldo);  

  while(1){
    char comando[3]; //apesar do comando ter apenas 2 caracteres, o computador insere o /0 no final.
    scanf("%s", comando);
    
    if(strcmp(comando, "IP")==0) // COMANDO DE INSERIR PRODUTO
    {
      char nome[100]; int quantidade; float preco;
      scanf("%s %d %f", nome, &quantidade, &preco); //Recebe os valores
      produtoVetor = realloc(produtoVetor, (indice+1) * sizeof(produto));
      insere_produto(nome, quantidade, preco, &produtoVetor[indice], indice); //Insere os valores no vetor
      indice++; //Aumenta o índice para a proxima inserção
  
    }
    
    if(strcmp(comando, "AE")==0) // COMANDO DE AUMENTAR ESTOQUE
    {
      int codigo; int quantidade;
      scanf("%d %d", &codigo, &quantidade); //Recebe os valores

      aumenta_estoque(quantidade, &produtoVetor[codigo]); //Coloca no vetor quantidades
    }
    
    if(strcmp(comando, "MP")==0) // COMANDO DE MODIFCAR PREÇO
    {
      int codigo; float preco;
      scanf("%d %f", &codigo, &preco); //Recebe os valores

      modifica_preco(preco, &produtoVetor[codigo]); //Coloca no vetor precos
    }
    
    if(strcmp(comando, "VE")==0) // COMANDO DE VENDER PRODUTOS
    {
      int codigo = 0;
      float total = 0;
      
      while(codigo != -1){ //Quando receber o codigo -1, vai executar pela ultima vez
        scanf("%d", &codigo);

        saldo = venda(codigo, saldo, &produtoVetor[codigo], &total); //A função vai retornar sempre o saldo apos vender uma unidade do produto, aumentar o total da venda alterar a quantidade no estoque e imprimir a saída necessária, caso o codigo seja -1, irá apenas imprimir o saldo
      }

      printf("--------------------------------------------------\n"); 
    }
    
    if(strcmp(comando, "CE")==0) // COMANDO DE CONSULTAR ESTOQUE
    {
      consulta_estoque(produtoVetor, indice); //Recebe os parametros necessários para a função void apresentar os valores
      printf("--------------------------------------------------\n"); 
    }
    
    if(strcmp(comando, "CS")==0) // COMANDO DE CONSULTAR SALDO
    {
      consultar_saldo(saldo); //O saldo é passado por parâmetro apenas para apresenta-lo na função
      printf("--------------------------------------------------\n"); 
    }

    if(strcmp(comando, "FE")==0) // COMANDO PARA FINALIZAR A EXECUÇÃO
    {
      break;
    }
  }
  
  //Adicionando produtos no estoque
  salvar_dados(produtoVetor, indice, saldo);
  
  //Liberação da memória alocada dinamicamente na Heap
  for(int i = 0; i < indice; i++)
    free(produtoVetor[i].nome);
  free(produtoVetor);
  
  return 0;
}