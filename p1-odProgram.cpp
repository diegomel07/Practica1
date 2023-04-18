#include <sys/wait.h>
#include <time.h>
#include "helpers.hpp"

int main()
{
  const char* pipe_name = "/tmp/my_pipe";

  // creando la tuberia nombrada
  mkfifo(pipe_name, 0666);

  // proceso que crea el menu
  pid_t pid_menu = fork();

  if (pid_menu == 0)
  {
    menu(pipe_name);
  }

  // proceso que realiza la busqueda
  pid_t pid_search = fork();

  if (pid_search == 0) 
  {
    int pipe_fd = open(pipe_name, O_RDONLY);
    Trip t;

    read(pipe_fd, &t, sizeof(Trip));


    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock();
    t.mean_travel_time = searchTrip("test.dat", t.source_id, t.dstid, t.hod);
    end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    cout << "\tTiempo empleado en la busqueda: " << cpu_time_used << " segundos" << endl;

    if (t.mean_travel_time < 0)
      {
        cout << "\n------- NA -------\n" << endl;
      } else {

      cout << "------- Tiempo de viaje medio: " << t.mean_travel_time << " -------\n" <<endl;
    }

    close(pipe_fd);

    _exit(0);

  }

  waitpid(pid_menu, NULL, 0);
  waitpid(pid_search, NULL, 0);

  unlink(pipe_name);

  return 0;

};
