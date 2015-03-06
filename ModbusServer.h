#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

#include <vector>
#include <stdint.h>
#include <iostream>

using namespace std;

typedef unsigned char byte;
//int16_t;

class ModbusServer {

public:
    ModbusServer();

    void printVectorDigital(string tipo, vector<bool>);
    void printVectorAnalogico(string tipo, vector<short>);
    vector<byte> peticion(vector<byte> recibido);
    vector<byte> vector_to_byte(vector<short> vect);
    bool check_range(short from, short to, short offset, short posiciones);
    short bin_to_short(string binario);
    // Declarar int to bytes y bytes to int

    vector<bool> digital_output;
    vector<bool> digital_input;
    vector<short> analog_output;
    vector<short> analog_input;
};

#endif