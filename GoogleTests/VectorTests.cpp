#include "pch.h"
#include "parameters.h"
#include "vector.h"
#include <random>

#ifdef VECTOR_TESTS

TEST(ClassVector, can_create_with_default_constructor) {
    Vector<double> v1;

    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), 15);
}

TEST(ClassVector, can_create_with_constructor_by_size) {
    Vector<double> v1(20);

    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), 30);
}

TEST(ClassVector, can_create_with_constructor_by_initializer_list) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9 });

    EXPECT_EQ(v1.size(), 9);
    EXPECT_EQ(v1.capacity(), 15);
}

TEST(ClassVector, can_create_with_init_constructor) {
    double* data = new double[10];
    for (size_t i = 0; i < 10; i++) {
        data[i] = i;
    }

    Vector<double> v1(data, 10);

    EXPECT_EQ(v1.size(), 10);
    EXPECT_EQ(v1.capacity(), 15);

    for (size_t i = 0; i < 10; i++) {
        EXPECT_EQ(v1[i], i);
    }
}

TEST(ClassVector, can_create_with_copy_constructor) {
    Vector<double> v1({ 0,1,2,3,4,5,6,7,8,9 });
    Vector<double> v2(v1);

    EXPECT_EQ(v1.size(), 10);
    EXPECT_EQ(v1.capacity(), 15);

    for (size_t i = 0; i < 10; i++) {
        EXPECT_EQ(v1[i], i);
    }
}

TEST(ClassVector, can_create_with_move_constructor) {
    Vector<double> v1({ 0,1,2,3,4,5,6,7,8,9 });
    Vector<double> v2 = std::move(v1);

    EXPECT_EQ(v2.size(), 10);
    EXPECT_EQ(v2.capacity(), 15);

    for (size_t i = 0; i < 10; i++) {
        EXPECT_EQ(v2[i], i);
    }
}

TEST(ClassVector, can_is_empty) {
    Vector<double> v1;
    Vector<double> v2({ 1,3,4 });

    EXPECT_TRUE(v1.is_empty());
    EXPECT_FALSE(v2.is_empty());
}

TEST(ClassVector, can_is_full) {
    Vector<double> v1;
    Vector<double> v2({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });

    EXPECT_FALSE(v1.is_full());
    EXPECT_TRUE(v2.is_full());
}

TEST(ClassVector, can_get_front) {
    Vector<double> v1({ 1,2,3 });

    EXPECT_EQ(v1.front(), 1);
}

TEST(ClassVector, can_get_back) {
    Vector<double> v1({ 1,2,3 });

    EXPECT_EQ(v1.back(), 3);
}

TEST(ClassVector, can_set_front) {
    Vector<double> v1({ 1,2,3 });
    v1.front() = 5;

    EXPECT_EQ(v1.front(), 5);
}

TEST(ClassVector, can_set_back) {
    Vector<double> v1({ 1,2,3 });
    v1.back() = 5;

    EXPECT_EQ(v1.back(), 5);
}

TEST(ClassVector, throw_when_try_get_front_in_empty_vector) {
    Vector<double> v1;
    EXPECT_ANY_THROW(v1.front());
}

TEST(ClassVector, throw_when_try_get_back_in_empty_vector) {
    Vector<double> v1;
    EXPECT_ANY_THROW(v1.back());
}

TEST(ClassVector, throw_when_try_set_front_in_empty_vector) {
    Vector<double> v1;
    EXPECT_ANY_THROW(v1.front() = 5);
}

TEST(ClassVector, throw_when_try_set_back_in_empty_vector) {
    Vector<double> v1;
    EXPECT_ANY_THROW(v1.back() = 5);
}

TEST(ClassVector, can_output_with_operator_cout) {
    Vector<double> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }", out.str());
}

TEST(ClassVector, can_input_with_operator_cin) {
    Vector<double> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream in("9 1 2 3 4 5 6 7 8 9");
    in >> vec;

    EXPECT_EQ(9, vec.size());
    EXPECT_EQ(15, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_push_front) {
    Vector<double> v1({ 1,2,3 });
    v1.push_front(10);

    EXPECT_EQ(v1.size(), 4);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1[0], 10);
}

TEST(ClassVector, can_push_front_in_empty_vector) {
    Vector<double> v1;
    v1.push_front(10);

    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.front(), 10);
}

TEST(ClassVector, can_push_front_with_reallocation) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });

    v1.push_front(10);
    EXPECT_EQ(v1.size(), 16);
    EXPECT_EQ(v1.capacity(), 30);
    EXPECT_EQ(v1.front(), 10);
}

TEST(ClassVector, can_push_back) {
    Vector<double> v1({ 1,2,3 });
    v1.push_back(10);

    EXPECT_EQ(v1.size(), 4);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1[3], 10);
}

TEST(ClassVector, can_push_back_in_empty_vector) {
    Vector<double> v1;
    v1.push_back(10);

    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.back(), 10);
}

TEST(ClassVector, can_push_back_with_reallocation) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });

    v1.push_back(10);
    EXPECT_EQ(v1.size(), 16);
    EXPECT_EQ(v1.capacity(), 30);
    EXPECT_EQ(v1.back(), 10);
}

