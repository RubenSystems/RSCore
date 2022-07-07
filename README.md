# RSCore
RubenSystems templating library for Mac and Lunix

Designed as a lightweight and performant templating library for projects that require easy customisation of and additions to standard features. 

It is header only and namespaced.


### Implemented features: 

- Allocator: Allocates contiguious blocks without calling (con/de)structors (be careful) 
- Array: Like a vector in c++  
- Text: Like a string in c++ 
- Queue: Implemented like a queue. 
- DispatchQueue: Implmeneted as a single threaded task execucutor for the execution of tasks on a seperate thread. 
	- To save resources, it only creates and reuses a single thread. 
