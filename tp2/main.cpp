#include <iostream>
#include "md5.h"
#include<vector> 
#include<tgmath.h> 
#include<thread>
#define MAX 4
using namespace std;
vector <char>Alpha_numer(62,'c');
vector<string>mot;
void trouve_mot_de_passe(string); 
void display(int start, int nb,string);
void autre_mot(string trouve);
void descendre(string ou_on_est,string trouve,int profondeur);
typedef struct arbre
{	
		char c ;
		struct arbre *next;		
}arbre;

int main(int argc, char *argv[])
{	/*if(argc<2)
	{
		fprintf(stderr, "erreur de saisie\n" );
		return EXIT_FAILURE;
	}*/
	size_t j=0;	
	for(auto i=65;i<=90;i++,j++)
		Alpha_numer[j]=i;
	for (auto i=97;i<=121;i++,j++)
		Alpha_numer[j]=i;
	for(auto i=48;i<=57;i++,j++)
		Alpha_numer[j]=i;
	/*thread t1(display,0,16,md5(argv[1]));
	thread t2(display,16,33,md5(argv[1]));
	thread t3(display,33,50,md5(argv[1]));
	thread t4(display,50,62,md5(argv[1]));
   t1.join();
   t2.join();
   t3.join();
   t4.join();*/
	autre_mot(md5("AAA"));
   return 0;
}

void display(int debut,int fin,string trouve){
	string mot;
	mot.clear();
	for (auto pr = debut; pr <fin ; ++pr)
	{					
		mot=Alpha_numer[pr];
		if(trouve.compare(md5(mot))==0)
					{	cout<<mot<<endl;
							exit(2) ;
					}
			mot.clear();
		for (auto de = 0; de < 62; ++de)
		{		mot=Alpha_numer[pr]+Alpha_numer[de];
					if(trouve.compare(md5(mot))==0)
					{	cout<<mot<<endl;
							exit(2) ;
					}
					mot.clear();

			for (auto tr = 0; tr <62 ; ++tr)
			{ 	mot=Alpha_numer[pr]+Alpha_numer[de]+Alpha_numer[tr];
					if(trouve.compare(md5(mot))==0)
					{	cout<<mot<<endl;
							exit(2) ;
					}
							mot.clear();
				for (int qu = 0; qu < 62; ++qu)
				{
					mot=Alpha_numer[pr]+Alpha_numer[de]+Alpha_numer[tr]+Alpha_numer[qu];
				
					if(trouve.compare(md5(mot))==0)
					{	cout<<mot<<endl;
							exit(2) ;
					}
					mot.clear();
				}

			}
		}
	}

  }


void autre_mot(string trouve){
		string c;
		for (int i = 0; i < 62; ++i){
				c=Alpha_numer[i];

				descendre(c,trouve,3);

				c.clear();
			}
			for (int i = 0; i < 62; ++i){
				c=Alpha_numer[i];

								descendre(c,trouve,2);

				c.clear();
			}

}


void descendre(string ou_on_est,string trouve,int profondeur){
	if(profondeur>MAX)
		return;
	cout<<ou_on_est<<endl;
	if((md5(ou_on_est)).compare(trouve)==0)
		{
			cout<<ou_on_est<<std::endl;
				exit(0);		}
	for (int i = 0; i < 62; ++i)
			{
				descendre(ou_on_est+Alpha_numer[i],trouve,profondeur+1);
			}		
}


















