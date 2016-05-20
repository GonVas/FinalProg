#include "Vende++.h"
#include <string>
#include <set>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <algorithm>    

void VendeMaisMais::LoadClientsFromFile(string & filename)
{
	string client, garbage;
	ifstream file(filename);
	getline(file, garbage);
	//cout << garbage << endl;
	
	while (getline(file, client))
	{
		Cliente newcliente(client);
		(this->clientes).push_back(newcliente);
	}

	this->clientesAlterados = true;

}

void VendeMaisMais::LoadTransFromFile(string & filename)
{
	string s_num, fullTrans, onlyprods, tempfind;
	string s_prod, singleprod;
	vector <string> prods;
	int prodpos;
	int i = 1;
	int clientid;

	ifstream file_Trans(filename);
	getline(file_Trans, s_num);

	for (int j = 0; j < (stoi(s_num)) ; j++)
	{
		getline(file_Trans, fullTrans);
		prodpos = fullTrans.find(';');
		tempfind = fullTrans.substr(prodpos);
		prodpos = 1 + tempfind.find(';');   //prodpos is the position where the products start
		tempfind = tempfind.substr(prodpos);
		prodpos = 1 + tempfind.find(';');
		onlyprods = tempfind.substr(prodpos); // onlyprods now equals to the portion of the products in the a line of the transaction file

		while (extract_from_string(i, onlyprods, ',', true) != "OVER") //see the documentation of extract_from_string in utils.cpp for more info
		{
			singleprod = extract_from_string(i, onlyprods, ',', true); //this will extract a single product
			prods.push_back(singleprod);
			i++;
		}
		clientid = stoi(extract_from_string(1, fullTrans, ';', 1));
		Transacao newTrans(clientid, Date(extract_from_string(2, fullTrans, ';', 1)), prods);
		prods.clear(); //need to reset the prods for another iteration
		transacoes.push_back(newTrans);
		i = 1;
	}

}

void VendeMaisMais::LoadProdFromFile(string & filename)
{
	string s_num, fullProduct;
	//string s_prod, s_value;

	ifstream file_Prod(filename);
	getline(file_Prod, s_num);

	for (int j = 0; j < stoi(s_num); j++)
	{
		getline(file_Prod, fullProduct);
		Produto newproduct(extract_from_string(1, fullProduct, ';', 1), stof(extract_from_string(2, fullProduct, ';', 1)));
		this->produtos.push_back(newproduct);
	}
	cout << " ";
}


VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes)
{
	this->loja = loja;
	//=========================Client====================================
	LoadClientsFromFile(fichClients);
	//cout << (this->clientes).size() << endl;
	this->makeClientMap();
	//=========================Client====================================
	//=======================Transaction=================================
	LoadTransFromFile(fichTransacoes);
	//cout << "Numero de transacoes: " <<(this->transacoes).size() << endl;
	MakeTransMap();
	//=======================Transaction=================================
	//=========================Product===================================
	LoadProdFromFile(fichProdutos);
	makeProdMap();
	//=========================Product===================================
	transacoesAlterdas = false;
	clientesAlterados = false;
	//=========================Product===================================
	findsmaxid();
}

void VendeMaisMais::makeClientMap()
{
	pair <string, int> newpair;
	for (int i = 0; i < ((this->clientes).size()); i++)
	{
		this->clienteIdx[(this->clientes)[i].getNome()] = i;
	}

	/*for (map<string, int >::const_iterator it = (this->clienteIdx).begin();
		it != (this->clienteIdx).end(); ++it)
		{
		cout << it->first << " " << it->second << "\n";
		}*/

}

void VendeMaisMais::MakeTransMap()
{

	for (int i = 0; i < ((this->transacoes).size()); i++)
	{
		this->transacaoIdx.insert(pair<int, int>((this->transacoes)[i].getIdCliente(), i));
	}
	
}

void VendeMaisMais::makeProdMap()
{
	pair <string, int> newpair;
	for (int i = 0; i < ((this->produtos).size()); i++)
	{
		this->produtoIdx[(this->produtos)[i].getNome()] = i;
	}
}

int VendeMaisMais::findsmaxid()
{
	int maxid = (this->clientes)[0].getId();
	for (int i = 0; i < (this->clientes).size(); i++)
	{
		if (maxid < (this->clientes)[i].getId())
			maxid = (this->clientes)[i].getId();
	}
	this->maxClientesId = maxid;
	return maxid;
}

/*********************************
 * Gestao de Clientes
 ********************************/

// lista os cleinets por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa() const
{
	set <string> alphabetic;

	for (int i = 0; i < (this->clientes).size(); i++)
		{
			alphabetic.insert((this->clientes)[i].getNome());
		}

	cout << setw(20) << "     Name" << "Date " << setw(20) << "Value  " << endl;

	for (set<string>::const_iterator it = alphabetic.begin();
		it != alphabetic.end(); ++it)
	{
		cout << setw(20) << *it << endl;
	}

	
}

