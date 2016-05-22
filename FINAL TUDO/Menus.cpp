#include "Menus.h"

inline void fileopening(ifstream & file, string & filename)  //Simple inline function that is gonna open a file
{
	getline(cin, filename);

	file.open(filename);

	while (!(file.good()))      //while it cant open file, send a error message and try again
	{
		cout << "Could not find file, try again. \n";
		getline(cin, filename);
		file.open(filename);
	}

}

bool infoInicial(string & loja, string & fichClientes, string & fichProdutos, string & fichTransacoes){

	cout << "What is the name of the store. \n";
	getline(cin, loja);

	cout << "Where is the Client file? \n";
	ifstream cl_file;
	fileopening(cl_file, fichClientes);

	cout << "Where is the Products file? \n";
	ifstream pro_file;
	fileopening(pro_file, fichProdutos);

	cout << "Where is the Transactions file? \n";
	ifstream tran_file;
	fileopening(tran_file, fichTransacoes);

	return true;
}

/******************************************
 * Gestao de Clientes
 ******************************************/
unsigned short int menuGestaoClientes(){
	unsigned short int opcao;

	//clearScreen();
	cout << TAB_BIG << "Menu Gestao Clientes" << endl;
	cout << endl;
	cout << TAB << "1 - Listar clientes" << endl;
	cout << TAB << "2 - Ver informacao cliente" << endl;
	cout << TAB << "3 - Editar cliente" << endl;
	cout << TAB << "4 - Remover cliente" << endl;
	cout << TAB << "5 - Adicionar cliente" << endl;
	cout << TAB << "6 - Voltar ao menu inicial" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	userinput("", opcao, 1, 6);

	if (opcao == 6)
		return 0;

	return opcao;
}



void opcoesGestaoClientes(VendeMaisMais & supermercado){
  unsigned int opcao;
  string nome;
  char entao;

  while((opcao = menuGestaoClientes()))
    switch (opcao){
	case 1: supermercado.listarClientesOrdemAlfa();
		//cin >> entao;
      break;
    case 2: cout << "Qual o nome do cliente: ";
      getline(cin, nome);
	  while (!(supermercado.mostraInformacaoCliente(nome)))
	  {
		  cout << "That client doesn't exist, try again .(CTRL+Z to quit)" << endl;
		  getline(cin, nome);
		  if (cin.eof())
		  {
			  cin.clear();
			  cin.ignore(1000, '\n');
			  break;
		  }
	  }    
	  cin >> entao;
      break;
	case 3: cout << "Client name?";
		getline(cin, nome);
		while (!(supermercado.mostraInformacaoCliente(nome)))
		{
			cout << "That client doesn't exist, try again .(CTRL+Z to quit)" << endl;
			getline(cin, nome);
			if (cin.eof())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}
		supermercado.editclient(nome);
      break;
	case 4: cout << "Client name?";
		getline(cin, nome);
		while (!(supermercado.mostraInformacaoCliente(nome)))
		{
			cout << "That client doesn't exist, try again .(CTRL+Z to quit)" << endl;
			getline(cin, nome);
			if (cin.eof())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}
		supermercado.removeClient(nome);
		cout << "" << endl;
      break;
	case 5: cout << "Client name?";
		getline(cin, nome);
		supermercado.newclient(nome);
		break;
		cout << " " << endl;
    }
  
}

/******************************************
 * Gestao de Transacoes
 ******************************************/
unsigned short int menuGestaoTransacoes()
{
	unsigned short int opcao;

	clearScreen();
	cout << TAB_BIG << "Menu Transactions" << endl;
	cout << endl;
	cout << TAB << "1 - List Transactions" << endl;
	cout << TAB << "2 - See Transactions" << endl;
	cout << TAB << "3 - Edit Transaction" << endl;
	cout << TAB << "4 - Create Transaction" << endl;
	cout << TAB << "5 - Return to main menu" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	userinput("", opcao, 1, 5);

	if (opcao == 5)
		return 0;

	return opcao;
}

unsigned int menuseeTransactions()
{
	unsigned short int opcao;

	clearScreen();
	cout << TAB_BIG << "Sub Menu Transactions" << endl;
	cout << endl;
	cout << TAB << "1 - Single Client" << endl;
	cout << TAB << "2 - Single Day" << endl;
	cout << TAB << "3 - Between Dates" << endl;
	cout << TAB << "4 - Return to main menu" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	userinput(" ", opcao, 1, 4);

	if (opcao == 4)
		return 0;

	return opcao;
}

void subTransactions(VendeMaisMais & supermercado)
{
	unsigned short int opcao;
	string nome;

	string name;
	string date1, date2;
	Date newdate1;
	Date newdate2;
	Date newdate;

	char entao;

	while ((opcao = menuseeTransactions()))
	{
		switch (opcao)
		{
		case 1: cout << "Client name?";
			getline(cin, nome);
			while (!(supermercado.mostraInformacaoCliente(nome)))
		{
			cout << "That client doesn't exist, try again .(CTRL+Z to quit)" << endl;
			getline(cin, nome);
			if (cin.eof())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}
			cout << "Transactions: " << endl;
			supermercado.singleclientTrans(name);
			cin >> entao;
			break;

		case 2: cout << "What is the date (dd/mm/yyyy) ?";
			getline(cin, date1);
			newdate.setstringDate(date1);
			cout << "Transactions: " << endl;
			supermercado.transday(newdate);
			cin >> entao;
			break;
		case 3:
		{
			cout << "What is the first date (dd/mm/yyyy) ?";
			getline(cin, date1);
			newdate1.setstringDate(date1);
			cout << "What is the second date (dd/mm/yyyy) ?";
			getline(cin, date2);
			newdate2.setstringDate(date2);
			cout << "Transactions: " << endl;
			supermercado.transinterval(newdate1, newdate2);
			cin >> entao;
			break;
		}
		}
	}

}



void getstringvec(vector <string> & prods, VendeMaisMais & supermercado)
{
	//prods.erase();
	string prod;
	cout << "Type products name. (CTRL+Z to end) " << endl;
	while (getline(cin, prod))
	{
		if (supermercado.doesprodexist(prod))
			prods.push_back(prod);
		else
			cout << "Prod does not exist, try again" << endl;
	}
	
	cin.clear();
	cin.ignore(1000, '\n');
}

void opcoesGestaoTransacoes(VendeMaisMais & supermercado){
  unsigned short int opcao;
  string newdate, name;
  int id;
  vector <string> prods;
 

  while((opcao = menuGestaoTransacoes()))
    switch (opcao){
	case 1: cout << "Transactions: " << endl;
		supermercado.listransactions();
      break;
	case 2: subTransactions(supermercado);
      break;
	case 3: 
      break; 
	case 4: cout << "Client name?";
			getline(cin, name);
			while (!(supermercado.mostraInformacaoCliente(name)))
		{
			cout << "That client doesn't exist, try again .(CTRL+Z to quit)" << endl;
			getline(cin, name);
			if (cin.eof())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}
			cout << "What is the date? " << endl;
			getline(cin, newdate);
			Date date1(newdate);
			getstringvec(prods, supermercado);
			supermercado.createtrans(name, date1, prods);
			cin >> id;

      break;
    }
}

/******************************************
 * Gestao de Transacoes
 ******************************************/
unsigned short int menuRecomendacao()
{
	unsigned short int opcao;

	clearScreen();
	cout << TAB_BIG << "Sub Menu Transactions" << endl;
	cout << endl;
	cout << TAB << "1 - Show Bottom 10" << endl;
	cout << TAB << "2 - Recommendation for single client" << endl;
	cout << TAB << "3 - Recommendation for Bottom 10" << endl;
	cout << TAB << "4 - Return to main menu" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	userinput(" ", opcao, 1, 4);

	if (opcao == 4)
		return 0;

	return opcao;
}


void opcoesRecomendacao(VendeMaisMais & supermercado){
	unsigned int opcao;
	int id;

	string name;

	while ((opcao = menuRecomendacao()))
		switch (opcao){
		case 1: cout << "Bottom 10: " << endl;
			supermercado.showbottom();
			cin >> id;
			break;
		case 2: cout << "What is the client name?";
			getline(cin, name);
			supermercado.recommendfor(name);
			char c;
			cin >> c;
			break;
		case 3: 
			supermercado.recommendbottom10();
			char d;
			cin >> d;
			break;
		case 4:
			break;
	}

}

/******************************************
 * Menu Inicial
 ******************************************/
unsigned short int menuInicial(){
  unsigned short int opcao;

  clearScreen();
  cout << TAB_BIG << "Menu Inicial" << endl;
  cout << endl;
  cout << TAB << "1 - Gestao de clientes" << endl;
  cout << TAB << "2 - Lista produto disponiveis" << endl;
  cout << TAB << "3 - Gestao de transacoes" << endl;
  cout << TAB << "4 - Recomendacoes" << endl;
  cout << TAB << "5 - Sair do programa" << endl << endl;
  cout << TAB << "Qual a sua opcao: ";
  userinput("",opcao,1, 5);

  if(opcao == 5)
    return 0;

  return opcao;
}

void opcoesIniciais(VendeMaisMais & supermercado){
  unsigned int opcao;
  char entao;

  while((opcao = menuInicial()))
    switch (opcao){
    case 1: opcoesGestaoClientes(supermercado);
      break;
    case 2: supermercado.listarProdutos();
		cin >> entao;
      break;
    case 3: opcoesGestaoTransacoes(supermercado);
      break;
    case 4: opcoesRecomendacao(supermercado);
      break;
    }

  supermercado.saveChanges();
}
