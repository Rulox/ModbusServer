#include <iostream>
#include "ModbusServer.h"

using namespace std;

int main() {

    ModbusServer modbus(6); // Inicializamos
    modbus.printVectorDigital("Digital Output ->", modbus.digital_output);
    modbus.printVectorDigital("Digital Input ->", modbus.digital_input);
    modbus.printVectorAnalogico("Analog Output -> ", modbus.analog_output);
    modbus.printVectorAnalogico("Analog Input -> ", modbus.analog_input);
    vector<byte> peti = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x7D };
    modbus.peticion(peti);
    return 0;
}