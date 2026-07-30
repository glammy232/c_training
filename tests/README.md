Types:

    1. Moduling(unit)   One function = one method.
    2. Integrational    Modules relationships.
    3. Regressional     Old bug didn`t come back, every found bug => new test.
    4. Propery-based    Invariants on random inputs(operations).
    5. Benchmarking     Speed and size.
    6. Fazzing          Random ruined inputs - need if project has parsing or serialization.

    level 1. Smoke tests.
    level 2. Boundary value analysis.
    level 3. Property-based testing.
    level 4. Multi-step scenarios.
    level 5. Stress-tests.

Thoughts:

    1. Does it work?            Code work and return right values, doesn`t ruine a data.
    2. Does it stay correct?    Which propertyes are truly everyway?
    3. What do I promise?       For example - insert work per O(log n) - it`s must work.

    4. Test is:
        a. Корректность возврата.
        b. Отсутствие утечек.
        c. Отсутствие обращений к освобождённой памяти(use-after-free)
        d. Отсутствие buffer overflow/underflow.

Metrics:

    1. Operation time       clock_gettime() before and after, average of 1000+ iterations 
    2. Amortised difficult  Time of N operations, / on N; equal O(1) / O(log n) / O(n)
    3. Data per element     malloc_usable_size and count in castom allocator
    4. Fragmentation        Count and size of free blocks in allocator
    5. Cache misses         perf stat -e cache-misses ./bench

Instruments:

    1. ASan(AddressSanitizer).
    2. Unity.
    3. Valgrind.
    4. UBSan(UndefinedBehaviorSanitizer).
    5. Google Benchmark or time util or castom found of clock_gettime() or nanobench.
