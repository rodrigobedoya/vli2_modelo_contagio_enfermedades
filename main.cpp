#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "cell_grid.h"

#define NUM_THREADS 16

const int numberX = 30;
const int numberY = 30;

void sequential_run(int infect,CellGrid* start, int iterations,int rep, long int& flops);
void parallel_run(int infect,CellGrid* start, int iterations,int rep,long int& flops);

int main()
{
    srand((unsigned)time(0));
    int startX,startY,infect;

    std::cout << "Infected: " << std::endl;
    std::cin >> infect;

    CellGrid start(numberX,numberY);
    for(int i = 0; i< infect; i++)
    {
        startX = rand()%numberX;
        startY = rand()%numberY;
        if(start.at(startX,startY)->getState() == 0)
        {
            start.at(startX,startY)->setState(1);
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
    
    long int rep;
    std::cin >> rep;

    long int flops = 0;

    std::cout << std::endl<< "Sequential:" << std::endl;
    sequential_run(infect,&start,iterations,rep,flops);
    std::cout << "Flops:" << flops << std::endl;

    flops = 0;
    std::cout << std::endl<< "Parallel with "<< NUM_THREADS << " threads:" << std::endl;
    parallel_run(infect,&start,iterations,rep,flops);
    std::cout << "Flops:" << flops << std::endl;        
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

void sequential_run(int infect,CellGrid* start, int iterations,int rep,long int& flops)
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
        //clocks += rep + rep*numberY*numberX*(3+11);

        /*std::cout << "=====================================" << std::endl;
        std::cout << "ITERACION "<< i+1 << std::endl;*/
        Grid.run(); 
        flops += numberY*numberX*(3+11);
        Grid.summary(dead_history,alive_history);
        flops += 3;
    }
    std::cout << std::endl;
    std::cout << "Average alive: " << average(alive_history) << std::endl;
    std::cout << "Average dead: " << average(dead_history) << std::endl;
    std::cout << "Time taken: " << (double)(clock() - start_time)/CLOCKS_PER_SEC << std::endl;
}

void parallel_run(int infect,CellGrid* start, int iterations,int rep,long int& flops)
{
    double start_time = omp_get_wtime();
    std::vector<int> dead_history; dead_history.reserve(iterations);
    std::vector<int> alive_history; alive_history.reserve(iterations);

    int iterations_per_thread = iterations/NUM_THREADS;

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        for(int i = 0; i < iterations_per_thread; i++)
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
            //clocks += rep + rep*numberY*numberX*(3+11);
            /*std::cout << "=====================================" << std::endl;
            std::cout << "ITERACION "<< i+1 << std::endl;*/
            Grid.run(); 
            flops += numberY*numberX*(3+11);
            Grid.summary(dead_history,alive_history);
            flops += 3;
        }
    }
    std::cout << std::endl;
    std::cout << "Average alive: " << average(alive_history) << std::endl;
    std::cout << "Average dead: " << average(dead_history) << std::endl;
    std::cout << "Time taken: " << omp_get_wtime() - start_time << std::endl;
}