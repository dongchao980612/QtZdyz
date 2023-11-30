#include <iostream>
#include <string>
using namespace std;

class Dog
{
public:
    string name;
    void func();
};

void Dog::func()
{
    this->name = "旺财";
    cout<<"小狗的名字叫："<<this->name<<endl;
}

int main()
{
    Dog dog;
    dog.func();
    return 0;
}



