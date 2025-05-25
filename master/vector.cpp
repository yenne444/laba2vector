#include "../VecH/Vector.h"

void Vector::printVec() const
{
    std::cout << "{ ";
    for (size_t i = 0; i < _size; ++i) {  
        std::cout << _data[i];            
        if (i != _size - 1) {             
            std::cout << ", ";
        }
    }
    std::cout << " }" << std::endl;       
}

void Vector::clear() 
{
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

//Vector::Vector() : _size(0), _capacity(0), _multiplicativeCoef(2.0f), _data(nullptr)
//{

//};

Vector::Vector(const ValueType* rawArray, const size_t size, float coef) : _size(size), _capacity(size), _multiplicativeCoef(coef)
{
    if (_size > 0)
    {
        _data = new ValueType[_capacity];

        for (size_t i = 0; i < size; ++i)
        {
            _data[i] = rawArray[i];
        };
    }

    else
    {
        _data = nullptr;
    }
};

Vector::Vector(const Vector& other) : _size(other._size), _capacity(other._size), _multiplicativeCoef(other._multiplicativeCoef)
{
    if (_size == 0)
    {
        _data = nullptr;
        return;
    }

    _data = new ValueType[_size];
    
    for (size_t i = 0; i < _size; ++i)
    {
        _data[i] = other._data[i];
    }
};

Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (this != &other)
    {
        delete[] _data;

        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;

        if (_size > 0)
        {
            _data = new ValueType[_size];

            for (size_t i = 0; i < other._size; ++i)
            {
                _data[i] = other._data[i];
            };
        }

        else
        {
            _data = nullptr;
        };
    };

    return *this;
};

Vector::Vector(Vector&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity), _multiplicativeCoef(other._multiplicativeCoef)
{
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
};

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this != &other)
    {
        clear();

        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;

        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;        
    };
    
    return *this;
};

Vector::~Vector()
{
    delete[] _data;
};

void Vector::pushBack(const ValueType& value)
{
    if (_size >= _capacity)
    {
        size_t new_capacity;

        if (_capacity == 0)
        {
            new_capacity = 4;
        }
    
        else
        {
            new_capacity = static_cast<size_t>(_capacity * _multiplicativeCoef);
        }

        ValueType* new_data = new ValueType[new_capacity];

        for (size_t i = 0; i < _size; ++i)
        {
            new_data[i] = _data[i];
        }

        delete[] _data;

        _data = new_data;
        _capacity = new_capacity;
    }

    _data[_size] = value;
    ++_size;
}

void Vector::pushFront(const ValueType& value)
{
    if (_size >= _capacity)
    {
        size_t new_capacity;

        if (_capacity == 0)
        {
            new_capacity = 4;
        }

        else
        {
            new_capacity = static_cast<size_t>(_capacity * _multiplicativeCoef);
        }

        ValueType* new_data = new ValueType[new_capacity];

        for (size_t i = 0; i < _size; ++i)
        {
            new_data[i + 1] = _data[i];
        }

        delete[] _data;

        _data = new_data;
        _capacity = new_capacity;
    }

    else
    {
        for (size_t i = _size; i > 0; --i)
        {
            _data[i] = _data[i - 1];
        }
    }

    _data[0] = value;
    ++_size;
}

void Vector::insert(const ValueType& value, size_t pos)
{
    if (pos > _size)
    {
        std::cout << "Error (pos > _size)" << std::endl;
        return;
    }

    size_t new_capacity;

    if (_size >= _capacity)
    {
        if (_capacity == 0)
        {
            new_capacity = 4;
        }

        else
        {
            new_capacity = static_cast<size_t>(_capacity * _multiplicativeCoef);
        }

        ValueType* new_data = new ValueType[new_capacity];

        for (size_t i = 0; i < pos; ++i)
        {
            new_data[i] = _data[i];
        }

        new_data[pos] = value;

        for (size_t i = pos; i < _size; ++i)
        {
            new_data[i + 1] = _data[i];
        }

        delete[] _data;

        _data = new_data;
        _capacity = new_capacity;
    }

    else
    {
        for (size_t i = _size; i > pos; --i)
        {
            _data[i] = _data[i - 1];
        }

        _data[pos] = value;
    }

    ++_size;
};

    
void Vector::insert(const ValueType* values, size_t size, size_t pos)
{
    if (pos > _size)
    {
        std::cout << "Error (pos > _size)";
        return;
    }

    if (size == 0)
    {
        return;
    }

    size_t new_capacity;

    if (_size + size >= _capacity)
    {
        if (_capacity == 0)
        {
            new_capacity = 4;
        }

        else
        {
            new_capacity = static_cast<size_t>(_capacity * _multiplicativeCoef);
        }

        ValueType* new_data = new ValueType[new_capacity];

        for (size_t i = 0; i < pos; ++i)
        {
            new_data[i] = _data[i];
        }

        for (size_t i = 0; i < size; ++i)
        {
            new_data[pos + i] = values[i];
        }

        for (size_t i = pos; i < _size; ++i)
        {
            new_data[i + size] = _data[i];
        }

        delete[] _data;

        _data = new_data;
        _capacity = new_capacity;
    }

    else
    {
        for (size_t i = pos; i < _size; ++i)
        {
            _data[i + size] = _data[i];
        }

        for (size_t i = 0; i < size; ++i)
        {
            _data[pos + i] = values[i];
        }
    }
    _size += size;
}

