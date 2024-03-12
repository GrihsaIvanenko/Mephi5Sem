from os import system
for threads in [1, 2, 3, 4, 5, 6, 7, 8]:
    system(f"/usr/lib64/openmpi/bin/mpirun --use-hwthread-cpus -np {threads} laba")
    #system(f"./laba {threads}")
