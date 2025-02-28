#ifndef __SGI_STL_INTERNAL_ALGOBASE_H
#define __SGI_STL_INTERNAL_ALGOBASE_H

#ifndef __STL_CONFIG_H
#include <stl_config.h>
#endif
#ifndef __SGI_STL_INTERNAL_RELOPS
#include <stl_relops.h>//这个头文件是提供操作符重载
#endif
#ifndef __SGI_STL_INTERNAL_PAIR_H
#include <stl_pair.h>
#endif
#ifndef __TYPE_TRAITS_H
#include <type_traits.h>//这个文件提供萃取技术
#endif

#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stddef.h>
#include <new.h>

#ifdef __STL_USE_NEW_IOSTREAMS 
#include <iosfwd>
#else /* __STL_USE_NEW_IOSTREAMS */
#include <iostream.h>
#endif /* __STL_USE_NEW_IOSTREAMS */

#ifndef __SGI_STL_INTERNAL_ITERATOR_H
#include <stl_iterator_base.h>
#include <stl_iterator.h>
#endif

// We pick up concept_checks.h from stl_iterator_base.h.

__STL_BEGIN_NAMESPACE

// swap and iter_swap
//交换两个迭代器a和b所指的内容
/*对外接口：
	template <class ForwardIterator1, class ForwardIterator2>
	void iter_swap (ForwardIterator1 a, ForwardIterator2 b);
*/
template <class _ForwardIter1, class _ForwardIter2, class _Tp>
inline void __iter_swap(_ForwardIter1 __a, _ForwardIter2 __b, _Tp*) {
  _Tp __tmp = *__a;
  *__a = *__b;
  *__b = __tmp;
}

template <class _ForwardIter1, class _ForwardIter2>
inline void iter_swap(_ForwardIter1 __a, _ForwardIter2 __b) {
  __STL_REQUIRES(_ForwardIter1, _Mutable_ForwardIterator);
  __STL_REQUIRES(_ForwardIter2, _Mutable_ForwardIterator);
  __STL_CONVERTIBLE(typename iterator_traits<_ForwardIter1>::value_type,
                    typename iterator_traits<_ForwardIter2>::value_type);
  __STL_CONVERTIBLE(typename iterator_traits<_ForwardIter2>::value_type,
                    typename iterator_traits<_ForwardIter1>::value_type);
  //调用上面的简单交换函数，萃取出a的型别
  __iter_swap(__a, __b, __VALUE_TYPE(__a));
}

//交换a和b的值
//这里采用引用传参
template <class _Tp>
inline void swap(_Tp& __a, _Tp& __b) {
  __STL_REQUIRES(_Tp, _Assignable);
  _Tp __tmp = __a;
  __a = __b;
  __b = __tmp;
}

//--------------------------------------------------
// min and max

/*
返回最小值：Returns the smallest of a and b. If both are equivalent, a is returned.
default (1)	：默认是采用operator<进行比较
	template <class T> const T& min (const T& a, const T& b);
custom (2)	：用户自己提供的comp
	template <class T, class Compare>
	const T& min (const T& a, const T& b, Compare comp);
*/
/*
返回最大值：Returns the largest of a and b. If both are equivalent, a is returned.
default (1)	默认是采用operator<进行比较
	template <class T> const T& max (const T& a, const T& b);
custom (2)	用户自己提供的comp
	template <class T, class Compare>
	const T& max (const T& a, const T& b, Compare comp);
*/
#if !defined(__BORLANDC__) || __BORLANDC__ >= 0x540 /* C++ Builder 4.0 */

#undef min
#undef max

template <class _Tp>
inline const _Tp& min(const _Tp& __a, const _Tp& __b) {
  __STL_REQUIRES(_Tp, _LessThanComparable);
  return __b < __a ? __b : __a;
}

template <class _Tp>
inline const _Tp& max(const _Tp& __a, const _Tp& __b) {
  __STL_REQUIRES(_Tp, _LessThanComparable);
  return  __a < __b ? __b : __a;
}

#endif /* __BORLANDC__ */

