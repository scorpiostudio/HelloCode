#include <memory>
#include <iostream>

template<typename T>
class UniquePtr
{
public:
	UniquePtr(T *pObject = NULL)
		: m_pObject(pObject)
	{

	}

	~UniquePtr()
	{
		if(nullptr != m_pObject) 
		{
			delete m_pObject;
			m_pObject = nullptr;
		}
	}

public:
	void reset(T* pObject) // 先释放资源(如果持有), 再持有资源
	{
		if(nullptr != m_pObject) 
		{
			delete m_pObject;
			m_pObject = nullptr;
		}
		m_pObject = pObject;
	}

	T* release() // 返回资源，资源的释放由调用方处理
	{
		T* pTemp = m_pObject;
		m_pObject = nullptr;
		return pTemp;
	}

	T* get() // 获取资源，调用方应该只使用不释放，否则会两次delete资源
	{
		return m_pObject;
	}

public:
	operator bool() const // 是否持有资源
	{
		return m_pObject != nullptr;
	}

	T& operator * ()
	{
		return *m_pObject;
	}

	T* operator -> ()
	{
		return m_pObject;
	}
private:
	UniquePtr(const UniquePtr &) = delete; // 禁用拷贝构造
	UniquePtr& operator = (const UniquePtr &) = delete; // 禁用拷贝赋值
private:
	T* m_pObject;
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

void print(UniquePtr<Student>& s)
{
    if(s.get() == nullptr)
    {
        std::cout << "nullptr" << std::endl;
        return;
    }
    std::cout << "id:" << s->id << "  " << "age:" << s->age << std::endl;
}

int main(int argc, char *argv[])
{
    {
        UniquePtr<Student> s1(new Student(0, 18));
        // UniquePtr<Student> s2 = std::move(s1);
        // UniquePtr<Student> s3 = std::move(s2);
        print(s1);

    }
    return 0;
}
