#include "Cliente.h"
#include <sstream>


Cliente::Cliente(string s_file)
{
	string info;
	stringstream stream;
	stream.str(s_file);

	getline(stream, info, ';');
	//cout << info << endl;
	this->id = stoi(info);
	getline(stream, info, ';');
	remove_thing_fromstring(info, ' ', true);
	this->nome = info;
	getline(stream, info, ';');
	Date newdate(info);
	this->cartaoCliente = newdate;
	getline(stream, info, ';');
	this->volCompras = stof(info);

}

Cliente::Cliente(unsigned int id, string nome, float value)
{
	this->id = id;
	this->nome = nome;
	this->volCompras = value;
}


string Cliente::getNome() const{
  return nome;
}

unsigned int Cliente::getId() const{
  return id;
}

float Cliente::getVolCompras() const{
  return volCompras;
}

void Cliente::save(ofstream & out) const{

  // A IMPLEMENTAR

}

void Cliente::setValue(float newvalue)
{
	this->volCompras = newvalue;
}

ostream& operator<<(ostream& out, const Cliente & cli){
	out << "ID: " << cli.getId() << "  Name: " << cli.getNome() << "  Money: " << cli.getVolCompras() << endl;
	return out;
}


bool operator<(const Cliente &cli1, const Cliente &cli2){
  // A IMPLEMENTAR
	return true;
}
