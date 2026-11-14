#include "Filtro.h"
#include <algorithm>
#include <cmath>

Umbral::Umbral(int umbral) : m_Umbral(umbral) {}
Imagen Umbral::aplicar(const Imagen& img) const {
    Imagen res(img.getAlto(), img.getAncho(), img.getMaxVal());
    for (int i = 0; i < img.getAlto(); ++i) {
        for (int j = 0; j < img.getAncho(); ++j) {
            res(i, j) = (img(i, j) >= m_Umbral) ? img.getMaxVal() : 0;
        }
    }
    return res;
}
std::string Umbral::nombre() const { return "Umbral"; }

Imagen Media::aplicar(const Imagen& img) const {
    int alto = img.getAlto();
    int ancho = img.getAncho();
    Imagen res(alto, ancho, img.getMaxVal());
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            int suma = 0;
            int count = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < alto && nj >= 0 && nj < ancho) {
                        suma += img(ni, nj);
                        count++;
                    }
                }
            }
            res(i, j) = suma / count;
        }
    }
    return res;
}
std::string Media::nombre() const { return "Media"; }

Imagen Sobel::aplicar(const Imagen& img) const {
    int alto = img.getAlto();
    int ancho = img.getAncho();
    Imagen res(alto, ancho, img.getMaxVal());
    for (int i = 1; i < alto - 1; ++i) {
        for (int j = 1; j < ancho - 1; ++j) {
            int gx = -img(i-1, j-1) + img(i-1, j+1)
                     -2*img(i, j-1)   + 2*img(i, j+1)
                     -img(i+1, j-1) + img(i+1, j+1);
            int gy = -img(i-1, j-1) - 2*img(i-1, j) - img(i-1, j+1)
                     +img(i+1, j-1) + 2*img(i+1, j) + img(i+1, j+1);
            int val = static_cast<int>(std::sqrt(gx*gx + gy*gy));
            res(i, j) = std::clamp(val, 0, img.getMaxVal());
        }
    }
    return res;
}
std::string Sobel::nombre() const { return "Sobel"; }

Imagen EspejoHorizontal::aplicar(const Imagen& img) const {
    int alto = img.getAlto();
    int ancho = img.getAncho();
    Imagen res(alto, ancho, img.getMaxVal());
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            res(i, j) = img(i, ancho - 1 - j);
        }
    }
    return res;
}
std::string EspejoHorizontal::nombre() const { return "EspejoHorizontal"; }

Imagen Rotar90::aplicar(const Imagen& img) const {
    int alto = img.getAlto();
    int ancho = img.getAncho();
    Imagen res(ancho, alto, img.getMaxVal());
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            res(j, alto - 1 - i) = img(i, j);
        }
    }
    return res;
}
std::string Rotar90::nombre() const { return "Rotar90"; }