template <class _Tp, class _Compare>
inline const _Tp& min(const _Tp& __a, const _Tp& __b, _Compare __comp) {
  return __comp(__b, __a) ? __b : __a;
}

template <class _Tp, class _Compare>
inline const _Tp& max(const _Tp& __a, const _Tp& __b, _Compare __comp) {
  return __comp(__a, __b) ? __b : __a;
}

//--------------------------------------------------
// copy

// All of these auxiliary functions serve two purposes.  (1) Replace
// calls to copy with memmove whenever possible.  (Memmove, not memcpy,
// because the input and output ranges are permitted to overlap.)
// (2) If we're using random access iterators, then write the loop as
// a for loop with an explicit count.

//若迭代器类型为输入迭代器，则调用此函数
template <class _InputIter, class _OutputIter, class _Distance>
inline _OutputIter __copy(_InputIter __first, _InputIter __last,
                          _OutputIter __result,
                          input_iterator_tag, _Distance*)
{
  for ( ; __first != __last; ++__result, ++__first)//只能一个一个的遍历输入区间
    *__result = *__first;//一个一个的赋值operator=
  return __result;
}
//若迭代器的类型为随机访问迭代器，则调用此函数
template <class _RandomAccessIter, class _OutputIter, class _Distance>
inline _OutputIter
__copy(_RandomAccessIter __first, _RandomAccessIter __last,
       _OutputIter __result, random_access_iterator_tag, _Distance*)
{
  for (_Distance __n = __last - __first; __n > 0; --__n) {//遍历输入区间
    *__result = *__first;//对应赋值operator=
    ++__first;
    ++__result;
  }
  return __result;
}

//直接调用memmove复制，不需要其他操作
template <class _Tp>
inline _Tp*
__copy_trivial(const _Tp* __first, const _Tp* __last, _Tp* __result) {
//memmove()是移动复制，注意：source和destination的内存空间可以重叠
/*
原型：void * memmove ( void * destination, const void * source, size_t num );
功能：
Copies the values of num bytes from the location pointed by source to the memory block pointed by destination. 
Copying takes place as if an intermediate buffer were used, allowing the destination and source to overlap.
注意：memmove有一个功能就是首先会把输入内容复制下来，所以允许输入区间与输出区间起始位置重叠
举例：example
	#include <stdio.h>
	#include <string.h>

	int main ()
	{
	  char str[] = "memmove can be very useful......";
	  //允许输出区间起始位置与输入区间重叠
	  //这是memmove的功能
	  memmove (str+20,str+15,11);
	  puts (str);
	  return 0;
	}
	Output：
	memmove can be very very useful.
*/
  memmove(__result, __first, sizeof(_Tp) * (__last - __first));
  return __result + (__last - __first);
}

#if defined(__STL_FUNCTION_TMPL_PARTIAL_ORDER)
//若不提供赋值操作assignment_operator，则调用此函数
template <class _InputIter, class _OutputIter>
inline _OutputIter __copy_aux2(_InputIter __first, _InputIter __last,
                               _OutputIter __result, __false_type) {
//首先萃取出迭代器的类型
  return __copy(__first, __last, __result,
                __ITERATOR_CATEGORY(__first),
                __DISTANCE_TYPE(__first));
}
//若提供赋值操作assignment_operator，则调用此函数
template <class _InputIter, class _OutputIter>
inline _OutputIter __copy_aux2(_InputIter __first, _InputIter __last,
                               _OutputIter __result, __true_type) {
	//首先萃取出迭代器的类型
  return __copy(__first, __last, __result,
                __ITERATOR_CATEGORY(__first),
                __DISTANCE_TYPE(__first));
}
#ifndef __USLC__

//偏特化，参数为T*
template <class _Tp>
inline _Tp* __copy_aux2(_Tp* __first, _Tp* __last, _Tp* __result,
                        __true_type) {
  return __copy_trivial(__first, __last, __result);
}

