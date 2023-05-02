#include "Fraction.hpp"
#include <iostream>
#include <cmath>
#include <numeric>
#include <limits.h>
using namespace std;

namespace ariel{
    //<<
    //I was having alot of trouble with this function, since I didn't define at as const or a friend in .hpp
    //So I used the internet for a solution.
        ostream& operator<<(ostream& output, const  Fraction& frac){
            output << frac.getNumerator() << "/" << frac.getDenominator() ;
            return output;
        };
    //Iput stream:
    istream& operator>>(istream& input , Fraction&  fraction){
        //char sep;
        int num, den;
        input >> num >>  den;
        cout << "num: " << num << endl;
        cout << "den: " << den << endl;
        if(den==0){
            throw runtime_error("invalid 0 input for denomitor");
        }
        if(input.fail() || input.peek() =='\n'){
            throw runtime_error("not the right format!");
        }

        fraction.nume = num;
        fraction.deno = den;
        return input;
    };
    
    //Constructor
    //do get transform in constructors as well.
        int Fraction::getDenominator()const{return this->deno;};
        int Fraction::getNumerator()const{return this->nume;};
        Fraction::Fraction(){};

        Fraction::Fraction(float number){
            reduce_float(number);
            this->nume = number*1000;
            this->deno = 1000;
            gcd_frac(this->nume,this->deno);

        };

        Fraction::Fraction(Fraction& first ,int second){
        };
        Fraction::Fraction(int first,int second){
                if(second == 0){
                    throw invalid_argument("invalid argument 0");
                }
            this->nume = first;
            this->deno = second;
            gcd_frac(nume,deno);
            // cout << nume << endl;
            // cout << deno << endl;
        };
        Fraction::Fraction(int first,Fraction& second){
        };
        //gcd is implemented using Euclidean algroithm i found on the web.
        int gcd(int num, int den) {
            if (den == 0)
                return num;
            else
                return gcd(den, num % den);
        }
        void gcd_frac(int& num , int& den){
            int divisor = gcd(num,den);
            num /= divisor;
            den /= divisor;
        };

        void reduce_float(float& num){
            num = floor(num * 1000) / 1000; 
        };

