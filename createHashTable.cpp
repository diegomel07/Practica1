#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <string>
#include <list>
#include <cstddef>
#include <algorithm>

#include "helpers.hpp"

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

// De que manera puedo escoger el tamaño, como me aseguro de que si se guardo todo de manera correcta. Porque la hashfunction genera el mismo numero que le mando
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


// funcion para imprimir la hash table
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
} 
