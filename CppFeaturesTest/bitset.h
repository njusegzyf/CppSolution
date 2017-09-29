#pragma once

#include <cassert>
#include <cstdint>
#include <cmath>
#include <memory>
#include <vector>

namespace zyf {
  namespace data_structure {

    // @see http://en.cppreference.com/w/cpp/utility/bitset

    using VectorUnitType = uint32_t;
    constexpr VectorUnitType kZero = 0;
    constexpr VectorUnitType kOne = 1;
    constexpr int kVectorUnitTypeSize = sizeof(VectorUnitType);
    constexpr int kBitsPerVectorUnit = kVectorUnitTypeSize << 3;
    constexpr int kShift = kVectorUnitTypeSize >> 1 + 3; // std::log2(kBitsPerVectorUnit)
    constexpr int kAddSize = kBitsPerVectorUnit - 1;

    constexpr int kDefaultSetSize = 64;


    class BitSet {
    private:
      size_t set_size_;
      size_t vector_size_;
      std::vector<VectorUnitType> vector_;

      void Swap(BitSet& r);

    public:
      BitSet(size_t init_set_size = kDefaultSetSize);
      BitSet(const BitSet& r);
      // BitSet(BitSet&& r);

      // ~BitSet() {}

      //BitSet& operator=(const BitSet& r);
      //BitSet& operator=(BitSet&& r);
      BitSet& operator=(BitSet r);

      // constexpr bool operator[](size_t pos) const;
      // reference operator[](std::size_t pos);

      // Returns the value of the bit at the position pos
      // Unlike operator[], performs a bounds check and throws std::out_of_range if pos does not correspond to a valid position in the bitset.
      bool Test(size_t pos) const;

      // // Sets all bits to true.
      // bitset<N>& set();

      // Sets the bit at position pos to the value value.
      BitSet& Set(size_t pos, bool value = true);

      bool Add(size_t pos);
      bool Remove(size_t pos);
      
      // Returns a bitset<N> containing the result of binary AND on corresponding pairs of bits of lhs and rhs.
      BitSet operator|(const BitSet& r) const;

      // Returns a bitset<N> containing the result of binary OR on corresponding pairs of bits of lhs and rhs.
      BitSet operator&(const BitSet& r) const;

      // Returns a bitset<N> containing the result of binary XOR on corresponding pairs of bits of lhs and rhs.
      BitSet operator^(const BitSet& r) const;

      BitSet operator-(const BitSet& r) const;

      //BitSet& operator |=(const BitSet& r);
      //BitSet& operator &=(const BitSet& r);
      //BitSet& operator ^=(const BitSet& r);
      //BitSet& operator -=(const BitSet& r);

      bool operator==(const BitSet& r) const;

      //bool isSubset(const BitSet& r);

      void Clear();

      inline bool BitSet::IsPosValid(const size_t pos) const {
        return pos >= 0 && pos < set_size_;
      }

      inline void BitSet::CheckPosValid(const size_t pos) const {
        assert(IsPosValid(pos));
      }

      inline void BitSet::CheckSameSetSize(const BitSet& r) const {
        assert(set_size_ == r.set_size_);
      }
    };
  }
}
