#include <memory>
#include <iostream>
#include <atomic>

// 定义一个callable对象类作为默认删除器
template<typename T>
class default_deleter
{
public:
    void operator()(T* pObject)
    {
        delete pObject;
    }
};

template<typename T, typename deleter = default_deleter<T>>
class SharedPtr
{
public:
    //-默认构造
    SharedPtr() = default;
    //-原生指针构造
    SharedPtr(T* pObject)
        :m_pObject(pObject), m_pRefCount(new std::atomic<int>(1))
    {

    }

    //-拷贝构造
    SharedPtr(const SharedPtr& lsh)
    {
        m_pObject = lsh.m_pObject;
        m_pRefCount = lsh.m_pRefCount;
        ++*m_pRefCount;
    }

    //-移动构造
    SharedPtr(SharedPtr&& lsh)
    {
        m_pObject = lsh.m_pObject;
        m_pRefCount = lsh.m_pRefCount;
        lsh.m_pObject = NULL;
        lsh.m_pRefCount = NULL;
    }

    //-拷贝赋值运算符
    SharedPtr& operator=(const SharedPtr& lsh)
    {
        if(this != &lsh) 
        {
            if(m_pObject)
            {
                --*m_pRefCount;
                if(*m_pRefCount <= 0)
                {
                    deleter()(m_pObject);
                    delete m_pRefCount;
                }
                m_pObject = nullptr;
                m_pRefCount = nullptr;
            }
            m_pObject = lsh.m_pObject;
            m_pRefCount = lsh.m_pRefCount;
            ++*m_pRefCount;
        }
        return *this;
    }

    //-移动赋值运算符
    SharedPtr& operator=(SharedPtr&& lsh)
    {
        if(this != &lsh) 
        {
            if(m_pObject)
            {
                --*m_pRefCount;
                if(*m_pRefCount <= 0)
                {
                    deleter()(m_pObject);
                    delete m_pRefCount;
                }
                m_pObject = nullptr;
                m_pRefCount = nullptr;
            }
            m_pObject = lsh.m_pObject;
            m_pRefCount = lsh.m_pRefCount;
            lsh.m_pObject = NULL;
            lsh.m_pRefCount = NULL;
        }
        return *this;
    }

    //-析构
    ~SharedPtr()
    {
        if(m_pObject)
        {
            --*m_pRefCount;
            if(*m_pRefCount <= 0)
            {
                deleter()(m_pObject);
                delete m_pRefCount;
            }
        }
    }

    //-箭头函数运算符重载
    T* operator->()
    {
        return m_pObject;
    }

    //-解引用运算符重载
    T& operator*()
    {
        return *m_pObject;
    }

    //-交换
    void swap(SharedPtr& lsh)
    {
        std::swap(m_pObject, lsh.m_pObject);
        std::swap(m_pRefCount,lsh.m_pRefCount);
    }

    //-解除对当前指针的管理, 如果有新的pObject则托管新的指针
    void reset(T* pObject = nullptr)
    {
        if(m_pObject)
        {
            //-如果当前SharedPtr有托管对象，先释放原托管
            --*m_pRefCount;
            if(*m_pRefCount <= 0)
            {
                deleter()(m_pObject);
                delete m_pRefCount;
            }
            m_pObject = nullptr;
            m_pRefCount = nullptr;
        }
        //-是否有新托管
        if(pObject)
        {
            m_pObject = pObject;
            m_pRefCount = new std::atomic<int>(1);
        }
    }

    //-获取引用计数
    int count()
    {
        return *m_pRefCount;
    }

    //-获取原生指针
    T* get()
    {
        return m_pObject;
    }
private:
    //-原生堆指针
    T* m_pObject = nullptr;
    //-指向use_count的指针
    std::atomic<int>* m_pRefCount = nullptr;
};

//-测试类
class Student
{
public:
    int id;
    int age;
    Student(int id_, int age_)
        :id(id_), age(age_)
    {

    }
};

void print(SharedPtr<Student>& s)
{
    if(s.get() == nullptr)
    {
        std::cout << "nullptr" << std::endl;
        return;
    }
    std::cout << "id:" << s->id << "  " << "age:" << s->age << std::endl;
    std::cout << "use count:" << s.count() << std::endl;
}

int main(int argc, char *argv[])
{
    {
        std::cout << "拷贝构造测试，解引用，箭头函数测试" << std::endl;
        SharedPtr<Student> s1(new Student(0, 18));
        SharedPtr<Student> s2(s1);
        (*s1).age = 19;
        print(s2);
        std::cout << "自赋值测试" << std::endl;
        s1 = s1;
        print(s1);
    }

    {
        std::cout << "测试reset" << std::endl;
        SharedPtr<Student> s1(new Student(0, 18));
        s1.reset();
        print(s1);
        s1.reset(new Student(1, 19));
        print(s1);

    }
    {
        std::cout << "移动构造测试" << std::endl;
        SharedPtr<Student> s0(new Student(0, 18));
        SharedPtr<Student> s1 = std::move(s0);
        print(s0);
        print(s1);

        std::cout << "拷贝赋值运算符测试" << std::endl;
        SharedPtr<Student> s2;
        s2 = s1;
        print(s1);
        print(s2);

        std::cout << "移动赋值运算符测试" << std::endl;
        SharedPtr<Student> s3 (new Student(2, 20));
        s1 = std::move(s3);
        print(s1);
        print(s3);
    }
    return 0;
}