#include "Integer.h"

namespace cosc326 {

	Integer::Integer() {
            //sets value of Integer to 0 by default
            value = new std::string("0");
            positive = false;
	
	}

	Integer::Integer(const Integer& i) {
            if(this != &i){
                value = new std::string(*i.value);
                positive = i.positive;
            }
	
	}

	Integer::Integer(const std::string& s) {
            /* char first = s.front();
            bool modifier = false;
            // check is it has negative sign
            if(first == '-'){
                positive = false;
                modifier = true;
                //check if it has positive sign
            } else if (first == '+'){
                positive = true;
                modifier = true;
            }
            std::string str(s);
            //if it has sign, get part of number without sign
            if(modifier && str.length() > 1){
                str = str.substr(1);
            }
            //set value to inputed string
            value = new std::string(str);
            */
            std::string str(s);
            if(str.at(0) == '-'){
                positive = false;
                str.erase(0,1);
            } else if(str.at(0) == '+'){
                positive = true;
                str.erase(0,1);
            }else{
                positive = true;
            }
            if(str.length() == 0){
                str = "0";
            }
            
            value = new std::string(str);
            
	}


	Integer::~Integer() {
            delete value;
            
	
	}

	Integer& Integer::operator=(const Integer& i) {
            if(this == &i){
                return *this;
            }
            /*this->value = i.value;
            this->positive = i.positive;
            return *this;*/
            value = new std::string(i.value->begin(), i.value->end());
            // for (std::string::iterator it = i.value->begin(); it != i.value->end(); ++it){
            //     i.value->push_back(*it);
            // }
            positive = i.positive;
            return *this;

	}

	Integer Integer::operator-() const {
            Integer integer(*this);
            integer.positive = false;
            return integer;
            return Integer(*this);
           
	}

	Integer Integer::operator+() const {
            Integer integer(*this);
            integer.positive = true;
            return integer;
            //	return Integer(*this);
	}

	Integer& Integer::operator+=(const Integer& i) {
           
                           
                
            static Integer zero("0");
            if(i == zero){
                return *this;
            }
            else if (*this == zero){
                *this = i;
                return *this;
            }
            //adding two negatives becomes additon
            if(this->positive == false && i.positive == false){
                *this = addition_overload_helper(+*this, +i);
                *this = -*this;
                return *this;
            }
            
            // if adding a negative, make it subtraction
            if(this->positive == true && i.positive == false){
                if(+*this > +i){
                *this = subtraction_overload_helper(*this, +i);
                // *this = -*this;
                return *this;
                }
                else{
                    *this = subtraction_overload_helper(*this, +i);
                    *this = -*this;
                    return *this;
                }
            }
            // eg -3 + 26
            if(this->positive == false && i.positive == true){
                if(+*this < +i){
                    *this = subtraction_overload_helper(i, +*this);
                    return *this;
                }
                else{
                    *this = subtraction_overload_helper(i, +*this);
                    *this = -*this;
                    return *this;
                }
            }
                
            //add
            
            *this = addition_overload_helper(*this, i);
	    return *this;
	}

	Integer& Integer::operator-=(const Integer& i) {
            //Integer large("2345");
            //Integer small("6");
            //std::cout << "Testing " << subtraction_overload_helper(small,large) << "\n";
            Integer zero("0");
            if(i == zero){
                return *this;
            } else if (*this == zero){
                *this = -i;
                return *this;
            }
            
            //if subtraction a negitive value change sign and make addition
            //eg 23 - (-12)
            if(this->positive == true && i.positive == false){
                
                *this = addition_overload_helper(*this, +i);
                return *this;
            }

            // -23 - 12
            if(this->positive == false && i.positive == true){
                *this = addition_overload_helper(+*this, i);
                *this = -*this;
                return *this;
            }

            // negative - negative
            if(this->positive == false && i.positive == false){
                // eg (-23)-(-12)
                if(+*this > +i){
                    *this = subtraction_overload_helper(+*this, +i);
                    *this = -*this;
                    return *this;
                }
                // eg (-12) - (-23)
                else if(+*this < +i){
                    *this = subtraction_overload_helper(+*this, +i);
                    
                    return *this;
                }
            }
            //case for situations like 12 - 23
            //if(this->positive == true && i.positive == true){
            //    if(*this < i){
            //        *this = subtraction_overload_helper(i, *this);
            //        *this = -*this;
            //        return *this;
            //    }
            //}
                    
           
            *this = subtraction_overload_helper(*this, i);
		return *this;
	}

