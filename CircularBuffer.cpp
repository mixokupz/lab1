#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(){
    this->buffer = new value_type[0]{};
    this->cap =0;
    this->tail =0;
    this->head =0;
}

CircularBuffer::~CircularBuffer(){
    delete(this->buffer);
    this->cap =0;
    this->tail =0;
    this->head =0;
}
CircularBuffer::CircularBuffer(const CircularBuffer & cb): buffer(new value_type[cb.cap]{}),cap(cb.cap){
    for(int i=0;i<cb.cap;i++){
        this->buffer[i] = cb.buffer[i];
    }
    this->cap = cb.cap;
    this->tail = cb.tail;
    this->head = cb.head;

} 
//Конструирует буфер заданной ёмкости., exiplit нельзя указывать?
CircularBuffer::CircularBuffer(int capacity){
    this->buffer = new value_type[capacity]{};
    this->cap =capacity;
    this->tail = 0;
    this->head =0;
}
//Конструирует буфер заданной ёмкости, целиком заполняет его элементом elem.
CircularBuffer::CircularBuffer(int capacity, const value_type & elem){
    this->buffer = new value_type[capacity]{};
    this->cap =capacity;
    this->tail = 0;
    this->head = 0;
    for(int i=0;i<this->cap;i++){
        this->buffer[i] = elem;
    }
}

//Доступ по индексу. Не проверяют правильность индекса.
value_type & CircularBuffer:: operator[](int i){
    return at(i);
}
const value_type & CircularBuffer::operator[](int i) const{
    return at(i);   
}

//Доступ по индексу. Методы бросают исключение в случае неверного индекса.
value_type & CircularBuffer::at(int i){
    if(i>=this->cap || i<0){
        std::cout<<"Error: wrong position\nIt'll be shot down";
        exit(0);
    }else{
        return this->buffer[i]; 
    }

}
const value_type & CircularBuffer::at(int i) const{
    if(i>=this->cap || i<0){
        std::cout<<"Error: wrong position\nIt'll be shot down";
    }else{
        return this->buffer[i]; 
    }
}

//Ссылка на первый элемент.
value_type & CircularBuffer::front(){
    return this->buffer[this->head];
} 
//Ссылка на последний элемент.
value_type & CircularBuffer::back(){
    return this->buffer[this->tail];
}  
const value_type & CircularBuffer::front() const{
    return this->buffer[this->head];
}
const value_type & CircularBuffer::back() const{
    return this->buffer[this->tail];
}

//Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
//переместится в начало аллоцированной памяти. Возвращает указатель 
//на первый элемент.
value_type * CircularBuffer::linearize(){
    //создаем массив, куда перезаписываем элементы из прошлого, учитывая новое место позиции
    if(!is_linearized()){
        value_type *new_buf = new value_type[this->cap]{};
        int place = 0;
        for(int i=0;i<this->cap;i++){
            if(this->head+i<this->cap){
                new_buf[i] = this->buffer[this->head+i];
            }else{
                new_buf[i] = this->buffer[place];
                place++;
            }
        }
        delete[] this->buffer;
        this->buffer = new_buf;
        this->head = 0;
        for(int i=0;i<this->cap;i++){
            this->tail = i;
            if((int)this->buffer[i]==0){
                break;
            }
        }
        return this->buffer;

    }else{
        return this->buffer;
    }
}
//Проверяет, является ли буфер линеаризованным.
bool CircularBuffer::is_linearized() const{
    if(this->head==0){
        return true;
    }
    return false;
}
//Сдвигает буфер так, что по нулевому индексу окажется элемент 
//с индексом new_begin.
void CircularBuffer::rotate(int new_begin){
    if(new_begin<this->cap && new_begin>-1){
        value_type *new_buf = new value_type[this->cap]{};
        int place = 0;
        for(int i=0;i<this->cap;i++){
            if(new_begin+i<this->cap){
                new_buf[i] = this->buffer[new_begin+i];
            }else{
                new_buf[i] = this->buffer[place];
                place++;
            }
        }
        delete[] this->buffer;
        this->buffer = new_buf;
        this->head = 0;
        for(int i=0;i<this->cap;i++){
            this->tail = i;
            if((int)this->buffer[i]==0){
                break;
            }
        }
    }else{
        std::cout<<"Wrong chosen position!\n";
        exit(0);
    }
    
}

