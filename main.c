#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
  float saldo = 100;
  int n_produtos; //numero de produtos que cabem no estoque
  scanf("%d", &n_produtos);
  //depois precisamos alocar dinamicamente os vetores nome, quantidade e valor de acordo com o n de produtos.
  while(1){
    char comando[3]; //apesar do comando ter apenas 2 caracteres, o computador insere o /0 no final.
    scanf("%s", comando);
    if(strcmp(comando, "IP")==0)
    {
      char nome[100]; int quantidade; float preco;
      scanf("%s %d %f", nome, &quantidade, &preco);
      //insere_produto(nome, quantidade, preco); //funcao precisa ser feita
    }
    if(strcmp(comando, "AE")==0)
    {
      int codigo; int quantidade;
      scanf("%d %d", &codigo, &quantidade);
      //aumenta_estoque(codigo, quantidade); //funcao precisa ser feita
    }
    if(strcmp(comando, "MP")==0)
    {
      int codigo; float preco;
      scanf("%d %f", &codigo, &preco);
      //modifica_preco(codigo, quantidade); //funcao precisa ser feita
    }
    if(strcmp(comando, "VE")==0)
    {
      int codigo = 0;
      do
      {
        scanf("%d", &codigo);
        //venda(codigo, &saldo); //funcao precisa ser implementada
      } while(codigo != (-1));
    }
    if(strcmp(comando, "CE")==0)
    {
      //consulta_estoque(); //funcao precisa ser implementada
    }
    if(strcmp(comando, "CS")==0)
    {
      //consulta_saldo(); //funcao precisa ser implementada
    }
    if(strcmp(comando, "FE")==0)
    {
      return 0;
    }
  }
}
