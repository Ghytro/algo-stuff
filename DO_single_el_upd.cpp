//Простейшее дерево отреков на примере деревьев минимумов и максимумов
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,tune=native")
#define MAXSIZE 100000
#define MININF -999999999999
#define PLUSINF 999999999999
#define endl "\n"

using namespace std;

vector<long long> maxtree, mintree, a(MAXSIZE);

void build(long long id, long long l, long long r)
{
    if (r - l == 1)
    {
        maxtree[id] = a[l];
        mintree[id] = a[l];
        return;
    }
    long long m = (l + r) / 2;
    build(id*2 + 1, l, m);
    build(id*2 + 2, m, r);
    maxtree[id] = max(maxtree[id*2 + 1], maxtree[id*2 + 2]);
    mintree[id] = min(mintree[id*2 + 1], mintree[id*2 + 2]);
}

long long get_max(long long id, long long l, long long r, long long s_l, long long s_r)
{
    if (r <= s_l || s_r <= l)
        return MININF;
    if (s_l <= l && r <= s_r)
        return maxtree[id];
    long long m = (l + r) / 2;
    return max(get_max(id*2 + 1, l, m, s_l, s_r), get_max(id*2 + 2, m, r, s_l, s_r));
}

long long get_min(long long id, long long l, long long r, long long l_s, long long r_s)
{
    if (r <= l_s || r_s <= l)
        return PLUSINF;
    if (l_s <= l && r <= r_s)
        return mintree[id];
    long long m = (l + r) / 2;
    return min(get_min(id*2 + 1, l, m, l_s, r_s), get_min(id*2 + 2, m, r, l_s, r_s));
}

void refresh_max(long long id, long long l, long long r, long long i, long long val)
{
    if (r - l == 1)
    {
        maxtree[id] = val;
        return;
    }
    long long m = (l + r) / 2;
    if (i < m)
        refresh_max(id*2 + 1, l, m, i, val);
    else
        refresh_max(id*2 + 2, m, r, i, val);
    maxtree[id] = max(maxtree[id*2 + 1], maxtree[id*2 + 2]);
}

void writetree(int id, int l, int r)
{
    if (r - l == 1)
        cout << maxtree[id] << ' ' << mintree[id];
    int m = (l + r) / 2;
    writetree(id, l, m);
    writetree(id, m, r);
}

void refresh_min(long long id, long long l, long long r, long long i, long long val)
{
    if (r - l == 1)
    {
        mintree[id] = val;
        return;
    }
    long long m = (l + r) / 2;
    if (i < m)
        refresh_min(id*2 + 1, l, m, i, val);
    else
        refresh_min(id*2 + 2, m, r, i, val);
    mintree[id] = min(mintree[id*2 + 1], mintree[id*2 + 2]);
}

long long _abs(long long x)
{
    if (x < 0)
        return -x;
    return x;
}

int main()
{

    for (long long i = 0; i < a.size(); i++)
    {
        a[i] = (((i + 1)*(i + 1)) % 12345) + (((i + 1)*(i + 1)*(i + 1)) % 23456);
    }
        //cout << "a filled" << endl;
    /*for (int i = 0; i < 10; i++)
        cout << a[i] << endl;
*/
    long long k;
    cin >> k;
    maxtree.resize(4*MAXSIZE, MININF);
    mintree.resize(4*MAXSIZE, PLUSINF);
    build(0, 0, MAXSIZE);
    //cout << "builded" << endl;
    vector<long long> ans;
    for (long long i = 0; i < k; i++)
    {
        long long x, y;
        cin >> x >> y;
        if (x > 0)
        {
            //cout << get_max(0, 0, MAXSIZE - 1, x - 1, y) << ' ' << get_min(0, 0, MAXSIZE - 1, x - 1, y) << endl;
            ans.push_back(get_max(0, 0, MAXSIZE, x - 1, y) - get_min(0, 0, MAXSIZE, x - 1, y));
            //cout << ans.back() << endl;
        }
        else
        {
            a[_abs(x) - 1] = y;
            refresh_max(0, 0, MAXSIZE, _abs(x) - 1, y);
            refresh_min(0, 0, MAXSIZE, _abs(x) - 1, y);
        }
    }
    for (long long i: ans)
        cout << i << endl;
    return 0;
}
