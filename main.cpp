#include "include/fixed_point.hpp"
#include <iostream>

template <typename T = int, unsigned int FRB = 8>
void operatorTest(fp::fixed_point<T,FRB> fp1, fp::fixed_point<T,FRB> fp2)
{
  std::cout << "Fixed point number 1: " << fp1 << " " << fp1.raw_value() << std::endl; 
  std::cout << "Fixed point number 2: " << fp2 << " " << fp2.raw_value() << std::endl; 
  std::cout<< "sum = " << fp1+fp2 << std::endl;
  std::cout<< "dif = " << fp1-fp2 << std::endl;
  std::cout<< "prod = " << fp1*fp2 << std::endl;
  std::cout<< "frac = " << fp1/fp2 << std::endl;
  std::cout<< fp1 << " == " << fp2 << "(" << (fp1 == fp2) << ")" << std::endl;  
  std::cout<< fp1 << " != " << fp2 << "(" << (fp1 != fp2) << ")" << std::endl;  
  std::cout<< fp1 << " <= " << fp2 << "(" << (fp1 <= fp2) << ")" << std::endl;  
  std::cout<< fp1 << " >= " << fp2 << "(" << (fp1 >= fp2) << ")" << std::endl;  
  std::cout<< fp1 << " < " << fp2 << "(" << (fp1 < fp2) << ")" << std::endl;  
  std::cout<< fp1 << " > " << fp2 << "(" << (fp1 > fp2) << ")" << std::endl;  
}

int main (int argc, char *argv[]) 
{
  fp::fixed_point<int, 2> fp2(103, 0);
  fp::fixed_point<int, 2> fp1(203,0);
  //operatorTest(fp1,fp2);

  fp::fixed_point<int, 8> fpeq1(10123, 4);
  fp::fixed_point<int, 8> fpeq2(1234, 4);
  //operatorTest(fpeq1, fpeq2);

  fp::fixed_point<int, 8> fpneg1(-100, 4);
  fp::fixed_point<int, 8> fpneg2(26, 4);
  operatorTest(fpneg1, fpneg2);
  return 0;
}
