#ifndef PGM_IO_H
#define PGM_IO_H

#include <string>

int** leerPGM(const std::string& ruta, int& alto, int& ancho, int& maxVal);
void escribirPGM(const std::string& ruta, int** pixeles, int alto, int ancho, int maxVal);
void liberarPGM(int** pixeles, int alto);

#endif
