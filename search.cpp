#include "helpers.hpp"

int main(int argc, char const *argv[])
{
    // primero vamos a leer de la tuberia, 

    // abrir la tuberia del menu en modo de lectura
    int pipe_fd = open("/tmp/menuPipe", O_RDONLY);

    Trip trip;

    read(pipe_fd, &trip, sizeof(Trip));

    trip.mean_travel_time = searchTrip("test.dat", trip.source_id, trip.dstid, trip.hod);

    close(pipe_fd);
    
    // creamos la tuberia de la busqueda
    const char *pipe_name = "/tmp/searchPipe";
    mkfifo(pipe_name, 0666);

    pipe_fd = open(pipe_name, O_WRONLY);

    write(pipe_fd, &trip, sizeof(Trip));

    close(pipe_fd);

    return 0;
}

