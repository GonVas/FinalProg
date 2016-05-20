#include "Produto.h"


Produto::Produto(ifstream & in){ // nome ; custo
  // A IMPLEMENTAR
}

string Produto::getNome() const {
  return nome;
}

float Produto::getCusto() const {
  return custo;
}

ostream& operator<<(ostream& out, const Produto & prod){

	out << "Name: " << prod.getNome() << ";" << " Cost: " << prod.getCusto() << endl;
	return out;

}

Produto::Produto(string nome, float custo)
{
	this->nome = nome;
	this->custo = custo;
}

bool operator<(const Produto &prod1, const Produto &prod2){
  // A IMPLEMENTAR
	return true;
}
