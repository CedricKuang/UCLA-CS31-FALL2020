

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string type;
    double value;
    string importer;
    double duty;

    cout << "Cheese type: ";
    getline(cin, type);
    if (type == "")
    {
        cout << "---" << endl;
        cout << "You must enter a cheese type" << endl;
        return 1;
    }

    cout << "Value: ";
    cin >> value;
    if (value <= 0)
    {
        cout << "---" << endl;
        cout << "The value must be positive" << endl;
        return 1;
    }

    cin.ignore(10000, '\n');
    cout << "Importer: ";
    getline(cin, importer);
    if (importer == "")
    {
        cout << "---" << endl;
        cout << "You must enter an importer" << endl;
        return 1;
    }

    if (value <= 1000)
        duty = value * 0.011;
    else if (value > 1000 && value <= 13000)
    {
        if (type == "cheshire" || type == "stilton")
            duty = 11 + (value - 1000) * 0.014;
        else
            duty = 11 + (value - 1000) * 0.02;
    }
    else if (value > 13000)
    {
        if (type == "cheshire" || type == "stilton")
            duty = 179 + (value - 13000) * 0.029;
        else
            duty = 251 + (value - 13000) * 0.029;
    }

    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "---\n";
    cout << "The import duty for " << importer << " is $" << duty << endl;
}


