#pragma once

#include<iostream>
#include <string>

using namespace std;

struct IP {
    string iP;
    int cantidad;

    IP();
    IP(string iP, int cantidad);
    bool operator>(IP);
    string print();
};

IP::IP() {
    iP = "";
    cantidad = 0;
}

bool IP::operator>(IP a) {
    return cantidad > a.cantidad;
}

string IP::print() {
    return iP + " " + to_string(cantidad);
}