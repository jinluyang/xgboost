#include<stdlib.h>
#include<iostream>
#include<sstream>

#include<string>
#include<fstream>
//using namespace std;
std::string num2str(int i)
{
        std::stringstream ss;
        ss<<i;
        return ss.str();
}

std::string convert_txt_libsvm(std::string usrstr){
        std::string fnin = usrstr;
        std::string fnout = usrstr+".libsvm";
        std::ifstream fin(fnin.c_str());
        std::ofstream fout(fnout.c_str());
        std::string temps;
	while(getline(fin,temps)){
		int i = temps.find(9)+1, pre = temps.find(9)+1, cnt = 0;				
                std::string line = "";
		for(;;i++){
			if(temps.c_str()[i]==9){//tab
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
        return fnout;
}

//int main(){
//	convert_txt_libsvm("test");
//	return 0;
//}
//


