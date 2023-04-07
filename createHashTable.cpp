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

struct Trip {
  int source_id;
  int dstid;
  int hod;
  float mean_travel_time;
};


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


//class that implement the hash table
class HashTable
{
  private:
    vector<vector<Trip>> table;
    
    int hashFunction(int n) 
    {
    
      static const int prime = 31;
      int hash = 0;
      hash = prime * hash + n;
      return hash % TABLE_SIZE;
      
      //return n % TABLE_SIZE;
    } 
  public:
    HashTable()
    {
      table.resize(TABLE_SIZE);
    }

    void insert(int key, Trip value)
    {
      int index = hashFunction(key);
      table[index].push_back(value);
      
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

    vector<Trip> find(int key)
    {
      int index = hashFunction(key);
     
      return table[index];
    }

    const vector<vector<Trip>>& getTable() const {
      return table;
    }
};


HashTable fillHashTable(HashTable ht)
{

  ifstream file("trips.csv");
  Trip tmp;
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

    tmp.source_id = stoi(fields[0]);
    tmp.dstid = stoi(fields[1]);
    tmp.hod = stoi(fields[2]);
    tmp.mean_travel_time = stof(fields[3]);

    ht.insert(tmp.source_id, tmp);

  }

  file.close();

  return ht;
}

void saveHashTableToFile(const HashTable& ht, const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Error: Unable to open file \"" << filename << "\" for writing." << endl;
        return;
    }

    int num_buckets = TABLE_SIZE;
    fout.write(reinterpret_cast<const char*>(&num_buckets), sizeof(num_buckets));

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


HashTable loadHashTableFromFile(const string& filename) {
    HashTable ht;
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Error: Unable to open file \"" << filename << "\" for reading." << endl;
        return ht;
    }

    int num_buckets;
    fin.read(reinterpret_cast<char*>(&num_buckets), sizeof(num_buckets));

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

vector<Trip> readBucketFromFile(const string& filename, int bucket_index) {
    vector<Trip> bucket;
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Error: Unable to open file \"" << filename << "\" for reading." << endl;
        return bucket;
    }

    int num_buckets;
    fin.read(reinterpret_cast<char*>(&num_buckets), sizeof(num_buckets));

    if (bucket_index >= num_buckets) {
        cerr << "Error: Bucket index out of range." << endl;
        return bucket;
    }

    for (int i = 0; i < bucket_index; i++) {
        int bucket_size;
        fin.read(reinterpret_cast<char*>(&bucket_size), sizeof(bucket_size));
        fin.seekg(bucket_size * sizeof(Trip), ios::cur);
    }

    int bucket_size;
    fin.read(reinterpret_cast<char*>(&bucket_size), sizeof(bucket_size));
    bucket.resize(bucket_size);

    for (Trip& trip : bucket) {
        fin.read(reinterpret_cast<char*>(&trip), sizeof(trip));
    }

    fin.close();
    return bucket;
}


int main (int argc, char *argv[])
{
  //HashTable ht;
  //saveHashTableToFile(fillHashTable(ht), "test.dat");

  //HashTable load = loadHashTableFromFile("test.dat");
  
  //printHashTable(load);
  //vector<Trip> test = load.find(hashFunction(462));
  /*
  for (Trip t : test)
  {
    cout << "Trip: " << t.source_id << " - " << t.dstid << " - " << t.hod << " - " << t.mean_travel_time << endl;
  }
  */

  vector<Trip> test = readBucketFromFile("test.dat", 462);
 
  /*
  for (Trip t : test) 
  {
    cout << "Trip: " << t.source_id << " - " << t.dstid << " - " << t.hod << " - " << t.mean_travel_time << endl;
  }
  */

  auto it = std::find_if(test.begin(), test.end(), [](const Trip& p) {
    return p.dstid == 494 && p.hod == 21;
  });


  if (it != test.end()) {
    cout << "Trip: " << it->source_id << " - " << it->dstid << " - " << it->hod << " - " << it->mean_travel_time << endl;
  } else {
    std::cout << "Person not found" << std::endl;
  }

  return 0;
}