//Количество элементов, хранящихся в буфере.
int CircularBuffer::size() const{
    int count =0;
    for(int i=0;i<this->cap;i++){
        if((int)this->buffer[i]!=0){
            count++;
        }
    }
    return count;
}
bool CircularBuffer::empty() const{
    int count = size();
    if(count==0){
        return true;
    }
    return false;
}
//true, если size() == capacity().
bool CircularBuffer::full() const{
    if(size()==capacity()){
        return true;
    }
    return false;
}
//Количество свободных ячеек в буфере.
int CircularBuffer::reserve() const{
    return capacity() - size();
}
//ёмкость буфера
int CircularBuffer::capacity() const{
    return this->cap;
}
//Изменяет размер буфера.
//В случае расширения, новые элементы заполняются элементом item.
void CircularBuffer::resize(int new_size, const value_type & item){
    value_type * new_buf = new value_type[new_size]{};
    for(int i=0;i<this->cap;i++){
        new_buf[i] = this->buffer[i]; 
    }
    delete[] this->buffer;
    this->buffer = new_buf;
    for(int i =this->cap;i<new_size;i++){
        this->buffer[i] = item;  
    }
    this->cap = new_size;
}

//Оператор присваивания.
CircularBuffer & CircularBuffer::operator=(const CircularBuffer & cb){
    delete[] this->buffer;
    this->cap = cb.cap;
    this->head = cb.head;
    this->tail = cb.tail;
    this->buffer = new value_type[cb.cap]{};
    for (int i = 0; i < cb.cap; i++) {
        this->buffer[i] = cb.buffer[i];
    }
    return *this;

}

//Обменивает содержимое буфера с буфером cb. Добавить проверку на возможность swap, чтобы ёмкости позволяли
void CircularBuffer::swap(CircularBuffer & cb){
    if(this->cap==cb.cap){
        value_type * new_buf = new value_type[this->cap]{};
        for(int i=0;i<this->cap;i++){
            new_buf[i] = this->buffer[i];
        }
        for(int i=0;i<this->cap;i++){
            this->buffer[i] = cb.buffer[i];
            cb.buffer[i] = new_buf[i];
        }
        delete[] new_buf;
    }
    else{
        std::cout<<"Error: 1st and 2nd capacity isn't the same\n";
        exit(0);
    }
}

//Добавляет элемент в конец буфера. 
//Если текущий размер буфера равен его ёмкости, то переписывается
//первый элемент буфера (т.е., буфер закольцован). 
void CircularBuffer::push_back(const value_type & item){
    if(this->tail<this->cap){
        this->buffer[this->tail] = item;
        this->tail+=1;
    }else{
        this->tail = (this->tail)%(this->cap);
        this->buffer[this->tail] = item;
        this->tail+=1;
    }
}
    
//Добавляет новый элемент перед первым элементом буфера. 
//Аналогично push_back, может переписать последний элемент буфера.
void CircularBuffer::push_front(const value_type & item){
    if(this->head>0){
        this->head -=1;
        this->buffer[this->head] = item;
    }else{
        this->head = this->cap - 1;
        this->buffer[this->head] = item;
    }
}
//удаляет последний элемент буфера.
void CircularBuffer::pop_back(){
    if(!empty()){
        value_type *new_buf = new value_type[this->cap]{};
        if(this->tail>0){
            for(int i =0;i<this->tail-1;i++){
                new_buf[i] = this->buffer[i];
            }
            for(int i = this->tail;i<this->cap;i++){
                new_buf[i] = this->buffer[i];
            }
            this->tail -=1;
        }else{
            this->tail = this->cap -1;
            for(int i =0;i<this->tail;i++){
                new_buf[i] = this->buffer[i];
            }
        }
        delete[] this->buffer;
        this->buffer = new_buf;
    }
    else{
        std::cout<<"Buffer is empty!\n";
        exit(0);
    }
    
}
    
//удаляет первый элемент буфера.
void CircularBuffer::pop_front(){
    if(!empty()){
        value_type *new_buf = new value_type[this->cap]{};
        if(this->head<this->cap){
            this->head +=1;
            for(int i =this->head; i<this->cap;i++){
                new_buf[i] = this->buffer[i];
            }
        }else{
            for(int i =0; i<this->head;i++){
                new_buf[i] = this->buffer[i];
            }
            this->head +=0;
        }
        delete[] this->buffer;
        this->buffer = new_buf;
    }
    else{
        std::cout<<"Buffer is empty!\n";
        exit(0);
    }
    

}
    
//Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
//Добавить исключение
void CircularBuffer::insert(int pos, const value_type & item){
    if(pos>=this->cap || pos<0){
        std::cout<<"Error: wrong position\nIt'll be shot down";
    }else{
        this->buffer[pos] = item;
    }
     
}
//Удаляет элементы из буфера в интервале [first, last).
void CircularBuffer::erase(int first, int last){
    if(first<0 || first>=this->cap || last<0 || last >=this->cap || first>=last){
        std::cout<<"Wrong interval!\n";
    }
    else{
        value_type *new_buf = new value_type[this->cap]{};
        for(int i=last;i<this->cap;i++){
            new_buf[i] = this->buffer[i];
        }
        delete[] this->buffer;
        this->buffer = new_buf;
    }
}

//Очищает буфер.
void CircularBuffer::clear(){
    value_type *new_buf = new value_type[this->cap]{};
    delete[] this->buffer;
    this->buffer = new_buf;
    this->head =0;
    this->tail =0;
}