    Integer& Integer::operator*=(const Integer& i) {
        Integer zero("0");
        Integer one("1");
        // Integer test("-5");
        //if(test < zero){
        //    std::cout << "hello testing please\n";
        //}
        //Multiply by 0 = 0
        if(*this == zero || i == zero){
            *this = zero;
            return *this;
        }
        else if(*this == one){
            *this = i;
            return *this;
        }
        else if(i == one){
            return *this;
        }
        // eg 5 * -1 = -5
        else if(*this > zero && i == -one){
            *this = -*this;
            return *this;
        }
        //multiplying two negative nums
        else if(*this < zero && i < zero){
            *this = +*this;
            ;
            if(*this < +i){
                Integer temp = *this;
                Integer tempi = +i;
                Integer secondtempi = +i;
                Integer secondOne("1");
                while(one < temp){
                    secondtempi +=(tempi);
                    one +=(secondOne);
                }
                *this = secondtempi;
            }
            else{
                Integer temp = *this;
                Integer tempi = +i;
                Integer secondOne("1");
                //add this to itself i time to represent multiplication
                while(one < tempi){
                    //Integer temp = *this;
                    // std::cout << *this << "\n";
                    *this+=(temp);
                    one +=(secondOne);
                }
            }
        }
        //multiplying a negative by a positive
        //convert both to positive
        //do regular postive multplication but change result to negative 
        else if(*this < zero || i < zero){
            //std::cout << "hello i am here\n";
            *this = +*this;
            
            if(*this < +i){
                Integer temp = *this;
                Integer tempi = +i;
                Integer secondtempi = +i;
                Integer secondOne("1");
                while(one < temp){
                    secondtempi +=(tempi);
                    one +=(secondOne);
                }
                *this = secondtempi;
            }
            else{
                Integer temp = *this;
                Integer tempi = +i;
                Integer secondOne("1");
                //add this to itself i time to represent multiplication
                while(one < tempi){
                    //Integer temp = *this;
                    // std::cout << *this << "\n";
                    *this+=(temp);
                    one +=(secondOne);
                }
            }
            *this = -*this; //set final value to a negatve
                }
        else{
            
            if(*this < i){
                Integer temp = *this;
                Integer tempi = i;
                Integer secondtempi = i;
                Integer secondOne("1");
                while(one < temp){
                    secondtempi +=(tempi);
                    one +=(secondOne);
                }
                //std::cout << secondtempi << "\n";
                *this = secondtempi;
            }
        
            
        
            else{
                Integer temp = *this;
                Integer tempi = i;
                Integer secondOne("1");
                //add this to itself i time to represent multiplication
                while(one < tempi){
                    //Integer temp = *this;
                    //std::cout << *this << "\n";
                    *this+=(temp);
                    one +=(secondOne);
                }
            }
        }
            
                         
            
        return *this;
    }


	Integer& Integer::operator/=(const Integer& i) {
            //cant divide by zero so will just make it equal 0
            Integer zero("0");
            Integer one("1");
            //if(i == zero){
            //        *this = i;
            //        return *this;
            //    }
            //to divide just subtract until you reach zero and the amount of times you subtracted is the result
            Integer count("0");
            Integer temp(i);
            while(*this > zero){
                if(i == zero){
                    break;
                }
                    *this -= temp;
                    count += one;
                }
            if(count == zero){
                *this = zero;
                //std::cout << "hello";
                return *this;
            }
                *this = count - one;
                //std::cout << "hello";          
		return *this;
                
	}
    //add something for if they try to mod by zero?
	Integer& Integer::operator%=(const Integer& i) {
            // subtract what your % by until the value = the mod or is smaller
            //result will equal this value
            Integer zero("0");
            if(*this == zero || i == zero){
                return *this;
            }
            while( *this > i){
                *this-=(i);
            }
	    return *this;
	}

	Integer operator+( Integer& lhs, const Integer& rhs) {
            Integer left = Integer(lhs);
            Integer right = Integer(rhs);
            
            left += right;
		return left;
	}

	Integer operator-( Integer& lhs, const Integer& rhs) {
            Integer left = Integer(lhs);
            Integer right = Integer(rhs);
            left -= right;
		return left;
	}

