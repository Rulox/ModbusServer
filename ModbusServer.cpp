#include "ModbusServer.h"
#include <iostream>
#include <unistd.h>
#include <sstream>

#define to_byte(num) dynamic_cast<byte> (num)

// Definición de los rangos de memoria
#define DIGITAL_OUTPUT_FROM = 1;
#define DIGITAL_OUTPUT_TO = 10000;
#define DIGITAL_INPUT_FROM = 10001;
#define DIGITAL_INPUT_TO = 20000;
#define ANALOG_INPUT_FROM = 30001;
#define ANALOG_INPUT_TO = 40000;
#define ANALOG_OUTPUT_FROM = 40001;
#define ANALOG_OUTPUT_TO = 50000;

bool ModbusServer::check_range(short from, short to, short offset, short posiciones) {
    return false;
}


vector<byte> ModbusServer::vector_to_byte(vector<short> vect) {
    byte * chunk;
    vector<byte> respuesta;
    for (int i = 0; i < vect.size(); i++) {
        short s = vect[i];
        short * ss = &s;
        chunk = reinterpret_cast<byte *>(ss);
        respuesta.push_back((*chunk));
        respuesta.push_back((*(chunk + 1)));
    }
    return respuesta;
}

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
    // 2 Entradas s y ms TODO
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

    short offset = recibido[2] + recibido[3];
    short posiciones = recibido[4] + recibido[5];
    offset = 1;
    posiciones = 1;
    if (funcion == 0x01) { // Lectura digital { 0x06, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x7D };
        string resultado;    // offset -> desde donde empiezas, Posiciones -> offset+...
        for (int i = offset; i < (offset + posiciones); i++) {
            if (this->digital_output[i]) {
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

