#ifndef UTEST_TREESET_H
#define UTEST_TREESET_H

#include <gtest/gtest.h>

struct TreesetObjectT
{
  virtual bool contains(int x) =0;
  virtual void insert(int x) =0;
  virtual void remove(int x) =0;
  virtual TreesetObjectT* clone() const = 0;
  virtual ~TreesetObjectT(){};
public:
  TreesetObjectT(std::string name): name(name){}
  std::string toString() const { return name; }
private:
  std::string name;
};

template<typename TestT>
struct TreesetObjectImpl : public TreesetObjectT
{
  using TreesetObjectT::TreesetObjectT;
  bool contains(int x) override { return test_obj.contains(x); }
  void insert(int x) override { return test_obj.insert(x); }
  void remove(int x) override { return test_obj.remove(x); }
  TreesetObjectImpl<TestT>* clone() const override { return new TreesetObjectImpl<TestT>(*this); }
private:
  TreesetObjectImpl(const TreesetObjectImpl<TestT>& arg):TreesetObjectT(arg),test_obj(arg.test_obj){}
  TestT test_obj {};
};

template <>
class testing::internal::UniversalTersePrinter<const TreesetObjectT*> {
public:
  static void Print(const TreesetObjectT* obj, ::std::ostream* os) {
    *os << obj->toString();
  }
};

template <>
class testing::internal::UniversalTersePrinter<const TreesetObjectT> {
public:
  static void Print(const TreesetObjectT& obj, ::std::ostream* os) {
    *os << obj.toString();
  }
};

template<typename TestT>
TreesetObjectT* make_treeset_object(std::string name){ return new TreesetObjectImpl<TestT>(name); }

#define NEW_TEST_OBJ(X) (make_treeset_object<X>(STR(X)))

#endif /*UTEST_TREESET_H*/
