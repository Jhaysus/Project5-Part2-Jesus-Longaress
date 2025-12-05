# Project5-Part2-Jesus-Longares

## Student infromation:

- Jesus Longares
- Id: 008685606
- https://github.com/Jhaysus/Project5-Part2-Jesus-Longaress.git
## Collaboration & Sources
- Partner: None
- Sources:
- For Cmake to work “https://stackoverflow.com/questions/7859623/how-do-i-use-cmake”
- I wanted to know how to create directories without messing up the current
- https://saco-evaluator.org.za/docs/cppreference/en/cpp/filesystem/create_directory.html
- https://en.wikipedia.org/wiki/Cache_replacement_policies
- https://www.scaler.com/topics/lru-page-replacement-algorithm/
## Implementation Details:
    - It has three parts: constructing the dataset, implementing the trace generator, and
       configuring the harness.
# Instructions on how to run
- I used CMake on Blue to compile my files.
- The CMakeLists.txt file could not be uploaded to GitHub.
- Instructions to run:
1. mkdir build
2. cd build
3. cmake ..
4. make

For Harness to run:
- make HashTablesOpenAddressing
- ./HashTablesOpenAddressing <arguments>
- <arguments> requires the trace file you want to run
- Example: ../traceFiles/lru_profile_N_1024_S_23.trace

For LRU_Profile:
- make LRU_Profile
- ./LRU_Profile <arguments>
- Arguments required: N, S, the text file to read, and the trace file
- Example: 1024 23 ../20980712_uniq_words.txt ../traceFiles/lru_profile_N_1024_S_23.trace



# # Testing & Status
I was able to run the harness but had an issue properly modifying the CSV values. It was able to run the value that I needed. Both my Clion and Blue ran out of space. I also ran into an issue with the trace generator that wouldn’t let me view what needed to be  viewed. After Thanksgiving, I worked out through the week to figure out why these issues were happening.

 ```iq_words.txt ../traceFiles/lru_profile_N_1024_S_23.trace

terminate called after throwing an instance of 'std::bad_alloc'
what(): std::bad_alloc
Aborted (core dumped)

 ```

These issues occurred due to poor coding practices and not placing values where they  should be. I also used ChatGPT to better understand the problem and see if it could help direct me toward a solution, as well as searched Reddit. However, there wasn’t any  information available that could help me resolve the issue.


