#include<thread>
#include<iostream>
#include<vector>
using namespace std;

void max123(vector<int> tab,int debut,int fin, int &max1)
{
	max1=tab[debut];
	for(auto i=debut+1;i<fin;i++)
	{
		if(tab[i]>max1)
			max1=tab[i];
	}

}

int main(){
	vector <int>tab(20,0);
	int max1=0;
	tab[5]=10;
	thread t1,t2;
	
	t1=thread(max123,tab,0,10,ref(max1));
	t2=thread(max123,tab,10,20,ref(max1));
	t1.join();
	t2.join();
	cout<<max1<<endl;
	return 0;	


}
