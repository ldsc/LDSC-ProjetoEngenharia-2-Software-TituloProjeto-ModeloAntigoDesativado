/**
===========================================================================
Lista com as principais novidades de c++20/14/17/20/23
Autor: Andr� Duarte Bueno.
Nota: procure nos diret�rios por c++20-14-17-20-23.cpp
Referencias: livros de c++20/14/17/20/23
Sites: isocpp.org herbsutter.com en.cppreference.com

===========================================================================
Lista com os principais arquivos #include
=========================================================================== 
*/
#include <algorithm>    // Algoritmos da STL
#include <functional>   // Fun��es
#include <tuple>        // Tuplas
#include <chrono>       // Biblioteca date time no c++20
#include <regex>	    // Biblioteca regex, replace, match_results
#include <random>       // Biblioteca n�meros randomicos e estat�stica
#include <thread>       // Biblioteca threads
#include <mutex>		// Bibliotecas processamento paralelo
#include <condition_variable>
#include <filesystem>
namespace fs = std::filesystem;

===========================================================================
Lista com as principais novidades de c++20 -> N�cleo da linguagem
=========================================================================== 
// [ ] ---------------------------------------------------------------------> auto
auto x = 3;
auto x { 1 };    // inteiro no C++17, lista inicializa��o no  c++20

// [ ] ---------------------------------------------------------------------> decltype
decltype(x) y;

// [ ] ---------------------------------------------------------------------> nullptr
char *pc = nullptr;     // OK
int  *pi = nullptr;     // OK

// [ ] ---------------------------------------------------------------------> rvalue reference
template<typename T> void f(T&& param);                 // par�metro do tipo rvalue reference
template<typename T> void f(std::vector<T>&& param);    // par�metro do tipo rvalue reference
int main() { int&& var1 = 10;                           // rvalue reference (nome para uma constante)
cout << "\nvar1 = " << var1 ; }

// [ ] ---------------------------------------------------------------------> novas strings
char     s8[]  = u8"UTF-8 cstring. ";                   // const char[].
char16_t s16[] = u"UTF-16 cstring. ";                   // const char16_t[].
char32_t s32[] = U"UTF-32 cstring. ";                   // const char32_t[].
cout << u8"This is a Unicode Character: \u2018"       << endl;

// [ ] ---------------------------------------------------------------------> raw strings 
// c++20 fornece a op��o de raw strings literal: R("string \t 1"), n�o � interpretada
cout <<  "(\a xx \b yy \t zz \n)" << endl;
cout << R"(\a xx \b yy \t zz \n)" << endl;

// [ ] ---------------------------------------------------------------------> sizeof
// c++20 permite obter o sizeof de membro da classe
class CPonto { public: double x; double y;};
cout << "sizeof(CPonto) = "    << sizeof(CPonto)    << endl;
cout << "sizeof(CPonto::x) = " << sizeof(CPonto::x) << endl;

// [ ] ---------------------------------------------------------------------> enum class
// A vantagem de enum class � que a mesma n�o pode ser convertida para int;
enum class EDiaSemanaCpp11 { segunda = 2, terca = 3, quarta = 4, quinta = 5, sexta = 6 };

// [ ] ---------------------------------------------------------------------> enum class: tipo
// Tamb�m podemos definir o tipo usado pela enumera��o
enum class EMesesAnoCpp11: unsigned int { janeiro = 1, fevereiro, marco, abril, 
maio, junho, julho, agosto, setembro, outubro, novembro, dezembro };

// [ ] ---------------------------------------------------------------------> union 
union UMiscelanea {   bool b;  int i;  double d;
  CPonto p;   // c++20 retirou restri��o dos tipos aceitos em uni�es
  UMisccelanea() { new( &p ) CPonto(); }     
};
// [ ] ---------------------------------------------------------------------> static_assert 
// Mensagem de erro em tempo de compital��o
static_assert(constant-expression, error-message);
static_assert(sizeof(int) <= sizeof(T), "A dimens�o de T n�o � suficiente!");
static_assert(std::is_integral<T>::value, "O par�metro de f deve ser do tipo integral.");
static_assert((pi < 3.14) && ( pi > 3.15), "Aumentar precis�o de pi!");
static_assert(constant-expression); // C++17 sem mensagem

// [ ] ---------------------------------------------------------------------> constexpr
constexpr int FuncaoConstante() { return 5; }
constexpr int XY (int x, int y) { return x * y; }
constexpr double aceleracaoGravidade = 9.8;

// [ ] ---------------------------------------------------------------------> range based for
int vetor_estilo_c[5] = { 1, 2, 3, 4, 5 };
for (int &elemento_vetor : vetor_estilo_c) cout << elemento_vetor << endl;
vector<int> v(5);
for( auto elemento_vetor : v )             cout << elemento_vetor << endl;

// [ ] ----------------------------------------------------------------> Inicializa��o uniforme
int x3{5.0}, x4 ={5.3}; // Com inicializa��o uniforme de c++20 aponta erro pois 5.0 � double
int x5, x6{}; 		// x5 valor indefinido, x6 valor padr�o = 0
int *ptr1,*ptr2{};    	// ptr1 valor indefinido, ptr2 em c++20 assume valor nullptr
char cx{14},cy{35000};  // cx OK, 14 � do tipo inteiro; cy Erro, estouro do intervalo
std::vector<int> vx { 0, 1, 2, 4, 5 };    // OK
std::vector<int> vy { 1, 2.3, 4, 5.6 };   // Erro
int vc1[3];   // Cria vetor estilo de C, com 3 elementos [0->2], valores indefinidos
int vc2 []= {1,2,3};  // Cria vetor estilo de C, com 3 elementos [0->2], valores definidos

// [ ] -----------------------------------------------------------------> Lista inicializa��o
class CLista { private:  vector< float > v;
               public:   CLista( std::initializer_list<float> lista ): v(lista){};
                         vector< float > V()	{ return v; }; };

class CPonto {  double x;   double y;        // Construtor
CPonto(double _x, double _y): x(_x), y(_y) { std::cout << "Passou pelo construtor de SPonto;";} };
CPonto GetCPonto() { return { 0.0, 0.9 }; } // O objeto � criado sem usarmos o tipo CPonto

void Saida ( std::initializer_list<int> l)  // Note que recebe como par�metro a lista l.
{    for (auto it = l.begin(); it != l.end(); ++it) std::cout << *it << "\n"; }

