#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

double sum(vector<double> v){
    double ret = 0;
    for(int i = 0; i<v.size(); i++){
        ret+=v[i];
    }
    return ret;
}

double mean(vector<double> v){
    return sum(v)/v.size();
}

double median(vector<double> v){
    sort(v.begin(), v.end());
    if(v.size()%2==0){
        return v[v.size()/2];
    }else{
        double dm1 = v[v.size()/2]-1;
        double dm2 = v[v.size()/2];
        return (dm1+dm2)/2;
    }
}

double range(vector<double> v){
    sort(v.begin(), v.end());
    double min = v[0];
    double max = v[v.size()-1];
    return max-min;
}

double cov(vector<double> rm, vector<double> medv){
    double sigma = 0;
    double rmmean = mean(rm);
    double medvmean = mean(medv);
    for(int i = 0; i<rm.size(); i++){
        sigma += (rm[i]-rmmean)*(medv[i]-medvmean);
    }
    return sigma / (rm.size()-1);
}

double standdev(vector<double> v){
    double ret;
    double sigma = 0;
    double meanv = mean(v);
    for(int i = 0; i<v.size(); i++){
        sigma += pow((v[i]-meanv),2);
    }
    ret = sigma/(v.size()-1);
    ret = pow(ret,0.5);
    return ret;
}

double corr(vector<double> rm, vector<double> medv){
    return cov(rm, medv)/(standdev(rm)*standdev(medv));
}

int main()
{
    vector<double> rm;
    vector<double> medv;
    string line; // stores each line being read
    stringstream ss; // used to convert string to double
    string s1,s2; // s1 stores rm substr, s2 stores medv substr
    double d1,d2; //d1 stores rm value, d2 stores medv value
    ifstream file("data.csv");
    getline(file,line); //we dont need the first line
    if(file.is_open()){
        while(getline(file,line)){
            s1 = line.substr(0,line.find(","));
            s2 = line.substr(line.find(",")+1);
            ss<<s1;
            ss>>d1;
            ss.clear();
            ss<<s2;
            ss>>d2;
            ss.clear();
            rm.push_back(d1);
            medv.push_back(d2);
        }
        file.close();
    }else{
        cout << "Could not open file" << endl;
    }
    
    cout<<"rm sum - "<<sum(rm)<<endl;
    cout<<"medv sum - "<<sum(medv)<<endl;
    cout<<"rm mean - "<<mean(rm)<<endl;
    cout<<"medv mean - "<<mean(medv)<<endl;
    cout<<"rm median - "<<median(rm)<<endl;
    cout<<"medv median - "<<median(medv)<<endl;
    cout<<"rm range - "<<range(rm)<<endl;
    cout<<"medv range - "<<range(medv)<<endl;

    cout<<"Covariance between rm and medv: "<<cov(rm, medv)<<endl;
    cout<<"Correlation between rm and medv: "<<corr(rm,medv)<<endl;

    return 0;
}


