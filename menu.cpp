#include <iostream>
#include "helpers.hpp"

using namespace std;

int main(){
  int opc, id_origen = -1, id_destino = -1, hora = -1;

  cout<<"*************************************************"<<endl;
  cout<<"*******************Bienvenido********************"<<endl;
  cout<<"*************************************************"<<endl;

  do
  {

    if (id_origen > 0 || id_destino > 0 || hora > 0)
    {
      cout << "Datos actuales:\n \torigen: " << id_origen << "\n\tdestino: " << id_destino << "\n \thora: " << hora << endl;
    }

    cout<<"1. Ingresar Origen"<<endl;
    cout<<"2. Ingresar Destino"<<endl;
    cout<<"3. Ingresar Hora"<<endl;
    cout<<"4. Buscar tiempo de viaje medio"<<endl;
    cout<<"5. Salir"<<endl;
    cout << "Digite la opcion: ";
    cin  >> opc;

    switch(opc){
      case 1:
        cout << "Selecciona el ID de origen (entre 1 - 1160): ";
        cin >> id_origen;
        cout << "\033[2J\033[1;1H";
        break;
      case 2:
        cout << "Selecciona el ID de destino (entre 1 - 1160): ";
        cin >> id_destino;
        cout << "\033[2J\033[1;1H";
        break;
      case 3:
        cout << "Selecciona la hora (entre 0 - 23): ";
        cin >> hora;
        cout << "\033[2J\033[1;1H";
        break;
      case 4:
        cout << "\033[2J\033[1;1H";
        cout << "Tiempo de viaje medio: " << searchTrip("test.dat", hashFunction(id_origen), id_destino, hora) << endl; //esto va con condicional ya que pueden existir dos valores
      case 5:
        break;
    }
  } while(opc != 5);

  return 0;
};
