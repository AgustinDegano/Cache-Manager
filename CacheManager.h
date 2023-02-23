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
  void showFile();
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
    exit();  
  }

  else
  {
    (auto x : cache_data_file)      // Si puedo acceder al archivo, le pido que me pase el ID, Data y Valor.
    {
      archivo << x.first << " "
              << " " << x.second.first.getId() << " " << x.second.first.getData() << " " << x.second.first.getValue() << endl;
    }
  }
  archivo.close();   
}

template <class T>
void CacheManager <T >::show_cache()
{
  for (auto x : cache_data) //Recorro el Caché
  {
    x.second.first.print(); //Muestro el Caché
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
          cache_data_file.insert(make_pair(key, make_pair(obj,MRU)))
        }
      }
      MRU++;
      cache_data.insert(make_pair(key, make_pair(obj,MRU)));
      cache_data_file.insert(make_pair(key, make_pair(obj,MRU)))
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
        if (l->second.second == f)
        {
          auto y = cache_data.find(l->first);
          cache_data.erase(y);
          mru++;
          cache_data.insert(make_pair(key, make_pair(obj, mru)));
          cache_data_file.insert(make_pair(key, make_pair(obj, mru)));
          writeFile();
        }
      }
    }
  }
}


//-----------------GET-----------
template <class T>
T CacheManager<T>::get(string key)
{
  string texto;
  ifstring archivo;
  archivo.open("ArchivoMemoriaRam.txt", ios::in | ios:binary);

  if(archivo.fail())
  {
    cout << "No se puede abrir o acceder al archivo";
  }  

  while (!archivo.oef())
  {
    getline(archivo, texto);
    try
    {
      
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    
  }
  













}