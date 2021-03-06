mylib::String::String()
{
    m_size = 0;
    m_capacity = 16;
    m_buffer = new char[m_capacity];
    m_buffer[0] = '\0';
}

mylib::String::String(int m_size)
{
    this->m_capacity = m_size;
    m_buffer = new char[m_capacity];
}

char* mylib::String::c_str() {
    return m_buffer;
}

mylib::String::String(unsigned int m_sizee, char ch)
{
    m_buffer = new char[m_sizee+1];
    m_size = m_sizee;
    if(m_size < 16) {
        m_capacity = 16;
    }
    else {
        m_capacity = m_size + 16;
    }
    for(int i = 0; i < m_sizee; ++i){
        m_buffer[i] = ch;
    }
    m_buffer[m_sizee] = '\0';
}

mylib::String::String(const char* arr)
{
    m_buffer = new char[mylib::strlen(arr)+1];
    this->m_size = mylib::strlen(arr);
    if(m_size < 16) {
        m_capacity = 16;
    }
    else {
        m_capacity = m_size + 16;
    }
    for(int i = 0; i < mylib::strlen(arr); ++i) {
        m_buffer[i] = arr[i];
    }
    m_buffer[m_size] = '\0';
}

mylib::String::String(const String & obj)
{
    this->m_size = obj.m_size;
    this->m_capacity = obj.m_capacity;
    this->m_buffer = new char[obj.m_size];
    for(int i = 0; i <= obj.m_size; ++i) {
        this->m_buffer[i] = obj.m_buffer[i];
    }
}

mylib::String::String(String && ob)
{
    this->m_size = ob.m_size;
    this->m_capacity = ob.m_capacity;
    this->m_buffer = ob.m_buffer;
    this->m_buffer[m_size] = '\0';
    ob.m_buffer = nullptr;
    ob.m_size = 0;
}

mylib::String& mylib::String::operator=(String&& obj)
{
    this->m_size=obj.m_size;
    delete[] this->m_buffer;
    this->m_buffer = obj.m_buffer;
    this->m_capacity = obj.m_capacity;
    this->m_buffer[m_size] = '\0';
    obj.m_buffer = nullptr;
    return *this;
}

mylib::String& mylib::String::operator=(const String& obj)
{
    if(this == &obj){
        return *this;
    }
    if(this->m_size > 1) {
        delete[] this->m_buffer;
    }
    else if(this->m_size == 1) {
        delete this->m_buffer;
    }
    this->m_size = obj.m_size;
    this->m_capacity = obj.m_capacity;
    this->m_buffer = new char[obj.m_size];
    for(int i = 0; i <= obj.m_size; ++i){
        this->m_buffer[i] = obj.m_buffer[i];
    }
    return *this;
}

mylib::String mylib::String::operator+(const String & robj) const
{
    String tmp;
    int tmpp = this->m_size + robj.m_size;
    tmp.m_size = tmpp;
    tmp.m_buffer = new char[tmp.m_size];
    tmp.m_capacity = tmp.m_size + 16;
    for(int i = 0; i < this->m_size; ++i) {
        tmp.m_buffer[i] = this->m_buffer[i];
    }   
    for(int i = this->m_size; i < tmp.m_size; ++i){
        tmp.m_buffer[i] = robj.m_buffer[i-(this->m_size)];
    }
    return tmp;
}

mylib::String mylib::String::operator+(const char* symbols) 
{
    String tmp;
    int tmpp = this->m_size + mylib::strlen(symbols);
    tmp.m_size = tmpp;
    tmp.m_buffer = new char [tmp.m_size];
    this->m_capacity = tmp.m_size + 16;
    for(int i=0;i<this->m_size;++i){
        tmp.m_buffer[i]=this->m_buffer[i];
    }
    for(int i = this->m_size; i < tmp.m_size; ++i){
        tmp.m_buffer[i] = symbols[i-(this->m_size)];
    }  
    return tmp;
}

mylib::String mylib::String::operator+(const char ch)
{
    push_back(ch);
    return *this;
}

mylib::String& mylib::String::operator+=(const String & robj)
{
    *this = *this + robj;
    return *this;
}

bool mylib::String::operator>(const String & robj) const
{
    if(this->m_size > robj.m_size && this->m_size != robj.m_size){
        return true;
    }
    if(this->m_size < robj.m_size)
    {
        return false;
    }
    for(int i = 0; i < this->m_size; ++i)
    {
        if(this->m_buffer[i] > robj.m_buffer[i] && this->m_buffer[i] != robj.m_buffer[i])
        {
            return true;
        }
        if(this->m_buffer[i] < robj.m_buffer[i] && this->m_buffer[i] != robj.m_buffer[i])
        {
            return false;
        }
    }
    return false;
}

