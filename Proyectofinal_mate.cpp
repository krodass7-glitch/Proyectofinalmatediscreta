/*Este programa crea y manipula arboles ABB con raiz y nodos, tambien podemos visualizar sus recorridos, saber si es binario, su altura y mostrar el arbol*/
//LIBRERIAS
#include <iostream>
#include <vector>
using namespace std;

//ESTRUCTURA PARA NODO
struct Nodo {
    int valor; //valor que se guardara en el nodo
    vector<Nodo*> hijosIzq; // nodo con valor menor que nodo padre
    vector<Nodo*> hijosDer; // nodo con valor mayor que nodo padre

    Nodo(int v) { valor = v; } //se inicia la variable v con el valor del nodo
};

//CLASE ARBOL
class Arbol {
private:
    Nodo* raiz; //Nodo denominado raiz

    // Funcion que nos permite buscar el nodo que se necesite para diferentes acciones
    Nodo* buscar(Nodo* nodo, int valor) {
        if (nodo == nullptr) return nullptr;
        if (nodo->valor == valor) return nodo; 

        for (auto hijo : nodo->hijosIzq) { //recorre todos los hijos izquierdos
            Nodo* encontrado = buscar(hijo, valor); //por cada nodo utilizamos la funcion buscar
            if (encontrado) return encontrado; 
        }

        for (auto hijo : nodo->hijosDer) { //recorre todos los hijos derechos
            Nodo* encontrado = buscar(hijo, valor); //por cada nodo utiliza la funcion buscar
            if (encontrado) return encontrado; 
        }

        return nullptr; //no existe el nodo, por lo que no retorna ninguno
    }

    // MOSTRAR ARBOL: ESTRUCTURA
    void mostrarRecursivo(Nodo* nodo, int nivel) { 
        if (nodo == nullptr) return;  //Si no cuenta con un nodo no realizara el procedimiento
        for (int i = 0; i < nivel; i++) 
        cout << "    "; //Sangrìa que se vera en cada nivel del arbol
        cout << "- " << nodo->valor << endl; //Guion para mantener un orden

        //se recorren los hijos derechos e izquierdos para aumentar la sangrìa     
        for (auto hijo : nodo->hijosIzq)
            mostrarRecursivo(hijo, nivel + 1); 
        for (auto hijo : nodo->hijosDer)
            mostrarRecursivo(hijo, nivel + 1);
    }

    // Recorridos
    // PREORDEN: recorre raiz, luego nodos izquierdos y por ultimo derechos
    void preorden(Nodo* nodo) {
        if (nodo == nullptr) return;
        cout << nodo->valor << " ";
        for (auto hijo : nodo->hijosIzq) preorden(hijo);
        for (auto hijo : nodo->hijosDer) preorden(hijo);
    }

    //INORDEN: recorre nodo izquierdos, luego raiz y por ultimo nodo derecho
    void inorden(Nodo* nodo) { 
        if (nodo == nullptr) return;
        for (auto hijo : nodo->hijosIzq) inorden(hijo);
        cout << nodo->valor << " ";
        for (auto hijo : nodo->hijosDer) inorden(hijo);
    }

    //POSTORDEN: recorre nodo izquierdo, luego nodo derecho y por ultimo raiz
    void postorden(Nodo* nodo) {
        if (nodo == nullptr) return;
        for (auto hijo : nodo->hijosIzq) postorden(hijo);
        for (auto hijo : nodo->hijosDer) postorden(hijo);
        cout << nodo->valor << " ";
    }

    // Calcular altura del árbol
    int altura(Nodo* nodo) {
        if (nodo == nullptr) return 0; //si no cuenta con nodos su resultado sera 0

        int maxAltura = 0; //inicia en 0
        for (auto hijo : nodo->hijosIzq) {
            int h = altura(hijo);
            if (h > maxAltura) maxAltura = h;
        }
        for (auto hijo : nodo->hijosDer) {
            int h = altura(hijo);
            if (h > maxAltura) maxAltura = h;
        }

        return 1 + maxAltura; //recursividad para aumentar la altura cuando recorre por cada subarbol
    }

    // Verificar si es binario 
    bool esBinario(Nodo* nodo) {
        if (nodo == nullptr) return true;

        if (nodo->hijosIzq.size() > 1 || nodo->hijosDer.size() > 1)
            return false; //Si se encuntra mas de un hijo derecho o izquierdo no es binario

        for (auto hijo : nodo->hijosIzq)
            if (!esBinario(hijo)) return false;
        for (auto hijo : nodo->hijosDer)
            if (!esBinario(hijo)) return false; //devuelve falso si cuanta con mas de un hijo por lado

        return true; //retorna verdadera si no cuenta con lo anterior
    }

public:
    Arbol() { raiz = nullptr; } //se inicia sin raiz

    //RAIZ
    void crearRaiz(int valor) { //se crea la raiz
            if (raiz != nullptr) {
            cout << "La raiz ya existe.\n";
            return;
        }
        raiz = new Nodo(valor); //cuando se ingresa el avlor de raiz
        cout << "Raiz creada con valor " << valor << endl;
    }

