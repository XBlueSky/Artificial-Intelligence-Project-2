#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;


int main(){
	
	char* testdata[] = {"adult","car","isolet","page-blocks","winequality"};
	vector<string> text;
	char buffer[8787],s[10];
	int k,num=0;
	cout<<"Input k-fold = ";
	cin>>k;
		
	//get .name content by loop
	for(int i=0;i<5;i++){
		//write names
		for(int j=1;j<(k+1);j++){
			sprintf(s, "%d", j);
			string ss(s);
			string str(testdata[i]);
			FILE *pFile_n= fopen( (str+".names").c_str(), "r" );
			FILE *wFile_n= fopen( (str+"_cv"+ss+".names").c_str(), "w" );
			while(fgets(buffer,8787,pFile_n)!=NULL){	
				fputs(buffer, wFile_n);	
			}
			fclose(wFile_n);
			fclose(pFile_n);
		}
	}
	
	//get .data content by loop
	for(int i=0;i<5;i++){
		//write names
		int start=0;

		for(int j=1;j<(k+1);j++){
			num=0;
			sprintf(s, "%d", j);
			string ss(s);
			string str(testdata[i]);
			FILE *pFile_n= fopen( (str+".data").c_str(), "r" );
			while(fgets(buffer,8787,pFile_n)!=NULL){	
				text.push_back(buffer);
				num++;	
			}
			FILE *wFile_n= fopen( (str+"_cv"+ss+".data").c_str(), "w" );
			FILE *wFile_t= fopen( (str+"_cv"+ss+".test").c_str(), "w" );

			start = j-1;
			for(int q=start;q<num;q=(q+k)){
				fputs(text[q].c_str(), wFile_t);
			}
			for(int q=start;q<num;q=(q+k)){
				text.erase(text.begin()+q);		
			}	
			cout<<text.size()<<endl;
			for(int q=0;q<text.size();q++){
				fputs(text[q].c_str(), wFile_n);		
			}	
					
			fclose(wFile_t);
			fclose(wFile_n);
			fclose(pFile_n);
			text.clear();
		}
	}
	
	return 0;

} 
