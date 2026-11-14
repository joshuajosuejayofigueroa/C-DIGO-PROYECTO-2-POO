#include "Editor.h"
#include <fstream>
#include <iostream>

Editor::Editor() {}

Editor::~Editor() {
    for (auto f : m_Filtros) {
        delete f;
    }
}

bool Editor::cargarImagen(const std::string& ruta) {
    Imagen img(ruta);
    if (img.getAlto() == 0) return false;
    m_Imagen = img;
    m_Bitacora.push_back("Cargar: " + ruta);
    return true;
}

bool Editor::guardarImagen(const std::string& ruta) const {
    return m_Imagen.guardar(ruta);
}

void Editor::agregarFiltro(Filtro* filtro) {
    m_Filtros.push_back(filtro);
}

void Editor::aplicarFiltros() {
    for (auto f : m_Filtros) {
        m_Imagen = f->aplicar(m_Imagen);
        m_Bitacora.push_back("Aplicar filtro: " + f->nombre());
    }
    for (auto f : m_Filtros) {
        delete f;
    }
    m_Filtros.clear();
}

void Editor::deshacerUltimaOperacion() {
    std::cout << "Operacion de deshacer no implementada en este bloque base.\n";
}

void Editor::mostrarBitacora() const {
    std::cout << "--- BITACORA DE OPERACIONES ---\n";
    for (const auto& op : m_Bitacora) {
        std::cout << "- " << op << "\n";
    }
}

bool Editor::guardarBitacora(const std::string& ruta) const {
    std::ofstream archivo(ruta);
    if (!archivo) return false;
    for (const auto& op : m_Bitacora) {
        archivo << op << "\n";
    }
    return true;
}
