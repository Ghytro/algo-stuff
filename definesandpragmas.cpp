#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("section-anchors")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")

#include <bits/stdc++.h>

#define inf 1e18
#define ll long long
#define all(x) x.begin(), x.end()
#define endl "\n"
#define pb push_back
#define pii pair<int, int>
#define pll pair<long long, long long>
#define forn(n) for (size_t i = 0; i < n; ++i)
#define forrn(n) for (size_t i = n; i >= 0; --i)


using namespace std;

using Graph = vector<vector<int>>; //список смежности

template<typename T>
using Table = vector<vector<T>>;

template<typename T>
std::ostream& operator <<(std::ostream &out, std::vector<T> v)
{
    for(auto i: v)
        std::cout<<i<<' ';

    std::cout<<endl;
    return out;
}

template<typename T>
std::istream& operator >>(std::istream &in, std::vector<T> &v)
{
    for (size_t i = 0; i < v.size(); ++i)
        std::cin>>v[i];
    return in;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    return 0;
}