TEST(ClassVector, can_insert) {
    Vector<double> v1({ 1,2,3 });
    v1.insert(10, 1);

    EXPECT_EQ(v1.size(), 4);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1[1], 10);
}

TEST(ClassVector, can_insert_with_reallocation) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });

    v1.insert(10, 3);
    EXPECT_EQ(v1.size(), 16);
    EXPECT_EQ(v1.capacity(), 30);
    EXPECT_EQ(v1[3], 10);
}

TEST(ClassVector, can_insert_to_front) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });

    v1.insert(10, 0);

    EXPECT_EQ(v1.size(), 16);
    EXPECT_EQ(v1.capacity(), 30);
    EXPECT_EQ(v1.front(), 10);
}

TEST(ClassVector, throw_when_try_insert_with_wrong_position) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });

    EXPECT_ANY_THROW(v1.insert(10, 19302));
}

TEST(ClassVector, can_pop_front) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });

    v1.pop_front();

    EXPECT_EQ(v1.size(), 14);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.front(), 2);
}

TEST(ClassVector, can_pop_front_with_reallocation) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });

    v1.pop_front();

    EXPECT_EQ(v1.size(), 15);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.front(), 2);
}

TEST(ClassVector, throw_when_try_pop_front_from_empty_vector) {
    Vector<double> v1;

    EXPECT_ANY_THROW(v1.pop_front());
}

TEST(ClassVector, can_pop_back) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });

    v1.pop_back();

    EXPECT_EQ(v1.size(), 14);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.back(), 14);
}

TEST(ClassVector, can_pop_back_with_reallocation) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });

    v1.pop_back();

    EXPECT_EQ(v1.size(), 15);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.back(), 15);
}

TEST(ClassVector, throw_when_try_pop_back_from_empty_vector) {
    Vector<double> v1;

    EXPECT_ANY_THROW(v1.pop_back());
}

TEST(ClassVector, can_correctly_recalc_back_in_area_of_zero) {
    Vector<double> vec;

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1);
    }

    vec.pop_front();
    vec.push_back(16);

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(16.0, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }

    vec.pop_back();

    EXPECT_EQ(14, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(15.0, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }
}

TEST(ClassVector, can_correctly_recalc_front_in_area_of_zero) {
    Vector<double> vec;

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1);
    }

    vec.pop_back();
    vec.push_front(0);

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(0.0, vec.front());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], static_cast<double>(i));
    }

    vec.pop_front();

    EXPECT_EQ(14, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(1.0, vec.front());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_erase) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10 });

    v1.erase(5);

    EXPECT_EQ(v1.size(), 9);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.back(), 10);
    EXPECT_EQ(v1[5], 7);
}

TEST(ClassVector, can_erase_front) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10 });

    v1.erase(0);

    EXPECT_EQ(v1.size(), 9);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.back(), 10);
    EXPECT_EQ(v1.front(), 2);
}

TEST(ClassVector, can_erase_back) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10 });

    v1.erase(9);

    EXPECT_EQ(v1.size(), 9);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.back(), 9);
}

TEST(ClassVector, can_erase_with_reallocation) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });

    v1.erase(9);

    EXPECT_EQ(v1.size(), 15);
    EXPECT_EQ(v1.capacity(), 15);
}

TEST(ClassVector, throw_when_try_erase_from_empty_vector) {
    Vector<double> v1;

    EXPECT_ANY_THROW(v1.erase(0));

}

TEST(ClassVector, throw_when_try_erase_with_wrong_position) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });

    EXPECT_ANY_THROW(v1.erase(21435));
}

TEST(ClassVector, combination_push_pop_insert_erase) {
    Vector<double> vec({ 3, 44, 5, 7, 8 });

    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_front();
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_front(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_back();
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_back(8 + i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(0);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.insert(6, 4);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    for (size_t i = 0; i < 5; i++) {
        vec.push_back(12 + i);
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    vec.insert(4, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    EXPECT_EQ(16, vec.size());
    EXPECT_EQ(30, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_assigment) {
    Vector<double> v1({ 1,2,3,4,5 });
    Vector<double> v2;

    v2 = v1;
    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2.capacity(), 15);
    EXPECT_EQ(v2.back(), 5);
    EXPECT_EQ(v2.front(), 1);


}

TEST(ClassVector, can_move_assigment) {
    Vector<double> vec_1;
    Vector<double> vec_2;

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_back(5 + i);
    }

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_front(4 - i);
    }

    vec_2 = std::move(vec_1);

    EXPECT_EQ(0, vec_1.size());
    EXPECT_EQ(15, vec_1.capacity());

    EXPECT_EQ(8, vec_2.size());
    EXPECT_EQ(15, vec_2.capacity());

    for (size_t i = 0; i < vec_2.size(); i++) {
        EXPECT_EQ(vec_2[i], i + 1);
    }
}

TEST(ClassVector, can_push_front_with_multilpe_elements) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8 });
    std::stringstream out;
    v1.push_front({ 89,2,3 });

    out << v1;
    EXPECT_EQ(v1.size(), 11);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.front(), 89);
    EXPECT_EQ("{ 89, 2, 3, 1, 2, 3, 4, 5, 6, 7, 8 }", out.str());
}

