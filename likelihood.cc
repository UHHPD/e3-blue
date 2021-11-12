#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu)/tgamma(k+1);
}

double prob(std::vector<int> daten, double mu) {
    double L = 1;
    for(int k : daten){
        L *= poisson(mu, k); 
    }
    return L;
}

double nll(std::vector<int> daten, double mu) {
    double L = 0;
    for(int k : daten) {
        L -= 2*log(poisson(mu, k));
    }
    return L;
}

int main() {
    // read in data
    using namespace std;
    ifstream fin("datensumme.txt");
    std::vector<int> daten;
    int n_i;
    for(int i = 0; i < 234; i++) {
        fin >> n_i;
        daten.push_back(n_i);
    }
    fin.close();

    // Likelihood
    double mu = 3.11538;
    std::cout << prob(daten, mu) << std::endl;

    // scanning likelihood
    int start = 0;
    int end = 6;
    double step = 0.1;
    ofstream fout("likelihood.txt");
    for(mu = start; mu <= end; mu += step) {
        fout << mu << " " << prob(daten, mu) << endl;
    }
    fout.close();
    
    // scanning log likelihood
    ofstream fnll("nll.txt");
    for(mu = start; mu <= end; mu += step) {
        fnll << mu << " " << nll(daten, mu) << endl;
        //fnll << mu << " " << -log(prob(daten, mu)) << endl;
    }
    fnll.close();

}
