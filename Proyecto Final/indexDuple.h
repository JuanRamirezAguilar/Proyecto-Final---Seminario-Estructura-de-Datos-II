#ifndef INDEXDUPLE_H
#define INDEXDUPLE_H

#include <string>
#include <iostream>

template <class DATA = std::string> 
class indexDuple {
    private:
        int index;
        DATA data;

    public:
        indexDuple();
        indexDuple(const indexDuple&);
        indexDuple(const int&, const DATA&);
        indexDuple(const DATA&);
        ~indexDuple();

        int getIndex()const;
        DATA getData() const;
        
        void setIndex(const int&);
        void setData(const DATA&);

        indexDuple& operator = (const indexDuple&);
        indexDuple& operator = (const DATA&);
        bool operator == (const indexDuple&);
        bool operator != (const indexDuple&);
        bool operator < (const indexDuple&);
        bool operator <= (const indexDuple&);
        bool operator > (const indexDuple&);
        bool operator >= (const indexDuple&);

        template <class x>
        friend std::istream& operator >> (std::istream&, indexDuple<x>&);
        template <class x>
        friend std::ostream& operator << (std::ostream&, indexDuple<x>&);

};

using namespace std;

template <class DATA>
indexDuple<DATA>::indexDuple() {}

template<class DATA>
indexDuple<DATA>::indexDuple(const indexDuple& t) : index(t.index), data(t.data) {}

template<class DATA>
inline indexDuple<DATA>::indexDuple(const int& i, const DATA &e) : index(i), data(e) {}

template<class DATA>
inline indexDuple<DATA>::indexDuple(const DATA &e) : data(e) {}

template <class DATA>
indexDuple<DATA>::~indexDuple() {}

template<class DATA>
inline int indexDuple<DATA>::getIndex() const { return index; }

template<class DATA>
inline DATA indexDuple<DATA>::getData() const { return data; }

template<class DATA>
inline void indexDuple<DATA>::setIndex(const int &i) {
    index = i;
}

template<class DATA>
inline void indexDuple<DATA>::setData(const DATA &e) { data = e; }

template<class DATA>
indexDuple<DATA> & indexDuple<DATA>::operator=(const indexDuple &t) {
    if (this == &t) {
        return *this;
    }

    this->index = t.index;
    this->data = t.data;

    return *this;
}

template<class DATA>
indexDuple<DATA>& indexDuple<DATA>::operator=(const DATA &e) {
    data = e;
    return *this;
}

template<class DATA>
inline bool indexDuple<DATA>::operator==(const indexDuple &t) {
    return (this->data == t.data);
}

template<class DATA>
inline bool indexDuple<DATA>::operator!=(const indexDuple &t) {
    return !(*this == t);
}

template<class DATA>
inline bool indexDuple<DATA>::operator<(const indexDuple &t) {
    return (this->index < t.index);
}

template<class DATA>
inline bool indexDuple<DATA>::operator<=(const indexDuple &t) {
    return (this->index <= t.index);
}

template<class DATA>
inline bool indexDuple<DATA>::operator>(const indexDuple &t) {
    return (this->index > t.index);
}

template<class DATA>
inline bool indexDuple<DATA>::operator>=(const indexDuple &t) {
    return (this->index >= t.index);
}

template<class x>
istream& operator >> (istream& is, indexDuple<x>& t) {
    string mySring;

    getline(is, mySring, '*');
    t.index = stoi(mySring);

    is >> t.data;

    return is;
}

template<class x>
ostream& operator << (ostream& os, indexDuple<x>& t) {
    os << t.index << "*";
    os << t.data << "*";
    return os;
}

template <class DATA>
std::ostream& operator<<(ostream& os, const indexDuple<DATA>& t) {
    os << t.getIndex() << "*" << t.getData() << "*";
    return os;
}

#endif
