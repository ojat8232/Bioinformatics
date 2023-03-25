#include <iostream>
#include <string>
#include <algorithm>
#include <initializer_list>

using namespace std;


int sigma(char a, char b) 
{

    if(a == '-' and b != '-'){
        return -2;
    }

    if(a != '-' and b == '-'){
        return -2;
    }
    
    if(a != b){
        return -1;
    }

    if (a == b){
        return 1;
    }

    std::cout << "ERROR";
    return 0;
}


int main() 
{

    string s = "TTGGTCCAGATGTAGTATCGAAGTTTTTAAATCGTCATGATATGGACTTAATATGTAGAGCACATCAAGTAGTCGAAGATGGGTATGAATTTTTTGCAAAAAGACAGTTAGTTACTTTATTTTCCGCACCAAATTATTGCGGAGAATTCGACAATGCCGGAGGAATGATGAGTGTTGACGAAACTCTAATGTGCAGTTTTCAGATTTTGAAACCATCAGAGAAGAAAGCTAAATACCAGTACTTAAGTTTGAACACGGGTCAAGCCACCAGACCATCTACACCACAAAGGAATCCAGCCAAAAAGAAATGACAGCCTTGTACTCGGTTTTTCCTTCAGTTAAGGAAGCTCGTCGATAAGGCGACCAAATTTTTGTTAAGGCGCGAACATTAAGAGCATAACATTGTATGATATGTTCTATCACTAACTAGCGGTTATGCCAAACAGATGCATAGCAAAGAAAAAAAAAACAAAAAAAC";
    string t = "TCTGAAAAGTGACGGCGCGAGAGACTGATCTCTGAGAGTGACGCGAAGCTACATTTCCTCTGTGGTTGTACGTGCGATTATACGTGCGATACATTCTCAACGTTTGTGTGAAGAAATTTATTTTANATAAATAAACTTCTGTGTTTTATTATCTGATTATACATAATTAAATACATTGTGAAAAGATGCCGGAGGACGTCACCATGGCTAATGCCGGAGAGGTTGAAACTTTCGCTTTCCAAGCTGAAATTGCACAATTGATGAGTTTGATTATTAATACATTTTATTCCAATAAAGAAATTTTTATTCGAGAATTGATTTCAAATGCATCTGATGCATTAGACAAAATTCGCTATGAATCTCTCACGGATCCATCTAAATTGGATACGTGTAAGGAATTATTTATTAAAATTGTTCCTAATAAAAATGATCGTACTTTAACCATACTTGATTCTGGTATTGGTATGAACAAGGCTGATCTTGTGAACAAT";
    int m = s.length();
    int n = t.length();

    int V[m+1][n+1];
    int B[m+1][n+1];
    V[0][0] = 0;
    B[0][0] = 2;

    for (int i = 1; i <= m; i++){
        V[i][0] = V[i-1][0] + sigma(s[i-1], '-');
        B[i][0] = 1;
    }

    for (int i = 1; i <= n; i++){
        V[0][i] = V[0][i-1] + sigma('-', t[i-1]);
        B[0][i] = -1;
    }

    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){

            int a = V[i-1][j-1] + sigma(s[i-1], t[j-1]);
            int b = V[i-1][j] + sigma(s[i-1], '-');
            int c = V[i][j-1] + sigma('-', t[j-1]);

            if (a >= b && a >= c){
                B[i][j] = 0;
                V[i][j] = a;
            } else if (b >= a && b >= c){
                B[i][j] = 1;
                V[i][j] = b;
            } else{
                B[i][j] = -1;
                V[i][j] = c;
            }

        }
    }

    string a;
    string b;
    int i = m;
    int j = n;

    while (B[i][j] != 2){

        if (B[i][j] == 0){
            a += s[i-1];
            b += t[j-1];
            i--;
            j--;
        } else if (B[i][j] == 1) {  
            a += s[i-1];
            b += '-';
            i--;
        } else if (B[i][j] == -1) {
            a += '-';
            b += t[j-1];
            j--;
            
        }
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    
    cout << "The maximal score is: " << V[m][n] << "\n";
    cout << a << "\n";
    cout << b << "\n";

    return 0;
    
}


