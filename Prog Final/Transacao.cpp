#include "Transacao.h"



unsigned int Transacao::getIdCliente() const{
  return this->idCliente;
}

Date Transacao::getDate() const
{
	return this->data;
}

Transacao::Transacao(unsigned int id, Date data, vector<string> produtos)
{
	this->idCliente = id;
	this->data = data;
	this->produtos = produtos;
}
//Transacao::Transacao(ifstream & in){ // le uma transacao na forma de  idcliente ; data ; lista produtos
  // A IMPLEMENTAR
//}

void Transacao::save(ofstream & out) const{ // transacao guardada como na forma de  idcliente ; data ; lista produtos
  // A IMPLEMENTAR
}

vector <string> Transacao::getProds() const
{
	return this->produtos;
}


ostream& operator<<(ostream& out, const Transacao & trans){
	out << trans.getIdCliente() << "; " << trans.getDate() << "; ";
	for (int i = 0; i < trans.produtos.size(); i++)
	{
		if (i == (trans.produtos.size() - 1) )
			out << trans.produtos[i] << endl;
		else
			out << trans.produtos[i] << ", ";
	}

	return out;
}
