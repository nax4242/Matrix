#include "pch.h"
#include "parameters.h"
#include "memdata.h"

#ifdef MEMDATA_TESTS

TEST(FunctionsForMemData, calculate_capacity_test) {
    EXPECT_EQ(calculate_capacity(67), 75);
}

TEST(ClassMemData, can_create_with_default_constructor) {
    MemData<double> m1;

    EXPECT_EQ(m1.size(), 0);
    EXPECT_EQ(m1.capacity(), calculate_capacity(0));
}

TEST(ClassMemData, can_create_with_constructor_by_size) {
    size_t size = 534;
    MemData<double> m1(size);

    EXPECT_EQ(m1.size(), 0);
    EXPECT_EQ(m1.capacity(), calculate_capacity(size));
}

TEST(ClassMemData, can_create_with_constructor_by_initializer_list) {
    std::initializer_list<double> data = { 67, 2, 42, 4, 52 };
    MemData<double> m1(data);

    EXPECT_EQ(m1.size(), 5);
    EXPECT_EQ(m1.capacity(), 15);

    for (size_t i = 0; i < m1.size(); i++) {
        EXPECT_EQ(*(data.begin() + i), m1.data()[i]);
    }
}

TEST(ClassMemData, can_create_with_init_constructor) {
    size_t size = 5;

    double* data = new double[size];
    for (size_t i = 0; i < size; i++) {
        data[i] = 5 * i;
    }

    MemData<double> m1(data, size);

    EXPECT_EQ(m1.size(), 5);
    EXPECT_EQ(m1.capacity(), 15);

    for (size_t i = 0; i < m1.size(); i++) {
        EXPECT_EQ(data[i], m1.data()[i]);
    }

    delete[]data;
}

TEST(ClassMemData, can_create_with_copy_constructor) {
    MemData<double> m2({ 67, 2, 42, 4, 52 });
    MemData<double> m1(m2);

    EXPECT_EQ(m1.size(), 5);
    EXPECT_EQ(m1.capacity(), 15);

    for (size_t i = 0; i < m1.size(); i++) {
        EXPECT_EQ(m2.data()[i], m1.data()[i]);
    }
}

TEST(ClassMemData, can_create_with_move_constructor) {
    MemData<double> m2({ 67, 2, 42, 4, 52 });
    const double* expected_data = m2.data();
    MemData<double> m1 = std::move(m2);

    EXPECT_EQ(m1.size(), 5);
    EXPECT_EQ(m1.capacity(), 15);

    for (size_t i = 0; i < m1.size(); i++) {
        EXPECT_EQ(expected_data[i], m1.data()[i]);
    }

    EXPECT_EQ(m2.data(), nullptr);
}

TEST(ClassMemData, can_is_empty) {
    MemData<double> m1;
    MemData<double> m2({ 1,2,3 });

    EXPECT_TRUE(m1.is_empty());
    EXPECT_FALSE(m2.is_empty());
}

TEST(ClassMemData, can_is_full) {
    MemData<double> m1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
    MemData<double> m2({ 1,2,3 });

    EXPECT_TRUE(m1.is_full());
    EXPECT_FALSE(m2.is_empty());
}

TEST(ClassMemData, can_set_memory_for_empty) {
    MemData<double> m1;
    EXPECT_NO_THROW(m1.set_memory(20));

    EXPECT_EQ(m1.size(), 0);
    EXPECT_EQ(m1.capacity(), 30);
    EXPECT_NE(m1.data(), nullptr);
}

TEST(ClassMemData, can_set_memory_for_not_empty) {
    MemData<double> m1({ 1,2,3 });
    EXPECT_NO_THROW(m1.set_memory(31));

    EXPECT_EQ(m1.size(), 0);
    EXPECT_EQ(m1.capacity(), 45);
    EXPECT_NE(m1.data(), nullptr);
}

