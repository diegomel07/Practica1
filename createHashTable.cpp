#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <list>
#include <cstddef>
#include <algorithm>
using namespace std;

const int TABLE_SIZE = 2000;

// Estructura que guarda un viaje
struct Trip {
  int source_id;
  int dstid;
  int hod;
  float mean_travel_time;
};


// Funcion para obtener la cantidada de viajes que tiene el archivo
// ---------- TODO revisar que en verdad esto me de lo que tiene que dar
/*
int getTableSize() {
  int table_size = 0, count = 0;

  ifstream file("trips.csv");

  string line;

  while (getline(file, line))
  {
    stringstream ss(line);
    string field;
    vector<string> fields;
    while (getline(ss, field, ','))
    {
      fields.push_back(field);
    }

    if (count != 0)
    {
      if (stoi(fields[0]) > table_size)
      {
        table_size = stoi(fields[0]);
      }
    }

    count++;
  }

  file.close();

  return table_size;
}
*/


// clase que implementa hash table
class HashTable
{
  private:
    vector<vector<Trip>> table;
    
    // funcion para obtner el hash de que un valor recibido
    int hashFunction(int n) 
    {
      static const int prime = 31;
      int hash = 0;
      hash = prime * hash + n;
      return hash % TABLE_SIZE;
    } 

  public:
    HashTable()
    {
      table.resize(TABLE_SIZE);
    }

    // agregar un nuevo bucket a la hash table
    void insert(int key, Trip value)
    {
      int index = hashFunction(key);
      table[index].push_back(value);
      
      // evitar colisiones al insertar
      /*
      int index = hashFunction(key);
      int i = 0;

      while(!table[index].empty() && i < TABLE_SIZE)
      {
        index = (index + 1) % TABLE_SIZE;
        i++;
      }

      if(i < TABLE_SIZE)
      {
        table[index].push_back(value);
      } else {
        cerr << "HashTable is full, could not insert Person" << endl;
      }
      */
    }
    

    // encontrar un bucker dentro de la hash table
    /*
    vector<Trip> find(int key)
    {
      int index = hashFunction(key);
     
      return table[index];
    }
    */

    // devolver la tabla
    const vector<vector<Trip>>& getTable() const {
      return table;
    }
};


// Funcion para llenar la hash table con los valores que estan en el archivo
HashTable fillHashTable(HashTable ht)
{

  ifstream file("trips.csv");
  Trip tmp;
  string line;

  // leemos todo el archivo, y cada linea leida la guardamos en la variable line
  while (getline(file, line))
  {
    stringstream ss(line);
    string field;
    vector<string> fields;

    // Guardamos los valores de la linea leida separados por coma
    while (getline(ss, field, ','))
    {
      fields.push_back(field);
    }

    // guardamos los datos que nos interesan una estructura temporal
    tmp.source_id = stoi(fields[0]);
    tmp.dstid = stoi(fields[1]);
    tmp.hod = stoi(fields[2]);
    tmp.mean_travel_time = stof(fields[3]);

    // guradamos la estructura en la hash table
    ht.insert(tmp.source_id, tmp);

  }

  file.close();

  return ht;
}


// Funcion para guardar el contenido de la hashtable en un archivo
void saveHashTableToFile(const HashTable& ht, const string& filename) {

    // creamos o abrimos el archivo para escribir
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Error: Unable to open file \"" << filename << "\" for writing." << endl;
        return;
    }

    // Escribimos en el archivo la cantidad de buckets que tiene la hash table
    int num_buckets = TABLE_SIZE;
    fout.write(reinterpret_cast<const char*>(&num_buckets), sizeof(num_buckets));

    // guradamos cada bucket con su respectivo tamanio
    const vector<vector<Trip>>& table = ht.getTable();

    for (const vector<Trip>& bucket : table) {
        int bucket_size = bucket.size();
        fout.write(reinterpret_cast<const char*>(&bucket_size), sizeof(bucket_size));

        for (const Trip& p : bucket) {
            fout.write(reinterpret_cast<const char*>(&p), sizeof(p));
        }
    }

    fout.close();
}


