#include "Vende++.h"
#include <string>
#include <set>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <algorithm>    
#include <iterator>

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
	bottom10 = false;
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
	string name;

	for (int i = 0; i < (this->clientes).size(); i++)
		{
			alphabetic.insert((this->clientes)[i].getNome());
		}

	clearScreen();
	cout << setw(15) << "Name" << setw(35) << "Date" << setw(22) << "Value " << endl;
	cout << endl;
	for (set<string>::const_iterator it = alphabetic.begin();
		it != alphabetic.end(); ++it)
	{
		name = *it;
		float value = this->clientes[this->clienteIdx.at(name)].getVolCompras();
		cout << setw(25) << name << setw(20) << this->clientes[this->clienteIdx.at(name)].getDate() << setw(20) << value << endl;
	}

	cout << endl;
	
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

void VendeMaisMais::createtrans(string name, Date date1, vector <string> prods)
{
	int pos = this->clienteIdx.at(name);
	int id = this->clientes[pos].getId();
	Transacao newtrans(id, date1, prods);
	(this->transacoes).push_back(newtrans);
	for (int i = 0; i < prods.size(); i++)
	{
		this->clientes[pos].addmoney(this->produtos[this->produtoIdx.at(prods[i])].getCusto());
	}
	MakeTransMap();
}

struct value_pos
{
	int pos;
	float value;
};

bool VendeMaisMais::doesprodexist(string prodname)
{
	
	for (int i = 0; i < this->produtos.size(); i++)
	{
		if (this->produtos[i].getNome() == prodname)
			return true;
	}
	return false;
}

bool valuesortfunc(const value_pos s1, const value_pos s2) { return (  (s1.value)  <    (s2.value)  ); }

void VendeMaisMais::showbottom()
{
	vector <value_pos> vec_vi;
	vector <int> bottom10posinclients;

	for (int i = 0; i < this->clientes.size(); i++)
	{
		value_pos newone;
		newone.pos = i;
		newone.value = (this->clientes)[i].getVolCompras();
		vec_vi.push_back(newone);
	}

	sort(vec_vi.begin(), vec_vi.end(), valuesortfunc);

	//cout << "Bottom 10: " << endl;
	int size = 10;
	if (vec_vi.size() < 10)
		size = vec_vi.size();
	for (int i = 0; i < size; i++)
	{
		cout << (this->clientes)[(vec_vi[i].pos)];
		bottom10posinclients.push_back((vec_vi[i].pos));
	}
	this->bottom10posinclients = bottom10posinclients;
	bottom10 = true;
}

bool VendeMaisMais::clienthasproduct(string name, string prod)
{
	int id;
	int timesran = 0;
	vector <string> clientsprods;

	//cout << "ran with name : " << name << endl;
	id = (this->clientes)[this->clienteIdx[name]].getId();
	if ((this->transacaoIdx).count(id) == 0)
		return false;
	pair <multimap<int, int>::iterator, multimap<int, int>::iterator> ret;
	ret = (this->transacaoIdx).equal_range(id);
	for (multimap<int, int>::iterator it = ret.first; it != ret.second; ++it)
	{
		vector <string> transvecprod = transacoes.at(it->second).getProds();

		for (int i = 0; i < transvecprod.size(); i++)
		{
			if (!(find(clientsprods.begin(), clientsprods.end(), transvecprod[i]) != clientsprods.end()))
				clientsprods.push_back(transvecprod[i]);
			//else
				//cout << "client " << name << " has: " << prod << endl;

			
		}

	}
	
	return (find(clientsprods.begin(), clientsprods.end(), prod) != clientsprods.end() );
}

struct idlinepos
{
	int line;
	int same;
	vector <string> npros;
};

struct commonstruct
{
	vector < vector <string>> pos_strings;
	int common;
};

struct prod_times
{
	int times;
	string name;
};

struct less_than_key
{
	inline bool operator() (const prod_times& struct1, const prod_times& struct2)
	{
		return (struct1.times > struct2.times);
	}
};



struct okclients
{
	int id;
	int score;
	string name;
};

struct less_than_score
{
	inline bool operator() (const okclients& struct1, const okclients& struct2)
	{
		return (struct1.score > struct2.score);
	}
};

struct clientis
{
	inline bool operator() (const okclients& struct1, const Cliente& cliente1)
	{
		return (struct1.name == cliente1.getNome());
	}
};

