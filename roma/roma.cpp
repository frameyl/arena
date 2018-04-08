#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int roma_power(char input)
{
    int power = 0;
    switch (input) {
        case 'I':
        case 'V':
            power = 1;
            break;
        case 'X':
        case 'L':
            power = 2;
            break;
        case 'C':
        case 'D':
            power = 3;
            break;
        case 'M':
            power = 4;
            break;
    }
    return power;
}

int roma_weight(char input)
{
    int weight = 0;
    switch (input) {
        case 'I':
        case 'X':
        case 'C':
        case 'M':
            weight = 1;
            break;
        case 'V':
        case 'L':
        case 'D':
            weight = 5;
            break;
    }
    return weight;
}

int roma_digit(string input, int& digit)
{
    int n = 0;
    int current_power=0, previous_power=0;
    int current_weight=0, previous_weight=0;
    digit = 0;

    while (n < input.length())
    {
        current_power = roma_power(input[n]);
        current_weight = roma_weight(input[n]);
        if (n > 0) {
            if (current_power == previous_power) {
                if(current_weight == 5) {
                    digit = (5 - digit);
                    n++;
                    break;
                } else {
                    digit++;
                }
            } else if (current_power == previous_power+1) {
                digit = (10 - digit);
                n++;
                break;
            } else {
                break;
            }
        } else {
            digit = current_weight;
        }

        n++;
        previous_power = current_power;
        previous_weight = current_weight;
    }

    digit = digit * pow(10, previous_power-1);
    return n;
}

int roma_number(string input)
{
    int n = 0;
    int number = 0;

    while (n < input.length()) {
        int digit;
        int barry;
        string sub = input.substr(n, string::npos);
        barry = roma_digit(sub, digit);
        cout << input.substr(n, barry) << " | ";
        cout << digit << " # ";
        n += barry;
        number += digit;
    }

    cout << "\n";
    return number;
}

int main()
{
    string temp;
    cout << "Please input the Roma number: ";
    cin >> temp;
    cout << "input string: " << temp << "\n";
    cout << "translated number: " << roma_number(temp) << "\n";

    //out << "debug:" << (4 * 10^0) << "\n";
    return 0;
}
