#ifndef FIXED_POINT_HPP
#define FIXED_POINT_HPP

#include <ios>
#include <limits>
#include <iostream>
#include <cmath>

namespace fp {

template <typename T = int>
constexpr T shiftValue(T value, int amount) noexcept
{
  if (value < 0) 
  {
    if (amount < 0) 
    {
      return ~(~value >> -amount);
    } 
    else 
  {
      return -(-value << amount);
    }
  } 
  else 
{
    if (amount < 0) 
    {
      return value >> -amount;
    } 
    else
  {
      return value << amount;
    }
  }
}


template<typename T = int, unsigned int FRB = 8>
struct fixed_point
{
private:
  // Raw data about this number
  T raw_;
public:

  // Static members
  static const int frac_count = FRB;
  static const int int_count = std::numeric_limits<T>::digits - FRB;

  // Constructors
  constexpr fixed_point(const fixed_point &other) = default;
  fixed_point &operator=(const fixed_point &other) = default;
  ~fixed_point() = default;

  constexpr fixed_point() noexcept : raw_(0) {}

  constexpr fixed_point(T int_part) noexcept
  : raw_(shiftValue(int_part, frac_count)) {}

  constexpr fixed_point(T raw_value, int shift) noexcept
  : raw_(shiftValue(raw_value, shift)) {}

  // Getters
  inline T raw_value() const noexcept 
  {
    return raw_;
  }

  constexpr T int_part() const noexcept
  {
    return shiftValue(raw_, -frac_count);
  }

  constexpr T frac_part() const noexcept
  {
    using ULL = unsigned long long;
    return raw_ & (frac_count <= 0 ? 0 : int_count <= 0 ? ~0ULL : (1ULL << ULL(frac_count >= 0 ? frac_count : 0)) - 1ULL);
  }

  // Arithmetics
  constexpr  fixed_point<T, FRB>& operator += (const fixed_point<T, FRB>& lfp)
  {
    raw_ += lfp.raw_value();
    return *this;
  }
  constexpr  fixed_point<T, FRB>& operator -= (const fixed_point<T, FRB>& lfp)
  {
    raw_ -= lfp.raw_value();
    return *this;
  }
  constexpr  fixed_point<T, FRB>& operator *= (const fixed_point<T, FRB>& lfp)
  {
    raw_ = shiftValue(raw_ * lfp.raw_value(), -fixed_point<T,FRB>::frac_count );
    return *this;
  }
  constexpr  fixed_point<T, FRB>& operator /= (const fixed_point<T, FRB>& lfp)
  {
    raw_ = shiftValue(raw_ / lfp.raw_value(), fixed_point<T,FRB>::frac_count );
    return *this;
  }

  constexpr fixed_point<T, FRB> operator+ (const fixed_point<T, FRB>& lfp) const
  {
    return {raw_ + lfp.raw_value(), 0};
  }
  constexpr   fixed_point<T, FRB> operator- (const fixed_point<T, FRB>& lfp) const
  {
    return {raw_ - lfp.raw_value(), 0};
  }
  constexpr  fixed_point<T, FRB> operator* (const fixed_point<T, FRB>& lfp) const
  {
    return {raw_ * lfp.raw_value(), -fixed_point<T,FRB>::frac_count};
  }
  constexpr  fixed_point<T, FRB> operator/ (const fixed_point<T, FRB>& lfp) const
  {
    return {raw_ / lfp.raw_value(), fixed_point<T,FRB>::frac_count} ;
  }

  // Comparison
  constexpr bool operator== (const fixed_point<T, FRB>& lfp) const
  {
    return raw_ == lfp.raw_value();
  }
  constexpr  bool operator!= (const fixed_point<T, FRB>& lfp) const
  {
    return raw_ != lfp.raw_value();
  }
  constexpr  bool operator< (const fixed_point<T, FRB>& lfp) const
  {
    return raw_ < lfp.raw_value();
  }
  constexpr  bool operator> (const fixed_point<T, FRB>& lfp) const
  {
    return raw_ > lfp.raw_value();
  }
  constexpr  bool operator <= (const fixed_point<T, FRB>& lfp) const
  {
    return raw_ <= lfp.raw_value();
  }
  constexpr  bool operator >= (const fixed_point<T, FRB>& lfp) const
  {
    return raw_ >= lfp.raw_value();
  }
};

// Stream
template <typename T = int, unsigned int FRB = 8>
inline std::ostream &operator<<(std::ostream &stream, const fixed_point<T, FRB> &fixedNum)
{
  //stream << fixedNum.int_part() << "+" << fixedNum.frac_part() << "*2^-" << fixed_point<T, FRB>::frac_count;

  T frac = static_cast<T>(fixedNum.frac_part() * std::pow(5, fixed_point<T, FRB>::frac_count));
  while(frac % 10 == 0 && frac != 0) frac /= 10; 

  stream << fixedNum.int_part() << "." << frac;
  return stream;
}

}

#endif // !FIXED_POINT_HPP 
