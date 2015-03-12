#include "ModbusServer.h"
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string.h>
#include <sys/types.h>

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

ModbusServer::ModbusServer(int id) {
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
    printVectorDigital("Digital Output ->", digital_output);
    printVectorDigital("Digital Input ->", digital_input);
    printVectorAnalogico("Analog Output -> ", analog_output);
    printVectorAnalogico("Analog Input -> ", analog_input);
    //recibido =  { 0x06, 0x10, 0x00, 0x00, 0x00, 0x01, 0x02, 0x13, 0x00, 0x8D, 0x50 };

    byte funcion = recibido[1];

    vector<byte> vector_respuesta;
    vector<byte> crc_respuesta;


    if (funcion == 0x01) { // Lectura digital { 0x06, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x7D };
        vector_respuesta.push_back(recibido[0]);
        vector_respuesta.push_back(funcion);

        int offset = bytes_to_short(recibido[2], recibido[3]);
        int posiciones = bytes_to_short(recibido[4], recibido[5]);

        string resultado;    // offset -> desde donde empiezas, Posiciones -> offset+...
        for (int i = offset; i < (offset + posiciones); i++) {
            resultado += this->digital_output[i] ? "1" : "0";
        }

        short res_short = bin_to_short(resultado);

        vector_respuesta.push_back(res_short);
        vector_respuesta.push_back(1);   // FIXME
        crc_respuesta = crc16(vector_respuesta);
        vector_respuesta.push_back(crc_respuesta[0]);
        vector_respuesta.push_back(crc_respuesta[1]);

    } else if (funcion == 0x05) {  // Escritura salida digital { 0x06, 0x05, 0x00, 0x13, 0xFF, 0x00, 0x7C, 0x48 };
                                    // RESPUESTA { 0x06, 0x05, 0x00, 0x13, 0xFF, 0x00, 0x7C, 0x48 };
        int offset = bytes_to_short(recibido[2], recibido[3]);
        digital_output[offset] = bytes_to_short(recibido[4], recibido[5] == 65280) != 0;
        vector_respuesta = recibido;

    } else if (funcion == 0x0F) {  // Escritura múltiple salida digital { 0x06, 0x0F, 0x00, 0x08, 0x00, 0x01, 0x01, 0x00, 0x8E, 0xB0 };
                                // Respuesta { 0x06, 0x0F, 0x00, 0x08, 0x00, 0x01, 0x14, 0x7E };
        vector_respuesta.push_back(recibido[0]);
        vector_respuesta.push_back(funcion);      // TODO

        int offset = bytes_to_short(recibido[2], recibido[3]);
        int posiciones = bytes_to_short(recibido[4], recibido[5]);
        int ndatos = recibido [6];
        int datos = bytes_to_short(recibido[7], recibido[8]);

        vector_respuesta.push_back(recibido[2]);
        vector_respuesta.push_back(recibido[3]);
        vector_respuesta.push_back(recibido[4]);
        vector_respuesta.push_back(recibido[5]);
        crc_respuesta = crc16(vector_respuesta);
        vector_respuesta.push_back(crc_respuesta[0]);
        vector_respuesta.push_back(crc_respuesta[1]);

    } else if (funcion == 0x03) { //{ 0x06, 0x03, 0x00, 0x02, 0x00, 0x06, 0x65, 0xBF };
//{ 0x06, 0x03, 0x0C, 0x00, 0x08, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x14, 0x00, 0x18, 0x00, 0x1C, 0x0B, 0x1E };
        vector_respuesta.push_back(recibido[0]);
        vector_respuesta.push_back(funcion);
        int offset = bytes_to_short(recibido[2], recibido[3]);
        int posiciones = bytes_to_short(recibido[4], recibido[5]);
        vector_respuesta.push_back(2 * posiciones);
        for (int i = offset; i < (offset + posiciones); i++) {
            vector<byte> bytes = short_to_bytes(analog_output[i]);
            vector_respuesta.push_back(bytes[0]);
            vector_respuesta.push_back(bytes[1]);
        }
        crc_respuesta = crc16(vector_respuesta);
        vector_respuesta.push_back(crc_respuesta[0]);
        vector_respuesta.push_back(crc_respuesta[1]);

    } else if (funcion == 0x06) { // { 0x06, 0x06, 0x00, 0x04, 0x03, 0x10, 0xC8, 0x80 }; same
        vector_respuesta = recibido;
    } else if (funcion == 0x10) { //  { 0x06, 0x10, 0x00, 0x00, 0x00, 0x01, 0x02, 0x13, 0x00, 0x8D, 0x50 };
        //{ 0x06, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x7E };
        vector_respuesta.push_back(recibido[0]);
        vector_respuesta.push_back(funcion);
        int offset = bytes_to_short(recibido[2], recibido[3]);
        int posiciones = bytes_to_short(recibido[4], recibido[5]);
        int ndatos = recibido[6];
        int indice = 7;
        vector_respuesta.push_back(recibido[2]);
        vector_respuesta.push_back(recibido[3]);
        vector_respuesta.push_back(recibido[4]);
        vector_respuesta.push_back(recibido[5]);
        crc_respuesta = crc16(vector_respuesta);
        vector_respuesta.push_back(crc_respuesta[0]);
        vector_respuesta.push_back(crc_respuesta[1]);

        for (int i = offset; i < (offset + posiciones); i++) {
            analog_output[i] = bytes_to_short(recibido[indice], recibido[indice + 1]);
            indice += 2;
        }

    }
/*
    cout << " RESULTADO = { ";
    for (int i = 0; i < vector_respuesta.size(); i++)
        cout << (int)vector_respuesta[i] << ", ";
    cout << " }";*/
    return vector_respuesta;
}

short ModbusServer::bin_to_short(string binario) {
    char bin[1024];
    strcpy(bin, binario.c_str());
    char * end;
    long value = strtol (bin, &end, 2);
    return (short)value;
}


byte ModbusServer::short_to_byte(short num) {
    return (byte)(num >> 4);
}



vector<byte> ModbusServer::short_to_bytes(short num) {
    vector<byte> resultado;
    resultado.push_back((byte)(num >> 8));
    resultado.push_back((byte)num);
    return resultado;
}

int16_t ModbusServer::bytes_to_short(int byte1, int byte2) {
    return (int16_t) byte2 + (int16_t)(byte1 <<8);
}


vector<byte>  ModbusServer::crc16( vector<byte> mensaje, int len) {
#define POLY 0xA001
    int i;
    unsigned int crc=0xFFFF;
    for(int ba=0; ba<len; ba++) {
        crc ^= mensaje[ba];
        for(i=0; i<8; i++) {
            if( crc & 0x0001 ) {
                crc = (crc>>1) ^ POLY;
            } else {
                crc >>= 1;
            }
        }
    }
    vector<byte> codr;
    codr.push_back(crc & 0xff);
    codr.push_back(crc >> 8);
    return codr;
}

/*! Calcula el código CRC-16 de TODOS los bytes del vector
 * \param mensaje vector de bytes de trabajo
 * \return vector con los dos bytes del CRC en el orden "correcto"
 */
vector<byte>  ModbusServer::crc16( vector<byte> mensaje) {
    return crc16( mensaje, mensaje.size() );
}

