/* 
   Test main for Rationals and Integer
 */


#include "Integer.h"
#include "Rational.h"

#include <iostream>

/*int main () {

	cosc326::Integer i;

	std::cout << "The Integer i is:" << std::endl;
	
	return 0;
        }*/

using namespace cosc326;

void print_operation(Integer *i, Integer *j, Integer *result, char op){
    std::cout << *i << " " << op << " " << *j << " = " << *result << "\n";
    //std::cout << "howdy\n";
}

void print_rational_operation(Rational *i, Rational *j, Rational *result, char op){
    std::cout << *i << " " << op << " " << *j << " = " << *result << "\n";
}

int main(void){
    std::cout << "Enter a number i\n";
    std::string str;
    std::cin >> str;
    Integer i(str);
    std::cout << "Enter a number j\n";
    std::string other_str;
    std::cin >> other_str;
    Integer j(other_str);
    if(i < j){
        std::cout << "hello";
    }
    Integer plus = i + j;
    Integer minus = i - j;
    print_operation(&i, &j, &plus, '+');
    print_operation(&i, &j, &minus, '-');
    Integer mult = i * j;
    print_operation(&i, &j, &mult, '*');
    Integer divide = i / j;
    print_operation(&i, &j, &divide, '/');
    Integer mod = i%j;
    //std::cout << "hello\n";
    print_operation(&i, &j, &mod, '%');
    //std::cout << "hello\n";
    //Integer y(gcd(i,j));
    Integer zero("0");
    Integer alsoZero("0");
    
    Integer g=gcd(i,j);
    
    print_operation(&i, &j, &g, 'g');
    std::string rational_expression;
    Integer num("12");
    Integer dom("24");
    Integer whole("3");;
    Rational test(whole ,num, dom);
    std::cout << "test " << test << "\n";
    std::cout << "enter a rational expression\n";
    std::cin >> rational_expression;
    Rational x(rational_expression);
    std::string rational_expression_y;
    std::cin >> rational_expression_y;
    Rational y(rational_expression_y);
    Rational add = x + y;
    Rational subtr = x - y;
    Rational times = x * y;
    print_rational_operation(&x, &y, &add, '+');
    print_rational_operation(&x, &y, &subtr, '-');
    print_rational_operation(&x, &y, &times, '*');
}