int main() {                                // Chama fun��o saida, imprime valores na tela
  Saida ({0,1,2,3,4,5,6,7,8,9});            // Usando initializer_list
  CLista lista{ 5.1, 5.2, 5.3, 5.4 };       // Cria objeto lista
  vector<int> v{ 1,2,3,4,5 };               // Usando initializer_list com biblioteca padr�o

  CPonto p2  { 5.1 , 6.1 };                 // Usando inicializa��o uniforme padr�o c++20
  // Criando uma lista de pontos usando inicializa��o uniforme padr�o c++20
  CPonto lista_pontos[4] =  { { 5.2,6.2 }, {5.3,6.3}, {5.4,6.4}, {5.5,6.5} };
}

// [ ] ---------------------------------------------------------------------> Fun��es lambda
/*auto nomeFuncao = [captura](parametros)->tipoRetorno {corpo da funcao}
[]: N�o capturar nada. 
[=]: Todas as vari�veis externas s�o capturadas por valor.
[&]: Todas as vari�veis externas s�o capturadas por refer�ncia.
[x, &y]: capturar x por valor(c�pia) e y por refer�ncia.
[&, x]: Todas as vari�veis externas s�o capturadas por refer�ncia, exceto x que � por valor.
[=, &z]: Todas as vari�veis externas s�o capturadas por valor, exceto z que � por refer�ncia. */

// Fun��o lambda an�nima � criada e j� executada. O () executa a fun��o.
[] { std::cout << "Fun��o lambda criada e j� executada" << std::endl;   } ();

// Fun��o lambda criada e chamada a seguir
auto l = [] { std::cout << "Fun��o lambda criada e chamada a seguir" << std::endl; };
l();                                                                // Chama fun��o lambda

// Defini��o de fun��o lambda que n�o captura nada e que n�o recebe par�metros.
auto ptr_funcao = [] () { cout << "Ol� mundo!\n"; };
ptr_funcao();

// Defini��o de fun��o lambda que n�o captura nada e que recebe os par�metros x e y.
auto ptr_funcao2 = [](int x, int y) { return x + y; }
cout << " x + y = " << ptr_funcao2(3,4) << endl;

// Usando fun��o lambda com captura por referencia
int soma = 0; 
auto Soma = [&soma]( int x ) { soma += x; cout << "Soma = " << soma << endl; };
Soma(10);

// [ ] ---------------------------------------------------------------> novo formato fun��es
auto X(int _x) -> void 		{ x = _x; }   // Nova vers�o de auto elimina necessidade -> tipo
auto X() -> int			{ return x; }
auto Set(int _x, int _y) -> void;
auto CPonto::Set(int _x, int _y) -> void{ x = _x;  y = _y; }

// [ ] ---------------------------------------------------------------------> Ponteiro Fun��o
void FC(int x)       { cout << "FC x=" << x << endl; } // // Declara e define fun��o
void (*pFC)(int) = &FC;                       // ponteiro para fun��o C++98
typedef void (*PonteiroFuncao)(double);       // ponteiro para fun��o C++98

using PonteiroFuncao = void (*)(double);      // ponteiro para fun��o c++20
std::function<void(int)> pF11 = &F11;         // ponteiro para fun��o c++20
auto autopF11 = &F11;                         // ponteiro para fun��o c++20

class C {    void F11(int x)   { cout << "F11 x=" << x << endl; } };
void (C::*pF03)(int) = &C::F03;               //  ponteiro para fun��o C++98
std::function<void (C&, int)> pF11_ref = &C::F11; // funciona como referencia
std::function<void (C*, int)> pF11_ptr = &C::F11; // funciona como ponteiro


// [ ] ----------------------------------------------------------------> delega��o construtor
explicit CPonto (int _x, int _y):x(_x),y(_y) 	{}
CPonto(int xy) : CPonto(xy,xy) 	{}  // um construtor chama o outro

// [ ] ---------------------------------------------------------------------> default e delete
class NonCopyable { public:  // Diz para o compilador desabilitar o operator= (n�o criar)
  NonCopyable& operator=(const NonCopyable&) = delete;
  
  // Diz para o compilador desabilitar o construtor de c�pia (n�o criar)
  NonCopyable(const NonCopyable&) = delete;
  
  // Diz para o compilador criar o construtor default
  NonCopyable() = default; 

// [ ] ---------------------------------------------------------------------> override e final
class CPonto { virtual auto Entrada() -> void;
               virtual auto Saida() -> void; };

class CCirculo: public CPonto {
    virtual void Entrada() override ; // sobrecreve m�todo virtual da classe base
    virtual void Saida() final; };    // �ltima atualiza��o de Saida

// [ ] ---------------------------------------------------------------------> for_each
char s[] = "Ol� Mundo!";
for_each( s, s + sizeof(s), [] (char c){ cout << c << endl; });
int vc[] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 };
for_each( begin(vc), end(vc), [](int x) { cout << x << ' ';});
int soma = 0;  
for_each( begin(vc), end(vc), [&soma] (int x) { soma += x;});

===============================================================================
Lista com as principais novidades de c++20 -> Biblioteca std
===============================================================================
// [ ] ---------------------------------------------------------------------> array
#include <array>
std::array<int, 4> array_4_int { {1,2,3,4} };    	// Precisa de duplo {}
array<int, 3> array_3_int = {1, 2, 3};   		    // Apos = precisa {} simples
array<string, 2> array_2_string = {"a", "b"} ;
sort(array_4_int.begin(), array_4_int.end());
for(auto& ae: array_4_int)         cout << ae << ' ';

// [ ] --------------------------------------------------------------> all_of any_of none_of
void Teste( vector<int> &v , string msg )
{ cout << "Vetor " << msg << endl;
  if ( all_of(v.begin(), v.end(), [](int ev) { return ev > 0;} ) )   // Todos positivos?
    cout << "Todos positivos\n";
  if ( any_of(v.begin(), v.end(), [](int ev) { return ev > 0;} ) )   // Pelo menos um positivo?
    cout << "Pelo menos um positivo\n"; }
int main() {  vector<int> v1{   1, 2, 3, 4, 5};    Teste( v1 , "v1"  );
              vector<int> v2{ 0,-1, 2, 3, 4, 5};   Teste( v2  , "v2" ); }
              
// [ ] ---------------------------------------------------------------------> unique_ptr
std::unique_ptr<int> ptr_int3( new int(3) );     // Cria ponteiro e objeto
cout << *ptr_int3 << endl;                       // Usa
unique_ptr<int> ptr_int5  = std::move(ptr_int3); // Transfere propriedade
cout << *ptr_int5 << endl;                       // Usa 
ptr_int5.reset();                                // Destr�e
ptr_int3.reset();                                // N�o faz nada.      

