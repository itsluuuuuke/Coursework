#include<iostream>
using namespace std;

int main()
{
	int a, b, i, j = 0, max, D1;
	int lcm, gcd;
	cout << "Please enter two integer for testing lcm and gcd: " << endl;
	cin >> a >> b;
	if(a>=b)
		max = a;
	else
		max = b;
	int *Multiple1 = new int[a*b];
	int *Multiple2 = new int[a*b];
	int *Divisor1 = new int[a/2];
	int *Divisor2 = new int[b/2];

//  Generate Multiples of a
	for(i = 1; i <= b; i++)
		Multiple1[i-1] = a*i;
// Generate Multiples of b
	for(i = 1; i <= a; i++)
		Multiple2[i-1] = b*i;

	i = 0;
//Compare and find the least common multiple
	while(1){
		if(Multiple1[i] == Multiple2[j]){
			lcm = Multiple1[i];
			break;
		}
		else if(Multiple1[i] < Multiple2[j])
			i++;
		else
			j++;
	}
// Generate divisors for a
	j = -1;
	for(i = 1; i <= a; i++){
		if(a%i == 0)
			Divisor1[++j] = i;
	}
	D1 = j - 1;
// Generate divisors for b
	j = -1;
	for(i = 1; i <= b; i++){
		if(b%i == 0)
			Divisor2[++j] = i;
	}
// Compare and get the greatest common divisor
	while(1){
		if(Divisor1[D1] == Divisor2[j]){
			gcd = Divisor1[D1];
			break;
		}
		else if(Divisor1[D1] < Divisor2[j])
			j--;
		else
			D1--;
	}
	delete Multiple1;
	delete Multiple2;
	delete Divisor1;
	delete Divisor2;
	cout << "The least common multiple is: " << lcm << endl;
	cout << "The greatest common divisor is: "<< gcd << endl;
	return 0;
}
