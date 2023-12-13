// Este programa exemplifica a estrutura de um programa t�pico em C++.
// Note que no arquivo .h documentamos a interface; a forma de uso;
// No arquivo .cpp detalhes dos c�digos; l�gica num�rica-computacional.
#include <string>
#include <vector>

/** Breve descri��o da classe termina com ponto. 
 * ...descri��o detalhada da classe...
 * ...pode ter v�rias linhas...
**/
class CAplicacao
{
public:    
    /// Descri��o breve do construtor.
    /** Descri��o detalhada do construtor. 
     *  ....blablabla....
     */
    CAplicacao()	{};
    
    /// Descri��o breve do construtor.
    /** Descri��o detalhada do construtor. 
     *  ....blablabla....
     */
   ~CAplicacao()	{};
   
   /// Apenas exibe mensagem na tela.
   void Run();
   
   /// Seta valor de x
   void X( int _x) 	{  x = _x; }
   
   /// Retorna valor de x 
   int X() 		{ return x; }
    
private:
    /// Descri��o breve do m�todo M1.
    /**
     * Descri��o detalhada....
     * Posso incluir informa��es sobre par�metros e retorno.
     * @param a um inteiro que representa ....
     * @param s uma string que representa ....
     * @return retorna ...
    */
    int M1(int a, std::string s);
       
    /// Descri��o breve do atributo...
    /** Descri��o detalhada do atributo... */
    std::vector<int> vy;

    /// Descri��o breve do atributo...
    int x;
 
    int z; ///< Descri��o breve (use apenas se for bem curta!).
    
    /// Enum representa (descri��o breve).
    /** Descri��o detalhada. */
    enum Enum { 
                 EVal1, ///< Breve descri��o EVal1. 
                 EVal2, ///< Breve descri��o EVal2. 
                 EVal3  ///< Breve descri��o EVal3. 
               } ;
	       
    /// Descri��o breve.
    /** Descri��o detalhada. */
    Enum   variavelDoTipoEnumeracao;  
       
};
