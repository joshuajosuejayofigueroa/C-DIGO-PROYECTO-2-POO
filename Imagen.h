#ifndef IMAGEN_H
#define IMAGEN_H

#include <string>
#include <iostream>

class Imagen {
private:
    int** m_Pixeles;
    int m_Alto;
    int m_Ancho;
    int m_MaxVal;

    void liberar();
    void copiar(const Imagen& otra);

public:
    Imagen();
    Imagen(int alto, int ancho, int maxVal = 255);
    Imagen(const std::string& ruta);
    Imagen(const Imagen& otra);
    Imagen& operator=(const Imagen& otra);
    ~Imagen();

    int getAlto() const;
    int getAncho() const;
    int getMaxVal() const;

    int& operator()(int fila, int col);
    int operator()(int fila, int col) const;

    Imagen operator+(int valor) const;
    Imagen operator-(const Imagen& otra) const;
    Imagen operator*(double factor) const;
    Imagen operator~() const;
    bool operator==(const Imagen& otra) const;
    bool operator!=(const Imagen& otra) const;

    friend std::ostream& operator<<(std::ostream& os, const Imagen& img);
    friend std::istream& operator>>(std::istream& is, Imagen& img);

    bool guardar(const std::string& ruta) const;
};

#endif
