#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include "cell_grid.h"

const int numberX = 30;
const int numberY = 30;

void sequential_run(int infect,CellGrid* start, int iterations,int rep, long int& flops,float &avg_alive, float &avg_dead, double &time);
float avg(std::vector<float> sample);

int main()
{

    MPI_Init(NULL, NULL);
    srand((unsigned)time(0));

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int infect;
    int rep;
    int it_per_process;
    std::vector<int> infectXpositions; 
    std::vector<int> infectYpositions;

    if(world_rank == 0)
    {
        int startX,startY;

        std::cout << "Infected: " << std::endl;
        std::cin >> infect;

        infectXpositions.reserve(infect);
        infectYpositions.reserve(infect);

        CellGrid start(numberX,numberY);
        for(int i = 0; i< infect; i++)
        {
            startX = rand()%numberX;
            startY = rand()%numberY;
            if(start.at(startX,startY)->getState() == 0)
            {
                start.at(startX,startY)->setState(1);
                infectXpositions.push_back(startX);
                infectYpositions.push_back(startY);
                continue;
            }
            i--;
        }

        std::cout << "INICIO: "<<std::endl;
        start.draw();

        int iterations;
        std::cout << "Inserte el numero de iteraciones totales: ";
        std::cin >> iterations;
        
        std::cout << "Inserte el numero de repeticiones: ";
        std::cin >> rep;

        long int flops = 0;

        it_per_process = iterations/world_size;
        std::cout << "Every process should do " << it_per_process << " iterations" << std::endl;

        for(int i = 1; i < world_size;i++)
        {
            MPI_Send(&infect, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&rep, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
            MPI_Send(&it_per_process, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
            MPI_Send(&infectXpositions[0], infect, MPI_INT, i, 3, MPI_COMM_WORLD);
            MPI_Send(&infectYpositions[0], infect, MPI_INT, i, 4, MPI_COMM_WORLD);
        }
        float avgAlive, avgDead;
        double time;
        sequential_run(infect,&start,it_per_process,rep,flops,avgAlive,avgDead,time);
        
        std::vector<float> avg_alive(world_size,0);
        std::vector<float> avg_dead(world_size,0);
        std::vector<long int> total_flops(world_size,0);
        std::vector<double> times(world_size,0);
        
        avg_alive[0] = avgAlive;
        avg_dead[0] = avgDead;
        total_flops[0] = flops;
        times[0] = time;

        long int totalFlops = flops;
        for(int i = 1; i < world_size; i++)
        {
            MPI_Recv(&avg_alive[i], 1, MPI_FLOAT, i, 4+i, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE); 
            MPI_Recv(&avg_dead[i], 1, MPI_FLOAT, i, 4+world_size-1+i, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
            MPI_Recv(&total_flops[i], 1, MPI_FLOAT, i, 4+2*(world_size-1)+i, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);  
            MPI_Recv(&times[i], 1, MPI_DOUBLE, i, 4+3*(world_size-1)+i, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);  
            totalFlops += total_flops[i];
            if(times[i] > time)
            {
                time = times[i];
            }
        }
        std::cout << "Average alive: " << avg(avg_alive) << std::endl;
        std::cout << "Average dead: " << avg(avg_dead) << std::endl;
        std::cout << "Flops: " << totalFlops << std::endl;
        std::cout << "Time taken: " << time << std::endl;
    }

    else
    {
        MPI_Recv(&infect, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
        MPI_Recv(&rep, 1, MPI_INT, 0, 1, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
        MPI_Recv(&it_per_process, 1, MPI_INT, 0, 2, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
        
        infectXpositions.resize(infect);
        infectYpositions.resize(infect);

        MPI_Recv(&infectXpositions[0], infect, MPI_INT, 0, 3, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
        MPI_Recv(&infectYpositions[0], infect, MPI_INT, 0, 4, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    
        CellGrid start(numberX,numberY);
        for(int i = 0; i< infect; i++)
        {
            start.at(infectXpositions[i],infectYpositions[i])->setState(1);   
        }
        float avg_alive, avg_dead;
        double time;
        long int flops = 0;
        sequential_run(infect,&start,it_per_process,rep,flops,avg_alive,avg_dead,time);
        
        MPI_Send(&avg_alive, 1, MPI_INT, 0, 4+world_rank, MPI_COMM_WORLD);
        MPI_Send(&avg_dead, 1, MPI_INT, 0, 4+world_size-1+world_rank, MPI_COMM_WORLD);
        MPI_Send(&flops, 1, MPI_INT, 0, 4+2*(world_size-1)+world_rank, MPI_COMM_WORLD);
        MPI_Send(&time, 1, MPI_DOUBLE, 0, 4+3*(world_size-1)+world_rank, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    
    return 0;
}


float average(std::vector<int> sample)
{
    float avg = 0;
    for (int i = 0; i < sample.size(); i++)
    {
        avg += sample[i];
    }
    avg /= sample.size();
    return avg;
}

float avg(std::vector<float> sample)
{
    float avg = 0;
    for (int i = 0; i < sample.size(); i++)
    {
        avg += sample[i];
    }
    avg /= sample.size();
    return avg;
}

void sequential_run(int infect,CellGrid* start, int iterations,int rep,long int& flops, float &avg_alive, float &avg_dead, double& time)
{
    clock_t start_time = clock();
    std::vector<int> dead_history; dead_history.reserve(iterations);
    std::vector<int> alive_history; alive_history.reserve(iterations);
    
    for(int i = 0; i < iterations; i++)
    {    
        CellGrid Grid(numberX,numberY);
        Grid.copy(start);
        flops+= numberX*numberY*5;

        for(int j = 0; j < rep; j++)
        {
            if(Grid.isDead())
            {
                break;
            }
            Grid.run();
            flops += 1 + numberY*numberX*(3+11);
        }
        Grid.run(); 
        flops += numberY*numberX*(3+11);
        Grid.summary(dead_history,alive_history);
        flops += 3;
    }
    avg_alive = average(alive_history);
    avg_dead = average(dead_history);
    time = (double)(clock() - start_time)/CLOCKS_PER_SEC; 
}
