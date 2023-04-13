#include "helpers.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <list>
#include <cstddef>
#include <algorithm>


int hashFunction(int n) 
{
  static const int prime = 31;
  int hash = 0;
  hash = prime * hash + n;
  return hash % TABLE_SIZE;
} 


// Funcion para realizar la busqueda de un indice o bucket de la hash table
float searchTrip(const string& filename, int bucket_index, int dstid, int hod) {
    vector<Trip> bucket;
    
    // Aprtura del archivo
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Error: Unable to open file \"" << filename << "\" for reading." << endl;
        return -1.0;
    }

    // leemos la cantidad de buckets que tiene la hash table
    int num_buckets;
    fin.read(reinterpret_cast<char*>(&num_buckets), sizeof(num_buckets));

    // si el indice proporcionado es mayor que la cantidad de buckets que tiene la hash table
    if (bucket_index >= num_buckets) {
        cerr << "Error: Bucket index out of range." << endl;
        return -1.0;
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

    //return bucket;
    return searcInBucket(bucket, dstid, hod);
}

float searcInBucket(vector<Trip> bucket, int dstid, int hod)
{
  // Se realiza ahora la busqueda de el viaje exacto que se necesita
  for (Trip t : bucket)
  {
    if (t.dstid == dstid && t.hod == hod)
    {
      return t.mean_travel_time;
    }
  }
  return -1.0;
}
