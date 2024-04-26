### open mp Directives 

1. **`#pragma omp parallel`**: Specifies a block of code to be executed by multiple threads in parallel.

2. **`#pragma omp for`**: Distributes the iterations of a loop across multiple threads for parallel execution.

3. **`#pragma omp sections`**: Divides the following code block into sections to be executed by different threads in parallel.

4. **`#pragma omp single`**: Specifies a block of code to be executed by only one thread. The single directive specifies that a block of code should be executed by only one thread.

5. **`#pragma omp master`**: Specifies a block of code to be executed only by the master thread.

6. **`#pragma omp barrier`**: Synchronizes all threads at a barrier point, ensuring that no thread proceeds beyond that point until all threads have reached it.

7. **`#pragma omp critical`**: Specifies a block of code to be executed by only one thread at a time, preventing concurrent execution by multiple threads.

8. **`#pragma omp atomic`**: Specifies an atomic operation that is executed as a single, indivisible unit, preventing data races when multiple threads access the shared variables.

9. **`flush`** : Specifies that all threads have the same view of memory for all shared objects.

10. **`ordered`** : Specifies that code under a parallelized for loop should be executed like a sequential loop.

### open mp functions 
omp_set_num_threads 	Sets the number of threads in upcoming parallel regions, unless overridden by a num_threads clause.
omp_get_num_threads 	Returns the number of threads in the parallel region.
omp_get_max_threads 	Returns an integer that is equal to or greater than the number of threads that would be available if a parallel region without num_threads were defined at that point in the code.
omp_get_thread_num 	Returns the thread number of the thread executing within its thread team.

