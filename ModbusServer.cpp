#include "ModbusServer.h"
#include <iostream>
#include <unistd.h>
#include <sstream>

using namespace std;
typedef short int16_t;

void ModbusServer::printVectorDigital(string tipo, vector<bool> vect) {
    cout << tipo << " [ ";
    for (int i = 0; i < vect.size(); i++) {
        cout << vect[i] << " ";
    }
    cout << "]" << endl;
}

void ModbusServer::printVectorAnalogico(string tipo, vector<short> vect) {
    cout << tipo << " [ ";
    for (int i = 0; i < vect.size(); i++) {
        cout << vect[i] << " ";
    }
    cout << "]" << endl;
}

ModbusServer::ModbusServer() {
    // Inicializar entradas analógicas
    time_t rawtime;
    struct tm * fecha;
    time(&rawtime);
    fecha = localtime(&rawtime);

    //mktime(&fecha);
    pid_t pid, ppid;
    uid_t uid;
    gid_t gid;

    pid = getpid();
    uid = getuid();
    gid = getgid();
    ppid = getppid();

    // 6 Entradas fecha
    this->analog_input.push_back(short(fecha->tm_year + 1900));
    this->analog_input.push_back(short(fecha->tm_mon + 1));
    this->analog_input.push_back(short(fecha->tm_mday));
    this->analog_input.push_back(short(fecha->tm_hour));
    this->analog_input.push_back(short(fecha->tm_min));
    this->analog_input.push_back(short(fecha->tm_sec));
    // 4 Entradas info proceso
    this->analog_input.push_back((short)uid);
    this->analog_input.push_back((short)gid);
    this->analog_input.push_back((short)pid);
    this->analog_input.push_back((short)ppid);
    // 2 Entradas s y ms
    this->analog_input.push_back(0);
    this->analog_input.push_back(0);
    // Peticiones, bytes recibidos y bytes enviados
    this->analog_input.push_back(0);
    this->analog_input.push_back(0);
    this->analog_input.push_back(0);

    for (int i = 16; i < 20; i ++) {
        this->analog_input.push_back(short(i % 2 ? 0 : 15));
    }


    // Inicializar salidas digitales
    for (int i = 0; i < 20; i++) {
        this->digital_output.push_back(i % 2 == 0);
    }

    // Inicializar entradas digitales
    for (int i = 0; i < 20; i ++) {
        this->digital_input.push_back(i < 13 ? this->analog_input[i] % 2 == 0 : false);
    }
    // Inicializar salidas analógicas
    for (int i = 0; i < 10; i++) {
        this->analog_output.push_back(short(i * 4));
    }


}

vector<byte> ModbusServer::peticion(vector<byte> recibido) {
    byte funcion = recibido[1];

    short offset = 0;     // FIXME recoger los valores
    short posiciones = 4; // FIXME recoger los valores

    if (funcion == 0x01) { // Lectura digital { 0x06, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x7D };
        string resultado;
        for (int i = 0; i < posiciones; i++) {
            if (this->digital_output[i + offset]) {
                resultado += "1";
            } else {
                resultado += "0";
            }
        }
        cout << "resultado = " << resultado << endl;
    } else if (funcion == 0x05) {

    } else if (funcion == 0x0F) {

    } else if (funcion == 0x03) {

    } else if (funcion == 0x06) {

    } else if (funcion == 0x10) {

    } else {
        // Return ERROR 01 - Funcion no implementada
    }
}