    //Addition
        Fraction operator+(const Fraction& first, const Fraction& second){
            int numerator =  0, denomator = 0;
            float result =0;
            result = (float(second.getNumerator())/second.getDenominator()) + (float(first.getNumerator())/first.getDenominator());
            if(result>INT_MAX || result < INT_MIN){
                throw overflow_error("more then int max");
            }
            numerator = ((first.getDenominator()*second.getNumerator())+(first.getNumerator()*second.getDenominator()));
            denomator= first.getDenominator()*second.getDenominator();
 
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);
        };

        Fraction operator+(float first,  const Fraction& second){
            int numerator = 0 , denomator = 0 ;
            reduce_float(first);
            float result =0;
            result = first + (float(second.getNumerator())/second.getDenominator());
            if(result>INT_MAX || result<INT_MIN){
                throw overflow_error("more then int max");
            }
            numerator = (first*1000*second.getDenominator()) + (1000*second.getNumerator());
            denomator = 1000*second.getDenominator();
            
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);

        };
        Fraction operator+(const Fraction& first , float second){
            int numerator = 0 , denomator = 0 ;
            float result =0;
            result = second + (float(first.getNumerator())/first.getDenominator());
            if(result>INT_MAX || result<INT_MIN){
                throw overflow_error("more then int max");
            }
            reduce_float(second);
            numerator = (first.getDenominator()*second*1000) + (1000*first.getNumerator());
            denomator = first.getDenominator()*1000;
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);
        };

    //Subtraction
        Fraction operator-(const Fraction& first, const Fraction& second){
            int numerator =0 , denomator =0 ;
            float result =0;
            result =   (float(first.getNumerator())/first.getDenominator()) - (float(second.getNumerator())/second.getDenominator());
            if(result>INT_MAX || result < INT_MIN){
                throw overflow_error("more then int max");
            }
            numerator = (first.getNumerator()*second.getDenominator())-(first.getDenominator()*second.getNumerator());
            denomator = first.getDenominator() * second.getDenominator();
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);
        };
        Fraction operator-(const Fraction& first, float second){
            int numerator = 0 , denomator = 0 ;
            reduce_float(second);
            float result =0;
            result =   (float(first.getNumerator())/first.getDenominator()) - second;
            if(result>INT_MAX || result < INT_MIN){
                throw overflow_error("more then int max");
            }
            numerator = (first.getNumerator()*1000) - (second*1000*first.getDenominator());
            denomator = first.getDenominator()*1000;
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);
        };
        Fraction operator-(float  first, const Fraction& second){
            int numerator = 0 , denomator = 0 ;
            reduce_float(first);
            float result =0;
            result =   first - (float(second.getNumerator())/second.getDenominator());
            if(result>INT_MAX || result < INT_MIN){
                throw overflow_error("more then int max");
            }
            numerator = (first*1000*second.getDenominator()) - (1000*second.getNumerator());
            denomator = 1000*second.getDenominator();
            
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);
        };
    //Divison
        Fraction operator/(const Fraction& first , const Fraction& second){
            if(second.getNumerator()==0){
                throw runtime_error("divided by zero");
            }
            float result =0;
            result =   (float(first.getNumerator())/first.getDenominator()) / (float(second.getNumerator())/second.getDenominator());
            if(result>INT_MAX || result < INT_MIN){
                throw overflow_error("more then int max");
            }
            int numerator =0 , denomator =0;
            numerator = first.getNumerator()*second.getDenominator();
            denomator = first.getDenominator()*second.getNumerator();
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);

        };
        Fraction operator/(const Fraction&  first, float second){
            if(second==0){
                throw runtime_error("divided by zero");
            }
            float result =0;
            result =   (float(first.getNumerator())/first.getDenominator()) / second;
            if(result>INT_MAX || result < INT_MIN){
                throw overflow_error("more then int max");
            }
            int numerator =0 , denomator =0;
            reduce_float(second);
            numerator = first.getNumerator()*1000;
            denomator = first.getDenominator()*second*1000;
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);
        };
        Fraction operator/(float  first , const Fraction& second){
            if(second.getNumerator()==0){
                throw runtime_error("divided by zero");
            }
            float result =0;
            result =   first / (float(second.getNumerator())/second.getDenominator());
            if(result>INT_MAX || result < INT_MIN){
                throw overflow_error("more then int max");
            }
            int numerator =0 , denomator =0;
            reduce_float(first);
            numerator = first*1000*second.getDenominator();
            denomator = 1000*second.getNumerator();
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);
        };
    //Mult
        Fraction operator*(const Fraction&  first, const Fraction& second){
            float result =0;
            result =   (float(first.getNumerator())/first.getDenominator()) * (float(second.getNumerator())/second.getDenominator());
            if(result>INT_MAX || result < INT_MIN){
                throw overflow_error("more then int max");
            }
            int numerator = 0 , denomator =0 ;
            numerator = first.getNumerator()*second.getNumerator();
            denomator = first.getDenominator() * second.getDenominator();
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);
        };
        Fraction operator*(const Fraction&  first, float second){
            float result =0;
            result =   (float(first.getNumerator())/first.getDenominator()) * second;
            if(result>INT_MAX || result < INT_MIN){
                throw overflow_error("more then int max");
            }
            int numerator = 0 , denomator =0 ;
            reduce_float(second);
            numerator = first.getNumerator()*second*1000;
            denomator = first.getDenominator() * 1000;
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);
        };
        Fraction operator*(float  first ,const Fraction& second){
            float result =0;
            result =   first * (float(second.getNumerator())/second.getDenominator());
            if(result>INT_MAX || result < INT_MIN){
                throw overflow_error("more then int max");
            }
            int numerator = 0 , denomator =0 ;
            reduce_float(first);
            numerator = first*1000*second.getNumerator();
            denomator = 1000 * second.getDenominator();
            gcd_frac(numerator,denomator);
            return Fraction(numerator,denomator);
        };
    //greater than
        bool operator>(const Fraction&  first , const Fraction& second){
            return ((float(first.getNumerator())/first.getDenominator())>(float(second.getNumerator())/second.getDenominator()));
        };
        bool operator>(const Fraction& first , float second){
            reduce_float(second);
            cout << "result : " << (float(first.getNumerator())/first.getDenominator()) << endl;
            return (float(first.getNumerator())/first.getDenominator())>(second);
        };
        bool operator>(float  first, const Fraction& second){
            reduce_float(first);
            return first>(float(second.getNumerator())/second.getDenominator());
        };
    //smaller then
        bool operator<(const Fraction&  first, const Fraction& second){
            return ((float(first.getNumerator())/first.getDenominator())<(float(second.getNumerator())/second.getDenominator()));
            };

        bool operator<(const Fraction&  first, float second){
            reduce_float(second);
            return (float(first.getNumerator())/first.getDenominator())<(second);
        };

        bool operator<(float  first, const Fraction& second){
            reduce_float(first);
            return first<(float(second.getNumerator())/second.getDenominator());
        };
    //greater equal
        bool operator>=(const Fraction&  first, const Fraction& second){
            return ((float(first.getNumerator())/first.getDenominator())>=(float(second.getNumerator())/second.getDenominator()));
        };
        bool operator>=(const Fraction&  first, float second){
            reduce_float(second);
            return (float(first.getNumerator())/first.getDenominator())>=(second);
        };
        bool operator>=(float  first, const Fraction& second){
            reduce_float(first);
            return first>=(float(second.getNumerator())/second.getDenominator());
        };
    //smaller equal
        bool operator<=(const Fraction&  first, const Fraction& second){
            return ((float(first.getNumerator())/first.getDenominator())<=(float(second.getNumerator())/second.getDenominator()));
        };
        bool operator<=(const Fraction&  first, float second){
            reduce_float(second);
            return (float(first.getNumerator())/first.getDenominator())<=(second);
        };
        bool operator<=(float  first, const Fraction& second){
            reduce_float(first);
            return first<=(float(second.getNumerator())/second.getDenominator());
        };
    //==
        bool operator==(const Fraction&  first, const Fraction& second){
            return ((float(first.getNumerator())/first.getDenominator())==(float(second.getNumerator())/second.getDenominator()));
        };
        bool operator==(const Fraction&  first, float second){
            reduce_float(second);
            return (float(first.getNumerator())/first.getDenominator())==(second);
        };
        bool operator==(float  first, const Fraction& second){
            reduce_float(first);
            return first==(float(second.getNumerator())/second.getDenominator());
        };
    ////Pre-fix
        Fraction& operator++(Fraction& fraction){
                fraction.nume += fraction.getDenominator();
                return fraction;
            };
        Fraction& operator--(Fraction& fraction){
                fraction.nume -= fraction.getDenominator();
                return fraction;
        };
    //Post-fix
        Fraction operator++(Fraction& fraction,int incerement){
            Fraction temp(fraction);
            fraction.nume += fraction.getDenominator();
            return temp;
        };
        Fraction operator--(Fraction& fraction,int increment){
            Fraction temp(fraction);
            fraction.nume -= fraction.getDenominator();
            return temp;
        };

    
}
