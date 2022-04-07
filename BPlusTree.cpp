#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
typedef long long ll;
#define pb push_back
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

int t,d;


class node{
    private:
        int* keys;
        node** childs;
        node* parent;
        bool isdata;
        int occupancy;
        int maxocc;
        int minocc;
    public:
        node(bool dataNode){
            isdata=dataNode;
            occupancy=0;
            if(isdata){//t  t-1:2t-1
                maxocc = 2*t+1;
                minocc = t;
                childs=(node**)malloc(sizeof(node*)*(2*t+1));
            }else{ //d d:2d
                maxocc = 2*d;
                minocc = d;
                childs=nullptr;
            }
            keys=(int*)malloc(sizeof(int)*(maxocc));
            
            parent=nullptr;
        }
        bool isFull(){ if(occupancy<maxocc)return 0;else return 1; }
        void insert(int key){//in sorted order
            if(!isFull()){
                keys[occupancy++]=key;
            }
        }
        void printnode(){
            //cout<<"occ:"<<occupancy<<"/"<<maxocc<<endl;
            REP(i,occupancy)
                cout<<keys[i]<<" ";
            cout<<endl;
        }

};

signed main(){
    FAST_IO
    cin>>t>>d;
    cout<<t<<endl;
    cout<<d<<endl;
    node n1(true);
    int x;
    while(cin>>x)
        switch(x){
            case 1: int y; cin>>y; n1.insert(y); break;
            case 2: goto end; break;
            case 3: n1.printnode(); break;
            
            default: cout<<".\n"; break;
        }
    
    end:
    return 0;
}