/* Avoiding Deadlock
1. Prefer locking single mutex.
2. Avoid locking a mutex and then calling a user provided function.
3. Use std::lock() to lock more than one mutex.
4. Lock the mutex in the same order.

Locking Granularity:
- Fine-grained lock: protects small amount of data.
- Coarse-grained lock: protects big amount of data.
*/