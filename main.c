#include "node.h"
#include "iostream"
#include "execution"
#include <chrono>

template <class T>
class Tlist {
private: 
    class TIterator <T> s;
public:
    TNode<T>* _head;
    TNode<T>* _tail;
public:
    typedef TIterator<T> iterator;
    Tlist();
    Tlist(const Tlist<T>& list);
    Tlist<T>& operator=(const Tlist<T>& list);
    ~Tlist();
    void push_front(const T& value) noexcept;
    void push_back(const T& value) noexcept;
    void insert(TNode<T>* node, T value);
    void insert(size_t pos, T value);
    TNode<T>* find(const T& value) const noexcept;
    TNode<T>* find_pos(size_t pos) const;
    TNode<T>* find_pres(TNode<T>* node) const noexcept;
    void pop_front();
    void pop_back();
    TIterator<T> begin() {

    }

    void erase(TNode <T>* node);
    void erase(size_t pos);
    bool isEmpty() const noexcept;
    void replace(TNode<T>* node, T value) const;
    void replace(size_t pos, T value) const;
    int get_size() const noexcept;
    void print() const noexcept;
    void qsort() noexcept;
    bool check_cycle_rabbit_turtle() noexcept;
    bool check_cycle_reverse_list() noexcept;
    long int test_time_algorithm_rabbit_turtle() noexcept;
    long int test_time_algorithm_reverse_list() noexcept;
private:
    template <class T>
    class TIterator {
        TNode<T>* _pcur;
        public:
            TIterator() {
                _pcur = _head;
            }
            TIterator(TIterator<T> iter) {
                _pcur = iter._pcur;
            }
            TIterator<T>& operator++() {
                TIterator<T> prev = new TIterator<T>(*this);
                _pcur = _pcur->next();
                return *prev;
            }
            TIterator<T> operator++(TIterator<T>& iter) {
                iter._pcur = _pcur->next();
                return iter;
            }
            bool operator!=(const TIterator<T>& iter) const noexcept {
                return this != nullptr;
            }
            bool operator==(const TIterator<T>& iter) const noexcept {
                return (*this)._pcur->value() == iter._pcur->value();
            }
    };
};

template <class T>
Tlist<T>::Tlist() {
    _head = _tail = nullptr;
}

template <class T>
Tlist<T>::Tlist(const Tlist<T>& list) {
    _head = list._head;
    _tail = list._tail;
}

template <class T>
Tlist<T>& Tlist<T>::operator=(const Tlist<T>& list) {
    if (&list != this) {
        _head = list._head;
        _tail = list._tail;
    }
    return *this;
}

template <class T>
Tlist<T>::~Tlist() {
    TNode<T>* cur = _head;
    TNode<T>* to_del;
    while (cur != nullptr) {
        to_del = cur;
        cur = cur->next();
        to_del = nullptr;
    }

}

template <class T>
bool Tlist<T>::isEmpty() const noexcept {
    return _head == nullptr;
}

template<class T>
int Tlist<T>::get_size() const noexcept {
    TNode<T>* node = _head;
    size_t total = 0;
    while (node != nullptr) {
        total++;
        node = node->next();
    }
    return total;
}

template <class T>
void Tlist<T>::insert(TNode<T>* node, T value) {
    if (node == nullptr) {
        throw std::logic_error("invalid pointer");
    }
    TNode<T>* new_node = new TNode<T>(value, node->next());
    node->next(new_node);
    if (node == _tail) {
        _tail = new_node;
    }
}

template <class T>
void Tlist<T>::push_front(const T& value) noexcept {
    TNode<T>* node = new TNode<T>(value);
    if (isEmpty()) {
        _tail = node;
    }
    else {
        node->next(_head);
    }
    _head = node;
}

template <class T>
void Tlist<T>::push_back(const T& value) noexcept {
    TNode<T>* node = new TNode<T>(value);
    if (isEmpty()) {
        _head = node;
    }
    else {
        _tail->next(node);
    }
    _tail = node;
}

template <class T>
TNode<T>* Tlist<T>::find(const T& value) const noexcept {
    TNode<T>* cur = _head;
    while (cur != nullptr) {
        if (cur->value() == value) {
            return cur;
        }
        cur = cur->next();
    }
    return nullptr;
}

template <class T>
TNode<T>* Tlist<T>::find_pos(size_t pos) const {
    size_t total = 0;
    TNode<T>* cur = _head;
    while (total != pos) {
        if (cur == nullptr)
            throw std::logic_error("invalid pointer");
        total++;
        cur = cur->next();
    }
    return cur;
}

template <class T>
TNode<T>* Tlist<T>::find_pres(TNode<T>* node) const noexcept {
    TNode<T>* cur = _head;
    while (cur->next() != node) {
        cur = cur->next();
    }
    return cur;
}

template <class T>
void Tlist<T>::insert(size_t pos, T value) {
    if (pos<0 || pos>get_size() - 1) {
        throw std::logic_error("invalid position");
    }
    TNode<T>* cur = find_pos(pos);
    TNode<T>* node = new TNode<T>(value, cur);
    if (cur == _head) {
        _head = node;
    }
    if (cur->next() == nullptr)
        _tail = node;
    else {
        TNode<T>* pred = find_pres(cur);
        pred->next(node);
    }
}

