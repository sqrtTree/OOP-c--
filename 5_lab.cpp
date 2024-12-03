#include <iostream>
#include <ostream>
#include <string.h>
#include <map>

using namespace std;

// typedef std::map<int, int> myMap;

class SBase
{
    public:
    virtual ~SBase(){}
    virtual int get(int i) = 0;
};
// class SFile : public SBase
// {
//     public:
//     SFile(){}
//     ~SFile(){}
//     int get(int i) override
//     {
//         return -1;
//     }
// };
// class SKbrd : public SBase
// {
//     public:
//     int get(int i) override
//     {
//         return -1;
//     }
// };
class SQueue : public SBase
{
    int length;

    public:
    SQueue(int len)
    {
        length = len;
    }
    int get(int i = 0) override
    {
        int mas[5]{2,1,1,2,1};
        if(i < 5) return mas[i];
        // if(i < length)
        //     return rand();
        return -1;
    }
};

class Freq
{
    map<int, int> m;
    int sum, count;
    
    public:
    void Calc(SBase &obj)// sum and map
    {
        int num = obj.get(count);
        while(num >= 0)
        {
            sum += num;
            
            if(m.count(num) == 0) m[num] = 1;
            else m.at(num)++;
            
            ++count;
            num = obj.get(count);
        }
        for(int num = obj.get(count), count = 0; num >= 0; ++count, num = obj.get(count))
        {
            sum += num;
            if(m.count(num) == 0)
                m[num] = 1;
            else
                m.at(num)++;
        }
    }
    friend ostream& operator<<(ostream &st, Freq &obj)
    {
        for (const auto& n : obj.m)
            st << n.first << " = " << n.second << "; ";
        st <<  "\nsum: " << obj.sum;
        return st;
    }
};
// class Diap : public Freq
// {
//     public:
//     void Calc()// min max and count
//     {
//         Diap::Calc();
//     }
//     friend ostream& operator<<(ostream &st, Freq &obj)
//     {}
// };


int main()
{
    srand (time(NULL));

    SBase *pa;
    SQueue squ(5);
    pa = &squ;

    Freq freq;

    freq.Calc(*pa);
    cout << freq;
    
    pa->get(1);
    
    return 0;
}