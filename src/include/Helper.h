#pragma once

namespace RanGui
{
    namespace Helper
    {
        template <class T>
        void SafeRelease(T **ppT)
        {
            if (*ppT)
            {
                (*ppT)->Release();
                *ppT = nullptr;
            }
        }

        template <class T>
        void SafeDelete(T **ppT)
        {
            if (*ppT)
            {
                delete *ppT;
                *ppT = nullptr;
            }
        }

        template <class T>
        void SafeDeleteArray(T **ppT)
        {
            if (*ppT)
            {
                delete[] *ppT;
                *ppT = nullptr;
            }
        }

        template <class T>
        T Min(const T &a, const T &b)
        {
            return a < b ? a : b;
        }

        template <class T>
        T Max(const T &a, const T &b)
        {
            return a > b ? a : b;
        }
    }
}