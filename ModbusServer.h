#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

#include <vector>
#include <stdint.h>
#include <iostream>

using namespace std;

typedef unsigned char byte;
typedef short int16_t;

class ModbusServer {

public:
    ModbusServer();

    void printVectorDigital(string tipo, vector<bool>);
    void printVectorAnalogico(string tipo, vector<short>);
    vector<byte> peticion(vector<byte> recibido);

    vector<bool> digital_output;
    vector<bool> digital_input;
    vector<short> analog_output;
    vector<short> analog_input;
};

#endif