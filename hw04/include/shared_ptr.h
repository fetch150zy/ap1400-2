#ifndef SHARED_PTR
#define SHARED_PTR

#include <cstddef>

template <typename T>
class SharedPtr
{
public:
    SharedPtr(): m_p(nullptr), m_cnt_ptr(new size_t(0)) { }
    SharedPtr(T* p): m_p(p), m_cnt_ptr(new size_t(1)) { }
    SharedPtr(const SharedPtr& sp)
    {
        ++(*sp.m_cnt_ptr);
        this->m_cnt_ptr = sp.m_cnt_ptr;
        this->m_p = sp.m_p;
    }
    SharedPtr& operator=(const SharedPtr& sp)
    {
        if (&sp != this) {
            this->~SharedPtr();
            ++(*sp.m_cnt_ptr);
            this->m_cnt_ptr = sp.m_cnt_ptr;
            this->m_p = sp.m_p;
        }
        return *this;
    }
    std::size_t use_count() const
    {
        if (this->m_cnt_ptr != nullptr)
            return *this->m_cnt_ptr;
        else
            return 0;
    }
    T* get() const
    {
        return this->m_p;
    }
    T* operator->() const
    {
        return this->m_p;
    }
    T& operator*() const
    {
        return *this->operator->();
    }
    void reset()
    {
        if (this->m_p != nullptr)
            delete this->m_p;
        this->m_p = nullptr;
        *this->m_cnt_ptr = 0;
    }
    void reset(T *p)
    {
        if (this->m_p != p) {
            if (this->m_p != nullptr)
                delete this->m_p;
            this->m_p = p;
            *this->m_cnt_ptr = 1;
        }
    }
    operator bool() const
    {
        return this->m_p != nullptr;
    }
    ~SharedPtr()
    {
        if (m_cnt_ptr == nullptr) {
            return;
        } else if (*m_cnt_ptr == 0) {
            delete m_cnt_ptr;
            return;
        } else {
            --(*m_cnt_ptr);
            if (*m_cnt_ptr == 0) {
                delete m_p;
                m_p = nullptr;
                delete m_cnt_ptr;
                m_cnt_ptr = nullptr;
            }
        }
    }
private:
    T* m_p = nullptr;
    std::size_t* m_cnt_ptr = nullptr;
};

template <typename T>
T* make_shared(const T& t)
{
    return new T(t);
}

#endif //SHARED_PTR
