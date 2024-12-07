#include <iostream>
#include <ostream>
#include <string.h>
#include <map>

using namespace std;

class SBase
{
    public:
    virtual ~SBase(){}
    virtual int get() = 0;
};
class SFile : public SBase
{
    public:
    FILE *in;
    SFile(const char *fName = "input.txt")
    {
        in = fopen(fName , "r");
    }
    ~SFile()
    {
        fclose(in);
        delete in;
    }
    int get() override
    {
        if(in != NULL)
        {
            char check = getc(in);
            int i = 0;
            while(i < 16)
            {
                ++i;
                if(feof(in))
                {
                    rewind(in);
                    return -1;
                }
                if(check > 47 and check < 58)
                    return check - '0';
                check = getc(in);
            }
        }
        return -1;
    }
    void reset()
    {
        rewind(in);
    }
};
class SKbrd : public SBase
{
    public:
    int get() override
    {
        char check = cin.get();
        while(true)
        {
            if(check == '\n')
                return -1;
            if(check > 47 and check < 58)
                return check - '0';
            check = cin.get();
        }
        return -1;
    }
    void reset()
    {
        cin.sync();
    }
};
class SQueue : public SBase
{
    int length, i = 0;

    public:
    SQueue(int len)
    {
        length = len;
    }
    int get() override
    {
        if(i < length)
        {
            ++i;
            return rand()%10;
        }
        i = 0;
        return -1;
    }
    void reset()
    {
        i = 0;
    }
};

class Freq
{
    protected:
    map<int, int> m;
    int sum = 0;
    
    public:
    virtual ~Freq() = default;
    void Calc(SBase &obj)// sum and map
    {
        for(int num = obj.get(); num >= 0;)
        {
            sum += num;
            if(m.count(num) == 0) m[num] = 1;
            else m.at(num)++;

            num = obj.get();
        }
    }
    void reset()
    {
        m.clear();
        sum;
    }
    friend ostream& operator<<(ostream &st, Freq &obj)
    {
        for (const auto& n : obj.m)
            st << n.first << " = " << n.second << "; ";
        st <<  "\nsum: " << obj.sum << "\n\n";
        return st;
    }
};
class Diap : public Freq
{
    int count = 0, min, max;

    public:
    void Calc(SBase &obj)// min max and count
    {
        Freq::Calc(obj);
        count = m.size();

        // int num = obj.get();
        min = m.begin()->first;
        max = (--m.end())->first;

        // for(; num > -1;)
        // {
        //     if(min > num) min = num;
        //     if(max < num) max = num;
        //     num = obj.get();
        // }
        // for (const auto& n : m)
        // {
        //     if(min > n.first) min = n.first;
        //     if(max < n.first) max = n.first;
        // }

    }
    void reset()
    {
        count = 0;
    }
    friend ostream& operator<<(ostream &st, Diap &obj)
    {
        for (const auto& n : obj.m)
            st << n.first << " = " << n.second << "; ";
        st <<  "\nsum: " << obj.sum << "\n";

        if(obj.count > 0) return st << "min: " << obj.min << " max: " << obj.max << " count: " << obj.count << "\n\n\n";
        return st;
    }
};

void test(Diap &di, SBase *p)
{
    di.Calc(*p);
    cout << di;

    di.reset();
}
void test_SFile()
{
    Diap diap;
    SBase *p = new SFile;

    diap.Calc(*p);
    cout << diap;

    delete p;
};
void test_SKbrd()
{
    Diap diap;
    SBase *p = new SKbrd;

    cout << "enter nums: ";

    diap.Calc(*p);
    cout << diap;

    delete p;
};
void test_SQueue()
{
    Diap diap;
    SBase *p = new SQueue(5);

    diap.Calc(*p);
    cout << diap;

    delete p;
};
int main()
{
    srand (time(NULL));

    test_SFile();
    test_SKbrd();
    test_SQueue();

    return 0;
}