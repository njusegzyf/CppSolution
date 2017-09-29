#pragma once

#include <cassert>
#include <memory>

// @see http://blog.csdn.net/cainv89/article/details/51398148
namespace zyf {

  template <typename T>
  class DualStack final {
  public:

    #pragma region Stack interface

    class IStack {
    public:
      virtual bool Push(const T&) = 0;
      virtual bool Push(T&&) = 0; // for r-values
      virtual bool Pop(T&) = 0;
      virtual void Clear() = 0;
      virtual bool IsFull() const = 0;
      virtual bool IsEmpty() const = 0;
      virtual size_t Size() const = 0;
    };

    #pragma endregion

  private:

    #pragma region Stack implementations

    class StackBase : public IStack {
    protected:
      DualStack& parent_;

    public:
      StackBase(DualStack& parent) : parent_(parent) {}

      bool IsFull() const override final { return parent_.IsFull(); }

      void Clear() override final {
        // Note: we pop all elements so that they are destructed
        while (!IsEmpty()) {
          T temp;
          Pop(temp);
        }
      }
    };

    class Stack0 final : public StackBase {
    public:
      Stack0(DualStack& parent) : StackBase(parent) {}
      bool IsEmpty() const override { return parent_.top0_ == -1; }
      size_t Size() const override { return parent_.top0_ - (-1); }

      bool Push(const T& v) override {
        if (IsFull()) { return false; }
        ++parent_.top0_;
        parent_.content_[parent_.top0_] = v;
        return true;
      }

      bool Push(T&& v) override {
        if (IsFull()) { return false; }
        ++parent_.top0_;
        parent_.content_[parent_.top0_] = v;
        return true;
      }

      bool Pop(T& v) override {
        if (IsEmpty()) { return false; }
        v = std::move(parent_.content_[parent_.top0_]);
        --parent_.top0_;
        return true;
      }
    };

    class Stack1 final : public StackBase {
    public:
      Stack1(DualStack& parent) : StackBase(parent) {}
      bool IsEmpty() const { return parent_.top1_ == parent_.contentSize_; }
      size_t Size() const { return parent_.contentSize_ - parent_.top1_; }

      bool Push(const T& v) override {
        if (IsFull()) { return false; }
        --parent_.top1_;
        parent_.content_[parent_.top1_] = v;
        return true;
      }

      bool Push(T&& v) override {
        if (IsFull()) { return false; }
        --parent_.top1_;
        parent_.content_[parent_.top1_] = v;
        return true;
      }

      bool Pop(T& v) override {
        if (IsEmpty()) { return false; }
        v = std::move(parent_.content_[parent_.top1_]);
        ++parent_.top1_;
        return true;
      }
    };

    friend class StackBase;
    friend class Stack0;
    friend class Stack1;

    #pragma endregion

    const size_t contentSize_;
    const std::unique_ptr<T[]> content_;
    // the two stacks and their top pointers
    Stack0 stack0_;
    size_t top0_;
    Stack1 stack1_;
    size_t top1_;

  public:
    DualStack(const size_t stackSize)
      : contentSize_(stackSize), content_(std::make_unique<T[]>(stackSize)), stack0_(*this), stack1_(*this), top0_(-1), top1_(stackSize) {
      assert(stackSize > 0);
    }

    bool IsFull() const {
      return top0_ + 1 == top1_;
    }

    bool IsEmpty() const {
      return top0_ == -1 && top1_ == contentSize_;
    }

    size_t Size() const {
      return stack0_.Size() + stack1_.Size();
    }

    IStack& getStack0() { return stack0_; }
    IStack& getStack1() { return stack1_; }
  };
}
