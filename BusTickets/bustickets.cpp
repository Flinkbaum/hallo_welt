
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vl=vector<ll>;
using vvl=vector<vl>;
using vb=vector<bool>;
using vs=vector<string>;
using pll=pair<ll,ll>;
const ll oo =0x3f3f3f3f3f3f3f3fLL;
const double eps=1e-0;

#define sz(c) ll((c).size())
#define all(c) begin(c),end(c)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define xx first
#define yy second
#define FOR(i,a,b) for(ll i=(a); i<(b); i++)
#define FORD(i,a,b) for(ll i=ll(b)-1; i>=(a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define TR(X) ({if(1) cerr << "TR: " << (#X) << " = " << (X) << endl; })

static int n;
static ll** busplan;

static void mod_plan_cheap_next(){
	FOR(i, 0, n){
		FOR(j, i + 1, n){
			if(busplan[i][j] == 0) break;
			if(busplan[i][j] == -1) continue;
			FORD(k, 0, j){
				if(busplan[i][k] == 0) break;
				if(busplan[i][k] > busplan[i][j] || busplan[i][k] == -1)
					busplan[i][k] = busplan[i][j];
				else 
					break;
			}
		}
	}
}

static void dp(){
	mod_plan_cheap_next();
	FOR(i, 2, n){
		FOR(j, 1, i){
			if(busplan[j][i] == -1) break;
			ll next = busplan[0][j] + busplan[j][i];
			if(busplan[0][i] == -1 || next < busplan[0][i])
				busplan[0][i] = next;
		}
	}
	if(busplan[0][n-1] == -1){
		cout << "Impossible" << endl;
		return;
	}
	cout << busplan[0][n-1] << endl;
}

static void fill_busplan(){
	cin >> n;
	busplan = new ll*[n];
	FOR(i, 0, n){
		busplan[i] = new ll[n];
	}
	FOR(i, 0, n){
		FOR(j, 0, n){
			busplan[i][j] = -1;
		}
	}
	for(int i = n-1, j = 0; i > 0; i--, j++){
		busplan[j][j] = 0;
		for(int k = 0; k < i; k++){
			cin >> busplan[j][j + k + 1];
		}
	}
	busplan[n - 1][n - 1] = 0;
}

static void calc_ticket(){
	fill_busplan();
	dp();
	FOR(i, 0, n){
		delete[] busplan[i];
	}
	delete[] busplan;
}

int main(){
	int ds;
	cin >> ds;
	FOR(i,0,ds){
		calc_ticket();
	}
	return 0;
}
