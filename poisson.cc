#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu) / tgamma(k+1);
}

int main() {
    using namespace std;

    ifstream fin("datensumme.txt");
    int n_i;
    
    vector<int> zaehler(11);
    
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        zaehler[n_i]++;
    }

    for(int k = 0 ; k < zaehler.size() ; ++k) {
    	cout << k << " " << zaehler[k] << std::endl;
    }
    
    
    fin.close();
    ofstream fout("hist.txt"); 
    ofstream poi_out("histpoi.txt");
    double mu = 3.11538;
    for(unsigned int k = 0 ; k < zaehler.size() ; ++k) {
    	fout << k << " " << zaehler[k] << endl;
        poi_out << k << " " << zaehler[k] << " " << poisson(mu, k) * 234 << endl; 
    }
    fout.close();
    poi_out.close();
}
