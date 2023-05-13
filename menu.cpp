// abrir ambos, el menu es el que va a escribir de primeras. El de busqueda va quedar en estado bloqueante mientras no reciba datos,
// al momento que se realice la busqueda en el menmu, este va a escribir los datos en la tuberia para que asi el otro archivo ya no quede bloqueante
// y pueda realizar la busqueda y devolver la informacion, en ese momento sera que se cerrara?
// porque si se realiza la busqueda el otro arhivo como tal ya terminaria su proceso. BUueno pues vamos a probar c:

#include "helpers.hpp"

int main(int argc, char const *argv[])
{

    const char *pipe_name = "/tmp/menuPipe";

    // creando la tuberia nombrada
    mkfifo(pipe_name, 0666);

    // datos para la busqueda
    int opc, id_origen = -1, id_destino = -1, hora = -1;
    float tiempo_medio = 0;

    cout << "*************************************************" << endl;
    cout << "*******************Bienvenido********************" << endl;
    cout << "*************************************************" << endl;

    do
    {

        if (id_origen > 0 || id_destino > 0 || hora > 0)
        {
            cout << "Datos actuales:\n \torigen: " << id_origen << "\n\tdestino: " << id_destino << "\n \thora: " << hora << endl;
        }

        cout << "\n1. Ingresar Origen" << endl;
        cout << "2. Ingresar Destino" << endl;
        cout << "3. Ingresar Hora" << endl;
        cout << "4. Buscar tiempo de viaje medio" << endl;
        cout << "5. Salir" << endl;
        cout << "Digite la opcion: ";
        cin >> opc;

        switch (opc)
        {
        case 1:
            do
            {
                cout << "Selecciona el ID de origen (entre 1 - 1160): ";
                cin >> id_origen;
            } while (id_origen < 1 || id_origen > 1160);

            cout << "\033[2J\033[1;1H";
            break;
        case 2:
            do
            {
                cout << "Selecciona el ID de destino (entre 1 - 1160): ";
                cin >> id_destino;
            } while (id_destino < 1 || id_destino > 1160);

            cout << "\033[2J\033[1;1H";
            break;
        case 3:
            do
            {
                cout << "Selecciona la hora (entre 0 - 23): ";
                cin >> hora;
            } while (hora < 0 || hora > 23);

            cout << "\033[2J\033[1;1H";
            break;
        case 4:
        {


            clock_t start_time, end_time;
            double cpu_time_used;

            // al llamar a la funciones lo que hace es enviar los datos a el otro processo
            start_time = clock();

            Trip t;
            t.source_id = id_origen;
            t.dstid = id_destino;
            t.hod = hora;
            t.mean_travel_time = -1;

            // abriendo la tuberia para escritura
            int pipe_fd = open(pipe_name, O_WRONLY);

            // escribiendo datos en la tuberia
            write(pipe_fd, &t, sizeof(Trip));

            // cerrando la tuberia
            close(pipe_fd);

            // necesito recibir de otra tuberia los datos encontrados por el otro arhivo
            pipe_fd = open("/tmp/searchPipe", O_RDONLY);

            read(pipe_fd, &t, sizeof(Trip));

            if (t.mean_travel_time < 0)
            {
                cout << "\n------- NA -------\n"
                     << endl;
            }
            else
            {

                cout << "------- Tiempo de viaje medio: " << t.mean_travel_time << " -------\n"
                     << endl;
            }

            close(pipe_fd);

            end_time = clock();

            cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            cout << "\tTiempo empleado en la busqueda: " << cpu_time_used << " segundos" << endl;

            opc = 5;
            break;
        }
        case 5:
            break;
        }
    } while (opc != 5);

    _exit(0);
    return 0;
}
