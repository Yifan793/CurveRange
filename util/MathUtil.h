#ifndef MATHUTIL_H
#define MATHUTIL_H


class MathUtil
{
public:
    //比较double值， d1<d2返回-1,  d1==d2返回0,  d1>d2返回1
    static int compare(double d1, double d2, double dEsp = 1e-6);

    template <typename T>
    static T varMax(T val1, T val2)
    {
        return val1 > val2 ? val1 : val2;
    }
    template <typename T, typename... Args>
    static T varMax(T val, Args... arg)
    {
        T result = varMax(arg...);
        return varMax(val, result);
    }
    template <typename T>
    static T varMin(T val1, T val2)
    {
        return val1 < val2 ? val1 : val2;
    }
    template <typename T, typename... Args>
    static T varMin(T val, Args... arg)
    {
        T result = varMin(arg...);
        return varMin(val, result);
    }
};

#endif // MATHUTIL_H
