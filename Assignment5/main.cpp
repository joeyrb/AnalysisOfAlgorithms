#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <limits>
#include <math.h>
#include <cmath>
using namespace std;

float MAX_FLOAT = numeric_limits<float>().max();


int GCD(int a, int b) {
	if (b == 0)
		return a;
	else{
		return GCD(b, a%b);
	}
}

// Find d
int GCD_ext(int a, int b, int &x, int &y) {
	if (b == 0){
		x = 1;
		y = 0;
		return a;
	}

	else {
		int x1, y1, gcd = GCD_ext(b, a%b, x1, y1);
		x = y1;
		y = x1 - floor(a/b)*y1;
		return gcd;
	}
}

int modAdd(int a, int b, int n) {
	return((a+b)%n);
}

int modMult(int a, int b, int n) {
	return((a*b)%n);
}

// Source: 
// https://stackoverflow.com/questions/2177781/how-to-calculate-modulus-of-large-numbers
int mod(int base, unsigned int exp, unsigned int mod) {
    int x = 1;
    int power = base % mod;

    for (int i = 0; i < sizeof(int) * 8; i++) {
        int least_sig_bit = 0x00000001 & (exp >> i);
        if (least_sig_bit)
            x = (x * power) % mod;
        power = (power * power) % mod;
    }

    return x;
}

// Returns true if E is valid, false otherwise
bool valid_E(int p, int q, int e){
	bool result = false;
	int n = (p-1)*(q-1);
	if(n%e != 0 || (p*q) % e == 1)
		result = true;
	else
		result = false;
	return result;
}

int* convertInput(int argc, char const *argv[]){
	int *nums = new int[3];
	for (int i = 1; i < 4; ++i)
	{
		nums[i-1] = atoi(argv[i]);
	}
	return nums;
}

vector<int> getKey(vector<int> M, int v, int n) {
	vector<int> key;
	for (int i = 0; i < M.size(); ++i)
	{
		key.push_back(mod(M.at(i), v, n));
	}
	return key;
}

// P(M)
vector<int> getPublicKey(vector<int> M, int e, int n) {
	return getKey(M, e, n);
}

// S(C)
vector<int> getSecretKey(vector<int> M, int d, int n) {
	return getKey(M, d, n);
}

// M
// convert text to ASCII int and build return message
vector<int> getMessage(int argc, char const *argv[]) {
	string m(argv[4]);
	int ascii;
	vector<int> msg;
	for (int i = 0; i < m.length(); ++i)
	{
		ascii = m[i];
		msg.push_back(ascii);
	}
	return msg;
}

// Prints necessary values for finding P() and S()
void printVals(int p, int q, int e, int d, int n){
	printf("\np:%d | q:%d | e:%d | d:%d | n:%d\n\n", p,q,e,d,n);
}

// Prints the elements of the key
void printKey(vector<int> k) {
	for (int i = 0; i < k.size(); ++i)
	{
		printf("%d ", k[i]);
	}
	cout << endl;
}

void printMsgStr(vector<int> msg) {
	cout << "Message: ";
	char alph;
	for (int i = 0; i < msg.size(); ++i)
	{
		alph = msg.at(i);
		cout << alph;
	} cout << endl;
}



/***************************************************************************************
** TODO: 
		* check range for e value compared to the message (n should be greater than all
			ASCII values)
		* print letters and numbers correctly (right now the numbers are printing as chars)
***************************************************************************************/
int main(int argc, char const *argv[]) {
	vector<int> Msg;

	// Check for correct usage, return if false
	if (argc < 4) {
		cout << "Usage: rsa.exe p q e my_text num1 num2 num3 ..." << endl;
		return -1;
	}

	// Check for message text
	if (argc > 4) {
		Msg = getMessage(argc, argv);
	} else {
		Msg.push_back(2);
		Msg.push_back(5);
		Msg.push_back(6);
	}
	cout << "Msg: " << endl; printKey(Msg);
	

	int *nums = convertInput(argc, argv);		// Array of p, q, & e from input
	int p = nums[0], q = nums[1], e = nums[2];	// Assign input to variables
	delete nums;								// Deallocate unused space
	
	int x, y;
	int n = p*q;
	int t = (p-1)*(q-1);
	int d = 0;

	// Check if e is a valid choice and exit program if false
	if(!valid_E(p, q, e)) {
		cout << "E is invalid" << endl;
		return -2;
	}
	else {
		d = GCD_ext(e, t, x, y);
		while(e*x < 0) x += t;
	}
	
	printVals(p,q,e,x,n);

	vector<int> C;					// cypher text
	C = getPublicKey(Msg, e, n);
	printf("Public Key: ");
	printKey(C);
	vector<int> M;
	M = getSecretKey(C, x, n);
	printf("Secret Key: ");
	printKey(M);
	
	printMsgStr(M);
	cout << endl;
	return 0;
}
/***************************************************************************************/
/***************************************************************************************/