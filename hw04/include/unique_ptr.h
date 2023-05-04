#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr
{
public:
    UniquePtr(): m_p(nullptr) { }
    UniquePtr(T* p): m_p(p) { }
    UniquePtr(const UniquePtr& ptr) = delete;
    UniquePtr& operator=(const UniquePtr& ptr) = delete;
    T* operator->() const
    {
        return this->m_p;
    }
    T& operator*() const
    {
        return *this->operator->();
    }
    operator bool() const
    {
        return this->m_p != nullptr;
    }
    T* get() const
    {
        return this->m_p;
    }
    void reset()
    {
        if (this->m_p != nullptr)
            delete this->m_p;
        this->m_p = nullptr;
    }
    void reset(T* p)
    {
        if (this->m_p != nullptr)
            delete this->m_p;
        this->m_p = p;
    }
    T* release()
    {
        T* p = this->get();
        this->m_p = nullptr;
        return p;
    }
    ~UniquePtr()
    {
        if (this->m_p != nullptr)
            delete this->m_p;
        this->m_p = nullptr;
    }
private:
    T* m_p;
};

template <typename T>
T* make_unique(const T& val)
{
    return new T(val);
}

#endif //UNIQUE_PTR
