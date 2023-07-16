#pragma once

#include <type_traits>

namespace Pilot
{

    template<typename T>
    class PublicSingleton
    {
    protected:
        //tell the compiler to generate the default constructor
        PublicSingleton() = default;

    public:
        // does not allow getInstance to throw exceptions if T is nothrow constructible
        static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value)
        {
            static T instance;
            return instance;
        }

        //The destructor can not throw any exception and it is telling the compiler to generate the default destructor
        virtual ~PublicSingleton() noexcept = default;

        //tell the compiler not to generate the copy constructor and the copy assignment operator
        PublicSingleton(const PublicSingleton&) = delete;
        PublicSingleton& operator=(const PublicSingleton&) = delete;
    };
} // namespace Pilot
