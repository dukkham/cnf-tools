EXECS=mpi_hello_world

all: ${EXECS}

mpi_hello_world: mpi_hello_world.c
    mpicc -o mpi_hello_world mpi_hello_world.c

clean:
    rm ${EXECS}
