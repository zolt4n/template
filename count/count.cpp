//
// Created by Zozo on 09/02/2021.
//

template<int ...numbers>
class SUM
{
public:
    static constexpr int sum()
    {
        int sum{};
        ((sum += numbers), ...);
        return sum;
    }
};

template <int... numbers>
struct REC_SUM;

template<int N, int ...numbers>
struct REC_SUM<N, numbers...>
{
    static constexpr int sum()
    {
        return N + REC_SUM<numbers...>().sum();
    }
};

template<int N>
struct REC_SUM<N>
{
    static constexpr int sum()
    {
        return N;
    }
};

int main()
{
    static_assert(SUM<1,2,3,5>().sum() == 11);
    static_assert(SUM<1,2,3,5>().sum() != 0);

    static_assert(REC_SUM<1,2,3,5>().sum() == 11);
    static_assert(REC_SUM<1,2,3,5>().sum() != 0);
}