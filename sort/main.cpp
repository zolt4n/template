#include <utility>

template <int... members>
class ARRAY
{
public:
    static constexpr auto sort()
    {
        return _sort(std::make_index_sequence<sizeof...(members)>());
    }

    constexpr bool operator==(ARRAY) const { return true; }

    template<int... others>
    constexpr bool operator==(ARRAY<others...>) const { return false; }

private:
    // return the index of the first occurrence of x in the sorted ARRAY
    template<int x>
    static constexpr int indexOf()
    {
        int sum {};
        ((x > members ? ++sum : 0), ...);
        return sum;
    }

    // count x occurrences.
    template<int x>
    static constexpr int count()
    {
        int sum {};
        ((x == members ? ++sum : 0), ...);
        return sum;
    }

    // return element at index i in the sorted array.
    template<int i>
    static constexpr int getValue()
    {
        int result{};
        // handle duplicates since indexOf only return the 1st occurrence we need to check the range.
        ((i >= indexOf<members>() && i < indexOf<members>() + count<members>() ? result = members : 0), ...);
        return result;
    }

    template<std::size_t... i>
    static constexpr auto _sort(std::index_sequence<i...>)
    {
        return ARRAY< getValue<i>()... >();
    }
};

int main() {
    static_assert(ARRAY<>().sort() == ARRAY<>(), "");
    static_assert(ARRAY<4, 7, 5, 2, 2, -1>().sort() == ARRAY<-1, 2, 2, 4, 5, 7>(), "");
    static_assert(ARRAY<4, 7, 5, 2, 1, 1>().sort() != ARRAY<1, 2, 4, 5, 7>(), "");
    static_assert(ARRAY<4, 7, 5, 2, -1, 1, -1, 1>().sort() == ARRAY<-1, -1, 1, 1, 2, 4, 5, 7>(), "");
}
