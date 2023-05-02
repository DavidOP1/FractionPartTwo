#include <iostream>
#include <cmath>
#include <string>
using namespace std;
namespace ariel{
class Fraction{
    public:
    //Constructor
        Fraction(Fraction&,Fraction&);
        Fraction(Fraction&,int);
        Fraction(int ,int);
        Fraction(int ,Fraction&);
        Fraction(float);
        Fraction();
        int nume , deno;
        int getDenominator() const;
        int getNumerator() const;
        float get_frac_val();
        float frac_val;
        
};
    istream& operator>>(istream&  , Fraction&);
    ostream& operator<<(ostream&,  const Fraction&);
    //gcd algo
        int gcd(int, int);
    //reduce fraction:
        void gcd_frac(int&,int&);
    //redduce float
        void reduce_float(float&);
 //Addition
        Fraction operator+(const Fraction&, const Fraction& );
        Fraction operator+(const Fraction&  , float );
        Fraction operator+(float  , const Fraction& );
    //Subtraction
        Fraction operator-(const Fraction&  , const Fraction& );
        Fraction operator-(const Fraction&  ,float);
        Fraction operator-(float  , const Fraction& );
    //Divison
        Fraction operator/(const Fraction&  , const Fraction& );
        Fraction operator/(const Fraction&  , float );
        Fraction operator/(float  , const Fraction& );
    //Mult
        Fraction operator*(const Fraction&  , const Fraction& );
        Fraction operator*(const Fraction&  , float );
        Fraction operator*(float  , const Fraction& );
    //greater than
        bool operator>(const Fraction&  , const Fraction& );
        bool operator>(const Fraction&  , float );
        bool operator>(float  , const Fraction& );
    //smaller then
        bool operator<(const Fraction&  , const Fraction& );
        bool operator<(const Fraction&  , float );
        bool operator<(float  , const Fraction& );
    //greater equal
        bool operator>=(const Fraction&  , const Fraction& );
        bool operator>=(const Fraction&  , float );
        bool operator>=(float  , const Fraction& );
    //smaller equal
        bool operator<=(const Fraction&  , const Fraction& );
        bool operator<=(const Fraction&  , float );
        bool operator<=(float  , const Fraction& );
    
    //==s
        bool operator==(const Fraction& , const Fraction&);
        bool operator==(const Fraction&  , float );
        bool operator==(float  , const Fraction& );

    //Pre-fix
        Fraction& operator++(Fraction&);
        Fraction& operator--(Fraction&);
    //Post-fix
        Fraction operator++(Fraction& , int);
        Fraction operator--(Fraction& , int);


}