#endif /* __USLC__ */
//偏特化，参数为const T*
//若提供赋值操作assignment_operator，则调用此函数
template <class _Tp>
inline _Tp* __copy_aux2(const _Tp* __first, const _Tp* __last, _Tp* __result,
                        __true_type) {
  return __copy_trivial(__first, __last, __result);//转而调用该函数
}

//调用该函数
template <class _InputIter, class _OutputIter, class _Tp>
inline _OutputIter __copy_aux(_InputIter __first, _InputIter __last,
                              _OutputIter __result, _Tp*) {
  typedef typename __type_traits<_Tp>::has_trivial_assignment_operator
          _Trivial;
  //首先判断是否提供赋值操作assignment_operator
  return __copy_aux2(__first, __last, __result, _Trivial());
}

/*
复制函数：
	template <class InputIterator, class OutputIterator>
	OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result);
功能：Copies the elements in the range [first,last) into the range beginning at result.
将输入区间[first,last)的内容复制到[result,result+(last-first))内

注意：result不能位于[first,last)内部，即输出端的起始位置不能位于输入区间内部；
但是允许输出区间的尾部与输入区间重叠，这与copy_backward相反

若两个区间不重叠则copy()和copy_backward()都可以使用
*/

//完全泛化版，对外接口
template <class _InputIter, class _OutputIter>
inline _OutputIter copy(_InputIter __first, _InputIter __last,
                        _OutputIter __result) {
  __STL_REQUIRES(_InputIter, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  //首先萃取出first的类型，然后针对特定类型调用对应的函数__copy_aux()
  return __copy_aux(__first, __last, __result, __VALUE_TYPE(__first));
}


// Hack for compilers that don't have partial ordering of function templates
// but do have partial specialization of class templates.
#elif defined(__STL_CLASS_PARTIAL_SPECIALIZATION)

//完全泛化版本
template <class _InputIter, class _OutputIter, class _BoolType>
struct __copy_dispatch {
  static _OutputIter copy(_InputIter __first, _InputIter __last,
                          _OutputIter __result) {
    typedef typename iterator_traits<_InputIter>::iterator_category _Category;
    typedef typename iterator_traits<_InputIter>::difference_type _Distance;
    return __copy(__first, __last, __result, _Category(), (_Distance*) 0);
  }
};

//偏特化1，两个参数都是T*
template <class _Tp>
struct __copy_dispatch<_Tp*, _Tp*, __true_type>
{
  static _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result) {
    return __copy_trivial(__first, __last, __result);
  }
};

//偏特化2，第一个参数是const T*，第二个参数是T*
template <class _Tp>
struct __copy_dispatch<const _Tp*, _Tp*, __true_type>
{
  static _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result) {
    return __copy_trivial(__first, __last, __result);
  }
};

//对外接口，完全泛化
template <class _InputIter, class _OutputIter>
inline _OutputIter copy(_InputIter __first, _InputIter __last,
                        _OutputIter __result) {
  __STL_REQUIRES(_InputIter, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  typedef typename iterator_traits<_InputIter>::value_type _Tp;
  typedef typename __type_traits<_Tp>::has_trivial_assignment_operator
          _Trivial;
  return __copy_dispatch<_InputIter, _OutputIter, _Trivial>
    ::copy(__first, __last, __result);
}

// Fallback for compilers with neither partial ordering nor partial
// specialization.  Define the faster version for the basic builtin
// types.
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class _InputIter, class _OutputIter>
inline _OutputIter copy(_InputIter __first, _InputIter __last,
                        _OutputIter __result)
{
  return __copy(__first, __last, __result,
                __ITERATOR_CATEGORY(__first),
                __DISTANCE_TYPE(__first));
}

#define __SGI_STL_DECLARE_COPY_TRIVIAL(_Tp)                                \
  inline _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result) { \
    memmove(__result, __first, sizeof(_Tp) * (__last - __first));          \
    return __result + (__last - __first);                                  \
  }