vector <string> intersection(vector <string> v1, vector <string> v2)
{
	vector <string> inter;
	vector<string>::iterator it;

	/*if (v1.size() < v2.size())
	{
		v1.resize(v2.size());
		inter.resize(v2.size());
	}
	else
	{
		if (v1.size() > v2.size())
		{
			v2.resize(v1.size());
			inter.resize(v2.size());
		}
	}

	sort(v1.begin(), v1.begin() + v1.size());
	sort(v2.begin(), v2.begin() + v1.size());


	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(inter));*/



	return inter;

}

struct stringtimes
{
	string prodname;
	int times;
};

struct less_than_key1
{
	inline bool operator() (const stringtimes& struct1, const stringtimes& struct2)
	{
		return (struct1.times > struct2.times);
	}
};

int foundinvec(string prod, vector <stringtimes> res)
{
	int bres = -1;
	for (int i = 0; i < res.size(); i++)
	{
		if (res[i].prodname == prod)
			bres = i;
	}
	return bres;
}

void counttimes(vector <string> v1, vector <stringtimes>  &res)
{
	string prod;

	/*if (v1.size() < res.size())
	{
		v1.resize(res.size());
	}
	else
	{
		if (v1.size() > res.size())
		{
			res.resize(v1.size());
		}
	}*/

	for (int i = 0; i < v1.size(); i++)
	{
		int found = (foundinvec(v1.at(i), res));
		if(found != -1)
			res.at(found).times = res.at(found).times + 1;
		else
		{
			stringtimes newstringtimes;
			newstringtimes.prodname = v1.at(i);
			newstringtimes.times = 1;
			res.push_back(newstringtimes);
		}
	}
	return;
}

void VendeMaisMais::recommendfor(string name)
{
	vector <vector <bool>> matrix;
	map <int, int > idtoline;
	map <int, string> linetoname;
	map <int, string> mpostoprodname;


	matrix.resize(this->clientes.size());
	for (int i = 0; i < matrix.size(); i++)
		matrix[i].resize(this->produtos.size());


	for (int k = 0; k < matrix.size(); k++)
	{
		idtoline[this->clientes[k].getId()] = k;
		linetoname[k] = this->clientes[k].getNome();
		for (int j = 0; j < this->produtos.size(); j++)
		{
			mpostoprodname[j] = this->produtos[j].getNome();
			bool func = clienthasproduct(this->clientes[k].getNome(), this->produtos[j].getNome());
			//cout << "whith name : " << this->clientes[k].getNome() << " and prod : " << this->produtos[j].getNome() << " is :" << func << endl;
			if (func)
			{
				matrix[k][j] = 1;
			}
			else
			{
				matrix[k][j] = 0;
			}
		}
	}

	/*cout << "Matrix: " << endl << endl;

	for (int i = 0; i < (matrix.size()); i++)
	{
		for (int l = 0; l < this->produtos.size(); l++)
		{
			cout << "->" << (matrix[i])[l] << " ";
		}
		cout << endl;
	}*/

	int targetclientid = (this->clientes)[this->clienteIdx[name]].getId();
	int targetclientline = idtoline.at(targetclientid);

	bool allzeros = true;
	for (int i = 0; i < this->produtos.size(); i++)
	{
		if (matrix[targetclientline][i] !=0)
		{allzeros = false;
			break;
		}
	}

	if (allzeros)
	{
		cout << "Client hasn't bought anything ." << endl;
		return;
	}

	

	int biggest = 0 ;
	vector <idlinepos> structsvec;


	for (int i = 0; i < (this->clientes.size()); i++)
	{

		if (i != targetclientline)
		{
			idlinepos newidposline;
			vector <string> temp;
			newidposline.line = i;
			newidposline.same = 0;
			for (int j = 0; j < this->produtos.size(); j++)
			{
				if (matrix[i][j] == matrix[targetclientline][j] && !(matrix[i][j] == 0))
				{
					newidposline.same = newidposline.same + 1;
					temp.push_back(this->produtos[j].getNome());
				}
			}
			for (int j = 0; j < this->produtos.size(); j++)
			{
				if (!(find(temp.begin(), temp.end(), mpostoprodname.at(j)) != temp.end()) && clienthasproduct(linetoname.at(i), mpostoprodname.at(j)) )
					(newidposline.npros).push_back(mpostoprodname.at(j));
			}
			structsvec.push_back(newidposline);
		}
	}

	bool nothing = true;

	for (int i = 0; i < structsvec.size(); i++)
	{
		if (structsvec[i].npros.size() != 0)
		{
			nothing = false;
			break;
		}
	}

	if (nothing)
	{
		cout << "Could not reccomnend anything :( ." << endl;
		return;
	}

	for (int i = 0; i < structsvec.size(); i++)
	{
		if(structsvec[i].same > biggest)
		{
			biggest = structsvec[i].same;
		}

	}

	//vector <commonstruct> commonvec;

	commonstruct common1;
	common1.common = 0;

	for (int i = 0; i < structsvec.size(); i++)
	{
		if (structsvec[i].same == biggest)
		{
			common1.pos_strings.push_back(structsvec[i].npros);
			common1.common = common1.common + 1;
		}
	}

	vector <stringtimes> interesult;
	//interesult.resize(common1.pos_strings.size());

	if (common1.common == 1)
	{
		cout << " Client should buy: " << common1.pos_strings[0][0] << endl;
		return;
	}
	else
	{
		for (int i = 0; i < ((common1.common) - 1); i++)
		{
			if (i == 0)
				counttimes(common1.pos_strings[0], interesult);
			else
				counttimes(common1.pos_strings[i+1], interesult);
		}
		if (interesult.size() == 0)
		{
			cout << " Client should buy: " << common1.pos_strings[0][0] << endl;
			return;
		}
		else
		{
			sort(interesult.begin(), interesult.end(), less_than_key1());
			cout << " Client should buy: " << interesult[0].prodname << endl;
			return;
		}
	}

	return;
}

