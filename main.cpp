#include <iostream>
#include <cstdio>
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
    vector<int>track[1000]; //penyimpan nanti track menuju index track[index] apa saja , dimasukkanny pake push_back
    int later[1000];    //penyimpan nilai sebelum dimasukkan kedalam track
    int dist[1000];      //distance dari src ke index
    bool visited[1000];  //apakah dia sudah fix / sudah di kunjungi?
public:
    void setBesar(int besar){
        this->besar=besar;
    }
    int getBesar(){return besar;}
    void setSrc(int src){this->src=src;}
    int getSrc(){return src;}
    void setInput();
    bool isValid(); //return apakah dia undirected , undirected pasti kalau di tranposkan hasilnya sama aja
    void djikstra();
    int searchLowCost();
    void print(){
        cout<<"Vertex\tDistance from source\tPath\n";
        for (int i=0 ; i < besar ; ++i){
            cout<<"  "<<i<<"\t\t"<<dist[i]<<" \t\t";

            for (int j=0 ; j < track[i].size();++j){
                cout<<track[i][j]<<" ";
            }
            cout<<endl;
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
                   //undirected pasti kalau di tranpos tidak akan mengubah nilainya
                return false;
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
    if (isValid()){ //apakah dia valid?
    for (int i=0 ; i < besar ; ++i) dist[i]=INT_MIN;
    memset(visited,false, sizeof(visited));

    dist[src]=0; //jarak dari mulai ke source pasti 0

    int current_shortest;

        for (int i=0 ;i < besar ; ++i){ //eror heres
        current_shortest=searchLowCost(); //disini pencarian terpendeknya
        //loop ke 0 pasti dia src


        visited[current_shortest]=true; //visited



        /*


        Print step by step like the ppt here


        */

        if(current_shortest!=src){  //Untuk push routenya
            int start=later[current_shortest]; //nah yang masuk sini pasti loop i>0 , brarti sudah masuk loop yang dibawah
            //dia pasti punya nilai later / nilai ke current_shortest itu lewat mana
            //kalau dia loop i=1 , maka later akan berisi source ,kan pasti dia dari source toh :)

            for (int j=0; j < track[start].size() ; ++j){
                track[current_shortest].push_back(track[start][j]);
            }
            track[current_shortest].push_back(current_shortest);
        }
        else {
            track[current_shortest].push_back(src); //klo awal ya inisialisasi aja pathnya dari dirinya sendiri
        }



            for (int j=0 ; j < besar ; ++j){
                    if (!visited[j] && !arr[current_shortest][j]
                        &&dist[current_shortest]!=INT_MAX && dist[current_shortest]+arr[current_shortest][j]<dist[j]){//akan diupdate trus
                            dist[j]=dist[current_shortest]+arr[current_shortest][j]; //untuk menuju vertex ke j dari vertex current_shortest , perlu cost sebanyank arr[current][j]
                            later[j]=current_shortest;   /*
                                Karena si dist[j] ini menyimpan jarak terdekat matrix ke j dari current_shortest
                                maka index J , cost yang paling ringan itu lewat dari Current
                            */

                    }
            }
        }
    }
}

int main(){

 Graph *mainframe = new Graph;



    int siz,vAwal, vAkhir,bobot;
    cout<<"Masukkan banyaknya vertex : ";
    cin>>siz;
    mainframe->setBesar(siz);

    cout<<"Masukkan Adjacency Matrix ( "<<siz<<" x " << siz<<" )\n";
    mainframe->setInput();

    cout<<"Masukkan vertex awal (1 - "<<siz<<") : ";
    cin>>vAwal;
    mainframe->setSrc(vAwal-1);
    cout <<"Masukkan vertex akhir (1 - "<<siz<<") : ";
    cin>>vAkhir;

    mainframe->djikstra();
    mainframe->print(); //edit printnya supaya passing & ngeprint vAkhir-nya aja

 delete mainframe;
}

/* Mere TC

9 x 9

0 4 0 0 0 0 0 8 0
4 0 8 0 0 0 0 11 0
0 8 0 7 0 4 0 0 2
0 0 7 0 9 14 0 0 0
0 0 0 9 0 10 0 0 0
0 0 4 14 10 0 2 0 0
0 0 0 0 0 2 0 1 6
8 11 0 0 0 0 1 0 7
0 0 2 0 0 0 6 7 0

http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/

*/