TEST(ClassMemData, can_set_memory_without_reallocation) {
    MemData<double> m1({ 1,2,3 });
    const double* prev_ptr = m1.data();
    EXPECT_NO_THROW(m1.set_memory(13));

    EXPECT_EQ(m1.size(), 0);
    EXPECT_EQ(m1.capacity(), 15);
    EXPECT_EQ(m1.data(), prev_ptr);
}

TEST(ClassMemData, can_reset_memory_for_empty) {
    MemData<double> m1;
    m1.reset_memory(35);

    EXPECT_EQ(m1.size(), 0);
    EXPECT_EQ(m1.capacity(), calculate_capacity(35));
}

TEST(ClassMemData, can_reset_memory_for_not_empty_increase) {
    MemData<double> m1({ 0,1,2,3,4,5,6,7,8,9 });
    m1.reset_memory(35);

    EXPECT_EQ(m1.size(), 10);
    EXPECT_EQ(m1.capacity(), calculate_capacity(35));

    for (int i = 0; i < m1.size(); i++) {
        EXPECT_EQ(m1.data()[i], i);
    }
}

TEST(ClassMemData, can_reset_memory_for_not_empty_decrease) {
    MemData<double> m1({ 0,1,2,3,4,5,6,7,8,9 });
    m1.reset_memory(3);

    EXPECT_EQ(m1.size(), 10);
    EXPECT_EQ(m1.capacity(), calculate_capacity(3));

    for (int i = 0; i < m1.size(); i++) {
        EXPECT_EQ(m1.data()[i], i);
    }
}

TEST(ClassMemData, can_reset_memory_without_reallocation) {
    MemData<double> m1({ 0,1,2,3,4,5,6,7,8,9 });
    m1.reset_memory(3);


}

TEST(ClassMemData, can_reset_memory_with_shift) {
    MemData<double> m1({ 1, 2, 3, 4, 5 });
    double* shift_data = new double[15];
    size_t start_indx = 13;
    size_t indx = start_indx;

    for (int i = 0; i < m1.size(); i++) {
        shift_data[indx++] = m1.data()[i];
        if (indx >= m1.capacity()) indx = 0;
    }

    MemData<double> m2(shift_data, 5);
    m2.reset_memory(89, 13);

    EXPECT_EQ(m2.size(), 5);
    EXPECT_EQ(m2.capacity(), 90);

    for (int i = 0; i < m2.size(); i++) {
        EXPECT_EQ(m2.data()[i], shift_data[start_indx++]);
        if (start_indx >= m1.capacity()) start_indx = 0;
    }

    delete[] shift_data;
}

TEST(ClassMemData, can_clear_memory_for_empty) {
    MemData<double> m1;
    m1.clear_memory();

    EXPECT_EQ(m1.size(), 0);
    EXPECT_EQ(m1.capacity(), MEM_STEP);
}

TEST(ClassMemData, can_clear_memory_for_not_empty) {
    MemData<double> m1({ 1,2,3 });
    m1.clear_memory();

    EXPECT_EQ(m1.size(), 0);
    EXPECT_EQ(m1.capacity(), MEM_STEP);
}

TEST(ClassMemData, can_assigment) {
    MemData<double> m1({ 1,2,3 });
    MemData<double> m2 = m1;

    EXPECT_EQ(m2.size(), m1.size());
    EXPECT_EQ(m2.capacity(), m1.capacity());

    for (int i = 0; i < m1.size(); i++) {
        EXPECT_EQ(m1.data()[i], m2.data()[i]);
    }
}

TEST(ClassMemData, can_move_assigment) {
    MemData<double> m1({ 1,2,3 });
    MemData<double> m2 = std::move(m1);

    EXPECT_EQ(m2.size(), 3);
    EXPECT_EQ(m2.capacity(), 15);
    EXPECT_EQ(m2.data()[0], 1);
    EXPECT_EQ(m2.data()[1], 2);
    EXPECT_EQ(m2.data()[2], 3);
    EXPECT_EQ(m1.data(), nullptr);
}

#endif