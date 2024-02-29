# C++11智能指针

## 一、C++智能指针
- 资源获取即初始化(Resource Acquisition Is Initialization，简称RAII)是一种C++编程技术，将使用前获取的资源(如分配的堆内存、执行线程、打开的套接字、打开的文件、锁定的互斥量、磁盘空间、数据库连接等有限资源)的生命周期与某个对象的生命周期绑定在一起，确保在控制对象的生命周期结束时，按照资源获取的相反顺序释放所有资源。
- 如果资源获取失败(构造函数退出并带有异常)，则按照初始化的相反顺序释放所有已完全构造的成员和基类子对象所获取的资源。
- RAII核心思想是利用栈上局部变量的自动析构来保证资源一定会被释放，充分利用了核心语言特性(对象生命周期、作用域退出、初始化顺序和堆栈展开)，以消除资源泄漏并确保异常安全。
- C++智能指针的实现充分利用了RAII特性。
    - unique_ptr独占对象的所有权，由于没有引用计数，因此性能较好。
    - shared_ptr共享对象的所有权，但性能略差。
    - weak_ptr配合shared_ptr，解决循环引用的问题。
## 二、shared_ptr
### 1、shared_ptr
- share_ptr是C++11引入的智能指针，share_ptr限定的资源可以被多个指针共享，只有指向动态分配的对象的指针才能交给shared_ptr对象托管。将指向普通局部变量、全局变量的指针交给shared_ptr托管，编译时不会有问题，但程序运行时会出错，因为不能析构一个并没有指向动态分配的内存空间的指针。

### 2、shared_ptr实现
- shared_ptr实现原理：通过引用计数的方式来实现多个shared_ptr对象之间共享资源。
- 有两种创建shared_ptr对象的方式：
    ```cpp
    auto p = std::shared_ptr<T>(new T);
    auto p = std::make_shared<T>(T{});
    ```
- shared_ptr在其内部，会为所管理的资源维护一份计数，并记录资源被多少个shared_ptr对象共享。当shared_ptr对象被销毁时(析构函数调用)，说明shared_ptr对象不再使用资源，shared_ptr对象的引用计数减一。如果引用计数是0，必须释放资源；如果不是0，说明有其它shared_ptr对象在使用资源，不能释放资源。
```cpp
#include <iostream>
#include <memory>
 
int main() 
{
  auto p = std::make_shared<int>(4);
  auto p1 = std::shared_ptr<int>(new int(4));
  std::cout << *p << *p1 << "\n";
  return 0;
}
```
- shared_ptr对象p1的内存布局如下：
    ![](image\shared_ptr1.png)
    - std::shared_ptr本身只包含两个对象：指向控制块对象的Ctr指针和一个指向其管理的资源的指针Ptr。
    - 当采用std::shared_ptr<T>(new T{})形式创建shared_ptr对象时，其控制块对象中会包含一个M_ptr成员，M_ptr指针指向智能指针所管理的资源。
    - 控制块对象至少会包含use_count(引用计数)、weak_count(弱引用计数)以及其它数据这三部分内容。

- shared_ptr对象p的内存布局如下：
    ![](image\shared_ptr2.png)
    - 当采用std::make_shared创建shared_ptr对象时，其控制块对象和被管理资源被存放在同一个内存块中。
    - 当采用std::make_shared创建shared_ptr对象时，其控制块对象中不会包含M_ptr成员(指向智能指针所管理的资源)。
- shared_ptr的拷贝构造函数会增加引用计数，而移动构造函数不会增加引用计数。
    ```cpp
    #include <iostream>
    #include <memory>
    
    int main() {
    auto p = std::make_shared<int>(4);
    auto p1 = p;
    std::cout << "p use_count: " << p.use_count() << "\n";
    auto p2 = std::move(p);
    std::cout << "p use_count: " << p1.use_count() << "\n";
    return 0;
    }
    ```
- shared_ptr自定义实现如下：
    ```cpp
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
    ```

