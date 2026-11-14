#include <iostream>
#include "Editor.h"

using namespace std;

int main() {
    Editor editor;
    
    if (editor.cargarImagen("patron.pgm")) {
        cout << "Imagen cargada con exito.\n";
        editor.agregarFiltro(new Media());
        editor.agregarFiltro(new Sobel());
        editor.aplicarFiltros();
        
        if (editor.guardarImagen("resultado.pgm")) {
            cout << "Imagen procesada y guardada exitosamente como resultado.pgm\n";
        }
        editor.mostrarBitacora();
        editor.guardarBitacora("bitacora.txt");
    } else {
        cerr << "Error al cargar la imagen. Verifique la ruta.\n";
    }

    return 0;
}
```[cite: 20, 21]
