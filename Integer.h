

#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <iostream>
#include <string>

namespace cosc326 {

	class Integer {

	public:

            std::string getValue() const;
		Integer();                             // Integer i;
		Integer(const Integer& i);             // Integer j(i);
		Integer(const std::string& s);         // Integer k("123");

		~Integer();

		Integer& operator=(const Integer& i);  // j = i;

		// Unary operators
		Integer operator-() const;                   // -j;
		Integer operator+() const;                   // +j;

		// Arithmetic assignment operators
		Integer& operator+=(const Integer& i); // j += i;
		Integer& operator-=(const Integer& i); // j -= i;
		Integer& operator*=(const Integer& i); // j *= i;
		Integer& operator/=(const Integer& i); // j /= i;
		Integer& operator%=(const Integer& i); // j %= i;
                // std::string *value;
                //bool positive = true;
                    

		// lhs < rhs -- a 'friend' means operator isn't a member, but can access the private parts of the class.
		// You may need to make some other functions friends, but do so sparingly.
		friend bool operator<(const Integer& lhs, const Integer& rhs);
                friend bool operator==(const Integer& lhs, const Integer& rhs); // lhs == rhs
                friend std::ostream& operator<<(std::ostream& os, const Integer& i);  // std::cout << i << std::endl;
                friend std::istream& operator>>(std::istream& is, Integer& i);        // std::cin >> i;
                friend Integer addition_overload_helper(const Integer& a, const Integer &b);    
                friend Integer subtraction_overload_helper(const Integer& a, const Integer &b);
                //std::string *value;
                //bool positive = true;
               

	private:
		// Can add internal storage or methods here
                std::string *value;
                bool positive = true;
               
	};

	// Binary operators
	Integer operator+(Integer& lhs, const Integer& rhs); // lhs + rhs;
	Integer operator-(Integer& lhs, const Integer& rhs); // lhs - rhs;
	Integer operator*(Integer& lhs, const Integer& rhs); // lhs * rhs;
	Integer operator/(Integer& lhs, const Integer& rhs); // lhs / rhs;
	Integer operator%(Integer& lhs, const Integer& rhs); // lhs % rhs;

	//std::ostream& operator<<(std::ostream& os, const Integer& i);  // std::cout << i << std::endl;
	//std::istream& operator>>(std::istream& is, Integer& i);        // std::cin >> i;

	bool operator> (const Integer& lhs, const Integer& rhs); // lhs > rhs
	bool operator<=(const Integer& lhs, const Integer& rhs); // lhs <= rhs
	bool operator>=(const Integer& lhs, const Integer& rhs); // lhs >= rhs
        //bool operator==(const Integer& lhs, const Integer& rhs); // lhs == rhs
	bool operator!=(const Integer& lhs, const Integer& rhs); // lhs != rhs

	Integer gcd(const Integer& a, const Integer& b);  // i = gcd(a, b);

        //Integer addition_overload_helper(const Integer& a, const Integer &b);    
        //Integer subtraction_overload_helper(const Integer& a, const Integer &b);
}

#endif
