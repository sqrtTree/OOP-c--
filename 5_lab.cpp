class SBase
{
    virtual int Get()
    {
        return -1;
    }
    virtual void f() = 0;
};
class SFile : SBase{};
class SKbrd : SBase{};
class SQueue : SBase{};
class Freq
{
    public:
    void Calc(){}
};
class Diap : Freq{};