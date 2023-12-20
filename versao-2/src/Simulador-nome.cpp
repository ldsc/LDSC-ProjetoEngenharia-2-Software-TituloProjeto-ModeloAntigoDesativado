
/** Este programa exemplifica a estrutura/layout de um programa t�pico em C++ */

// Inclui o arquivo "CAplicacao.h" que tem a declara��o da classe CAplicacao
#include "CAplicacao.h"

/// A fun��o main(), retorna um inteiro, se chama main() e nao tem nenhum parametro
int main ()
{
  CAplicacao ap;  // Cria objeto do tipo CAplicacao com nome ap

  ap.Run ();	  // Executa o m�todo Run() do objeto ap

  return 0;	  // A fun��o main() deve retornar um inteiro 
                  // o zero indica que o programa terminou bem.
}

