  #include "Graph.hpp"
#define TAILLE 800  

void creer_noued(int val)
{  
    noued nouveau;
    nouveau.val=val;
    nouveau.x=distribution(generator)%( TAILLE-50);
    nouveau.y=distribution(generator)%( TAILLE-50);
    nouveau.voiture=false;
    if((size_t)(val+1)>Graph.size())
        Graph.resize(val+1);
    Graph[val]=nouveau;
    
}
/*
    j'utilise deux methodes pour creer 
    des routes pour eviter les dedodances dans le cas charger
    alors que de manieres alatoire il faut le faire doublement
*/
void ajouter_arrete(int val1,int val2)
{
    Graph[val1].autre.push_back(val2);
}

void ajouter_arrete_double(int val1,int val2)
{
    Graph[val1].autre.push_back(val2);
    Graph[val2].autre.push_back(val1);   
}
void charger(string name)
{
    ifstream fichier(name);
    int debut,liste,taille;
    while(fichier.good())
    {   
        fichier >> taille ;
        fichier >> debut ;
        creer_noued(debut);
        while(taille>0){
        
            fichier>>liste;
            ajouter_arrete(debut,liste);
            taille--;
        }
       
    }
    fichier.close();
    erase_all_point_null();
}
// fonction pas utilisé 
/*
void charger_2(string name)
{
    ifstream fichier(name);
    int debut,liste,taille,nbr_element;
    fichier >> nbr_element;
    for (int i = 0; i < nbr_element; ++i)
    {
        fichier >> taille ;
        fichier >> debut ;
        printf("creation de %d\n",debut );
        creer_noued(debut);
        printf("taille de %d est %d \n",debut,taille );
        while(taille>0)
        {    
            fichier>>liste;
            ajouter_arrete(debut,liste);
            taille--;
        }
        //affiche();
    }
    fichier.close();
}
*/
void affiche(){
    for (size_t i = 0; i < Graph.size(); ++i){
         if(Graph[i].autre.size()==0)
            continue;
       printf("%d : ",Graph[i].val );
        for (size_t j = 0; j < Graph[i].autre.size(); ++j)
        {
            printf("%d |",(Graph[i].autre[j]));
        }
        printf("\n");
    }
}
//fonction qui determine si un nouead a deja une connection avec un autre
/*
    fonction qui determine si il existe un chemin entre
    deux point
*/
int existe_pas(int val1 ,int val2)
{   if(Graph[val1].autre.size()<=Graph[val2].autre.size()){ 
           for (size_t i = 0; i < Graph[val1].autre.size(); ++i)
                if(Graph[val1].autre[i]==val2)
                    return 1;
           }
    else{
          for (size_t i = 0; i < Graph[val2].autre.size(); ++i)
           
                if(Graph[val2].autre[i]==val1)
                    return 1;
              }
    return 0;
}

void init_aleatoire(int val){
    Graph.resize(val);
    int i=0,premier,deuxieme;
    vector<int> Lien;
    for (size_t i = 0; i < Graph.size(); i++)   
      creer_noued(i);
    for(size_t i=0;i<Graph.size()*2;i++)
    {
        do {
            premier = distribution(generator) % Graph.size();
        }while(premier==i);
        if(Graph[premier].autre.size()<4 &&Graph[i].autre.size()<4)
            ajouter_arrete_double(i,premier);
    }
   
}
  

/*
    ici on dit que les voitures sont distribue librement
*/
void init_voiture(int val){   
    int numero_de_thread=0;
    for (size_t i = 0; i < Thread.size()-1; ++i)
        {
        Graph[i].voiture=true;
        Thread[numero_de_thread].second=i;
        numero_de_thread++;
        }

    for (size_t i = 0; i < Graph.size(); ++i)
        {
            printf("voiture %d est %d\n",Graph[i].val,Graph[i].voiture );
        }    

}

/*
    ici on elemeiment les point qui n'ont pas de successeur 
    cette fonction est utile uniquement si on charge 
    un graphe depuis un fichier ou autre 

*/

