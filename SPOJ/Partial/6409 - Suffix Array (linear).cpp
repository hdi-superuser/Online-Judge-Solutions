#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXLEN 100050

int a[3 * MAXLEN],sa[3 * MAXLEN],R[MAXLEN],R2[MAXLEN],cont[MAXLEN],c[MAXLEN];

bool eq(int *r, int a, int b){
    return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}

bool comp(int k, int *r, int a, int b){
    if (k == 2) return r[a] < r[b] || (r[a] == r[b] && comp(1, r, a + 1, b + 1));
    else return r[a] < r[b] || (r[a] == r[b] && c[a + 1] < c[b + 1]);
}

void radix(int *r, int *a, int *b, int n, int K){
    for(int i = 0;i < K;++i) cont[i] = 0;
    for(int i = 0;i < n;++i) ++cont[ r[ a[i] ] ];
    for(int i = 1;i < K;++i) cont[i] += cont[i - 1];
    for(int i = n - 1;i >= 0;--i) b[ --cont[ r[ a[i] ] ] ] = a[i];
}

#define F(x) ((x) / 3 + ((x) % 3 == 1? 0 : n1))
#define G(x) (((x) >= n1)?((x) - n1) * 3 + 2 : (x) * 3  + 1)

void dc3(int *a, int *sa, int n, int K){
    int *an = a + n,*san = sa + n,n0 = 0,n1 = (n + 1) / 3,n12 = 0,pos = 1;
    a[n] = a[n + 1] = 0;
    
    for(int i = 1;i < n;++i)
        if(i % 3 != 0) R[n12++] = i;
    
    radix(a + 2,R,R2,n12,K);
    radix(a + 1,R2,R,n12,K);
    radix(a + 0,R,R2,n12,K);
    
    an[ F(R2[0]) ] = 0;
    
    for(int i = 1;i < n12;++i)
        an[ F(R2[i]) ] = eq(a,R2[i - 1],R2[i])? pos - 1 : pos++;
    
    if(pos < n12) dc3(an,san,n12,pos);
    else for(int i = 0;i < n12;++i) san[ an[i] ] = i;
    
    for(int i = 0;i < n12;++i)
        if(san[i] < n1) R2[n0++] = san[i] * 3;
    
    if(n % 3 == 1) R2[n0++] = n - 1;
    
    radix(a,R2,R,n0,K);
    
    for(int i = 0;i < n12;++i) c[R2[i] = G(san[i])] = i;
    
    int x = 0,y = 0,p = 0;
    
    while(x < n0 && y < n12)
        sa[p++] = comp(R2[y] % 3,a,R[x],R2[y])? R[x++] : R2[y++];
    
    while(x < n0) sa[p++] = R[x++];
    while(y < n12) sa[p++] = R2[y++];
}

char s[MAXLEN + 1];

int main(){
    scanf("%s",s);
    int n = strlen(s);
    
    for(int i = 0;i < n;++i)
        a[i] = s[i];
        
    a[n++] = 0;
    
    dc3(a,sa,n,'z' + 1);
    
    for(int i = 1;i < n;++i)
        printf("%d\n",sa[i]);
    
    return 0;
}
