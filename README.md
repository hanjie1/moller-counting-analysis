GenRoot.C
Generate a smaller root file with only valid tracks (track that fire all the wanted detectors)
The new root file has "hit" and "part" for each event. "hit" records the hits information from the valid tracks, and "part" records the initial particles information at the target (from the particle gun).

Since there is a branch based on a vector of a struct, need to use linkdef, and CMake to compile it.

In order to complie the scripts:

>> mkdir build
>> cd build
>> cmake ../
>> make 
