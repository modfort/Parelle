#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#define T 7
using namespace std;

void max_tab(vector<int> tab,int debut,int fin,int & max)
{	
	max=tab[debut];
	for (auto i = debut+1; i <fin ; ++i)
		{
			if(max<tab[i])
				max=tab[i];
		}	
}

int main(int argc, char const *argv[])
{	int max1;
	vector<int> tab(50,0),max(T,0);
	thread t[T];
	tab[10]=6;
	tab[49]=10;
	tab[25]=3;
	tab[0]=11;
	for (int i = 0; i < T; ++i)
	{
		t[i]=thread(max_tab,tab, i*tab.size()/T,(i+1)*tab.size()/T ,std::ref(max[i]));
	}
	for (int i = 0; i < T; ++i)
	{
		t[i].join();
	}
	max_tab(max_tab,max, 0,T ,std::ref(max1));
	std::cout<<max1<<std::endl;
	return 0;
}




