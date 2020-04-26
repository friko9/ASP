#ifndef UTEST_HASHSET_H
#define UTEST_HASHSET_H

#include <gtest/gtest.h>

struct HashsetObjectT
{
  virtual bool contains(int x) =0;
  virtual void insert(int x) =0;
  virtual void remove(int x) =0;
  virtual HashsetObjectT* clone() const = 0;
  virtual ~HashsetObjectT(){};
public:
  HashsetObjectT(std::string name): name(name){}
  std::string toString() const { return name; }
private:
  std::string name;
};

template<typename TestT>
struct HashsetObjectImpl : public HashsetObjectT
{
  using HashsetObjectT::HashsetObjectT;
  bool contains(int x) override { return test_obj.contains(x); }
  void insert(int x) override { return test_obj.insert(x); }
  void remove(int x) override { return test_obj.remove(x); }
  HashsetObjectImpl<TestT>* clone() const override { return new HashsetObjectImpl<TestT>(*this); }
private:
  HashsetObjectImpl(const HashsetObjectImpl<TestT>& arg):HashsetObjectT(arg),test_obj(arg.test_obj){}
  TestT test_obj {};
};

template <>
class testing::internal::UniversalTersePrinter<const HashsetObjectT*> {
public:
  static void Print(const HashsetObjectT* obj, ::std::ostream* os) {
    *os << obj->toString();
  }
};

template <>
class testing::internal::UniversalTersePrinter<const HashsetObjectT> {
public:
  static void Print(const HashsetObjectT& obj, ::std::ostream* os) {
    *os << obj.toString();
  }
};

template<typename TestT>
HashsetObjectT* make_hashset_object(std::string name){ return new HashsetObjectImpl<TestT>(name); }

#define NEW_TEST_OBJ(X) (make_hashset_object<X>(STR(X)))

template <typename T>
struct HashF_echo
{
  int operator ()(T x) const { return int(x);}
};

template <typename T>
struct RehashF_linear
{
  int operator ()(T x,int h) const { return ++h;}
};

#endif /*UTEST_HASHSET_H*/
