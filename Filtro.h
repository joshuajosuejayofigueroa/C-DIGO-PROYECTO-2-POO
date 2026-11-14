#ifndef FILTRO_H
#define FILTRO_H

#include "Imagen.h"
#include <string>

class Filtro {
public:
    virtual ~Filtro() {}
    virtual Imagen aplicar(const Imagen& img) const = 0;
    virtual std::string nombre() const = 0;
};

class Umbral : public Filtro {
private:
    int m_Umbral;
public:
    Umbral(int umbral);
    Imagen aplicar(const Imagen& img) const override;
    std::string nombre() const override;
};

class Media : public Filtro {
public:
    Imagen aplicar(const Imagen& img) const override;
    std::string nombre() const override;
};

class Sobel : public Filtro {
public:
    Imagen aplicar(const Imagen& img) const override;
    std::string nombre() const override;
};

class EspejoHorizontal : public Filtro {
public:
    Imagen aplicar(const Imagen& img) const override;
    std::string nombre() const override;
};

class Rotar90 : public Filtro {
public:
    Imagen aplicar(const Imagen& img) const override;
    std::string nombre() const override;
};

#endif