     Integer operator*( Integer& lhs, const Integer& rhs) {
         Integer left = Integer(lhs);
         Integer right = Integer(rhs);
         left *= right;
		return left;
	}

	Integer operator/(Integer& lhs, const Integer& rhs) {
            Integer left = Integer(lhs);
            Integer right = Integer(rhs);
            left /= right;
		return left;
	}

	Integer operator%(Integer& lhs, const Integer& rhs) {
            Integer left = Integer(lhs);
            Integer right = Integer(rhs);
            left %= right;
		return left;
	}


	std::ostream& operator<<(std::ostream& os, const Integer& i) {
            std::string out_string = *i.value;
            if (!i.positive){
                out_string.insert(0, "-");
            }
            os << out_string;
            return os;
	}

	std::istream& operator>>(std::istream& is, Integer& i) {
            //          is >> i.positive >> i.value;
            //https://stackoverflow.com/a/4421719
            // if ( /* no valid Integer object found in input stream*/){
            // is.setstate(std::ios::failbit);
            // }
            //is >> *i.value;
           
            
            return is;
        }// std::cin >> i;
	

	bool operator<(const Integer& lhs, const Integer& rhs) {
            /* std::cout << "\n\nlhs value\n" << lhs.value << "\n"; */
            /* std::cout << "\n\nrhs value\n" << rhs.value << "\n"; */
            ////////
            //eg -2 < 4
            if(lhs.positive == false && rhs.positive == true){
                return true;
            }
            unsigned int lhs_length = lhs.value->length();
            unsigned int rhs_length = rhs.value->length();
            // If one and only one integer is positive
            if (lhs.positive ^ rhs.positive
                && *lhs.value != "0" && *rhs.value != "0"
                && *lhs.value != *rhs.value){
                // if rhs is positive lhs < rhs
                return rhs.positive;
            }
            if (lhs_length > rhs_length){
                return false;
            } else if (lhs_length < rhs_length){
                return true;
            }
            int increment = 9;
            // if (lhs_length <= increment){
            // 	return stoi(*lhs.value) < stoi(*rhs.value);
            // }

            int padding = lhs_length % increment;
            int lhs_stoi;
            int rhs_stoi;

            for (unsigned int i = 0; i < lhs_length; i+=increment){
	
                lhs_stoi = stoi(lhs.value->substr(i, increment));
                rhs_stoi = stoi(rhs.value->substr(i, increment));
                //std::cout << "\nlhs stoi\n" << lhs_stoi << "\n";
                //std::cout << "\nrhs stoi\n" << rhs_stoi << "\n";
                if (lhs_stoi != rhs_stoi){
                    //std::cout << "burder\n";
                    return lhs_stoi < rhs_stoi;
                }
            }
            return false;
	}

	bool operator> (const Integer& lhs, const Integer& rhs) {
            return !(lhs < rhs);
	}

	bool operator<=(const Integer& lhs, const Integer& rhs) {
            return lhs < rhs || lhs == rhs;
	}

	bool operator>=(const Integer& lhs, const Integer& rhs) {
            return lhs > rhs || lhs == rhs;
	}

	bool operator==(const Integer& lhs, const Integer& rhs) {
            //return lhs.positive == rhs.positive && lhs.value.compare(rhs.value) == 0;
            std::string str1 = *lhs.value;
            std::string str2 = *rhs.value;
            int result = str1.compare(str2);
            return lhs.positive == rhs.positive && result == 0;
		
	}

	bool operator!=(const Integer& lhs, const Integer& rhs) {
            return !(lhs == rhs);
	}


	Integer gcd(const Integer& a, const Integer& b) {
            //std::cout << "hello";
            Integer zero("0");
            
            Integer lhs(+a);
            Integer rhs(+b);
            Integer temp;
            if(lhs == zero || rhs == zero){ // solving gcd with a 0 in it
                return lhs;
            }

            if(lhs == zero){
                return rhs;
            }
            if(rhs == zero){
                return lhs;
            }
            //std::cout << lhs % rhs;
            return gcd(rhs, lhs % rhs);
        }
            
            
            /*if(lhs < 0){
                lhs = -lhs;
            }
            if(rhs < 0){
                rhs = -rhs;
            }
            if(v){
            while((lhs %= rhs) && ( rhs %= lhs))*/
            //if(rhs == zero){
            //    return lhs;
            // }
            //return gcd(rhs, (lhs % rhs));
                