// [ ] ---------------------------------------------------------------------> shared_ptr
// Use shared_ptr? quando quizer v�rios ponteiros apontando para mesmo objeto,
// somente quando o �ltimo for deletado o objeto ser� efetivamente deletado. 
shared_ptr<int> ptr_int6(new int(6));            // Cria ponteiro e objeto
cout << *ptr_int6 << endl;                       // Usa
shared_ptr<int> ptr_int7 = ptr_int6;             // ptr7 aponta p/ mesmo objeto que ptr6
cout << *ptr_int7 << endl;
ptr_int6.reset();                                // N�o destr�e e objeto 
cout << *ptr_int7 << endl;                       // Usa objeto 
ptr_int7.reset();                                // Agora deleta objeto

// [ ] ---------------------------------------------------------------------> weak_ptr
shared_ptr<int> ptr_int8(new int(8));
cout << *ptr_int8 << endl;
weak_ptr<int> wptr_int8 = ptr_int8;            // ptr_int8 owns the memory. 
  {
  shared_ptr<int> ptr_int9 = wptr_int8.lock(); // Agora p8 e p9 acessam a mesma mem�ria.
  cout << *ptr_int9 << endl;
  if( ptr_int9 )                               // Sempre verifique o ponteiro 
    cout << *ptr_int9 << endl;                 // Fa�a algo com ptr_int9
  }     // ptr_int9 � destru�do; ptr_int8 volta a ter a propriedade.
  cout << *ptr_int8 << endl; 
  ptr_int8.reset();                            // A memoria � deletada.
}