bool VendeMaisMais::findnormalclient(vector <int> bottom10, string name)
{
	for (int i = 0; i < bottom10.size(); i++)
	{
		if (bottom10[i] == this->clienteIdx.at(name))
			return true;
	}
	return false;
}

void VendeMaisMais::recommendbottom10()
{
	vector <prod_times> vecprodtimes;

	this->showbottom();
	cout << endl;
	for (int i = 0; i < this->produtos.size(); i++)
	{
		prod_times prod_times1;
		prod_times1.times = 0;
		prod_times1.name = this->produtos[i].getNome();
		vecprodtimes.push_back(prod_times1);
	}

	for (int j = 0; j < vecprodtimes.size(); j++)
	{

		for (int i = 0; i < this->bottom10posinclients.size(); i++)
		{
			string clientname = this->clientes[bottom10posinclients[i]].getNome();
			string prodname = vecprodtimes[j].name;
			bool haprodct = clienthasproduct(clientname, prodname);
			if (haprodct)
			{
				vecprodtimes[j].times = vecprodtimes[j].times + 1;
			}
		}

	}
	std::sort(vecprodtimes.begin(), vecprodtimes.end(), less_than_key());

	vector <okclients> notbottom10inclientes;
	for (int i = 0; i < this->clientes.size(); i++)
	{
		bool exists = findnormalclient(bottom10posinclients, this->clientes[i].getNome());
		if (!exists)
		{
			okclients newokclient;
			newokclient.id = i;
			newokclient.name = this->clientes[i].getNome();
			newokclient.score = 0;
			notbottom10inclientes.push_back(newokclient);
		}
	}

	if (notbottom10inclientes.size() == 0)
	{
		cout << "There are less than 10 clients . " << endl;
		cout << "They should buy: " << vecprodtimes[vecprodtimes.size() - 1].name;
		return;
	}
	for (int j = 0; j < notbottom10inclientes.size(); j++)
	{
		for (int i = 0; i < vecprodtimes.size(); i++)
		{
			if (clienthasproduct(notbottom10inclientes[j].name, vecprodtimes[i].name))
			{
				notbottom10inclientes[j].score = vecprodtimes.size() - i + notbottom10inclientes[j].score;
			}
		}

	}


	std::sort(notbottom10inclientes.begin(), notbottom10inclientes.end(), less_than_score());

	for (int i = vecprodtimes.size() - 1; i > -1; i--)
	{
		if (clienthasproduct( notbottom10inclientes[0].name, vecprodtimes[i].name))
		{
			cout << "The product recommended is: " << vecprodtimes[i].name << endl;
			return;
		}


	}
	cout << "Something bad has happened " << endl;

	return;

		
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
