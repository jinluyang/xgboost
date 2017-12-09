#include<stdlib.h>
#include<iostream>
#include<sstream>

#include<string>
#include<fstream>
using namespace std;
string num2str(int i)
{
        stringstream ss;
        ss<<i;
        return ss.str();
}

void convert_txt_libsvm(string usrstr){
	string fnin = usrstr+".txt";
	string fnout = usrstr+".libsvm";
	ifstream fin(fnin.c_str());
	ofstream fout(fnout.c_str());
	string temps;
	while(getline(fin,temps)){
		int i = temps.find(9)+1, pre = temps.find(9)+1, cnt = 0;				
		string line = "";
		for(;;i++){
			if(temps.c_str()[i]==9){
				line= line+" "+num2str(cnt)+":"+temps.substr(pre,i-pre);
				cnt++;
				pre = i+1;
			}
			if(i==temps.size()-1) break;
		}
		line = temps.substr(pre,i-pre)+" "+line;
		fout<<line.c_str();
		fout<<"\r\n";
		cnt = 0;
	}
	fin.close();
	fout.close();
}

int main(){
	convert_txt_libsvm("test");
	return 0;
}



