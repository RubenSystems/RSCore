//
//  DispatchQueue.h
//  RSCore
//
//  Created by Ruben Ticehurst-James on 06/07/2022.
//

#ifndef DispatchQueue_h
#define DispatchQueue_h

#include "Queue.h"
#include "Text.h"
#include <pthread.h>


namespace core {
	
	typedef void (*task)();
	
	
	class DispatchQueue: protected Queue<task> {
		
		public:
			DispatchQueue(int size): Queue<task>(size), running(true) {
				::pthread_create(&thread, NULL, runner, this);
				
			}
		
		
			~DispatchQueue() {
				::pthread_join(thread, NULL);
				stop();
				
			}
		
			void run(task function) {
				enqueue(function);
			}
		
			void stop() {
				running = false;
			}
		
		private:
			// U G L Y
			static void * runner(void * passthrough) {
				
				DispatchQueue * obj = (DispatchQueue *)passthrough;
				while (obj->running) {
					if (obj->size() != 0) {
						
						task newJob = obj->top();
						if(newJob) {
							(*newJob)();
						}
						obj->dequeue();
					} else {
						break;
					}
					
				}
				return NULL;
			}
		
		private:
			::pthread_t thread;
			bool running;
	};
}

#endif /* DispatchQueue_h */