### 3、shared_ptr API
- shared_ptr<T>构造函数：创建一个空的shared_ptr，不指向任何对象。
```cpp
std::shared_ptr<int> ptr;
```
- make_shared<T>(args...)：创建一个shared_ptr，并在单次内存分配中同时创建对象和控制块，比直接使用shared_ptr的构造函数要高效。
```cpp
std::shared_ptr<int> ptr = std::make_shared<int>(42);
```
- reset()：释放当前shared_ptr的所有权，将其设置为nullptr。如果当前shared_ptr是最后一个拥有对象所有权的智能指针，则会删除对象。
```cpp
ptr.reset();
```
- reset(T*)：释放当前shared_ptr的所有权，并使其指向新的对象。如果当前shared_ptr是最后一个拥有对象所有权的智能指针，则会删除原对象。
```cpp
ptr.reset(new int(42));
```
- get()：返回指向的对象的裸指针。裸指针的生命周期由shared_ptr管理，不应该使用它来创建另一个智能指针。
```cpp
int* raw_ptr = ptr.get();
```
- operator* 和 operator->：访问指向的对象。
```cpp
int value = *ptr;
std::shared_ptr<std::vector<int>> vec_ptr = std::make_shared<std::vector<int>>();
vec_ptr->push_back(42);
```
- use_count()：返回当前shared_ptr的引用计数，即有多少个shared_ptr共享同一个对象。注意，use_count()通常用于调试，不应该用于程序逻辑。
```cpp
size_t count = ptr.use_count();
```
- unique()：检查当前shared_ptr是否是唯一拥有对象所有权的智能指针。等价于use_count() == 1。
```cpp
bool is_unique = ptr.unique();
```
- swap(shared_ptr&)：交换两个shared_ptr的内容。
```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
std::shared_ptr<int> ptr2 = std::make_shared<int>(24);
ptr1.swap(ptr2);
```
- operator bool()：将shared_ptr隐式转换为bool类型，用于检查其是否为空。
```cpp
if (ptr) {
    std::cout << "ptr 不为空" << std::endl;
} else {
    std::cout << "ptr 为空" << std::endl;
}
```
### 4、shared_ptr使用
```cpp
#include <iostream>
#include  <memory> // 共享指针必须要包含的头文件
using namespace std;
int main()
{
	// 最好使用make_shared创建共享指针，
	shared_ptr<int> p1 = make_shared<int>();//make_shared 创建空对象，
	*p1 = 10;
	cout << "p1 = " << *p1 << endl; // 输出10

	// 打印引用个数：1
	cout << "p1 count = " << p1.use_count() << endl;
	
	// 第2个 shared_ptr 对象指向同一个指针
	std::shared_ptr<int> p2(p1);
	
	// 输出2
	cout << "p2 count = " << p2.use_count() << sendl;
	cout << "p1 count = " << p1.use_count() << endl;

	// 比较智能指针，p1 等于 p2
	if (p1 == p2) {
		std::cout<< "p1 and p2 are pointing to same pointer\n";
	}
	
	p1.reset();// 无参数调用reset，无关联指针，引用个数为0
	cout << "p1 Count = " << p1.use_count() << endl;
	
	p1.reset(new int(11));// 带参数调用reset，引用个数为1
	cout << "p1 Count = " << p1.use_count() << endl;

	p1 = nullptr;// 把对象重置为NULL，引用计数为0
	cout << "p1  Reference Count = " << p1.use_count() << endl;
	if (!p1) {
		cout << "p1 is NULL" << endl; // 输出
	}
	return 0;
}
```

- 在初始化shared_ptr智能指针时，可以自定义所指堆内存的释放规则，当堆内存的引用计数为0时，会优先调用自定义的释放规则。
- 对于申请动态数组，shared_ptr指针默认的释放规则是不支持释放数组的，只能自定义对应的释放规则，才能正确地释放申请的堆内存。
- 对于申请动态数组，释放规则可以使用C++11标准中提供的default_delete<T>模板类，也可以自定义释放规则。
    ```cpp
    // 指定default_delete作为释放规则
    std::shared_ptr<int> p6(new int[10], std::default_delete<int[]>());
    // 自定义释放规则
    void deleteInt(int* p) {
        delete [] p;
    }
    // 初始化智能指针，并自定义释放规则
    std::shared_ptr<int> p7(new int[10], deleteInt);
    //  初始化智能指针，并使用Lambda自定义释放规则
    std::shared_ptr<int> p7(new int[10], [](int* p) {delete[]p; });
    ```

- shared_ptr的类型转换应该使用专门用于shared_ptr类型转换的接口，如果使用一般的static_cast进行的转换将会导致转换后的指针无法再被shared_ptr对象正确管理。
    ```cpp
    static_pointer_cast<T>() 
    const_pointer_cast<T>() 
    dynamic_pointer_cast<T>()
    ```

- shared_ptr的double free问题：
    - 直接使用原始指针创建多个shared_ptr，而没有使用shared_ptr的make_shared工厂函数，从而导致多个独立的引用计数。
    - 循环引用，即两个或多个shared_ptr互相引用，导致引用计数永远无法降为零，从而无法释放内存。
- shared_ptr double free问题解决方案：
    - 使用make_shared函数创建shared_ptr实例，而非直接使用原始指针，确保所有shared_ptr实例共享相同的引用计数。
    - 使用weak_ptr避免循环引用导致的内存泄漏问题。weak_ptr是一种不控制对象生命周期的智能指针，只观察对象，而不增加引用计数。
### 5、shared_ptr注意事项
- shared_ptr使用注意事项如下：
    - 不能使用原始指针初始化多个shared_ptr。
    - 不要使用栈中的指针构造shared_ptr对象。
    - 不要使用shared_ptr的get()方法返回指针初始化或reset另一个shared_ptr。
    - 不要把this指针给shared_ptr。
    - 不要在函数实参里创建shared_ptr。
    - 环状的链式结构shared_ptr将会导致内存泄漏(可以结合weak_ptr来解决)；
    - 共享拥有权的对象一般比限定作用域的对象生存更久，从而将导致更高的平均资源使用时间。
    - 多线程环境中使用shared_ptr的代价非常大，因为需要避免关于引用计数的数据竞争。
    - 不使用相同的内置指针值初始化(或reset)多个shared_ptr对象。
    - 不要delete get()返回的指针。
    - 如果智能指针管理的资源不是new分配的内存，记住传递给它一个删除器。

