//
//  Queue.h
//  RSCore
//
//  Created by Ruben Ticehurst-James on 06/07/2022.
//

#ifndef Queue_h
#define Queue_h

#include "Allocator.h"

namespace core {
	template <typename T>
	class Queue : public Allocator<T>{
		
		public:
			Queue(typename Allocator<T>::index_type size): start(0), end(0), count(0) {
				Allocator<T>::allocate(size);
			}
		
			~Queue() {
				for (int i = 0; i < Allocator<T>::allocatedSize(); i ++) {
					Allocator<T>::operator[](i).~T();
				}
			}
		
			T & top() {
				if (size() == 0) {
					throw std::runtime_error("[QUEUE] - attempting to access top item from empty queue");
				}
				
				return Allocator<T>::operator[](start);
			}
		
			void enqueue (const T & item) {
				if (size() + 1 == Allocator<T>::allocatedSize()) {
					throw std::runtime_error("[QUEUE] - inserting into full queue");
				}
				Allocator<T>::operator[]( end ) = item;
				
				
				end = (++end % Allocator<T>::allocatedSize());
				count++;
				
			}
		
			void enqueue (T && item) {
				if (size() + 1 == Allocator<T>::allocatedSize()) {
					throw std::runtime_error("[QUEUE] - inserting into full queue");
				}
				Allocator<T>::operator[]( end ) = std::move(item);
				
				
				end = (++end % Allocator<T>::allocatedSize());
				count++;
				
			}
		
			void dequeue () {
				if (size() == 0) {
					throw std::runtime_error("[QUEUE] - nothing to dequeue");
				}
				
				// TODO: remove std lib
				Allocator<T>::operator[]( start ).~T();
				start = (++start%Allocator<T>::allocatedSize());
				count --;
			}
		
			typename Allocator<T>::index_type size() const {
				return count;
			}
			
		
		
		private :
			typename Allocator<T>::index_type start;
			typename Allocator<T>::index_type end;
			typename Allocator<T>::index_type count;
	};
}

#endif /* Queue_h */
