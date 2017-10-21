#include<iostream>
#include<cstring>
#include<ctype.h>
#define MAX_LENGTH 100
using namespace std;


double power(double m, int n = 2){
	if(n == 0)
		return 1;
	cout << "Now in DoubleBase Power" << endl;
	int i;
	double result = m;
	for(i = 1; i < n; i++)
	result *= m;
	return result;
}

double power(int m, int n = 2){
	if(n == 0)
		return 1;
	cout << "Now in IntBase Power" << endl;
	int i;
	double result = m;
	for(i = 1; i < n; i++)
		result *= m;
	return result;
}

void Convert(char *str1, char *str2, int &n)
{
	int i, j = 0;
	cout << "Input length = " << strlen(str1) << endl;
	for(i = 0; i < strlen(str1); i++){
		if(!isdigit(str1[i]))
			str2[j++] = str1[i];
	}
	cout << "str2 = : " << str2 << endl;
	cout << "Output length(inside convert): " << strlen(str2) << endl;
	n = strlen(str2);	
}

int main()
{
	int intBase, pow, len;
	double doubleBase;
	double result1, result2;
	char InStr[MAX_LENGTH];
	char OutStr[MAX_LENGTH];

	cout << "Double base test: " << endl;
	cin >> doubleBase >> pow;
	result1 = power(doubleBase, pow);
	cout << "result1 = " << result1 << endl;

	cout << "int base test: " << endl;
	cin >> intBase >> pow;
	result2 = power(intBase, pow);
	cout << "result2 = " << result2 << endl;
	
	cout << "Default :" << endl;
	result1 = power(doubleBase);
	cout << "result1 = " << result1 << endl << endl;
	
	cout << "Convert Test" << endl;
	cin >> InStr;
	Convert(InStr,OutStr,len);
	cout << "len in Main function: " << len << endl;
}
