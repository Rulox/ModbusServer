/**
 * Programa de prueba de la parte básica de la práctica 3
 *
 * \author Alberto Hamilton Castro
 */

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "ModbusServer.hpp"

#define ID_DEV  6

//si vale 0 se haran todas las pruebas aunque fallen
//si vale 1 se parará desde que falle la primera
int SalSiFallo = 1;

#define BVEC(v) vector<byte>( v, v + sizeof(v)/sizeof(byte) )

typedef unsigned char byte;

using namespace std;


ostream& operator<<(ostream &os, const vector<byte> &v) {
  os << "[("  << v.size() << ") " << setfill('0') << hex ;
  for ( unsigned int ba = 0; ba < v.size(); ba++)
    os << setw(2) << (int)v[ba] << ' ';
  os << "] " << dec;
  return os;
}

int testea(ModbusServer &mbs
  , string titulo, vector<byte> peticion
  , vector<byte> respuestaOK) {

  vector<byte> respuesta = mbs.peticion( peticion );

  if( respuesta != respuestaOK ) {
    cout << "Error en el dialogo: " ;
    cout << "enviamos " << peticion << ", ";
    cout << "la respuesta debería ser " << respuestaOK
      << " pero es " << respuesta << endl;
    cout << "Test '" << titulo << "' ---> FALLO\n" << endl;
    if (SalSiFallo) {
      exit(1);
    }
    return 0;
  }

  cout << "Test '" << titulo << "' ---> CORRECTO\n" << endl;
  return 1;
}