__SGI_STL_DECLARE_COPY_TRIVIAL(char)
__SGI_STL_DECLARE_COPY_TRIVIAL(signed char)
__SGI_STL_DECLARE_COPY_TRIVIAL(unsigned char)
__SGI_STL_DECLARE_COPY_TRIVIAL(short)
__SGI_STL_DECLARE_COPY_TRIVIAL(unsigned short)
__SGI_STL_DECLARE_COPY_TRIVIAL(int)
__SGI_STL_DECLARE_COPY_TRIVIAL(unsigned int)
__SGI_STL_DECLARE_COPY_TRIVIAL(long)
__SGI_STL_DECLARE_COPY_TRIVIAL(unsigned long)
#ifdef __STL_HAS_WCHAR_T
__SGI_STL_DECLARE_COPY_TRIVIAL(wchar_t)
#endif
#ifdef _STL_LONG_LONG
__SGI_STL_DECLARE_COPY_TRIVIAL(long long)
__SGI_STL_DECLARE_COPY_TRIVIAL(unsigned long long)
#endif 
__SGI_STL_DECLARE_COPY_TRIVIAL(float)
__SGI_STL_DECLARE_COPY_TRIVIAL(double)
__SGI_STL_DECLARE_COPY_TRIVIAL(long double)

#undef __SGI_STL_DECLARE_COPY_TRIVIAL
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

//--------------------------------------------------
// copy_backward
/*原型
	template <class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator2 copy_backward (BidirectionalIterator1 first,
                                        BidirectionalIterator1 last,
                                        BidirectionalIterator2 result);
*/

//迭代器类型是双向迭代器的调用
template <class _BidirectionalIter1, class _BidirectionalIter2, 
          class _Distance>
inline _BidirectionalIter2 __copy_backward(_BidirectionalIter1 __first, 
                                           _BidirectionalIter1 __last, 
                                           _BidirectionalIter2 __result,
                                           bidirectional_iterator_tag,
                                           _Distance*)
{
  while (__first != __last)//遍历输入区间
    *--__result = *--__last;//逆向赋值operator=
  return __result;
}
//迭代器类型是随机访问迭代器的调用
template <class _RandomAccessIter, class _BidirectionalIter, class _Distance>
inline _BidirectionalIter __copy_backward(_RandomAccessIter __first, 
                                          _RandomAccessIter __last, 
                                          _BidirectionalIter __result,
                                          random_access_iterator_tag,
                                          _Distance*)
{
  for (_Distance __n = __last - __first; __n > 0; --__n)//遍历输入区间
    *--__result = *--__last;//逆向赋值operator=
  return __result;
}

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION 

// This dispatch class is a workaround for compilers that do not 
// have partial ordering of function templates.  All we're doing is
// creating a specialization so that we can turn a call to copy_backward
// into a memmove whenever possible.
//完全泛化版
template <class _BidirectionalIter1, class _BidirectionalIter2,
          class _BoolType>
struct __copy_backward_dispatch
{
  typedef typename iterator_traits<_BidirectionalIter1>::iterator_category 
          _Cat;
  typedef typename iterator_traits<_BidirectionalIter1>::difference_type
          _Distance;

  static _BidirectionalIter2 copy(_BidirectionalIter1 __first, 
                                  _BidirectionalIter1 __last, 
                                  _BidirectionalIter2 __result) {
    return __copy_backward(__first, __last, __result, _Cat(), (_Distance*) 0);
  }
};

//偏特化，参数为原生指针T*
template <class _Tp>
struct __copy_backward_dispatch<_Tp*, _Tp*, __true_type>
{
  static _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result) {
    const ptrdiff_t _Num = __last - __first;
    memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
    return __result - _Num;
  }
};

//偏特化，第一个参数为const T*，第二个参数为T*
template <class _Tp>
struct __copy_backward_dispatch<const _Tp*, _Tp*, __true_type>
{
  static _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result) {
    return  __copy_backward_dispatch<_Tp*, _Tp*, __true_type>
      ::copy(__first, __last, __result);
  }
};

