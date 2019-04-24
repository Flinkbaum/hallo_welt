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

#define FSZ 8

#include <algorithm>

static ll field[FSZ][FSZ];
static vector<string> sols;
static int iter_next[7];

static void set_zero(){
	FOR(i,0,FSZ){
		FOR(j,0,FSZ){
			field[i][j] = 0;
		}
	}
}

void print_mat()
{
    int i, j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j){
		if(field[i][j] >= oo){
			cout << "Q ";
		}else{
			cout << field[i][j] << " ";
		}
	}
	cout << endl;
    }
}

static void add(ll &i){
	i++;
}

static void sub(ll &i){
	i--;
}

static void move_queen(int r, int c, function<void(ll &)> f){
	int temp_r = r;
	int temp_c = c;
	while(temp_c > 0 && temp_r > 0) {
		temp_c--;
		temp_r--;
		f(field[temp_r][temp_c]);
	}
	temp_r = r;
	temp_c = c;
	while(temp_c < 7 && temp_r < 7) {
		temp_c++;
		temp_r++;
		f(field[temp_r][temp_c]);
	}
	temp_r = r;
	temp_c = c;
	while(temp_c > 0 && temp_r < 7) {
		temp_c--;
		temp_r++;
		f(field[temp_r][temp_c]);
	}
	temp_r = r;
	temp_c = c;
	while(temp_c < 7 && temp_r > 0) {
		temp_c++;
		temp_r--;
		f(field[temp_r][temp_c]);
	}
	
	temp_r = r;
	while(temp_r < 7) {
		temp_r++;
		f(field[temp_r][c]);
	}
	temp_r = r;
	while(temp_r > 0) {
		temp_r--;
		f(field[temp_r][c]);
	}
	temp_c = c;
	while(temp_c > 0) {
		temp_c--;
		f(field[r][temp_c]);
	}
	temp_c = c;
	while(temp_c < 7) {
		temp_c++;
		f(field[r][temp_c]);
	}
}
static void remove_queen(int r, int c){
	field[r][c] = 0;
	move_queen(r,c,sub);
}

static void put_queen(int r, int c){
	//Set queens val to oo
	field[r][c] = oo;
	move_queen(r,c,add);
}

static void remember_solution(){
	stringstream sol;
	FOR(i,0,FSZ){
		FOR(j,0,FSZ){
			if(field[j][i] >= oo) sol << (j+1) << " "; 
		}
	}
	sols.push_back(sol.str());
}

static void deep_search(int qtp){
	if(qtp == 0){
		remember_solution();
		return;
	}
	int i = iter_next[qtp - 1];
	FOR(j,0,FSZ){
		if(field[i][j] == 0){
			put_queen(i,j);
			deep_search(qtp - 1);
			remove_queen(i,j);
		}
	}
}

static void print(){
	sort(all(sols)); 
	string old = "";
	FORIT(next,sols){
		if(old != *next){
			cout << *next << endl;
		}
		old = *next;
	}
	sols.clear();
}

static void read_input(void){
	int qs, x, y;
	cin >> qs;
	FOR(i,0,qs){
		cin >> x;
		cin >> y;
		put_queen(x - 1, y - 1);
		int j = 0;
		FOR(i,0,FSZ-1){
			if(i == x-1) j++;
			iter_next[i] = j;
			j++;
		}
		deep_search(7);
		print();
		if(i < qs - 1) cout << endl;
		set_zero();
	}
}

int main(){
	set_zero();
	read_input();
	return 0;
}