TEST(ClassVector, can_push_front_with_multilpe_elements_to_empty_vector) {
    Vector<double> v1;
    std::stringstream out;
    v1.push_front({ 89,2,3 });

    out << v1;
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.front(), 89);
    EXPECT_EQ("{ 89, 2, 3 }", out.str());
}

TEST(ClassVector, can_push_front_with_multilpe_elements_to_full_vector) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
    std::stringstream out;
    v1.push_front({ 89,2,3 });

    out << v1;
    EXPECT_EQ(v1.size(), 18);
    EXPECT_EQ(v1.capacity(), 30);
    EXPECT_EQ(v1.front(), 89);
    EXPECT_EQ("{ 89, 2, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }", out.str());
}

TEST(ClassVector, can_push_back_with_multilpe_elements) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8 });
    std::stringstream out;
    v1.push_back({ 89,2,3 });

    out << v1;
    EXPECT_EQ(v1.size(), 11);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.back(), 3);
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 89, 2, 3 }", out.str());
}

TEST(ClassVector, can_push_back_with_multilpe_elements_to_empty_vector) {
    Vector<double> v1;
    std::stringstream out;
    v1.push_back({ 89,2,3 });

    out << v1;
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.back(), 3);
    EXPECT_EQ("{ 89, 2, 3 }", out.str());
}

TEST(ClassVector, can_push_back_with_multilpe_elements_to_full_vector) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
    std::stringstream out;
    v1.push_back({ 89,2,3 });

    out << v1;
    EXPECT_EQ(v1.size(), 18);
    EXPECT_EQ(v1.capacity(), 30);
    EXPECT_EQ(v1.back(), 3);
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 89, 2, 3 }", out.str());
}

TEST(ClassVector, stress_push_front_back_wraparound) {
    Vector<double> v;

    v.push_back({ 1,2,3,4,5,6,7,8,9,10,11,12 });

    v.push_front({ -1, -2, -3 });

    v.push_back({ 13, 14, 15 });

    std::stringstream out;
    out << v;

    EXPECT_EQ(v.size(), 18);
    EXPECT_EQ(v.front(), -1);
    EXPECT_EQ(v.back(), 15);
    EXPECT_EQ("{ -1, -2, -3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }", out.str());
}

TEST(ClassVector, can_insert_multiple_elements_with_left_push) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9 });
    std::stringstream out;

    v1.insert({ 67,42,52 }, 2);
    out << v1;

    EXPECT_EQ(v1.size(), 12);
    EXPECT_EQ("{ 1, 2, 67, 42, 52, 3, 4, 5, 6, 7, 8, 9 }", out.str());
}

TEST(ClassVector, can_insert_multiple_elements_with_right_push) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9 });
    std::stringstream out;

    v1.insert({ 67,42,52 }, 7);
    out << v1;

    EXPECT_EQ(v1.size(), 12);
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 67, 42, 52, 8, 9 }", out.str());
}

TEST(ClassVector, can_insert_multiple_elements_in_front) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9 });
    std::stringstream out;

    v1.insert({ 67,42,52 }, 0);
    out << v1;

    EXPECT_EQ(v1.size(), 12);
    EXPECT_EQ("{ 67, 42, 52, 1, 2, 3, 4, 5, 6, 7, 8, 9 }", out.str());
}

TEST(ClassVector, can_insert_multiple_elements_in_back) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9 });
    std::stringstream out;

    v1.insert({ 67,42,52 }, 9);
    out << v1;

    EXPECT_EQ(v1.size(), 12);
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 67, 42, 52 }", out.str());
}

TEST(ClassVector, can_throw_insert_multiple_elements_with_wrong_pos) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9 });

    EXPECT_ANY_THROW(v1.insert({ 67,42,52 }, 1234));
}

TEST(ClassVector, insert_with_wraparound_left) {
    Vector<double> v;

    v.push_back({ 1,2,3,4,5,6,7,8,9,10 });
    v.push_front({ -1,-2,-3,-4,-5 }); // создаём wrap

    std::stringstream out;

    v.insert({ 100,200 }, 3);
    out << v;

    EXPECT_EQ("{ -1, -2, -3, 100, 200, -4, -5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }", out.str());
}

TEST(ClassVector, insert_middle_with_full_wraparound) {
    Vector<double> v;

    // почти заполняем
    v.push_back({ 1,2,3,4,5,6,7,8,9,10 });

    // создаём wrap (front уходит в конец буфера)
    v.push_front({ -1,-2,-3,-4,-5 });

    // теперь структура почти точно кольцевая (_front > _back)

    std::stringstream out;

    v.insert({ 100,200,300 }, 5); // ВАЖНО: середина

    out << v;

    EXPECT_EQ(
        "{ -1, -2, -3, -4, -5, 100, 200, 300, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }",
        out.str()
    );
}

TEST(ClassVector, insert_near_front_wraparound) {
    Vector<double> v;

    v.push_back({ 1,2,3,4,5,6,7,8 });
    v.push_front({ -1,-2,-3,-4,-5 }); // wrap

    std::stringstream out;

    v.insert({ 99 }, 1);

    out << v;

    EXPECT_EQ(
        "{ -1, 99, -2, -3, -4, -5, 1, 2, 3, 4, 5, 6, 7, 8 }",
        out.str()
    );
}