//对外接口
template <class _BI1, class _BI2>
inline _BI2 copy_backward(_BI1 __first, _BI1 __last, _BI2 __result) {
  __STL_REQUIRES(_BI1, _BidirectionalIterator);
  __STL_REQUIRES(_BI2, _Mutable_BidirectionalIterator);
  __STL_CONVERTIBLE(typename iterator_traits<_BI1>::value_type,
                    typename iterator_traits<_BI2>::value_type);
  typedef typename __type_traits<typename iterator_traits<_BI2>::value_type>
                        ::has_trivial_assignment_operator
          _Trivial;
  return __copy_backward_dispatch<_BI1, _BI2, _Trivial>
              ::copy(__first, __last, __result);
}

#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */

template <class _BI1, class _BI2>
inline _BI2 copy_backward(_BI1 __first, _BI1 __last, _BI2 __result) {
  return __copy_backward(__first, __last, __result,
                         __ITERATOR_CATEGORY(__first),
                         __DISTANCE_TYPE(__first));
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

//--------------------------------------------------
// copy_n (not part of the C++ standard)
/*原型
	template <class InputIterator, class Size, class OutputIterator>
	OutputIterator copy_n (InputIterator first, Size n, OutputIterator result);

例子：
	#include <iostream>     // std::cout
	#include <algorithm>    // std::copy
	#include <vector>       // std::vector

	int main () {
	  int myints[]={10,20,30,40,50,60,70};
	  std::vector<int> myvector;

	  myvector.resize(7);   // allocate space for 7 elements

	  std::copy_n ( myints, 7, myvector.begin() );

	  std::cout << "myvector contains:";
	  for (std::vector<int>::iterator it = myvector.begin(); it!=myvector.end(); ++it)
		std::cout << ' ' << *it;

	  std::cout << '\n';

	  return 0;
	}
	Output：
	myvector contains: 10 20 30 40 50 60 70
*/
//C++11已经把这个列入标准库

//迭代器类型为输入迭代器
//从指定位置开始复制__count个与*first值相等的值
template <class _InputIter, class _Size, class _OutputIter>
pair<_InputIter, _OutputIter> __copy_n(_InputIter __first, _Size __count,
                                       _OutputIter __result,
                                       input_iterator_tag) {
  for ( ; __count > 0; --__count) {//若个数不小于0，则进行操作
    *__result = *__first;//赋值operator=
    ++__first;
    ++__result;
  }
  return pair<_InputIter, _OutputIter>(__first, __result);
}

//迭代器为随机访问迭代器
template <class _RAIter, class _Size, class _OutputIter>
inline pair<_RAIter, _OutputIter>
__copy_n(_RAIter __first, _Size __count,
         _OutputIter __result,
         random_access_iterator_tag) {
  _RAIter __last = __first + __count;
  return pair<_RAIter, _OutputIter>(__last, copy(__first, __last, __result));
}

//萃取迭代器的类型
template <class _InputIter, class _Size, class _OutputIter>
inline pair<_InputIter, _OutputIter>
__copy_n(_InputIter __first, _Size __count, _OutputIter __result) {
  return __copy_n(__first, __count, __result,
                  __ITERATOR_CATEGORY(__first));
}

//对外接口，完全泛化
template <class _InputIter, class _Size, class _OutputIter>
inline pair<_InputIter, _OutputIter>
copy_n(_InputIter __first, _Size __count, _OutputIter __result) {
  __STL_REQUIRES(_InputIter, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  return __copy_n(__first, __count, __result);
}

//--------------------------------------------------
// fill and fill_n

/*
填充值：Assigns val to all the elements in the range [first,last).
	template <class ForwardIterator, class T>
	void fill (ForwardIterator first, ForwardIterator last, const T& val);
*/
//把区间[first,last)的值都填充为value
template <class _ForwardIter, class _Tp>
void fill(_ForwardIter __first, _ForwardIter __last, const _Tp& __value) {
  __STL_REQUIRES(_ForwardIter, _Mutable_ForwardIterator);
  for ( ; __first != __last; ++__first)//遍历区间
    *__first = __value;//当前位置赋予值value
}
/*
在指定位置连续填充n个值：Assigns val to the first n elements of the sequence pointed by first.
	template <class OutputIterator, class Size, class T>
	void fill_n (OutputIterator first, Size n, const T& val);
*/
//从first开始连续填充n个value值
template <class _OutputIter, class _Size, class _Tp>
_OutputIter fill_n(_OutputIter __first, _Size __n, const _Tp& __value) {
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  for ( ; __n > 0; --__n, ++__first)//从first开始遍历n个位置
    *__first = __value;//当前位置赋予值value
  return __first;
}

// Specialization: for one-byte types we can use memset.

inline void fill(unsigned char* __first, unsigned char* __last,
                 const unsigned char& __c) {
  unsigned char __tmp = __c;
  //按字节填充
  //Sets the first num bytes of the block of memory pointed by ptr to the specified value (interpreted as an unsigned char).
  memset(__first, __tmp, __last - __first);
}

inline void fill(signed char* __first, signed char* __last,
                 const signed char& __c) {
  signed char __tmp = __c;
  memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
}

inline void fill(char* __first, char* __last, const char& __c) {
  char __tmp = __c;
  memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Size>
inline unsigned char* fill_n(unsigned char* __first, _Size __n,
                             const unsigned char& __c) {
  fill(__first, __first + __n, __c);
  return __first + __n;
}

template <class _Size>
inline signed char* fill_n(char* __first, _Size __n,
                           const signed char& __c) {
  fill(__first, __first + __n, __c);
  return __first + __n;
}

template <class _Size>
inline char* fill_n(char* __first, _Size __n, const char& __c) {
  fill(__first, __first + __n, __c);
  return __first + __n;
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

//--------------------------------------------------
// equal and mismatch

/*
判断两个区间的第一个不匹配点，返回一个由两个迭代器组成的pair，
其中第一个迭代器指向第一个区间的不匹配点，第二个迭代器指向第二个区间的不匹配点
如果都匹配，返回的是指向两个区间的last迭代器。

quality (1)	：采用默认operator==比较
	template <class InputIterator1, class InputIterator2>
	pair<InputIterator1, InputIterator2>
    mismatch (InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2);
predicate (2)：指定比较规则pred
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	pair<InputIterator1, InputIterator2>
    mismatch (InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, BinaryPredicate pred);
*/
//版本一：采用默认比较规则operator==
template <class _InputIter1, class _InputIter2>
pair<_InputIter1, _InputIter2> mismatch(_InputIter1 __first1,
                                        _InputIter1 __last1,
                                        _InputIter2 __first2) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(typename iterator_traits<_InputIter1>::value_type,
                 _EqualityComparable);
  __STL_REQUIRES(typename iterator_traits<_InputIter2>::value_type,
                 _EqualityComparable);
  //遍历区间，寻找不匹配点
  //注意：第一个区间的元素不能比第二个区间元素多
  while (__first1 != __last1 && *__first1 == *__first2) {
    ++__first1;
    ++__first2;
  }
  return pair<_InputIter1, _InputIter2>(__first1, __first2);
}
//版本二：自定义比较规则
template <class _InputIter1, class _InputIter2, class _BinaryPredicate>
pair<_InputIter1, _InputIter2> mismatch(_InputIter1 __first1,
                                        _InputIter1 __last1,
                                        _InputIter2 __first2,
                                        _BinaryPredicate __binary_pred) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  //遍历区间，寻找不匹配点
  while (__first1 != __last1 && __binary_pred(*__first1, *__first2)) {
    ++__first1;
    ++__first2;
  }
  return pair<_InputIter1, _InputIter2>(__first1, __first2);
}
/*
Compares the elements in the range [first1,last1) with those in the range beginning at first2, 
and returns true if all of the elements in both ranges match.
比较两个序列指定范围大小：如果两个序列在[first,last)区间相等，则返回true
		如果第二个序列的元素比较多，多出来的元素不予考虑;
equality (1):默认采用operator==比较
	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2);
predicate (2):用户可指定比较规则
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, BinaryPredicate pred);
*/
//版本一‘：采用默认比较规则operator==
template <class _InputIter1, class _InputIter2>
inline bool equal(_InputIter1 __first1, _InputIter1 __last1,
                  _InputIter2 __first2) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(typename iterator_traits<_InputIter1>::value_type,
                 _EqualityComparable);
  __STL_REQUIRES(typename iterator_traits<_InputIter2>::value_type,
                 _EqualityComparable);
  //遍历区间
  for ( ; __first1 != __last1; ++__first1, ++__first2)
    if (*__first1 != *__first2)
      return false;//若对应元素不相等，返回FALSE
  return true;//至此全部相等
}
//版本二：采用用户自定义的比较规则
template <class _InputIter1, class _InputIter2, class _BinaryPredicate>
inline bool equal(_InputIter1 __first1, _InputIter1 __last1,
                  _InputIter2 __first2, _BinaryPredicate __binary_pred) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  //遍历区间
  for ( ; __first1 != __last1; ++__first1, ++__first2)
    if (!__binary_pred(*__first1, *__first2))
      return false;//若对应元素不符合规则，返回FALSE
  return true;//至此全部符合
}

