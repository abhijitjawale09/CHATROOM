#include<bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin>>n;
    int inside = 0;
    int result = 0;
    for(int i = 0;i < n; i++) {
        int a , b;
        cin>>a>>b;
        cout<<endl;
        inside += b - a;
        result = max(result , inside);
        
    }
    cout<<result<<endl;
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
