//Author: D. Nisritha Reddy
#include<bits/stdc++.h>
#define int long long 
#define pb push_back
#define ndl "\n"
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define mod (int)(1e9 + 7)
#define F first
#define S second
#define vi vector<int>
#define vc vector<char>
#define vpi vector<pair<int,int>>
#define pi pair<int,int>
#define mi map<int, int>
#define miv map<int,vector<int>>
using namespace std;

template<class T>
void inp(vector<T>&a){ for(auto &x : a)cin>>x; }

template<class T>
void print(vector<T>&a){
    for(auto &x: a)cout<<x<<" ";
    cout<<ndl;
}

template<class T>
void print(T x){cout<<x<<" ";}

template<class T>
void println(T x){ cout<<x<<"\n";}

template<class T>
T maxEle(vector<T>&a){
    T maxi = LLONG_MIN;
    for(auto x : a)
        if(x>maxi)maxi = x;
    return maxi;
}

template<class T>
T minEle(vector<T>&a){
    T mini = LLONG_MAX;
    for(auto x: a)
        if(x<mini) mini = x;
    return mini;
}

template<class T>
void sortAll(vector<T>&a){ sort(a.begin(), a.end());}

template<class T>
T sumAll(vector<T>&a){
    T sum = 0;
    for(auto x : a) sum +=x;
    return sum;
}

template<class T>
void revAll(vector<T>&a){reverse(a.begin(),a.end());}



///////////////////////////////////////////////////////////////////////////////////////////////////

int n;
vi inTime, outTime;
vi dfs, values, parent;
vector<vi>children;

void DFS(int node){
    
    inTime[node] = dfs.size();
    dfs.pb(node);
    
    for(auto it: children[node]){
        DFS(it); 
    }
    outTime[node] = dfs.size();
    dfs.pb(node);
    
}

class MST{
    
    public:
    
    vector<vi>tree;
    int sz;
    
    void merge(vi& tmp, vi& v1, vi& v2){
        
           int sz1 = v1.size();
           int sz2 = v2.size();
           
           int i = 0, j = 0;
        
           while(i<sz1 && j<sz2){
               
               if(v1[i] < v2[j]){
                   tmp.pb(v1[i++]);
               }
               else{
                   tmp.pb(v2[j++]);  
               }
           }
        
           while(i<sz1){
               tmp.pb(v1[i++]);
           }
           while(j<sz2){
               tmp.pb(v2[j++]);
           }
        
    }
    
    void build(int l, int r, int idx){
        
           if(l==r){
               tree[idx].pb(values[dfs[l]]); 
               return;
           }
        
           int mid = ( l + r ) >> 1;
           build(l, mid, 2*idx + 1);
           build(mid+1, r, 2*idx + 2);
           
           /* merge sort */
        
           merge(tree[idx], tree[2*idx+1], tree[2*idx+2]);

    }
    
    MST(){
        
        this-> sz = dfs.size();
        this->tree.resize(4*sz+1);
        this->build(0,sz-1, 0);
    }
    
    int bs(vi& tmp, int x){
        
        int l = 0, h = tmp.size()-1;
        
        int ans = -1;
        
        while(l<=h){
            int mid = ( l + h ) >> 1;
            if(tmp[mid] < x){   
                ans = mid; l = mid + 1; 
            }
            else{
                h = mid - 1;
            }
        }
        return ans + 1;
    }
    
    int query(int l, int r, int idx, int low, int high, int parVal){
         
        if(l > high || r < low){
            return 0;
        }
        
        if(l >= low && r <= high){
            
            return bs(tree[idx], parVal);
        }
        
        int mid = (l + r) >> 1;
        
        int ans1 = query(l, mid, 2*idx + 1, low, high, parVal);
        int ans2 = query(mid + 1, r, 2*idx + 2, low, high, parVal);

        return (ans1 + ans2);      
    }
    
    int query(int low, int high, int parVal){
        
        return query(0,sz-1,0,low, high, parVal);        
    }

};