    //AGREGAR NODO
    void agregarNodo(int padre, int nuevoValor) {
        if (raiz == nullptr) { //revisa si existe raiz
            cout << "Primero debes crear la raiz.\n";
            return;
        }

        Nodo* nodoPadre = buscar(raiz, padre); //recorre buscando el nodo
        if (nodoPadre == nullptr) {
            cout << "No se encontro el nodo padre con valor " << padre << ".\n";
            return;
        }

        if (nuevoValor < nodoPadre->valor) { //si es menor al nodo padre sera agregado a la izquierda (arriba)
            nodoPadre->hijosIzq.push_back(new Nodo(nuevoValor));
            cout << "Nodo " << nuevoValor << " agregado a la IZQUIERDA de " << padre << ".\n";
        } else {
            nodoPadre->hijosDer.push_back(new Nodo(nuevoValor));//si es mayor al nodo padre sera agregado a la derecha (abajo)
            cout << "Nodo " << nuevoValor << " agregado a la DERECHA de " << padre << ".\n";
        }
    }
    //MOSTRAR ARBOL
    void mostrar() {
        if (raiz == nullptr) { //si no se encuntra una raiz, mostrara el mensaje 
            cout << "El arbol esta vacio.\n";
            return;
        }
        cout << "\nEstructura del arbol:\n"; 
        mostrarRecursivo(raiz, 0); //empieza en nivel 0 y llama a la funcion mostrarrecursivo
    }

    //OPCION 4: escoger el recorrido
    void recorrer(int tipo) {
        if (raiz == nullptr) {
            cout << "El arbol esta vacio.\n";
            return;
        }
        //se llama cada a cada recorrido 
        cout << "\nRecorrido: ";
        if (tipo == 1) {
            cout << "Preorden:  ";
            preorden(raiz);
        } else if (tipo == 2) {
            cout << "Inorden:  ";
            inorden(raiz);
        } else if (tipo == 3) {
            cout << "Postorden:  ";
            postorden(raiz);
        }
        cout << endl;
    }

    //ALTURA: se muestra la variable altura
    void mostrarAltura() {
        cout << "La altura del arbol es: " << altura(raiz) << endl;
    }

    //Binario: se muestra el mesaje segùn el estado de la variable
    void verificarBinario() {
        if (esBinario(raiz))
            cout << "El arbol ES binario.\n";
        else
            cout << "El arbol NO es binario.\n";
    }

    //Se llaman a todos los recorridos para mostrarse
    void realizarTodosRecorridos() {
        cout << "\nPreorden: ";
        preorden(raiz);
        cout << "\nInorden: ";
        inorden(raiz);
        cout << "\nPostorden: ";
        postorden(raiz);
        cout << endl;
    }
};

int main() {
    Arbol arbol; //Objeto de clase arbol
    int opcion;

    do { //OPCIONES
        cout << "\n==================== MENU ARBOL  ====================\n";
        cout << "1. Crear nodo raiz\n";
        cout << "2. Agregar nuevo nodo\n";
        cout << "3. Mostrar arbol\n";
        cout << "4. Recorridos (Preorden, Inorden, Postorden)\n";
        cout << "5. Altura del arbol\n";
        cout << "6. Es binario\n";
        cout << "7. Realizar todos los recorridos\n";
        cout << "8. Salir\n";
        cout << "======================================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {//AGREGAR RAIZ
                int valor;
                cout << "Ingrese valor de la raiz: ";
                cin >> valor;
                arbol.crearRaiz(valor);
                break;
            }
            case 2: { //AGREGAR NODO, DEPENDIENDO DEL NODO PADRE
                int padre, nuevo;
                cout << "Ingrese valor del nodo padre: ";
                cin >> padre;
                cout << "Ingrese valor del nuevo nodo: ";
                cin >> nuevo;
                arbol.agregarNodo(padre, nuevo);
                break;
            }
            case 3://MUESTRA ARBOL
                arbol.mostrar();
                break;
            case 4: {//MUESTRA OPCIONES DE RECORRIDO
                int tipo;
                cout << "1. Preorden"<< endl;
                cout << "2. Inorden"<<endl;
                cout << "3. Postorden" << endl;
                cout << "Seleccione tipo de recorrido: ";
                cin >> tipo;
                arbol.recorrer(tipo);
                break;
            }
            case 5://MUESTRA ALTURA
                arbol.mostrarAltura();
                break;
            case 6: //MUESTRA SI ES BINARIO
                arbol.verificarBinario();
                break;
            case 7: //REALIZA TODOS LOS RECORRIDOS
                arbol.realizarTodosRecorridos();
                break;
            case 8: //SALIDA
                cout << "Saliendo...\n";
                break;
            default: //MENSAJE QUE NO SE ENCONTRO LA OPCION
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 8); //SE REPITE HASTA SALIR

    return 0;
}
