//
// Created by Aeomanate on 07.08.2021.
//

#ifndef LODE_RUNNER_RINGBUFFER_HPP
#define LODE_RUNNER_RINGBUFFER_HPP


#include <vector>

template <class T>
class RingBuffer {
  public:
    explicit RingBuffer(size_t count_nodes = 0): data(count_nodes) { }
    explicit RingBuffer(std::initializer_list<T> list): data(list) { }
    RingBuffer& operator=(std::initializer_list<T> list) {
        data = list;
        return *this;
    }
    
    
    void Resize(size_t count_nodes) {
        data.resize(count_nodes);
    }
    
    T const& PeekNext() const { return data[NextIndex()]; }
    T const& PeekPrev() const { return data[PrevIndex()]; }
    void SetNext(T const& next) {
        data[NextIndex()] = next;
    }
    
    operator T&() {
        return data[cur_pos];
    }
    operator T const&() const {
        return *this;
    }
    T& Next() { return data[cur_pos = NextIndex()]; }
    T& Prev() { return data[cur_pos = PrevIndex()]; }
    T CurAndNext() {
        T t = *this;
        Next();
        return t;
    }
    
    size_t CurIndex() { return cur_pos; }
    
    [[nodiscard]] size_t size() const { return data.size(); }
    [[nodiscard]] bool empty() const { return size() == 0; }
    [[nodiscard]] bool IsBegin() const { return cur_pos == 0; }
    [[nodiscard]] bool IsEnd() const { return NextIndex() == 0; }
    
  private:
    [[nodiscard]] size_t NextIndex() const { return (cur_pos + 1) % data.size(); }
    [[nodiscard]] size_t PrevIndex() const { return cur_pos ? cur_pos - 1 : data.size() - 1; }
    
  private:
    std::vector<T> data;
    size_t cur_pos = 0;
};


#endif // LODE_RUNNER_RINGBUFFER_HPP