TEST(ClassVector, insert_near_back_wraparound) {
    Vector<double> v;

    v.push_back({ 1,2,3,4,5,6,7,8 });
    v.push_front({ -1,-2,-3,-4,-5 }); // wrap

    std::stringstream out;

    v.insert({ 99 }, v.size() - 1);

    out << v;

    EXPECT_EQ(
        "{ -1, -2, -3, -4, -5, 1, 2, 3, 4, 5, 6, 7, 99, 8 }",
        out.str()
    );
}

TEST(ClassVector, insert_small_buffer_edge_case) {
    Vector<double> v;

    v.push_back({ 1,2,3 });
    v.push_front({ -1 }); // минимальный wrap

    std::stringstream out;

    v.insert({ 99,100 }, 2);

    out << v;

    EXPECT_EQ("{ -1, 1, 99, 100, 2, 3 }", out.str());
}

TEST(ClassVector, can_pop_front_multiple_elements) {
    Vector<double> v1({ 1,2,3,4,5,6,7 });
    std::stringstream out;

    v1.pop_front(3);
    out << v1;
    EXPECT_EQ(v1.front(), 4);
    EXPECT_EQ(v1.size(), 4);
    EXPECT_EQ("{ 4, 5, 6, 7 }", out.str());

}

TEST(ClassVector, can_pop_front_multiple_elements_with_realoc) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 });
    std::stringstream out;

    v1.pop_front(3);
    out << v1;

    EXPECT_EQ(v1.front(), 4);
    EXPECT_EQ(v1.size(), 15);
    EXPECT_EQ(v1.capacity(), 15);

    EXPECT_EQ("{ 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 }", out.str());

}

TEST(ClassVector, can_pop_front_multiple_elements_throw) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 });

    EXPECT_ANY_THROW(v1.pop_front(23441));
}

TEST(ClassVector, can_pop_back_multiple_elements) {
    Vector<double> v1({ 1,2,3,4,5,6,7 });
    std::stringstream out;

    v1.pop_back(3);
    out << v1;

    EXPECT_EQ(v1.back(), 4);
    EXPECT_EQ(v1.size(), 4);
    EXPECT_EQ("{ 1, 2, 3, 4 }", out.str());

}

TEST(ClassVector, can_pop_back_multiple_elements_with_realoc) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 });
    std::stringstream out;

    v1.pop_back(3);
    out << v1;

    EXPECT_EQ(v1.back(), 15);
    EXPECT_EQ(v1.size(), 15);
    EXPECT_EQ(v1.capacity(), 15);

    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }", out.str());

}

TEST(ClassVector, can_pop_back_multiple_elements_throw) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 });

    EXPECT_ANY_THROW(v1.pop_back(23441));
}

TEST(ClassVector, can_erase_multiple_elements_with_right_push) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9 });
    std::stringstream out;

    v1.erase(2, 3);
    out << v1;

    EXPECT_EQ("{ 1, 2, 6, 7, 8, 9 }", out.str());
    EXPECT_EQ(v1.size(), 6);
}

TEST(ClassVector, can_erase_multiple_elements_with_left_push) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10,11,12 });
    std::stringstream out;

    v1.erase(8, 3);
    out << v1;

    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 12 }", out.str());
    EXPECT_EQ(v1.size(), 9);
}

// === ГРАНИЧНЫЕ СЛУЧАИ ===

TEST(ClassVector, erase_single_element_from_middle) {
    Vector<double> v1({ 10, 20, 30, 40, 50 });
    v1.erase(2, 1);  // Удаляем 30
    std::stringstream out;
    out << v1;
    EXPECT_EQ("{ 10, 20, 40, 50 }", out.str());
    EXPECT_EQ(v1.size(), 4);
}

TEST(ClassVector, erase_from_beginning_uses_pop_front) {
    Vector<double> v1({ 1, 2, 3, 4, 5 });
    v1.erase(0, 2);  // Удаляем 1, 2
    std::stringstream out;
    out << v1;
    EXPECT_EQ("{ 3, 4, 5 }", out.str());
    EXPECT_EQ(v1.front(), 3);  // _front должен обновиться
}

TEST(ClassVector, erase_from_end_uses_pop_back) {
    Vector<double> v1({ 1, 2, 3, 4, 5 });
    v1.erase(3, 2);  // Удаляем 4, 5
    std::stringstream out;
    out << v1;
    EXPECT_EQ("{ 1, 2, 3 }", out.str());
    EXPECT_EQ(v1.back(), 3);  // _back должен обновиться
}

TEST(ClassVector, erase_all_elements) {
    Vector<double> v1({ 1, 2, 3 });
    v1.erase(0, 3);
    EXPECT_TRUE(v1.is_empty());
    EXPECT_EQ(v1.size(), 0);
    // После полного удаления следующие push должны работать
    v1.push_back(42);
    EXPECT_EQ(v1.front(), 42);
    EXPECT_EQ(v1.back(), 42);
}

TEST(ClassVector, erase_zero_count_is_noop) {
    Vector<double> v1({ 1, 2, 3 });
    size_t old_size = v1.size();
    v1.erase(1, 0);
    EXPECT_EQ(v1.size(), old_size);
    std::stringstream out;
    out << v1;
    EXPECT_EQ("{ 1, 2, 3 }", out.str());
}


// === ЦИКЛИЧЕСКИЙ БУФЕР: обёртывание индексов ===