//--------------------------------------------------
// lexicographical_compare and lexicographical_compare_3way.
// (the latter is not part of the C++ standard.)

/*功能：Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
default (1)	
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2);
custom (2)	
	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2,
                                Compare comp);
*/
/*
对两个序列[first1,last1)和[first2,last2)进行比较，比较操作针对两个序列对应位置上的元素进行；
并持续到：
（1）某一组对应元素不相等
（2）同时达到last1和last2(即两个序列大小相等)
（3）达到last1或last2(两个序列大小不相等)
*/

//版本一：默认比较操作为less
template <class _InputIter1, class _InputIter2>
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(typename iterator_traits<_InputIter1>::value_type,
                 _LessThanComparable);
  __STL_REQUIRES(typename iterator_traits<_InputIter2>::value_type,
                 _LessThanComparable);
  //以下任何一个序列到达尾端，则结束，否则两序列就相应元素进行比较
  for ( ; __first1 != __last1 && __first2 != __last2
        ; ++__first1, ++__first2) {
    if (*__first1 < *__first2)//若第一序列对应元素小于第二序列对应元素
      return true;//返回TRUE
    if (*__first2 < *__first1)//若第二序列对应元素小于第一序列对应元素
      return false;//返回FALSE
	//若两序列对应元素相等，则继续进入下一组对应元素比较
  }
  //如果第一序列已到达尾端，而第二序列还存在元素，则第一序列小于第二序列
  return __first1 == __last1 && __first2 != __last2;
}

