#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>
#include <map>
using namespace std;

mutex mutex_ordini;
map<string, list<string>> dict;
condition_variable cv;
unique_lock<mutex> lk(mutex_ordini);


void inserisci_ordine(string nome_studente)
{
    mutex_ordini.lock();
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
    mutex_ordini.unlock();
    cv.notify_all();
}

void invia_ordini(int numero_minimo){
    
    cv.wait(lk,[numero_minimo]{
        return (dict.size() == numero_minimo);
        });
    cout << "Invio ordini: "<<endl;
    for(const auto& x : dict){
        cout<< x.first << " ha ordinato: ";
        for(const auto& y : x.second){
            if(y == x.second.back()){
                cout << y << "." << endl;
                cout << "Prof ha inviato 📦 di " << x.first << " ..." << x.first << " ricevuto"<<endl;
            }
            else{
            cout << y << ", ";
            }
        }
    }
    cout << "Invio ordini completato!"
    cv.notify_all();
}

int main() {
    thread studente1(inserisci_ordine, "Giorgio");
    thread studente2(inserisci_ordine, "Carla");
    thread studente3(inserisci_ordine, "Bonromeo");
    thread insegnante(invia_ordini, 3);
    studente1.join();
    studente2.join();
    studente3.join();
    insegnante.join();
    
    return 0;
}