TEST(ClassVector, erase_after_push_front_causes_wrap) {
    Vector<double> v1(5);  // Ёмкость 15, но начнём с малого
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    // _front=0, _back=2

    // Сдвигаем _front вправо через много push_front, чтобы создать "дыру" в начале
    v1.push_front(10);
    v1.push_front(11);
    v1.push_front(12);
    // Теперь логический порядок: [12,11,10,1,2,3], _front != 0

    v1.erase(2, 2);  // Удаляем 10,1 (индексы 2 и 3 в логическом порядке)
    std::stringstream out;
    out << v1;
    EXPECT_EQ("{ 12, 11, 2, 3 }", out.str());
    EXPECT_EQ(v1.size(), 4);
}

TEST(ClassVector, erase_wraps_around_buffer_boundary) {
    // Создаём ситуацию, когда удаляемый блок пересекает физический конец массива
    Vector<double> v1;
    // Заполняем так, чтобы _back был близко к capacity-1
    for (int i = 1; i <= 14; ++i) v1.push_back(i);  // Ёмкость по умолчанию 15
    // _front=0, _back=13 (size=14)

    // Сдвигаем начало, чтобы данные "обернулись"
    v1.pop_front(10);  // Осталось [11,12,13,14], _front=10, _back=13
    v1.push_back(15);  // _back=14
    v1.push_back(16);  // _back=0 (обёртывание!), размер=6
    // Логически: [11,12,13,14,15,16], физически: [16, ?, ..., 11,12,13,14,15]

    v1.erase(3, 2);  // Удаляем 14,15 (пересекают границу: индексы 3,4)
    std::stringstream out;
    out << v1;
    EXPECT_EQ("{ 11, 12, 13, 16 }", out.str());
    EXPECT_EQ(v1.size(), 4);
}


// === ОШИБКИ И ИСКЛЮЧЕНИЯ ===

TEST(ClassVector, erase_throws_when_index_out_of_range) {
    Vector<double> v1({ 1, 2, 3 });
    EXPECT_THROW(v1.erase(5, 1), std::logic_error);  // index >= size
    EXPECT_THROW(v1.erase(3, 1), std::logic_error);  // index == size (не <= size-1)
}

TEST(ClassVector, erase_throws_when_count_exceeds_remaining) {
    Vector<double> v1({ 1, 2, 3, 4, 5 });
    EXPECT_THROW(v1.erase(2, 4), std::logic_error);  // 2+4 > 5
    EXPECT_THROW(v1.erase(0, 10), std::logic_error); // count > size
}

TEST(ClassVector, erase_on_empty_vector_throws) {
    Vector<double> v1;
    EXPECT_THROW(v1.erase(0, 1), std::logic_error);
    // Но erase(0,0) должен быть no-op (если реализовано)
    EXPECT_NO_THROW(v1.erase(0, 0));
}


// === СОСТОЯНИЕ ПОСЛЕ ОПЕРАЦИЙ ===

TEST(ClassVector, erase_then_push_consistency) {
    Vector<double> v1({ 1, 2, 3, 4, 5 });
    v1.erase(1, 2);  // Удаляем 2,3 → осталось [1,4,5]

    v1.push_back(6);
    v1.push_front(0);

    std::stringstream out;
    out << v1;
    EXPECT_EQ("{ 0, 1, 4, 5, 6 }", out.str());
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.front(), 0);
    EXPECT_EQ(v1.back(), 6);
}

TEST(ClassVector, multiple_consecutive_erases) {
    Vector<double> v1({ 1,2,3,4,5,6,7,8,9,10 });

    v1.erase(2, 2);  // [1,2,5,6,7,8,9,10]
    v1.erase(0, 1);  // [2,5,6,7,8,9,10]
    v1.erase(4, 2);  // [2,5,6,7,10]

    std::stringstream out;
    out << v1;
    EXPECT_EQ("{ 2, 5, 6, 7, 10 }", out.str());
    EXPECT_EQ(v1.size(), 5);
}

TEST(ClassVector, erase_triggers_capacity_shrink) {
    // Создаём вектор, который после erase станет меньше порога ёмкости
    Vector<double> v1;
    for (int i = 1; i <= 30; ++i) v1.push_back(i);  // Ёмкость вырастет до 30
    size_t old_capacity = v1.capacity();

    v1.erase(0, 20);  // Остаётся 10 элементов
    // Если calculate_capacity(10) < old_capacity, должен сработать reset_memory

    EXPECT_EQ(v1.size(), 10);
    EXPECT_LE(v1.capacity(), old_capacity);  // Ёмкость не должна увеличиться
    // Проверка, что данные целы
    EXPECT_EQ(v1.front(), 21);
    EXPECT_EQ(v1.back(), 30);
}


// === ПРОВЕРКА ИНВАРИАНТОВ ПОСЛЕ ERASE ===

