//пример с обновлениями на отрезке
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,tune=native")

using namespace std;

vector<int> maxtree, sumtree, a, prom;

void push(int id, int l, int r)
{
    if (prom[id] == -1)
        return;
    maxtree[id] += prom[id];
    if (r - l > 1)
    {
        for (int i = 1; i <= 2; i++)
        {
            if (prom[id*2 + i] == -1)
                prom[id*2 + i] = prom[id];
            else
                prom[id*2 + i] += prom[id];
        }

    }
    prom[id] = -1;
}

void build(int id, int l, int r)
{
    if (r - l == 1)
    {
        maxtree[id] = a[l];
        sumtree[id] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(id*2 + 1, l, m);
    build(id*2 + 2, m, r);
    maxtree[id] = max(maxtree[id*2 + 1], maxtree[id*2 + 2]);
    sumtree[id] += sumtree[id*2 + 1] + sumtree[id*2 + 2];
}

long long get_max(long long id, long long l, long long r, long long s_l, long long s_r)
{
    push(id, l, r);
    if (r <= s_l || s_r <= l)
        return -1;
    if (s_l <= l && r <= s_r)
        return maxtree[id];
    long long m = (l + r) / 2;
    return max(get_max(id*2 + 1, l, m, s_l, s_r), get_max(id*2 + 2, m, r, s_l, s_r));
}

void refresh(int id, int l, int r, int s_l, int s_r, int v)
{
    push(id, l, r);
    if (r <= s_l || s_r <= l)
        return;
    if (s_l <= l && r <= s_r)
    {
        prom[id] = v;
        push(id, l, r);
        return;
    }
    int m = (l + r) / 2;
    refresh(id*2 + 1, l, m, s_l, s_r, v);
    refresh(id*2 + 2, m, r, s_l, s_r, v);
    maxtree[id] = max(maxtree[id*2 + 1], maxtree[id*2 + 2]);
}

int main()
{

    int n, k;
    cin >> n;
    a.resize(n);
    maxtree.resize(4*n, -1);
    sumtree.resize(4*n, -1);
    prom.resize(4*n, -1);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(0, 0, n);
    cin >> k;
    vector<int> ans;
    for (int i = 0; i < k; i++)
    {
        char z;
        cin >> z;
        if (z == 'a')
        {
            int l, r, add;
            cin >> l >> r >> add;
            refresh(0, 0, n, l - 1, r, add);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            ans.push_back(get_max(0, 0, n, l - 1, r));
        }
    }
    for (auto i: ans)
        cout << i << ' ';
    return 0;
}
