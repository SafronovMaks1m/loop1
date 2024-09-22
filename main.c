#include "iostream"
#define STEP_CAPACITY 15

enum State { empty, busy, deleted };

template<typename T>
class TDMassive{
    T* _data;                  
    State* _states;
    size_t _capacity;        
    size_t _size;              
    size_t _deleted;           
    public:
        TDMassive();
        TDMassive(const TDMassive& archive);
        TDMassive(const T* arr, size_t n);
        TDMassive(size_t n, T value);
        TDMassive(const TDMassive& archive, size_t pos, size_t n);

        ~TDMassive();

        void print() const noexcept;

        inline bool empty() const noexcept;
        inline bool full() const noexcept;

        size_t size();
        size_t capacity();
        const T* data();

        void overexposure();

        void push_back(T value);

        void pop_back();

        void push_front(T value);

        void pop_front();

        TDMassive& insert(T value, size_t pos);

        TDMassive& replace(size_t pos, T new_value); 

        TDMassive& remove_all(T value);

        TDMassive& remove_last(T value);

        TDMassive& remove_by_index(size_t pos);

        size_t* find_all(T value) const noexcept;

        size_t find_first(T value);

        size_t find_last(T value);

private:
    size_t count_value(T value); //????????
};

template <typename T>
TDMassive<T>::TDMassive() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < STEP_CAPACITY; i++) {
        _states[i] = State::empty;
    }
}

template <typename T>
TDMassive<T>::TDMassive(const TDMassive& archive){
    _size = archive._size;
    _capacity = archive._capacity;
    _deleted = archive._deleted;
    for (size_t i = 0; i<_capacity; i++){
        _data[i] = archive._data[i];
        _states[i] = archive._states[i]
    }
}

template <typename T>
TDMassive<T>::TDMassive(const T* arr, size_t n){
    _size = n;
    _capacity = (n/15+1)*15;
    _deleted = 0;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i<_capacity; i++){
        if (i<n){
            _data[i] = arr[i];
            _states[i] = State::busy;}
        else{
            _states[i] = State::empty;}
    }
}

template <typename T>
TDMassive<T>::TDMassive(size_t n, T value){
    _size = n;
    _capacity = (n/15+1)*15;
    _deleted = 0;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i<_capacity; i++){
        if (i<n){
            _data[i] = value;
            _states[i] = State::busy;}
        else{
            _states[i] = State::empty;}
    }
}

template <typename T>
TDMassive<T>::TDMassive(const TDMassive& archive, size_t pos, size_t n){
    _size = n;
    _capacity = (n/15+1)*15;
    _deleted = 0;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i<_capacity; i++){
        if (i<n){
            _data[i] = archive[i+pos-1];
            _states[i] = State::busy;}
        else{
            _states[i] = State::empty;}
    }
}

template <typename T>
TDMassive<T>::~TDMassive() {
    delete[] _data;
    _data = nullptr;
}

template <typename T>
void TDMassive<T>::print() const noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] != State::deleted) {
            std::cout << _data[i] << ", ";
        }
    }
}

template <typename T>
inline bool TDMassive<T>::empty() const noexcept {
    return _size == 0;
}

template <typename T>
inline bool TDMassive<T>::full() const noexcept {
    return _size == _capacity;
}

template <typename T>
size_t TDMassive<T>::size(){
    return _size;
}

template <typename T>
size_t TDMassive<T>::capacity(){
    return _capacity;
}

template <typename T>
const T* TDMassive<T>::data(){
    return data;
}

template <typename T>
void TDMassive<T>::overexposure(){
    if (_deleted == 0){
        _capacity+=15;
        int* array = new T[_size];
        _states = new State[_capacity];
        for(size_t i = 0; i < _capacity; i++){
            if (i<_size){
                array[i] = _data[i];
                _states[i] = State::busy;}
            else{
                _states[i] = State::empty;}}
        delete[] _data;
        _data = new T[_capacity];
        _data = array;
    }
    else{
        int count = 0;
        for (size_t i = _size-1; i>=0; i--){
            if (_states[i] == State::deleted)
                count++;
            else if (count!=0) {
                for (size_t j = i+count+1; j<_size; j++){
                    _data[j-count] = _data[j];
                    _states[j] = State::empty;
                    _states[j-count] = State::busy;
                }
                _size -=count;
                count = 0;}
        }
    }
}

template <typename T>
void TDMassive<T>::push_back(T value){
    if (_size == _capacity){
        overexposure();}
    _data[_size-1] = value;
    _states[_size-1] = State::busy;
}

template <typename T>
void TDMassive<T>::pop_back(){ 
    _size--;
    _states[_size-1] = State::empty;
}

template <typename T>
void TDMassive<T>::push_front(T value){ //????
    if (_size == _capacity){
        overexposure();}
    for (size_t i = _size-1; i>=0; i--){
        if (_states[i]!=State::deleted){
            _data[i+1] = _data[i];
            _states[i+1] = State::busy;
        }
    }
}


template <typename T>
void TDMassive<T>::pop_front(){ //что быстрее
    if (_states[0]!=State::deleted){
        _states[0] = State::deleted;
        _deleted+=1;
    }
    if (double(_deleted)*100/double(_size) >= 40){ 
        overexposure();
    }
}

template <typename T> //может быть не правильно
TDMassive<T>& TDMassive<T>::insert(T value, size_t pos) {
    if (_size < pos) {
        throw std::logic_error("Error in function \
\"TArchive<T>& insert(T value, size_t pos)\": wrong position value.");
    }
    for (size_t i = _size; i > pos; i--) {
        _data[i] = _data[i - 1];
    }
    _data[pos] = value;
    _states[pos] = State::busy;
    _size++;
    return *this;
}

template <typename T>
TDMassive<T>& TDMassive<T>::replace(size_t pos, T new_value){
    _data[pos] = new_value;
    _states[pos] = State::busy;
    return *this;
}

template <typename T>
TDMassive<T>& TDMassive<T>::remove_all(T value){
    for (size_t i = 0; i<_size; i++){
        if (_data[i] == value){
            if (i == _size-1)
                _states[i] = State::empty;
            else{
                _states[i] = State::deleted;
                _deleted+=1;}
        }
    }
    if (double(_deleted)*100/double(_size) >= 40){ 
        overexposure();
    }
    return *this;
}

template <typename T>

TDMassive<T>& TDMassive<T>::remove_all(T value){
    for (size_t i = 0; i<_size; i++){
        if (_data[i] == value){
            if (i == _size-1)
                _states[i] = State::empty;
            else{
                _states[i] = State::deleted;
                _deleted+=1;}
            break;
        }
    }
    if (double(_deleted)*100/double(_size) >= 40){ 
        overexposure();
    }
    return *this;
}

template <typename T>
TDMassive<T>& TDMassive<T>::remove_by_index(size_t pos){
    if (_size == pos+1)
        _states[pos] = State::empty;
    else{
        _states[pos] = State::deleted;
        _deleted+=1;}
    if (double(_deleted)*100/double(_size) >= 40){ 
        overexposure();
    }
    return *this;
}

template <typename T>
size_t* TDMassive<T>::find_all(T value) const noexcept{
    size_t total = 0;
    for (size_t i = 0; i<_size; i++){
        if (_data[i] = value) total++;
    }
    return total;
}

template <typename T>
size_t TDMassive<T>::find_first(T value){
    for (size_t i = 0; i<_size; i++){
        if (_data[i] = value) return i;
    }
}

template <typename T>
size_t TDMassive<T>::find_last(T value){
    for (size_t i = _size; i>0; i--){
        if (_data[i] = value) return i;
    }
}





