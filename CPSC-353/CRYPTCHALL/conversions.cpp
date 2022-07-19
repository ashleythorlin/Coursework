#include <iostream>
#include <string>

int main()
{
	unsigned int decimalNum = 0;
	string hexa;
	int size;
	int temp = 0;

	cout << " enter hexadecimal value  " << endl;
	cin >> hexa;
	reverse(hexa.begin(), hexa.end()); //TAKE IT FROM LEFT TO RIGHT 

	size = hexa.size();
	
		for (int i = 0 ; i <  size; i++){

			if (hexa[i] >= '0' && hexa[i] <= '9'){

				temp = hexa[i] - 48; // it keeps iteraring from 48 - 57 in the ascii code 
				decimalNum = decimalNum + temp * pow(16, i);

			}
				
			else if (hexa[i] >= 'A' && hexa[i] <= 'Z'){

				temp = hexa[i] - 55; // why it didnt work with the number 65 in ascii code although its the beginning of the A-Z ?
				decimalNum = decimalNum + temp * pow(16, i);
			}	// so when starts for example AB, then hexa[i] equal 65 in decimal in ascii table  65 - 55 = 10
				// then decimal = 10 * 16^1 = 160. For B, its 66 in ascii table in decimal, then 66 - 55 = 11 * 16^0 = 11
				// then decimal = 160 + 11 = 171 
			
		}
		cout << decimalNum << endl;

	system("pause");
	return 0;
}