TEST(ClassVector, erase_maintains_front_back_invariants) {
    Vector<double> v1({ 1,2,3,4,5 });

    // Удаляем из середины
    v1.erase(1, 2);
    EXPECT_EQ(v1.front(), 1);
    EXPECT_EQ(v1.back(), 5);
    EXPECT_EQ(v1.size(), 3);

    // Удаляем до конца
    v1.erase(1, 2);
    EXPECT_EQ(v1.front(), 1);
    EXPECT_EQ(v1.back(), 1);  // Последний == первый при size==1
    EXPECT_EQ(v1.size(), 1);

    // Удаляем последний
    v1.erase(0, 1);
    EXPECT_TRUE(v1.is_empty());
    // После полного удаления индексы должны быть валидны для следующего push
    EXPECT_NO_THROW(v1.push_back(42));
    EXPECT_EQ(v1.front(), 42);
}

// === ASSIGNMENT: SELF-ASSIGNMENT ===
// Часто забывают проверить v = v

TEST(ClassVector, copy_assignment_to_self) {
    Vector<double> v1({ 1,2,3,4,5 });
    v1 = v1;  // Самоприсваивание не должно ломать вектор

    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.front(), 1);
    EXPECT_EQ(v1.back(), 5);
    std::stringstream out;
    out << v1;
    EXPECT_EQ("{ 1, 2, 3, 4, 5 }", out.str());
}

TEST(ClassVector, move_assignment_to_self) {
    Vector<double> v1({ 1,2,3,4,5 });
    v1 = std::move(v1);  // Самоперемещение

    // После self-move объект должен остаться в валидном (возможно пустом) состоянии
    // Т.к. у тебя в operator= есть проверка &other == this, он должен сохраниться
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.front(), 1);
}

TEST(ClassVector, operator_index_after_complex_wrap) {
    Vector<double> v;
    // Создаём хаотичное состояние буфера
    v.push_back({ 1,2,3,4,5 });
    v.push_front({ -3,-2,-1 });      // [-3,-2,-1,1,2,3,4,5]
    v.pop_front(2);                // [-1,1,2,3,4,5]
    v.push_back({ 6,7,8 });          // [-1,1,2,3,4,5,6,7,8]
    v.erase(1, 2);                 // [-1,3,4,5,6,7,8]
    v.insert(0, 1);                // [-1,0,3,4,5,6,7,8]

    // Проверяем каждый индекс через operator[]
    std::vector<double> expected = { -1, 0, 3, 4, 5, 6, 7, 8 };
    EXPECT_EQ(v.size(), expected.size());
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v[i], expected[i]) << "Mismatch at index " << i;
    }
}


// === EMPTY INITIALIZER_LIST ===
// Пустые списки могут вызвать неочевидные баги

TEST(ClassVector, push_back_empty_initializer_list) {
    Vector<double> v1({ 1,2,3 });
    v1.push_back({});  // Пустой список
    EXPECT_EQ(v1.size(), 3);  // Размер не должен измениться
    EXPECT_EQ(v1.back(), 3);
}

TEST(ClassVector, insert_empty_initializer_list) {
    Vector<double> v1({ 1,2,3 });
    v1.insert({}, 1);  // Пустая вставка
    EXPECT_EQ(v1.size(), 3);
    std::stringstream out;
    out << v1;
    EXPECT_EQ("{ 1, 2, 3 }", out.str());
}


// === BOUNDARY: MEM_STEP (15) ===
// Критично для calculate_capacity

TEST(ClassVector, capacity_boundary_at_MEM_STEP) {
    Vector<double> v;
    // Ровно 15 элементов — граница
    for (int i = 1; i <= 15; ++i) v.push_back(i);
    EXPECT_EQ(v.size(), 15);
    EXPECT_EQ(v.capacity(), 15);  // Не 30!

    // 16-й элемент должен увеличить ёмкость до 30
    v.push_back(16);
    EXPECT_EQ(v.capacity(), 30);
    EXPECT_EQ(v.size(), 16);
}

TEST(ClassVector, const_methods_on_const_vector) {
    const Vector<double> v1({ 1,2,3,4,5 });

    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.capacity(), 15);
    EXPECT_EQ(v1.front(), 1);
    EXPECT_EQ(v1.back(), 5);
    EXPECT_EQ(v1[2], 3);  // const operator[]
    EXPECT_TRUE(v1.is_empty() == false);
    EXPECT_TRUE(v1.is_full() == false);
}


// === LARGE COUNT OPERATIONS ===
// Удаление/вставка большого количества элементов за раз

TEST(ClassVector, erase_large_count_from_middle) {
    Vector<double> v;
    for (int i = 0; i < 100; ++i) v.push_back(i);

    v.erase(25, 50);  // Удаляем 50 элементов из середины

    EXPECT_EQ(v.size(), 50);
    EXPECT_EQ(v.front(), 0);
    EXPECT_EQ(v.back(), 99);
    EXPECT_EQ(v[24], 24);   // Последний перед удаляемыми
    EXPECT_EQ(v[25], 75);   // Первый после удаляемых
}

TEST(ClassVector, reset_memory_to_same_capacity_is_noop_for_data) {
    Vector<double> v1({ 1,2,3,4,5 });
    size_t old_capacity = v1.capacity();

    // Добавляем и удаляем, чтобы триггернуть reset_memory
    for (int i = 0; i < 10; ++i) v1.push_back(10 + i);
    for (int i = 0; i < 10; ++i) v1.pop_back();

    // Данные должны остаться целыми
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.front(), 1);
    EXPECT_EQ(v1.back(), 5);
}


// === EXCEPTION SAFETY (basic guarantee) ===
// Если бросается исключение, вектор должен остаться валидным

