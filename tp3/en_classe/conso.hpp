#include <iostream>
#include <vector>
class Conso{
	public:
		std::vector<int> v;
		int mange;
	Conso(std::vector<int> v){
		this.v=v;
		mange=0;
	}	
	void affiche()
	{
		std::cout<<"j'ai mangé "<<this->mange<<std::endl;
	}

	void mange()
	{
		mange++;
		v.pop();
	}

};