#include "CompactChainList.h"
#include<algorithm>
#include<cstdio>
#include<cmath>

//Operaciones constructoras
CompactChainList::CompactChainList() {
  this -> s = 0;
  this -> midPos = 0;
  this -> midSum = 0;
};

CompactChainList::CompactChainList(vector<Element> &v) {
  Element aux;
  int count = 1;
  this -> s = v.size();
  this -> midSum = 0;
  
  if (!v.empty()) aux = v.at(0);
  for (int i = 1; i < v.size(); ++i) {
    if (v.at(i) == aux) {
      ++count;
    } else {
      this -> l.push_back(make_pair(v.at(i - 1), count));
      count = 1;
      aux = v.at(i);
    }
  }
  if (!v.empty())
    this -> l.push_back(make_pair(v.at(v.size() - 1), count));
  
  this -> midPos = ceil(l.size()/2) - 1;
  list<pair<Element, int>>::iterator it = l.begin();
  for (int i = 0; i < ceil(l.size()/2); ++i) {
    this -> midSum += (*it).second;
    ++it;
  }
  this -> mid = --it;
};

CompactChainList::CompactChainList(CompactChainList &l2) {
  this -> s = l2.s;
  this -> midPos = l2.midPos;
  this -> midSum = l2.midSum;
  for (list<pair<Element, int>>::iterator it = l2.l.begin(); it != l2.l.end(); ++it)
    this -> l.push_back(*it);
  
  list<pair<Element, int>>::iterator it = l.begin();
  for (int i = 0; i <= midPos; ++i)
    ++it;
  this -> mid = --it;
};
  
//Operaciones analizadoras

int CompactChainList::size() {
  return s;
};

int CompactChainList::searchElement(Element e) {
  int ans = 0;
  bool flag = false;
  for (list<pair<Element, int>>::iterator it = l.begin(); it != l.end() && !flag; ++it) {
    if ((*it).first == e)
      flag = true;
    else
      ans += (*it).second;
  }
  return ans;
};

int CompactChainList::getConsecutiveOcurrences(vector<Element> &v) {
  list<Element> l1 = this -> expand();
  int ans = 0, count = 0;
  bool flag1 = false, flag2;
  for (list<Element>::iterator it = l1.begin(); it != l1.end() && !v.empty() && !flag1; ++it) {
    flag2 = false;
    if (l1.size() - count < v.size()) flag1 = true;
    if (!flag1 && *it == v[0]) {
      list<Element>::iterator it2 = ++it;
      for (int i = 1; i < v.size() && !flag2; ++i) {
	if (*it2 != v[i]) flag2 = true;
	++it2;
      }
      if (!flag2) ++ans;
    }
    ++count;
  }
  return ans;
};

int CompactChainList::getIndexFirstConsecutiveOcurrence(vector<Element> &v) {
  list<Element> l1 = this -> expand();
  int ans = 0, count = 0, acc = 0;
  bool flag1 = false, flag2, flag3 = false;
  for (list<Element>::iterator it = l1.begin(); it != l1.end() && !v.empty() && !flag1 && !flag3; ++it) {
    flag2 = false;
    if (l1.size() - count < v.size()) flag1 = true;
    if (!flag1 && *it == v[0]) {
      list<Element>::iterator it2 = ++it;
      for (int i = 1; i < v.size() && !flag2; ++i) {
	if (*it2 != v[i]) flag2 = true;
	++it2;
      }
      if (!flag2) flag3 = true;
    }
    ++count;
  }
  if (!flag3)
    ans = l.size();
  else
    ans = --count;
  return ans;
};

int CompactChainList::getOcurrences(vector<Element> &v) {
  int ans = 0;
  if (!v.empty()) {
    list<Element> seq = this -> expand();
    if (!seq.empty()) {
      vector<Element> sequence;
      for (list<Element>::iterator it = seq.begin(); it != seq.end(); ++it) 
        sequence.push_back(*it); 
      int seqSize = sequence.size();
      int vSize = v.size();
      if (seqSize >= vSize) {
        vector<pair<int, int>> stack;
        stack.push_back(make_pair(0, 0));
        
        bool flag = false;
        while (!stack.empty() && !flag) {
          pair<int, int> actual = stack.back();
          stack.pop_back();
          int posSeq = actual.first;
          int posV = actual.second;
          if (posV >= vSize)
            ans++;
          else if (posSeq < seqSize) {
            bool encontrado = false;
            for (int i = posSeq; i < seqSize && !encontrado; ++i) {
              if (sequence[i] == v[posV]) {
                stack.push_back(make_pair(i + 1, posV + 1));
                encontrado = false; 
              }
            }
          }
        }
      }
    }
  }
  
  return ans;
};

