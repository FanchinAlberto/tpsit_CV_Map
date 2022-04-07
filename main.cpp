#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>
#include <map>
using namespace std;

mutex m;
map<string, list<string>> dict;
condition_variable cv;
mutex a;

void inserisci_ordine(string nome_studente)
{
    a.lock();
    list<string> orders;
    string input;
    cout << "Ordini di: " << nome_studente << endl;
    while(true){
        cout <<"Articolo: ";
        cin>>input;
        if(input == "."){
            break;
        }
        orders.push_back(input);
    }
    dict[nome_studente] = orders;
    a.unlock();
}

int main() {
    thread studente1(inserisci_ordine, "Giorgio");
    thread studente2(inserisci_ordine, "Carla");
    studente1.join();
    studente2.join();
    for(const auto& x : dict){
        cout<< x.first <<  endl;
    }
    
    return 0;
}
