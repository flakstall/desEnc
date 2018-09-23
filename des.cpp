#include <bits/stdc++.h>
#include <string>
using namespace std;

string rearrange(string s, int Arr[], int size) { //buat expand, sama permutasi
	int bc[size];
	for (int i=0; i<size; i++) {
		bc[i]=s[i];
	}
	
	
	for (int i=0; i<size; i++) {
		s[i]=bc[Arr[i]];
	}
}

string toBin(char s) {
	string biner="";
	int ascii=int(s);
	while(ascii!=0) {
		biner=(ascii%2==0 ?"0":"1")+biner; 
		ascii/=2;
	}
	int j=8-biner.length();
	for (int i=0;i<j;i++)
		biner="0"+biner;
		
	return biner;
}

int toDec(string s) {
	int n=0;
	int len=s.length();
	for (int i=0;i<len;i++) {
		if (s[i]==1)
			n+=pow(2,i);
	}
	return n;
}

string leftShift(string s) {
	int len = s.length()-1;
	char temp=s[len];
	for (int i=len; i>0; i--) {
		s[i]=s[i-1];
	}
	s[0]=temp;
	return s;
}

string leftSide(string s) {
	int len=s.length();
	len/=2;
	string left="";
	for (int i=0;i<len;i++)
		left+=s[i];
	return left;
}

string rightSide(string s) {
	int len=s.length();
	int awal = len/2;
	string right="";
	for (int i=awal;i<len;i++)
		right+=s[i];
	return right;
}

string genKey(string k, int i) {
	int nLeftShift[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	string left=leftSide(k);
	string right=rightSide(k);
	int pc2[48]={14,17,11,24,1,5,2,28,15,6,21,10,
			 23,19,12,4,26,8,16,7,27,20,13,2,
			 41,52,31,37,47,55,30,40,51,45,33,48,
			 44,49,39,56,34,53,46,42,50,36,29,32};
	
	for (int j=0;j<nLeftShift[i];j++) {
		left=leftShift(left);
		right=leftShift(right);		
	}
	k=left+right;
	k=rearrange(k,pc2,48);
	return k;
	
}

string orx(string a, string b) {
	string tempXor="";
	for (int i=0;i<48;i++)
		tempXor+=a[i]^b[i];
	return tempXor;
}

string sBox(string s) {
	int s1[4][16]={{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7}, //[4][16]
			{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
			{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
			{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13},
			};
	string tempA="";
	string tempB="";
	for (int i=1;i<=8;i++) {
		int dvde =6*i;		
		for (int j=dvde-6;j<dvde;j++) {
			tempA+=s[j];
		}
		stringstream ss1,ss2,ss3,ss4;
		ss1<<tempA[1];
		ss2<<tempA[2];
		ss3<<tempA[3];
		ss4<<tempA[4];
//		string indX=tempA[1]+tempA[2]+tempA[3]+tempA[4];
		string indX=ss1.str()+ss2.str()+ss3.str()+ss4.str();
		stringstream ss0,ss5;
		ss0<<tempA[0];
		ss5<<tempA[5];
//		string indY=tempA[0]+tempA[5];
		string indY=ss0.str()+ss5.str();
		tempB+=s1[toDec(indY)][toDec(indX)];
	}
	return tempB;
}

string enc(string left, string right, string key, int i) {	
	string right0=right;
	if (i==17) {
		return left+right;
	} else {
		//plain right di expand dari 32 ke 48
		int expan[48]={32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,
				12,13,12,13,14,15,16,17,18,17,18,19,20,21,20,21,
				22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
		int pLast[32]={16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
				2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
		right=rearrange(right,expan,48);
		key=genKey(key,i);
		//permutasi key
		
		right=orx(right,key); // ini A
		right=sBox(right);
		//permutasi 32 jadi 32
		right=rearrange(right,pLast,32);
		right=orx(right,left);
		
		
		return enc(right0,right,key,i+1);
	}	
}

string binerSequen(string s) {
	string sequen="";
	for (int i=0;i<s.length();i++)
		sequen+=toBin(s[i]);
	return sequen;
}

int main() {
	string plain="#EOFIT#1";
	string key;
	int permutP[64]={58,50,42,34,26,18,10,2,
				  60,52,44,36,28,20,12,4,
				  62,54,46,38,30,22,14,6,
				  64,56,48,40,32,24,16,8,
				  57,49,41,33,25,17,9,1,
				  59,51,43,35,27,19,11,3,
				  61,53,45,37,29,21,13,5,
				  63,55,47,39,31,23,15,7};
	int permuChoice[56]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,
			10,2,59,51,43,35,27,19,11,3,60,52,44,36,
			63,55,47,35,31,23,15,7,62,54,47,38,30,22,
			14,6,61,53,45,3,29,21,15,5,28,20,12,4};
	int ipmin[64]={40,8,48,16,56,24,64,32,
			   39,7,47,15,55,23,63,31,
			   38,6,46,14,54,22,62,30,
			   37,5,45,13,53,21,61,29,
			   36,4,44,12,52,20,60,28,
			   35,3,43,11,51,19,59,27,
			   34,2,42,10,50,18,58,26,
			   33,1,41,9,49,17,57,25};
	//tabel-tabel lainnya
	
	cin >> plain;
	cin >> key;
	
	//diubah ke baris biner
	plain=binerSequen(plain);
	key=binerSequen(key);
	
	
	/////////////// permutasi key dari 64 jadi 56
	key=rearrange(key,permuChoice,56);
	
	//plain text
	//permutation plain 64 jadi 56
	plain=rearrange(plain,permutP,56);
	
	string left=leftSide(plain);
	string right=rightSide(plain);
	//panggil enc
	string cipher = enc(left,right,key,0);
	///////////////////////////////////////////////reverse + permutasi cipher
	cipher = rearrange(cipher,ipmin,64);
	cout << cipher << endl;
}