bool mylib::String::operator<(const String & robj) const
{
    if(this->m_size < robj.m_size && this->m_size != robj.m_size){
        return true;
    }
    if(this->m_size > robj.m_size)
    {
        return false;
    }
    for(int i = 0; i < this->m_size; ++i)
    {
        if(this->m_buffer[i] < robj.m_buffer[i] && this->m_buffer[i] != robj.m_buffer[i])
        {
            return true;
        }
        if(this->m_buffer[i] > robj.m_buffer[i] && this->m_buffer[i] != robj.m_buffer[i])
        {
            return false;
        }
    }
    return false;
}

bool mylib::String::operator==(const String &rhs) const
{
    if(this->m_size!=rhs.m_size){
        return false;
    }
    for(int i =0; i<this->m_size;++i){
        if(this->m_buffer[i]!=rhs.m_buffer[i]){
            return false;
        }
    }
    return true;
}

bool mylib::String::operator!=(const String &rhs) const
{
    return !(*this==rhs);
}

bool mylib::String::operator>=(const String & rhs) const
{
    if(this->m_size>=rhs.m_size){
        return true;
    }
    else {
        return false;  
    }  
}

bool mylib::String::operator<=(const String & rhs) const
{
    if(this->m_size<=rhs.m_size){
        return true;
    }
    else {
        return false;  
    }  
}

char& mylib::String::operator[](const unsigned index)
{
    return this->m_buffer[index];
}

const char& mylib::String::operator[](const unsigned index) const
{
    return this->m_buffer[index];
}

void mylib::String::push_back(char symbol)
{
    if(this->m_size != this->m_capacity) {
        m_buffer[m_size] = symbol;
        ++m_size;
        m_buffer[m_size] = '\0';
        return;
    }
    String tmp(*this);
    if(this->m_size != 0 && this->m_size == this->m_capacity) {
        this->m_capacity *= 1.8;
        delete[] m_buffer;
        m_buffer = new char[m_capacity];
        for(int i = 0; i < tmp.m_size; ++i) {
            m_buffer[i] = tmp.m_buffer[i];
        }
        m_buffer[m_size] = symbol;
        m_buffer[m_size+1] = '\0';
        ++m_size;
    }
}

char mylib::String::pop_back()
{
    if(m_size >= 1) {
        --m_size;
        m_buffer[m_size] = '\0';
    }
    return '\0';
}

void mylib::String::push_front(char symbol)
{
    String tmp;
    tmp.m_buffer = new char[this->m_size+1];
    tmp.m_buffer[0] = symbol;
    for(int i=1; i < this->m_size+1; ++i){
        tmp.m_buffer[i] = this->m_buffer[i-1];
    }
    delete[] this->m_buffer;
    this->m_size++;
    this->m_buffer = tmp.m_buffer;
    tmp.m_buffer = nullptr;
}

char mylib::String::pop_front()
{
    char tmpp = this->m_buffer[0];
    erase(0);
    return tmpp;
}

void mylib::String::resize(const int count,char symbol)
{
    for(int i=0;i < count; ++i) {
        *this=*this+symbol;
    }
}

char mylib::String::erase(const int index)
{
    char syml = this->m_buffer[index];
    String tmp;
    tmp.m_size = this->m_size-1;
    tmp.m_buffer = new char[tmp.m_size];
    for(int i=0; i < tmp.m_size; ){
        if(i == index){
            for(int j=i; j < tmp.m_size; ++j){
                tmp.m_buffer[j] = this->m_buffer[i+1];
                ++i;
            }
            break;
        }
        else {
            tmp.m_buffer[i] = this->m_buffer[i];
            ++i;
        }
    }
    delete[] this->m_buffer;
    this->m_buffer = tmp.m_buffer;
    this->m_size = tmp.m_size;
    tmp.m_buffer = nullptr;
    return syml;
}

mylib::String& mylib::String::erase(const int index,int count)
{
    if(count>this->m_size){
        std::cout<<"Error";
        exit(0);
    }
    while(count){
        erase(index);
        count--;
    }
    return *this;
}

int mylib::String::find(const char ch) const
{
    for(int i = 0; i < this->m_size; ++i) {
        if(this->m_buffer[i]==ch){
            return i;
        }
    }
    return -1;
}

int mylib::String::find(const String obj) const
{
    int tmp;
    int counter{};
    for(int i = 0; i < this->m_size; ++i) {
        counter = 0;
       if(this->m_buffer[i] == obj.m_buffer[0]) {
           tmp = i;
           i++;           
           for(int j = 1; j < obj.m_size; ++j) {
                if(this->m_buffer[i] != obj.m_buffer[j]) {
                   break;
                }
                counter++;
                i++;
            }
            if(counter == obj.m_size-1) {
                return tmp;
            }
            --i;
        }
    }
    return -1;
}

int mylib::String::find(const char * arr)const
{
    int tmp;
    int counter {};
        for(int i = 0; i < this->m_size; ++i) {
        counter = 0;
            if(this->m_buffer[i] == arr[0]) {
                tmp = i;
                i++;  
                for(int j = 1; j < mylib::strlen(arr); ++j) {
                    if(this->m_buffer[i] != arr[j]) {
                    break;
                }
                counter++;
                i++;
            }
            if(counter == mylib::strlen(arr)-1){
                return tmp;
            }
            --i;
        }
    }
    return -1;
}
    
