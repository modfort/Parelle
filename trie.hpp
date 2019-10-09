#include <vector>
#include <string>
#include<algorithm>
#include<utility>
class Trie{

		
			char c;
			std::vector<Trie>next;
		
		Trie operator=(){}
		Trie(char n,std::vector<char>  vect){
			c=n;
			for (int i = 0; i < vect.size(); ++i)
			{
				next[i].c=vect[i];
				next[i].next=Trie();

			}
		}

};