//版本二：用户可自行指定比较规则
template <class _InputIter1, class _InputIter2, class _Compare>
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2,
                             _Compare __comp) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  //以下任何一个序列到达尾端，则结束，否则两序列就相应元素进行比较
  for ( ; __first1 != __last1 && __first2 != __last2
        ; ++__first1, ++__first2) {
    if (__comp(*__first1, *__first2))//若第一序列对应元素符合规则于第二序列对应元素
      return true;//返回TRUE
    if (__comp(*__first2, *__first1))//若第二序列对应元素符合规则于第一序列对应元素
      return false;//返回FALSE
	//若两序列对应元素相等，则继续进入下一组对应元素比较
  }
  //如果第一序列已到达尾端，而第二序列还存在元素，则第一序列符合规则于第二序列
  return __first1 == __last1 && __first2 != __last2;
}

//这是针对const unsigned cahr*的特化版本
inline bool 
lexicographical_compare(const unsigned char* __first1,
                        const unsigned char* __last1,
                        const unsigned char* __first2,
                        const unsigned char* __last2)
{
  const size_t __len1 = __last1 - __first1;//第一序列长度
  const size_t __len2 = __last2 - __first2;//第二序列长度
  //先比较长度相同的一小段
  /*
  memcmp函数的描述：
  原型：int memcmp ( const void * ptr1, const void * ptr2, size_t num );

Compares the first num bytes of the block of memory pointed by ptr1 to the first num bytes pointed by ptr2, 
returning zero if they all match or a value different from zero representing which is greater if they do not.
  */
  const int __result = memcmp(__first1, __first2, min(__len1, __len2));
  //根据返回结果result的值与0比较进行判断
  //result<0：第一序列小于第二序列
  //result>0：第一序列大于第二序列
  //result=0：两个序列相等
  return __result != 0 ? __result < 0 : __len1 < __len2;
}

