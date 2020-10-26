#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Registro
{
    int id;
    int iMes;
    int iDia;
    int iHora;
    int iMin;
    int iSeg;
    string sIp;
    string sFalla;

    Registro();
    Registro(int,int,int,int,int,int,string,string);

    void calcularId();
    int findMes(string);

    string findDia(int);
    string print();
    
    bool operator<(Registro e);
    bool operator<=(Registro e);
    bool operator>(Registro e);
};


Registro::Registro() {
    id = 0;
    iMes = 0;
    iDia = 0;
    iHora = 0;
    iMin = 0;
    iSeg = 0;
    sIp = "";
    sFalla = "";
}

Registro::Registro(int iD,int mes,int dia,int hora, int min, int seg,string ip,string falla) {
    id = iD;
    iMes = mes;
    iDia = dia;
    iHora = hora;
    iMin = min;
    iSeg = seg;
    sIp = ip;
    sFalla = falla;
}

void Registro :: calcularId() {
    id = (iMes * 100000000) + (iDia * 1000000) + (iHora * 10000) + (iMin * 100) + (iSeg);
}

int Registro :: findMes(string mes)
{
    if(mes == "Jan") {
        return 1;
    }
    else if(mes == "Feb") {
        return 2;
    }
    else if(mes == "Mar") {
        return 3;
    }
    else if(mes == "Apr") {
        return 4;
    }
    else if(mes == "May") {
        return 5;
    }
    else if(mes == "Jun") {
        return 6;
    }
    else if(mes == "Jul") {
        return 7;
    }
    else if(mes == "Aug") {
        return 8;
    }
    else if(mes == "Sep") {
        return 9;
    }
    else if(mes == "Oct") {
        return 10;
    }
    else if(mes == "Nov") {
        return 11;
    }
    else if(mes == "Dec") {
        return 12;
    }

    return -1;
}

string Registro :: findDia(int mes)
{
    if(mes == 1) {
        return "Jan";
    }
    else if(mes == 2) {
        return "Feb";
    }
    else if(mes == 3) {
        return "Mar";
    }
    else if(mes == 4) {
        return "Apr";
    }
    else if(mes == 5) {
        return "May";
    }
    else if(mes == 6) {
        return "Jun";
    }
    else if(mes == 7) {
        return "Jul";
    }
    else if(mes == 8) {
        return "Aug";
    }
    else if(mes == 9) {
        return "Sep";
    }
    else if(mes == 10) {
        return "Oct";
    }
    else if(mes == 11) {
        return "Nov";
    }
    else if(mes == 12) {
        return "Dec";
    }
    return "";
}

string Registro :: print() {
    return  findDia(iMes) + " " + to_string(iDia) + " " + to_string(iHora) + ":" + to_string(iMin) + ":" + to_string(iSeg) + " " + sIp + " " +  sFalla;
}

bool Registro :: operator<(Registro e) {
    if (sIp < e.sIp) {
        return true;
    }
    return false;
}

bool Registro :: operator>(Registro e) {
    if (sIp > e.sIp) {
        return true;
    }
    return false;
}

bool Registro :: operator<=(Registro e) {
    if (sIp <= e.sIp) {
        return true;
    }
    return false;
}