// [ ] ---------------------------------------------------------------------> function 
#include <functional>
function<double(double)> fx2 = [](double x) { return x*x;};  // funcao f
function<double(double)> f2x = [](double x) { return 2.0*x;};// funcao g
// Cada vez mais perto da nota��o matem�tica! Agrupando fun��es, como g(f(x));
std::function<double(double)> gf(function<double(double)> f, function<double(double)> g ) 
     { return [=](double x) { return g(f(x)); };
// Uso de gf, cria funcao fx4, retorna double, recebe funcao
function<double(double)> fx4 = gf(fx2, fx2);
int main() {    double x = 3;
   cout << "x = " << x << end;
   cout << "fx2 = " << fx2(x) << endl;
   cout << "fx4 = " << fx4(x) << endl; }

 // [ ] ---------------------------------------------------------------------> bind
// Declara fun��o f que recebe dois par�metros, um int e uma string
void fis( int x, string s) { cout << "int x = " << x << " string s = " << s << endl; }
int main() {
  fis( 2, " oi tudo bem ");
  // Cria ponteiro para fun��o fis que recebe apenas a string
  std::function<void( string )> fs = std::bind(&fis, 3 , std::placeholders::_1);
  fs("Usando fs, passando apenas a string");
  // Cria ponteiro para fun��o alternativa que recebe apenas o inteiro
  function<void( int )> fi = std::bind(&fis, "Usando fi" ,std::placeholders::_2);
  fi(7); }

// [ ] ---------------------------------------------------------------------> pair
// Mostra uso de tie com pair<> e equivalencia de pair com tuple
  pair<double,double> p = make_pair(1.1,2.2);
  cout << "get<0>(p) = " << get<0>(p) 	<< " , get<1>(p) = " 	<< get<1>(p) << endl;
  cout << "p.first   = " << p.first 	<< " , p.second  = " 	<< p.second << endl;

// [ ] ---------------------------------------------------------------------> tuple
// Mostra uso de tuple, get<>, tie, pair 
#include <tuple>
// Cria tuple com 3 doubles
tuple<double, double, double> notasJoao(8.7,4.2,5.7);
cout<< "\nJoao\n"
      << "P1: " << get<0>(notasJoao) << ", "	// Acesso aos elementos da tuple
      << "P2: " << get<1>(notasJoao) << ", "	// usando funcao get<indice>(objeto_tuple)
      << "P3: " << get<2>(notasJoao) << '\n';
std::get<2>(notasJoao) = 6.3; 		        // Nota p3 corrigida, usa referencia.
      
// Mostra uso da funcao tie() para obter, separadamente, os valores da tuple
double n1,n2,n3;
tie(n1, n2, n3) = notasJoao;
cout<< "\nJoao\n" << "n1: " << n1 << ", " << "n2: " << n2 << ", " << "n3: " << n3 << '\n';

auto [a,b,c] = notasJoao; // C++17
// [ ] ---------------------------------------------------------------------> forward_as_tuple 
// forward_as_tuple cria objeto temporario que funciona como uma tupla
// para objetos rvalue (right value). Note que como sao rvalue, nao alocam espaco em disco; 
#include <tuple>	// std::tuple e std::make_tuple
// Note que os parametros da tuple sao right value
void print_pack (std::tuple<std::string&&,double&&> pack) 
{   std::cout << std::get<0>(pack) << ", " << std::get<1>(pack) << std::endl; }
int main() { print_pack (std::forward_as_tuple(string("Joao"), 8.7)); }

// [ ] ---------------------------------------------------------------------> remove_if
bool is_even(int N) { return N % 2 == 0; } // Retorna verdadeiro se for par
int main() {   vector<int> v{1,2,3,4,5,6};
  for_each (v.begin(),v.end(),[](int ev){ cout << ev << '\t'; });  // Vetor v antes de remove_if
  remove_if(v.begin(),v.end(),is_even);  
  for_each (v.begin(),v.end(),[](int ev){ cout << ev << '\t'; });  // Vetor v depois de remove_if

  // Efetivamente remove elementos no intervalo final do vetor
  v2.erase(remove_if(v2.begin(), v2.end(), is_even), v2.end());  }

// [ ] ---------------------------------------------------------------------> random
// O gerador n�meros randomicos tem duas partes; um motor que gera n�meros randomicos 
// e uma distribui��o matem�tica. 
// Motores: linear_congruential_engine,subtract_with_carry_engine e mersenne_twister_enginee.
// Distribui��es: uniform_int_distribution, uniform_real_distribution, 
// bernoulli_distribution, binomial_distribution, geometric_distribution, poisson_distribution,
// normal_distribution, student_t_distribution, chi_squared_distribution, 
// exponential_distribution, gamma_distribution, lognormal_distribution, 
// cauchy_distribution, lognormal_distribution, weibull_distribution, 
// extreme_value_distribution, fisher_f_distribution, negative_binomial_distribution,  
// discrete_distribution, piecewise_constant_distribution, piecewise_linear_distribution.
#include <random>
int main()
{ uniform_int_distribution<int> distribuicao(-20, 20); // Cria distribui��o uniforme
  mt19937 motor;                                       // Cria motor "Mersenne twister MT19937"
  int numeroRandomico = distribuicao(motor);           // Gera n�mero aleat�rio

  std::normal_distribution<double>  normal(0.0,1.0);   // Normal, media 0 e desvio padrao 1
  cout << " media = " << normal.mean() << " desvio padrao = " << normal.stddev() 
       << " max = " << normal.max() << " min = " << normal.min() << endl;
  normal = normal_distribution<double>(12,3);          // Seta media = 12 e desvio padrao = 3

std::default_random_engine motor2;           // Cria motor, usa default
auto Normal = std::bind(normal, motor2);     // Cria gerador de n�mero aleatorio 
vector<double> vna(500);                     // Cria vetor de numeros aleatorios 
for( double &ev : vna )	ev = Normal();       // Gera n�meros aleat�ros
}

// [ ] ---------------------------------------------------------------------> chrono
#include <chrono> // Biblioteca date time no c++20
#include <ctime>  // Biblioteca date time no C++03 (<time> no C)
int main() { // Cria objeto time_point
  chrono::time_point<chrono::system_clock> start;
// Define valor de start como sendo agora (antes do processamento)
  start = chrono::system_clock::now();
// Chama fun��o com determinado tempo de processamento
  int result = sin(45);  
// Define valor de end como sendo agora (depois do processamento)
  auto end = chrono::system_clock::now();
// count() retorna numero ticks, a diferen�a � convertida em segundos.
  int elapsed_seconds = chrono::duration_cast<chrono::seconds>(end-start).count();
  time_t end_time = chrono::system_clock::to_time_t(end);
  cout << "Computa��o terminada em  " << ctime(&end_time)
       << "tempo(s) decorrido : " << elapsed_seconds << "s\n";
}

// [ ] ---------------------------------------------------------------------> regex (-lregex)
#include <regex>	// regex, replace, match_results
// regex - Classe que representa uma Express�o Regular - ER.
// match_results - representa as ocorr�ncias, casos em que a ER foi encontrada.
// regex_search - fun��o usada para localizar uma ocorr�ncia da ER.
// regex_replace - fun��o que substitue a ocorr�ncia encontrada por outro texto.
// As fun��es regex_search e regex_replace recebem uma express�o regular e uma string e 
// escreve as ocorr�ncias encontradas na estrutura match_results. 
int main(){
if (regex_match ("Palmeiras, Campe�o Mundial 1951", regex("r") ) )
 cout << "\nA express�o regular \"(ras)\" foi encontrada em \"Palmeiras, Campe�o Mundial 1951\"";

// A procura pela expressao regular er, sera feita em s pela funcao regex_match.
string s ("Palmeiras campe�o mundial 1951");	// string a ser pesquisada
regex er ("r)");				// expressao regular usada na pesquisa
if (regex_match (s,er))			// faz a procura
 cout << "\nA express�o regular \"(ras)\" foi encontrada em \"Palmeiras, Campe�o Mundial 1951\"";
  
// Faz a procura usando iteradores
if ( regex_match ( s.begin(), s.end(), er ) )    cout << "range matched\n";

// o mesmo que match_results<const char*> cm;
cmatch cm;    
regex_match ("Palmeiras, Campe�o Mundial 1951",cm,er);
cout << "string literal with " << cm.size() << " matches\n";

// o mesmo que match_results<string::const_iterator> sm;
smatch sm;    
regex_match (s,sm,er);
cout << "string object with " << sm.size() << " matches\n";

regex_match ( s.cbegin(), s.cend(), sm, er);
cout << "Usando intervalo, foram encontradas " << sm.size() << " ocorr�ncias\n";

// usando os flags de forma explicita:
regex_match ( "subject", sm, er, regex_constants::match_default );
cout << "As ocorr�ncias s�o: ";
for (unsigned i=0; i<sm.size(); ++i) {    cout << "[" << sm[i] << "] ";  }
}
---
#include <regex> 
int main(){ std::string fnames[] = {"foo.txt", "bar.txt", "zoidberg"}; 
std::regex txt_regex("[a-z]+\\.txt");
for (const auto &fname : fnames) 
        std::cout << fname << ": " << std::regex_match(fname, txt_regex) << '\n';}
        
// [ ] ---------------------------------------------------------------------> threads (c++20/14/17)
// g++ -std=c++17 thread-Resumo.cpp -o thread-Resumo -lpthread
#include <thread>
#include <mutex>		// Bibliotecas processamento paralelo
#include <condition_variable>
                                        // Fun��o e classe com sobrecarga operador().
void f(){  std::cout << "Ol� Mundo - fun��o f." << std::endl; }
class COlaMundo { public:
 COlaMundo()	{ cout << "\nConstrutor"; }
 ~COlaMundo()	{ cout << "\nDestrutor" ; }
 void operator()(){ Ola();  Mundo(); }
private:
 void Ola() 	{ cout << "\nOl�" ; }
 void Mundo() 	{ cout << "\nMundo - classe COlaMundo." ; }
 void Repeat(int n) { while (n--) {Ola();  Mundo();} }
};
void FuncaoDestacada() {                 // Fun��o destacada
cout << "Fun��o destacada, id = " << this_thread::get_id() << endl;}
int main() {
std::cout   << "\n================THREADS======================";
  std::thread t1{ f };  // Cria e dispara a thread t1 fun��o f
                        // ...c�digos de main em paralelo...
                        // thread de fun��o lambda
  thread t2([](){ cout << "Fun��o lambda." << endl;});
  COlaMundo obj;        // Cria objeto
  thread t3{obj}; 	    // Cria a thread t3
                        // ...c�digos de main em paralelo...
  thread t4( &FuncaoDestacada );                  
  t4.detach();          // Torna a thread destacada, t4 n�o tem mais acesso a join(), usa sleep_for
  t1.join();t2.join();  // Aguarda retorno das threads
  if(! t4.joinable())   // Verifica se n�o foi destacada  
	this_thread::sleep_for ( chrono::seconds(1) );  // Aguarda 1 segundo
  thread t5{&COlaMundo::Repeat,&obj,3}; // executa 3x

  thread t6 = move(t1); // Move t1 para t6
  
  cout  << "\nMain thread, this_thread::get_id() = " << this_thread::get_id() 
        << "\nMain thread, t.get_id() = " << t.get_id() 
        << "\nN�mero de threads, thread::hardware_concurrency() = " 
        << thread::hardware_concurrency() << endl;

  return 0;
}
std::cout   << "\n================THREADS Classes Auxiliares======================";
/// Uma classe que chama join quando e destruida.
class thread_guard {
    std::thread& t; 	/// referencia para uma thread
public:
    /// Construtor deve ser chamado explicitamente
    explicit thread_guard(std::thread& t_): t(t_) 	{}
    /// Destrutor chama join automaticamente.
    ~thread_guard() { if(t.joinable()) t.join(); }
    /// Construtor de copia desativado
    thread_guard(thread_guard const&)=delete;
    /// Operador de atribuicao desativado
    thread_guard& operator=(thread_guard const&)=delete;
};
/// Neste caso a classe � proprietaria da thread e recebe a mesma no ato de construcao.
class scoped_thread {
    std::thread t; 	/// uma thread
public:
    /// Construtor deve ser chamado explicitamente
    explicit scoped_thread(std::thread t_): t(std::move(t_)) {
	if( !t.joinable())
		throw std::logic_error("Not joinable!");	}
    /// Destrutor chama join automaticamente.
    ~scoped_thread() { t.join(); }   
    /// Construtor de copia desativado
    scoped_thread(scoped_thread const&)=delete;
    /// Operador de atribuicao desativado
    scoped_thread& operator=(scoped_thread const&)=delete;
};

int main() {
    COlaMundo obj;
    // dispara thread com objeto_funcao
    thread t(obj); 
    // cria thread_guard que chama join automaticamente
    thread_guard tg(t); // quando sai de escopo.
    // dispara thread que executa f1, vai chamar join automaticamente
    scoped_thread st( std::thread ( f1, "thread secundaria" ) ); 
}
std::cout   << "\n================THREADS com vector======================";
int main() {
  std::vector<std::thread> vthreads;		// Cria vetor de threads
  for( int i = 0; i < 4; ++i )
        vthreads.push_back( std::thread(f) );	// Adiciona fun��es
  for( int i = 0; i < 4; ++i ) {                // Adiciona fun��es lambda
    vthreads.push_back( thread(
	[](){ 	cout 	<< "Fun��o lambda: this_thread::get_id() = "
			<< this_thread::get_id() << endl;}));
    }
  for(auto& t : vthreads)
      t.join();					            // Aguarda finaliza��o
      
  // for_each(vthread.begin(), vthread.end(), std::mem_fun_ref(&std::thread::join));
}
std::cout   << "\n================THREADS Par�metros======================";
void FuncaoParametrosPorCopia(string s) {
    cout << "FuncaoParametrosPorCopia, s = " << s << endl;
    s = "string s modificada em FuncaoParametrosPorCopia.";
}
void FuncaoParametroPorPonteiro(string* s) {
    cout << "FuncaoParametroPorPonteiro, s = " << *s << endl;
    *s = "string s modificada em FuncaoParametroPorPonteiro.";
}
void FuncaoParametrosPorReferencia(string& s) {
    cout << "FuncaoParametrosPorReferencia, s = " << s << endl;
    s = "string s modificada em FuncaoParametrosPorReferencia.";
}
int main() {
    string s = "String passada como par�metro";
    thread t_copy(&FuncaoParametrosPorCopia, s);
    cout << "main thread ap�s FuncaoParametrosPorCopia, s = " << s << endl;
    thread t_pointer(&FuncaoParametroPorPonteiro, &s);
    cout << "main thread ap�s FuncaoParametroPorPonteiro, s = " << s << endl;

    thread t_reference2(&FuncaoParametrosPorReferencia, ref(s));
    cout << "main thread ap�s FuncaoParametrosPorReferencia, ref(s) = " << s << endl;
    t_copy.join(); t_pointer.join(); t_reference2.join();
    return 0;
}
std::cout   << "\n================THREADS MUTEX======================";
class CContador  {
    std::mutex mutex_c;    // Cria um mutex = mutual exclusion
    int contador{0};
public:
    void operator++() {  
        mutex_c.lock();    // Bloqueia 
        ++contador;        
        mutex_c.unlock();  // Libera 
      }
    int Valor() { return contador; }
};
int main() {
 CContador contador;
 vector<thread> vthreads;
 for( int i = 0; i < 40; ++i ) {
  vthreads.push_back( thread( 
    [&contador]() { for(int i = 0; i < 100000; ++i){ ++contador; } }));}
 for(auto& thread : vthreads) 
	 thread.join(); 
 cout << contador.Valor() << endl;
 return 0;
}
int main() {
	mutex mutex_cout; // Mutual Exclusion para acesso a cout
	vector<thread> vt;
	for (int i = 0; i < 5; i++) {
		auto t = thread([i,&mutex_cout]() {
			mutex_cout.lock();   	// Uso de lock
			cout << "thread function: " << i << "\n";
			mutex_cout.unlock(); 	// Uso de unlock
		});
		vt.push_back(move(t)); 		// Uso de move
	}
	for (int i = -5; i < 1; i++) {
	  mutex_cout.lock();			// Uso de lock
	  cout << "main thread i =" << i << "\n";
	  mutex_cout.unlock();			// Uso de unlock
	}
	for_each(vt.begin(), vt.end(), [](thread &t) {
		assert(t.joinable());
		t.join();
	});
	return 0;
}
mutex mcout;                                // mutex com std::lock_guard<std::mutex>
void f1() {   for (int k = 100; k > 0; k--) {
	// lock_guard chama lock no construtor e unlock no destrutor
	std::lock_guard<std::mutex> l(mcout);
	...c�digo compartilhado... uso de cout
	}
}

std::cout   << "\n================THREADS VARI�VEL CONDICIONAL======================";
std::mutex mut;				                  // Cria mutex
std::queue<CData> data_queue;
std::condition_variable data_cond;	          // Cria variavel condicional
void data_preparation_thread() {	          // Prepara dados
    while(more_data_to_prepare()) {
        CData const data = prepare_data();    // Gera dados
        std::lock_guard<std::mutex> lk(mut);  // Bloqueia mutex
        data_queue.push(data);			      // Usa base de dados
        data_cond.notify_one();			      // Notifica variavel condicional
    }	}
void data_processing_thread() {
    while(true) {
	std::unique_lock<std::mutex> lk(mut);	  // Bloqueia mutex
                                              // Aguarda variavel condicional
	data_cond.wait(lk,[]{return !data_queue.empty();}); // liberacao de dados
	CData data=data_queue.front();	          // Usa base de dados
	data_queue.pop();
	lk.unlock();				              // Desbloqueia o mutex
	process(data);				              // Processa dados
	if(is_last_chunk(data))			          // Encerra processamento
		break;
    }	}
int main() {
    std::thread t1(data_preparation_thread);  // Produz dados
    std::thread t2(data_processing_thread);	  // Consome dados    
    t1.join();    t2.join();
}

std::cout   << "\n================THREADS ASYNC FUTURE======================";
#include <future>
#include <iostream>
int  f1() {    return 42;}
void f2(std::string const& message)  { cout << (message + "\n"); }

int main() {        
// Dispara fun��o usando async
auto a1 = async(f2,"1 - Ol� mundo disparado usando async(write_message\n");
// Dispara fun��o write_message usando std::launch::async
auto a2 = async( launch::async,f2,"1 - Ol� mundo disparado usando async(launch::async,write_message,..\n" );
f2("2 - Ol� mundo disparado de main\n");
// Dispara fun��o usando async usando std::launch::deferred
auto a3 = async( launch::deferred, f2,"1 - Ol� mundo disparado usando async(launch::deferred,write_message,\n" );
a1.wait();  a2.wait(); a3.wait();  // Aguarda retorno de chamada a async.

std::future<int> resultado = std::async(processar1);
thread t (processar2);
std::cout << "The answer is "<< resultado.get() << std::endl; 
t.join();   
}
int find_the_answer() { throw std::runtime_error("Unable to find the answer");}
int main() {
 auto f =  async( find_the_answer ) ; 
 try {      cout << "the answer is "<< f.get() << "\n";     }
 catch( runtime_error const& e ) { cout << "\nCaught exception: " << e.what() << endl;}
return 0;
}
#include <condition_variable>
#include <mutex>
#include <chrono>
std::condition_variable cv;
bool done;
std::mutex m;
bool wait_loop(){
    auto const timeout= std::chrono::steady_clock::now()+
        std::chrono::milliseconds(500);
    std::unique_lock<std::mutex> lk(m);
    while(!done)    {
        if(cv.wait_until(lk,timeout)==std::cv_status::timeout)
            break;
    }
    return done;
}
std::cout   << "\n================THREADS PROMISE======================";
// Usando thread com future.
// AguardandoNotificacao � chamada duas vezes; e s� continua quando
// usu�rio pressiona enter, executando o cin.get() e a seguir set_value que libera sf.get().
#include <future> #include <thread> #include <iostream> #include <sstream>
using namespace std;
// Recebe id da thread e shared_future
void AguardandoNotificacao ( int id , std::shared_future<int> sf ) {
 ostringstream os;
 os << "Thread " << id <<" waiting\n";
 cout << os.str(); os.str("");           // Chama shared_future.get()
 os << "Thread " << id <<" woken, val=" << sf.get() << "\n";
 cout << os.str();
}
int main()  {
  std::promise<int> p;                  // Cria um promise
  auto sf = p.get_future().share(); 
  thread t1(AguardandoNotificacao, 1 ,sf);
  thread t2(AguardandoNotificacao, 2 ,sf);  
  cout << "Waiting\n"; cin.get();
  p.set_value(42);  
  t2.join(); t1.join();
  return 0;
}

===========================================================================
Lista com as principais novidades de C++14 -> N�cleo da linguagem
=========================================================================== 

--> extens�o das possibilidades das fun��es lambda, por exemplo com o uso de auto.
auto lambda = [](auto x, auto y) {return x + y;}; //C++14
auto lambda = [](int x, int y) {return x + y;}; //c++20

--> dedu��o de retorno
[=]() -> int { return foo() * 42; } // ok
[=] { return foo() * 42; } // ok, deduces "-> some_type"

--> melhoria no uso de decltype
string look_up_a_string_1() { return lookup1(); } //c++20
string& look_up_a_string_2() { return lookup2(); }//c++20
decltype(auto) look_up_a_string_1() { return lookup1(); }//C++14
decltype(auto) look_up_a_string_2() { return lookup2(); }//C++14

--> extens�o do uso de constexpr que agora suportam o uso de if, switch, e de loops (incluindo range-based for loops).

--> uso de auto para determinar o tipo de retorno de uma fun��o: 
auto Pi() { return 3.1415 };

--> uso de variable templates.

--> uso do atributo [[deprecated]].

--> uso de literais bin�rios
auto a1 = 42; // ... decimal
auto a2 = 0x2A; // ... hexadecimal
auto a3 = 0b101010; // ... binary

===========================================================================
Lista com as principais novidades de C++14 -> Biblioteca std
=========================================================================== 
--> uso de literais definidos pelo usu�rio para tipos de biblioteca padr�o (user-defined literals for standard library types).

--> Facilita uso de std::string
string s = string("c++20 n�o permite ")
          + string(" somar diretamente strings"); 
using namespace std::string_literals; 
string s = "C++14 permite, "s 
          + " basta informar que � uma string adicionando s"s; 

--> Facilita uso de chrono
using namespace std::literals::chrono_literals;
auto duration = 1h + 2min + 3s + 4ms + 5us + 6ns;

--> uso de sequ�ncias de inteiros determinados em tempo de compila��o. 

--> uso de std::make_unique - substitiu new.
std::unique_ptr<ClasseX> v = std::make_unique<ClasseX>();
std::unique_ptr<ClasseX> v = std::make_unique<ClasseX>(p1,p2,p3);

--> uso de ' para facilitar a leitura de n�meros.
double x = 123'456'789;

===========================================================================
Lista com as principais novidades de C++17 -> N�cleo da linguagem
=========================================================================== 

--> uso de assert sem texto.

--> uso de typename em templates e n�o class.

--> uso de namespace X::Y { ? } no lugar de namespace X { namespace Y { ? )).

--> uso de atributos em namespaces e enumera��es.

--> uso de unicializa��o em if e switch.
 if(inicializa��o, condi��o) {...} 
 if(int x=4; x+j<4) {...j--...}

--> uso de if constexpr(expression).
 funciona como static-if para o C++. Reduz uso de SFINAE.
 if constexpr (is_floating_point_v<T>) {}

--> uso de dedu��o de tipo em construtores permitindo std::pair(5.0, false) no lugar de std::pair<double,bool>(5.0, false).

--> uso de vari�veis inline, permitindo defini��es de vari�veis em arquivos de cabe�alho

--> fold expression, forma compacta para variadic template
 template<typename... Args>
 auto Soma(Args... args) { return args + ...; }

--> expecifica��o de exce��es passam a ser parte do tipo da fun��o;

--> fun��es lambda declaradas dentro de m�todos membro capturam automaticamente this;
  a captura de *this cria uma c�pia do objeto.

--> agora constexpr pode ser usada com lambda
 constexpr auto N = [] (int n) { return n;} 
 static_assert ( N(5) == 5 );

--> adicionada vari�vel de pr�-processamento _has_include

--> uso facilitado de tuplas
 auto [a,b,c] = notasJoao; // C++17 notasJoao � uma tupla

--> atributos/vari�veis inline 
 class X { static inline const double pi = 3.1415; };

--> static_assert sem mensagem;

--> u8 characteres literal

--> hexadecimal floating point decimal

--> nova especifica��o para construtor de heran�a

--> atributos:
 [[nodiscard]] Informa se o retorno da fun��o foi desconsiderado!
 [[maybe_unused]] compilador desconsidera se n�o for usado

--> Deprecated:
  Uso de register foi descontinuado;
  Removidos os trigraphs;
  Removido operador operator++(bool);
  Removidos auto_ptr, random_shufle e outros.
  
===========================================================================
Lista com as principais novidades de C++17 -> Biblioteca std 
=========================================================================== 
--> Adi�ao da biblioteca std::filesystem baseada em boost::filesystem.

--> uso de fun��es matem�tica especiais - Mathematical Special Functions.
 bessel, laguerre, hermite, neumann, beta

--> uso de std::string_view, uma vers�o leve e r�pida de string (somente leitura).

--> uso de std::optional, para representar objetos opcionais.

--> uso de std::any, para manter valores �nicos de qualquer tipofor holding single values of any type.

--> uso de std::variant, um cont�iner de uni�o marcadoa tagged union container.

--> uso de vers�es paralelizadas dos containers da STL (mais desempenho).

--> uso de std::byte.

--> Remo��o de conceitos ultrapassados como std::auto_ptr, std::random_shuffle, e vers�es de adaptadores de fun��o.

--> uso de Logical operator traits: std::conjunction, std::disjunction and std::negation.

--> std::uncaught_exceptions, as a replacement of std::uncaught_exception

--> New insertion functions try_emplace and insert_or_assign for std::map and std::unordered_map 

--> Uniform container access: std::size, std::empty and std::data

--> Definition of "contiguous iterators"

===========================================================================
Lista com as principais novidades de C++17 -> Biblioteca filesystem (C++17)
=========================================================================== 
// Resumo dos comandos da biblioteca filesystem.
// Para compilar: g++ -std=c++17 filesystem-00-resumo.cpp -o resumo -lstdc++fs
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

int main() {
auto p = fs::current_path();
std::cout   << "\n================Informa��es da path======================"
            << "\nPath completa: " << p 
            << "\nNote que o Caminho corrente pode ser decomposto nas seguintes partes:"
            << "\nroot_name()="       << p.root_name()     
            << "\nroot_directory()="  << p.root_directory()
            << "\nroot_path()="       << p.root_path()     
            << "\nroot_path().string() =" << p.root_path().string() 
            << "\nparent_path()="     << p.parent_path()   
            << "\nfileName()="        << p.fileName()      
            << "\nextension()="       << p.extension();
            //<< "\nnative_file_string()      =" << p.native_file_string()
            //<< "\nnative_directory_string() =" << p.native_directory_string()
            //<< "\nrelative_path().string()  =" << p.relative_path().string() 
            //<< "\nbranch_path().string()    =" << p.branch_path().string()<< endl;
std::cout   << "\nis_block_file (device)     = " << is_block_file(p)
            << "\nis_character_file (device) = " << is_character_file(p)
            << "\nis_directory               = " << is_directory(p)
            << "\nis_fifo                    = " << is_fifo(p)
            << "\nis_other                   = " << is_other(p)
            << "\nis_regular_file            = " << is_regular_file(p)
            << "\nis_socket                  = " << is_socket(p)
            << "\nis_symlink                 = " << is_symlink    (p)
            << "\nis_empty                   = "  << fs::is_empty(p)         
            << "\nexists                     = "  << fs::exists(p);    
    // Tamb�m posso criar uma path, um caminho para um arquivo
    fs::path p1 = "/tmp/teste/imagens/img1.pgm";
    ofstream img1(p1);                          // Cria arquivo
    string spgm = "p4 \n2 2 4\n1 2\n3 4\n" ;    // Cria string com conte�do arquivo processado
    img1 << spgm;                               // Substitui conte�do do arquivo
    img1.close();                               // Fecha o arquivo antes de mudar seu nome
cin.get();    
    // Arquivo com . no nome
    fs::path p2 = "/tmp/teste/imagens/img1.processada.pbm";
    // Caso em que o arquivo tem . s� tem extens�o (arquivo oculto no GNU/Linux)
    fs::path p3 = "/tmp/teste/imagens/.arquivoOcultoNoLinux";
std::cout   << "\n================DISCO======================";   
    // Informa��es de espa�o em disco
    fs::space_info home = fs::space("/home");
    cout  <<"\nDiret�rio" << "Capacidade"     << "Livre"     <<  "Dispon�vel\n"
         << setw(20) << "/home: " << setw(20) << home.capacity << setw(20) 
         << home.free << setw(20) << " " << home.available  << '\n';
std::cout   << "\n================DIRET�RIOS======================";
    // Criando um diret�rio e tentando copiar
    fs::path dir1 = "/tmp/teste/imagens";
    fs::path dir2 = "/tmp/teste/imagens.backup";
    fs::create_directory("/tmp/teste/");
    fs::create_directory("/tmp/teste/imagens");
    try {
        fs::copy_file(p1, "/tmp/teste/imagens/img1.pbm");
    } catch(fs::filesystem_error& e) {
        cout << "\nN�o deu para copiar o arquivo /tmp/teste/imagens/img1.pgm: " << e.what() << '\n';
    }
    try { fs::copy(dir1, dir2);                       // C�pia sem recurs�o e com recurs�o
          fs::copy("/tmp/teste/imagens", 
                 "/tmp/teste/imagens.backup2", fs::copy_options::recursive);
    } catch(fs::filesystem_error& e) {
        std::cout << "N�o deu para copiar o diret�rio: " << e.what() << '\n';    }        
    //fs::remove_all("/tmp/teste"); // Removendo diret�rio        
    // Iterando pelo diret�rio
    cout << "\nVai iterar n�o recursivamente pelo diret�rio e mostrar as paths :";
    for(auto& arq: fs::directory_iterator("/tmp/teste"))  // Itera pelo diret�rio
        cout << arq << '\n';                         // e mostra path dos arquivos
    // Iterando recursivamente pelo diret�rio
    cout << "\nVai iterar recursivamente pelo diret�rio e mostrar as paths :";
    for(auto& arq: fs::recursive_directory_iterator("/tmp/teste")) // Itera recursivamente
        cout << arq << '\n';                        // e mostra arquivos

std::cout   << "\n================ARQUIVOS======================";
    // Cria��o e manipula��o de arquivos
    cout << "\nConte�do do arquivo: \n" << ifstream(p1).rdbuf() << '\n';
    auto p4 = p1;
    p4.replace_fileName("img1_processada");      // Substitui nome da path
    p4.replace_extension(".pbm");                // Substitui extens�o da path
    p4 +=".backup";
    fs::copy(p1,p4);                             // C�pia de arquivos
    
std::cout   << "\n================LINKS======================";
    cout << "\n\nVai criar links:";              // Criando links
    fs::create_hard_link("/tmp/teste/imagens/img1.pbm", "/tmp/teste/imagens/hard_link_img1.pbm");
    fs::path p5 = "/tmp/teste/imagens/hard_link_img1.pbm";// hard link simb�lico
    fs::create_symlink("/tmp/teste/imagens/img1.pbm", "teste/imagens/symlink_img1.pbm");
    fs::path p6 = "/tmp/teste/imagens/symlink_img1.pbm"; // link simb�lico
    fs::create_directory_symlink("/tmp/teste/imagens/","symlink_imagens");
    fs::path p7 = "symlink_imagens";             // link simb�lico diret�rio
    system("tree /tmp/teste");
  std::cout << "Os caminhos para p1 e p2 s�o equivalentes? " 
            << equivalent(p1,p2) << endl;
  std::cout << "O tamanho do p1 � de " <<  file_size(p1) << "bytes" << endl;
  auto ftime = fs::last_write_time(p1);
  //std::cout << "A ultima escrita no p1 ocorreu �s =" << ftime  << endl; //C++20 verificar
  rename( p1,  "/tmp//teste/arquivoRenomeado.pbm" );
  std::cout << "O arquivo p1 foi renomeado para arquivoRenomeado.pbm." << endl;
  remove( p1 );   std::cout << "O arquivo p1 foi removido." << endl;
  fs::remove_all("/tmp/teste"); // Removendo diret�rio
return 0;}

// [ ] ---------------------------------------------------------------------> header cstring
Defined in header <cstring>
void* memset( void* dest, int ch, std::size_t count );
memset( ponteiroVetor, 0, vetorSize * sizeof(tipo) );

===========================================================================
Lista com as principais novidades de C++20 -> N�cleo da linguagem
=========================================================================== 
--> adi��o de concepts ou conceitos, expandindo as possibilidades de uso dos templates.

--> adi��o de modules simplificando e melhorando a velocidade da compila��o.

--> adi��o de coroutines 
 co_await para suspender a execu��o at� retomar.
 co_yield para suspender a execu��o retornando um valor.
 co_return para completar a execu��o retornando um valor.

--> uso de std::format semelhante a prinft.
 cout << std::format("{} {}!", "Hello", "world", "algo mais");
 https://en.cppreference.com/w/cpp/utility/format

--> uso de [=, this] para capturar this.

--> uso de constinit, inicializa��o na compila��o.
 const char* FS() { return "retorna cstring 1"; }
 constexpr const char *F(bool b) { return b ? "retorna cstring 2" : FS(); }
 constinit const char *c = F(true);

--> Designated initializers[70] (based on the C99 feature, and common G++ extension)

--> template parameter lists on lambdas[72]

--> three-way comparison using the "spaceship operator", operator <=>

--> initialization of an additional variable within a range-based for statement[73]

--> lambdas in unevaluated contexts[74][75]

--> default constructible and assignable stateless lambdas[74][76]

--> allow pack expansions in lambda init-capture[74][77]

--> string literals as template parameters[74][78]

--> removing the need for typename in certain circumstances[79]

--> new standard attributes [[no_unique_address]],[80] [[likely]] and [[unlikely]][81]

--> conditional explicit, allowing the explicit modifier to be contingent on a boolean expression[82]

--> expanded constexpr: virtual functions,[83] union,[84] try and catch,[85] dynamic_cast and typeid,[86] std::pointer_traits[87]

--> immediate functions using the new consteval keyword[88]

--> signed integers are now defined to be represented using two's complement (signed integer overflow remains undefined behavior)[89]

--> a revised memory model[90]

--> various improvements to structured bindings (interaction with lambda captures, static and thread_local storage duration)[91][92]

--> using on scoped enums[94]

===========================================================================
Lista com as principais novidades de C++20 -> Biblioteca
=========================================================================== 
--> ranges (The One Ranges Proposal)[96]

--> std::make_shared and std::allocate_shared for arrays[97]

--> atomic smart pointers (such as std::atomic<shared_ptr<T>> and std::atomic<weak_ptr<T>>)[98]

--> std::to_address to convert a pointer to a raw pointer[99]

--> calendar and time-zone additions to <chrono>[100]

--> std::span, providing a view to a contiguous array (analogous to std::string_view but span can mutate the referenced sequence)[101]

--> std::erase and std::erase_if, simplifying element erasure for most standard containers[102]

--> <version> header[103]

--> std::bit_cast<> for type casting of object representations, with less verbosity than memcpy() and more ability to exploit compiler internals[104]

--> feature test macros[105]

--> various constexpr library bits[106]

--> smart pointer creation with default initialization[107]

--> std::map::contains method[108]

--> bit operations, such as leading/trailing zero/one count,[109] and log2 operations[110][111][112]

--> std::bind_front[113]

--> Attributes in C++20: 
    [[likely]], 
    [[unlikely]], 
    [[no_unique_address]]

============================================================================
Dicas performance:
============================================================================
- Na sa�da para cout tente montar toda a sa�da e somente depois redirecione, evite diversas chamadas ao operator<<.
Ex:
    std::cout  << "\n\nBot�o Help:\n\tAjuda do aplicativo.\
                   \n\nBot�o Selecionar Material:\
                   \n\t vai plotar todas as curvas de condutividade\n";
- S� use  << std::endl; quando absolutamente necess�rio.

============================================================================
Dicas estilo de c�digo (c�digo limpo)
============================================================================
- Na hora que esta escrevendo a classe pode usar nomes abreviados e, antes de iniciar os testes, converter para nomes padr�es usando search-replace. Mas isso apenas para objetos que ter�o nomes grandes.

- Nome classe CNomeClasse, ex: class CFuncao; class CFDarcy: public CFuncao;
- Nome objeto CFFuncao funcao2G; CFDarcy functionDarcy
- Nome dos m�todos devem indicar a��o (verbos); 
ex: funcao->Salvar(fileName); funcao->Ler(fileName);
ex: funcao->SalvarDisco(fileName); funcao->LerDadosDisco(fileName);
ex: funcao2G->Read(fileName); funcao2G->Write(fileName);
ex: functionDarcy->Read(fileName); function_darcy->Plot(grafico);
Note que a codifica��o fica clara, auto explicativa.
Havendo necessidade pode-se colocar alguns coment�rios, mas a ideia � que ao usar nomes claros quase tudo fique autoexplicativo.
- Na medida do poss�vel o nome do objeto deve dar uma indica��o do nome da classe base da hierarquia a que pertence.