            /*
            while(rhs != zero){
            temp = rhs;
            rhs = (lhs % rhs);
            lhs = temp;
            }
            return lhs;
            */
		
	

   

    Integer addition_overload_helper(const Integer& a, const Integer &b){

        std::string str = "";
        std::string str1 = *a.value;
        std::string str2 = *b.value;
        if(a > b){
            str1 = *b.value;
            str2 = *a.value;
        }
        //std::cout << "str1 " << str1 << "\n";
        //std::cout << "str2 " << str2 << "\n";
        int n1 = str1.length();
        int n2 = str2.length();

        reverse(str1.begin(), str1.end());
        reverse(str2.begin(), str2.end());

        int carry = 0;
        for(int i = 0; i < n1; i++){
            int sum = ((str1[i]-'0') + (str2[i]-'0') + carry);
            str.push_back((sum%10)+'0');
            carry = sum/10;
        }

        for(int i=n1; i < n2; i++){
            int sum = ((str2[i]-'0') + carry);
            str.push_back((sum%10)+'0');
            carry = sum/10;
        }

        if(carry){
            str.push_back(carry+'0');
        }
        reverse(str.begin(), str.end());
        //std::cout << "final string " << str << "\n";
        Integer result(str);
        return result;
                
            
            
       

    }

    Integer subtraction_overload_helper(const Integer& a, const Integer &b){

        //std::string result = "";
        std::string left = *a.value;
        std::string right = *b.value;
        std::string top;
        std::string bot;
        int leftSize = left.length();
        int rightSize = right.length();
        bool isneg = false;
        //if both have same length
        if (leftSize == rightSize){
            if(left.compare(right) < 0){
                isneg = true;
            }
        }
        
        //if left has smaller length than right
        else if(leftSize < rightSize){
            //left pad zeros so both strings have the same length for strcmp
            while(left.length() != right.length()){
                left = "0" + left;
            }
            if(left.compare(right) < 0){
                isneg = true;
            }
        }
        else if(rightSize < leftSize){
            //left pad zeros so both strings have the same length for strcmp
            while(right.length() != left.length()){
                right = "0" + right;
            }
            if(left.compare(right) < 0){
                isneg = true;
            }
        }
        
        top = left;
        bot = right;
        if(isneg){
            top = right;
            bot = left;
        }
        top = "00" + top;
        bot = "00" + bot;
        //std::cout << "top " << top << "\n";
        //std::cout << "bot " << bot << "\n";
        int carry = 0;
        int temp;
        int maxSize = top.length();
        std::string result = top; // make it the same as top, so you can just directly change each value instead of appending onto empty string
        int helper; //used for converting between chars and ints
        //std::string six = "6";
        //std::string three = "3";
        //int answer = (six[0]-'0') - (three[0]-'0');
        //std::string hope = "hope";
        //hope[0] = answer+'0';
        //std::cout << hope;
        
        //return a;
            
        //loop through the string subtracting the nums as you go
        for(int i = maxSize - 1; i >0; i--){
            temp = (top[i]-'0') - (bot[i]-'0');
            if(temp < 0){
                //if the value before current one is not zero, subtract one from it
                if(top[i - 1] != '0'){
                    top[i - 1] = ((top[i-1]-'0') - 1)+'0';
                }
                // if the value before hand is zero, but not first element(as will always be a leading zero)
                else if(top[i -1] == '0' && i - 1 != 0){
                    top[i - 1] = '9'; // turn zero into 9
                    int j = i - 2; // j is element before the zero
                    while(j > 0){ //if there is a zero befroe the current number, convert it to nine, if its not a zero just subtract it by one
                        if(top[j] != '0'){
                            top[j] = ((top[j]-'0') -1)+'0';
                            break;
                        }
                        if(top[j] == '0'){
                            top[j] = '9';
                        }
                        j--;
                    }
                }
                temp = temp + 10;
                result[i] = temp+'0';
            }
            else{
                result[i] = temp+'0';
            }
                        
                        
        }
        //removes leading zeros
        result.erase(0, std::min(result.find_first_not_of('0'), result.size()-1));
        //std::cout << "result is " << result << "\n";
        
        Integer final(result);
        if(isneg){
            
            return -final;
        }
        else{
            //std::cout << "final result is " << result << "\n";
            return final;
        }
        //std::cout << "final result is " << result << "\n";
        //return final;
    }
    std::string Integer::getValue() const{
        return *value;
    }
}     
