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

double self_prob(std::vector<int> daten) {
    double L =1;
    for(int k: daten) {
        L *= poisson(k, k);
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
    double step = 0.01;
    ofstream fout("likelihood.txt");
    for(mu = start; mu <= end; mu += step) {
        fout << mu << " " << prob(daten, mu) << endl;
    }
    fout.close();
    
    // scanning log likelihood
    ofstream fnll("nll.txt");
    ofstream f_delta("deltanll.txt");
    std::vector<double> nll_values;
    for(mu = start; mu <= end; mu += step) {
        fnll << mu << " " << nll(daten, mu) << endl;
        nll_values.push_back(nll(daten, mu));
        f_delta << mu << " " << nll(daten, mu) - nll(daten, 3.11538) << endl;
    }
    fnll.close();
    f_delta.close();

    // determine best mu
    ifstream nll_in("nll.txt");
    double nll_i;
    double min = 100000;
    int min_ind = 0;
    for(int n = 0; n <= (end-start)/step; n++){
        if(nll_values[n] < min) {
            min = nll_values[n];
            min_ind = n;
        }
    }
    std::cout << "best guess for mu: " << start + min_ind * step << std::endl;

    // likelihood ratio
    double Lambda = prob(daten, 3.11538) / self_prob(daten);
    double logLambda = -2*log(Lambda);
    std::cout << "likelihood ratio: " << logLambda << std::endl; 

    // deviation of likelihood ratio:
    double z = (logLambda - 233)/sqrt(2*233);
    std::cout << "deviation of likelihood ratio: " << z << std::endl;
}
