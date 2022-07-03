//
//  Allocator.h
//  RSCore
//
//  Created by Ruben Ticehurst-James on 02/07/2022.
//

#ifndef Allocator_h
#define Allocator_h

/*
 
 This is an allocator for allocating contigious blocks
 It should be used as a subclass as by itself it will
 not hit the destructor of any of the classes.
 
 to allocate contigious blocks, use allocate
 You should call destroy before deallocating as that calls
 the destructor
 
 
 */

#include <system_error>


namespace core {
	template <class T>
	class Allocator {
		public:

		
			~Allocator() {
				::operator delete(data, sizeof(T) * allocated_size);
			}
		
			T & operator[](int index) const {
				if (allocated_size < index) {
					throw std::runtime_error("[ALLOCATOR] - attempt to access out of bounds index");
				}
				return data[index];
			}
		
			void allocate(int blocks) {
				T * newAddress = (T *)(::operator new(sizeof(T) * blocks));
				
				if (data != nullptr) {
					for (int i = 0; i < allocated_size; i ++) {
						newAddress[i] = data[i];
					}
//					memmove(newAddress, data, allocated_size * sizeof(T));
					::operator delete(data, sizeof(T) * allocated_size);
				}
				
				data = newAddress;
				allocated_size = blocks;
			}
		
			void destroy(int index) {
				data[index].~T();
			}
		
			int allocatedSize() {
				return allocated_size;
			}

		
		protected:
			mutable T * data = nullptr;
			int allocated_size = 0;
			
	};
}

#endif /* Allocator_h */
