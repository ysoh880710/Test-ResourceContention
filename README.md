# Test-ResourceContention

## Purpose

- To verify and measure how [resource contention](https://en.wikipedia.org/wiki/Resource_contention) affects [shared resource](https://en.wikipedia.org/wiki/Shared_resource) access frequency. ([Resource contention](https://en.wikipedia.org/wiki/Resource_contention))
- To verify and measure how '[resource contention](https://en.wikipedia.org/wiki/Resource_contention) resolving mechanisms' affects [shared resource](https://en.wikipedia.org/wiki/Shared_resource) access frequency. ([Resource contention](https://en.wikipedia.org/wiki/Resource_contention) resolving mechanism)
- To verify and measure reduction of [resource contention](https://en.wikipedia.org/wiki/Resource_contention) by 'assigning a [shared resource](https://en.wikipedia.org/wiki/Shared_resource) per [thread](https://en.wikipedia.org/wiki/Thread_(computing))'. (Reduction of [resource contention](https://en.wikipedia.org/wiki/Resource_contention))

### '[Resource contention](https://en.wikipedia.org/wiki/Resource_contention) resolving mechanisms'

- [Lock](https://en.wikipedia.org/wiki/Lock_(computer_science)) (using [Interlocked API](https://docs.microsoft.com/en-us/windows/win32/sync/interlocked-variable-access))
- [Critical section](https://en.wikipedia.org/wiki/Critical_section)

### 'Assigning a [shared resource](https://en.wikipedia.org/wiki/Shared_resource) per [thread](https://en.wikipedia.org/wiki/Thread_(computing))'

- Reduction of [resource contention](https://en.wikipedia.org/wiki/Resource_contention) from 'minimum of 8 [threads](https://en.wikipedia.org/wiki/Thread_(computing)), maximum of 9 [threads](https://en.wikipedia.org/wiki/Thread_(computing)) conflicting over access to 1 [shared resource](https://en.wikipedia.org/wiki/Shared_resource)' to 'minimum of 1 [thread](https://en.wikipedia.org/wiki/Thread_(computing)), maximum of 2 [thread](https://en.wikipedia.org/wiki/Thread_(computing)) conflicting over access to 1 [shared resource](https://en.wikipedia.org/wiki/Shared_resource)' is expected.
- Resulting the increase of access frequency of [shared resources](https://en.wikipedia.org/wiki/Shared_resource).

## Requirement

- [Multi-core processor](https://en.wikipedia.org/wiki/Multi-core_processor) hardware
- Operating system

## Restriction

- [Threads](https://en.wikipedia.org/wiki/Thread_(computing)) count fixed to 8.

## Result

### [Threads](https://en.wikipedia.org/wiki/Thread_(computing)) access frequency of non [shared resource](https://en.wikipedia.org/wiki/Shared_resource) (local variable)
![NonSharedResource0](NonSharedResource0_edit.png)
![NonSharedResource1](NonSharedResource1_edit.png)
![NonSharedResource2](NonSharedResource2_edit.png)
![NonSharedResource3](NonSharedResource3_edit.png)
![NonSharedResource4](NonSharedResource4_edit.png)
![NonSharedResource5](NonSharedResource5_edit.png)
![NonSharedResource6](NonSharedResource6_edit.png)
![NonSharedResource7](NonSharedResource7_edit.png)

- Average access frequency of non [shared resource](https://en.wikipedia.org/wiki/Shared_resource) per [thread](https://en.wikipedia.org/wiki/Thread_(computing)) for 3 seconds : **2246624495** (17972995963 / 8 = 2246624495.375)

### [Threads](https://en.wikipedia.org/wiki/Thread_(computing)) access frequency of [shared resource](https://en.wikipedia.org/wiki/Shared_resource) by lock (8 threads to 1 shared resource)

![Lock0](Lock0_edit.png)

- Access frequency of [shared resource](https://en.wikipedia.org/wiki/Shared_resource) for 3 seconds : **15729828**

### [Threads](https://en.wikipedia.org/wiki/Thread_(computing)) access frequency of [shared resource](https://en.wikipedia.org/wiki/Shared_resource) by critical section (8 threads to 1 shared resource)

![CriticalSection0](CriticalSection0_edit.png)

- Access frequency of [shared resource](https://en.wikipedia.org/wiki/Shared_resource) for 3 seconds : **11937905**

### [Threads](https://en.wikipedia.org/wiki/Thread_(computing)) access frequency of a [shared resource](https://en.wikipedia.org/wiki/Shared_resource) per [thread](https://en.wikipedia.org/wiki/Thread_(computing)) by lock (1 thread to 1 shared resource)

![Lock_ThreadResource](Lock_ThreadResource_edit.png)

- Average access frequency of [shared resource](https://en.wikipedia.org/wiki/Shared_resource) per [thread](https://en.wikipedia.org/wiki/Thread_(computing)) for 3 seconds : **194424288** (1547394305 / 8 = 194424288.125)

### [Threads](https://en.wikipedia.org/wiki/Thread_(computing)) access frequency of a [shared resource](https://en.wikipedia.org/wiki/Shared_resource) per [thread](https://en.wikipedia.org/wiki/Thread_(computing)) by critical section (1 thread to 1 shared resource)

![CriticalSection_ThreadResource](CriticalSection_ThreadResource_edit.png)

- Average access frequency of [shared resource](https://en.wikipedia.org/wiki/Shared_resource) per [thread](https://en.wikipedia.org/wiki/Thread_(computing)) for 3 seconds : **177813038** (1422504303 / 8 = 177813037.875)

## Summary

|Case|Thread count|Shared resource count|[Resource contention](https://en.wikipedia.org/wiki/Resource_contention) resolving mechanisms|Access frequency|
|---|---|---|---|---|
|Non shared resource|8|0|None|2246624495|
|8 threads 1 shared resource|8|1|Lock|15729828|
|8 threads 1 shared resource|8|1|Critical section|11937905|
|8 threads each shared resource|8|8|Lock|194424288|
|8 threads each shared resource|8|8|Critical section|177813038|

### 
- Compared to access frequency of non shared resource (2246624495), access frequency of 1 shared resource by lock (15729828) was significantly small (0.70%).
- Compared to access frequency of non shared resource (2246624495), access frequency of 1 shared resource by critical section (11937905) was even smaller (0.53%).
- Compared to access frequency of non shared resource (2246624495), access frequency of shared resource per thread by lock (194424288) was small (8.65%).
- Compared to access frequency of non shared resource (2246624495), access frequency of shared resource per thread by critical section (177813038) was even smaller (7.91%).

- Compared to access frequency of 1 shared resource by lock (15729828), access frequency of shared resource per thread by lock (194424288) was significantly greater (1236.02%).
- Compared to access frequency of 1 shared resource by critical section (11937905), access frequency of shared resource per thread by critical section (177813038) was significantly greater (1489.48%).

- Compared to access frequency of shared resource per thread by critical section (11937905), access frequency of shared resource per thread by critical section (177813038) was significantly greater (1489.48%).

## Note

- [False sharing](https://en.wikipedia.org/wiki/False_sharing) causes significant degradation of performance if [shared resources](https://en.wikipedia.org/wiki/Shared_resource) per [thread](https://en.wikipedia.org/wiki/Thread_(computing)) is not aligned.
- Therefore, each [shared resource](https://en.wikipedia.org/wiki/Shared_resource) per [thread](https://en.wikipedia.org/wiki/Thread_(computing)) is aligned to cache line(64) and never accessed by other threads except owner [thread](https://en.wikipedia.org/wiki/Thread_(computing)).
