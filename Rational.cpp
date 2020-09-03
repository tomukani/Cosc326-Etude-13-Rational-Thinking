#include "Rational.h"

namespace cosc326 {

	Rational::Rational() {
            whole = Integer();//std::string("0");
            denominator = Integer();//std::string("0");
            numerator = Integer();//std::string("0");
            positive = true;

	}

	Rational::Rational(const std::string& s) {
            std::string str = s;
            //std::cout << "str " << str << "\n";
            if(str.at(0) == '-'){
                positive = false;
                str.erase(0,1);
            }
            else if(str.at(0) == '+'){
                positive = true;
                str.erase(0,1);
            }
            else{
                positive = true;
            }
            bool containsDecimal = false;
            bool containsFraction = false;
            // looks through string to see if it contains a decimal, or fractional point
            for( int i = 0; i < str.length(); i++){
                if(str[i] == '.'){
                    containsDecimal = true;
                }
                if(str[i] == '/'){
                    containsFraction = true;
                }
            }
            //std::cout << "str " << str << "\n";
            int i = 0;
            std::string first = "";
            std::string denom = "";
            std::string numer = "";
            // if input is 4/3 so has no whole number part
            if(containsFraction == true && containsDecimal == false){
                while(str[i] != '/'){
                    numer.push_back(str[i]);
                    i++;
                }
                while(i < str.length()){
                    if(str[i] != '/'){
                        denom.push_back(str[i]);
                    }
                    i++;
                }
                i = 0;
                //std::cout << "str " << str << "\n";
                //std::cout << "denominator " << denom << "\n";
                //std::cout << "numerator " << numer << "\n";

            }
           
            else{
                i = 0;
                //if theres a decimal point in input, extract the whole number part
                //std::cout << "hello";
                if(containsDecimal){
                
                    while(str[i] != '.'){
                        first.push_back(str[i]);
                        i++;
                    }
                }
                //if there's not then whole string is the whole number
                else{
                    first = str;
                }
                //i = 0;
                //sepearte the denominator and the numerator from the string
                if(containsFraction){
                    while(str[i] != '/'){
                        if(str[i] != '.'){
                            numer.push_back(str[i]);
                        }
                        i++;
                    }
                    while(i < str.length()){
                        if(str[i] != '/'){
                            denom.push_back(str[i]);
                        }
                        i++;
                    }
                }
            }
            //std::cout << "whole " << first << "\n";
            //std::cout << "denom" << denom << "\n";
            //std::cout << "numer " << numer << "\n";
            if(first.length() == 0){
                first = "0";
            }
            if(denom.length() == 0){
                denom = "0";
            }
            if(numer.length() == 0){
                numer = "0";
            }
            whole = Integer(first);
            denominator = Integer(denom);
            numerator = Integer(numer);
            //std::cout << "whole " << first << "\n";
            //std::cout << "denom" << denom << "\n";
            //std::cout << "numer " << numer << "\n";
                

	}

	Rational::Rational(const Rational& r) {
            if(this != &r){
                positive = r.positive;
                whole = r.whole;
                denominator = r.denominator;
                numerator = r.numerator;
                }

	}

	Rational::Rational(const Integer& a) {
            Integer zero("0");
            
            if(a >= zero){
                positive = true;
            }
            if(a < zero){
                positive = false;
            }
            whole = a;
            

	}

