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
  map<string, pair<T, int>> cache_data; // <Clave , <Obj ,Indice de Uso > >
  bool write_file(string, T);
  int MRU = 0;


public:
  CacheManager(int); // recibe la capacidad en el int
  ~CacheManager();

  void insert(string key, T obj);
  T get(string key);
  void show_cache();
  void showFile();
  void writeFile();
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
void CacheManager <T>::writeFile()
{
  ofstream archivo;
  archivo.open("ArchivoMemoriaRam.txt", ios::out | ios::binary);
  if (archivo.fail())
  {
    cout << "No se puede abrir o acceder al archivo";
    exit();  
  }   
}

template <class T>
void CacheManager <T >::show_cache()
{
  for (auto x : cache_data) //Recorro el Caché
  {
    x.second.first.print(); //Muestro el Caché
  }
}

// -------------- INSERT ----------------
template <class T>
void CacheManager<T>::insert(string key, T obj)
{ 
  if (cache_data.empty())
  {
    mru++;
    cache_data.insert(make_pair(key, make_pair(obj,1)));
    write_file();
    return;
  }
  else
  {
    if(cache_data.size() < capacity)
    {
       
    }
  }



}








//-----------------GET-----------
template <class T>
T CacheManager<T>::get(string key)
{
//Falta el get
}