// Примечание: для полноценного теста нужен mock аллокатора,
// но можно проверить хотя бы логику

TEST(ClassVector, erase_does_not_corrupt_on_partial_operation) {
    Vector<double> v1({ 1,2,3,4,5 });

    // Попытка удалить больше, чем есть — должно бросить и не сломать вектор
    try {
        v1.erase(2, 10);
        FAIL() << "Expected std::logic_error";
    }
    catch (const std::logic_error&) {
        // После исключения вектор должен быть цел
        EXPECT_EQ(v1.size(), 5);
        EXPECT_EQ(v1.front(), 1);
        EXPECT_EQ(v1.back(), 5);
        std::stringstream out;
        out << v1;
        EXPECT_EQ("{ 1, 2, 3, 4, 5 }", out.str());
    }
}

TEST(ClassVector, stress_alternating_operations) {
    Vector<double> v;

    // Много чередующихся операций для стресса циклической логики
    for (int round = 0; round < 50; ++round) {
        v.push_back(round * 2);
        v.push_front(round * 2 + 1);
        if (v.size() > 10) {
            v.pop_back(2);
            v.pop_front(1);
        }
    }

    // Просто проверяем, что не упало и инварианты целы
    EXPECT_GE(v.size(), 0);
    EXPECT_LE(v.size(), v.capacity());
    if (!v.is_empty()) {
        EXPECT_NO_THROW(v.front());
        EXPECT_NO_THROW(v.back());
    }
}


// === STRESS: RANDOM-LIKE SEQUENCE ===
TEST(ClassVector, stress_deterministic_sequence) {
    Vector<double> v;

    // Детерминированная "случайная" последовательность операций
    v.push_back(1);      // [1]
    v.push_front(2);     // [2,1]
    v.insert(3, 1);      // [2,3,1]
    v.erase(0, 1);       // [3,1]
    v.push_back(4);      // [3,1,4]
    v.pop_front();       // [1,4]
    v.push_front(5);     // [5,1,4]
    v.erase(1, 1);       // [5,4]
    v.insert(6, 1);      // [5,6,4]
    v.pop_back();        // [5,6]

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.front(), 5);
    EXPECT_EQ(v.back(), 6);
    EXPECT_EQ(v[0], 5);
    EXPECT_EQ(v[1], 6);
}

TEST(SelectionSortTest, EmptyVector) {
    Vector<double> v;
    v.selection_sort();
    EXPECT_TRUE(v.is_empty());
}

TEST(SelectionSortTest, SingleElement) {
    Vector<double> v = { 42.0 };
    v.selection_sort();
    EXPECT_EQ(v.size(), 1);
    EXPECT_DOUBLE_EQ(v[0], 42.0);
}

TEST(SelectionSortTest, AlreadySorted) {
    Vector<double> v = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    v.selection_sort();

    for (size_t i = 0; i < v.size(); i++) {
        EXPECT_DOUBLE_EQ(v[i], i + 1);
    }
}

TEST(SelectionSortTest, ReverseSorted) {
    Vector<double> v = { 5.0, 4.0, 3.0, 2.0, 1.0 };
    v.selection_sort();

    for (size_t i = 0; i < v.size(); i++) {
        EXPECT_DOUBLE_EQ(v[i], i + 1);
    }
}

TEST(SelectionSortTest, RandomOrder) {
    Vector<double> v = { 3.0, 1.0, 4.0, 1.0, 5.0, 9.0, 2.0, 6.0, 5.0, 3.0 };
    v.selection_sort();

    for (size_t i = 1; i < v.size(); i++) {
        EXPECT_LE(v[i - 1], v[i]);
    }
}

TEST(SelectionSortTest, WithDuplicates) {
    Vector<double> v = { 3.0, 1.0, 3.0, 2.0, 1.0, 2.0 };
    v.selection_sort();

    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 1.0);
    EXPECT_DOUBLE_EQ(v[2], 2.0);
    EXPECT_DOUBLE_EQ(v[3], 2.0);
    EXPECT_DOUBLE_EQ(v[4], 3.0);
    EXPECT_DOUBLE_EQ(v[5], 3.0);
}

TEST(SelectionSortTest, NegativeNumbers) {
    Vector<double> v = { -3.0, 5.0, -1.0, 0.0, -5.0, 2.0 };
    v.selection_sort();

    EXPECT_DOUBLE_EQ(v[0], -5.0);
    EXPECT_DOUBLE_EQ(v[1], -3.0);
    EXPECT_DOUBLE_EQ(v[2], -1.0);
    EXPECT_DOUBLE_EQ(v[3], 0.0);
    EXPECT_DOUBLE_EQ(v[4], 2.0);
    EXPECT_DOUBLE_EQ(v[5], 5.0);
}

TEST(SelectionSortTest, LargeVector) {
    Vector<double> v;
    for (int i = 1000; i > 0; i--) {
        v.push_back(i);
    }

    v.selection_sort();

    for (size_t i = 0; i < v.size(); i++) {
        EXPECT_DOUBLE_EQ(v[i], i + 1);
    }
}

TEST(SelectionSortTest, PushFrontThenSort) {
    Vector<double> v;
    v.push_front(3.0);
    v.push_front(1.0);
    v.push_front(2.0);
    v.selection_sort();

    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
}

