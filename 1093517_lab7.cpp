#include<iostream>
#include<iomanip>
using namespace std;
class Array
{
    friend ostream &operator<<(ostream &, const Array &);
    friend istream &operator>>(istream &, Array &);
    public:
    Array(int = 10);
    Array( const Array & ); // copy constructor
    ~Array(); // destructor
    int getSize() const; // return size
    Array &operator-();
    const Array &operator=( const Array & ); // assignment operator
    Array operator+(Array &);
    bool operator==( const Array & ) const; // equality operator
    // inequality operator; returns opposite of == operator
    bool operator!=( const Array &right ) const {
    return ! ( *this == right ); // invokes Array::operator==
    } // end function operator!=
    // subscript operator for non-const objects returns modifiable lvalue
    int &operator[]( int );
    // subscript operator for const objects returns rvalue
    int operator[]( int ) const;
    Array &operator>>( int );
    private:
    int size; // pointer-based array size
    int *ptr; // pointer to first element of pointer-based array

}; // end class Array
Array::Array( int Asize )
{
    size = ( Asize > 0 ? Asize : 10 );
    ptr = new int[size];
    for ( int i = 0; i < size; i++ )
    {
        ptr[i] = 0; 
    }
}
Array::Array(const Array &copy)
:size(copy.size)
{
    cout << "copy constructor" << endl;
    ptr = new int[size];
    for ( int i = 0; i < size; i++ )
    {
        ptr[i] = copy.ptr[i];
    }
}
Array::~Array()
{
    delete[]ptr;
}
int Array::getSize() const
{
    return size;
}
const Array &Array::operator=(const Array &right)
{
    if ( &right != this )
    {
        if ( size != right.size )
        {
            delete[] ptr;
            size = right.size;
            ptr = new int[size];
        }
        for ( int i = 0 ; i < size; i++ )
        {
            ptr[i] = right.ptr[i];
        }
    }
    return *this;
}
bool Array::operator==(const Array &right) const
{
    if ( size != right.size )
        return false;
    for ( int i = 0; i < size; i++ )
        if ( ptr[i] != right.ptr[i] )
            return false;
        return true;
}
int &Array::operator[](int subscript)
{
    if ( subscript < 0 || subscript >= size )
    {
        cerr << "\nError: Subscript " << subscript << " out of range " << endl;
        exit(1);
    }
    return ptr[subscript];
}
ostream &operator<<( ostream &output, const Array &a )
{
    int i;
    // output private ptr-based array
    for ( i = 0; i < a.size; i++ ) 
    {
        output << setw( 12 ) << a.ptr[ i ];
        if ( ( i + 1 ) % 4 == 0 ) // 4 numbers per row of output
            output << endl;
    } // end for
    if ( i % 4 != 0 )  // end last line of output
        output << endl;
    return output;   // enables cout << x << y;
}
istream &operator>>( istream &input, Array &a )
{
    for ( int i = 0; i < a.size; i++ )
        input >> a.ptr[i];
    return input;   // enables cin >> x >> y;
}
Array &Array::operator-()
{
    for ( int n = 0 ; n < size; n++ )
    {
        ptr[n] = -ptr[n];
    }
    return *this;
}
Array Array::operator+(Array &a)
{
    Array w(size + a.size);
    for ( int i = 0; i < size; i++ )
    {
        w.ptr[i] = ptr[i];
    }
    for ( int i = 0; i < a.size; i++ )
    {
        w.ptr[i+size] = a.ptr[i];
    }
    return w;
}
Array &Array::operator>>(int b)
{
    Array cpy(size);
    for ( int i = 0; i < size; i++ )
    {
        cpy.ptr[i] = ptr[i];
    }
    int c;
    while( b > size )
    {
        b = b % size;
    }
    for ( int i = 0; i < b; i++ )
    {
        int x;
        int y;
        x = ptr[size-1];
        y = ptr[0];
        cout << "f " << y << endl;
        for ( int j = 0; j < size; j++ )
        {
            if ( j != 0 )
            {
                ptr[j] = cpy.ptr[j-1];
            }
        }
        ptr[0] = x;
        for ( int j = 0; j < size; j++ )
        {
            cpy.ptr[j] = ptr[j];
        }
        for ( int j = 0; j < size; j++ )
        {
            cout << ptr[j] << ' ';
        }
        cout << endl;
    }
    /*
    for ( int i = 0 ; i < b; i++ )
    {
        ptr[i] = ptr[size-b+i];
    }
    */

}
int main()
{
    Array integers1(7);
    Array integers2;
    cout << "Size of intergers1 is" << integers1.getSize() << "\nSize of the initialization:\n" << integers1;
    cout << "Size of intergers2 is" << integers2.getSize() << "\nSize of the initialization:\n" << integers2;
    cout << "\nEnter 17 intergers:" << endl;
    cin >> integers1 >> integers2;
    cout << "\nAfter input, the arrays contain:\n" << "intergers1:\n" << integers1 << "intergers2:\n" << integers2;
    cout << "\nEvaluating: intergers1 != intergers2" << endl;
    if ( integers1 != integers2 )
    {
        cout << " not equal "<< endl;
    }
    Array integers3(integers1);
    cout << "\nSize of the Array intergers3 is " << integers3.getSize() << "\nArray after initialization:\n" << integers3;
    cout << "\nAssigning integers2 to integers1\n";
    integers1 = integers2;
    cout << " intergers1:\n" << integers1 << " intergers2:\n" << integers2;
    cout << "\nEvaluating:integers1 == integers2" << endl;
    if ( integers1 == integers2 )
    {
        cout << "equal" << endl;
    }
    cout << "\nintergers1[5] is " << integers1[5];
    cout << "\n\nAssigning 1000 to integers1[5]" <<endl;
    integers1[5] = 1000;
    cout << "intergers1:\n" << integers1;
//----------------------------------------------------------------------
    
    integers3 = -integers3;
    cout << "intergers2:\n" << integers2;
    cout << "intergers3:\n" << integers3;
    Array C;
    C = integers1+integers2+integers3;
    cout << "Array C = integer1+ integer2 + integer3:\n" << C;
    int k = 30;
    C >> k;
    cout << "shifting to the right by" << k << "Placed \n " << C;  

//----------------------------------------------------------------------
    cout << "\nAttempt to assign 1000 to integers1[15]"<<endl;
    integers1[15] = 1000; // Error
}