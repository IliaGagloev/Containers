#pragma once
#include<iostream>

using ValueType = double;
//! \brief Класс, реализующий С++ контейнер vector для типа int
class Vector
{
public:
    //! \note Все конструкторы и операторы присваивания должны создавать вектор, где _capacity равно _size
    //! Конструктор без параметров
    Vector() = default;//yes
    //! Конструктор с параметрами
    Vector(const ValueType* rawArray, const size_t size, float coef = 2.0f);//yes
    //! Конструктор копирования
    //! \param other - копируемый объект
    explicit Vector(const Vector& other);//yes
    //! Оператор присваивания копированием
    //! \param other - копируемый объект
    Vector& operator=(const Vector& other);//yes
    //! Конструктор перемещения
    //! \param other - перемещаемый объект
    explicit Vector(Vector&& other) noexcept;
    //! Оператор присваивания перемещением
    //! \param other - перемещаемый объект
    Vector& operator=(Vector&& other) noexcept;
    //! Деструктор
    ~Vector();//yes

	//! Вставка в конец
    void pushBack(const ValueType& value);//yes
	//! Вставка в начало
    void pushFront(const ValueType& value);//yes

	//! Вставка элемента value в позицию pos
    void insert(const ValueType& value, size_t pos);//yes
	//! Вставка массива элементов типа ValueType в позицию pos
    void insert(const ValueType* values, size_t size, size_t pos);//yes
	//! Вставка содержимого вектора в позицию pos
    void insert(const Vector& vector, size_t pos);//yes

	//! Удаление с конца
    void popBack();//yes
	//! Удаление из начала
    void popFront();//yes

    /*!
        \brief Удалить элемент(ы) из вектора
        \param pos: позиция начала удаляемого участка
        \param count: количество удаляемых элементов
        если (pos + count) > size, то элементы интервала [pos, size) должны быть удалены
    */
    void erase(size_t pos, size_t count = 1);//yes

    /*!
        \brief Удалить элемент(ы) из вектора
        \param beginPos: позиция начала удаляемого участка
        \param endPos: позиция окончания удаляемого участка
        Все элементы интервала [beginPos, endPos) должны быть удалены:
            [1, 2, 3, 4] -> erase(1, 3) -> [1, 4]
        если endPos > size, то элементы интервала [beginPos, size) должны быть удалены
    */
    void eraseBetween(size_t beginPos, size_t endPos);//yes

	//! Количество элементов
    size_t size() const;//yes
	//! Максимальное количество элементов
    size_t capacity() const;//yes
	//! Фактор загруженности
    double loadFactor() const;//yes

    //! Доступ к элементу по индексу
    ValueType& operator[](size_t idx);//yes
    //! Доступ к элементу по индексу
    const ValueType& operator[](size_t idx) const;//yes

    //! Поиск первого вхождения значения
    //! \return - индекс элемента
    long long find(const ValueType& value) const;//yes
   
    //! Если capacity > _capacity, то выделить новый участок памяти размером capacity и перенести вектор туда, иначе - ничего
    void reserve(size_t capacity);//yes
	//! Уменьшить capacity до size
    void shrinkToFit();//yes
	
	//! Класс, реализующий итератор
    class Iterator
    {
        ValueType* _ptr;
    public:
        explicit Iterator(ValueType* ptr);
        ValueType& operator*();
        const ValueType& operator*() const;
        ValueType* operator->();
        const ValueType* operator->() const;
        Iterator operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

	//! Получить итератор на начало вектора
    Iterator begin();
	//! Получить итератор на элемент вектора, следующий за последним
    Iterator end();
private:
    ValueType* _data = nullptr; //! "сырой" указатель на данные
    size_t _size = 0; //! текущий размер
    size_t _capacity = 0; //! максимальный размер (количество элементов, под которое выделена память)
    float _multiplicativeCoef = 2.0f; //! коэффициент увеличения _capacity вектора при _size == _capacity
};