// cargar en memoria la hash table desde un archivo
HashTable loadHashTableFromFile(const string& filename) {

    // abrimos el archivo en modo de lectura
    HashTable ht;
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Error: Unable to open file \"" << filename << "\" for reading." << endl;
        return ht;
    }

    // leeemos la cantidad de buckets que tiene la hash table del archivo
    int num_buckets;
    fin.read(reinterpret_cast<char*>(&num_buckets), sizeof(num_buckets));

    // guardamos los buckets leidos
    for (int i = 0; i < num_buckets; i++) {
        int bucket_size;
        fin.read(reinterpret_cast<char*>(&bucket_size), sizeof(bucket_size));
        for (int j = 0; j < bucket_size; j++) {
            Trip p;
            fin.read(reinterpret_cast<char*>(&p), sizeof(p));
            ht.insert(p.source_id, p);
        }
    }

    fin.close();

    return ht;
}



void printHashTable(HashTable ht) 
{
  const vector<vector<Trip>>& table = ht.getTable();
  for (int i = 0; i < TABLE_SIZE; i++) 
  {
    if (!table[i].empty()) 
    {
      cout << "Bucket " << i << ": ";
      for (Trip t : table[i]) 
      {
        cout << "Trip: " << t.source_id << " - " << t.dstid << " - " << t.hod << " - " << t.mean_travel_time << endl;
      }
      cout << endl;
    }
  }
}

 
int hashFunction(int n) 
{
    
  static const int prime = 31;
  int hash = 0;
  hash = prime * hash + n;
  return hash % TABLE_SIZE;
      
  //return n % TABLE_SIZE;
} 

// Funcion para realizar la busqueda de un indice o bucket de la hash table
vector<Trip> readBucketFromFile(const string& filename, int bucket_index) {
    vector<Trip> bucket;
    
    // Aprtura del archivo
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Error: Unable to open file \"" << filename << "\" for reading." << endl;
        return bucket;
    }

    // leemos la cantidad de buckets que tiene la hash table
    int num_buckets;
    fin.read(reinterpret_cast<char*>(&num_buckets), sizeof(num_buckets));

    // si el indice proporcionado es mayor que la cantidad de buckets que tiene la hash table
    if (bucket_index >= num_buckets) {
        cerr << "Error: Bucket index out of range." << endl;
        return bucket;
    }

    // realizamos la busqueda del bucket
    for (int i = 0; i < bucket_index; i++) {
        int bucket_size;
        fin.read(reinterpret_cast<char*>(&bucket_size), sizeof(bucket_size));
        fin.seekg(bucket_size * sizeof(Trip), ios::cur);
    }

    // leemos el tamanio del bucket y redimensionamos un vector para poder guardar los datos 
    int bucket_size;
    fin.read(reinterpret_cast<char*>(&bucket_size), sizeof(bucket_size));
    bucket.resize(bucket_size);
  
    // leemos y guardamos en un vector los datos del bucket leido del archivo
    for (Trip& trip : bucket) {
        fin.read(reinterpret_cast<char*>(&trip), sizeof(trip));
    }

    fin.close();
    return bucket;
}


int main (int argc, char *argv[])
{
  // Primero guardamos en un archivo la hash table que creamos del archivo csv
  HashTable ht;
  saveHashTableToFile(fillHashTable(ht), "test.dat");

  // --------- Prueba ----------
  // Cargarmos la hash table de el archivo
  //HashTable load = loadHashTableFromFile("test.dat");
  // --------- Fin Prueba ------- 

  // prueba de la funcion de busqueda
  vector<Trip> test = readBucketFromFile("test.dat", 462);
  
  // La funcion de readBucketFromFile devueve un vector con todos los viajes que empiecen en el destino proporcionado por el id
  // Se realiza ahora la busqueda de el viaje exacto que se necesita
  auto it = std::find_if(test.begin(), test.end(), [](const Trip& p) {
    return p.dstid == 494 && p.hod == 21;
  });

  // imprimimos el viaje encontrado 
  if (it != test.end()) {
    cout << "Trip: " << it->source_id << " - " << it->dstid << " - " << it->hod << " - " << it->mean_travel_time << endl;
  } else {
    std::cout << "Trip not found" << std::endl;
  }

  return 0;
}
