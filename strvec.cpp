//每个StrVec有三个指针成员指向其元素所使用的内存
//elements,分配内存中的首元素
//first_free，指向最后一个实际元素之后的位置
//cap，指向分配的内存末尾之后的位置
#include <iostream>
#include <string>
#include <memory>       //allocator
using namespace std;

class StrVec{
public:
    StrVec():   //allocator成员进行默认初始化
        elements(nullptr), first_free(nullptr),cap(nullptr){};
    StrVec(const StrVec&);              //拷贝构造函数
    StrVec &operator=(const StrVec&);   //拷贝赋值运算符
    ~StrVec();
    void push_back(const std::string&);
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    std::string *begin() const {return elements;}
    std::string *end() const {return first_free;}
private:
    static allocator<string> alloc;//分配元素
    //被添加元素的函数所使用
    void chk_n_alloc()
    {if(size()==capacity()) reallocate();}
    //工具函数，被拷贝构造函数、赋值运算符和析构运算符所使用
    pair<string*,string*> alloc_n_copy
        (const string*,const string*);
    void free();
    void reallocate();          //获得更多内存并拷贝已有元素
    std::string *elements;  
    std::string *first_free;
    std::string *cap;
};

void StrVec::push_back(const std::string &s){
    //push_back调用chk_n_alloc确保有空间容纳新元素
    chk_n_alloc();
    alloc.construct(first_free++,s);
    //construct成员接受一个指针和零或多个额外参数
    //在给定位置构造一个元素
}

pair<string*,string*> StrVec::alloc_n_copy(const string* b,const string* e){
//返回一个指针的pair，两个指针分别指向新空间的开始位置和拷贝的尾后
    auto data=alloc.allocate(e-b);
    return {data,uninitialized_copy(b,e,data)};
    //从迭代器b和e指出的输入范围中拷贝元素到迭代器data指定的未构造内存中 
}

void StrVec::free()
{//free函数：destroy元素，释放分配的内存
    if(elements){//逆序销毁旧元素
        for(auto p=first_free;p!=elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements,cap-elements);
        //allocate分配内存，deallocate释放内存
    }
}
StrVec::StrVec(const StrVec &s){
    //调用alloc_n_copy分配空间以容纳与s中一样多的元素
    auto new_data=alloc_n_copy(s.begin(),s.end());   //返回pair
    elements=new_data.first;
    first_free=new_data.second;
}
StrVec::~StrVec() {free();}
StrVec &StrVec::operator=(const StrVec &rhs){
    auto data=alloc_n_copy(rhs.begin(),rhs.end());
    free();
    elements=data.first;
    first_free=cap=data.second;
    return *this;
}
void StrVec::reallocate(){
    //如果StrVec为空，分配一个元素；每次分配，容量加倍
    // if(!capacity()) 
    //     auto data=alloc.allocate(1);
    // else 
    //     auto data=alloc.allocate(2*(capacity()));
    auto newcapacity=size()?2*size():1;
    auto newdata=alloc.allocate(newcapacity);
    auto dest=newdata;//指向新数组中下一个空闲位置
    auto elem=elements;//指向旧数组下一个位置
    for(size_t i=0;i!=size();++i)
        alloc.construct(dest++,std::move(*elem++));   
    free();//移动完就释放旧内存空间
    elements=newdata;
    first_free=dest;
    cap=elements+newcapacity;
}

StrVec::StrVec(StrVec &&s){

}
