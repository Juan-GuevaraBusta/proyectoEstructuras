#include "CompactChainList.h"
#include<algorithm>
#include<cstdio>
#include<cmath>

//Operaciones constructoras

//O(1), solo se realizan asignaciones
CompactChainList::CompactChainList() { 
  s = 0;
  midPos = 0;
  midSum = 0;
};

//O(n), donde n es el tamaño del vector
CompactChainList::CompactChainList(vector<Element> &v) { 
  Element aux;
  int count = 1;
  s = v.size();
  midSum = 0;
  
  if (!v.empty()) aux = v.at(0);
  for (int i = 1; i < v.size(); ++i) {
    if (v.at(i) == aux) {
      ++count;
    } else {
      l.push_back(make_pair(v.at(i - 1), count));
      count = 1;
      aux = v.at(i);
    }
  }
  if (!v.empty())
    l.push_back(make_pair(v.at(v.size() - 1), count));
  
  midPos = ceil(l.size()/2.0) - 1;
  list<pair<Element, int>>::iterator it = l.begin();
  
  for (int i = 0; i < ceil(l.size()/2.0); ++i) {
    midSum += (*it).second;
    ++it;
  }
  mid = --it;
};

// O(n), donde n es el tamaño de la ccl l2
CompactChainList::CompactChainList(CompactChainList &l2) {
  this -> s = l2.s;
  this -> midPos = l2.midPos;
  this -> midSum = l2.midSum;
  for (list<pair<Element, int>>::iterator it = l2.l.begin(); it != l2.l.end(); ++it)
    this -> l.push_back(*it);
  
  list<pair<Element, int>>::iterator it = l.begin();
  for (int i = 0; i <= midPos; ++i)
    ++it;
  mid = --it;
};
  
//Operaciones analizadoras

// O(1), solo se retorna una variable
int CompactChainList::size() { 
  return s;
};

//O(n) en el peor caso cuando el elemento no está o está en el último bloque donde n es el tamaño de la lsta interna l
//en el mejor caso cuando el elemento está en la primera posición de la lista interna la complejidad es O(1)
int CompactChainList::searchElement(Element e) {
  int ans = 0;
  bool flag = false;
  for (list<pair<Element, int>>::iterator it = l.begin(); it != l.end() && !flag; ++it) {
    if ((*it).first == e)
      flag = true;
    else
      ans += (*it).second;
  }
  if (!flag) ans = -1;
  return ans;
};


int CompactChainList::getConsecutiveOcurrences(vector<Element> &v) {
  list<pair<Element, int>>::iterator it1, it2, aux1, aux2;
  CompactChainList aux(v);
  int ans = 0, count = 0, rep;
  bool flag1 = false, flag2, flag3;
  for (it1 = l.begin(); it1 != l.end() && !v.empty() && !flag1; ++it1) {
    flag1 = l.size() - count < aux.size();
    it2 = aux.l.begin();
    rep = 0;
    flag3 = false;
    while (!flag1 && !flag3 && (*it1).first == (*it2).first && (*it1).second - rep >= (*it2).second) {
      flag2 = false;
      aux1 = it1;
      if (aux.l.size() > 1) ++aux1;
      for (it2 = ++aux.l.begin(); it2 != --aux.l.end() && aux.l.size() > 2 && !flag2; ++it2) {
	flag2 = (*it2) != (*aux1);
	++aux1;
      }
      if (!flag2) flag2 = (*(--aux.l.end())).second > (*aux1).second - rep;
      if (!flag2) ++ans;
      ++rep;
      it2 = aux.l.begin();
      flag3 = aux.l.size() > 1;
    }
    ++count;
  }
  return ans;
}

int CompactChainList::getIndexFirstConsecutiveOcurrence(vector<Element> &v) {
  list<pair<Element, int>>::iterator it1, it2, aux1, aux2;
  CompactChainList aux(v);
  int ans = 0, count = 0, indx = 0, rep;
  bool flag1 = false, flag2, flag3, flag4 = false;
  for (it1 = l.begin(); it1 != l.end() && !v.empty() && !flag1 && !flag4; ++it1) {
    flag1 = l.size() - count < aux.size();
    it2 = aux.l.begin();
    rep = 0;
    flag3 = false;
    while (!flag1 && !flag3 && !flag4 && (*it1).first == (*it2).first && (*it1).second - rep >= (*it2).second) {
      flag2 = false;
      aux1 = it1;
      if (aux.l.size() > 1) ++aux1;
      for (it2 = ++aux.l.begin(); it2 != --aux.l.end() && aux.l.size() > 2 && !flag2; ++it2) {
	flag2 = (*it2) != (*aux1);
	++aux1;
      }
      if (!flag2) flag2 = (*(--aux.l.end())).second > (*aux1).second - rep;
      if (!flag2) {
	++ans;
	flag4 = true;
      }
      ++rep;
      it2 = aux.l.begin();
      flag3 = aux.l.size() > 1;
    }
    indx += (*it1).second;
    ++count;
  }
  aux2 = it1;
  indx -= (*(--aux2)).second;
  if (flag4) {
    if (aux.l.size() > 1) indx += ((*(--it1)).second - (*(aux.l.begin())).second);
  } else {
    indx = -1;
  }
  return indx;
};

int CompactChainList::getOcurrences(vector<Element> &v) {
  list<pair<Element, int>>::iterator it1, it2, it3;
  CompactChainList aux(v);
  int ans = 0;
  bool flag1 = aux.l.empty(), flag2;
  for (it1 = l.begin(); it1 != l.end() && !flag1; ++it1) {
    it2 = aux.l.begin();
    it3 = it1;
    flag2 = false;
    while (!flag2 && it2 != aux.l.end() && it3 != l.end()) {
      if ((*it2).first == (*it3).first && (*it2).second <= (*it3).second)
        ++it2;
      ++it3;
      flag2 = it3 == l.end() && it2 != aux.l.end();
    }
    if (!flag2 && it2 == aux.l.end())
      ++ans;
  }
  return ans;
};

int CompactChainList::getIndexFirstOcurrence(vector<Element> &v) {
  list<pair<Element, int>>::iterator it1, it2, it3;
  CompactChainList aux(v);
  int ans = -1, idx = 0;
  bool flag1 = aux.l.empty(), flag2, flag3 = false;
  for (it1 = l.begin(); it1 != l.end() && !flag1 && !flag3; ++it1) {
    it2 = aux.l.begin();
    it3 = it1;
    flag2 = false;
    while (!flag2 && it2 != aux.l.end() && it3 != l.end()) {
      if ((*it2).first == (*it3).first && (*it2).second <= (*it3).second)
        ++it2;
      ++it3;
      flag2 = it3 == l.end() && it2 != aux.l.end();
    }
    if (!flag2 && it2 == aux.l.end()) {
      ans = idx;
      flag3 = true;
    }
    idx += (*it1).second;
  }
  if (flag1) ans = 0;
  return ans;
};

CompactChainList CompactChainList::getLexicographicFusion(CompactChainList &oth) {
  CompactChainList ans;
  list<pair<Element, int>>::iterator it1 = l.begin(), it2 = oth.l.begin();
  while (it1 != l.end() && it2 != oth.l.end()) {
    if ((*it1).first == (*it2).first) {
      ans.l.push_back(make_pair((*it1).first, (*it1).second + (*it2).second));
      ans.s += (*it1).second + (*it2).second;
      ++it1;
      ++it2;
    } else if ((*it1).first < (*it2).first) {
      ans.l.push_back(*it1);
      ans.s += (*it1).second;
      ++it1;
    } else {
      ans.l.push_back(*it2);
      ans.s += (*it2).second;
      ++it2;
    }
  }
  if (it1 != l.end()) {
    while (it1 != l.end()) {
      ans.l.push_back(*it1);
      ans.s += (*it1).second;
      ++it1;
    }
  } else if (it2 != oth.l.end()) {
    while (it2 != oth.l.end()) {
      ans.l.push_back(*it2);
      ans.s += (*it2).second;
      ++it2;
    }
  }
  ans.midPos = ceil(ans.l.size()/2.0) - 1;
  list<pair<Element, int>>::iterator it = ans.l.begin();
  for (int i = 0; i < ceil(ans.l.size()/2); ++i) {
    ans.midSum += (*it).second;
    ++it;
  }
  ans.mid = --it;
  return ans;
};

list<Element> CompactChainList::expand() {
  list<Element> ans;
  for (list<pair<Element, int>>::iterator it = l.begin(); it != l.end(); ++it)
    for (int i = 0; i < (*it).second; ++i)
      ans.push_back((*it).first);
  return ans;
};

//Operaciones modificadoras

void CompactChainList::set(int p, Element e) {
  list<pair<Element, int>>::iterator it = l.begin(), aux;
  int i = 0, indx = 0, iz, der, pos;
  if (p >= 0 && p < s) {
    if (p < midSum) {
      while (i <= p) {
	if (i != 0) {
	  ++it;
	  ++indx;
	}
	if (i + (*it).second > p) {
	  iz = p - i;
	  der = (*it).second - iz - 1;
	}
	i += (*it).second;
      }
    } else {
      it = --l.end();
      indx = l.size() - 1;
      while (i <= s - p - 1) {
	if (i != 0) {
	  --it;
	  --indx;
	}
	if (i + (*it).second > s - p - 1) {
	  iz = (*it).second - der - 1;
	  der = s - p - i - 1;
	}
	i += (*it).second;
      }
    }
    
    if ((*it).first != e && iz == 0 && der == 0) {
      (*it).first = e;
    } else if ((*it).first != e && iz == 0) {
      list<pair<Element, int>>::iterator it2 = mid;
      pos = ceil((l.size() + 1)/2.0) - 1;
      if (indx <= pos) {
	midSum -= ((*(++it2)).second - 1);
	(*it).second -= 1;
        if (pos != midPos && it == ++mid) {
	  l.insert(it, make_pair(e, 1));
	  it2 = mid;
	  mid = ++it2;
	} else if (pos == midPos) {
	  it2 = mid;
	  l.insert(it, make_pair(e, 1));
	  mid = --it2;
	} else {
	  l.insert(it, make_pair(e, 1));
	}
      } else {
	l.insert(it, make_pair(e, 1));
	if (pos != midPos) {
	  it2 = mid;
	  mid = ++it2;
	}
      }
      midPos = pos;
    } else if ((*it).first != e){
      list<pair<Element, int>>::iterator it2 = mid;
      pos = ceil((l.size() + 2)/2.0) - 1;
      if (indx <= pos) {
	if (indx == pos) {
	  midSum -= (der + 1);
	} else if (indx == pos - 1) {
	  midSum -= der;
	} else {
	  midSum -= (*mid).second;
	}
      }
      (*it).second -= (der + 1);
      if (it != --l.end()) {
	aux = it;
	l.insert(++aux, make_pair(e, 1));
	--aux;
	if (der != 0) l.insert(++aux, make_pair((*it).first, der));
      } else {
	l.push_back(make_pair(e, 1));
	if (der != 0) l.push_back(make_pair((*it).first, der));
      }
      if (indx >= pos || indx == midPos ) {
	aux = mid;
	mid = ++aux;
      } else if (indx < midPos) {
	aux = mid;
	mid = --aux;
      }
      midPos = pos;
    }
  }
}

void CompactChainList::removeFirstOcurrence(Element e) {
  list<pair<Element, int>>::iterator it = l.begin();
  bool flag = false;
  int i = 0, indx = 0;
  while (i < s && !flag) {    
    if (i != 0) {
      ++it;
      ++indx;
    }
    flag = (*it).first == e;
    i += (*it).second;
  }
  if (flag) {
    if ((*it).second > 1) {
      s -= 1;
      (*it).second -= 1;
      if (indx <= midPos)
	midSum -= 1;
    } else {
      remove(it, indx);
    }
    midPos = ceil(l.size()/2.0) - 1;
  }
};

void CompactChainList::removeAllOcurrences(Element e) {
  list<pair<Element, int>>::iterator it = l.begin(), aux, aux2;
  int i = 0;
  while (it != l.end()) {
    if ((*it).first == e) {
      aux = it;
      ++it;
      remove(aux, i);
      midPos = ceil(l.size() / 2.0) - 1;
    } else {
      ++it;
    }
    ++i;
  }
}

void CompactChainList::removeBlockPosition(int p) {
  list<pair<Element, int>>::iterator it = l.begin(), aux;
  int i = 0, indx = 0, pos;
  if (p >= 0 && p < s) {
    if (p < midSum) {
      while (i <= p) {
	if (i != 0) {
	  ++it;
	  ++indx;
	}
	i += (*it).second;
      }
    } else {
      it = --l.end();
      indx = l.size() - 1;
      while (i <= s - p - 1) {
	if (i != 0) {
	  --it;
	  --indx;
	}
	i += (*it).second;
      }
    }
    this -> remove(it, indx);
    midPos = ceil(l.size() / 2.0) - 1;
  }
};

void CompactChainList::remove(list<pair<Element, int>>::iterator it, int indx) {
  list<pair<Element, int>>::iterator aux;
  int pos;
  if (l.size() > 1) {
    list<pair<Element, int>>::iterator it2 = mid;
    pos = ceil((l.size() - 1)/2.0) - 1;
    if (indx <= midPos) {
      aux = it;
      midSum -= (*it).second;
      if (it != --l.end() && pos == midPos)
	midSum += (*(++aux)).second;
      aux = mid;
      if (pos != midPos && it == mid)
	mid = --aux;
      else if (pos == midPos) {
	aux = mid;
	mid = ++aux;
      }
    } else if (pos != midPos) {
      aux = mid;
      mid = --aux;
    }
    if (pos != midPos)
      pos -= 1;	  
  } else {
    midSum = 0;
    mid = l.end();
  }
  s -= (*it).second;
  l.erase(it);
};

void CompactChainList::insertElement(int p, Element e) {
  list<pair<Element, int>>::iterator it = l.begin(), aux;
  int i = 0, indx = 0, aux2 = s, iz, der, pos;
  if (p >= 0 && p < s) {
    s = ++aux2;
    if (p < midSum) {
      while (i <= p) {
	if (i != 0) {
	  ++it;
	  ++indx;
	}
	if (i + (*it).second > p) {
	  iz = p - i;
	  der = (*it).second - iz - 1;
	}
	i += (*it).second;
      }
    } else {
      it = --l.end();
      indx = l.size() - 1;
      while (i <= s - p - 1) {
	if (i != 0) {
	  --it;
	  --indx;
	}
	if (i + (*it).second > s - p - 1) {
	  iz = (*it).second - der - 1;
	  der = s - p - i - 1;
	}
	i += (*it).second;
      }
    }
    if ((*it).first == e) {
      (*it).second += 1;
      if (p <= midPos)
	midSum += 1;
    } else if (iz == 0) {
      list<pair<Element, int>>::iterator it2 = mid;
      pos = ceil((l.size() + 1)/2.0) - 1;
      if (indx <= pos) {
	midSum -= (*(++it2)).second;
	midSum += 1;
	if (pos != midPos && it == ++mid) {
	  l.insert(it, make_pair(e, 1));
	  it2 = mid;
	  mid = ++it2;
	} else if (pos == midPos) {
	  it2 = mid;
	  l.insert(it, make_pair(e, 1));
	  mid = --it2;
	} else {
	  it2 = mid;
	  l.insert(it, make_pair(e, 1));
	  mid = --it2;
	}
      } else {
	l.insert(it, make_pair(e, 1));
	if (pos != midPos) {
	  it2 = mid;
	  mid = ++it2;
	}
      }
      midPos = pos;
    } else {
      list<pair<Element, int>>::iterator it2 = mid;
      pos = ceil((l.size() + 2)/2.0) - 1;
      if (indx <= pos) {
	if (indx == pos) {
	  midSum -= (der + 1);
	} else if (indx == pos - 1) {
	  midSum -= der;
	} else {
	  midSum += 1;
	  midSum -= (*mid).second;
	}
      }
      (*it).second -= (der + 1);
      if (it != --l.end()) {
	aux = it;
	l.insert(++aux, make_pair(e, 1));
	--aux;
	l.insert(++aux, make_pair((*it).first, der + 1));
      } else {
	l.push_back(make_pair(e, 1));
	l.push_back(make_pair((*it).first, der + 1));
      }
      if (indx >= pos || indx == midPos ) {
	aux = mid;
	mid = ++aux;
      } else if (indx < midPos) {
	aux = mid;
	mid = --aux;
      }
      midPos = pos;
    }
  }
};


void CompactChainList::modifyAllOcurrences(Element e1, Element e2) {
  for (list<pair<Element, int>>::iterator it = l.begin(); it != l.end(); ++it) {
    if ((*it).first == e1)
      (*it).first = e2;
  }
};

void CompactChainList::push_front(Element e, int count) {
  int pos;
  s += count;
  if (!l.empty() && l.front().first == e) {
    l.front().second += count;
    midSum += count;
  } else {
    l.push_front(make_pair(e, count));
    pos = ceil(l.size()/2.0) - 1;
    if (pos > midPos) {
      midPos = pos;
      midSum += count;
    } else if (pos == midPos && l.size() != 1) {
      list<pair<Element, int>>::iterator it = mid;
      midSum -= (*mid).second;
      midSum += count;
      mid =  --it;
    } else {
      mid = l.begin();
      midSum = count;
    }
  }
};

void CompactChainList::push_back(Element e, int count) {
  int pos;
  s += count;
  if (!l.empty() && l.back().first == e) {
    l.back().second += count;
    if (l.size() == 1)
      midSum += count;
  } else {
    l.push_back(make_pair(e, count));
    pos = ceil(l.size()/2.0) - 1;
    if (pos > midPos) {
      list<pair<Element, int>>::iterator it = mid;
      mid = ++it;
      midPos = pos;
      midSum += (*mid).second;
    } else if (l.size() == 1) {
      mid = l.begin();
      midSum = count;
    }
  }
};

//static
void CompactChainList::sortVectirCCL(vector<CompactChainList> &v) {
  //sort(v.begin(), v.end());
};

//falta
void CompactChainList::print() {
  list<pair<Element, int>>::iterator it;
  printf("Size: %d, Blocks: %d, Midpos: %d, Mid: {%d, %d},  MidSum: %d\n", s, l.size(), midPos, (*mid).first, (*mid).second, midSum);
  
  printf("[");
  for (it = l.begin(); it != --l.end(); ++it)
    printf("{%d, %d},", (*it).first, (*it).second);
  if (!l.empty())
    printf("{%d, %d}]\n", (*it).first, (*it).second);
  else
    printf("]\n");
};

//Sobrecarga de operadores

CompactChainList CompactChainList::operator+(CompactChainList &oth) {
  CompactChainList ans = this -> getLexicographicFusion(oth);
  return ans;
};

Element CompactChainList::operator[](int p) {
  Element ans;
  list<pair<Element, int>>::iterator it = l.begin();
  int i = 0;
  if (p < midSum) {
    while (i <= p) {
      if (i != 0) ++it;
      i += (*it).second;
    }
  } else {
    it = --l.end();
    while (i <= s - p - 1) {
      if (i != 0) --it;
      i += (*it).second;
    }
  }
  ans = (*it).first;
  return ans;
};

bool CompactChainList::operator<(CompactChainList &oth) {
  bool ans = this -> s == oth.s;
  list<pair<Element, int>>::iterator it2 = oth.l.begin();
  for (list<pair<Element, int>>::iterator it1 = l.begin(); it1 != l.end() && ans; ++it1) {
    if ((*it1).first > (*it2).first) ans = false;
    ++it2;
  }
  return ans;
};

//O(n) en el peor caso cuando las listas son de igual size y tamaño de la lista interna, todos sus elementos son iguales o
// difieren solo en el último bloque, donde n es el tamaño de la lista interna, en el mejor de los casos es O(1) cuando las
//listas internas de las ccl difieren de size o tamaño de la lista interna

bool CompactChainList::operator==(const CompactChainList &oth) const {
  bool ans = s == oth.s && l.size() == oth.l.size();
  list<pair<Element, int>>::const_iterator it2 = oth.l.cbegin();
  for (list<pair<Element, int>>::const_iterator it1 = l.cbegin(); it1 != l.cend() && ans; ++it1) {
    if ((*it1).first != (*it2).first || (*it1).second != (*it2).second) ans = false;
    ++it2;
  }
  return ans;
};
