#ifndef UTEST_LIST_H
#define UTEST_LIST_H

#include <gtest/gtest.h>

struct ListObjectT
{
  virtual bool contains(int x) =0;
  virtual void insert(int x) =0;
  virtual void remove(int x) =0;
  virtual ListObjectT* clone() const = 0;
public:
  ListObjectT(std::string name): name(name){}  
  std::string toString() const { return name; }
private:
  std::string name;
};

template<typename TestT>
struct ListObjectImpl : public ListObjectT
{
  using ListObjectT::ListObjectT;
  bool contains(int x) override { return test_obj.contains(x); }
  void insert(int x) override { return test_obj.insert(x); }
  void remove(int x) override { return test_obj.remove(x); }
  ListObjectImpl<TestT>* clone() const override { return new ListObjectImpl<TestT>(*this); }
private:
  ListObjectImpl(const ListObjectImpl<TestT>& arg):ListObjectT(arg),test_obj(arg.test_obj){}
  TestT test_obj {};
};

template <>
class testing::internal::UniversalTersePrinter<const ListObjectT*> {
public:
  static void Print(const ListObjectT* obj, ::std::ostream* os) {
    *os << obj->toString();
  }
};

template <>
class testing::internal::UniversalTersePrinter<const ListObjectT> {
public:
  static void Print(const ListObjectT& obj, ::std::ostream* os) {
    *os << obj.toString();
  }
};

template<typename TestT>
ListObjectT* make_list_object(std::string name){ return new ListObjectImpl<TestT>(name); }

#define NEW_TEST_OBJ(X) (make_list_object<X>(STR(X)))

#endif /*UTEST_LIST_H*/