void deplacement(int nbrthread,int &val,mutex&bloque){
    /*
    dans cette partie du code en veut passer d'un point A a un point b
    */
    int voiture;
    
   while(1){ 
         if(Prog==false)
            return;
         do{
           /*
           ici on determine le chemin possible , je joue a l'aleatoire pour
           ne pas qu'a chaque fois l'on prennent le pemier chemain venue
           */
           voiture=distribution(generator)%( Graph[val].autre.size()+1);
        
        }while(Graph[element(Graph[val].autre[voiture])].voiture==true);
        bloque.lock();
        printf("la voiture %d est partie de %d  a %d \n",nbrthread,Graph[val].val, Graph[element(Graph[val].autre[voiture])].val);
        Graph[val].voiture=false;
        voiture= element(Graph[val].autre[voiture]); 
        Graph[voiture].voiture=true;
        val=voiture;
           for (size_t j = 0; j < Graph.size(); ++j)
                    {
                        printf("voiture %d est %d\n",Graph[j].val,Graph[j].voiture );
                    }   
            for (int i = 0; i < 5; ++i)
                        {
                                printf("\n");
                        }        
       // val=Thread[nbrthread].second;
        bloque.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    }
}
/*
    fonction qui nous retourne la position d'un element donneé
*/
int element(int val){
    
    for (size_t i = 0; i < Graph.size(); ++i)
    {
        if(Graph[i].val==val)
            return i;
    }
    return 0;

}

void erase_all_point_null(){

    for (size_t i = 0; i < Graph.size(); ++i){
    
        if(Graph[i].autre.size()==0)
            Graph.erase(Graph.begin()+i);
    }
}
int main(int argc, char const *argv[]){   
    if(!argv[1]  || atoi(argv[1])<=0  ){
        fprintf(stderr, "%s\n", "erreur de parametre  <Thread>");
        exit(0);
        }
   //  Pair_thread Thread;
    mutex bloque;    
    Prog=true;
    int nbrthread=atoi(argv[1]); 
    Thread.resize(nbrthread+1);   
    //charger("graph.txt");
    init_aleatoire(200);
    init_voiture(nbrthread);
    
    for (size_t i = 0; i < Thread.size(); ++i) {  
                if(i==Thread.size()-1)
                        if(mainA()==1)
                            Prog=false;


             Thread[i].first=thread(deplacement,i,ref(Thread[i].second),ref(bloque));
        
    }

    for (size_t i = 0; i < Thread.size(); ++i)
        Thread[i].first.join();
     
    for (size_t i = 0; i < Graph.size(); ++i)
            printf("voiture %d est %d\n",Graph[i].val,Graph[i].voiture );
   
   /*init_aleatoire(atoi(argv[1]));  */
   affiche();
    return 0;
}




 int mainA()
{
    sf::RenderWindow window(sf::VideoMode(TAILLE, TAILLE), "SFML works!");
    vector<sf::Vertex> vertices;
    std::vector<sf::CircleShape> Circle((int)Graph.size()); 
    sf::CircleShape APousser(3.0f);
    int position;
    
    for (size_t i = 0; i < Graph.size(); ++i)
    {
        for (size_t j = 0; j < Graph[i].autre.size(); ++j)
        {
            vertices.push_back(sf::Vector2f(Graph[i].x, Graph[i].y));
            position= element(Graph[i].autre[j]);
            vertices.push_back(sf::Vector2f(Graph[position].x, Graph[position].y));

        }
    }
    
    // pour dessiner, on utilise les mêmes fonctions
    for (int i = 0; i < 3; ++i)
    {
        std::cout<<vertices[i].position.y<<std::endl;
    }

            for (size_t i = 0; i < Graph.size(); ++i)
                            {
                                APousser.setPosition(Graph[i].x,Graph[i].y);
                                if(Graph[i].voiture==false)
                                    APousser.setFillColor(sf::Color::Green);
                                else
                                    APousser.setFillColor(sf::Color::Blue);
                               Circle[i]=APousser;
                     }
    // on la dessine dans la fenêtre
        while (window.isOpen())
        {     for (size_t i = 0; i < Graph.size(); ++i)
                            {
                                if(Graph[i].voiture==false)
                                    Circle[i].setFillColor(sf::Color::Green);
                                else
                                    Circle[i].setFillColor(sf::Color::Blue);
                     }
    // on la dessine dans la fenêtre
            sf::Event event;
            while (window.pollEvent(event))
            {   
                if (event.type == sf::Event::Closed){
                    window.close();
                    return 1;

                }
            }

            window.clear();
            for (int i = 0; i < vertices.size(); i+=2)
            {   sf::Vertex line[] =
                    {
                        vertices[i],
                        vertices[i+1]
                    };
                window.draw(line, 2, sf::Lines);
            }
            for (size_t i = 0; i < Circle.size(); ++i)
                       {
                          window.draw(Circle[i]);
                       }           
            // window.draw(&Circle[0], Circle.size() , sf::Circle);           

          window.display();
        }

        return 0;
}