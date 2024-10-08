#include <iostream>
#include "CircularBuffer.h"
#include "gtest/gtest.h"
using namespace std;

TEST(buffer_test, buffer_create) {
    CircularBuffer first = CircularBuffer();
    int size = first.size();
    ASSERT_EQ(size, 0);
}
TEST(buffer_test, buffer_create_capacity) {
    CircularBuffer first = CircularBuffer(4);
    ASSERT_EQ(first.capacity(), 4);
}
TEST(buffer_test, buffer_err) {
    CircularBuffer first = CircularBuffer(4);
    first.at(-1);
    //ASSERT_EQ(first.capacity(), 4);
}
TEST(buffer_test, buffer_create_from_another) {
    CircularBuffer first = CircularBuffer(4,'a');
    CircularBuffer second = CircularBuffer(first);
    ASSERT_EQ(first.size(), second.size());
    for(int i=0;i<4;i++){
        ASSERT_EQ((int)first[i], (int)second[i]);
    }
}
TEST(buffer_test, buffer_create_by_insertion) {
    CircularBuffer first = CircularBuffer(4,'a');
    for(int i=0;i<4;i++){
        ASSERT_EQ((int)first[i], (int)'a');
    }
}
TEST(buffer_test, buffer_empty) {
    CircularBuffer first = CircularBuffer(4);
    CircularBuffer second = CircularBuffer(3,'q');
    ASSERT_TRUE(first.empty());
    ASSERT_FALSE(second.empty());
}
TEST(buffer_test, buffer_full) {
    CircularBuffer first = CircularBuffer(4);
    CircularBuffer second = CircularBuffer(3,'q');
    ASSERT_FALSE(first.full());
    ASSERT_TRUE(second.full());
}
TEST(buffer_test, buffer_reserve) {
    CircularBuffer first = CircularBuffer(4);
    CircularBuffer second = CircularBuffer(3,'q');
    ASSERT_EQ(first.reserve(),4);
    ASSERT_EQ(second.reserve(),0);
}
TEST(buffer_test, buffer_reszie) {
    CircularBuffer first = CircularBuffer(4);
    first.resize(5);
    ASSERT_EQ(first.capacity(),5);
}
TEST(buffer_test, buffer_linearize_and_islinerize) {
    CircularBuffer first = CircularBuffer(4,'a');
    ASSERT_TRUE(first.is_linearized());
    first.push_front('q');
    first.push_back('r');
    first.push_front('z');
    //razq
    ASSERT_EQ(first[0],'r');
    ASSERT_EQ(first[1],'a');
    ASSERT_EQ(first[2],'z');
    ASSERT_EQ(first[3],'q');
    ASSERT_FALSE(first.is_linearized());
    first.linearize();
    //zqra
    ASSERT_EQ(first[0],'z');
    ASSERT_EQ(first[1],'q');
    ASSERT_EQ(first[2],'r');
    ASSERT_EQ(first[3],'a');
}
TEST(buffer_test, buffer_rotate) {
    CircularBuffer first = CircularBuffer(4);
    first.push_back('a');
    first.push_back('b');
    first.push_back('c');
    first.push_back('d');
    ASSERT_EQ(first[0],'a');
    ASSERT_EQ(first[1],'b');
    ASSERT_EQ(first[2],'c');
    ASSERT_EQ(first[3],'d');
    first.rotate(2);
    ASSERT_EQ(first[0],'c');
    ASSERT_EQ(first[1],'d');
    ASSERT_EQ(first[2],'a');
    ASSERT_EQ(first[3],'b');
}
TEST(buffer_test, buffer_front_back) {
    CircularBuffer first = CircularBuffer(4,'a');
    first.push_front('w');
    first.push_back('t');
    first.push_back('b');
    ASSERT_EQ(first.front(),'w');
    ASSERT_EQ(first.back(),'a');
}
TEST(buffer_test, buffer_swap) {
    CircularBuffer first = CircularBuffer(4,'a');
    CircularBuffer second = CircularBuffer(4,'b');
    for(int i=0;i<4;i++){
        ASSERT_EQ(first[i],'a');
        ASSERT_EQ(second[i],'b');    
    }
    first.swap(second);
    for(int i=0;i<4;i++){
        ASSERT_EQ(first[i],'b');
        ASSERT_EQ(second[i],'a');    
    }
}
TEST(buffer_test, buffer_clear) {
    CircularBuffer first = CircularBuffer(4,'a');
    for(int i=0;i<4;i++){
        ASSERT_EQ(first[i],'a');
    }
    first.clear();
    for(int i=0;i<4;i++){
        ASSERT_EQ(first[i],0);
    }
}
TEST(buffer_test, buffer_erase) {
    CircularBuffer first = CircularBuffer(4,'a');
    for(int i=0;i<4;i++){
        ASSERT_EQ(first[i],'a');
    }
    first.erase(0,2);
    ASSERT_EQ(first[0],0);
    ASSERT_EQ(first[1],0);
    ASSERT_EQ(first[2],'a');
    ASSERT_EQ(first[3],'a');
}
TEST(buffer_test, buffer_insert) {
    CircularBuffer first = CircularBuffer(4,'a'); 
    first.insert(0,'q');
    ASSERT_EQ(first[0],'q');
    ASSERT_EQ(first[1],'a');
    ASSERT_EQ(first[2],'a');
    ASSERT_EQ(first[3],'a');
}
TEST(buffer_test, buffer_popfr) {
    CircularBuffer first = CircularBuffer(4,'a');
    first.push_front('q'); 
    first.pop_front();
    first.pop_front();
    ASSERT_EQ(first[0],0);
    ASSERT_EQ(first[1],'a');
    ASSERT_EQ(first[2],'a');
    ASSERT_EQ(first[3],0);
}
TEST(buffer_test, buffer_popbck) {
    CircularBuffer first = CircularBuffer(4,'a'); 
    first.push_back('b');
    first.pop_back();
    ASSERT_EQ(first[0],0);
    ASSERT_EQ(first[1],'a');
    ASSERT_EQ(first[2],'a');
    ASSERT_EQ(first[3],'a');
}
TEST(buffer_test, buffer_at) {
    CircularBuffer first = CircularBuffer(3,'w');
    ASSERT_EQ(first.at(0),'w');
}