template <class T>
void Tlist<T>::pop_front() {
    if (isEmpty()) {
        throw std::logic_error("error isEmpty");
    }
    TNode<T>* new_head = _head->next();
    _head = nullptr;
    _head = new_head;
}

template <class T>
void Tlist<T>::pop_back() {
    if (isEmpty()) {
        throw std::logic_error("error isEmpty");
    }
    else if (_head == _tail) {
        _head = nullptr;
    }
    else {
        TNode<T>* new_tail = find_pres(_tail);
        _tail = nullptr;
        _tail = new_tail;
    }
}

template <class T>
void Tlist<T>::erase(TNode <T>* node) {
    if (node == nullptr) {
        throw std::logic_error("invalid pointer");
    }
    else if (node == _head) {
        pop_front();
    }
    else if (node == _tail) {
        pop_back();
    }
    else {
        TNode<T>* node_pres = find_pres(node);
        node_pres->next(node->next());
        node = nullptr;
    }
}

template <class T>
void Tlist<T>::erase(size_t pos) {
    if (pos<0 || pos>get_size() - 1) {
        throw std::logic_error("invalid pointer");
    }
    TNode <T>* cur = find_pos(pos);
    if (cur == _head) {
        pop_front();
    }
    else if (cur == _tail) {
        pop_back();
    }
    else {
        TNode <T>* pred = find_pres(cur);
        pred->next(cur->next());
        cur = nullptr;
    }
}

template <class T>
void Tlist<T>::replace(TNode<T>* node, T value) const {
    if (node == nullptr) {
        throw std::logic_error("invalid pointer");
    }
    node->value(value);
}

template <class T>
void Tlist<T>::replace(size_t pos, T value) const {
    if (pos<0 || pos>get_size() - 1) {
        throw std::logic_error("invalid position");
    }
    TNode<T>* node = find_pos(pos);
    node->value(value);
}

template<class T>
void Tlist<T>::print() const noexcept {
    TNode<T>* cur = _head;
    while (cur != _tail) {
        std::cout << cur->value() << " ";
        cur = cur->next();
    }
    std::cout << cur->value() << std::endl;
}

// template <class T>
// void qsort(Tlist<T> list) noexcept{
//     int cur = list.get_size();
//     TNode<T>* var = list._head;
//     while(cur>0){
//         var = list._head;
//         while(var->next()!=nullptr){
//             if (var->value()>(var->next()->value())){
//                 TNode<T>* nex = var->next();
//                 if (var == list._head){
//                     list.insert(nex, var->value());
//                     list._head = nullptr;
//                     list._head = nex;
//                 }
//                 else{
//                     TNode<T>* pred = list.find_pres(var);
//                     list.insert(nex, var->value());
//                     pred->next(nex);
//                 }
//                 var = nullptr;
//                 var = nex;
//             }
//             var = var->next();
//         }
//         if (cur == 0)
//             list._tail = var;
//         cur--;
//     }
// };

template <class T>
void Tlist<T>::qsort() noexcept {
    int cur = get_size();
    TNode<T>* var = _head;
    while (cur > 0) {
        var = _head;
        while (var->next() != nullptr) {
            if (var->value() > (var->next()->value())) {
                TNode<T>* nex = var->next();
                if (var == _head) {
                    insert(nex, var->value());
                    _head = nullptr;
                    _head = nex;
                }
                else {
                    TNode<T>* pred = find_pres(var);
                    insert(nex, var->value());
                    pred->next(nex);
                }
                var = nullptr;
                var = nex;
            }
            var = var->next();
        }
        if (cur == 0)
            _tail = var;
        cur--;
    }
};

template<class T>
bool Tlist<T>::check_cycle_rabbit_turtle() noexcept {
    TNode<T>* turtle = _head;
    TNode<T>* rabbit = _head;

    while (rabbit != nullptr && rabbit->next() != nullptr) {
        rabbit = rabbit->next()->next();
        turtle = turtle->next();

        if (rabbit == turtle) {
            return true;
        }
    }
    return false;
}

template <class T>
bool Tlist<T>::check_cycle_reverse_list() noexcept {
    TNode<T>* cur = _head->next();
    TNode<T>* prev = _head;
    while (cur->next() != nullptr) {
        TNode<T>* next = cur->next();
        cur->next(prev);
        if (next == _head) {
            return true;
        }
        prev = cur;
        cur = next;
    }
    return false;
}

template <class T>
long int Tlist<T>::test_time_algorithm_rabbit_turtle() noexcept {
    auto start = std::chrono::high_resolution_clock::now();
    bool has_cycle_rabbit_turtle = this->check_cycle_rabbit_turtle();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_rabbit_turtle = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return duration_rabbit_turtle;
}

template <class T>
long int Tlist<T>::test_time_algorithm_reverse_list() noexcept {
    auto start = std::chrono::high_resolution_clock::now();
    bool has_cycle_reverse_list = this->check_cycle_reverse_list();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_reverse_list = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return duration_reverse_list;
}
