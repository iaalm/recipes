#include <stdio.h>
#include <stdlib.h>
#include<map>
#include<string>
#include<string.h>
#include<vector>
#include<iostream>
#include<fstream>
#include "m3n.h"
#include "svm.h"

using namespace std;
map<string,double> mm;
double getIndex(string& str){
	static double max = 0;
	double ret;
	if(ret = mm[str])
		return ret;
	mm[str] = ++max;
	return max;
}

int main(int argc, const char *argv[])
{
	if(argc < 3){
		printf("Usage: %s input result\n",argv[0]);
		return 1;
	}

	int i,end;
	int count = 0;
	double td;
	string str;
	vector<string> t;
	t.push_back("NN");
	t.push_back("NN");
	t.push_back("NN");
	vector<vector<string> > m3n_in,m3n_tag;
	vector<double> svm_in;
	vector<char> svm_tag; 
	ifstream fin(argv[1]);
	ifstream fdic("dic");
	ofstream fout(argv[2]);
	struct svm_node *svm_input;
	vector < double > sequencep;
	vector < vector < double > > nodep;
	//read dic
	while(!fdic.eof()){
		fdic >> str >> td;
		mm[str] = td;
	}
	fdic.close();
	//init svm
	struct svm_model* model=svm_load_model("svm.model");
	//init m3n
	M3N *m=new M3N();
	m->set_para("margin","0");
	m->set_para("nbest","1");
	m->load_model("m3n.model");

	while(!fin.eof()){
		printf("[CONTROL] processing %d line\n",++count);
		fin >> str;
		m3n_in.clear();
		svm_in.clear();
		svm_tag.clear();
		m3n_tag.clear();
		while(str[0] != '.'){
			t[0] = str;
			m3n_in.push_back(t);
			svm_in.push_back(getIndex(str));
			fin >> str;
		}
		end = m3n_in.size();
		svm_input = (struct svm_node *) malloc((end + 2)*sizeof(struct svm_node));
		svm_input[0].index = 1;
		svm_input[end+1].index = -1;
		for(i = 1;i <= end;i++){
			svm_input[i].index = i + 1;
			svm_input[i].value = svm_in[i - 1];
		}
		for(i = 0;i < end;i++){
			svm_input[0].value = i;
			td = svm_predict(model,svm_input);
			if(td >= 0)
				svm_tag.push_back('B');
			else
				svm_tag.push_back('O');
		}
		//m->tag(m3n_in,m3n_tag);
		m->tag(m3n_in,m3n_tag,sequencep,nodep);
		for(i = 0;i < end;i++){
			fout << m3n_in[i][0] << " " << svm_tag[i] << " " << m3n_tag[0][i] << endl;
		}
		
	}

	svm_destroy_model(model);
	delete m;
	fin.close();
	fout.close();
	return 0;
}
