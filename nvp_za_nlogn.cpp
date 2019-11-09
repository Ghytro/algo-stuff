//надо реверс убрать, будет нвп
#include <bits/stdc++.h>
#define ll long long
#define INF 999999999999999

using namespace std;

vector<ll> a;
int main()
{
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    reverse(a.begin(), a.end());
    //for (int i = 0; i < n; i++)
      //  cout << a[i] << ' ';
    vector<ll> dp(n + 1, INF), num(n, -1), par(n, -1);
    dp[0] = -INF;
    for (int i = 0; i < n; i++)
    {
        auto it = lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        dp[it] = a[i];
        num[it] = i;
        par[i] = num[it - 1];
    }

    int st = 0;
    for (int i = par.size() - 1; i >= 0; i--)
    {
        if (par[i] != -1)
        {
            st = i;
            break;
        }
    }
    vector<int> ans;
    ans.push_back(st);
    while (par[ans.back()] != -1)
        ans.push_back(par[ans.back()]);

    cout << ans.size() << endl;
    for (int i: ans)
        cout << a.size() - i << ' ';
    return 0;
}
