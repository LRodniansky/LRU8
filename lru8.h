#include <string>

namespace LRDN {

template <typename Key, typename Value> class LRU8 {
	private:
		uint64_t _lru_matrix;
		unsigned char _dirty;
		Key   arr_keys[8];
		Value arr_values[8];

		void set_bits(int idx) {
			_lru_matrix |= (0xFF00000000000000UL>>(8*idx));
			_lru_matrix &=~(0x8080808080808080UL>>idx);
		}

		int find(const Key& k) const {
			int ret = -1;

			for (int i = 0; i<8; i++) {
				if ((_dirty&(0x1U<<i))&&arr_keys[i]==k) {
					ret = i;
					break;
				}
			}

			return ret;
		}

		Value& insert(const Key& k, const Value& v) {

			int idx = least_used_slot();					
			arr_keys[idx] = k;
			arr_values[idx] = v;
			set_bits(idx);
			_dirty |= (0x1U<<idx);

			return arr_values[idx];
		}

		int least_used_slot() { 
			if ((_lru_matrix>>56)==0) return 0;
			else if ((_lru_matrix&0x00FF000000000000UL)==0) return 1;
			else if ((_lru_matrix&0x0000FF0000000000UL)==0) return 2;
			else if ((_lru_matrix&0x000000FF00000000UL)==0) return 3;
			else if ((_lru_matrix&0x00000000FF000000UL)==0) return 4;
			else if ((_lru_matrix&0x0000000000FF0000UL)==0) return 5;
			else if ((_lru_matrix&0x000000000000FF00UL)==0) return 6;
			else if ((_lru_matrix&0x00000000000000FFUL)==0) return 7;
			else return 0;	// This should not happen.
		}

	public:
		LRU8():_lru_matrix(0ULL),_dirty(0x00) {;}
		virtual ~LRU8() {;}

		size_t size() const {
			return 8U;
		}

		bool exists(const Key& k) const {
			int idx = find(k);

			return (idx>=0);
		}

		Value& operator[](const Key& k) {

			int idx = find(k);

			if (idx<0) {
				// create a new entry
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
				Value v;
				return insert(k,v);
#pragma GCC diagnostic pop
			} else {
				set_bits(idx);
				return arr_values[idx];
			}
		}
};

} // namespace LRDN