void mylib::String::insert(const int index, char symbol)
{
    if(index>this->m_size){
        std::cout<<"ERROR";
        exit(0);
    }
    int counter{};
    for(int i = index; i < this->m_size; ++i){
        counter++;
    }
    String tmp(*this);
    tmp.erase(index, counter);
    tmp = tmp + symbol;
    counter = 0;
    for(int i = 0; i < index; ++i) {
        counter++;
    }
    String tmp1(*this);
    tmp1.erase(0, counter);
    tmp += tmp1;
    delete[] this->m_buffer;
    this->m_buffer = tmp.m_buffer;
    tmp.m_buffer = nullptr;
    delete[] tmp1.m_buffer;
    tmp1.m_buffer = nullptr;
    this->m_size++;
}

void mylib::String::insert(const int index,int count,char symbol)
{
    if(index > this->m_size){
        std::cout << "ERROR";
        exit(0);
    }
    while(count){
        this->insert(index, symbol);
        count--;
    }
}

void mylib::String::insert(const int index,const String & obj)
{
    if(index > this->m_size){
        std::cout<<"ERROR";
        exit(0);
    }
    int tmpm_size = this->m_size+obj.m_size;
    int counter{};
    for(int i = index; i < this->m_size; ++i) {
        counter++;
    }
    String tmp(*this);
    tmp.erase(index, counter);
    tmp += obj;
    counter = 0;
    for(int i = 0; i < index; ++i) {
        counter++;
    }
    String tmp1(*this);
    tmp1.erase(0, counter);
    tmp += tmp1;    
    delete[] this->m_buffer;
    this->m_buffer = tmp.m_buffer;
    tmp.m_buffer = nullptr;
    delete[] tmp1.m_buffer;
    tmp1.m_buffer = nullptr;
    this->m_size = tmpm_size;    
}

void mylib::String::insert(const int index, const char* symbols)
{
    if(index > this->m_size){
        std::cout << "ERROR";
        exit(0);
    }
    int tmpm_size = this-> m_size + mylib::strlen(symbols);
    int counter{};
    for(int i = index; i < this->m_size; ++i) {
        counter++;
    }
    String tmp(*this);
    tmp.erase(index, counter);
    tmp = tmp + symbols;
    counter = 0;
    for(int i = 0; i < index; ++i) {
        counter++;
    }
    String tmp1(*this);
    tmp1.erase(0, counter);
    tmp += tmp1;
    delete[] this->m_buffer;
    this->m_buffer = tmp.m_buffer;
    tmp.m_buffer = nullptr;
    delete[] tmp1.m_buffer;
    tmp1.m_buffer = nullptr;
    this->m_size = tmpm_size;
}

void mylib::String::clear()
{
    while(m_size) {
        pop_back();
    }
}

bool mylib::String::empty()
{
    return m_size==0 ;
}

void mylib::String::replace(char ch , int index)
{
    this->insert(index, ch);
    this->erase(index + 1);
}

void mylib::String::replace(int index , const char* arr)
{
    int tmpm_size = this->m_size;
    int counter = mylib::strlen(arr);
    this->insert(index, arr);
    while(counter) {
        this->erase(index + mylib::strlen(arr));
        --counter;
    }
}

mylib::String mylib::String::substr(int start,int end) const
{
    int counter {};
    if(start < 0 || start > this->m_size) {
        std::cout << "Error";
        exit(0);
    }
    if(end < 0 || end > this->m_size) {
        std::cout<<"Error";
        exit(0);
    }
    String tmp(*this);
    for(int i = 0; i < this->m_size; ++i) {
        if(i == start) {
            break;
        }
        ++counter;                      
    }
    int countertmp = counter;
    while(counter){
        tmp.pop_front();
        counter--;
    }
    end -= countertmp;
    countertmp = tmp.m_size-end;
    while(countertmp){
        tmp.pop_back();
        countertmp--;
    }
    return tmp;
}

std::ostream& operator<<(std::ostream& os , const mylib::String& str)
{
    os<< &str[0] ;
    return os;
}

std::istream& operator>>(std::istream &in, mylib::String &ob)
{
    char temp[100];
    in.get(temp,100);
    if(in){
        ob = temp;
    }
    while(in && in.get() != '\0'){
        continue;
    }
    return in;
}

char& mylib::String::at(const unsigned index)
{
    if(index<0 || index>this->m_size){
        std::cout<<"ERROR";
        exit(0);
    }
    return this->m_buffer[index];
}

const char& mylib::String::at(const unsigned index) const 
{
    if(index<0 || index>this->m_size){
        std::cout<<"ERROR";
        exit(0);
    }
    return this->m_buffer[index];
}

mylib::String::~String()
{
    if(m_capacity > 1) {
        delete[] m_buffer;
    }
    else if(m_capacity == 1) {
        delete m_buffer;
    }
}