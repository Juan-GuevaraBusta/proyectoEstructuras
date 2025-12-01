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
  list<pair<Element, int>>::iterator  mid;
  int s;
  int midPos;
  int midSum;

  void remove(list<pair<Element, int>>::iterator it, int indx); // listo - probar
  
 public:
  //Operaciones constructoras
  CompactChainList();
  CompactChainList(vector<Element> &v);
  CompactChainList(CompactChainList &l2);
  
  //Operaciones analizadoras
  int size();
  int searchElement(Element e);
  int getConsecutiveOcurrences(vector<Element> &v);
  int getIndexFirstConsecutiveOcurrence(vector<Element> &v);
  int getOcurrences(vector<Element> &v);
  int getIndexFirstOcurrence(vector<Element> &v);
  CompactChainList getLexicographicFusion(CompactChainList &oth);
  list<Element> expand();

  //Operaciones modificadoras
  void set(int p, Element e);
  void removeFirstOcurrence(Element e);
  void removeAllOcurrences(Element e);
  void removeBlockPosition(int p);
  void insertElement(int p, Element e);
  void modifyAllOcurrences(Element e1, Element e2);
  void push_front(Element e, int count);
  void push_back(Element e, int count);
  void sortVectorCCL(vector<CompactChainList> &v);
  void print();
  
  //Sobrecarga de operadores
  CompactChainList operator+(CompactChainList &oth);
  Element operator[](int p);
  bool operator<(CompactChainList &oth);
  bool operator==(const CompactChainList &oth) const;
  CompactChainList& operator=(const CompactChainList &oth);
};

#endif
