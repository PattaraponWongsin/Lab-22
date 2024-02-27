#include <iostream>
using namespace std;

double averageDouble(double* numbers, int len) {
    double sum = 0.0;
    for (int i = 0; i < len; i++) {
        sum += numbers[i];
    }
    return sum / len;
}

int main (int argc, char** argv) {
    int len = argc - 1;
    if (len < 1) {
        cout << "Please input numbers to find average.";
    } 
    else {
        double numbers[len];
        
        for (int i = 0; i < len; i++) {
            numbers[i] = atof(argv[i+1]);
        }
        
        double average = averageDouble(numbers, len);
        cout << "---------------------------------\n";
        cout << "Average of " << len << " numbers = " << average << "\n";
        cout << "---------------------------------\n";
    }
    
    return 0;
}
