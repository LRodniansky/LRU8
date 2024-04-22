/*
MIT License

Copyright (c) 2024 Leonid Rodniansky

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <cstdint>
#include <cstddef>

namespace LRDN {

template <typename Key, typename Value>
class LRU8 {
private:
    std::uint64_t _lru_matrix;
    unsigned char _dirty;
    Key arr_keys[8];
    Value arr_values[8];

    void set_bits(int idx) {
        _lru_matrix |=  (0xFF00000000000000ULL >> (8 * idx));
        _lru_matrix &= ~(0x8080808080808080ULL >> idx);
    }

    int find(const Key &k) const {
        int ret = -1;

        for (int i = 0; i < 8; i++) {
            if ((_dirty & (0x1U << i)) && arr_keys[i] == k) {
                ret = i;
                break;
            }
        }

        return ret;
    }

    Value &insert(const Key &k, const Value &v) {

        int idx = least_used_slot();
        arr_keys[idx] = k;
        arr_values[idx] = v;
        set_bits(idx);
        _dirty |= (0x1U << idx);

        return arr_values[idx];
    }

    int least_used_slot() {
        if ((_lru_matrix >> 56) == 0)
            return 0;
        else if ((_lru_matrix & 0x00FF000000000000ULL) == 0)
            return 1;
        else if ((_lru_matrix & 0x0000FF0000000000ULL) == 0)
            return 2;
        else if ((_lru_matrix & 0x000000FF00000000ULL) == 0)
            return 3;
        else if ((_lru_matrix & 0x00000000FF000000ULL) == 0)
            return 4;
        else if ((_lru_matrix & 0x0000000000FF0000ULL) == 0)
            return 5;
        else if ((_lru_matrix & 0x000000000000FF00ULL) == 0)
            return 6;
        else if ((_lru_matrix & 0x00000000000000FFULL) == 0)
            return 7;
        else
            return 0; // This should not happen.
    }

public:
    LRU8() : _lru_matrix(0ULL), _dirty(0x00) {}
    virtual ~LRU8() {}

    std::size_t size() const {
        return 8UL;
    }

    bool exists(const Key &k) const {
        return (find(k) >= 0);
    }

    Value &operator[](const Key &k) {

        int idx = find(k);

        if (idx < 0) {
            // create a new entry
            Value v{};
            return insert(k, v);
        } else {
            set_bits(idx);
            return arr_values[idx];
        }
    }
};

} // namespace LRDN

