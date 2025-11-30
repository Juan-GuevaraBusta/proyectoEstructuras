#ifndef COMPACTCHAINLIST_H
#define COMPACTCHAINLIST_H

#include<list>
#include<utility>
#include<vector>

using namespace std;

typedef int Element;

class CompactChainList {
 private:
  list<pair<Element, int>> l;
  list<pair<Element, int>>::iterator mid;
  int s;
  int midPos;
  int midSum;

  void remove(list<pair<Element, int>>::iterator it, int indx); // listo - probar
  
 public:
  //Operaciones constructoras
  CompactChainList(); // listo - probar
  CompactChainList(vector<Element> &v); // listo - probar
  CompactChainList(CompactChainList &l2); // listo - probar
  
  //Operaciones analizadoras
  int size(); // listo - probar
  int searchElement(Element e); // listo - probar
  int getConsecutiveOcurrences(vector<Element> &v);// listo - probar
  int getIndexFirstConsecutiveOcurrence(vector<Element> &v); // listo - probar
  int getOcurrences(vector<Element> &v);
  int getIndexFirstOcurrence(vector<Element> &v);
  CompactChainList getLexicographicFusion(CompactChainList &oth); // listo - probar
  list<Element> expand(); // listo - probar

  //Operaciones modificadoras
  void set(int p, Element e); // listo - probar
  void removeFirstOcurrence(Element e);// listo - probar
  void removeAllOcurrences(Element e); // listo - probar
  void removeBlockPosition(int p); // listo - probar
  void insertElement(int p, Element e); // listo - probar
  void modifyAllOcurrences(Element e1, Element e2); // listo - probar
  void push_front(Element e, int count); // listo - probar
  void push_back(Element e, int count); //listo - probar
  //static
  void sortVectirCCL(vector<CompactChainList> &v); // yuca
  void lol(); //falta

  //Sobrecarga de operadores
  CompactChainList operator+(CompactChainList &oth); // listo - probar
  Element operator[](int p); // listo - probar
  bool operator<(CompactChainList &oth); // no se si es asi 
  bool operator==(const CompactChainList &oth) const; //listo - probar
};

#endif