int main (int argc, char *argv[]) {

  //Procesamos parámetros de entrada para fijar SalSiFallo
  if( (argc > 1) ) {
    char* ptfin;
    long int val=strtol( argv[1], &ptfin, 10);
    if ( ptfin==argv[1] ) {
      cerr << "Primer parámetro '"<< argv[1] <<"' no parece entero" << endl;
      exit(2);
    }
    if ( (val!=0)  && (val!=1) ) {
      cerr << "El parametro debe ser 0 ó 1" << endl;
      exit(2);
    }
    SalSiFallo = val;
  }



  ModbusServer mbs(ID_DEV);

  //mensajes de prueba
  int tot=0, ok=0;

  // ==========================================================
  //Código generado automaticamente
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x00, 0x00, 0x01, 0x85, 0xBD };
    byte resp[] = { 0x06, 0x03, 0x02, 0x00, 0x00, 0x0D, 0x84 };
    ok += testea(mbs, "Leemos las salidas analogicas de la 1 a la 1", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD4, 0x7D };
    byte resp[] = { 0x06, 0x03, 0x02, 0x00, 0x04, 0x0C, 0x47 };
    ok += testea(mbs, "Leemos las salidas analogicas de la 2 a la 2", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x09, 0x00, 0x01, 0x55, 0xBF };
    byte resp[] = { 0x06, 0x03, 0x02, 0x00, 0x24, 0x0D, 0x9F };
    ok += testea(mbs, "Leemos las salidas analogicas de la 10 a la 10", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC5, 0xBC };
    byte resp[] = { 0x06, 0x03, 0x04, 0x00, 0x00, 0x00, 0x04, 0x8D, 0x30 };
    ok += testea(mbs, "Leemos las salidas analogicas de la 1 a la 2", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x02, 0x00, 0x06, 0x65, 0xBF };
    byte resp[] = { 0x06, 0x03, 0x0C, 0x00, 0x08, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x14, 0x00, 0x18, 0x00, 0x1C, 0x0B, 0x1E };
    ok += testea(mbs, "Leemos las salidas analogicas de la 3 a la 8", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x00, 0x00, 0x0A, 0xC4, 0x7A };
    byte resp[] = { 0x06, 0x03, 0x14, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x14, 0x00, 0x18, 0x00, 0x1C, 0x00, 0x20, 0x00, 0x24, 0x7D, 0xA8 };
    ok += testea(mbs, "Leemos las salidas analogicas de la 1 a la 10", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x7D };
    byte resp[] = { 0x06, 0x01, 0x01, 0x01, 0x91, 0x3C };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 1", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x01, 0x00, 0x01, 0xAD, 0xBD };
    byte resp[] = { 0x06, 0x01, 0x01, 0x00, 0x50, 0xFC };
    ok += testea(mbs, "Leemos las salidas digitales de la 2 a la 2", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x02, 0x00, 0x08, 0x9D, 0xBB };
    byte resp[] = { 0x06, 0x01, 0x01, 0x55, 0x90, 0xC3 };
    ok += testea(mbs, "Leemos las salidas digitales de la 3 a la 10", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x09, 0x00, 0x0B, 0xAC, 0x78 };
    byte resp[] = { 0x06, 0x01, 0x02, 0xAA, 0x02, 0xF3, 0x5D };
    ok += testea(mbs, "Leemos las salidas digitales de la 10 a la 20", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x14, 0x3D, 0xB2 };
    byte resp[] = { 0x06, 0x01, 0x03, 0x55, 0x55, 0x05, 0xD2, 0xBA };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 20", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x05, 0x00, 0x00, 0x00, 0x00, 0xCC, 0x7D };
    byte resp[] = { 0x06, 0x05, 0x00, 0x00, 0x00, 0x00, 0xCC, 0x7D };
    ok += testea(mbs, "Formazos salida digital unica 1 a valor 0", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x14, 0x3D, 0xB2 };
    byte resp[] = { 0x06, 0x01, 0x03, 0x54, 0x55, 0x05, 0x83, 0x7A };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 20", BVEC(peti), BVEC(resp) );
    //Salidas digitales valen ahora [0 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x05, 0x00, 0x01, 0xFF, 0x00, 0xDC, 0x4D };
    byte resp[] = { 0x06, 0x05, 0x00, 0x01, 0xFF, 0x00, 0xDC, 0x4D };
    ok += testea(mbs, "Formazos salida digital unica 2 a valor 1", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x14, 0x3D, 0xB2 };
    byte resp[] = { 0x06, 0x01, 0x03, 0x56, 0x55, 0x05, 0x22, 0xBA };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 20", BVEC(peti), BVEC(resp) );
    //Salidas digitales valen ahora [0 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x05, 0x00, 0x09, 0xFF, 0x00, 0x5D, 0x8F };
    byte resp[] = { 0x06, 0x05, 0x00, 0x09, 0xFF, 0x00, 0x5D, 0x8F };
    ok += testea(mbs, "Formazos salida digital unica 10 a valor 1", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x14, 0x3D, 0xB2 };
    byte resp[] = { 0x06, 0x01, 0x03, 0x56, 0x57, 0x05, 0x23, 0xDA };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 20", BVEC(peti), BVEC(resp) );
    //Salidas digitales valen ahora [0 1 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x05, 0x00, 0x04, 0x00, 0x00, 0x8D, 0xBC };
    byte resp[] = { 0x06, 0x05, 0x00, 0x04, 0x00, 0x00, 0x8D, 0xBC };
    ok += testea(mbs, "Formazos salida digital unica 5 a valor 0", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x14, 0x3D, 0xB2 };
    byte resp[] = { 0x06, 0x01, 0x03, 0x46, 0x57, 0x05, 0x22, 0x1F };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 20", BVEC(peti), BVEC(resp) );
    //Salidas digitales valen ahora [0 1 1 0 0 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x05, 0x00, 0x13, 0xFF, 0x00, 0x7C, 0x48 };
    byte resp[] = { 0x06, 0x05, 0x00, 0x13, 0xFF, 0x00, 0x7C, 0x48 };
    ok += testea(mbs, "Formazos salida digital unica 20 a valor 1", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x14, 0x3D, 0xB2 };
    byte resp[] = { 0x06, 0x01, 0x03, 0x46, 0x57, 0x0D, 0x23, 0xD9 };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 20", BVEC(peti), BVEC(resp) );
    //Salidas digitales valen ahora [0 1 1 0 0 0 1 0 1 1 1 0 1 0 1 0 1 0 1 1]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x0F, 0x00, 0x08, 0x00, 0x01, 0x01, 0x00, 0x8E, 0xB0 };
    byte resp[] = { 0x06, 0x0F, 0x00, 0x08, 0x00, 0x01, 0x14, 0x7E };
    ok += testea(mbs, "Formazos salidas digitales de la 9 a la 9 a los valores 0", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x14, 0x3D, 0xB2 };
    byte resp[] = { 0x06, 0x01, 0x03, 0x46, 0x56, 0x0D, 0x22, 0x49 };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 20", BVEC(peti), BVEC(resp) );
    //Salidas digitales valen ahora [0 1 1 0 0 0 1 0 0 1 1 0 1 0 1 0 1 0 1 1]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x0F, 0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x0F, 0x71 };
    byte resp[] = { 0x06, 0x0F, 0x00, 0x00, 0x00, 0x03, 0x14, 0x7D };
    ok += testea(mbs, "Formazos salidas digitales de la 1 a la 3 a los valores [1 0 0]", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x14, 0x3D, 0xB2 };
    byte resp[] = { 0x06, 0x01, 0x03, 0x41, 0x56, 0x0D, 0x93, 0x88 };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 20", BVEC(peti), BVEC(resp) );
    //Salidas digitales valen ahora [1 0 0 0 0 0 1 0 0 1 1 0 1 0 1 0 1 0 1 1]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x0F, 0x00, 0x04, 0x00, 0x06, 0x01, 0x1B, 0x6F, 0x7B };
    byte resp[] = { 0x06, 0x0F, 0x00, 0x04, 0x00, 0x06, 0x95, 0xBF };
    ok += testea(mbs, "Formazos salidas digitales de la 5 a la 10 a los valores [1 1 0 1 1 0]", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x14, 0x3D, 0xB2 };
    byte resp[] = { 0x06, 0x01, 0x03, 0xB1, 0x55, 0x0D, 0x93, 0x4B };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 20", BVEC(peti), BVEC(resp) );
    //Salidas digitales valen ahora [1 0 0 0 1 1 0 1 1 0 1 0 1 0 1 0 1 0 1 1]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x0F, 0x00, 0x09, 0x00, 0x0B, 0x02, 0x55, 0x01, 0x3C, 0xFD };
    byte resp[] = { 0x06, 0x0F, 0x00, 0x09, 0x00, 0x0B, 0xC5, 0xB9 };
    ok += testea(mbs, "Formazos salidas digitales de la 10 a la 20 a los valores [1 0 1 0 1 0 1 0 1 0 0]", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x14, 0x3D, 0xB2 };
    byte resp[] = { 0x06, 0x01, 0x03, 0xB1, 0xAB, 0x02, 0x93, 0x2F };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 20", BVEC(peti), BVEC(resp) );
    //Salidas digitales valen ahora [1 0 0 0 1 1 0 1 1 1 0 1 0 1 0 1 0 1 0 0]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x0F, 0x00, 0x00, 0x00, 0x14, 0x03, 0x4E, 0x54, 0x0D, 0x7E, 0xBD };
    byte resp[] = { 0x06, 0x0F, 0x00, 0x00, 0x00, 0x14, 0x54, 0x73 };
    ok += testea(mbs, "Formazos salidas digitales de la 1 a la 20 a los valores [0 1 1 1 0 0 1 0 0 0 1 0 1 0 1 0 1 0 1 1]", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x01, 0x00, 0x00, 0x00, 0x14, 0x3D, 0xB2 };
    byte resp[] = { 0x06, 0x01, 0x03, 0x4E, 0x54, 0x0D, 0xA2, 0xEB };
    ok += testea(mbs, "Leemos las salidas digitales de la 1 a la 20", BVEC(peti), BVEC(resp) );
    //Salidas digitales valen ahora [0 1 1 1 0 0 1 0 0 0 1 0 1 0 1 0 1 0 1 1]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x06, 0x00, 0x00, 0x03, 0x00, 0x88, 0x8D };
    byte resp[] = { 0x06, 0x06, 0x00, 0x00, 0x03, 0x00, 0x88, 0x8D };
    ok += testea(mbs, "Formazos salida analogica unica 1 a valor 768", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x00, 0x00, 0x0A, 0xC4, 0x7A };
    byte resp[] = { 0x06, 0x03, 0x14, 0x03, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x14, 0x00, 0x18, 0x00, 0x1C, 0x00, 0x20, 0x00, 0x24, 0x39, 0x9B };
    ok += testea(mbs, "Leemos las salidas analogicas de la 1 a la 10", BVEC(peti), BVEC(resp) );
    //Salidas analogicas valen ahora [768 4 8 12 16 20 24 28 32 36]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x06, 0x00, 0x09, 0x03, 0x24, 0x58, 0x94 };
    byte resp[] = { 0x06, 0x06, 0x00, 0x09, 0x03, 0x24, 0x58, 0x94 };
    ok += testea(mbs, "Formazos salida analogica unica 10 a valor 804", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x00, 0x00, 0x0A, 0xC4, 0x7A };
    byte resp[] = { 0x06, 0x03, 0x14, 0x03, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x14, 0x00, 0x18, 0x00, 0x1C, 0x00, 0x20, 0x03, 0x24, 0x39, 0x6B };
    ok += testea(mbs, "Leemos las salidas analogicas de la 1 a la 10", BVEC(peti), BVEC(resp) );
    //Salidas analogicas valen ahora [768 4 8 12 16 20 24 28 32 804]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x06, 0x00, 0x04, 0x03, 0x10, 0xC8, 0x80 };
    byte resp[] = { 0x06, 0x06, 0x00, 0x04, 0x03, 0x10, 0xC8, 0x80 };
    ok += testea(mbs, "Formazos salida analogica unica 5 a valor 784", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x00, 0x00, 0x0A, 0xC4, 0x7A };
    byte resp[] = { 0x06, 0x03, 0x14, 0x03, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0C, 0x03, 0x10, 0x00, 0x14, 0x00, 0x18, 0x00, 0x1C, 0x00, 0x20, 0x03, 0x24, 0x3D, 0x6F };
    ok += testea(mbs, "Leemos las salidas analogicas de la 1 a la 10", BVEC(peti), BVEC(resp) );
    //Salidas analogicas valen ahora [768 4 8 12 784 20 24 28 32 804]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x10, 0x00, 0x00, 0x00, 0x01, 0x02, 0x13, 0x00, 0x8D, 0x50 };
    byte resp[] = { 0x06, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x7E };
    ok += testea(mbs, "Formazos salidas analogicas de la 1 a la 1 a los valores 4864", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x00, 0x00, 0x0A, 0xC4, 0x7A };
    byte resp[] = { 0x06, 0x03, 0x14, 0x13, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0C, 0x03, 0x10, 0x00, 0x14, 0x00, 0x18, 0x00, 0x1C, 0x00, 0x20, 0x03, 0x24, 0xFF, 0xFC };
    ok += testea(mbs, "Leemos las salidas analogicas de la 1 a la 10", BVEC(peti), BVEC(resp) );
    //Salidas analogicas valen ahora [4864 4 8 12 784 20 24 28 32 804]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x10, 0x00, 0x01, 0x00, 0x03, 0x06, 0x10, 0x04, 0x10, 0x08, 0x10, 0x0C, 0xC7, 0x95 };
    byte resp[] = { 0x06, 0x10, 0x00, 0x01, 0x00, 0x03, 0xD0, 0x7F };
    ok += testea(mbs, "Formazos salidas analogicas de la 2 a la 4 a los valores [4100 4104 4108]", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x00, 0x00, 0x0A, 0xC4, 0x7A };
    byte resp[] = { 0x06, 0x03, 0x14, 0x13, 0x00, 0x10, 0x04, 0x10, 0x08, 0x10, 0x0C, 0x03, 0x10, 0x00, 0x14, 0x00, 0x18, 0x00, 0x1C, 0x00, 0x20, 0x03, 0x24, 0xE7, 0x25 };
    ok += testea(mbs, "Leemos las salidas analogicas de la 1 a la 10", BVEC(peti), BVEC(resp) );
    //Salidas analogicas valen ahora [4864 4100 4104 4108 784 20 24 28 32 804]
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x10, 0x00, 0x03, 0x00, 0x07, 0x0E, 0x20, 0x0C, 0x13, 0x10, 0x10, 0x14, 0x10, 0x18, 0x10, 0x1C, 0x10, 0x20, 0x13, 0x24, 0x9E, 0x60 };
    byte resp[] = { 0x06, 0x10, 0x00, 0x03, 0x00, 0x07, 0x70, 0x7C };
    ok += testea(mbs, "Formazos salidas analogicas de la 4 a la 10 a los valores [8204 4880 4116 4120 4124 4128 4900]", BVEC(peti), BVEC(resp) );
  }
  {
    tot++;
    byte peti[] = { 0x06, 0x03, 0x00, 0x00, 0x00, 0x0A, 0xC4, 0x7A };
    byte resp[] = { 0x06, 0x03, 0x14, 0x13, 0x00, 0x10, 0x04, 0x10, 0x08, 0x20, 0x0C, 0x13, 0x10, 0x10, 0x14, 0x10, 0x18, 0x10, 0x1C, 0x10, 0x20, 0x13, 0x24, 0x1D, 0xE3 };
    ok += testea(mbs, "Leemos las salidas analogicas de la 1 a la 10", BVEC(peti), BVEC(resp) );
    //Salidas analogicas valen ahora [4864 4100 4104 8204 4880 4116 4120 4124 4128 4900]
  }

  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  //Código generado automaticamente

  //conclusiones
  cout << "\n\nRealizados " << tot << " pruebas: correctas=" << ok
    << " FALLOS=" << tot-ok << endl;
  if( tot == ok )
    cout << "TODO CORRECTO" << endl;
}
