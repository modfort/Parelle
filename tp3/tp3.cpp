#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <chrono>
#define NBMAX 2
#define NBDEP 5
#define VCONS 1000
#define VPRO  550
using namespace std;

vector<int> mange(NBMAX,10);

void consomme(mutex & lock,vector<int> &  v,int numero)
{	while(1){

	if(v.size() > 0){
		lock.lock();
		cout<<"Mon consommateur "<<numero+1<<" a consomme"<<v.back()<<endl;
		v.pop_back();
		lock.unlock();
		mange[numero]++;

		}
	std::this_thread::sleep_for(std::chrono::milliseconds(VCONS));
	if(mange[numero]==20)
		return;
}

}

void produit(mutex &lock,vector<int> & v)
{	int nbr_mange=0;
	while(1){

		if(v.size()<10){
	
			lock.lock();

			v.push_back(v.size());
			cout<<" produit"<<v.size()<<endl;
			lock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(VPRO));
		}
	for (int i = 0; i < NBMAX ; ++i)
	{
		if(mange[i]==20)
			nbr_mange++;
	}
	if(nbr_mange==NBMAX)	
		return;
	}

}

int main(int argc, char const *argv[])
{	vector<int> v;
	v.resize(NBDEP);
	cout<<v.size()<<endl;
	mutex lock;
	
	thread consommateur[NBMAX+1];
	 consommateur[0]=thread(produit,ref(lock),ref(v));

	for (int i = 1; i < NBMAX+1; ++i)
	{
		consommateur[i]=thread(consomme,ref(lock),ref(v),i-1);
	}
	for (int i = 0; i < NBMAX+1; ++i)
	{
		consommateur[i].join();
	}
	return 0;
}