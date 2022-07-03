//
//  Array.h
//  RSwDE
//
//  Created by Ruben Ticehurst-James on 02/07/2022.
//

#ifndef Array_h
#define Array_h

#include "Allocator.h"

namespace core {
	template <class T>
	class Array : public Allocator<T> {
		public:
		Array(int initial_size = 2, int expansion_size = 2, bool resizable = true) : Allocator<T>(),
			used_size(0), expansion_size(expansion_size), resizable(resizable)
		{
			Allocator<T>::allocate(initial_size);
		}
		
		Array(const Array & toCopy): Allocator<T>(), used_size(toCopy.used_size), expansion_size(toCopy.expansion_size), resizable(toCopy.resizable) {
			
			Allocator<T>::allocate(toCopy.allocated_size);
			for (int i = 0; i < toCopy.used_size; i ++) {
				T copied (toCopy.data[i]);
				Allocator<T>::data[i] = copied;
			}
//			used_size = toCopy.used_size;
		}
		
		void operator=(Array<T>& other) {
			Allocator<T>::allocate(other.Allocator<T>::allocated_size);
			for(int i = 0; i < other.size(); i ++) {
				T copied (other.data[i]);
				Allocator<T>::data[i] = copied;
			}
			
			
			
		}
		
		~Array() {
			for(int i = 0; i < used_size; i ++) {
				Allocator<T>::destroy(i);
			}
		}
		
		void add(T element) {
			
			if (used_size + 1 > Allocator<T>::allocatedSize()){
				Allocator<T>::allocate(1 + Allocator<T>::allocatedSize() + expansion_size);
			}
			Allocator<T>::operator[](used_size++) = element;
			
		}
		
		int size() const {
			return used_size;
		}
		
		void operator += (const Array<T> & rhs) {
			for(int i = 0; i < rhs.size(); i ++) {
				add(rhs[i]);
			}
		}
		
		private:
			int used_size;
			int expansion_size;
			bool resizable;
		
		
	};
}

#endif /* Array_h */
