#include "Imagen.h"
#include <fstream>
#include <cmath>
#include <algorithm>

void Imagen::liberar() {
    if (m_Pixeles) {
        for (int i = 0; i < m_Alto; ++i) {
            delete[] m_Pixeles[i];
        }
        delete[] m_Pixeles;
        m_Pixeles = nullptr;
    }
}

void Imagen::copiar(const Imagen& otra) {
    m_Alto = otra.m_Alto;
    m_Ancho = otra.m_Ancho;
    m_MaxVal = otra.m_MaxVal;
    m_Pixeles = new int*[m_Alto];
    for (int i = 0; i < m_Alto; ++i) {
        m_Pixeles[i] = new int[m_Ancho];
        for (int j = 0; j < m_Ancho; ++j) {
            m_Pixeles[i][j] = otra.m_Pixeles[i][j];
        }
    }
}

Imagen::Imagen() : m_Pixeles(nullptr), m_Alto(0), m_Ancho(0), m_MaxVal(255) {}

Imagen::Imagen(int alto, int ancho, int maxVal) : m_Alto(alto), m_Ancho(ancho), m_MaxVal(maxVal) {
    m_Pixeles = new int*[m_Alto];
    for (int i = 0; i < m_Alto; ++i) {
        m_Pixeles[i] = new int[m_Ancho];
        for (int j = 0; j < m_Ancho; ++j) {
            m_Pixeles[i][j] = 0;
        }
    }
}

Imagen::Imagen(const std::string& ruta) : m_Pixeles(nullptr), m_Alto(0), m_Ancho(0), m_MaxVal(255) {
    std::ifstream archivo(ruta);
    if (archivo) {
        archivo >> *this;
    }
}

Imagen::Imagen(const Imagen& otra) {
    copiar(otra);
}

Imagen& Imagen::operator=(const Imagen& otra) {
    if (this != &otra) {
        liberar();
        copiar(otra);
    }
    return *this;
}

Imagen::~Imagen() {
    liberar();
}

int Imagen::getAlto() const { return m_Alto; }
int Imagen::getAncho() const { return m_Ancho; }
int Imagen::getMaxVal() const { return m_MaxVal; }

int& Imagen::operator()(int fila, int col) {
    return m_Pixeles[fila][col];
}

int Imagen::operator()(int fila, int col) const {
    return m_Pixeles[fila][col];
}

Imagen Imagen::operator+(int valor) const {
    Imagen res(m_Alto, m_Ancho, m_MaxVal);
    for (int i = 0; i < m_Alto; ++i) {
        for (int j = 0; j < m_Ancho; ++j) {
            int v = m_Pixeles[i][j] + valor;
            res.m_Pixeles[i][j] = std::clamp(v, 0, m_MaxVal);
        }
    }
    return res;
}

Imagen Imagen::operator-(const Imagen& otra) const {
    Imagen res(m_Alto, m_Ancho, m_MaxVal);
    for (int i = 0; i < m_Alto; ++i) {
        for (int j = 0; j < m_Ancho; ++j) {
            int v = std::abs(m_Pixeles[i][j] - otra(i, j));
            res.m_Pixeles[i][j] = std::clamp(v, 0, m_MaxVal);
        }
    }
    return res;
}

Imagen Imagen::operator*(double factor) const {
    Imagen res(m_Alto, m_Ancho, m_MaxVal);
    for (int i = 0; i < m_Alto; ++i) {
        for (int j = 0; j < m_Ancho; ++j) {
            int v = static_cast<int>(std::round(m_Pixeles[i][j] * factor));
            res.m_Pixeles[i][j] = std::clamp(v, 0, m_MaxVal);
        }
    }
    return res;
}

Imagen Imagen::operator~() const {
    Imagen res(m_Alto, m_Ancho, m_MaxVal);
    for (int i = 0; i < m_Alto; ++i) {
        for (int j = 0; j < m_Ancho; ++j) {
            int v = m_MaxVal - m_Pixeles[i][j];
            res.m_Pixeles[i][j] = std::clamp(v, 0, m_MaxVal);
        }
    }
    return res;
}

bool Imagen::operator==(const Imagen& otra) const {
    if (m_Alto != otra.m_Alto || m_Ancho != otra.m_Ancho) return false;
    for (int i = 0; i < m_Alto; ++i) {
        for (int j = 0; j < m_Ancho; ++j) {
            if (m_Pixeles[i][j] != otra(i, j)) return false;
        }
    }
    return true;
}

bool Imagen::operator!=(const Imagen& otra) const {
    return !(*this == otra);
}

std::ostream& operator<<(std::ostream& os, const Imagen& img) {
    os << "P2\n" << img.m_Ancho << " " << img.m_Alto << "\n" << img.m_MaxVal << "\n";
    for (int i = 0; i < img.m_Alto; ++i) {
        for (int j = 0; j < img.m_Ancho; ++j) {
            os << img.m_Pixeles[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Imagen& img) {
    std::string magic;
    is >> magic;
    if (magic != "P2") return is;

    is >> img.m_Ancho >> img.m_Alto >> img.m_MaxVal;
    img.liberar();
    img.m_Pixeles = new int*[img.m_Alto];
    for (int i = 0; i < img.m_Alto; ++i) {
        img.m_Pixeles[i] = new int[img.m_Ancho];
        for (int j = 0; j < img.m_Ancho; ++j) {
            is >> img.m_Pixeles[i][j];
        }
    }
    return is;
}

bool Imagen::guardar(const std::string& ruta) const {
    std::ofstream archivo(ruta);
    if (!archivo) return false;
    archivo << *this;
    return true;
}
