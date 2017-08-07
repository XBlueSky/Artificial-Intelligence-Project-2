#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;



int main(){

	//char* testdata[] = {"adult","car","isolet","page-blocks","winequality"};
	string tedata;
	vector <string> text,cate,test,data_row;
	vector <double> pro;
	vector <double> count;
	vector < vector <string> > data;
	vector <int> continuous;
	char buffer[8787],s[10];
	double k,num=0.0,total=0.0,acc=0.0;
	double prob,acc_f;
	cout<<"Input k-fold = ";
	cin>>k;
	cout<<"Input testdata = ";
	cin>>tedata;

		
	//get .name content by loop
	//for(int g=0;g<5;g++){
		//write names
		for(int j=1;j<(k+1);j++){
			int t = 0;
			sprintf(s, "%d", j);
			string ss(s);
			//string str(testdata[g]);
			FILE *pFile_n= fopen( (tedata+"_cv"+ss+".names").c_str(), "r" );
			//FILE *pFile_n= fopen( ("page-blocks_cv"+ss+".names").c_str(), "r" );
			fgets(buffer,8787,pFile_n);
			char *p = strtok(buffer," ,.\n");
			while (p != NULL)
			{
				cate.push_back(p);
			    p = strtok (NULL," ,.\n");
			}    
			//for(int i=0; i<cate.size(); i++) cout << cate[i] << " ";
			
			while(fgets(buffer,8787,pFile_n)!=NULL){
				if(buffer[strlen(buffer)-2]=='.'){
					//text.push_back(buffer);
					char *p = strtok(buffer,"\n");
					while (p != NULL)
					{
						text.push_back(p);
						continuous.push_back(0);
					    p = strtok (NULL,"\n");
					} 
				}			
			}
			
			for(int i=0; i<text.size(); i++) {
				if(text[i].find("continuous",0)!=-1){
					continuous[i] = 1;		
				}
				//cout << text[i] <<" : "<<text[i].find("vhigh",0)<<endl;	
			}
			FILE *pFile_d= fopen( (tedata+"_cv"+ss+".data").c_str(), "r" );
			//FILE *pFile_d= fopen( ("page-blocks_cv"+ss+".data").c_str(), "r" );
			while(fgets(buffer,8787,pFile_d)!=NULL){
				char *p = strtok(buffer," ,\n");
				while (p != NULL)
				{
					data_row.push_back(p);
				    p = strtok (NULL," ,\n");
				} 
				data.push_back(data_row);
				data_row.clear();	
			} 
			
			 /*vector<double> row;
			 vector< vector<double> > con;
			 con.assign(text.size(),row);//°t¸m2ºû*/
			
			vector <double> con[text.size()];
			
			for(int i=0;i<data.size();i++){
				for(int j=0;j<data[i].size();j++){
					if(continuous[j] == 1){
						con[j].push_back(strtod((data[i][j]).c_str(),NULL));
					}
				} 
			}

			double sum = 0.0,max,min,SD = 0.0;
			for(int i=0;i<text.size();i++){
				if(continuous[i] == 1){
					//max = *std::max_element(con[i].begin(), con[i].end());
					//min = *std::min_element(con[i].begin(), con[i].end());
					for(int j=0;j<con[i].size();j++){
						sum += con[i][j];		
					} 
					sum = sum/con[i].size();
					for(int j=0;j<con[i].size();j++){
						
						SD = SD + (con[i][j]-sum)*(con[i][j]-sum);
					} 

					SD = sqrtl(SD/con[i].size());
					con[i].clear();
					//cout<<sum<<" : "<<SD<<endl;
					con[i].push_back(sum+2*SD);
					con[i].push_back(sum+SD);
					con[i].push_back(sum);
					con[i].push_back(sum-SD);
					con[i].push_back(sum-2*SD);
				}
			}

			for(int i=0;i<data.size();i++){
				for(int j=0;j<data[i].size();j++){
					if(continuous[j] == 1){
						if(strtod((data[i][j]).c_str(),NULL)>(con[j][0])) data[i][j] = "A";
						else if(strtod((data[i][j]).c_str(),NULL)>(con[j][1])) data[i][j] = "B";
						else if(strtod((data[i][j]).c_str(),NULL)>(con[j][2])) data[i][j] = "C";
						else if(strtod((data[i][j]).c_str(),NULL)>(con[j][3])) data[i][j] = "D";
						else if(strtod((data[i][j]).c_str(),NULL)>(con[j][4])) data[i][j] = "E";
						else data[i][j] = "F";
						//t++;
					}
				} 
			}
			/*for(int i=0;i<data.size();i++){
				for(int j=0;j<data[i].size();j++){
					cout<<data[i][j]<<" ";
				}
				cout<<endl;
			}*/ 
			//cout<<text.size()<<" : "<<t<<endl;

			
			FILE *pFile_t= fopen( (tedata+"_cv"+ss+".test").c_str(), "r" );
			//FILE *pFile_t= fopen( ("page-blocks_cv"+ss+".test").c_str(), "r" );
			total = 0.0;
			acc = 0.0;
			while(fgets(buffer,8787,pFile_t)!=NULL){
				double count_s=0.0; 
				total++;
				char *p = strtok(buffer," ,\n");
				while (p != NULL)
				{
					test.push_back(p);
				    p = strtok (NULL," ,\n");
				} 
				for(int j=0;j<test.size();j++){
					if(continuous[j] == 1){
						if(strtod((test[j]).c_str(),NULL)>(con[j][0])) test[j] = "A";
						else if(strtod((test[j]).c_str(),NULL)>(con[j][1])) test[j] = "B";
						else if(strtod((test[j]).c_str(),NULL)>(con[j][2])) test[j] = "C";
						else if(strtod((test[j]).c_str(),NULL)>(con[j][3])) test[j] = "D";
						else if(strtod((test[j]).c_str(),NULL)>(con[j][4])) test[j] = "E";
						else test[j] = "F";
						//t++;
					}
				} 
				
				for(int i=0;i<cate.size();i++){
					for(int a=0;a<test.size()-1;a++)
						count.push_back(0);
					count_s=0.0;
					for(int ix=0;ix<data.size();ix++){
						string cat(cate[i]);
						string data_back(data[ix].back());
						if(cat==data_back){
							count_s++;
							for(int j=0;j<(data[ix].size()-2);j++){
							string tes(test[j]);
							string data_bac(data[ix][j]);								
								if(tes==data_bac){
									count[j]++;
								}
							}	
						}
					} 
					double p,k;
					k = data.size();
					prob = count_s/k;
					for(int i=0;i<count.size();i++){
						if(count[i]==0.0){
							p = (count[i]+1.0)/(count_s+2.0);
						}
						else{
							p = count[i]/count_s;
						}
						prob = prob*p;

					}
					pro.push_back(prob);
					count.clear();
				}
				double max = 0.0;
				double max_i;
				for(int i=0;i<pro.size();i++){
					if(pro[i]>max){
						max = pro[i];
						max_i = i;
					}
				}
				if(cate[max_i]==test.back()) acc++;
				pro.clear();
				test.clear();	
			} 
			data.clear();
			cate.clear();
			fclose(pFile_n);
			fclose(pFile_d);
			fclose(pFile_t);
			cout<<acc<<" : "<<total<<endl;
			acc_f = acc/total;
			cout<<ss<<" : "<<acc_f<<endl;
			
			for(int i=0;i<text.size();i++){
				con[i].clear();
			}
			continuous.clear();
			text.clear();	
		}
		//cout<<"\n";
	//}
	

	return 0;
} 


