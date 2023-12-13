//  Este programa exemplifica a estrutura de um programa t�pico em C++
#include <iostream>

// Inclui a declara��o da classe
#include "CAplicacao.h" 

/** Note que no arquivo .cpp n�o � necess�rio colocar novamente a documenta��o
 * que foi colocada no arquivo .h. 
 * A documenta��o no arquivo .cpp costuma usar o padr�o b�sico de C++ que � //
 * e costuma estar mais diretamente relacionada a implementa��o em s�,
 * ou seja, aos detalhes num�ricos e computacionais; 
 * detalhes e explica��o das contas e da l�gica computacional.
 * */
void CAplicacao::Run()
{
  // std::cout escreve na tela  o texto "Bem-vindo ao C++!"
  std::cout << "Bem-vindo ao C++!" << std::endl;
}
