#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Date.h"



using namespace std;


class Transacao {
 private:
  unsigned int idCliente;
  Date data; // na forma DD/MM/AAAAA
  vector<string> produtos;

 public:
  //Transacao(ifstream & in); // transacao na forma de  idCliente ; data ; lista de produtos
  unsigned int getIdCliente() const;
  void save(ofstream & out) const; // guarda a transacao
  friend ostream& operator<<(ostream& out, const Transacao & trans); // mostra a transacao

  Transacao(unsigned int id, Date data, vector<string> produtos);
  Date getDate() const;
  vector <string> getProds() const;
};



