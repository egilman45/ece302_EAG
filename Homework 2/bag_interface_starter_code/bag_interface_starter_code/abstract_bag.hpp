#ifndef STUDENT_ABSTRACT_BAG_HPP
#define STUDENT_ABSTRACT_BAG_HPP

template<typename T> class AbstractBag {
public:

  virtual std::size_t getCurrentSize() const = 0;

  virtual bool isEmpty() const = 0;

  virtual bool add(const T& entry) = 0;

  virtual bool remove(const T& entry) = 0;

  virtual void clear() = 0;

  virtual std::size_t getFrequencyOf(const T& entry) const = 0;

  virtual bool contains(const T& entry) const = 0;

};

#endif
