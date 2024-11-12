#include <iostream>
#include <ostream>
#include <string.h>
using namespace std;

    class CStr
    {
        int len;
        char *string;
        char *generate(int length)
        {
            char *line = new char[length];
            const char *symbols = new char[26];
            symbols = "abcdefghijklmnopqrstuvwxyz";

            for(int i = 0; i < length; ++i)
                line[i] = symbols[rand()%26];
    
            return line;
        };

        int get_len(const char *str)
        {   
            int i = 0;
            while(str[i] != '\0') ++i;
            return i; 
        };
        
    public:
        CStr()
        {
            len = rand()%20;
            string = generate(len);
        };
        CStr(const char *str)
        {
            int i;
            len = get_len(str);
            string = new char[len];

            for(i = 0; i < len; i++)  
                string[i] = str[i];
        };
        CStr(int length)
        {
            len = length;
            string = generate(len);
        };
        CStr(const CStr &obj)
        {
            len = obj.len; 
            string = new char[len];
            strcpy(string, obj.string);
        };
        ~CStr()
        {
            delete []string;
        };
        CStr& operator=(const CStr &obj)
        {
            if(this != &obj)
            {
                delete []string;
                string = new char[obj.len];
                strcpy(string, obj.string);
            }
            return *this;
        };
        CStr& operator=(const char *str)
        {
            delete []string;
            len = get_len(str);
            string = new char[len + 1];
            strcpy(string, str);
            
            return *this;
        };
        CStr operator+(const CStr &obj)
        {
            int i = 0;
            char *line = new char[len + obj.len];
            for(; i < len; i++)
                line[i] = string[i];
            for(; i < len + obj.len; i++)
                line[i] = obj.string[i-len];
            CStr a1(line);
            delete []line;
            return a1;
        };
        CStr& operator+=(CStr &obj)
        {
            *this = *this + obj;
            return *this;
        };
        bool operator>(CStr &obj)
        {
            int i = 0;
            while(i < min(len, obj.len))
            {
                if(string[i] > obj.string[i]) return true;
                if(string[i] < obj.string[i]) return false;
                ++i;
            };
            if(len <= obj.len) return false;
            else return true;
        };

        char& operator[](int index)
        {
            return string[index];
        };
        int get_length()
        {   
            return len; 
        };
        friend ostream& operator<<(ostream &st, CStr &obj){
            st << obj.string; return st;
        };
        friend istream& operator>>(istream &stream, CStr &obj)
        {
            char buf[80];
            cout << "\nВведите строку: ";
            gets_s(buf, 79);
            CStr q(buf);
            obj = q;
            return stream;
        };
    };
///////////////////////////////////////////////////
    class CStrArray
    {
        CStr **arr;
        int capacity, size = 0;
    public:
        CStrArray(int cap)
        {
            capacity = cap;
            arr = new CStr*[capacity];
            // for(int i = 0; i < capacity; ++i)
            //     arr[i] = new CStr;
        };
        CStrArray& operator+=(CStr *obj)
        {
            if(capacity > size)
            {
                arr[size] = obj;
                ++size;
            };
            return *this;
        };
        ~CStrArray()
        {
            // for(int i = 0; i < capacity; ++i)
            //     delete arr[i];
            delete [] arr;
        };
        CStr* operator[](int index)
        {
            return arr[index];
        };
        void sort_by_content()
        {
            for (int i = 0; i + 1 < size; ++i)
                for (int j = 0; j + 1 < size - i; ++j)
                    if (*arr[j+1] > *arr[j])
                        swap(arr[j], arr[j + 1]);
        };
        void sort_by_length()
        {
            for (int i = 0; i + 1 < size; ++i)
                for (int j = 0; j + 1 < size - i; ++j)
                    if (arr[j + 1]->get_length() < arr[j]->get_length())
                    {
                        swap(arr[j], arr[j + 1]);
                        // CStr *buf;
                        // arr[j] = buf;
                        // arr[j] = arr[j + 1];
                        // arr[j + 1] = buf;
                    };
        };
        bool check_sort()
        {
            for (int j = 0; j + 1 < size; ++j)
                if (*arr[j] > *arr[j + 1]) return false;
            return true;
        };
        friend ostream& operator<<(ostream &stream, CStrArray &obj)
        {
            // stream << *obj.arr[0]; return stream;
            for(int i = 0; i < obj.size; ++i)
                stream << "|> " << *obj[i] << endl;
            return stream;
        };
    };


int main()
{
    srand (time(NULL));

    // CStr a1("first");
    // cout << a1.get_length();
    // CStr a2[4] = {"abcd", 4, a1};
    // cout << "a2[0]: " << a2[0] << '\n';
    // cout << "a2[1]: " << a2[1] << '\n';
    // cout << "a2[2]: " << a2[2] << '\n';
    // cout << "a2[3]: " << a2[3] << '\n';
    // cout << "——————————————————————\n";

    // a2[0] = a1 + a2[1];
    // a2[1] += a2[2];
    // CStr a2;
    // a2 = "qwerty";
    
    // cout << "a2[0]: " << a2[0] << '\n';
    // cout << "a2[1]: " << a2[1] << '\n';
    // cout << "a2[2]: " << a2[2] << '\n';
    // cout << "a2[3]: " << a2[3] << '\n';
    // cout << "——————————————————————\n";

    // cout << "(a1[0] > a1[1]): " << (a1[0] > a1[1]) << '\n';
    // cout << "a1[0]: " << a1[0] << '\n';
    // cout << "——————————————————————————————————————————\n";

    CStrArray arr_str(4);
    CStr *a4 = new CStr;
    *a4 = "first12345";
    CStr a5("h");
    CStr a6("third");
    CStr a7("fourth");



    arr_str += a4;
    arr_str += &a5;
    arr_str += &a6;
    arr_str += &a7;

    cout << arr_str << endl;

    arr_str.sort_by_content();
    cout << "sorted by content:\n" << arr_str << endl;
    
    arr_str.sort_by_length();
    cout << "sorted by length:\n" << arr_str << endl;

    cout << "checking: " << arr_str.check_sort() << endl;
    return 0;
}