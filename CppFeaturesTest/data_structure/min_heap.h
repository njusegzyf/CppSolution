#pragma once

#include <algorithm>
#include <functional>
#include <gsl/span>

namespace zyf {

  constexpr size_t kDefaultMaxHeapSize = 48;

  template<typename E, typename K>
  using KeyExtractor = std::function<K(const E&)>;

  template<typename E, typename K>
  class MinHeap final {
  public:

    MinHeap(KeyExtractor<E, K> keyExtractor, size_t maxHeapSize, gsl::span<E> initElements);

    MinHeap(KeyExtractor<E, K> keyExtractor, size_t maxHeapSize = kDefaultMaxHeapSize)
      : keyExtractor_(keyExtractor), heap_(gsl::make_span<E>(new E[maxHeapSize], maxHeapSize)), curSize_(0) {
    }

    ~MinHeap() { delete[] heap_.data(); }

    void siftDown(size_t start, size_t m);
    void siftUp(size_t start);
    bool Insert(const E& x);
    bool Insert(E&& x);
    bool RemoveMin(E& x);

    size_t MaxSize() { return heap_.length(); }
    bool Clear() { curSize_ = 0; }
    bool IsEmpty() const { return curSize_ == 0; }
    bool IsFull() const { return curSize_ == MaxSize(); }

  private:
    gsl::span<E> heap_;
    KeyExtractor<E, K> keyExtractor_;
    size_t curSize_;
  };

  template<typename E, typename K>
  MinHeap<E, K>::MinHeap(KeyExtractor<E, K> keyExtractor, size_t maxHeapSize, gsl::span<E> initElements)
    : keyExtractor_(keyExtractor), curSize_(initElements.length) {

    size_t acutalMaxHeapSize = maxHeapSize >= initElements.length ? maxHeapSize : initElements.length;
    heap_ = gsl::make_span<E>(new E[acutalMaxHeapSize], acutalMaxHeapSize);
    // copy init elements to heap
    std::copy(initElements.cbegin(), initElements.cend(), heap_.begin());
    // fix heap
    int curPos = (curSize_ / 2) - 1;
    while (curPos >= 0) {
      siftDown(curPos, curSize_ - 1);
      curPos--;
    }
  }


  // @see http://flforever1213.iteye.com/blog/945971
  template<typename E, typename K>
  void MinHeap<E, K>::siftDown(size_t start, size_t m) {
    size_t i = start, j = 2 * i + 1;

    while (j <= m) {
      if (j < m && keyExtractor_(heap_[j]) > keyExtractor_(heap_[j + 1]))
        j++;
      if (keyExtractor_(heap_[i]) < keyExtractor_(heap_[j])) {
        break;
      } else {
        std::swap(heap_[i], heap_[j]);
        i = j;
        j = 2 * j + 1;
      }
    }
  }

  template<typename E, typename K>
  void MinHeap<E, K>::siftUp(size_t start) {
    size_t j = start, i = (j - 1) / 2;

    while (j > 0) {
      if (keyExtractor_(heap_[i]) <= keyExtractor_(heap_[j])) {
        break;
      } else {
        std::swap(heap_[j], heap_[i]);
        j = i;
        i = (i - 1) / 2;
      }
    }
  }

  template<typename E, typename K>
  bool MinHeap<E, K>::Insert(const E& element) {
    if (curSize_ == MaxSize()) { return false; }

    // copy the element
    heap_[curSize_] = element;
    ++curSize_;
    siftUp(curSize_ - 1);
    return true;
  }

  template<typename E, typename K>
  bool MinHeap<E, K>::Insert(E&& element) {
    if (curSize_ == MaxSize()) { return false; }

    // move the element
    heap_[curSize_] = std::move(element);
    ++curSize_;
    siftUp(curSize_ - 1);
    return true;
  }

  template<typename E, typename K>
  bool MinHeap<E, K>::RemoveMin(E& x) {
    if (curSize_ == 0) { return false; }

    // move first element
    x = std::move(heap_[0]);
    --curSize_;

    if (curSize_ != 0) {
      // move the last element to head
      heap_[0] = std::move(heap_[curSize_]);
      
      // fix heap
      siftDown(0, curSize_ - 1);
    }

    return true;
  }

}
