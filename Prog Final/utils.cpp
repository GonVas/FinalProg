#include "utils.h"
#include <string>
#include <sstream>


void clearScreen(){

	if (system("CLS")) system("clear");
	
}


unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int  max){

  // A IMPLEMENTAR
	return 1;
}


int leInteiro(int min, int max){

  // A IMPLEMENTAR
	return true;
}





void remove_thing_fromstring(string & input, char thing, bool dont_erase_middle)
//This function allows for a string to be cleaned, simply put the string , the char that you want to remove, and also if
// you want to remove that char from between text, example:
// string ex = " ola  ergerg "; remove_thing_fromstring(ex, ' ', true) cahnges it to -> "ola  ergerg"
// remove_thing_fromstring(ex, ' ', false) cahnges it to -> "olaergerg"
// WARNING, for some reason if it start with two or more spaces at the begingin it wont remove them
{
	string temps;

	//cout << input << "." <<endl;

	if (dont_erase_middle)
	{
		for (int i = 0; input[i] == thing && i < input.size(); i++)
		{
			if (input[i] == thing)
			{
				input.erase(input.begin() + i);
			}
		}

		for (int j = input.size() - 1; input[j] == thing && j > -1; j--)
		{
			if (input[j] == thing)
			{
				input.erase(input.begin() + j);
			}
		}
	}
	else
	{
		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] != thing)
			{
				temps += input[i];
			}
		}
		input = temps;
	}

	//cout << input << "." <<endl;
}

string extract_from_string(int iterator, string input, char delimiter, bool removespaces)
// This functions allows for parts between a char delimiter , example '/', to be extracted into another string, the bool removespaces
// removes the spaces in the ends of the each string if it is set to true, example:
// string ex: "bananas,vinho"; extract_from_string(0 , ex , ',' , 0) return -> bananas; extract_from_string(1 , ex , ',' , 0) returns -> vinho
// returns "OVER" when it kinda of ends, combine with loop for full effect example:
//=======================================================example==========================================================================
// int i;
// string things = " banana,cao  , gato  , pato, ola, como    esta";
//while( extract_from_string(i, things, ',', true) != "OVER" )
//    {

//        cout << i << " extractio: " << extract_from_string(i, things, ',', true) << endl;
//        i++;
//    }  this will return banana,cao,gato,pato,ola,como    esta// each in separated lines,
// if the removespace bool == true then it will return  banana,cao  ,gato  , pato, ola, como    esta// each in separeted lines
{
	stringstream buffer_s;
	string temp_s;
	int i = 0;

	buffer_s.str(input);

	while (i != iterator && getline(buffer_s, temp_s, delimiter))
	{
		i++;
	}

	if (i != iterator)
	{
		return "OVER";
	}
	else
	{
		if (removespaces)
		{
			remove_thing_fromstring(temp_s, ' ', true);
			return temp_s;
		}
		else
		{
			return temp_s;
		}
	}
}

void userinput(string text, int & a, int low, int high )
//Functions that handles user input with error handling, changes values permantely of variable a
{
	bool validOperands, anotherOperation;

	cout << text << endl;
	anotherOperation = true;

	do
	{
		cin >> a;
		validOperands = true;
		if (cin.fail())
		{
			validOperands = false;
			if (cin.eof()) // use cin.eof() only after cin.fail() returns TRUE
				anotherOperation = false; //ALTERNATIVE: return 1;
			else
			{
				cout << "Error please try again. \n";
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		else
		{
			cin.ignore(1000, '\n'); //clear any additional chars
			if (a > high || a < low)
			{
				validOperands = false;
				cout << "Number out of range. Try again." << endl;
			}

		}
	} while (anotherOperation && !validOperands);

}

void userinput(string text, unsigned short int & a, unsigned short int low, unsigned short int high)
//Functions that handles user input with error handling, changes values permantely of variable a
{
	bool validOperands, anotherOperation;

	cout << text << endl;
	anotherOperation = true;

	do
	{
		cin >> a;
		validOperands = true;
		if (cin.fail())
		{
			validOperands = false;
			if (cin.eof()) // use cin.eof() only after cin.fail() returns TRUE
				anotherOperation = false; //ALTERNATIVE: return 1;
			else
			{
				cout << "Error please try again. \n";
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		else
		{
			cin.ignore(1000, '\n'); //clear any additional chars
			if (a > high || a < low)
			{
				validOperands = false;
				cout << "Number out of range. Try again." << endl;
			}

		}
	} while (anotherOperation && !validOperands);

}

void userinput(string text, float & a, float low, float high)
//Functions that handles user input with error handling, changes values permantely of variable a
{
	bool validOperands, anotherOperation;

	cout << text << endl;
	anotherOperation = true;

	do
	{
		cin >> a;
		validOperands = true;
		if (cin.fail())
		{
			validOperands = false;
			if (cin.eof()) // use cin.eof() only after cin.fail() returns TRUE
				anotherOperation = false; //ALTERNATIVE: return 1;
			else
			{
				cout << "Error please try again. \n";
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		else
		{
			cin.ignore(1000, '\n'); //clear any additional chars
			if (a > high || a < low)
			{
				validOperands = false;
				cout << "Number out of range. Try again." << endl;
			}

		}
	} while (anotherOperation && !validOperands);

}