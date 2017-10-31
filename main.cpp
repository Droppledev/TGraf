#include <iostream>
#include <string.h>
#include <vector>
#include <limits.h>
using namespace std;

class Graph{
private:
    int holder;
    int besar;
    vector<int>arr[100]; //menyimpan input array sebagai representasi adjacency matrix
    bool undirected;    //penyimpan nilai apakah dia sebuah undirected atau tidak
    vector<int>track[100]; //penyimpan nanti track menuju index track[index] apa saja , dimasukkanny pake push_back
    int dist[100];      //distance dari src ke index
    bool visited[100];  //apakah dia sudah fix / sudah di kunjungi?
public:
    Graph(){undirected=true;}
    ~Graph();
    void setBesar(int besar){
        this->besar=besar;
    }
    int getBesar(){return besar;}
    void setInput();
    bool isValid();
    void djikstra();
};


void Graph::setInput(){

    for (int i=0 ; i < getBesar(); ++i){
            for (int j=0 ; j < getBesar() ; ++j){
                cin>>holder;
                arr[i].push_back(holder);
         }
    }
}

bool Graph::isValid(){
    for (int i=0 ; i<getBesar() ; ++i){
        for (int j=0 ; j <getBesar() ; ++j){
            if (arr[i][j]!=arr[j][i]){
                cout<<"Input tidak valid / undirected!\n";
                undirected=false;   //undirected pasti kalau di tranpos tidak akan mengubah nilainya
                break;
            }
        }
    }

}

void Graph::djikstra(){




}

int main(){

}
