#include <iostream>

using namespace std;

int main(){
    int opc;
    int ID_origen;
    int ID_destino;
    int Hora;
    cout<<"*************************************************"<<endl;
    cout<<"*******************Bienvenido********************"<<endl;
    cout<<"*************************************************"<<endl;
    cout<<"1. Ingresar Origen"<<endl;
    cout<<"2. Ingresar Destino"<<endl;
    cout<<"3. Ingresar Hora"<<endl;
    cout<<"4. Buscar tiempo de viaje medio"<<endl;
    cout<<"5. Salir"<<endl;
    cin>>opc;

    switch(opc){
        case 1:
        cout<<"Selecciona el ID de origen (entre 1 - 1160): "<<endl;
        cin>>ID_origen;
        break;
        case 2:
        cout<<"Selecciona el ID de destino (entre 1 - 1160): "<<endl;
        cin>>ID_destino;
        break;
        case 3:
        cout<<"Selecciona la hora (entre 0 - 23): "<<endl;
        cin>>Hora;
        break;
        case 4:
        cout<<"tiempo de viaje medio:"<<endl; //esto va con condicional ya que pueden existir dos valores
        case 5:
        break;
    }

    return 0;
};