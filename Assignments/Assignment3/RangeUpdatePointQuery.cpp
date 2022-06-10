#include<bits/stdc++.h>
using namespace std;
class BIT{
    int n;
    vector<long long> bit;
    public:
    BIT(int NN){
        this->n= NN;
        this->bit= vector<long long> (n+1,(long long)0);
    }
    BIT (vector<int > a): BIT(a.size()){
        for(size_t i=0;i<a.size();i++){
            add(i+1,i+1, a[i]);
        }
        
    }
    
    long long sum(int index){
        long long res=0;
        for(;index>0;index-=(index&(-index))){
           
            res+=bit[index];
        }
        
      
        return res;
    }
    long long sum(int l, int r){
        return sum(r)-sum(l-1);
    }
    void add(int index, int delta){
        for(; index<=n;index+=index&(-index)){
            bit[index]+=delta;
        }
    }
    void add(int l, int r, int val){
        add(l, val);
        add(r+1, -val);
    }
    
};
int main(){
    int n;
    int q;
    cin>>n>>q;
    vector<int> a(n);
    
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
   
    BIT Bit(a);
    int d,b, c, u, k;
    while(q--){
      cin>>d;
      if(d==1){
          cin>>b>>c>>u;
          Bit.add(b, c, u);
          
         
      }
      else{
          cin>>k;
          cout<<Bit.sum(k)<<endl;
      }
    }
}