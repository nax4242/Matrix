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

    EXPECT_FALSE(m2.data() == nullptr);
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

    EXPECT_EQ(m1.size(), 3);
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
    EXPECT_FALSE(m1.data() == nullptr);
}

// ---------------------------------------------------------------
// 1. Конструктор MemData(T*, size_t) читает _capacity элементов
//    из источника, хотя тот содержит только size. Валиден он
//    только тогда, когда src физически имеет размер _capacity
//    (как и строился в вашем собственном тесте can_reset_memory_with_shift).
//    Здесь источник — ровно size элементов, как и ожидает обычный
//    пользователь класса (например, Vector(T*, size_t)).
// ---------------------------------------------------------------
TEST(ClassMemData, construct_from_pointer_does_not_read_out_of_bounds) {
    int* src = new int[5] { 10, 20, 30, 40, 50 };   // буфер ровно на 5 элементов

    // ASAN должен поймать выход за границы на 6-м и далее чтении.
    MemData<int> m(src, 5);

    EXPECT_EQ(m.size(), 5u);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(m.data()[i], src[i]);
    }

    delete[] src;
}

// ---------------------------------------------------------------
// 2. Конструктор от initializer_list{} (пустой список) должен
//    оставлять класс в рабочем состоянии: capacity = MEM_STEP,
//    data не nullptr (иначе падает на первом push).
// ---------------------------------------------------------------
TEST(ClassMemData, empty_initializer_list_leaves_usable_buffer) {
    MemData<int> m({});

    EXPECT_EQ(m.size(), 0u);
    EXPECT_EQ(m.capacity(), static_cast<size_t>(MEM_STEP));

    // Если _data == nullptr, следующая строка упадёт по сегфолту.
    const_cast<int*>(m.data())[0] = 42;
    SUCCEED();
}

// ---------------------------------------------------------------
// 3. Перемещающий конструктор обязан оставить источник в
//    консистентном состоянии: size == 0, capacity == MEM_STEP,
//    data доступен для дальнейшего использования (например,
//    объект продолжают переиспользовать после std::move).
// ---------------------------------------------------------------
TEST(ClassMemData, move_constructor_leaves_source_usable) {
    MemData<int> m1({ 1, 2, 3 });
    MemData<int> m2(std::move(m1));

    EXPECT_EQ(m2.size(), 3u);
    EXPECT_EQ(m1.size(), 0u);
    EXPECT_EQ(m1.capacity(), static_cast<size_t>(MEM_STEP));

    // m1 должен быть пригоден для дальнейшей работы, а не хранить
    // противоречивые capacity/data (в исходнике capacity = 15,
    // но data = nullptr — set_memory на этом ломается).
    m1.set_memory(5);
    SUCCEED();
}

// ---------------------------------------------------------------
// 4. Move-присваивание обязано обнулить _size/_capacity источника,
//    иначе получаем "битый" объект: data == nullptr, но size/capacity
//    ненулевые, и любое обращение к data()[i] падает или UB.
// ---------------------------------------------------------------
TEST(ClassMemData, move_assignment_resets_source_state) {
    MemData<int> m1({ 1, 2, 3 });
    MemData<int> m2({ 9, 9 });

    m2 = std::move(m1);

    EXPECT_EQ(m2.size(), 3u);
    EXPECT_EQ(m1.size(), 0u);
    EXPECT_EQ(m1.capacity(), 0u);   // в исходнике данные не обнуляются вовсе
}

// ---------------------------------------------------------------
// 5. reset_memory с неизменной capacity должна тем не менее
//    физически "выпрямлять" кольцо начиная с start_index.
//    В исходнике при равной capacity функция выходит без действий,
//    и данные остаются на старых (кольцевых) позициях.
// ---------------------------------------------------------------
TEST(ClassMemData, reset_memory_realigns_even_when_capacity_unchanged) {
    // Конструктор от initializer_list уже выставляет _size = 5,
    // capacity = 15 и кладёт данные линейно в data[0..4].
    MemData<int> m({ 1, 2, 3, 4, 5 });

    // Вручную переносим те же значения в "кольцевую" раскладку
    // со сдвигом (как если бы Vector держал _front = 13),
    // не трогая _size — он уже равен 5.
    int tmp[15] = {};
    size_t idx = 13;
    for (int v : {1, 2, 3, 4, 5}) {
        tmp[idx] = v;
        idx = (idx + 1) % 15;
    }
    int* raw = const_cast<int*>(m.data());
    std::copy(std::begin(tmp), std::end(tmp), raw);

    // capacity останется той же (15), значит сработает именно
    // ветка "ёмкость не меняется".
    m.reset_memory(5, 13);

    // Ожидание: data()[0..4] == 1..5, то есть кольцо выпрямлено.
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(m.data()[i], i + 1)
            << "reset_memory не переложила элементы, хотя capacity не изменилась";
    }
}

// ---------------------------------------------------------------
// 6. reset_memory обязана усекать _size, если новый size меньше
//    текущего (например, pop несколько элементов подряд).
// ---------------------------------------------------------------
TEST(ClassMemData, reset_memory_shrinks_size_when_requested_size_is_smaller) {
    MemData<int> m({ 1, 2, 3, 4, 5 });
    m.reset_memory(2, 0);   // просим оставить только 2 элемента

    EXPECT_EQ(m.size(), 2u)
        << "reset_memory не уменьшила _size при запросе меньшего размера";
}
#endif