#pragma once

#include <memory>

// @see http://blog.csdn.net/dm_vincent/article/details/7655764

template <typename T>
class UnionFindSets {

private:

  struct DataSlot {
    size_t parent_id;
    T data;
  };

  std::unique_ptr<DataSlot[]> data_;
  size_t data_size_;

public:


};