int CompactChainList::getIndexFirstOcurrence(vector<Element> &v) {
  int ans = -1;
  if (!v.empty()) {
    list<Element> seq = this -> expand();
    if (!seq.empty()) {
      vector<Element> sequence;
      for (list<Element>::iterator it = seq.begin(); it != seq.end(); ++it)
        sequence.push_back(*it);
      int seqSize = sequence.size();
      int vSize = v.size();
      if (seqSize >= vSize) {
        bool flag = false;
        for (int inicio = 0; inicio < seqSize && ans == -1 && !flag; ++inicio) {
          if (sequence[inicio] == v[0]) {
            vector<pair<int, int>> stack;
            stack.push_back(make_pair(inicio + 1, 1));
            bool encontrado = false;
            while (!stack.empty() && !encontrado && !flag) {
              pair<int, int> actual = stack.back();
              stack.pop_back();
              int posSeq = actual.first;
              int posV = actual.second;
              if (posV >= vSize) {
                ans = inicio;
                encontrado = true;
                flag = true;
              }
              else if (posSeq < seqSize) {
                bool encontrado2 = false;
                for (int i = posSeq; i < seqSize && !encontrado2; ++i) {
                  if (sequence[i] == v[posV]) {
                    stack.push_back(make_pair(i + 1, posV + 1));
                    encontrado2 = false;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
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
  ans.midPos = ceil(ans.l.size()/2) - 1;
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
  int i = 0, indx = 0, aux2 = s, iz, der, pos;
  if (p >= 0 && p < s) {
    if (p < midSum) {
      while (i <= p) {
	if (i != 0) {
	  ++it;
	  ++indx;
	}
	if (i += (*it).second > p) {
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
	if (i += (*it).second > s - p - 1) {
	  iz = (*it).second - der - 1;
	  der = s - p - i - 1
	}
	i += (*it).second;
      }
    }
    
    if ((*it).first != e && iz == 0) {
      list<pair<Element, int>>::iterator it2 = mid;
      pos = ceil((l.size() + 1)/2) - 1;
      if (indx <= pos) {
	midsum -= (*(++it2)).second;
	(*(++it2)).second -= 1;
	midsum += 1;
      } else {
	it2 = mid;
	mid = ++it2;
	midPos = pos;
      }
      l.insert(it, make_pair(e, 1));
    } else {
      list<pair<Element, int>>::iterator it2 = mid;
      pos = ceil((l.size() + 2)/2) - 1;
      if (indx <= pos) {
	if (indx == pos) {
	  midsum -= (der + 1);
	} else if (indx == pos - 1) {
	  midsum -= der;
	  midsum -= (*mid).second;
	} else {
	  aux = mid;
	  midsum += 1;
	  midsum -= (*mid).second;
	  midsum -= (*(--aux)).second;
	}
      }
      (*it).second -= (der + 1);
      if (it != --l.end()) {
	aux = it;
	l.insert(++aux, make_pair((*it).first, der + 1));
	l.insert(++aux, make_pair(e, 1));
      } else {
	l.push_back(make_pair(e, 1));
	l.push_back(make_pair((*it).first, der + 1));
      }
      midpos = pos;
      aux = mid;
      mid = ++aux;
    }
  }
}

void CompactChainList::set(int p, Element e) {
  //FALTAA
  list<pair<Element, int>>::iterator it = l.begin(), aux;
  int i = 0, rem, indx = 0;
  if (p >= 0 && p < s) {
    while (i < p && p < s) {
      i += (*it).second;
      if (i <= p) ++it;
    }
    aux = it;
    if ((*it).first != e && (*it).second > 1 && p < s) {
      if (i == p)
	if (it != --l.end())
	  l.insert(++aux, make_pair((*it).first, (*it).second - 1));
	else
	  l.push_back(make_pair((*it).first,  (*it).second - 1));
      else if (i > p && i - (*it).second  + 1 == p) 
	l.insert(it, make_pair((*it).first, (*it).second - 1));
      else {
	rem = p - (i - (*it).second);
	l.insert(it, make_pair((*it).first, rem));
	if (it != --l.end())
	  l.insert(++aux, make_pair((*it).first, (*it).second - rem));
	else
	  l.push_back(make_pair((*it).first, (*it).second - rem));
      }
      (*it).first = e;
      (*it).second = 1;
    } else if ((*it).first != e && p < s)
      (*it).first = e;
  }
};

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
	if (i += (*it).second > p) {
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
	if (i += (*it).second > s - p - 1) {
	  iz = (*it).second - der - 1;
	  der = s - p - i - 1
	}
	i += (*it).second;
      }
    }
    
    if ((*it).first != e && iz == 0 && der == 0) {
      (*it).first = e;
    } else if ((*it).first != e && iz == 0) {
      list<pair<Element, int>>::iterator it2 = mid;
      pos = ceil((l.size() + 1)/2) - 1;
      if (indx <= pos) {
	midsum -= ((*(++it2)).second - 1);
	(*it).second -= 1;
        if (pos != midpos && it == ++mid) {
	  l.insert(it, make_pair(e, 1));
	  it2 = mid;
	  mid = ++it2;
	} else if (pos == midpos) {
	  it2 = mid;
	  l.insert(it, make_pair(e, 1));
	  mid = --it2;
	} else {
	  l.insert(it, make_pair(e, 1));
	}
      } else {
	l.insert(it, make_pair(e, 1));
	if (pos != midpos) {
	  it2 = mid;
	  mid = ++it2;
	}
      }
      midpos = pos;
    } else if ((*it).first != e){
      list<pair<Element, int>>::iterator it2 = mid;
      pos = ceil((l.size() + 2)/2) - 1;
      if (indx <= pos) {
	if (indx == pos) {
	  midsum -= (der + 1);
	} else if (indx == pos - 1) {
	  midsum -= der;
	} else {
	  midsum -= (*mid).second;
	}
      }
      (*it).second -= (der + 1);
      if (it != --l.end()) {
	aux = it;
	l.insert(++aux, make_pair((*it).first, der));
	l.insert(++aux, make_pair(e, 1));
      } else {
	l.push_back(make_pair(e, 1));
	l.push_back(make_pair((*it).first, der));
      }
      if (indx >= pos || indx == midpos ) {
	aux = mid;
	mid = ++aux;
      } else if (indx < midpos) {
	aux = mid;
	mid = --aux;
      }
      midpos = pos;
    }
  }
}

void CompactChainList::removeFirstOcurrence(Element e) {
  list<pair<Element, int>>::iterator it;
  bool flag;
  int i = 0, indx;
  
  while (i <= p && !flag) {
    flag = (*it).first == e;
    if (i != 0) {
      ++it;
      ++indx;
    }
    i += (*it).second;
  }

  if (flag) {
    s -= 1;
    if ((*it).second > 1) {
      (*it).second -= 1;
      if (indx <= midpos)
	midSum -= 1;
    } else {
      remove(it, indx);
    }  
  }
};

void CompactChainList::removeAllOcurrences(Element e) {
  list<pair<Element, int>>::iterator it = l.begin(), aux, aux2;
  int i = 0;
  while (it != l.end()) {
    if ((*it).first == e) {
      aux = it;
      ++it;
      remove(it, i);
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
  }
};

void CompactChainList::remove(list<pair<Element, int>>::iterator it, int indx) {
  if (l.size() > 1) {
    list<pair<Element, int>>::iterator it2 = mid;
    pos = ceil((l.size() - 1)/2) - 1;
    if (indx <= midpos) {
      aux = it;
      midsum -= (*it).second;
      if (it != --l.end() && pos == midpos)
	midsum += (*(++aux)).second;
      aux = mid;
      if (pos != midpos && it == mid)
	mid = --aux;
      else if (pos == midpos) {
	aux = mid;
	mid = ++aux;
      }
    } else if (pos != midpos) {
      aux = mid;
      mid = --aux;
    }
    if (pos != midpos)
      pos -= 1;	  
  } else {
    midsum = 0;
    mid = NULL;
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
	if (i += (*it).second > p) {
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
	if (i += (*it).second > s - p - 1) {
	  iz = (*it).second - der - 1;
	  der = s - p - i - 1
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
      pos = ceil((l.size() + 1)/2) - 1;
      if (indx <= pos) {
	midsum -= (*(++it2)).second;
	midsum += 1;
	if (pos != midpos && it == ++mid) {
	  l.insert(it, make_pair(e, 1));
	  it2 = mid;
	  mid = ++it2;
	} else if (pos == midpos) {
	  it2 = mid;
	  l.insert(it, make_pair(e, 1));
	  mid = --it2;
	} else {
	  l.insert(it, make_pair(e, 1));
	}
      } else {
	l.insert(it, make_pair(e, 1));
	if (pos != midpos) {
	  it2 = mid;
	  mid = ++it2;
	}
      }
      midpos = pos;
    } else {
      list<pair<Element, int>>::iterator it2 = mid;
      pos = ceil((l.size() + 2)/2) - 1;
      if (indx <= pos) {
	if (indx == pos) {
	  midsum -= (der + 1);
	} else if (indx == pos - 1) {
	  midsum -= der;
	} else {
	  midsum += 1;
	  midsum -= (*mid).second;
	}
      }
      (*it).second -= (der + 1);
      if (it != --l.end()) {
	aux = it;
	l.insert(++aux, make_pair((*it).first, der + 1));
	l.insert(++aux, make_pair(e, 1));
      } else {
	l.push_back(make_pair(e, 1));
	l.push_back(make_pair((*it).first, der + 1));
      }
      if (indx >= pos || indx == midpos ) {
	aux = mid;
	mid = ++aux;
      } else if (indx < midpos) {
	aux = mid;
	mid = --aux;
      }
      midpos = pos;
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
  s += count;
  if (!l.empty() && l.front().first == e) {
    l.front().second += count;
    midSum += count;
  } else {
    l.push_front(make_pair(e, count));
    pos = ceil(l.size()/2) - 1;
    if (pos > midPos) {
      midPos = pos;
      midSum += count;
    } else if (pos == midPos && l.size() != 1) {
      list<pair<Element, int>>::iterator it = mid;
      midSum -= mid.second;
      midsum += count;
      mid =  --it;
    } else {
      mid = l.begin();
      midSum = count;
    }
  }
};

void CompactChainList::push_back(Element e, int count) {
  s += count;
  if (!l.empty() && l.back().first == e) {
    l.back().second += count;
    if (l.size() == 1)
      midSum += count;
  } else {
    l.push_back(make_pair(e, count));
    pos = ceil(l.size()/2) - 1;
    if (pos > midPos) {
      list<pair<Element, int>>::iterator it = mid;
      mid = ++it;
      midPos = pos;
      midSum += mid.second;
    } else if (l.size() == 1) {
      mid = l.begin();
      midSum = count;
    }
  }
};

static void CompactChainList::sortVectirCCL(vector<CompactChainList> &v) {
  sort(v.begin(), v.end());
};

//falta
void CompactChainList::lol() {
  list<pair<Element, int>>::iterator it;
  printf("<");
  for (it = l.begin(); it != --l.end(); ++it)
    printf("(%d, %d), ", (*it).first, (*it).second);
  if (!l.empty())
    printf("(%d, %d)>\n", (*it).first, (*it).second);
  else
    printf(">\n");
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

//confirmar si es así ??
bool CompactChainList::operator<(CompactChainList &oth) {
  bool ans = this -> s == oth.s;
  list<pair<Element, int>>::iterator it2 = oth.l.begin();
  for (list<pair<Element, int>>::iterator it1 = l.begin(); it1 != l.end() && ans; ++it1)
    if ((*it1) > (*it2)) ans = false;
  return ans;
};

bool CompactChainList::operator==(const CompactChainList &oth) const {
  bool ans = this -> s == oth.s;
  list<pair<Element, int>>::const_iterator it2 = oth.l.cbegin();
  for (list<pair<Element, int>>::const_iterator it1 = l.cbegin(); it1 != l.cend() && ans; ++it1)
    if ((*it1) != (*it2)) ans = false;
  return ans;
};
