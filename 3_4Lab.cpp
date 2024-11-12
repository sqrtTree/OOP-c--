#include <iostream>
#include <ostream>
#include <string.h>
using namespace std;

template <class T = int>
class TVector
{
    T *vec;
    int length;
    
    public:
    TVector(int len = 1)
    {
        vec = new T[len]{}; 
        length = len;
    };
    TVector(TVector <T> &obj)
    {
        length = obj.length;
        vec = new T[length];
        for(int i = 0; i < length; ++i)
            vec[i] = obj[i];
    };
    ~TVector()
    {
        delete []vec;
    };
    void setLength(int new_len)
    {
        int min_len = min(length, new_len);
        T *buf = new T[new_len];
        for(int i = 0; i < min_len; ++i)
            buf[i] = vec[i];
        
        delete []vec;
        vec = buf;

        length = new_len;
    };
    TVector& operator=(const TVector <T> &obj)
    {
        delete []vec;
        length = obj.length;
        vec = new T[length];
        for(int i = 0; i < length; ++i)
            vec[i] = obj.vec[i];
        return *this;
    };
    TVector& operator+=(TVector <T> &obj)
    {
        T *buf = new T[length];
        for(int i = 0; i < length; ++i)
            buf[i] = vec[i];

        delete []vec;
        vec = new T[length * 2]{};

        int i = 0;
        for(; i < length; ++i)
            vec[i] = buf[i];

        length *= 2;

        for(int j = 0; i < length; ++i, ++j)
            vec[i] = obj.vec[j];

        delete []buf;
        return *this;
    };
    T& operator[](int index)
    {
        return vec[index];
    };
    friend ostream& operator<<(ostream &st, TVector <T> &obj)
    {
        for(int i = 0; i < obj.length ; ++i)
            st << obj.vec[i] << ' ';
        return st;
    };
    int get_len()
    {
        return length;
    };
};
//////////////////////////////////////////////////////////////////////////////////
template <class T>
class TMatrix
{
    void *matrix;
    int row, column;
    
    public:
    TMatrix(int r = 1, int col = 1)
    {
        matrix = new TVector<TVector<T>>(r);
        // for(int i = 0; i < r; ++i)
        //     matrix[i] = new TVector<T> (col);
    }

    // TMatrix(TMatrix <T> &obj)
    // {
    //     column = obj.column;
    //     row = obj.row;
    //     matrix = new T*[row];
    //     for(int i = 0; i < row; ++i)
    //         matrix[i] = obj[i];
    // };
    // ~TMatrix()
    // {
    //     delete []matrix;
    // }
    // TVector& operator=(const TVector <T> &obj)
    // {
    //     delete []vec;
    //     length = obj.length;
    //     vec = new T[length];
    //     for(int i = 0; i < length; ++i)
    //         vec[i] = obj.vec[i];
    //     return *this;
    // };
    // TVector& operator+=(TVector <T> &obj){};
    const TVector<T>& operator[](int index)
    const{
        return matrix[index];
    }
    TVector<T>& operator[](int index)
    {
        return matrix[index];
    }
    // friend ostream& operator<<(ostream &st, TVector <T> &obj)
    // {
    //     for(int i = 0; i < obj.length ; ++i)
    //         st << obj.vec[i] << ' ';
    //     return st;
    // };

};


int main()
{
    TMatrix<int> mat1(2, 3);
    mat1[1][1] = 1;
    cout << mat1[1][1];


//     TVector<double> vec1(3);
//     vec1[1] = 67;
//     TVector<double> vec2(vec1);
//     vec2[2] = 66;

//     cout << "   "<< vec1 << "|| " << vec2 << endl << "   length: " << vec1.get_len() << endl;

//     vec1 = vec2;
//     cout << " = " << vec1 << "|| " << vec2 << endl;

//     vec1 += vec2;
//     cout << "+= " << vec1 << "|| " << vec2 << endl;

//     vec1.setLength(2);
//     cout << "new length: " << vec1 << "\n\n\n";
// //-------------------------------------------------------------------------------------

//     TVector<string> vec3(3);
//     vec3[1] = "first";
//     TVector<string> vec4(vec3);
//     vec4[2] = "second";

//     cout << "   "<< vec3 << "|| " << vec4 << endl << "   length: " << vec3.get_len() << endl;

//     vec3 = vec4;
//     cout << " = " << vec3 << "|| " << vec4 << endl;

//     vec3 += vec4;
//     cout << "+= " << vec3 << "|| " << vec4 << endl;

//     vec3.setLength(5);
//     cout << "new length: " << vec3 << endl;



    return 0;
}