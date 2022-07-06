//
//  Allocator.h
//  RSCore
//
//  Created by Ruben Ticehurst-James on 02/07/2022.
//

#ifndef Allocator_h
#define Allocator_h


#include <system_error>
#include "Output.h"

namespace core {
	template <typename T>
	class Allocator {
		public:
			typedef unsigned long index_type;
			
		
			/**
			 Creates an allocator. Initally pointing to unallocated data.
			 */
			Allocator() : data(nullptr), allocated(0) {}
	
		
			Allocator(const Allocator & copy) {
				allocate(copy.allocatedSize());
				for (index_type i = 0; i < copy.allocatedSize(); i ++) {
					operator[](i) = copy[i];
				}
			}
			
			Allocator(Allocator && move) {
				data = move.data;
				allocated = move.allocatedSize();
			}
			
			Allocator & operator = (const Allocator & copy) {
				allocate(copy.allocatedSize());
				for (index_type i = 0; i < copy.allocatedSize(); i ++) {
					operator[](i) = copy[i];
				}
				return *this;
			}
			
			Allocator & operator = (Allocator && move) {
				data = move.data;
				allocated = move.allocatedSize();
				move.data = nullptr;
				return *this;
			}
			
		
			
			/**
			 Destructor. Will free the amount of memory allocated
			 
			 Notes:
				- Does not hit the destructor of the objects in its allocation. That should be done by calling ::destroy(index: )
			 */
			~Allocator() {
				::operator delete(data, allocated * sizeof(T));
			}
		
		
			T operator[](index_type index) const {
				if (index > allocated) { throw std::runtime_error("[ALLOCATOR] - cannot access element that is out of bounds"); }
				return data[index];
			}
		
			T & operator[](index_type index) {
				if (index > allocated) { throw std::runtime_error("[ALLOCATOR] - cannot access element that is out of bounds"); }
				return data[index];
			}
		
			/**
			 Allocates memory of size blocks.
			 
			 Notes:
				- Preserves previously allocated data.
				- If there was previous data, it will move it over.
			 
			 Warning:
				- If the size of previous data > size, it will truncate the data and not destroy it.
				- You need to make sure that the data is being destroyed
			 */
			void allocate(index_type size) {
				T * newData = (T *)::operator new(size * sizeof(T));
				if (data != nullptr && allocated != 0){
					for (int i = 0; i < allocated; i ++) {
						newData[i] = std::move(data[i]);
					}
					::operator delete(data, allocated * sizeof(T));
				}
				
				data = newData;
				allocated = size;
				
				
			}
		
			/**
			 Size. Returns the amount of blocks (where a block is sizeof(T)) have been allocated.
			 */
			index_type allocatedSize() const {
				return allocated;
			}
		
		
		
		protected:
			T * data;
			index_type allocated;
	};
}


#endif /* Allocator_h */
