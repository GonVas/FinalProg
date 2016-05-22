#pragma once

#include <iostream>
#include <string>
#include <map>
#include<algorithm>


#include "defs.h"
#include "Date.h"
#include "Cliente.h"
#include "Transacao.h"
#include "Produto.h"
#include "utils.h"


using namespace std;

class VendeMaisMais{
 private:
  string loja; // nome da loja
  string fichClientes, fichProdutos, fichTransacoes; // nome dos
						     // ficheiros de
						     // clientes,
						     // produtos e
						     // transacoes
  bool transacoesAlterdas; // flag que fica a true se for preciso guardar no final as transacoes
  bool clientesAlterados; // flag que fica a true se for preciso guardar no final os clientes
  unsigned int maxClientesId; // variavel que guarda o identificador unico do cliente com o maior numero de identificacao
  vector<Cliente> clientes; // vetor que guarda a informacao dos clientes existentes
  vector<Produto> produtos; // vetor que guarda a informacao dos produtos disponiveis
  vector<Transacao> transacoes; // vetor que guarda a informacao das ttransacoes efetuadas
  map<string, int> clienteIdx;  // map para "traduzir" nome do cliente no  correspondente  indice no vetor de clientes
  map<string, int> produtoIdx;  // map para "traduzir" nome do produto no correspondente indice no vetor de produtos
  multimap<int, int> transacaoIdx; // multimap para "traduzir" o identificador do cliente nos indices das suas
				   // transacoes no vetor de transacoes
  vector <int> bottom10posinclients;
  bool bottom10;
  

 public:
  VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes);
  void listarClientesOrdemAlfa() const;
  void listarProdutos() const;
  bool mostraInformacaoCliente(string nome);
  void saveChanges() const;

  void LoadClientsFromFile(string & filename);
  void LoadTransFromFile(ifstream & file);
  void LoadTransFromFile(string & filename);
  void LoadProdFromFile(string & filename);
  void makeClientMap();
  void MakeTransMap();
  void makeProdMap();
  int findsmaxid();
  void editclient(string nome);
  void newclient(string nome);
  void removeClient(string nome);
  void listransactions();
  void singleclientTrans(string name);
  void transday(Date date1) const;
  void transinterval(Date date1, Date date2) const;
  void createtrans(string name, Date date1, vector <string> prods);
  void showbottom();
  void recommendfor(string name);
  bool clienthasproduct(string name, string prod);
  void recommendbottom10();
  bool findnormalclient(vector <int> bottom10, string name);
  bool doesprodexist(string prodname);

  friend ostream& operator<<(ostream& out, const VendeMaisMais & supermercado);
};
