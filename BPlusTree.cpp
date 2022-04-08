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
#define printarr(temp, occ) REP(i,occ)cout<<temp[i]<<" ";cout<<endl;

int t,d;

void insertkey(int* keys, int occupancy, int key){
    int temp;bool ins=false;
        REP(i,occupancy+1){
            if(!ins){
                if(i==occupancy)keys[occupancy]=key;
                else if(keys[i]>key){
                    temp=keys[i];
                    keys[i]=key;
                    ins=1;
                }
            }
            else swap(temp,keys[i]);
        }
}


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
            if(!isdata){
                maxocc = 2*t+1;
                minocc = t;
                childs=(node**)malloc(sizeof(node*)*(2*t+1));
            }else{
                maxocc = 2*d;
                minocc = d;
                childs=nullptr;
            }
            keys=(int*)malloc(sizeof(int)*(maxocc));
            parent=nullptr;
        }
        bool isFull(){ if(occupancy<maxocc)return 0;else return 1; }
        void insert(int key){//in sorted order
            if(!isFull()){//***only for data node***
                /*int temp;bool ins=false;
                REP(i,occupancy+1){
                    if(!ins){
                        if(i==occupancy)keys[occupancy]=key;
                        else if(keys[i]>key){
                            temp=keys[i];
                            keys[i]=key;
                            ins=1;
                        }
                    }
                    else swap(temp,keys[i]);
                }*/
                insertkey( keys, occupancy, key);
                occupancy++;
            }
        }
        bool getisdata(){return isdata;}
        int getkey(int k){return keys[k];}
        int* getkeys(){return keys;}
        node* getchild(int k){return childs[k];}
        void setchild(node* node, int k){childs[k]=node;}
        node* getparent(){return parent;}void setparent(node* p){parent=p;}
        int getocc(){return occupancy;}
        void setocc(int occ){occupancy=occ;}
        void del(int key){//change
            if(!isFull()){
                int temp;bool ins=false;
                REP(i,occupancy+1){
                    if(!ins){
                        if(i==occupancy)keys[occupancy]=key;
                        else if(keys[i]>key){
                            temp=keys[i];
                            keys[i]=key;
                            ins=1;
                        }
                    }
                    else
                        swap(temp,keys[i]);
                }occupancy++;
            }
        }
        void printnode(){
            //cout<<"occ:"<<occupancy<<"/"<<maxocc<<endl;
            REP(i,occupancy)
                cout<<keys[i]<<" ";
            //cout<<endl;
        }
};


pair<int,int> count(node* n1){
    int i=0; int d=0;
    if(n1!=nullptr){
        if(n1->getisdata())d++;
        else {
            i++;
            for(int i=0;i<(n1->getocc()+1);i++){
                pair<int,int> p=count(n1->getchild(i));
                i+=p.first;
                d+=p.second;
            }
        }
    }
    return make_pair(i,d);
}

void printtree(node* n1){
    if(n1==nullptr)return;
    n1->printnode();
    
    if(n1->getisdata()==0){
        cout<<" c( ";
        int occ=n1->getocc();
        REP(i,occ+1){
            printtree(n1->getchild(i));
            cout<<" :: ";
        }
        cout<<") ";
    }
    
}
node* splitindexnode(node* n1, int x){

}

node* splitDataNode(node* n1, int key){
    int* temp1=n1->getkeys();
    int occ=n1->getocc(); 
    int temp[occ+1];
    copy(temp1, temp1+occ, temp);
    insertkey(temp, occ, key);

    node* newnode=new node(1);
    if(n1->getparent()==nullptr){
        node* parent =new node(0);
        parent->setchild(n1,0);
        n1->setparent(parent);
    }
    node* p=n1->getparent();
    int p_occ=p->getocc();
    n1->setocc(d);
    FOR(i,d, occ+1){newnode->insert(temp[i]);}
    //check if parent is full...
    p->insert(newnode->getkey(0));
    p->setchild(newnode,p_occ+1);newnode->setparent(p);
    return p;
}

class BPlusTree{
    private:
        node* root;
    public:
        BPlusTree(){
            root=nullptr;
        }
        void insert(int key){
            if(root==nullptr){
                root=new node(1);
                root->insert(key);
                return;
            }else{
                if(!root->isFull() && root->getisdata())
                    root->insert(key);
                else{
                    /**
                    *   case: if root is data also (only one node and isfull)
                    *   split data node() -> 2 data nodes ... d, d+1
                    **/
                   
                    if(root->getisdata()==1){
                        node* n1=root;
                        if(n1->getparent()==nullptr)
                            root=splitDataNode(n1,key);
                        else splitDataNode(n1,key);
                        
                    }else{//travel to data node...
                        node* curr=root;
                        while(curr->getisdata()){
                            //if(key<curr->getkey(0))curr->getchild(0);
                            //else 
                            REP(i,curr->getocc()){
                                if(key<curr->getkey(i)){curr->getchild(i);continue;}
                            }curr->getchild(curr->getocc());
                        }
                    }
                    
                }
            }
        }
        void print(){
            if(root!=nullptr){
                pair<int, int> p=count(root);
                cout<<p.first<<" "<<p.second<<" ";
                root->printnode();
                cout<<endl;
            }else cout<<"0 0\n";
        }
        void print2(){
            printtree(root);
            cout<<endl;
        }
        
};

signed main(){
    FAST_IO
    cin>>d>>t;
    BPlusTree T;
    int x;
    while(cin>>x)
        switch(x){
            case 1: int y; cin>>y; T.insert(y); break;
            case 2: T.print(); break;
            case 3: goto end; break;
            case 4: T.print2(); break;
            default: cout<<".\n"; break;
        }
    
    end:
    return 0;
}