// mostra a informacao individual de um cliente
bool VendeMaisMais::mostraInformacaoCliente(string nome)
{
	map<string, int>::iterator it;

	it = (this->clienteIdx).find(nome);
	if (it == (this->clienteIdx).end())
		return false;
	cout << "Informacao cliente: " << endl;
	cout << this->clientes[it->second];
	return true;

}

void VendeMaisMais::editclient(string nome)
{
	float newvalue;
	cout << "What is the new value? ";
	cin >> newvalue;
	this->clientes[this->clienteIdx[nome]].setValue(newvalue);

}

void VendeMaisMais::newclient(string nome)
{
	float value;
	int newid = this->findsmaxid() + 1;
	userinput("What is the new value? ", value, 0, 100000.0);
	Cliente newclient1(newid, nome, value);
	(this->clientes).push_back(newclient1);
	makeClientMap();

}

void VendeMaisMais::removeClient(string nome)
{
	this->clientes.erase(this->clientes.begin() + this->clienteIdx[nome]);
	makeClientMap();
	cout << "RIP" << endl;
}

/*********************************
 * Gestao de Produtos
 ********************************/  

// lisat os produto por ordem alfabetica crescente
void VendeMaisMais::listarProdutos() const{
	
	cout << "Products avaiable: " << endl;

	for (int i = 0; i < (this->produtos).size(); i++)
	{
		cout << (this->produtos)[i];
	}

}

void VendeMaisMais::listransactions()
{
	cout << endl;
	for (int i = 0; i < (this->transacoes).size(); i++)
	{
		cout << (this->transacoes)[i] << endl;;
	}
}

void VendeMaisMais::singleclientTrans(string name)
{
	int id;
	 
		cout << endl;
		id = (this->clientes)[this->clienteIdx[name]].getId();
		pair <multimap<int, int>::iterator, multimap<int, int>::iterator> ret;
		ret = (this->transacaoIdx).equal_range(id);
		for (multimap<int, int>::iterator it = ret.first; it != ret.second; ++it)
		{
			cout << transacoes.at(it->second);
		}

}

void VendeMaisMais::transday(Date date1) const
{
	cout << endl;
	for (int i = 0; i < (this->transacoes).size(); i++)
	{
		Date date2 = ((this->transacoes)[i]).getDate();
		if (date2 == date1)
			cout << ((this->transacoes).at(i));

	}
}

void VendeMaisMais::transinterval(Date date1, Date date2) const
{
	for (int i = 0; i < (this->transacoes).size(); i++)
	{
		if ((((this->transacoes).at(i)).getDate() >= date1) && !(((this->transacoes).at(i)).getDate() > date2))
		{
			cout << ((this->transacoes).at(i));
		}
	}
}

void VendeMaisMais::createtrans(int id, Date date1, vector <string> prods)
{
	Transacao newtrans(id, date1, prods);
	(this->transacoes).push_back(newtrans);
	MakeTransMap();
}

struct value_pos
{
	int pos;
	float value;
};

bool valuesortfunc(const value_pos s1, const value_pos s2) { return (  (s1.value)  <    (s2.value)  ); }

void VendeMaisMais::showbottom()
{
	vector <value_pos> vec_vi;

	for (int i = 0; i < this->clientes.size(); i++)
	{
		value_pos newone;
		newone.pos = i;
		newone.value = (this->clientes)[i].getVolCompras();
		vec_vi.push_back(newone);
	}

	sort(vec_vi.begin(), vec_vi.end(), valuesortfunc);

	//cout << "Bottom 10: " << endl;
	for (int i = 0; i < vec_vi.size(); i++)
	{
		cout << (this->clientes)[(vec_vi[i].pos)];
	}

}

void VendeMaisMais::recommendfor(string name)
{
	vector <vector <bool>> matrix;


	matrix.resize(this->clientes.size());
	for (int i = 0; i < matrix.size(); i++)
		matrix[i].resize(this->produtos.size());


	for (int k = 0; k < matrix.size(); k++)
	{
		for (int j = 0; j < this->produtos.size(); j++)
		{
			if (find(this->clientes.begin(), this->clientes.end(), this->produtos[j]) != this->clientes.end())
			{
				matrix[k][j] = 1;
			}
			else
			{
				matrix[k][j] = 0;
			}
		}
	}

	cout << "Matrix: " << endl << endl;

	for (int i = 0; i < (matrix.size()); i++)
	{
		for (int l = 0; l < this->produtos.size(); l++)
		{
			cout << "->" << (matrix[i])[l] << " ";
		}
		cout << endl;
	}

}


/*********************************
 * Preservar Informacao
 ********************************/  

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada
void VendeMaisMais::saveChanges() const{

  // A IMPLEMENTAR 

}

/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma loja
ostream& operator<<(ostream& out, const VendeMaisMais & supermercado){

  // A IMPLEMENTAR 
	return out;
}