- shared_ptr的引用计数本身是安全且无锁的，但对象的读写则不是，因为shared_ptr 有两个数据成员，读写操作不能原子化。shared_ptr的线程安全级别和内建类型、标准库容器、std::string一样，即：
    - 一个shared_ptr对象实体可被多个线程同时读取。
    - 两个shared_ptr对象实体可以被两个线程同时写入，析构算写操作。
    - 如果要从多个线程读写同一个shared_ptr对象，那么需要加锁。


### 6、enable_shared_from_this
- shared_ptr不能直接从this指针进行构造shared_ptr对象。如果需要返回this指针，可以通过继承enable_shared_from_this类，调用方法shared_from_this实现。
```cpp
#include <iostream>
#include <memory>
 
class Good : public std::enable_shared_from_this<Good>
{
public:
    std::shared_ptr<Good> GetSelf()
    {
        return shared_from_this();
    }
};

int main()
{
    Good* pGood = new Good();
    shared_ptr<Good> p1(pGood);
    shared_ptr<Good> p2 = pGood->GetSelf();
    std::cout << p1.use_count() << std::endl;
    std::cout << p2.use_count() << std::endl;
    return 0;
}
```
- enable_shared_from_this使用注意事项：
    - 必须以public继承std::enable_shared_from_this。
    - 在使用shared_from_this()接口时，必须已经存在相应的控制块。


## 三、weak_ptr
### 1、weak_ptr
- std::weak_ptr是C++11引入的一个不拥有所有权的智能指针，与std::shared_ptr配合使用，主要用于解决循环引用问题、观察std::shared_ptr对象而不影响引用计数，以及在需要时提供对底层资源的访问。
    - 解决循环引用问题：当两个或多个std::shared_ptr对象互相引用时，会导致循环引用，从而导致内存泄漏。std::weak_ptr不会增加引用计数，可以打破循环引用，只需要将其中一个对象的std::shared_ptr替换为std::weak_ptr，即可解决循环引用问题。
    - 观察std::shared_ptr对象：std::weak_ptr可以用作观察者，监视std::shared_ptr对象的生命周期。std::weak_ptr不会增加引用计数，因此不会影响资源的释放。

- weak_ptr指针通常不单独使用，只能和shared_ptr类型指针搭配使用。将一个weak_ptr绑定到一个shared_ptr不会改变shared_ptr的引用计数。一旦最后一个指向对象的shared_ptr被销毁，对象就会被释放，即使有weak_ptr指向对象，对象也还是会被释放。

### 2、weak_ptr API
- use_count：返回shared_ptr的引用计数
- expired：检查是否shared_ptr所管理的资源已经被删除
- lock：生成一个shared_ptr。如果需要访问weak_ptr所指向的对象，需要将std::weak_ptr通过weak_ptr::lock()临时转换为std::shared_ptr。在使用lock()方法前，应当检查使用std::weak_ptr::expired()检查std::weak_ptr是否有效，即它所指向的对象是否仍然存在。


## 四、unique_ptr
### 1、unique_ptr
- std::unique_ptr是一个独占所有权的智能指针，保证指向的内存只能由一个unique_ptr拥有，不能共享所有权。
- unique_ptr对象包装一个原始指针，并负责其生命周期。当unique_ptr对象被销毁时，会在其析构函数中删除关联的原始指针。
- unique_ptr具有->和*运算符重载符，可以像普通指针一样使用。
    - unique_ptr不能被复制到另外一个unique_ptr。
    - unique_ptr所持有的对象只能通过转移语义将所有权转移到另外一个unique_ptr。

### 2、unique_ptr实现
```cpp
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
		if(nullptr ！= m_pObject) 
        {
            delete m_pObject;
            m_pObject = nullptr;
        }
	}

public:
	void reset(T* pObject) // 先释放资源(如果持有), 再持有资源
	{
		if(nullptr ！= m_pObject) 
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
```

### 3、unique_ptr使用
- unique_ptr不像shared_ptr一样拥有标准库函数make_shared来创建一个shared_ptr实例。要想创建一个unique_ptr对象，需要将一个new操作符返回的指针传递给unique_ptr的构造函数。
- unique_ptr没有copy构造函数，不支持普通的拷贝和赋值操作。
- unique_ptr虽然没不支持普通的拷贝和赋值操作，但却提供了一种移动机制来将指针的所有权从一个unique_ptr转移给另一个unique_ptr。如果需要转移所有权，可以使用std::move()函数。
- unique_ptr不支持拷贝操作，但却有一个例外：可以从函数中返回一个unique_ptr。

```cpp
 unique_ptr<int> pInt(new int(5));
 unique_ptr<int> pInt2 = std::move(pInt); // 转移所有权
 //cout << *pInt << endl; // 出错，pInt为空
 cout << *pInt2 << endl;
 unique_ptr<int> pInt3(std::move(pInt2));
```
