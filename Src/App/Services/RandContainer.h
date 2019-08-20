#pragma once

// Std libs
#include <random>
#include <string>
#include <memory>


namespace App::Services
{

    class RandContainer
    {
    public:

        RandContainer()
            :   m_generator(*new std::random_device)
        {

        }


        ~RandContainer()
        {

        }


        // Type of RNG
        enum class Distributions
        {
            UniformInt,
            ExponentialDouble
        };


        // Get return type
        template<typename T>
        struct Return
        {
            bool status;
            T value;

            T operator->()
            {
                return value;
            }

            operator T const()
            {
                return value;
            }

        };


        /**
         * Setup a random number generator which requires min and max parameters
         */
        bool create(Distributions distri, int min, int max)
        {
            // Delete object if it already exists
            erase(distri);

            switch(distri)
            {
            case Distributions::UniformInt:
                m_uniformInt = std::make_unique<std::uniform_int_distribution<int>>(min, max);
                break;
            default:
                // Incorrect paramters for selected type
                return false;
            }

            return true;
        }


        /**
         * Setup a random number generator which requires a scale
         */
        bool create(Distributions distri, double scale)
        {
            // Delet object if it already exists
            erase(distri);

            switch(distri)
            {
            case Distributions::ExponentialDouble:
                m_ExponentialDouble = std::make_unique<std::exponential_distribution<double>>(scale);
                break;
            default:
                // Incorrect paramters for selected type
                return false;
            }

            return true;
        }


        /**
         * Get a random number genertor
         */
        template<typename T>
        Return<T> get(Distributions distri)
        {
            // Create return
            Return<T> i;

            // Assume failure
            i.status = false;
            i.value = 0;

            switch(distri)
            {
            case Distributions::UniformInt:
                // Check setup
                if(m_uniformInt != nullptr && typeid(T) == typeid(int))
                {
                    // Update return struct
                    i.status = true;
                    i.value = (*m_uniformInt)(m_generator);
                }
                break;
            case Distributions::ExponentialDouble:
                // Check setup
                if(m_ExponentialDouble != nullptr && typeid(T) == typeid(double))
                {
                    // Update return struct
                    i.status = true;
                    i.value = (*m_ExponentialDouble)(m_generator);
                }
                break;
            }

            return i;
        }

        template<typename T>
        T max(Distributions distri)
        {
            switch(distri)
            {
            case Distributions::UniformInt:
                    return static_cast<T>(m_uniformInt->max());
                break;
            case Distributions::ExponentialDouble:
                    return m_ExponentialDouble->max();
                break;
            }

            return T(0);
        }

        void erase()
        {
            m_uniformInt.reset(nullptr);
            m_ExponentialDouble.reset(nullptr);
        }

        void erase(Distributions distribution)
        {
            switch(distribution)
            {
            case Distributions::UniformInt:
                m_uniformInt.reset(nullptr);
                break;
            case Distributions::ExponentialDouble:
                m_ExponentialDouble.reset(nullptr);
                break;
            }
        }



    private:

        // Generator
        std::random_device& m_generator;

        // Save instances
        std::unique_ptr<std::uniform_int_distribution<int>> m_uniformInt = nullptr;
        std::unique_ptr<std::exponential_distribution<double>> m_ExponentialDouble = nullptr;

    };

}