//针对const char*的特化版本
inline bool lexicographical_compare(const char* __first1, const char* __last1,
                                    const char* __first2, const char* __last2)
{
#if CHAR_MAX == SCHAR_MAX
  return lexicographical_compare((const signed char*) __first1,
                                 (const signed char*) __last1,
                                 (const signed char*) __first2,
                                 (const signed char*) __last2);
#else /* CHAR_MAX == SCHAR_MAX */
  return lexicographical_compare((const unsigned char*) __first1,
                                 (const unsigned char*) __last1,
                                 (const unsigned char*) __first2,
                                 (const unsigned char*) __last2);
#endif /* CHAR_MAX == SCHAR_MAX */
}

//类似于strcmp()的泛化版本
//默认比较操作是less
template <class _InputIter1, class _InputIter2>
int __lexicographical_compare_3way(_InputIter1 __first1, _InputIter1 __last1,
                                   _InputIter2 __first2, _InputIter2 __last2)
{
//以下任何一个序列到达尾端，则结束，否则两序列就相应元素进行比较
  while (__first1 != __last1 && __first2 != __last2) {
    if (*__first1 < *__first2)//若第一个元素小于第二序列对应的元素
      return -1;//则返回负值-1
    if (*__first2 < *__first1)//若第二序列元素小于第一序列对应元素
      return 1;//则返回正值1
	//继续遍历
	//若两序列对应元素相等，则继续进入下一组对应元素比较
    ++__first1;
    ++__first2;	
  }
  //若第二序列已到达尾端
  if (__first2 == __last2) {
	  //若第一序列也同时到达尾端，表示两序列相等，则返回0；
	  //若第一序列没到达尾端，则表示第一序列大于第二序列
	  //则返回正值1
    return !(__first1 == __last1);
  }
  else {//若第一序列已到达尾端，而第二序列还没到达尾端
	  //则返回负值-1
    return -1;
  }
}

//以下是针对const unsigned char*
inline int
__lexicographical_compare_3way(const unsigned char* __first1,
                               const unsigned char* __last1,
                               const unsigned char* __first2,
                               const unsigned char* __last2)
{
  const ptrdiff_t __len1 = __last1 - __first1;
  const ptrdiff_t __len2 = __last2 - __first2;
  const int __result = memcmp(__first1, __first2, min(__len1, __len2));
  return __result != 0 ? __result 
                       : (__len1 == __len2 ? 0 : (__len1 < __len2 ? -1 : 1));
}
//这是const char*特化版
inline int 
__lexicographical_compare_3way(const char* __first1, const char* __last1,
                               const char* __first2, const char* __last2)
{
#if CHAR_MAX == SCHAR_MAX
  return __lexicographical_compare_3way(
                                (const signed char*) __first1,
                                (const signed char*) __last1,
                                (const signed char*) __first2,
                                (const signed char*) __last2);
#else
  return __lexicographical_compare_3way((const unsigned char*) __first1,
                                        (const unsigned char*) __last1,
                                        (const unsigned char*) __first2,
                                        (const unsigned char*) __last2);
#endif
}
//针对上面函数的封装
template <class _InputIter1, class _InputIter2>
int lexicographical_compare_3way(_InputIter1 __first1, _InputIter1 __last1,
                                 _InputIter2 __first2, _InputIter2 __last2)
{
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(typename iterator_traits<_InputIter1>::value_type,
                 _LessThanComparable);
  __STL_REQUIRES(typename iterator_traits<_InputIter2>::value_type,
                 _LessThanComparable);
  return __lexicographical_compare_3way(__first1, __last1, __first2, __last2);
}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_ALGOBASE_H */

// Local Variables:
// mode:C++
// End:
