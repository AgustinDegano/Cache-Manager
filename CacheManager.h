#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>

using namespace std;

template <class T>
class CacheManager 
{
  // members ( private )
  int capacity ;
  map<string, pair<T, int>> cache_data;       // La funcion encargada de transportar la información que se pide,sube.
  map<string, pair<T, int>> cache_data_file; // Acá puedo leer, y pedir informacion sobre lo que está en la caché 
  bool write_file(string, T);
  int MRU = 0;


public:
  CacheManager(int); // recibe la capacidad en el int
  ~CacheManager();

  void insert(string key, T obj);
  T get(string key);
  void show_cache();
  void showFile(string key);
  void write_file();
};

// CACHEMANAGER (STRING CAPACITY) 
template <class T> 
CacheManager <T>:: CacheManager (int cap)
{
  capacity = cap;
}

template <class T>
CacheManager <T>::~ CacheManager () {}


template <class T>
bool CacheManager<T>::write_file(string key , T obj) 
{
 return true ;
}

template <class T>
void CacheManager <T>::write_file()
{
  ofstream archivo;
  archivo.open("ArchivoMemoriaRam.txt", ios::out | ios::binary);
  if (archivo.fail())
  {
    cout << "No se puede abrir o acceder al archivo";
    exit(1);  
  }
  else
  {
    {
      for (auto x : cache_data_file)      // Si puedo acceder al archivo, le pido que me pase el ID, Data y Valor.
      {
        archivo << x.first << " "
              << " " << x.second.first.getId() << " " << x.second.first.getData() << " " << x.second.first.getValue() << endl;
      }
    }
  archivo.close();   
  }
} 

// -------------- INSERT ---------------- //
template <class T>
void CacheManager<T>::insert(string key, T obj)
{ 
  if (cache_data.empty())           // Si la memoria caché está vacía 
  {
    MRU++;
    cache_data.insert(make_pair(key, make_pair(obj,1)));
    cache_data_file.insert(make_pair(key, make_pair(obj,MRU)));
    write_file();
    return;
  }
  else
  {
    if(cache_data.size() < capacity)
    {
      for (auto x = cache_data.begin(); x!= cache_data.end(); x++)
      {
        if (x->first == key)
        {      
          auto y = cache_data.find(x->first);
          cache_data.erase(y);
          MRU++;
          cache_data.insert(make_pair(key,make_pair(obj,MRU)));
          auto t = cache_data_file.find(x->first);
          cache_data_file.erase(t);
          cache_data_file.insert(make_pair(key, make_pair(obj,MRU)));
        }
      }
      MRU++;
      cache_data.insert(make_pair(key, make_pair(obj,MRU)));
      cache_data_file.insert(make_pair(key, make_pair(obj,MRU)));
      write_file();
    }
    else
    {
      auto x = cache_data.begin()->second.second;
      int y = 0;
      //cada = cache_data 
      for (auto cada = cache_data.begin();cada != cache_data.end();cada++ )
      {
        if (cada->second.second < x)
        {
          y = cada->second.second;
        }
        else
        {
          y = x;
        }
      }

      for (auto l = cache_data.begin(); l != cache_data.end(); l++)
      {
        int f = 0;
        if (l->second.second == f)
        {
          auto y = cache_data.find(l->first);
          cache_data.erase(y);
          MRU++;
          cache_data.insert(make_pair(key, make_pair(obj, MRU)));
          cache_data_file.insert(make_pair(key, make_pair(obj, MRU)));
          writeFile();
        }
      }
    }
  }
}

// -------------- GET ---------------- //
template <class T>
T CacheManager<T>::get(string key)
{
  string texto;
  ifstream archivo;
  archivo.open("ArchivoMemoriaRam.txt", ios::in | ios::binary);

  if(archivo.fail())
  {
    cout << "No se puede abrir o acceder al archivo";
  }  

  while (!archivo.eof())
  {
    getline(archivo, texto);
    try
    {
      if (texto.rfind(key) < 1231233)
      {
        auto obj_file = cache_data_file.find(key);
        auto x = cache_data.begin()->second.second;
        int f = 0;

        for (auto cada = cache_data.begin(); cada != cache_data.end(); cada++)
        {
          if (cada->second.second < x)
          {
            f = cada -> second.second;
          }
          else
          {
            f = x;
          }
        }

        for (auto l = cache_data.begin(); l != cache_data.end(); l++)
        {
          if (l->second.second == x)
          {
            auto z = cache_data.find(l->first);
            cache_data.erase(z);
            MRU++;
            cache_data.insert(make_pair(obj_file->first, make_pair(obj_file->second.first, MRU)));
          }
        } 
        return obj_file->second.first;
      }

      auto item = cache_data.find(key);
      if (item != cache_data.end())
      {
        item->second.second++;
        return item->second.first;
      }
    }
    catch(...)
    {
     cout << "No se pudo encontrar la clave " << endl;
    }    
  }
  archivo.close();
}

// -------------- MOSTRAR CACHE ---------------- //
template <class T>
void CacheManager<T>::show_cache()
{
  for (auto x : cache_data)
  {
    cout << x.first << " "
         << "MRU: " << x.second.second << " " << x.second.first.getId() << " " << x.second.first.getData() << " " << x.second.first.getValue() << endl;
  }
}

//--------------- MOSTRAR ARCHIVO --------------------//
template <class T>
void CacheManager<T>::showFile (string key)
{
  string texto;
  ifstream archivo;
  archivo.open("ArchivoMemoriaRam.txt", ios::in | ios::binary);

  if(archivo.fail())
  {
    cout << "No se puede abrir o acceder al archivo";
  }

  cout << "ArchivoFinal" << endl;
  
  while (!archivo.eof())
  {
    getline(archivo, texto);
    cout << texto << endl;
  }
  
}