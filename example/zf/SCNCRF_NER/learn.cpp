#include<stdio.h>
extern int svm_main_learn(int,char**);
extern int main_learn(int,char**);
extern int trans_train(char*,char*,char*);
void train_svm(char* train,char* model){
	char *args[3];
	args[0] = "svm";
	args[1] = train;
	args[2] = model;
	svm_main_learn(3,args);

}
void train_m3n(char* train,char* temp,char* model){
	char *args[4];
	args[0] = "m3n";
	args[1] = temp;
	args[2] = train;
	args[3] = model;
	main_learn(4,args);
}
int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("Usage:%s train m3n_template\n",argv[0]);
		return 1;
	}
	train_m3n(argv[1],argv[2],"m3n.model");
	trans_train(argv[1],"train_svm.tmp","dic");
	train_svm("train_svm.tmp","svm.model");
	return 0;
}
