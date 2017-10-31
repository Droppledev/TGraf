#include <iostream>
#include <string.h>
#include <vector>
#include <limits.h>
#include <string.h>

using namespace std;

class Graph{
private:
    int holder;
    int besar;
    int src;
    vector<int>arr[1000]; //menyimpan input array sebagai representasi adjacency matrix
    bool undirected;    //penyimpan nilai apakah dia sebuah undirected atau tidak
    vector<int>track[100]; //penyimpan nanti track menuju index track[index] apa saja , dimasukkanny pake push_back
    int dist[1000];      //distance dari src ke index
    bool visited[1000];  //apakah dia sudah fix / sudah di kunjungi?
public:
    Graph(){undirected=true;}
    ~Graph();
    void setBesar(int besar){
        this->besar=besar;
    }
    int getBesar(){return besar;}
    void setSrc(int src){this->src=src;}
    int getSrc(){return src;}
    void setInput();
    bool isValid();
    void djikstra();
    int searchLowCost();
    void print(){
        cout<<"Vertex \t Distance from source\n";
        for (int i=0 ; i < besar ; ++i){
            cout<<"  "<<i<<"\t\t"<<dist[i]<<endl;
        }
    }
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

int Graph::searchLowCost(){
    int mi=INT_MAX,index;
    for (int j=0 ; j < besar ; ++j){
        if (mi>=dist[j]&& !visited[j]){
            mi=dist[j];
            index=j;
        }
    }
    return index;
}

void Graph::djikstra(){
for (int i=0 ; i < besar ; ++i) dist[i]=INT_MAX;
memset(visited,false, sizeof(visited));

dist[src]=0; //jarak dari mulai ke source pasti 0

int current_shortest;

    for (int i=0 ;i < besar ; ++i){ //eror heres
    current_shortest=searchLowCost(); //disini pencarian terpendeknya
    visited[current_shortest]=true;

        for (int j=0 ; j < besar ; ++j){
                if (!visited[j] && arr[current_shortest][j]
                    &&dist[current_shortest]!=INT_MAX && !dist[current_shortest]+arr[current_shortest][j]<dist[j]){
                        dist[j]=dist[current_shortest]+arr[current_shortest][j]; //untuk menuju vertex ke j dari vertex current_shortest , perlu cost
                                                                            //sebanyank arr[current][j]
                                                                            //akan diupdate trus
                }
        }
    }
}

int main(){
 Graph *mainframe = new Graph;
 mainframe->setBesar(9);
 mainframe->setSrc(0);
 mainframe->setInput();
 mainframe->djikstra();
 mainframe->print();
}
