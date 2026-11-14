#ifndef EDITOR_H
#define EDITOR_H

#include "Imagen.h"
#include "Filtro.h"
#include <vector>
#include <string>

class Editor {
private:
    Imagen m_Imagen;
    std::vector<Filtro*> m_Filtros;
    std::vector<std::string> m_Bitacora;

public:
    Editor();
    ~Editor();

    bool cargarImagen(const std::string& ruta);
    bool guardarImagen(const std::string& ruta) const;
    void agregarFiltro(Filtro* filtro);
    void aplicarFiltros();
    void deshacerUltimaOperacion();
    void mostrarBitacora() const;
    bool guardarBitacora(const std::string& ruta) const;
};

#endif
