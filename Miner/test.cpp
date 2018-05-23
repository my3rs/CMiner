//
// Created by cyril on 3/16/18.
//

#include <iostream>
#include <map>
#include <string>

using namespace std;

class A {
private:
    int support;
public:
    A(int support) {
        this->support = support;
    }
    void setSupport(int support) {
        this->support = support;
    }
    int getSupport() {
        return  this->support;
    }
};

void traverseMap(map<int, A> m) {
    for (auto iter : m) {
        cout<<"key: "<<iter.first<<"\tvalue: support: "<<iter.second.getSupport()<<endl;
    }
}


int main()
{
    map<int, A> m;
    m.insert({1, A{1}});
    m.insert({2, A{2}});
    traverseMap(m);

    cout<<"\n";
    m.find(2)->second.setSupport(3);
    traverseMap(m);

}