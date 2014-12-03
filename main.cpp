#include <iostream>
#include <list>
#include <fstream>

using namespace std;

class Pastel
{
public:
    string nombre;
    int cantidad;
    bool esta_vencido;
    Pastel(string nombre, int cantidad, bool esta_vencido)
    {
        this->nombre = nombre;
        this->cantidad = cantidad;
        this->esta_vencido = esta_vencido;
    }

    void imprimir()
    {
        cout<<this->nombre<<" ";
        cout<<this->cantidad<<" ";
        cout<<this->esta_vencido<<endl;
    }
};

void escribirLista(list<Pastel*> pasteles, string archivo)
{
    ofstream out(archivo.c_str());
    for(list<Pastel*>::iterator i = pasteles.begin();
            i!=pasteles.end();
            i++)
    {
        out<<(*i)->nombre<<" ";
        out<<(*i)->cantidad<<" ";
        out<<(*i)->esta_vencido<<endl;
    }
    out.close();
}

list<Pastel*> leerLista(string archivo)
{
    list<Pastel*> pasteles;
    ifstream in(archivo.c_str());
    string nombre;
    int cantidad;
    bool esta_vencido;
    while(in>>nombre)
    {
        in>>cantidad;
        in>>esta_vencido;
        pasteles.push_back(new Pastel(nombre,cantidad,esta_vencido));
    }
    in.close();
    return pasteles;
}

void escribirListaBinario(list<Pastel*> pasteles, string archivo)
{
    ofstream out(archivo.c_str());
    for(list<Pastel*>::iterator i = pasteles.begin();
            i!=pasteles.end();
            i++)
    {
        out.write((*i)->nombre.c_str(),10);
        out.write((char*)&(*i)->cantidad,4);
        out.write((char*)&(*i)->esta_vencido,1);
    }
    out.close();
}

list<Pastel*> leerListaBinario(string archivo)
{
    list<Pastel*>pasteles;
    ifstream in(archivo.c_str(),ios::ate);
    int tamano = in.tellg();
    in.seekg(0);
    while(in.tellg()<tamano)
    {
        char nombre[10];
        int cantidad;
        bool esta_vencido;
        in.read(nombre,10);
        in.read((char*)&cantidad,4);
        in.read((char*)&esta_vencido,1);
        pasteles.push_back(new Pastel(nombre,cantidad,esta_vencido));
    }
    in.close();
    return pasteles;
}


void modificarPastel(Pastel* pastel, string archivo, int posicion)
{
    ofstream out(archivo.c_str(),ios::in);
    if(!out.is_open())
    {
        ofstream out(archivo.c_str());
    }
    out.seekp(posicion*15);
    out.write(pastel->nombre.c_str(),10);
    out.write((char*)&pastel->cantidad,4);
    out.write((char*)&pastel->esta_vencido,1);
    out.close();
}

int main()
{
//    list<Pastel*>pasteles;
//    pasteles.push_back(new Pastel("fresa",3,false));
//    pasteles.push_back(new Pastel("choco",2,true));
//    pasteles.push_back(new Pastel("queso",4,false));
//    escribirListaBinario(pasteles,"pasteles.txt");
    modificarPastel(new Pastel("coco",6,true),"pasteles.txt",1);

    list<Pastel*>pasteles = leerListaBinario("pasteles.txt");
    for(list<Pastel*>::iterator i = pasteles.begin();
            i!=pasteles.end();
            i++)
    {
        (*i)->imprimir();
    }
    return 0;
}