TEST(SelectionSortTest, CyclicMemoryAfterInsertErase) {
    Vector<double> v = { 5.0, 3.0, 8.0, 1.0, 4.0 };
    v.insert(2.0, 2);
    v.erase(3, 1);
    v.selection_sort();

    for (size_t i = 1; i < v.size(); i++) {
        EXPECT_LE(v[i - 1], v[i]);
    }
}

// ---------------------------------------------------------------
// 1. operator<< обязан возвращать os (используется как
//    os << a << b или в условиях). В исходнике нет return os,
//    что уже UB по стандарту; на практике часто ловится как
//    "мусорное" значение / предупреждение компилятора,
//    а в некоторых сборках — падение при цепочке вызовов.
// ---------------------------------------------------------------
TEST(ClassVector, stream_insertion_returns_reference_to_stream) {
    Vector<int> v{ 1, 2, 3 };
    std::ostringstream os;

    // Цепочка: если operator<< не возвращает os, второй '<<' либо
    // не скомпилируется, либо (если компилятор всё же что-то вернул
    // по UB) даст не тот результат.
    os << v << " end";

    EXPECT_EQ(os.str(), "{ 1, 2, 3 } end");
}

// ---------------------------------------------------------------
// 2. operator>> должен прочитать ровно n элементов и выставить
//    size() == n. В исходнике цикл идёт до _size - 1, то есть
//    последний элемент не читается, а size не обновляется вовсе
//    (возможен указатель в никуда, если вектор был пуст).
// ---------------------------------------------------------------
TEST(ClassVector, stream_extraction_reads_exactly_n_elements) {
    Vector<int> v;
    std::istringstream is("4 10 20 30 40");

    is >> v;

    ASSERT_EQ(v.size(), 4u)
        << "operator>> не выставил правильный size после чтения";
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
    EXPECT_EQ(v[3], 40);   // в исходнике этот элемент никогда не читается
}

// ---------------------------------------------------------------
// 3. Копирующее присваивание должно воспроизводить логическое
//    содержимое вектора независимо от того, как элементы лежат
//    в кольце у исходного объекта (т.е. с учётом other._front).
// ---------------------------------------------------------------
TEST(ClassVector, copy_assignment_preserves_logical_order_for_wrapped_ring) {
    Vector<int> src;
    // Заполняем РОВНО под capacity (15), чтобы не спровоцировать resize,
    // затем выталкиваем часть спереди: _front становится ненулевым,
    // а calculate_capacity(size) после pop всё ещё равен текущей capacity,
    // поэтому автоматический shrink (который сбросил бы _front на 0
    // и замаскировал бы баг) не срабатывает.
    for (int i = 1; i <= 15; i++) src.push_back(i);
    for (int i = 0; i < 5; i++) src.pop_front();

    Vector<int> dst;
    dst = src;

    ASSERT_EQ(dst.size(), src.size());
    for (size_t i = 0; i < src.size(); i++) {
        EXPECT_EQ(dst[i], src[i])
            << "copy assignment исказил порядок элементов на индексе " << i;
    }
}

// ---------------------------------------------------------------
// 4. Move-присваивание не должно терять память исходного буфера
//    (утечка) и должно оставлять other в рабочем состоянии —
//    в частности, capacity() у other не должна быть равна 0,
//    иначе любое дальнейшее обращение к other делит на ноль
//    в (index % capacity).
// ---------------------------------------------------------------
TEST(ClassVector, move_assignment_leaves_source_in_valid_state) {
    Vector<int> src{ 1, 2, 3 };
    Vector<int> dst;

    dst = std::move(src);

    ASSERT_EQ(dst.size(), 3u);
    EXPECT_EQ(dst[0], 1);
    EXPECT_EQ(dst[1], 2);
    EXPECT_EQ(dst[2], 3);

    // В исходнике other._mem._capacity = 0, поэтому push_back
    // на src после move делит на ноль в operator[] / индексации.
    EXPECT_NO_THROW({
        src.push_back(99);
        });
}

// ---------------------------------------------------------------
// 7. shuffle должен компилироваться и работать для произвольного T,
//    а не только для типов, неявно приводимых к double
//    (в исходнике используется "double tmp" внутри шаблона).
// ---------------------------------------------------------------
TEST(ClassVector, shuffle_works_for_non_numeric_type) {
    Vector<std::string> v{ "a", "b", "c", "d" };
    v.shuffle();

    // Перемешивание не должно терять/дублировать элементы.
    std::vector<std::string> result;
    for (size_t i = 0; i < v.size(); i++) result.push_back(v[i]);
    std::sort(result.begin(), result.end());

    EXPECT_EQ(result, (std::vector<std::string>{ "a", "b", "c", "d" }));
}

// ---------------------------------------------------------------
// 9. erase на пустом векторе должен бросать исключение, а не
//    падать по UB. В исходнике "human_index > _mem._size - 1"
//    при _size == 0 даёт size_t-underflow (_size - 1 == SIZE_MAX),
//    и проверка перестаёт работать как задумано.
// ---------------------------------------------------------------
TEST(ClassVector, erase_on_empty_vector_throwsgvjh) {
    Vector<int> v;
    EXPECT_THROW(v.erase(0), std::exception);
}

#endif