    // Now when creating a fractional part will simplify the fractions
	Rational::Rational(const Integer& a, const Integer& b) {
              
            Integer zero("0");
            Integer one("1");
            Integer lhs(a);
            Integer rhs(b);

            whole = zero;
            //while(lhs > rhs){
            //    whole += one;
            //    lhs -= rhs;
            //}
            //std::cout << " whole is " << whole << "\n";
            //std::cout << "num is " << lhs << "\n";
            //std::cout << "denom is " << rhs << "\n";
            Integer divisor(gcd(a,b));
            if(divisor != zero){
                lhs/=divisor;
                rhs/=divisor;
            }
            if(lhs < zero){
                positive = false;
            }
            denominator = rhs;
            numerator = lhs;

	}
    // Simplification also works with this constructor
	Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
            Integer zero("0");
            if(a < zero){
                positive = false;
            }
            Integer lhs(b);
            Integer rhs(c);

           
            //while(lhs > rhs){
            //    whole += one;
            //    lhs -= rhs;
            //}
            //std::cout << " whole is " << whole << "\n";
            //std::cout << "num is " << lhs << "\n";
            //std::cout << "denom is " << rhs << "\n";
            Integer divisor(gcd(a,b));
            if(divisor != zero){
                lhs/=divisor;
                rhs/=divisor;
            }
            if(lhs < zero){
                positive = false;
            }
            whole = a;
            denominator = rhs;
            numerator = lhs;
	}

	Rational::~Rational() {
            //delete whole.value;
            //delete denominator.value;
            //delete numerator.value;

	}

	Rational& Rational::operator=(const Rational& r) {
            
            if(this == &r){
		return *this;
            }
           
            this->whole = r.whole;
            
            this->denominator = r.denominator;
            
            this->numerator = r.numerator;
           
            this->positive = r.positive;
            
            return *this;
	}

	Rational Rational::operator-() const {
            Rational rational(*this);
            rational.positive = true;
            
            return Rational(rational);
	}

	Rational Rational::operator+() const {
            Rational rational(*this);
            rational.positive = true;
            
		return Rational(rational);
	}


    //Currently can += two positive numbers that can be whole, fractional or both
    // Next step is to add negative functionality and add case for when adding two fractions will make a whole number or will be above 1
	Rational& Rational::operator+=(const Rational& r) {
            // first step determine the fractional relationships of the numbers being +
            // will use an integer that = 0, to tell whether both rationals have whole/factional parts etc
            //std::cout << "mad it to += \n";
            Integer zero("0");
            Integer one("1");
            Rational lhs(*this);
            Rational rhs(r);
            
            // if lhs = zero return rhs
            if(lhs.whole == zero && lhs.denominator == zero && lhs.numerator == zero){
                *this = rhs;
                return *this;
            }
            //if rhs = zero return lhs
            if(rhs.whole == zero && rhs.denominator == zero && rhs.numerator == zero){
                *this = lhs;
                return *this;
            }
            

            //both only have whole parts
            if(((lhs.whole != zero && lhs.denominator == zero) && lhs.numerator == zero) && (rhs.whole != zero && rhs.denominator == zero) && rhs.numerator == zero){
                lhs.whole = lhs.whole + rhs.whole; // add the whole parts together
                *this = lhs;
                return *this;
            }
            
            //both only have fractional parts
            if((lhs.whole == zero && lhs.denominator != zero) && (rhs.whole == zero && rhs.denominator != zero)){
                Integer leftTop;
                Integer rightTop;
                Integer finalTop;
                Integer bottom;
                if(lhs.denominator == rhs.denominator){
                    bottom = lhs.denominator;
                    finalTop = lhs.numerator + rhs.numerator;
                }
                else{
                    leftTop = lhs.numerator * rhs.denominator;
                    rightTop = rhs.numerator * lhs.denominator;
                    finalTop = leftTop + rightTop;
                    bottom = lhs.denominator * rhs.denominator;
                    Integer divider=gcd(finalTop,bottom);
                    //std::cout << " numerator is " << finalTop << "\n";
                    //std::cout << " denominator is " << bottom << "\n";
                    if(divider != one){
                        finalTop/=divider;
                        bottom/=divider;
                    }
                }
                lhs.denominator = bottom;
                lhs.numerator = finalTop;
                *this = lhs;
                return *this;
            }
            
            //if only lhs has fraction
            if(lhs.denominator != zero && rhs.denominator == zero){
                lhs.whole += rhs.whole;
                *this = lhs;
                return *this;
            }

            //if only rhs has fraction
            if(lhs.denominator == zero && rhs.denominator != zero){
                lhs.whole += rhs.whole;
                lhs.denominator = rhs.denominator;
                lhs.numerator = rhs.numerator;
                *this = lhs;
                return *this;
            }
            
            // if reach here, just add the whole number parts and the fractional parts
            lhs.whole += rhs.whole;
            //steps for adding two fractions
            Integer leftTop;
            Integer rightTop;
            Integer finalTop;
            Integer bottom;
            if(lhs.denominator == rhs.denominator){
                bottom = lhs.denominator;
                finalTop = lhs.numerator + rhs.numerator;
            }
            else{
                leftTop = lhs.numerator * rhs.denominator;
                rightTop = rhs.numerator * lhs.denominator;
                finalTop = leftTop + rightTop;
                bottom = lhs.denominator * rhs.denominator;
                Integer divider=gcd(finalTop,bottom);
                //std::cout << " numerator is " << finalTop << "\n";
                //std::cout << " denominator is " << bottom << "\n";
                if(divider != one){
                    finalTop/=divider;
                    bottom/=divider;
                }
            }
            lhs.denominator = bottom;
            lhs.numerator = finalTop;
            *this = lhs;
            return *this;
	}


	Rational& Rational::operator-=(const Rational& r) {
            // first step determine the fractional relationships of the numbers being +
            // will use an integer that = 0, to tell whether both rationals have whole/factional parts etc
            //std::cout << "mad it to += \n";
            Integer zero("0");
            Integer one("1");
            Rational lhs(*this);
            Rational rhs(r);
            
            // if lhs = zero return rhs
            if(lhs.whole == zero && lhs.denominator == zero && lhs.numerator == zero){
                *this = rhs;
                return *this;
            }
            //if rhs = zero return lhs
            if(rhs.whole == zero && rhs.denominator == zero && rhs.numerator == zero){
                *this = lhs;
                return *this;
            }

            if(lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator){
                lhs.numerator = zero;
                rhs.numerator = zero;
                lhs.denominator = zero;
                rhs.denominator = zero;
            }

            //both only have whole parts
            if(((lhs.whole != zero && lhs.denominator == zero) && lhs.numerator == zero) && (rhs.whole != zero && rhs.denominator == zero) && rhs.numerator == zero){
                lhs.whole = lhs.whole - rhs.whole; // add the whole parts together
                *this = lhs;
                return *this;
            }
            
            //both only have fractional parts
            if((lhs.whole == zero && lhs.denominator != zero) && (rhs.whole == zero && rhs.denominator != zero)){
                //std::cout << "howdy";
                Integer leftTop;
                Integer rightTop;
                Integer finalTop;
                Integer bottom;
                if(lhs.numerator == zero && rhs.denominator == zero && lhs.denominator == zero && rhs.numerator == zero){
                    lhs.whole = zero;
                }
                if(lhs.denominator == rhs.denominator){
                    bottom = lhs.denominator;
                    finalTop = lhs.numerator - rhs.numerator;
                }
                else{
                    leftTop = lhs.numerator * rhs.denominator;
                    rightTop = rhs.numerator * lhs.denominator;
                    //std::cout << "right top is " << rightTop << "\n";
                    //std::cout << "left top is " << leftTop << "\n";
                    //finalTop = leftTop - rightTop;
                    if(leftTop > rightTop){
                        finalTop = leftTop - rightTop;
                    }
                    else{
                        finalTop = rightTop - leftTop;
                    }
                    
                    bottom = lhs.denominator * rhs.denominator;
                    //std::cout << "bottom is " << bottom << "\n";
                    Integer divider=gcd(finalTop,bottom);
                    //std::cout << " numerator is " << finalTop << "\n";
                    //std::cout << " denominator is " << bottom << "\n";
                    if(divider != one){
                        finalTop/=divider;
                        bottom/=divider;
                    }
                }
                lhs.denominator = bottom;
                lhs.numerator = finalTop;
                *this = lhs;
                return *this;
            }
            
            //if only lhs has fraction
            if(lhs.denominator != zero && rhs.denominator == zero){
                lhs.whole -= rhs.whole;
                *this = lhs;
                return *this;
            }

            //if only rhs has fraction
            if(lhs.denominator == zero && rhs.denominator != zero){
                lhs.whole -= rhs.whole;
                lhs.denominator = rhs.denominator;
                lhs.numerator = rhs.numerator;
                *this = lhs;
                return *this;
            }
            
            // if reach here, just add the whole number parts and the fractional parts
            lhs.whole -= rhs.whole;
            //steps for adding two fractions
            Integer leftTop;
            Integer rightTop;
            Integer finalTop;
            Integer bottom;
            if(lhs.denominator == rhs.denominator){
                bottom = lhs.denominator;
                finalTop = lhs.numerator - rhs.numerator;
            }
            else{
                leftTop = lhs.numerator * rhs.denominator;
                rightTop = rhs.numerator * lhs.denominator;
                if(leftTop > rightTop){
                    finalTop = leftTop - rightTop;
                }
                else{
                    finalTop = rightTop - leftTop;
                }
                //finalTop = leftTop - rightTop;
                bottom = lhs.denominator * rhs.denominator;
                Integer divider=gcd(finalTop,bottom);
                //std::cout << " numerator is " << finalTop << "\n";
                //std::cout << " denominator is " << bottom << "\n";
                if(divider != one){
                    finalTop/=divider;
                    bottom/=divider;
                }
            }
            lhs.denominator = bottom;
            lhs.numerator = finalTop;
            //std::cout << "value is " << lhs << "\n";
            *this = lhs;
            return *this;
	}

	Rational& Rational::operator*=(const Rational& r) {
            //std::cout << "Hello I am here\n";
            Rational zero("0");
            if(r == zero){
                *this = zero;
                    
		return *this;
            }
            if(*this == zero){
                return *this;
            }
            Rational lhs(*this);
            Rational rhs(r);
            Integer top; //numerator
            Integer bottom; //denominator
            top = lhs.numerator * rhs.numerator;
            bottom = lhs.denominator * rhs.denominator;
            //std::cout << "bottom " << bottom << "\n";
            //std::cout << "top " << top << "\n";
            lhs.numerator = top;
            lhs.denominator = bottom;
            lhs.whole *= rhs.whole;
            *this = lhs;
            return *this;
	}

	Rational& Rational::operator/=(const Rational& r) {
		return *this;
	}

	Rational operator+(const Rational& lhs, const Rational& rhs) {
            //std::cout << "made it to plus";
            Rational left(lhs);
            Rational right(rhs);
            left += right;
		return left;
	}

	Rational operator-(const Rational& lhs, const Rational& rhs) {
            Rational left(lhs);
            Rational right(rhs);
            left -= right;
		return left;
	}

	Rational operator*(const Rational& lhs, const Rational& rhs) {
            //std::cout << "hello I am here\n";
            Rational left(lhs);
            Rational right(rhs);
            left *= right;
		return left;
	}

	Rational operator/(const Rational& lhs, const Rational& rhs) {
		return lhs;
	}

	std::ostream& operator<<(std::ostream& os, const Rational& i) {
            //std::cout << "made it to output \n";
            std::string whole_string = ""; //holds value of whole part
            std::string numerator_string = ""; // holds valueof numerator
            std::string denominator_string = ""; //holds value of denominator
            Integer zero("0");
            if(i.getWhole() == zero){
                whole_string = zero.getValue();
            }
            if(i.getNumerator() == zero && i.getDenominator() == zero){
                numerator_string = zero.getValue();
                denominator_string = zero.getValue();
            }
            if(i.getWhole() != zero){
                whole_string = i.getWhole().getValue();
            }
            if(i.getNumerator() != zero){
                numerator_string = i.getNumerator().getValue();
            }
            if(i.getDenominator() != zero){
                denominator_string = i.getDenominator().getValue();
            }
            //print whole . fraction
            if(i.getNumerator() != zero && i.getWhole() != zero){
                os << whole_string << "." << numerator_string << "/" << denominator_string;
            }
            //print just fraction
            else if(i.getNumerator() != zero && i.getWhole() ==zero){
                os << numerator_string << "/" << denominator_string;
            }
            
            //print jut whole;
            else{
                os << whole_string;
            }
            
		return os;
	}
	std::istream& operator>>(std::istream& is, Rational& i) {
		return is;
	}

	bool operator<(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator> (const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator<=(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator>=(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator!=(const Rational& lhs, const Rational& rhs) {
            return true;
	}
    
    Integer Rational::getNumerator() const{
        return numerator;
    }
    Integer Rational::getDenominator() const{
        return denominator;
    }
    Integer Rational::getWhole() const{
        return whole;
    }

}
