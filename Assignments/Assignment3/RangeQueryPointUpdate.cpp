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
            add(i+1, a[i]);
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
    int d, b, c;
    while(q--){
      cin>>b>>c>>d;
      if(b==1){
          
          Bit.add(c,d-a[c-1]);
          a[c-1]= d;
      }
      else{
          cout<<Bit.sum(c, d)<<endl;
      }
    }
}