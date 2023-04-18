#include <sys/wait.h>
#include <time.h>
#include "helpers.hpp"

int main(){
  int opc, id_origen = -1, id_destino = -1, hora = -1;
  float tiempo_medio = 0;

  cout<<"*************************************************"<<endl;
  cout<<"*******************Bienvenido********************"<<endl;
  cout<<"*************************************************"<<endl;

  do
  {

    if (id_origen > 0 || id_destino > 0 || hora > 0)
    {
      cout << "Datos actuales:\n \torigen: " << id_origen << "\n\tdestino: " << id_destino << "\n \thora: " << hora << endl;
    }

    cout<<"\n1. Ingresar Origen"<<endl;
    cout<<"2. Ingresar Destino"<<endl;
    cout<<"3. Ingresar Hora"<<endl;
    cout<<"4. Buscar tiempo de viaje medio"<<endl;
    cout<<"5. Salir"<<endl;
    cout << "Digite la opcion: ";
    cin  >> opc;

    switch(opc){
      case 1:
        do
        {
          cout << "Selecciona el ID de origen (entre 1 - 1160): ";
          cin >> id_origen;
        } while(id_origen < 1 || id_origen > 1160);

        cout << "\033[2J\033[1;1H";
        break;
      case 2:
        do
        {
          cout << "Selecciona el ID de destino (entre 1 - 1160): ";
          cin >> id_destino;
        } while(id_destino < 1 || id_destino > 1160);

        cout << "\033[2J\033[1;1H";
        break;
      case 3:
        do
        {
          cout << "Selecciona la hora (entre 0 - 23): ";
          cin >> hora;
        } while(hora < 0 || hora > 23);

        cout << "\033[2J\033[1;1H";
        break;
      case 4:
        cout << "\033[2J\033[1;1H";

        clock_t start_time, end_time;
        double cpu_time_used;

        start_time = clock();
        tiempo_medio = pipe_process(id_origen, id_destino, hora);
        end_time = clock();

        cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        cout << "\tTiempo empleado en la busqueda: " << cpu_time_used << " segundos" << endl;
        
        if (tiempo_medio < 0)
          {
            cout << "\n------- NA -------\n" << endl;
          } else {

          cout << "------- Tiempo de viaje medio: " << tiempo_medio << " -------\n" <<endl;
        }
      case 5:
        break;
    }
  } while(opc != 5);

  return 0;
};
