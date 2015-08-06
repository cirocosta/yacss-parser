#ifndef YACSS__CSSBASEVALUE_HH
#define YACSS__CSSBASEVALUE_HH

#include "CSSValues.hh"
#include <iostream>
#include <stdexcept>

namespace yacss
{

class CSSBaseValue
{
private:
  struct m_base {
    virtual ~m_base() {}
    virtual m_base* clone() const = 0;
  };

  template <typename T>
  struct m_data : m_base {
    T _value;

    m_data(T const& value) : _value(value) {}

    m_base* clone() const { return new m_data<T>(*this); }
  };

  m_base* _ptr;

public:
  ValueType type;

public:
  CSSBaseValue()
  {
    type = ValueType::Undefined;
    _ptr = new m_data<char>(0);
  }

  template <typename T>
  CSSBaseValue(T const& value)
      : _ptr(new m_data<T>(value))
  {
    type = value.type;
  }

  CSSBaseValue(CSSBaseValue const& other) : _ptr(other._ptr->clone())
  {
    type = other.type;
  }

  CSSBaseValue& operator=(CSSBaseValue const& other)
  {
    CSSBaseValue(other).swap(*this);

    return *this;
  }

  void swap(CSSBaseValue& other)
  {
    std::swap(this->_ptr, other._ptr);
    std::swap(this->type, other.type);
  }

  ~CSSBaseValue()
  {
    if (this->_ptr)
      delete this->_ptr;
    this->_ptr = nullptr;
  }

  template <typename T>
  inline const T& get() const
  {
    return static_cast<m_data<T>&>(*this->_ptr)._value;
  }

  inline bool operator==(const CSSBaseValue& other) const
  {
    if (other.type != this->type)
      return false;
    if (other.type == ValueType::Length)
      return this->get<LengthValue>() == other.get<LengthValue>();
    else if (other.type == ValueType::Keyword)
      return this->get<KeywordValue>() == other.get<KeywordValue>();
    else if (other.type == ValueType::ColorRGBA)
      return this->get<ColorRGBAValue>() == other.get<ColorRGBAValue>();
    else
      throw std::runtime_error("CSSBaseValue== : Unknown Type.");
  }
};
std::ostream& operator<<(std::ostream& o, const CSSBaseValue& val);

}; // ! ns yacss

#endif