void Vector::insert(const Vector& vector, size_t pos)
{
    if (pos > _size)
    {
        std::cout << "Error (pos > _size)";
        return;
    }

    if (vector.size() == 0)
    {
        return;
    }

    if (_size + vector.size() >= _capacity)
    {
        size_t tmp_size = _size + vector.size();

        size_t new_capacity = std::max(tmp_size, static_cast<size_t>(_capacity * _multiplicativeCoef));

        ValueType* new_data = new ValueType[new_capacity];

        for (size_t i = 0; i < pos; ++i)
        {
            new_data[i] = _data[i];
        }

        for (size_t i = 0; i < vector.size(); ++i)
        {
            new_data[pos + i] = vector._data[i];
        }

        for (size_t i = pos; i < _size; ++i)
        {
            new_data[i + vector.size()] = _data[i];
        }

        delete[] _data;

        _data = new_data;
        _capacity = new_capacity;

    }
    
    else
    {
        for (size_t i = pos; i < _size; ++i)
        {
            _data[i + vector.size()] = _data[i];
        }

        for (size_t i = 0; i < vector.size(); ++i)
        {
            _data[pos + i] = vector._data[i];
        }
    }

    _size += vector.size();
}

void Vector::popBack()
{
    if (_size == 0)
    {
        throw std::out_of_range ("It is not possible to delete an element from an empty vector");
    }

    --_size;
}

void Vector::popFront()
{
    if (_size == 0)
    {
        throw std::out_of_range ("It is not possible to delete an element from an empty vector");
    }

    for (size_t i = 1; i < _size; ++i)
    {
        _data[i - 1] = _data[i];
    }

    --_size;
}

void Vector::erase(size_t pos, size_t count)
{
    if (pos > _size) 
    {
        std::cout << "Error (pos > _size)";
        return;
    }
    
    if (count > _size - pos)
    {
        count = _size - pos;
    }

    if (_size == 0)
    {
        return;
    } 

    for (size_t i = pos; i < _size - count; ++i)
    {
        _data[i] = _data[i + count];
    }

    _size -= count;
};

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if (_size == 0)
    {
        return;
    }

    if (beginPos > _size || beginPos > endPos)
    {
        std::cout << "Error (beginPos > _size || beginPos > endPos)";
        return;
    }

    if (endPos > _size)
    {
        endPos = _size;
    }
    
    size_t count = endPos - beginPos;
    
    for (size_t i = beginPos; i < _size - count; ++i)
    {
        _data[i] = _data[i + count];                                                                    
    }

    _size -= count;                    
};

size_t Vector::size() const
{
    return _size;
};

size_t Vector::capacity() const
{
    return _capacity;
};

double Vector::loadFactor() const
{
    if (_capacity == 0)
    {
        return 0.0;
    };
    return double(_size) / double(_capacity);
};

ValueType& Vector::operator[](size_t idx)
{
    if (_size <= idx)
    {
        std::cout << "The index is not suitable";
    };
    return _data[idx];
};

const ValueType& Vector::operator[](size_t idx) const
{
    if (_size <= idx)
    {
        std::cout << "The index is not suitable";
    };
    return _data[idx];
};

long long Vector::find(const ValueType& value) const
{
    if (_size == 0) 
    {
        std::cout << "Error (_size == 0)";
        return -1;
    }

    for (size_t i = 0; i < _size; ++i)
    {
        if (_data[i] == value)
        {
            return static_cast<long long>(i);
        }
    }

    std::cout << "Element is not in vector";

    return -1;
};

void Vector::reserve(size_t capacity)
{
    if (capacity > _capacity)
    {
        ValueType* new_data = new ValueType[capacity];

        for (size_t i = 0; i < _size; ++i)
        {
            new_data[i] = _data[i];
        }

        delete[] _data;

        _data = new_data;
        _capacity = capacity;
    }

    else {return;}
};

void Vector::shrinkToFit()
{
    if (_size == _capacity)
    {
        return;
    }

    if (_size == 0)
    {
        clear();
    }

    ValueType* new_data = new ValueType[_size];

    for (size_t i = 0; i < _size; ++i)
    {
        new_data[i] = _data[i];
    };

    delete[] _data;
    
    _data = new_data;
    _capacity = _size;
};

Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}

ValueType& Vector::Iterator::operator*()
{
    return *_ptr;
};

const ValueType& Vector::Iterator::operator*() const
{
    return *_ptr;
};

ValueType* Vector::Iterator::operator->()
{
    return _ptr;
};

const ValueType* Vector::Iterator::operator->() const
{
    return _ptr;
};

Vector::Iterator Vector::Iterator::operator++()
{
    ++_ptr;
    return *this;
};

Vector::Iterator Vector::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++_ptr;
    return *this;
};

bool Vector::Iterator::operator==(const Iterator& other) const
{
    return _ptr == other._ptr;
};

bool Vector::Iterator::operator!=(const Iterator& other) const
{
    return _ptr != other._ptr;
};

Vector::Iterator Vector::begin()
{
    return Iterator(_data);
};

Vector::Iterator Vector::end()
{
    return Iterator(_data + _size);
};

