#include<string>
#include<iostream>


using namespace std;
int main(){
	
	string mot("a");
	mot[0]++;
	cout<<mot[0]<<"\n";
	printf("%d\n",mot[0]);
	if(60<mot[0])
		mot.replace(0,1,"a");
	cout<<mot<<endl;
	return 0;


}

